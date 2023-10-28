cmake_minimum_required(VERSION 3.8)

project("counting_sort")

add_executable(${PROJECT_NAME} "main.cpp" "counting_sort.hpp")

set_target_properties(${PROJECT_NAME}
        PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)