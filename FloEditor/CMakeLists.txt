#FLORENCIA EDITOR FILE
cmake_minimum_required(VERSION "3.20")
project("FloEditor" VERSION "0.0.1" LANGUAGES CXX)

# Set global properties
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable C++20 modules
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmodules-ts")

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*)
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE "Florencia-Engine")
target_include_directories(${PROJECT_NAME} PRIVATE "Florencia-Engine")