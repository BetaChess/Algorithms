cmake_minimum_required (VERSION 3.8)

project (insertion_sort)

add_executable(${PROJECT_NAME} "main.cpp" "insertion_sort.h" "insertion_sort.cpp")

set_target_properties(${PROJECT_NAME}
	PROPERTIES
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED YES
	CXX_EXTENSIONS NO
	)