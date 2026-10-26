//
// Created by treta on 10/26/26.
//

#include "map.hpp"

Map::Map(int width, int height): width_(width), height_(height), tiles_(width * height, Tile::Wall){}

bool Map::inBounds(int x,int y) const {
    return x >= 0 && x <= width_ && y >= 0 && y < height_;
}

Tile Map::at(int x, int y) const {
    return tiles_[index(x,y)];
}

void Map::set(int x, int y, Tile tile) {
    if (inBounds(x,y)) {
        tiles_[index(x, y)] = tile;
    }
}

bool Map::isWalkable(int x, int y) const {
    return inBounds(x,y) && at(x,y) == Tile::Floor;
}
