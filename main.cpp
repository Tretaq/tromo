#include <algorithm>
#include <ncurses.h>
#include <iostream>
#include <random>
#include "dungeon.hpp"
#include "map.hpp"
#include "world.hpp"
#include "ai.hpp"
#include "colors.hpp"
class Terminal {
    public:
    Terminal() {
        initscr();
        start_color();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);
        curs_set(0);
        init_pair(1,COLOR_RED,COLOR_BLACK);
        init_pair(2,COLOR_GREEN,COLOR_BLACK);
        init_pair(3,COLOR_YELLOW,COLOR_BLACK);
        init_pair(4,COLOR_MAGENTA,COLOR_BLACK);
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
void drawHud(const World& world) {
    const Entity& p = world.player();
    const int row = world.map.height();
    int color = (p.hp * 3 <= p.maxHp) ? ColRed : ColGreen;
    attron(COLOR_PAIR(color));
    mvprintw(row,0,"HP %d/%d", std::max(p.hp,0),p.maxHp);
    attroff(COLOR_PAIR(color));
    const int total = static_cast<int>(world.log.size());
    const int shown = std::min(4, total);
    for (int i = 0; i < shown ; i++) {
        const Message& m = world.log[total - shown + i];
        const bool newest = (i == shown - 1);
        if (!newest) {
            attron(A_DIM);
        }
        attron(COLOR_PAIR(m.color));
        mvprintw(row + 1 + i, 0 , "%s",m.text.c_str());
        attroff(COLOR_PAIR(m.color));
        attroff(A_DIM);
    }
}

void drawMap(const Map& map, const Fov& fov) {
    for (int y = 0; y < map.height(); ++y) {
        for (int x = 0 ; x < map.width(); ++x) {
            if (fov.isVisible(x, y)) {
                mvaddch(y,x,tileIs(map.at(x,y)));
            } else if (fov.isExplored(x,y)) {
                attron(A_DIM);
                mvaddch(y,x,tileIs(map.at(x,y)));
                attroff(A_DIM);
            }
        }
    }
}

void newLevel(World& world, std::mt19937& rng) {
    world = World(80,24);
    Dungeon dungeon = generateDungeon(world.map,rng);
    world.entities.push_back({dungeon.start.x,dungeon.start.y,'@',"you",20,20 , ColMagenta,4, 0});
    spawnMonsters(world,dungeon.rooms,rng);
}
void drawEntities(const World& world) {

    for (const Entity&e : world.entities) {
        if (!world.fov.isVisible(e.x, e.y)) {
            continue;
        }
        attron(COLOR_PAIR(e.color));
            mvaddch(e.y,e.x,e.glyph);
        attroff(COLOR_PAIR(e.color));
    }
}
void drawFrame(const World& world, unsigned seed,int radius) {
    erase();
    drawMap(world.map, world.fov);
    drawEntities(world);
    drawHud(world);
    mvprintw(0,0, "x=%d y=%d seed=%u radius=%d", world.player().x, world.player().y, seed,radius);
    if (world.playerDead()) {
        const std::string b = " YOU DIED r: retry q: quit ";
        attron(A_REVERSE | A_BOLD);
        mvprintw(world.map.height() / 2,(world.map.width() - static_cast<int>(b.size())) / 2, "%s", b.c_str());
        attroff(A_REVERSE | A_BOLD);
    }
    refresh();
}
int main(int argc, char** argv) {

    std::random_device rnd;
    unsigned seed = rnd();
    if (argc > 1) {
        try {
            seed = std::stoul(argv[1]);
        }catch (const std::invalid_argument& e) {
            std::cerr << "Error: Given argument '" << argv[1] << "' is not a number! " <<  "\n";
        }

    }
    std::mt19937 rng(seed);
    World world(80,24);
    newLevel(world,rng);
    Terminal terminal;
    int radiusOfSight = 8;

    bool running = true;

    while (running) {

        world.updateFov(radiusOfSight);
        drawFrame()

        int key = getch();
        bool acted = false;;
        int dx = 0;
        int dy = 0;
        switch (key) {
            case 'q': running = false; break;
            case KEY_UP: case 'w': case 'k': dy = -1; break;
            case KEY_DOWN: case 's': case 'j': dy = 1; break;
            case KEY_LEFT: case 'a': case 'h': dx = -1; break;
            case KEY_RIGHT: case 'd': case 'l': dx = 1; break;
            case '=': radiusOfSight++; break;
            case '-': radiusOfSight--;  break;
            case 'r': seed = rnd(); rng.seed(seed);newLevel(world, rng); break;
            case 'm': world.ShowAll(); break;
            case '.': case ' ': acted = true; break;
            default: break;

        }
        radiusOfSight = std::clamp(radiusOfSight, 2, 16);
        if (dx != 0 || dy != 0) {
            acted = world.tryMove(world.player(),dx,dy);
        }
        if (acted) {
            world.updateFov(radiusOfSight);
            monstersTakeTurn(world, rng);
        }
    }
    return 0;

}