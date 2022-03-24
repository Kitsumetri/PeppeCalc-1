#pragma once

#include "stack.h"

typedef struct {
   char *name;
   stack_type *ptr;
} Var;

typedef struct {
    Var *vars;
    int size;
    int not_initialized;
} VarQueue;

Var *create_var(char *name, stack_type *ptr);
VarQueue *create_queue();
void *add_to_queue(VarQueue **queue, Var elem);
void pop_from_queue(VarQueue **queue, Var *elem);
Var* find_elem_in_queue(VarQueue *queue, char *name);