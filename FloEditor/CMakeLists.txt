cmake_minimum_required(VERSION "3.21")
project("FloEditor" VERSION "0.0.1" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} "src/FloEditor.ixx")
target_link_libraries(${PROJECT_NAME} PRIVATE "Florencia-Engine")