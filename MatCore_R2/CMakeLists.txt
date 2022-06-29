# CMakeList.txt : CMake project for MatCore_R2, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Używamy c++11
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Zapisuje w zmiennej SRC_FILES pliki .cpp znalezione w folderze source
file(GLOB_RECURSE SRC_FILES "source/*.cpp")

# Pliki do skompilowania
add_executable (MatCore_R2 ${SRC_FILES}  "Dependece/glad/src/glad.c")

# Dołącza pliki nagłówkowe z folderu headers
target_include_directories(MatCore_R2 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/headers)

# Dołącza zewnętrzne biblioteki

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory("Dependece/glfw-3.3.7")
target_link_libraries(MatCore_R2 glfw)

# OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(MatCore_R2 OpenGL::GL)

# glm
set(GLM_INCLUDE_DIRS "./Dependece/glm")
target_include_directories(MatCore_R2 PUBLIC ${GLM_INCLUDE_DIRS})

# glad
set(GLAD_INCLUDE_DIRS "./Dependece/glad/include/glad")
target_include_directories(MatCore_R2 PUBLIC ${GLAD_INCLUDE_DIRS})

# entt
set(ENTT_INCLUDE_DIRS "./Dependece/entt")
target_include_directories(MatCore_R2 PUBLIC ${ENTT_INCLUDE_DIRS})



# TODO: Add tests and install targets if needed.
