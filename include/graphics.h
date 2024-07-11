#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <ncurses.h>
#include "../include/strings.h"

typedef struct
{
    size_t cols;
    size_t rows;

    size_t cursorX;
    size_t cursorY;
} context_t;

void graphics_init(void);
void graphics_hello(void);
void graphics_close(void);
void graphics_displayText(text_t text);

#endif


