cmake_minimum_required(VERSION 3.15)
project(Astroids)

set(CMAKE_CXX_STANDARD 17)

find_package(threepp CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

add_executable(Astroids astroids.cpp
        src/Astroid.cpp
        src/CollitionDetection.cpp
        src/Ship.cpp
        src/Enemy.cpp
        src/ExplotionCreator.cpp
        src/Laser.cpp
        src/ObjectCreator.cpp
        src/BaseObject.cpp
        src/GameLoop.cpp
        src/BaseShip.cpp)

target_include_directories(Astroids PRIVATE include)
target_include_directories(Astroids PRIVATE textures)
target_include_directories(Astroids PRIVATE src)

target_link_libraries(Astroids PUBLIC threepp::threepp)

add_subdirectory(tests)