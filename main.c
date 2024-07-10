#include <stdio.h>
#include "include/graphics.h"
#include "include/strings.h"
#include "include/files.h"

int main()
{
    string_t str = files_read("../text");

    text_t text = strings_strToText(str);
    printf("lines count = %zu\n", text.size);

    for (size_t i = 0; i < text.size; i++) 
    {
        printf("line %zu:\t %s \t soiz: %zu \n", i, text.data[i].data, text.data[i].size);
    }
}
