// block_tracking_support.hpp
// Track block structure (start/end/type) for nested block diagnostics

#pragma once
#include <vector>
#include <string>

struct BlockInfo {
    size_t id;
    size_t startIP;
    size_t endIP;
    std::string type;  // e.g., "loop", "func", "if", etc.
};

class BlockRegistry {
public:
    void registerBlock(size_t start, size_t end, const std::string& type) {
        blocks.push_back({nextID++, start, end, type});
    }

    const std::vector<BlockInfo>& getBlocks() const {
        return blocks;
    }

    std::optional<BlockInfo> blockContaining(size_t ip) const {
        for (const auto& b : blocks) {
            if (ip >= b.startIP && ip <= b.endIP)
                return b;
        }
        return std::nullopt;
    }

private:
    std::vector<BlockInfo> blocks;
    size_t nextID = 1;
};
