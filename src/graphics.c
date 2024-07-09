#include "../include/graphics.h"
#include <ncurses.h>

struct context_t context;

void graphics_init(void)
{
    initscr();
    getmaxyx(stdscr, context.rows, context.cols);
}


void graphics_hello(void)
{
    move(context.rows / 2, context.cols / 2);
    printw("Hello from %d %d", context.rows / 2, context.cols / 2);
    refresh();
}


void graphics_close(void)
{
    endwin();
}
