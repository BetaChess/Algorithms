# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required(VERSION 3.8)

project(Algorithms)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "-Wno-narrowing ${CMAKE_CXX_FLAGS}")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS "-DNOMINMAX ${CMAKE_CXX_FLAGS}") # exclude M$ min/max macros
    set(CMAKE_CXX_FLAGS "/wd4996 ${CMAKE_CXX_FLAGS}") # don't warn about use of plain C functions without (non-portable) "_s" suffix
    set(CMAKE_CXX_FLAGS "/wd4244 ${CMAKE_CXX_FLAGS}") # don't warn about use of plain C functions without (non-portable) "_s" suffix
    set(CMAKE_EXE_LINKER_FLAGS "/WX:NO ${CMAKE_EXE_LINKER_FLAGS}") # don't treat warnings as compile errors--gtest doesn't build
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /STACK:4194304")
endif ()


enable_testing()
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)


# Add vendor projects
add_subdirectory("vendor/googletest")
add_subdirectory("vendor/benchmark")

# Include sub-projects.
add_subdirectory("algorithms")
add_subdirectory("benchmarks")
add_subdirectory("testing")