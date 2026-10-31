#pragma once
#include <random>
#include <vector>
#include "entity.hpp"
#include "fov.hpp"
#include "map.hpp"
#include "rect.hpp"

struct World {
    World(int width, int height) : map(width, height), fov(width,height) {}

    Map map;
    std::vector<Entity> entities;
    Fov fov;
    Entity& player(){ return entities.front();}

    Entity* entityAt(int x, int y);
    bool isBlocked(int x, int y) const;
    bool tryMove(Entity& e, int dx, int dy);
    void updateFov();
};
void spawnMonsters(World& world, const std::vector<Rect>& room, std::mt19937& rng);