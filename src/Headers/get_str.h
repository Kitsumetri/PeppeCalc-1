#pragma once

typedef struct {
    char *var;
    char *def;
} VarDef;

char *get_string_from_input();
VarDef get_variable_from_input();
char *get_new_str(char *);
char *get_RPN_from_str(char *);