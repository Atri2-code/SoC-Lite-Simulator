cmake_minimum_required(VERSION 3.14)
project(SoC_Lite_Simulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(src)

# Main Executable
add_executable(soc_simulator src/main.cpp)

# Fetch Catch2 Testing Framework
include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0
)
FetchContent_MakeAvailable(Catch2)

# Test Executable
add_executable(soc_tests tests/test_cpu.cpp)
target_link_libraries(soc_tests PRIVATE Catch2::Catch2WithMain)
