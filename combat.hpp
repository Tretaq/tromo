#pragma once
#include <random>
#include "world.hpp"

void performAttack(World& world, Entity& attacker, Entity& defender, std::mt19937& rng);

bool playerMoveOrAttack(World& world, int dx, int dy, std::mt19937& rng);