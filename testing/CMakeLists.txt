cmake_minimum_required(VERSION 3.8)


project("tests")

add_executable(${PROJECT_NAME} "sorting.cpp")


target_include_directories(${PROJECT_NAME}
        PUBLIC ../../vendor/googletest/googletest/include
        PUBLIC ../src
)

target_link_directories(${PROJECT_NAME}
        PRIVATE ../vendor/googletest/
)

target_link_libraries(${PROJECT_NAME} PUBLIC
        gtest_main
        #	suuri
)

set_target_properties(${PROJECT_NAME}
        PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)

add_test(
        NAME ${PROJECT_NAME}
        COMMAND ${PROJECT_NAME}
)