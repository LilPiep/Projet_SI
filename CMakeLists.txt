CMAKE_MINIMUM_REQUIRED(VERSION 3.7)
PROJECT(project)

SET(CMAKE_CXX_STANDARD 14)
SET(CMAKE_BUILD_TYPE DEBUG)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(/home/pierrick/glfw /home/pierrick/glfw/src)


FIND_PACKAGE(OpenGL REQUIRED)

SET(SOURCE_FILES main.cpp glad.c EBO.cpp shaderClass.cpp VAO.cpp VBO.cpp stb.cpp texture.cpp camera.cpp mesh.cpp model.cpp)

ADD_EXECUTABLE(project ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(project glfw)
TARGET_LINK_LIBRARIES(project OpenGL::GL)