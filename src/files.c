#include <stdio.h>

#include "../include/files.h"

string_t* files_read(const char* path)
{
    FILE* file = fopen(path, "r");
    if (file == NULL)
    {
        printf("Can not open the file\n");
        exit(-1);
    }

    size_t soiz = 0;

    while(fgetc(file) != EOF)
        soiz++;
   
    fclose(file);
    file = fopen(path, "r");
    if (file == NULL)
    {
        printf("Can not open the file\n");
        exit(-1);
    }

    string_t* res = malloc(sizeof(string_t));

    res->data = malloc(soiz * sizeof(char));
    if (res->data == NULL)
    {
        printf("Can not allocate memory for string\n");
        exit(0);
    }

    fread(res->data, sizeof(char), soiz, file);

    res->data[soiz - 1] = 0;
    res->size = soiz;

    fclose(file);
    return res;    
}


