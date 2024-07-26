#include "../include/graphics.h"
#include <ncurses.h>

#define LOWERLINE 5

#define NORMALBG 0
#define WHITEBG 1

context_t context;

void graphics_init(void)
{
    initscr();
    start_color();
    getmaxyx(stdscr, context.rows, context.cols);
    
    context.startX = 0;
    context.startY = 0;

    context.lowerLineOffset = LOWERLINE;
    context.rows -= context.lowerLineOffset;

    context.state = NORMALMODE;

    init_pair(NORMALBG, COLOR_WHITE, COLOR_BLACK);
    init_pair(WHITEBG, COLOR_BLACK, COLOR_WHITE);
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

void graphics_drawMenu(void)
{
    move(context.rows, 0); 

    attron(COLOR_PAIR(WHITEBG));
    for(size_t i = 0; i < context.cols; i++)
        printw(" ");
    attroff(COLOR_PAIR(WHITEBG));

    move(context.rows + 2, 1);
    switch (context.state) 
    {
        case NORMALMODE:
            printw("Normal mode");
            break;

        case INSERTMODE:
            printw("Insert mode");
            break;
    }
    move(context.rows + 2, context.cols - 9);  // 9 = "controls".size() + 1
    printw("controls");

    move(context.rows + 3, context.cols - 9);
    printw("h j k l ");

    move(context.rows + 2, context.cols - 9 - 22); // 22 = "esc - normal mode".size() + 1 + offset (4)
    printw("esc - normal mode");

    move(context.rows + 3, context.cols - 9 - 22); 
    printw("i   - insert mode");

}

void graphics_displayText(text_t text)
{
    move(0, 0);

    for(size_t i = context.startY, line = 0; i < text.size && line < context.rows; i++, line++)
    {
        move(line, 0);
        //for(size_t j = context.startX; j < context.cols + context.startX && j < text.data[i]->size; j++)
        //    printw("%c", text.data[i]->data[j]);

        charNode_t* it = text.data[i]->head;
        size_t past = 0;

        size_t ind = context.startX;
        for (size_t i = 0; i <= ind && i < text.data[i]->strlen; i++ )
        {
            if (i + it->size - 1 < ind)
            {
                --i;
                i += it->size;
                past += it->size;
                it = it->next;
                continue;
            }
        }
        ind -= past;

        for (size_t j = 0, pos = ind; j < context.cols && j < text.data[i]->strlen; j++)
        {
            if (pos == it->size)
            {
                pos = 0;
                it = it->next;
            }

            printw("%c", it->data[pos]);
            pos++;
            continue;
        }

        printw("\n");
    }
        
    if (text.size < context.rows + context.startY)
        for (size_t i = text.size; i < context.rows + context.startY; i++)
            printw("~ \n");

    graphics_drawMenu();

    move(context.cursorY, context.cursorX);
    refresh();
}

void graphics_close(void)
{
    endwin();
}

#undef LOWERLINE
#undef WHITEBG
#undef NORMALBG
