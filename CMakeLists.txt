cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(image_viewer)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Dependencies
include(FetchContent)

# Raylib
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 4.5.0
)
FetchContent_MakeAvailable(raylib)

# Main executable
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# Checks if OSX and links appropriate frameworks (only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} PRIVATE "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} PRIVATE "-framework OpenGL")
endif()
