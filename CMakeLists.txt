cmake_minimum_required(VERSION 3.15)
cmake_policy(SET CMP0091 NEW)
project(cimgui_example)

include(FetchContent)

# Fetch cimgui with a stable tag
FetchContent_Declare(
    cimgui
    GIT_REPOSITORY https://github.com/cimgui/cimgui.git
    GIT_TAG 1.92.1 # Matches ImGui 1.92.1 updated.
)
FetchContent_MakeAvailable(cimgui)

# Fetch GLFW
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Define cimgui sources
set(IMGUI_SOURCES
    ${cimgui_SOURCE_DIR}/cimgui.cpp
    ${cimgui_SOURCE_DIR}/imgui/imgui.cpp
    ${cimgui_SOURCE_DIR}/imgui/imgui_draw.cpp
    ${cimgui_SOURCE_DIR}/imgui/imgui_widgets.cpp
    ${cimgui_SOURCE_DIR}/imgui/imgui_demo.cpp
    ${cimgui_SOURCE_DIR}/imgui/imgui_tables.cpp
    ${cimgui_SOURCE_DIR}/imgui/backends/imgui_impl_glfw.cpp
    ${cimgui_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.cpp
)

# Build cimgui as a static library with a custom name
add_library(custom_cimgui STATIC ${IMGUI_SOURCES})

# Set include directories for custom_cimgui
target_include_directories(custom_cimgui PUBLIC
    ${cimgui_SOURCE_DIR}
    ${cimgui_SOURCE_DIR}/imgui
    ${glfw_SOURCE_DIR}/include
)

# Set compile definitions for custom_cimgui (no CIMGUI_DEFINE_ENUMS_AND_STRUCTS)
target_compile_definitions(custom_cimgui PUBLIC
    IMGUI_DISABLE_OBSOLETE_FUNCTIONS=1
    IMGUI_IMPL_API=extern\ \"C\"
)

# Link custom_cimgui with GLFW and OpenGL
target_link_libraries(custom_cimgui PUBLIC glfw OpenGL::GL)

# Application
set(APP_NAME cimgui_example2)
add_executable(${APP_NAME} src/main.c)

# Link application with custom_cimgui
target_link_libraries(${APP_NAME} PRIVATE custom_cimgui)

# Include directories for the application
target_include_directories(${APP_NAME} PUBLIC
    ${cimgui_SOURCE_DIR}
    ${cimgui_SOURCE_DIR}/imgui
    ${glfw_SOURCE_DIR}/include
)

# Set compile definitions for the application
target_compile_definitions(${APP_NAME} PRIVATE
    CIMGUI_DEFINE_ENUMS_AND_STRUCTS=1
    IMGUI_DISABLE_OBSOLETE_FUNCTIONS=1
)

# Windows-specific settings
if(WIN32)
    target_link_libraries(${APP_NAME} PRIVATE gdi32 user32 shell32)
    # target_link_options(${APP_NAME} PRIVATE -static-libgcc)

    target_link_options(${APP_NAME} PRIVATE
        -static-libgcc
        -static-libstdc++  # Uncomment if C++ code is used
        -static           # Avoid full static linking to prevent issues with system libraries
    )
endif()