#include "world.hpp"
#include "rng.hpp"

Entity *World::entityAt(int x, int y) {
    for (Entity& e: entities) {
        if (e.x == x && e.y == y) {
            return &e;
        }
    }
    return nullptr;
}

bool World::isBlocked(int x, int y) const {
    if (!map.isWalkable(x,y)) {
        return true;
    }
    for (const Entity& e : entities) {
        if (e.x == x && e.y == y) {
            return true;
        }
    }
    return false;
}

bool World::tryMove(Entity &e, int dx, int dy) {
    int nx =  e.x + dx;
    int ny = e.y + dy;
    if (isBlocked(nx,ny)) {
        return false;
    }
    e.x = nx;
    e.y = ny;
    return true;
}

void World::updateFov(int radius) {
    fov.compute(map, {player().x, player().y}, radius);
}

void World::ShowAll() {
    fov.togRevealAll();
}

namespace {
    struct MonsterType {
        const char* name;
        char glyph;
        int hp;
        int color;
    };
    constexpr MonsterType monsterTypes[] = {
        {"rat", 'r',3,1},
        {"goblin",'g',7,1},
        {"orc", 'o', 12,1},
    };
}
    void spawnMonsters(World& world, const std::vector<Rect>& rooms, std::mt19937& rng) {
        for (std::size_t i = 1; i < rooms.size(); i++) {
            const Rect& room = rooms[i];
            int count = randInt(rng,1,3);
            for (int ammount = 1; ammount <= count; ++ammount)
            {

                for (int attempt = 0; attempt < 10 ; ++attempt) {
                    int x = randInt(rng, room.x, room.x + room.w -1);
                    int y = randInt(rng, room.y, room.y + room.h -1);
                    if (world.isBlocked(x,y)) {
                        continue;
                    }
                    const MonsterType& t = monsterTypes[randInt(rng,0,static_cast<int>(std::size(monsterTypes))-1)];
                    world.entities.push_back({x,y,t.glyph,t.name,t.hp, t.hp,t.color});
                    break;
                }
            }
        }
    }

