cmake_minimum_required(VERSION 3.25.2)
project(scratch_engine2 VERSION 0.0.1)

# set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug FORCE)
endif()

find_package(SFML 2.5.1 COMPONENTS system window graphics REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/src/)
aux_source_directory(src/ SRC)
add_executable(scratch_engine2 ${SRC})

target_link_libraries(scratch_engine2 sfml-graphics sfml-window sfml-system)
target_compile_options(scratch_engine2 PRIVATE -Wall -Wextra -Wpedantic)

install(TARGETS scratch_engine2 DESTINATION ${CMAKE_SOURCE_DIR}/engine)
