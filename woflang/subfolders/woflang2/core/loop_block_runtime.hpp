// loop_block_runtime.hpp
// Loop block support: push/pop loop frames for ⟳ ⨯ ⍺ blocks

#pragma once
#include <stack>
#include <optional>
#include <string>

struct LoopFrame {
    size_t startIP;
    size_t endIP;
    std::optional<int64_t> counter;  // only for repeat/for
    std::string type;                // "loop", "repeat", "for"
};

class LoopContext {
public:
    void push(const LoopFrame& frame) {
        frames.push(frame);
    }

    void pop() {
        if (!frames.empty()) frames.pop();
    }

    std::optional<LoopFrame> current() const {
        if (frames.empty()) return std::nullopt;
        return frames.top();
    }

    bool hasActiveLoop() const {
        return !frames.empty();
    }

    void breakLoop(size_t& ip) {
        if (hasActiveLoop()) {
            ip = frames.top().endIP;  // jump to ⺘
            pop();
        }
    }

    void continueLoop(size_t& ip) {
        if (hasActiveLoop()) {
            ip = frames.top().startIP;  // jump back to ⺆
        }
    }

private:
    std::stack<LoopFrame> frames;
};
