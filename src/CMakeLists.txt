cmake_minimum_required(VERSION 3.5)
project(VirusGame)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (WIN32)
  find_package(SDL2 CONFIG REQUIRED)     # check if SDL2     is installed
  find_package(sdl2-gfx CONFIG REQUIRED) # check if SDL2_gfx is installed
endif (WIN32)
if (UNIX)
  list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)
  find_package(SDL2 REQUIRED)     # check if SDL2     is installed
  find_package(SDL2_gfx REQUIRED) # check if SDL2_gfx is installed
endif (UNIX)

include_directories(${SDL2_INCLUDE_DIRS})
find_path(SYSTEM_INCLUDE_DIR SDL2/SDL.h)
include_directories(${SYSTEM_INCLUDE_DIR})

add_executable(VirusGame VirusGame.cpp)

if (WIN32)
  target_link_libraries(VirusGame PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2::SDL2_gfx)
  target_compile_options(VirusGame PRIVATE /W4)
endif (WIN32)
if (UNIX)
  target_link_libraries(VirusGame PRIVATE SDL2::Main SDL2::GFX)
  target_compile_options(VirusGame PRIVATE -Wall -Wextra -pedantic)
endif (UNIX)
