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
            bool atTarget = (x == x1 & y == y1);
            if (!atTarget && map.isOpaque(x,y)) {
                return false;
            }
        }
        return true;
    }
}
