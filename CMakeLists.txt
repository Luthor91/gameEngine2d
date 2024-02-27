cmake_minimum_required(VERSION 3.10)
project(my_project)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_C_FLAGS "-O3")

set(SOURCES
  Core/Graphics/src/window.c
  Core/Graphics/src/button.c
  Examples/Window/button_test.c
)

set(INCLUDE_DIRS
  Core/Graphics/include
  /usr/include/SDL2
  /usr/include/SDL2_image
)

set(LIBRARIES
  SDL2
  SDL2_image
)

add_executable(gameEngine ${SOURCES})

target_include_directories(gameEngine PRIVATE ${INCLUDE_DIRS})
target_link_libraries(gameEngine PRIVATE ${LIBRARIES})