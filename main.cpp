#include <algorithm>
#include <ncurses.h>
#include <iostream>
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

int main() {
    Terminal terminal;


    int x = 10;
    int y = 5;
    bool running = true;

    while (running) {
        int rows, cols;
        getmaxyx(stdscr, rows, cols);
        erase();
        mvprintw(0,0, "x=%d y=%d", x, y);
        mvaddch(y, x, '@');
        refresh();

        int key = getch();

        switch (key) {
            case 'q': running = false; break;
            case KEY_UP: case 'w': case 'h': --y; break;
            case KEY_DOWN: case 's': case 'j': ++y; break;
            case KEY_LEFT: case 'a': case 'k': --x; break;
            case KEY_RIGHT: case 'd': case 'l': ++x; break;
            default: break;
        }
        x = std::clamp(x, 0, cols -1);
        y = std::clamp(y, 0, rows -1);
    }
    return 0;

}