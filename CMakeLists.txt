cmake_minimum_required(VERSION 3.20)
project(tromo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED  ON)

find_package(Curses REQUIRED)

add_executable(tromo main.cpp
        map.cpp
        map.hpp
        rect.hpp
        dungeon.hpp
        dungeon.cpp
        rng.hpp
        entity.hpp
        world.hpp
        world.cpp
)
target_include_directories(tromo PRIVATE ${CURSES_INCLUDE_DIR})
target_link_libraries(tromo PRIVATE ${CURSES_LIBRARIES})