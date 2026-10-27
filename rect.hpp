#pragma once

struct Point {
    int x;
    int y;
};

struct Rect {
    int x, y, w, h;

    Point center() const {
        return {x + w / 2, y + h / 2};
    }

    bool intersects(const Rect& other) const {
        return x <= other.x + other.w && x + w >= other.x &&
            y <= other.y + other.h && y + h >= other.y;
    }
};