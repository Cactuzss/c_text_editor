#include <ncurses.h>
#include "include/graphics.h"
#include "include/strings.h"
#include "include/files.h"
#include "include/charList.h"

int normalControls(const char c);

// context_t context; 
text_t* text;
#define arraySize(arr) (sizeof(arr) / sizeof(arr[0]))
int main()
{
    charList_t* lst = charlist_construct(charnode_construct("brown fox the"));

    char toFront[] = "A quick ";
    for (int i = arraySize(toFront) - 1; i >= 0; i--)
        charlist_push_front(lst, toFront[i]);

    char toBack[] = " lazy dog";
    for (size_t i = 0; i < arraySize(toBack) - 1; i++)
        charlist_push_back(lst, toBack[i]);

    char toInsert[] = "jumps over ";
    size_t start = arraySize(toFront) + arraySize(toBack);
    for(size_t i = 0; i < arraySize(toInsert); i++)
        charlist_insert(lst, start + i, toInsert[i]);

    for(size_t i = 0; i < 6; i++)           // 6 = "quick ".size()
        charlist_remove(lst, 2);            // 2 if position of quick

    printf("size = %zu;  strlen = %zu\t\n", lst->size, lst->strlen);

    charNode_t* it = lst->head;
    for(size_t i = 0; i < lst->size; i++)
    {
        printf("Block №%zu; size = %d\t", i, it->size);    
        for (size_t j = 0; j < it->size; j++) printf("%c", it->data[j]);
        printf("\n");
        it = it->next;
    }   

    printf("\n");
    for(size_t i = 0; i < lst->strlen; i++)
    {
        char* c = charlist_at(lst, i);
        printf("%c", *c);
    }

    charlist_free(lst);
}
#undef arraySize

int m2in(int argc, char* argv[])
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
                if (context.cursorY + 1 < text->size)
                {
                    if (context.cursorX >= text->data[context.cursorY + 1]->size)
                    {
                        context.cursorX = text->data[context.cursorY + 1]->size == 0 ? 0 : text->data[context.cursorY + 1]->size - 1;
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

            if (context.cursorX < context.cols - 1 && context.cursorX + 1 <= text->data[context.cursorY + context.startY]->size) 
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
