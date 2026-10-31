#include "ai.hpp"

#include <queue>
#include <vector>

namespace {
    constexpr int dirs[4][2] = {{0, -1}, {0, 1},{ -1 , 0}, { 1, 0} };

    std::vector<int> distanceMap(const Map& map, Point target) {
        const int w = map.width();
        std::vector<int> dist(w * map.height(), -1);

        std::queue<Point> frontier;
        dist[target.y * w + target.x] = 0;
        frontier.push(target);
        while (!frontier.empty()) {
            Point p = frontier.front();
            frontier.pop();

            for (const auto& d : dirs) {
                int nx = p.x + d[0];
                int ny = p.y + d[1];
                if (!map.isWalkable(nx, ny)) {
                    continue;
                }
                if (dist[ny * w + nx] != -1) {
                    continue;
                }
                dist[ny * w + nx] = dist[p.y * w + p.x] + 1;
                frontier.push({nx,ny});
            }
        }
        return  dist;

    }
}

void monstersTakeTurn(World &world) {
    Point playerPos{world.player().x , world.player().y};
    std::vector<int> dist = distanceMap(world.map, playerPos);
    const int w = world.map.width();

    for (std::size_t i = 1 ; i < world.entities.size(); ++i) {
        Entity& m = world.entities[i];

        if (!world.fov.isVisible(m.x,m.y)) {
            continue;
        }
        int bestDist = dist[m.y * w + m.x];
        int bestDx = 0;
        int bestDy = 0;
        for (const auto& d : dirs) {
            int nx = m.x + d[0];
            int ny = m.y + d[1];
            if (world.isBlocked(nx , ny)) {
                continue;
            }
            int nd = dist[ny * w + nx];
            if (nd != -1 && nd < bestDist) {
                bestDist = nd;
                bestDx = d[0];
                bestDy = d[1];
            }
        }
        if (bestDx != 0 || bestDy != 0) {
            world.tryMove(m,bestDx,bestDy);
        }

    }
}
