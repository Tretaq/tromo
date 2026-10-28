#include "dungeon.hpp"

#include <algorithm>
#include <cstdlib>
#include <vector>

#include "map.hpp"

namespace {
    int randInt(std::mt19937& rng, int lo , int hi) {
        return std::uniform_int_distribution<int>(lo,hi)(rng);
    }
    void carveHorizontal(Map& map, int x1, int x2, int y) {
        map.fillRect(std::min(x1, x2), y, std::abs(x2-x1) + 1, 1 , Tile::Floor);
    }
    void carveVertical(Map& map, int y1, int y2, int x) {
        map.fillRect(x,std::min(y1,y2), 1, std::abs(y2 - y1) + 1, Tile::Floor);
    }
    void connect(Map &map, std::mt19937 rng, Point a, Point b) {
        if (randInt(rng, 0, 1) == 0) {
            carveHorizontal(map, a.x, b.x,a.y);
            carveVertical(map, a.y, b.y , b.x);
        } else {
            carveHorizontal(map, a.y, b.y,a.x);
            carveVertical(map, a.x, b.x , b.y);
        }
    }
}

Point generateDungeon(Map &map, std::mt19937 &rng)
{
    constexpr int maxRooms = 12;
    constexpr int attempts = 60;
    constexpr int minW = 4, maxw = 12, minH = 4, maxh = 12;

    std::vector<Rect> rooms;
    for (int i = 0; i < attempts && static_cast<int>(rooms.size()) < maxRooms; ++i)
    {
        int w = randInt(rng, minW, maxw);
        int h = randInt(rng, minH, maxh);
        int x = randInt(rng,1, map.width()-w-1);
        int y = randInt(rng,1,map.height()-h-1);
        Rect room = Rect(x,y,w,h);

        bool overlaps = std::any_of(rooms.begin(), rooms.end(),
            [&](const Rect other)
            {
                return room.intersects(other); });

        if (!overlaps)
        {
            continue;
        }
        map.fillRect(room.w,room.y,room.w,room.h,Tile::Floor);
        if (!rooms.empty())
        {
            connect(map, rng, rooms.back().center(), room.center());
        }
        rooms.push_back(room);
    }
    return rooms.front().center();
}