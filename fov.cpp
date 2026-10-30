#include "fov.hpp"

#include <algorithm>
#include <cstdlib>
namespace {
    bool hasSight(const Map& map, int x0, int y0, int x1, int y1){
        int dx = std::abs(x1 - x0);
        int dy = -std::abs(y1-y0);
        int sx = x0 < x1 ? 1 : -1;
        int sy = y0 < y1 ? 1 : -1;
        int err = dx + dy;
        int x = x0;
        int y = y0;
        while (x != x1 || y != y1) {
            int e2 = 2 * err;
            if (e2 >= dy) {
                err += dy;
                x += sx;
            }
            if (e2 <= dx) {
                err += dx;
                y += sy;
            }
            bool atTarget = (x == x1 && y == y1);
            if (!atTarget && map.isOpaque(x,y)) {
                return false;
            }
        }
        return true;
    }
}

Fov::Fov(int width, int height): width_(width),height_(height),visible_(width * height, 0), explored_(width * height, 0) {}

bool Fov::inBounds(int x, int y) const {
    return x >= 0 && x < width_ && y >= 0 && y < height_;
}

bool Fov::isVisible(int x, int y) const {
    return inBounds(x, y) && explored_[index(x, y)];
}

bool Fov::isExplored(int x, int y) const {
    return inBounds(x, y) && explored_[index(x, y)];
}

Fov Fov::compute(const Map &map, Point origin, int radius) {
    
}

