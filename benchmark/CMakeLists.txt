# Locate GTest
find_package(benchmark REQUIRED)
include_directories(${BENCHMARK_INCLUDE_DIRS})

# Link FqBenchmark with benchmark and gmp
add_executable(FqBenchmark FqBenchmark.cpp)
target_link_libraries(FqBenchmark benchmark::benchmark gmp Fq)
