#pragma once
#include "Cache.h"
#include <array>
#include <iostream>

class CPU {
private:
    Cache& cache;
    std::array<uint32_t, 16> registers{};
    uint32_t pc = 0; // Program Counter
    bool halted = false;

public:
    CPU(Cache& c) : cache(c) {}

    bool isHalted() const { return halted; }

    void tick() {
        if (halted) return;

        // 1. FETCH
        uint32_t instruction = cache.read32(pc);
        pc += 4;

        // 2. DECODE 
        // Instruction Format: Opcode [8 bits] | Reg1 [4 bits] | Reg2 [4 bits] | Immediate/Address [16 bits]
        uint8_t opcode = (instruction >> 24) & 0xFF;
        uint8_t r1     = (instruction >> 20) & 0x0F;
        uint8_t r2     = (instruction >> 16) & 0x0F;
        uint16_t imm   = instruction & 0xFFFF;

        // 3. EXECUTE
        switch (opcode) {
            case 0x01: // LOAD: R1 = Mem[Imm]
                registers[r1] = cache.read32(imm);
                break;
            case 0x02: // STORE: Mem[Imm] = R1
                cache.write32(imm, registers[r1]);
                break;
            case 0x03: // ADD: R1 = R1 + R2
                registers[r1] = registers[r1] + registers[r2];
                break;
            case 0x04: // HALT
                halted = true;
                break;
            default:
                halted = true; // Safety halt on unknown opcode
                break;
        }
    }
    
    void printState() const {
        std::cout << "CPU State -> PC: 0x" << std::hex << pc 
                  << " | R1: " << std::dec << registers[1] 
                  << " | R2: " << registers[2] << "\n";
    }
};
