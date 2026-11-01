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
        fov.cpp
        fov.hpp
        ai.cpp
        ai.hpp
        colors.hpp
        combat.cpp
        combat.hpp
)
target_include_directories(tromo PRIVATE ${CURSES_INCLUDE_DIR})
target_link_libraries(tromo PRIVATE ${CURSES_LIBRARIES})

target_link_options(tromo PRIVATE -static-libstdc++ -static-libgcc)

install(TARGETS tromo RUNTIME DESTINATION .)
install(FILES README.md DESTINATION . OPTIONAL)

set(CPACK_GENERATOR "ZIP")
set(CPACK_PACKAGE_NAME "tromo")
set(CPACK_PACKAGE_FILE_NAME "tromo-linux-x86_64")
include(CPack)