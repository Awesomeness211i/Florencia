#FLORENCIA ENGINE FILE
cmake_minimum_required(VERSION "3.21")
project("Florencia-Engine" VERSION "0.0.1" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

#add external libraries
add_subdirectory("vendor/glad")
add_subdirectory("vendor/glfw")

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*)
add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
	PUBLIC
		$<INSTALL_INTERFACE:src>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
	PRIVATE
		glfw
)
target_link_libraries(${PROJECT_NAME}
	PUBLIC
		
	PRIVATE
		glfw
)
