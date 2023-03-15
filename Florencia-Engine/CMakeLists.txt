#FLORENCIA ENGINE FILE
cmake_minimum_required(VERSION "3.20")
project("Florencia-Engine" VERSION "0.0.1" LANGUAGES CXX)

# Set global properties
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable C++20 modules
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmodules-ts")

# Add required external libraries
find_package(glfw3 REQUIRED)

# Add all sources to the library
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*)
add_library(${PROJECT_NAME} ${SOURCES})

# Include the directories containing the headers for the found libraries
target_include_directories(${PROJECT_NAME}
	PUBLIC
		$<INSTALL_INTERFACE:src>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

# Link libraries
target_link_libraries(${PROJECT_NAME} glfw)