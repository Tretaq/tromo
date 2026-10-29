#pragma once
#include  <random>

#include "map.hpp"
#include "rect.hpp"



struct Dungeon
{
    Point start;
    std::vector<Rect> rooms;
};

Dungeon generateDungeon(Map& map, std::mt19937& rng);