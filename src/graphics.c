#include "../include/graphics.h"
#include <ncurses.h>

context_t context;

void graphics_init(void)
{
    initscr();
    getmaxyx(stdscr, context.rows, context.cols);
}


void graphics_hello(void)
{
    move(context.rows / 2, context.cols / 2);
    printw("Hello from %zu %zu", context.rows / 2, context.cols / 2);
    refresh();
}

void graphics_displayText(text_t text)
{
    move(0, 0);
    context.cursorY = 0;
    context.cursorX = 0;

    for(size_t i = 0; i < text.size && i < context.rows; i++)
    {
        move(i, 0);
        printw("%s\n", text.data[i]->data);
    }

    move(0, 0);
    refresh();
}

void graphics_close(void)
{
    endwin();
}
