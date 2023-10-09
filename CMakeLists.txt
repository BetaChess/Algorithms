# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project (Algorithms)

#set(COMPILE_WARNING_AS_ERROR off)

# Add vendor projects
add_subdirectory("vendor/googletest")
add_subdirectory("vendor/benchmark")

# Include sub-projects.
add_subdirectory ("algorithms")
add_subdirectory ("benchmarks")
