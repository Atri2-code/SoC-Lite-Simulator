# SoC-Lite: Multicore Memory & Pipeline Simulator 🖥️⚡

[![C++ Standard](https://img.shields.io/badge/C++-17-blue.svg)](https://isocpp.org/)
[![Build System](https://img.shields.io/badge/CMake-3.14+-green.svg)](https://cmake.org/)
[![Testing](https://img.shields.io/badge/Tests-Catch2-orange.svg)](https://github.com/catchorg/Catch2)

A low-level C++ CPU and memory simulator designed to model instruction execution, hardware/software boundaries, and direct-mapped caching behavior. 

This project was built from first principles to explore the intricacies of system-level validation, memory management, and how software physically executes on simulated silicon. It emphasizes deterministic state-validation and strict numerical integrity across simulated clock cycles.

---

## 🏗️ Core Architecture

The simulator is broken down into three primary hardware abstractions:

1. **Main Memory (`Memory.h`):** * Simulates physical RAM using a dynamically allocated byte array.
   * Utilizes strict bitwise shift operators to read and write 32-bit words, ensuring accurate byte-addressing and preventing simulated memory leakage.
2. **L1 Cache (`Cache.h`):**
   * Implements a direct-mapped, write-through caching strategy.
   * Tracks hardware-level metrics including Cache Hits and Cache Misses to validate memory access optimization and execution latency.
3. **Central Processing Unit (`CPU.h`):**
   * Models the classic **Fetch-Decode-Execute** pipeline.
   * Maintains a Program Counter (PC) and an array of general-purpose 32-bit registers.
   * Executes a custom Instruction Set Architecture (ISA) via bitwise masking and decoding.

---

## 📜 Instruction Set Architecture (ISA)

The CPU decodes custom 32-bit instructions formatted as follows:

| Opcode (8 bits) | Register 1 (4 bits) | Register 2 (4 bits) | Immediate / Address (16 bits) |
| :---: | :---: | :---: | :---: |
| `[31:24]` | `[23:20]` | `[19:16]` | `[15:0]` |

### Supported Operations:
* `0x01` **LOAD**: `R1 = Mem[Imm]` (Loads a 32-bit word from memory into Register 1)
* `0x02` **STORE**: `Mem[Imm] = R1` (Stores a 32-bit word from Register 1 into memory)
* `0x03` **ADD**: `R1 = R1 + R2` (Adds the contents of R2 to R1)
* `0x04` **HALT**: Terminates the execution pipeline safely.

---

## 🚀 Build and Execution

This project uses **CMake** for cross-platform building and dependency management.

### Prerequisites
* A C++17 compatible compiler (GCC, Clang, or MSVC)
* CMake (v3.14 or higher)

### Build Instructions (Linux / macOS)
```bash
# Clone the repository
git clone [https://github.com/Atri2-code/SoC-Lite-Simulator.git](https://github.com/Atri2-code/SoC-Lite-Simulator.git)
cd SoC-Lite-Simulator

# Create a build directory
mkdir build && cd build

# Generate build files and compile
cmake ..
make
