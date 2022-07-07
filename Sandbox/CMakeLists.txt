cmake_minimum_required (VERSION 3.8)

# U¿ywamy c++11
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SRC_FILES "*.cpp")

add_executable (Sandbox ${SRC_FILES})

target_include_directories(Sandbox PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

#Do³¹czamy MatCore_R2 jako bibliotekê
target_link_libraries(Sandbox MatCore_R2)