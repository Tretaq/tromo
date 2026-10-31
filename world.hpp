#pragma once
#include <random>
#include <vector>
#include "entity.hpp"
#include "fov.hpp"
#include "map.hpp"
#include "rect.hpp"

struct Message {
    std::string text;
    int color;
};
struct World {
    World(int width, int height) : map(width, height), fov(width,height) {}

    Map map;
    std::vector<Entity> entities;
    Fov fov;
    std::vector<Message> log;
    std::vector<Point> hits;
    int turn = 0;
    const Entity& player() const { return entities.front();}
     Entity& player()  { return entities.front();}
    void say(std::string text, int color);
    bool playerDead() const;
    void removeDeadMonsters();
    void endTurn();
    Entity* entityAt(int x, int y);
    bool isBlocked(int x, int y) const;
    bool tryMove(Entity& e, int dx, int dy);
    void updateFov(int radius);
    void ShowAll();
};
void spawnMonsters(World& world, const std::vector<Rect>& room, std::mt19937& rng);