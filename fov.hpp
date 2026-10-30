#pragma once
#include "map.hpp"
#include "rect.hpp"

class Fov
{
public:
    Fov(int width, int height);

    Fov compute(const Map& map, Point origin, int radius);

    bool isVisible(int x, int y) const;
    bool isExplored(int x, int y) const;

private:
    bool inBounds(int x, int y) const;
    int index(int x, int y) const {return y * width_ + x;};

    int width_;
    int height_;
    std::vector<char> visible_;
    std::vector<char> explored_;
};


