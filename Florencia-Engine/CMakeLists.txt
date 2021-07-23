cmake_minimum_required(VERSION "3.21")
project("Florencia-Engine" VERSION "0.0.1" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_library(${PROJECT_NAME}
    "${CMAKE_CURRENT_SOURCE_DIR}/src/**.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/**.ixx"
)
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)