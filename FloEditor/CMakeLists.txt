#FLORENCIA EDITOR FILE
cmake_minimum_required(VERSION "3.21.2")
project("FloEditor" VERSION "0.0.1" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} "src/FloEditor.ixx")

target_link_libraries(${PROJECT_NAME} PRIVATE "Florencia-Engine")
target_include_directories(${PROJECT_NAME} PRIVATE "Florencia-Engine")