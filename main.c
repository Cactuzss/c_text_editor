#include <ncurses.h>
#include "include/graphics.h"
#include "include/strings.h"
#include "include/files.h"

int normalControls(const char c);
int insertControls(const char c);

// context_t context; 
text_t* text;

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("required path to file\n");
        return 1;
    }

    string_t* str = files_read(argv[1]);
    text = strings_strToText(str);
    strings_freeString(str);

    graphics_init();

    while(true)
    {
        graphics_displayText(*text);
        if (context.state == NORMALMODE)
            normalControls(getch());
    }

    graphics_close();
    strings_freeText(text);

}

int normalControls(const char c)
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
                if (context.cursorX >= text->data[context.cursorY - 1]->strlen)
                {
                    context.cursorX = text->data[context.cursorY - 1]->strlen == 0 ? 0 : text->data[context.cursorY - 1]->strlen - 1;
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
                if (context.cursorY + 1 < text->size)
                {
                    if (context.cursorX >= text->data[context.cursorY + 1]->strlen)
                    {
                        context.cursorX = text->data[context.cursorY + 1]->strlen == 0 ? 0 : text->data[context.cursorY + 1]->strlen - 1;
                        context.startX = 0;
                    }
                    ++(context.cursorY); 
                }
            }
            else
            {
                ++context.startY;
            }
            break;

        case 'l': 
            if (context.cursorY + context.startY >= text->size)
                break;

            if (context.cursorX < context.cols - 1 && context.cursorX + 1 <= text->data[context.cursorY + context.startY]->strlen) 
                ++(context.cursorX);
            else if (context.cursorX == context.cols - 1) 
            {
                ++context.startX;
                --context.cursorX;
            }
            break;  

        case 'i':
            context.state = INSERTMODE;
            break;
    }
    return 0;  
}

int insertControls(const char c);
