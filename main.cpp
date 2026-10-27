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

void drawMap(const Map& map) {
    for (int y = 0; y < map.height(); ++y) {
        for (int x = 0 ; x < map.width(); ++x) {
            mvaddch(y,x,map.at(x, y) == Tile::Wall ? '#' : '.');
        }
    }
}
int main() {
    Terminal terminal;

    Map map(80,24);
    // for (int y = 5; y < 15; ++y) {
    //     for (int x = 10 ; x< 40; ++x) {
    //         map.set(x,y, Tile::Floor);
    //     }
    // }
    map.fillRect(10,5,30,10,Tile::Floor);

    map.set(20, 8, Tile::Wall);

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