#include <catch2/catch_test_macros.hpp>
#include "../src/Memory.h"
#include "../src/Cache.h"
#include "../src/CPU.h"

TEST_CASE("CPU Execution and Cache Validation", "[cpu]") {
    Memory mem(1024);
    Cache cache(8, mem);
    CPU cpu(cache);

    // Load simple ADD program
    mem.write32(0x00, 0x01100100); // LOAD R1, [0x0100]
    mem.write32(0x04, 0x01200104); // LOAD R2, [0x0104]
    mem.write32(0x08, 0x03120000); // ADD R1, R2
    mem.write32(0x0C, 0x02100108); // STORE R1, [0x0108]
    mem.write32(0x10, 0x04000000); // HALT

    // Write input variables
    mem.write32(0x0100, 15);
    mem.write32(0x0104, 25);

    // Execute
    while (!cpu.isHalted()) {
        cpu.tick();
    }

    // Validate memory integrity
    REQUIRE(mem.read32(0x0108) == 40);
}
