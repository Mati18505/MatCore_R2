# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.2 FATAL_ERROR)

project ("MatCore_R2" VERSION 1.0)
add_subdirectory ("MatCore_R2")

project ("Sandbox" VERSION 1.0)
add_subdirectory ("Sandbox")

project ("Editor" VERSION 1.0)
add_subdirectory ("Editor")
