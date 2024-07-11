#include "../include/graphics.h"
#include <ncurses.h>

context_t context;

void graphics_init(void)
{
    initscr();
    getmaxyx(stdscr, context.rows, context.cols);
    
    context.startX = 0;
    context.startY = 0;
}

context_t* graphics_getContext(void)
{
    return &context;
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
    //context.cursorY = 0;
    //context.cursorX = 0;

    for(size_t i = context.startY, line = 0; i < text.size && line < context.rows; i++, line++)
    {
        move(line, 0);
        //printw("%s\n", text.data[i]->data);
        for(size_t j = context.startX; j < context.cols + context.startX && j < text.data[i]->size; j++)
            printw("%c", text.data[i]->data[j]);
        printw("\n");
    }
        
    if (text.size < context.rows + context.startY)
        for (size_t i = text.size; i < context.rows + context.startY; i++)
            printw("~ \n");

    move(context.cursorY, context.cursorX);
    refresh();
}

void graphics_close(void)
{
    endwin();
}
