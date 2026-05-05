cmake_minimum_required(VERSION 3.20)

project(
    tinydb
    VERSION 1.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(settings examples/settings.cpp)
add_executable(cache examples/cache.cpp)

option(TINYDB_BUILD_TESTS "Build the tinydb test suite" ON)

if(TINYDB_BUILD_TESTS)
    add_subdirectory(external/googletest)
    enable_testing()
    add_executable(tinydb_tests tests/test.cpp)
    target_include_directories(tinydb_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    target_link_libraries(tinydb_tests PRIVATE GTest::gtest_main)
    include(GoogleTest)
    gtest_discover_tests(tinydb_tests)
endif()

option(TINYDB_BUILD_BENCHMARKS "Build the tinydb benchmarks" ON)
if(TINYDB_BUILD_BENCHMARKS)
    set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
    set(BENCHMARK_ENABLE_INSTALL OFF CACHE BOOL "" FORCE)
    add_subdirectory(external/googlebenchmark)
    add_executable(tinydb_benchmarks benchmarks/bench.cpp)
    target_include_directories(tinydb_benchmarks PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    target_link_libraries(tinydb_benchmarks PRIVATE benchmark::benchmark_main)
endif()

