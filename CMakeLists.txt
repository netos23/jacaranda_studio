cmake_minimum_required(VERSION 3.20)
project(jacaranda_studio C)

set(CMAKE_C_STANDARD 99)
#set(CMAKE_C_FLAGS "-arch x86_64")

find_package(OpenGL REQUIRED)

add_executable(jacaranda_studio main.c)

include_directories(
        third_party/glfw-3.3.4/include/
        third_party/glew-2.0.0/include/
        ${OPENGL_INCLUDE_DIRS}
)

add_subdirectory(third_party/glew-2.0.0/build/cmake/)
add_subdirectory(third_party/glfw-3.3.4/)
#target_link_libraries(glew_s)
add_definitions(
        -DTW_STATIC
        -DTW_NO_LIB_PRAGMA
        -DTW_NO_DIRECT3D
        #        -D_CRT_SECURE_NO_WARNINGS
)

set(ALL_LIBS ${OPENGL_LIBRARY} glfw glew)
target_link_libraries(jacaranda_studio ${ALL_LIBS})
#set_target_properties(jacaranda_studio PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}")



