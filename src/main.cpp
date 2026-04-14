#include "Memory.h"
#include "Cache.h"
#include "CPU.h"
#include <iostream>

int main() {
    std::cout << "--- Booting SoC-Lite Simulator ---\n";

    Memory mem(1024);     // 1KB Main Memory
    Cache cache(16, mem); // 16-line Cache
    CPU cpu(cache);

    // --- LOAD DUMMY PROGRAM ---
    // Instruction Format: Opcode [8] | Reg1 [4] | Reg2 [4] | Imm [16]
    
    // 1. LOAD R1, [0x0100] -> Opcode 0x01, R1=1, R2=0, Imm=0x0100 => 0x01100100
    mem.write32(0x00, 0x01100100);
    mem.write32(0x0100, 42); // Seed data

    // 2. LOAD R2, [0x0104] -> Opcode 0x01, R1=2, R2=0, Imm=0x0104 => 0x01200104
    mem.write32(0x04, 0x01200104);
    mem.write32(0x0104, 10); // Seed data

    // 3. ADD R1, R2 -> Opcode 0x03, R1=1, R2=2, Imm=0x0000 => 0x03120000
    mem.write32(0x08, 0x03120000);

    // 4. STORE R1, [0x0108] -> Opcode 0x02, R1=1, R2=0, Imm=0x0108 => 0x02100108
    mem.write32(0x0C, 0x02100108);

    // 5. HALT -> Opcode 0x04 => 0x04000000
    mem.write32(0x10, 0x04000000);

    // --- RUN CLOCK CYCLES ---
    int cycles = 0;
    while (!cpu.isHalted() && cycles < 1000) {
        cpu.tick();
        cycles++;
    }

    std::cout << "Simulation HALTED after " << cycles << " clock cycles.\n";
    cpu.printState();
    cache.printStats();

    uint32_t result = mem.read32(0x0108);
    std::cout << "Final Calculation in Memory [0x0108]: " << result << " (Expected 52)\n";
    std::cout << "--- Shutdown Complete ---\n";

    return 0;
}
