add_executable(Tests tests.cpp)
add_test(NAME Tests COMMAND Tests)

find_package(Catch2 CONFIG REQUIRED)
target_link_libraries(Tests PRIVATE Catch2::Catch2WithMain)

target_include_directories(Tests PRIVATE ../include)

target_link_libraries(Tests PUBLIC threepp::threepp imgui::imgui)