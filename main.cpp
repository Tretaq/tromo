#include <ncurses.h>

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
        erase();
        mvaddch(y, x, '@');
        refresh();

        int key = getch();

        switch (key) {
            case 'q': running = false; break;
            case KEY_UP: --y; break;
            case KEY_DOWN: ++y; break;
            case KEY_LEFT: --x; break;
            case KEY_RIGHT: ++x; break;
            default: break;
        }
    }
    return 0;

}