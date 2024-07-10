#include <stdio.h>

#include "../include/files.h"

string_t files_read(const char* path)
{
    FILE* file = fopen(path, "r");
    size_t soiz = 0;

    while(fgetc(file) != EOF)
        soiz++;
   
    fclose(file);
    file = fopen(path, "r");

    string_t res;

    if (file == NULL)
    {
        res.data = NULL;
        res.size = 0;

        return res;
    }

    res.data = malloc(soiz * sizeof(char));
    fread(res.data, sizeof(char), soiz, file);

    res.data[soiz - 1] = 0;
    res.size = soiz;

    fclose(file);
    return res;    
}


