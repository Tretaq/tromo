#pragma once
#include "map.hpp"
#include "rect.hpp"

class Fov
{
public:
    Fov(int width, int height);
`
    bool isVisible(int x, int y) const;
    bool isExplored(int x, int y) const;
private:
    bool inBounds(int x, int y) const;
    int index(int x, int y) const {return y * width_ + x;};
    int width_, height_;
    std::vector<char> visible_;
    std::vector<char> explored_;



};


