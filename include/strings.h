#ifndef STRINGS_H
#define STRINGS_H

#include <stdlib.h>
#include "../include/charList.h"

typedef struct 
{
    char* data;
    size_t size;
} string_t;

typedef struct 
{
    charList_t** data;
    size_t size;
} text_t;

string_t* strings_construct(const char*);
string_t* strings_recountSize(string_t* str);

text_t* strings_strToText(string_t* str);

void strings_freeString(string_t* str);
void strings_freeText(text_t* text);

#endif
