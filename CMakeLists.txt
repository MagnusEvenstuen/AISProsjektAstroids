cmake_minimum_required(VERSION 3.15)
project(Astroids)

set(CMAKE_CXX_STANDARD 20)

find_package(threepp CONFIG REQUIRED)

add_executable(Astroids astroids.cpp)

target_include_directories(Astroids PUBLIC include)
target_include_directories(Astroids PUBLIC textures)

add_subdirectory(${CMAKE_SOURCE_DIR}/src)

target_link_libraries(Astroids PUBLIC threepp::threepp PUBLIC libsrc)

#Testing

enable_testing()
add_subdirectory(${CMAKE_SOURCE_DIR}/tests)