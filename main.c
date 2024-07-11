#include <stdio.h>
#include "include/graphics.h"
#include "include/strings.h"
#include "include/files.h"

int main()
{
    string_t* str = files_read("../text");

    text_t* text = strings_strToText(str);

    graphics_init();
    graphics_displayText(*text);
    getchar();
    graphics_close();

    strings_freeString(str);
    strings_freeText(text);
}


