// plugins/modexp_ops.cpp
#include <iostream>

namespace woflang {

long long modexp(long long base,long long exp,long long mod){
    long long res=1; base%=mod;
    while(exp>0){
        if(exp&1) res=(res*base)%mod;
        exp>>=1;
        base=(base*base)%mod;
    }
    return res;
}

} // namespace woflang
