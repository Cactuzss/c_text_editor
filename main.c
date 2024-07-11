#include <ncurses.h>
#include "include/graphics.h"
#include "include/strings.h"
#include "include/files.h"

int controls(const char c);

text_t* text;

int main()
{
    string_t* str = files_read("../text");
    text = strings_strToText(str);
    strings_freeString(str);

    graphics_init();

    while(true)
    {
        graphics_displayText(*text);
        controls(getch());
    }

    graphics_close();
    strings_freeText(text);

}


int controls(const char c)
{
    switch (c) 
    {
        case 'h': 
            if (context.cursorX != 0) 
                --(context.cursorX); 
            else if (context.startX != 0)
                --(context.startX);

            break;

        case 'k': 
            if (context.cursorY != 0) 
            {
                if (context.cursorX >= text->data[context.cursorY - 1]->size)
                {
                    context.cursorX = text->data[context.cursorY - 1]->size == 0 ? 0 : text->data[context.cursorY - 1]->size - 1;
                    context.startX = 0;
                }
                --(context.cursorY); 
            }
            else if (context.startY > 0)
            {
                --context.startY;
            }
            break;

        case 'j': 
            if (context.cursorY < context.rows - 2 && context.cursorY < text->size) 
            {
                if (context.cursorX >= text->data[context.cursorY + 1]->size)
                {
                    context.cursorX = text->data[context.cursorY + 1]->size == 0 ? 0 : text->data[context.cursorY + 1]->size - 1;
                    context.startX = 0;
                }
                ++(context.cursorY); 
            }
            else
            {
                ++context.startY;
            }
            break;

        case 'l': 
            if (context.cursorX < context.cols - 1 && context.cursorX + 1 <= text->data[context.cursorY]->size) 
                ++(context.cursorX);
            else if (context.cursorX == context.cols - 1) 
            {
                ++context.startX;
                --context.cursorX;
            }
            break;  
    }
    return 0;  
}
