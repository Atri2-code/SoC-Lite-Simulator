#pragma once
#include "Memory.h"
#include <vector>
#include <iostream>

class Cache {
private:
    struct CacheLine {
        bool valid = false;
        uint32_t tag = 0;
        uint32_t data = 0;
    };
    std::vector<CacheLine> lines;
    Memory& main_memory;
    int hits = 0;
    int misses = 0;

public:
    Cache(size_t num_lines, Memory& mem) : lines(num_lines), main_memory(mem) {}

    uint32_t read32(uint32_t addr) {
        uint32_t index = (addr / 4) % lines.size();
        uint32_t tag = addr / (4 * lines.size());

        if (lines[index].valid && lines[index].tag == tag) {
            hits++;
            return lines[index].data;
        } else {
            misses++;
            uint32_t data = main_memory.read32(addr);
            lines[index].valid = true;
            lines[index].tag = tag;
            lines[index].data = data;
            return data;
        }
    }

    // Write-through cache strategy
    void write32(uint32_t addr, uint32_t val) {
        uint32_t index = (addr / 4) % lines.size();
        uint32_t tag = addr / (4 * lines.size());

        lines[index].valid = true;
        lines[index].tag = tag;
        lines[index].data = val;
        main_memory.write32(addr, val);
    }

    void printStats() const {
        std::cout << "Cache Performance -> Hits: " << hits << " | Misses: " << misses << "\n";
    }
};
