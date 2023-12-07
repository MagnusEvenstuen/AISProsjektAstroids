add_library(libsrc Astroid.cpp BaseObject.cpp BaseShip.cpp CollitionDetection.cpp Enemy.cpp
            ExplotionCreator.cpp GameLoop.cpp Laser.cpp ObjectCreator.cpp Ship.cpp)

target_include_directories(libsrc PUBLIC ${CMAKE_SOURCE_DIR}/include)

find_package(threepp CONFIG REQUIRED)

target_link_libraries(libsrc PUBLIC threepp::threepp)