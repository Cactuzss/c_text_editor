#ifndef STRINGS_H
#define STRINGS_H

#include <stdlib.h>

typedef struct 
{
    char* data;
    size_t size;
} string_t;

typedef struct 
{
    string_t* data;
    size_t size;
} text_t;

string_t strings_construct(const char*);
string_t strings_recountSize(string_t str);

text_t strings_strToText(string_t str);

#endif
