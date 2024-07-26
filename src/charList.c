#include "../include/charList.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define OUT_OF_MEMORY(ptr, str) if (ptr == NULL) { printf(str); exit(-1); };
#define CHAR_ALIGNMENT 7    // 7 bytes of data we losing to structure alignment 

charNode_t* charnode_construct(const char* str)
{
    charNode_t* head = malloc(sizeof(charNode_t));
    OUT_OF_MEMORY(head, "Malloc returned NULL at charnode_construct");

    charNode_t* it = head;

    size_t soiz = 0;
    while(str[soiz]) soiz++;

    const int32_t blockSoiz = sizeof(int32_t);
    size_t fullBlocks = (soiz - 1) / blockSoiz;

    size_t pos = 0;
    for (size_t i = 0; pos + 4 < soiz && i < fullBlocks; pos+=blockSoiz)
    {
        (*((int32_t*)(it->data))) = (*((int32_t*)(str + pos)));
        it->size = blockSoiz;
        it->next = malloc(sizeof(charNode_t));
        OUT_OF_MEMORY(it->next, "Malloc returned NULL at charnode_construct");
        it = it->next;
    }

    it->size = 1;

    for(; pos <= soiz; pos++)
    {
        if (it->size == 4)
        {
            it->next = malloc(sizeof(charNode_t));
            OUT_OF_MEMORY(it->next, "Malloc returned NULL at charnode_construct");
            it = it->next;
            it->size = 1;
            it->next = NULL;
        }

        it->data[it->size - 1] = str[pos];
        if (str[pos] == 0)
            break;
        (it->size)++;
    }

    it->next = NULL;
    return head;
}

charList_t* charlist_construct(charNode_t* cn)
{
    charList_t* res = malloc(sizeof(charList_t));
    memset(res, 0, sizeof(charList_t));
    OUT_OF_MEMORY(res, "Malloc returned NULL at charlist_construct");

    res->head = cn;

    charNode_t* it = cn;
    while(it != NULL) 
    {
        res->strlen += it->size;
        it = it->next;
        res->size++;
    }

    return res;
}

void charlist_free(charList_t* cl)
{
    charNode_t* it = cl->head;
    for(size_t i = 0; it != NULL; i++)
    {
        charNode_t* prev = it;
        it = it->next;
        free(prev);
    }

    free(cl);
    cl = NULL;
}

void charnode_print(charNode_t* cn)
{
    charNode_t* it = cn;
    while(it != NULL)
    {
        for (size_t i = 0; i < it->size; i++)
            printf("%c", it->data[i]);
        it = it->next;
    }
    printf("\n");
}

char* charlist_at(charList_t* cl, size_t ind)
{
    charNode_t* it = cl->head;
    size_t past = 0;

    for (size_t i = 0; i <= ind && i < cl->strlen; i++ )
    {
        if (i + it->size - 1< ind)
        {
            --i;
            i += it->size;
            past += it->size;
            it = it->next;
            continue;
        }

    }
    return it->data + ind - past;
}

void charlist_push_front(charList_t* cl, char c)
{
    if (cl->head->size < CHAR_ALIGNMENT)
    {
        for(int i = cl->head->size - 1; i >= 0; i--)
            cl->head->data[i + 1] = cl->head->data[i];
        cl->head->data[0] = c;
        cl->head->size++;
        cl->strlen++;
        return;
    }

    charNode_t* newHead = malloc(sizeof(charNode_t));
    OUT_OF_MEMORY(newHead, "Malloc returned NULL in charlist_push_front");
    memset(newHead, 0, sizeof(charNode_t));

    newHead->next = cl->head;
    newHead->size = 1;
    newHead->data[0] = c;

    cl->strlen++;
    cl->size++;

    cl->head = newHead;
}

void charlist_push_back(charList_t* cl, char c)
{
    charNode_t* it = cl->head;
    while (it->next != NULL) it = it->next;

    if(it->size != CHAR_ALIGNMENT)
    {
        it->data[it->size] = c;
        it->size++;
        cl->strlen++;
        return;
    }

    it->next = malloc(sizeof(charNode_t));
    memset(it->next, 0, sizeof(charNode_t));

    it->next->data[0] = c;
    it->next->size = 1;
    cl->size++;
    cl->strlen++;
}

void charlist_insert(charList_t* cl, size_t ind, char c)
{
    charNode_t* it = cl->head;
    size_t past = 0;

    for (size_t i = 0; i <= ind && i < cl->strlen; i++ )
    {
        if (i + it->size - 1 < ind)
        {
            --i;
            i += it->size;
            past += it->size;
            it = it->next;

            continue;
        }
    }

    ind -= past;
    
    if (it->size >= CHAR_ALIGNMENT)
    {
        charNode_t* newNode = malloc(sizeof(charNode_t));
        memset(newNode, 0, sizeof(charNode_t));

        size_t offset = CHAR_ALIGNMENT - sizeof(int32_t);

        newNode->next = it->next;
        it->next = newNode;

        (*((int32_t*)(newNode->data))) = (*((int32_t*)(it->data + offset)));
        newNode->size = sizeof(int32_t);

        cl->size++;

        *((int32_t*)(it->data + offset)) = 0;
        it->size = offset; 
        
        if (ind > offset)
        {
            it = it->next;
            ind -= offset;
        }
    }

    for(int i = it->size - 1; i >= 0 && i >= ind; i--)
        it->data[i + 1] = it->data[i];

    it->data[ind] = c;
    it->size++;

    cl->strlen++;
};

void charlist_remove(charList_t* cl, size_t ind)
{
    charNode_t* it = cl->head;
    size_t past = 0;

    for (size_t i = 0; i <= ind && i < cl->strlen; i++ )
    {
        if (i + it->size - 1 < ind)
        {
            --i;
            i += it->size;
            past += it->size;
            it = it->next;

            continue;
        }
    }

    ind -= past;

    if (ind == it->size - 1)
    {
        it->data[it->size] = 0;
        it->size--;
        cl->strlen--;
        return;
    }       

    for(size_t i = ind; i < it->size - 1; i++)
        it->data[i] = it->data[i + 1];

    it->size--;
    cl->strlen--;

}

#undef CHAR_ALIGNMENT
#undef OUT_OF_MEMORY
