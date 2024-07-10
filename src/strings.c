#include "../include/strings.h"
#include <memory.h>
#include <stdlib.h>

#define BUF_SIZE 128

string_t strings_recountSize(string_t str)
{
    for(str.size = 0; str.data[str.size]; str.size++);
    return str;
}

string_t strings_construct(const char* data)
{
    string_t res;
    size_t soiz = strlen(data);

    res.data = malloc(sizeof(char) * soiz);
    memcpy(res.data, data, soiz);

    return strings_recountSize(res);
}


text_t strings_strToText(string_t str)
{
    text_t text;
    text.size = 1;

    for (size_t i = 0; i < str.size; i++)
        if (str.data[i] == '\n')
            ++text.size;

    text.data = malloc(sizeof(string_t) * text.size);
    char* buf = malloc(sizeof(char) * BUF_SIZE);

    size_t current = 0;
    for(size_t start = 0, end = 0; end <= str.size; ++end)
    {
        if (str.data[end] != '\n' && str.data[end] != 0)
            continue;

        memcpy(buf, str.data + start, end - start);
        buf[end - start] = 0;

        text.data[current] = strings_construct(buf);

        start = end + 1;
        ++current;
    }
 
    return text;
}
