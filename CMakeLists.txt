cmake_minimum_required(VERSION 3.15)

project(RPNXCore-Benchmarks)

find_package(RPNXCore REQUIRED)
find_package(benchmark REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)

add_executable(rpnxcore-benchmark)
target_sources(rpnxcore-benchmark PRIVATE private/sources/benchmark.cpp)
target_link_libraries(rpnxcore-benchmark benchmark::benchmark benchmark::benchmark_main RPNX::rpnx-core nlohmann_json::nlohmann_json)
set_target_properties(rpnxcore-benchmark PROPERTIES CXX_STANDARD 17)
