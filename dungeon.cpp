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
