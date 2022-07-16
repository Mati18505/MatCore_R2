cmake_minimum_required (VERSION 3.16 FATAL_ERROR)

# U¿ywamy c++11
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SRC_FILES "*.cpp")

add_executable (${PROJECT_NAME} ${SRC_FILES})

#target_precompile_headers(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../MatCore_R2/headers/MatCore.h")

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Do³¹czamy MatCore_R2 jako bibliotekê
target_link_libraries(${PROJECT_NAME} PUBLIC MatCore_R2)