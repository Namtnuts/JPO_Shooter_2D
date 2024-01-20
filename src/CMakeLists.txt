project(Shooter_2D)

set(SFML_STATIC_LIBRARIES TRUE)

set(SFML_ROOT "C://Users//glosu//Coding stuff//SFML//SFML-2.6.1//lib//cmake//SFML")

find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

add_library(Classes Game.cpp Map.cpp Ray.cpp Player.cpp Enemy.cpp Guard.cpp Path.cpp 
                    Counterterrorist.cpp Specialforce.cpp Bullet.cpp Star.cpp FinishStar.cpp)

include_directories(${CMAKE_SOURCE_DIR}/include)

target_link_libraries(Classes sfml-graphics sfml-window sfml-system)