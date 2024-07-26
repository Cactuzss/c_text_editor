#include "../include/strings.h"
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>

#define BUF_SIZE 1024

string_t* strings_recountSize(string_t* str)
{
    for(str->size = 0; str->data[str->size]; str->size++);
    return str;
}

string_t* strings_construct(const char* data)
{
    string_t* res = malloc(sizeof(string_t));
    size_t soiz = strlen(data);

    res->data = malloc(sizeof(char) * soiz + 1);
    if (res->data == NULL)
    {
        printf("Can not allocate memory for string\n");
        exit(-1);
    }

    //memcpy(res->data, data, soiz);
    strcpy(res->data, data);

    res->data[soiz] = 0;
    return strings_recountSize(res);
}


text_t* strings_strToText(string_t* str)
{
    text_t* text = malloc(sizeof(text_t));
    text->size = 1;

    for (size_t i = 0; i < str->size; i++)
        if (str->data[i] == '\n')
            ++text->size;

    text->data = malloc(sizeof(charList_t) * text->size);
    if (text->data == NULL) 
    {
        printf("Can not allocate memory for text_t text\n");
        exit(-1);
    }

    char buf[BUF_SIZE] = {0};

    size_t current = 0;
    for(size_t start = 0, end = 0; end <= str->size; ++end)
    {
        if (str->data[end] != '\n' && str->data[end] != 0)
            continue;

        memcpy(buf, str->data + start, end - start);

        buf[end - start] = 0;

        text->data[current] = charlist_construct(charnode_construct(buf));

        start = end + 1;
        ++current;
    }
 
    return text;
}


void strings_freeString(string_t* str)
{
    free(str->data);
    free(str);
}

void strings_freeText(text_t* text)
{
    for(size_t i = 0; i < text->size; i++)
        charlist_free(text->data[i]);
    free(text->data);
}

#undef BUF_SIZE
