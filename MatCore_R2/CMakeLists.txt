# CMakeList.txt : CMake project for MatCore_R2, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.2 FATAL_ERROR)

# Używamy c++11
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(INCLUDE_DIRS "./Dependece/glm" "./Dependece/glad/include/glad" "./Dependece/entt" "./Dependece/spdlog/include" "./Dependece/stb_image" "./Dependece/assimp/include")

# Zapisuje w zmiennej SOURCE_FILES wszystkie pliki .cpp znalezione w folderze source
file(GLOB_RECURSE RSOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")

set(SOURCE_FILES ${RSOURCE_FILES} "Dependece/glad/src/glad.c" "./Dependece/stb_image/stb_image.cpp")


add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

# Dołącza pliki nagłówkowe z folderu headers
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/headers")



# Zewnętrzne biblioteki
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS})

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory("Dependece/glfw-3.3.7")
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)

# OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC OpenGL::GL)

# assimp
target_link_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Dependece/assimp/dynamicDebug")
target_link_libraries(${PROJECT_NAME} PUBLIC assimp-vc142-mtd)

# TODO: Add tests and install targets if needed.
