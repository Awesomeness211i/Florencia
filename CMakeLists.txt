#WORKING DIRECTORY FILE
cmake_minimum_required(VERSION "3.20")
project("Florencia" VERSION "0.0.1" LANGUAGES CXX)

# Set global properties
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable C++20 modules
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmodules-ts")

# Add subdirectories for engine
add_subdirectory("Florencia-Engine")
add_subdirectory("FloEditor")