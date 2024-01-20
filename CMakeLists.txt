cmake_minimum_required(VERSION 3.28.0)

project(Shooter_2D)

add_subdirectory(include)
add_subdirectory(src)

option(
    BUILD_EXAMPLES "Whether or not to build examples"
    ON
    )

if(BUILD_EXAMPLES)
    message("Building examples...")
    add_subdirectory(examples)
endif()