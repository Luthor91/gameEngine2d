cmake_minimum_required(VERSION 3.22)
add_library(SDL2 SHARED IMPORTED)
set_property(TARGET SDL2 PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/SDL2-2.0.14/lib/x64/libSDL2.so)

set(SDL2_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/SDL2-2.0.14/include)
find_package(SDL2 REQUIRED)

target_link_libraries(engine SDL2::Main SDL2::Static)