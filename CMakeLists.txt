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
    set(CMAKE_BUILD_TYPE Debug FORCE)
endif()

# Find the SFML library and its required components (system, window, and graphics) and add include directories and linker flags to the project
find_package(SFML 2.5.1 COMPONENTS system window graphics REQUIRED)

# Add the 'src' directory to the list of include directories for the project
include_directories(${CMAKE_SOURCE_DIR}/src/)

# Search for all source files in the 'src' directory and add them to the variable SRC
aux_source_directory(src/ SRC)

# Create an executable named "scratch_engine2" from the source files listed in the SRC variable
add_executable(scratch_engine2 ${SRC})

# Link the SFML libraries to the 'scratch_engine2' executable
target_link_libraries(scratch_engine2 sfml-graphics sfml-window sfml-system)

# Add compiler options to the 'scratch_engine2' target. In this case, it enables some additional warnings during compilation
target_compile_options(scratch_engine2 PRIVATE -Wall -Wextra -Wpedantic)

# Install the 'scratch_engine2' executable to the 'engine' directory located in the project root directory
install(TARGETS scratch_engine2 DESTINATION ${CMAKE_SOURCE_DIR}/engine)
