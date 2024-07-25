#ifndef CHARLIST_H
#define CHARLIST_H

#include <stdlib.h>
#include <memory.h>
#include <stdint.h>
#include <stdio.h>

#define CHAR_ALIGNMENT 7            // 7 bytes of data we losing to structure alignment

typedef struct charNode
{
    struct charNode* next;
    char size;
    char data[CHAR_ALIGNMENT];

} charNode_t;

typedef struct
{
   charNode_t* head;
   size_t size;
   size_t strlen;
} charList_t;

charList_t* charlist_construct(charNode_t*);
charNode_t* charnode_construct(const char*);

void charlist_free(charList_t*);

void charnode_print(charNode_t*);

char* charlist_at(charList_t*, size_t);
void charlist_push_front(charList_t*, char);
void charlist_push_back(charList_t*, char);
void charlist_insert(charList_t*, size_t, char);
void charlist_remove(charList_t*, size_t);

#undef CHAR_ALIGNMENT
#endif
