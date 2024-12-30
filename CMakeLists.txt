# Set the minimum required version of CMake
# Default compiler used for this CMake is GCC 12.2.1 x86_64-pc-linux-gnu
cmake_minimum_required(VERSION 3.25.2)

# Set the project name and version number
project(scratch_engine2 VERSION 0.0.1)

# Disable the use of C++ language extensions and enforce the use of the specified C++ standard
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# If build type is not specified, set it to Debug
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Find the SFML library and its required components (system, window, and graphics)
find_package(SFML COMPONENTS System Window Graphics REQUIRED)

# Search for all source files in the 'src' directory and add them to the variable SRC
file(GLOB SRC "${CMAKE_SOURCE_DIR}/src/*.cpp")

# Create an executable named "scratch_engine2" from the source files listed in the SRC variable
add_executable(scratch_engine2 ${SRC})

# Add include directories and linker flags to the 'scratch_engine2' target
target_include_directories(scratch_engine2 PRIVATE ${CMAKE_SOURCE_DIR}/src/)
target_link_libraries(scratch_engine2 PRIVATE SFML::Graphics SFML::Window SFML::System)

# Add compiler options to the 'scratch_engine2' target
target_compile_options(scratch_engine2 PRIVATE -g -Og -Wall -Wextra -Wpedantic)

# Install the 'scratch_engine2' executable to the 'bin' directory
install(TARGETS scratch_engine2 DESTINATION engine)
