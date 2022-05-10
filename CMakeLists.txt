cmake_minimum_required(VERSION 3.0.0)
project(StlComplement VERSION 0.1.0)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

include(CTest)
enable_testing()
add_subdirectory(google_test)
include_directories(google_test/googletest/include)

add_executable(dynamic_array_test src/dynamic_array_test.cpp)
target_link_libraries(dynamic_array_test  gtest gtest_main)
add_test(NAME dynamic_array_test COMMAND dynamic_array_test)

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
