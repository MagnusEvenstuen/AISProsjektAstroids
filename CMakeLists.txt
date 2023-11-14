cmake_minimum_required(VERSION 3.15)
project(Astroids)

set(CMAKE_CXX_STANDARD 17)

find_package(threepp CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

add_executable(Astroids main.cpp)
target_include_directories(Astroids PRIVATE include)
target_include_directories(Astroids PRIVATE textures)

target_link_libraries(Astroids PUBLIC threepp::threepp imgui::imgui)