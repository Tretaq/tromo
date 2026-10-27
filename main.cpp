#include <algorithm>
#include <ncurses.h>
#include <iostream>

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
    if (tile == Tile::Floor) {
        return '.';
    } else if (tile == Tile::Water) {
        return '~';
    } else {
        return '#';
    }
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

    Map map(80,24);
    map.fillRect(10,5,30,10,Tile::Floor);
    map.set(20, 8, Tile::Wall);
    map.fillRect(26,13,2,2,Tile::Water);
    int x = 12;
    int y = 7;
    bool running = true;

    while (running) {
        erase();
        drawMap(map);
        mvprintw(0,0, "x=%d y=%d", x, y);
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
            default: break;
        }
        if (map.isWalkable(x + dx, y + dy)) {
            x += dx;
            y += dy;
        }
    }
    return 0;

}