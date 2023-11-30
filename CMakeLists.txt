cmake_minimum_required(VERSION 3.15)
project(Astroids)

set(CMAKE_CXX_STANDARD 17)

find_package(threepp CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

add_executable(Astroids astroids.cpp
        src/Astroid.cpp
        src/CollitionDetection.cpp
        src/Controls.cpp
        src/Enemy.cpp
        src/Explotion.cpp
        src/Game.cpp
        src/LaserControls.cpp
        src/ObjectCreator.cpp
        src/ObjectUpdater.cpp)

target_include_directories(Astroids PRIVATE include)
target_include_directories(Astroids PRIVATE textures)

target_link_libraries(Astroids PUBLIC threepp::threepp)

#add_subdirectory(tests)