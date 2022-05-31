# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
find_package(benchmark REQUIRED)
include_directories(${BENCHMARK_INCLUDE_DIRS})

# Link runTests with what we want to test and the GTest and pthread library
add_executable(FqTests FqTest.cpp TestDependencies.h)
add_executable(Fq2Tests Fq2Tests.cpp)
target_link_libraries(FqTests ${GTEST_LIBRARIES} FqBig pthread)
target_link_libraries(Fq2Tests ${GTEST_LIBRARIES} Fq2 Fq pthread)