#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <ncurses.h>
#include "../include/strings.h"

#define NORMALMODE 0
#define INSERTMODE 1

typedef struct
{
    size_t cols;
    size_t rows;

    size_t cursorX;
    size_t cursorY;

    size_t startX;
    size_t startY;

    size_t lowerLineOffset; 

    char state;

} context_t;

extern context_t context;

context_t* graphics_getContext(void);

void graphics_init(void);
void graphics_hello(void);
void graphics_close(void);
void graphics_drawMenu(void);
void graphics_displayText(text_t text);

#endif


