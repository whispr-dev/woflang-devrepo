// plugins/crypto_ops.cpp
#ifndef WOFLANG_PLUGIN_EXPORT
#  ifdef _WIN32
#    define WOFLANG_PLUGIN_EXPORT extern "C" __declspec(dllexport)
#  else
#    define WOFLANG_PLUGIN_EXPORT extern "C"
#  endif
#endif

#include "core/woflang.hpp"
#include <array>
#include <cstdint>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>
#include <stack>

namespace woflang {

static inline double need_num(const WofValue& v, const char* op){
    if (!v.is_numeric()) throw std::runtime_error(std::string(op)+": numeric required");
    return v.as_numeric();
}

static std::string to_hex_bytes(const std::vector<uint8_t>& bytes) {
    static const char* hex = "0123456789abcdef";
    std::string out; out.reserve(bytes.size()*2);
    for (uint8_t b: bytes){ out.push_back(hex[b>>4]); out.push_back(hex[b&15]); }
    return out;
}
static std::vector<uint8_t> from_hex_bytes(const std::string& s) {
    auto H=[&](char c)->int{
        if(c>='0'&&c<='9') return c-'0';
        if(c>='a'&&c<='f') return c-'a'+10;
        if(c>='A'&&c<='F') return c-'A'+10;
        return -1;
    };
    if (s.size()%2) throw std::runtime_error("from_hex: odd length");
    std::vector<uint8_t> out; out.reserve(s.size()/2);
    for(size_t i=0;i<s.size();i+=2){
        int hi=H(s[i]), lo=H(s[i+1]);
        if(hi<0||lo<0) throw std::runtime_error("from_hex: bad digit");
        out.push_back(uint8_t((hi<<4)|lo));
    }
    return out;
}

static const char* B64="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static std::string b64_encode(const std::vector<uint8_t>& data){
    std::string out; out.reserve(((data.size()+2)/3)*4);
    size_t i=0; while(i+3<=data.size()){
        uint32_t n=(data[i]<<16)|(data[i+1]<<8)|data[i+2]; i+=3;
        out.push_back(B64[(n>>18)&63]); out.push_back(B64[(n>>12)&63]);
        out.push_back(B64[(n>>6)&63]);  out.push_back(B64[n&63]);
    }
    if(i+1==data.size()){
        uint32_t n=(data[i]<<16);
        out.push_back(B64[(n>>18)&63]); out.push_back(B64[(n>>12)&63]);
        out.push_back('='); out.push_back('=');
    }else if(i+2==data.size()){
        uint32_t n=(data[i]<<16)|(data[i+1]<<8);
        out.push_back(B64[(n>>18)&63]); out.push_back(B64[(n>>12)&63]);
        out.push_back(B64[(n>>6)&63]); out.push_back('=');
    }
    return out;
}
static std::vector<uint8_t> b64_decode(const std::string& s){
    std::array<int,256> T{}; T.fill(-1);
    for(int i=0;i<64;++i) T[uint8_t(B64[i])] = i;
    std::vector<uint8_t> out; int val=0, valb=-8;
    for(unsigned char c: s){
        if(c=='=') break;
        int d=T[c]; if(d<0) continue;
        val=(val<<6)|d; valb+=6;
        if(valb>=0){ out.push_back(uint8_t((val>>valb)&0xFF)); valb-=8; }
    }
    return out;
}

class CryptoOpsPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& I) override {

        // to_hex: string -> hex string
        I.register_op("to_hex", [](std::stack<WofValue>& S){
            if (S.size() < 1) throw std::runtime_error("to_hex: stack underflow");
            auto v = S.top(); S.pop();
            if (v.type != WofType::String && v.type != WofType::Symbol)
                throw std::runtime_error("to_hex: expected string/symbol");
            const auto& s = std::get<std::string>(v.value);
            std::vector<uint8_t> b(s.begin(), s.end());
            S.push(WofValue(to_hex_bytes(b)));
        });

        // from_hex: hex string -> raw string
        I.register_op("from_hex", [](std::stack<WofValue>& S){
            if (S.size() < 1) throw std::runtime_error("from_hex: stack underflow");
            auto v = S.top(); S.pop();
            if (v.type != WofType::String && v.type != WofType::Symbol)
                throw std::runtime_error("from_hex: expected string/symbol");
            auto bytes = from_hex_bytes(std::get<std::string>(v.value));
            S.push(WofValue(std::string(bytes.begin(), bytes.end())));
        });

        // base64_encode: string -> b64
        I.register_op("base64_encode", [](std::stack<WofValue>& S){
            if (S.size() < 1) throw std::runtime_error("base64_encode: stack underflow");
            auto v = S.top(); S.pop();
            if (v.type != WofType::String && v.type != WofType::Symbol)
                throw std::runtime_error("base64_encode: expected string/symbol");
            const auto& s = std::get<std::string>(v.value);
            std::vector<uint8_t> b(s.begin(), s.end());
            S.push(WofValue(b64_encode(b)));
        });

        // base64_decode: b64 -> raw string
        I.register_op("base64_decode", [](std::stack<WofValue>& S){
            if (S.size() < 1) throw std::runtime_error("base64_decode: stack underflow");
            auto v = S.top(); S.pop();
            if (v.type != WofType::String && v.type != WofType::Symbol)
                throw std::runtime_error("base64_decode: expected string/symbol");
            auto bytes = b64_decode(std::get<std::string>(v.value));
            S.push(WofValue(std::string(bytes.begin(), bytes.end())));
        });

        // random: -> [0,1)
        I.register_op("random", [](std::stack<WofValue>& S){
            static thread_local std::mt19937_64 rng{std::random_device{}()};
            std::uniform_real_distribution<double> d(0.0,1.0);
            S.push(WofValue(d(rng)));
        });

        // random_bytes: n -> raw string of n bytes
        I.register_op("random_bytes", [](std::stack<WofValue>& S){
            if (S.size() < 1) throw std::runtime_error("random_bytes: stack underflow");
            auto nV = S.top(); S.pop();
            int n = static_cast<int>(need_num(nV,"random_bytes"));
            if (n < 0 || n > 1'000'000) throw std::runtime_error("random_bytes: n out of range");
            static thread_local std::mt19937_64 rng{std::random_device{}()};
            std::uniform_int_distribution<int> d(0,255);
            std::string s; s.resize(n);
            for(int i=0;i<n;++i) s[i]=char(d(rng));
            S.push(WofValue(std::move(s)));
        });
    }
};

} // namespace woflang

WOFLANG_PLUGIN_EXPORT void register_plugin(woflang::WoflangInterpreter& interp) {
    static woflang::CryptoOpsPlugin plugin;
    plugin.register_ops(interp);
}
