#pragma once
#include  <random>

#include "map.hpp"
#include "rect.hpp"

Point generateDungeon(Map& map, std::mt19937&rng);