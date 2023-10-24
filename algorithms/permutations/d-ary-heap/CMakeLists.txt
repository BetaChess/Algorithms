cmake_minimum_required(VERSION 3.8)

project("daryheap")

add_executable(${PROJECT_NAME} "main.cpp" "daryheap.h")

target_include_directories(${PROJECT_NAME}
        PUBLIC ../../
)

set_target_properties(${PROJECT_NAME}
        PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)