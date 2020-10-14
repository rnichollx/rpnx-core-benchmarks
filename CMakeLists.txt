cmake_minimum_required(VERSION 3.15)

project(RPNXCore-Benchmarks)

find_package(RPNXCore REQUIRED)
find_package(benchmark REQUIRED)

add_executable(rpnxcore-benchmark)
target_sources(rpnxcore-benchmark PRIVATE private/sources/benchmark.cpp)
target_link_libraries(rpnxcore-benchmark benchmark::benchmark benchmark::benchmark_main RPNX::rpnx-core)
set_target_properties(rpnxcore-benchmark PROPERTIES CXX_STANDARD 17)
target_include_directories(rpnxcore-benchmark PRIVATE private/third-party-include)
