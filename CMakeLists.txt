cmake_minimum_required(VERSION 3.16)

project(DictionaryApp)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(
    DictionaryApp

    src/main.cpp

    external/imgui/imgui.cpp
    external/imgui/imgui_draw.cpp
    external/imgui/imgui_tables.cpp
    external/imgui/imgui_widgets.cpp

    external/imgui/backends/imgui_impl_glfw.cpp
    external/imgui/backends/imgui_impl_opengl3.cpp
)

target_include_directories(
    DictionaryApp PRIVATE

    external/imgui
    external/imgui/backends
)

target_link_libraries(
    DictionaryApp

    glfw
    OpenGL::GL
)