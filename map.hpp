#pragma once
#include <vector>

enum class Tile { Wall, Floor, Water};

class Map {
public:
    Map(int width, int height);

    int width() const { return width_; }
    int height() const { return height_; }

    bool inBounds(int x, int y) const;
    Tile at(int x, int y) const;
    void set(int x, int y, Tile tile);
    bool isWalkable(int x, int y) const;
    void fillRect(int x, int y , int w , int h, Tile tile);
private:
    int index(int x, int y) const {return y * width_ + x;} // we use a long vector so the logic is x = wehere on x axis + y * width so which row

    int width_;
    int height_;
    std::vector<Tile> tiles_;
};