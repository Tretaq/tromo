#include <algorithm>
#include <ncurses.h>
#include <iostream>
#include <random>
#include "dungeon.hpp"
#include "map.hpp"

class Terminal {
    public:
    Terminal() {
        initscr();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);
        curs_set(0);
    }
    ~Terminal() {
        endwin(); // terminal is back to shell state
    }
    Terminal(const Terminal&) = delete;
    Terminal& operator=(const Terminal&) = delete;
 };

char tileIs(Tile tile) {
    switch (tile) {
        case Tile::Wall: return '#';
        case Tile::Water: return '~';
        case Tile::Floor: return '.';
    }
    return '?';
}
void drawMap(const Map& map) {
    for (int y = 0; y < map.height(); ++y) {
        for (int x = 0 ; x < map.width(); ++x) {
            mvaddch(y,x,tileIs(map.at(x, y)));
        }
    }
}
int main() {
    Terminal terminal;
    std::random_device rnd;
    unsigned seed = rnd();
    std::mt19937 rng(seed);
    Map map(80,24);
    Point start = generateDungeon(map, rng);
    int x = start.x;
    int y = start.y;
    bool running = true;

    while (running) {
        erase();
        drawMap(map);
        mvprintw(0,0, "x=%d y=%d seed=%d", x, y, seed);
        mvaddch(y, x, '@');
        refresh();


        int key = getch();

        int dx = 0;
        int dy = 0;
        switch (key) {
            case 'q': running = false; break;
            case KEY_UP: case 'w': case 'k': dy = -1; break;
            case KEY_DOWN: case 's': case 'j': dy = 1; break;
            case KEY_LEFT: case 'a': case 'h': dx = -1; break;
            case KEY_RIGHT: case 'd': case 'l': dx = 1; break;
            case 'r': map = Map(80,24); start = generateDungeon(map, rng); x = start.x; y = start.y;break;
            default: break;
        }
        if (map.isWalkable(x + dx, y + dy)) {
            x += dx;
            y += dy;
        }
    }
    return 0;

}