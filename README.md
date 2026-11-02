# Tromo

Tromo is a small rougelike for the terminal currently half done, written in C++ with ncurses.


Done for terra <3 
Theme: Vintage

## Features 

- Randomly genarated dungeons: random rooms watter pools and corridors.
- Redo runs: By passing a seed after command u can reproduce seeds
- Fov and Fog: you have explored areas and Field of view
- Turn Based: Word only moves when you move
- Monster Ai: If monster sees you it moves to you. 
- Combat: you can miss, crit and defence reducess attack.
- Color: message lof, Hp , hit flashes, slow healing.
- Death screen.
## Build

You need a C++20 compiler, CMake 3.20+ and the ncurses development files.

```shell
git clone https://github.com/Tretaq/tromo
cd tromo
cmake -S . -B build
cmake --build build
./build/tromo
```

Run with specific seed:

```shell
./build/tromo 12345
```

Your terminal needs to be big enough for you to play it, otherwise you won't see everything.

## Controls

| Key | Action |
|-----|--------|
| Arrow keys / `w a s d` / `h j k l` | Move (walk into a monster to attack it) |
| `.` or Space | Wait one turn |
| `=` / `-` | Increase / decrease sight radius |
| `m` | Toggle "reveal whole map" (debug) |
| `r` | New dungeon (also retries after death) |
| `q` | Quit |

Going into a wall, or using 'm', '=', '-', 'r', does not use up a turn.

## Just try it! 

```shell
git clone https://github.com/Tretaq/tromo.git
cd tromo
cmake -S . -B build -DCMAKE_BUILD_TYPE=Relase
cmake --build build -j
./build/tromo
```
## TO DO 
- Items 
- More monsters
- make it more scarry
- levels
- classes? 