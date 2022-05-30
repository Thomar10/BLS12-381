# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Link runTests with what we want to test and the GTest and pthread library
add_executable(FqTests FqTest.cpp)
target_link_libraries(FqTests ${GTEST_LIBRARIES} Fq pthread)