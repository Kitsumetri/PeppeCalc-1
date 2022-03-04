#include "get_str.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

const int LIMIT_SIZE = 1000;

char *get_string_from_input() {
    char *input_str = (char*) calloc(LIMIT_SIZE, sizeof(char));
    fgets(input_str, LIMIT_SIZE, stdin);
    return input_str;
}


char *get_new_str() {
    const char keys[] = "()+-*^/";
    char *input_str = get_string_from_input();
    char *new_str = (char*) calloc(LIMIT_SIZE, sizeof(char));
    int i = 0; int j = 0;

    while (i < strlen(input_str))
    {
        new_str[j++] = input_str[i];
        if (strchr(keys,input_str[i+1]) || strchr(keys,input_str[i]))
            new_str[j++] = ' ';
        i++;
    }
    free(input_str);
    return new_str;
}