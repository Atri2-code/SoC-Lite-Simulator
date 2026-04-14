#pragma once
#include <vector>
#include <cstdint>

class Memory {
private:
    std::vector<uint8_t> mem;

public:
    // Initialize memory with a specific size in bytes
    Memory(size_t size) : mem(size, 0) {}

    // Read a 32-bit word using bitwise shifts
    uint32_t read32(uint32_t addr) {
        if (addr + 3 >= mem.size()) return 0; // Memory boundary safeguard
        return (mem[addr] << 24) | (mem[addr+1] << 16) | (mem[addr+2] << 8) | mem[addr+3];
    }

    // Write a 32-bit word
    void write32(uint32_t addr, uint32_t val) {
        if (addr + 3 >= mem.size()) return;
        mem[addr]   = (val >> 24) & 0xFF;
        mem[addr+1] = (val >> 16) & 0xFF;
        mem[addr+2] = (val >> 8)  & 0xFF;
        mem[addr+3] =  val        & 0xFF;
    }
};
