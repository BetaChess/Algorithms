cmake_minimum_required(VERSION 3.8)

project("merge_sort")

add_executable(${PROJECT_NAME} "main.cpp" "merge_sort.hpp")

set_target_properties(${PROJECT_NAME}
        PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)