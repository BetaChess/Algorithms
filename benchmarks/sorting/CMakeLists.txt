cmake_minimum_required(VERSION 3.8)

project("sorting_benchmark")

add_executable(${PROJECT_NAME} "sorting_benchmark.cpp")

target_include_directories(${PROJECT_NAME}
        PUBLIC ../../vendor/benchmark/include
        PUBLIC ../../src
)

target_link_directories(${PROJECT_NAME}
        PRIVATE ../../vendor/benchmark
)

target_link_libraries(${PROJECT_NAME}
        benchmark::benchmark
)

set_target_properties(${PROJECT_NAME}
        PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)