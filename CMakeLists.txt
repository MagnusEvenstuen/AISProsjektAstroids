cmake_minimum_required(VERSION 3.15)
project(placeholder)

set(CMAKE_CXX_STANDARD 17)

find_package(threepp CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

add_executable(placeholder main.cpp)
target_include_directories(placeholder PRIVATE include)

target_link_libraries(placeholder PUBLIC threepp::threepp imgui::imgui)