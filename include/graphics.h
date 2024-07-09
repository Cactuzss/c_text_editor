#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <ncurses.h>


struct context_t
{
    int cols;
    int rows;
};

void graphics_init(void);
void graphics_hello(void);
void graphics_close(void);

#endif


