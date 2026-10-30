#include "dungeon.hpp"
#include <algorithm>
#include <cstdlib>
#include <vector>
#include "map.hpp"
#include "rng.hpp"
namespace {

    void carveHorizontal(Map& map, int x1, int x2, int y) {
        map.fillRect(std::min(x1, x2), y, std::abs(x2-x1) + 1, 1 , Tile::Floor);
    }
    void carveVertical(Map& map, int y1, int y2, int x) {
        map.fillRect(x,std::min(y1,y2), 1, std::abs(y2 - y1) + 1, Tile::Floor);
    }
    void connect(Map &map, std::mt19937& rng, Point a, Point b) {
        if (randInt(rng, 0, 1) == 0) {
            carveHorizontal(map, a.x, b.x,a.y);
            carveVertical(map, a.y, b.y , b.x);
        } else {
            carveVertical(map, a.y, b.y, a.x);
            carveHorizontal(map, a.x, b.x, b.y);
        }
    }
}

Dungeon generateDungeon(Map &map, std::mt19937 &rng)
{
    constexpr int maxRooms = 8;
    constexpr int attempts = 30;
    constexpr int minW = 6, maxw = 12, minH = 6, maxh = 9;
    constexpr  int watW = 2, watH = 2;

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

        if (overlaps)
        {
            continue;
        }
        map.fillRect(room.x,room.y,room.w,room.h,Tile::Floor);

        int xw = randInt(rng,x, x + w - watW  );
        int yw = randInt(rng, y, y + h - watH);
        map.fillRect(xw,yw, watW, watH, Tile::Water);



        if (!rooms.empty())
        {
            connect(map, rng, rooms.back().center(), room.center());
        }
        rooms.push_back(room);
    }
    const int count = static_cast<int>(rooms.size());
    if (count >= 3) {
        int a, b;
        do {
            a = randInt(rng,0,count-1);
            b = randInt(rng,0,count-1);
        } while (std::abs(a-b) < 2);
        connect(map, rng, rooms[a].center(), rooms[b].center());
    }
    return {rooms.front().center(),  rooms};
}