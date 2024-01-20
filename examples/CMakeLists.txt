project(Shooter_2D)

add_executable(main main.cpp)

include_directories(${CMAKE_SOURCE_DIR}/include)

target_link_libraries(main Classes)