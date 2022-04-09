#pragma once

#include "stack.h"

typedef enum
{
    NUMBER,
    OPERATION,
    VARIABLE,
} TypeOfElem;

typedef struct {
    char *name;
    stack_type value;
    TypeOfElem type;
} Elem;

typedef struct {
    Elem **elems;
    int size;
} Queue;

Elem *create_elem(char *name, stack_type value, TypeOfElem type);
Queue *create_queue();
void *add_to_queue(Queue *queue, Elem *elem);
Elem* find_variable_in_queue(Queue *queue, char *name);
void apply_variable(Elem *elem, stack_type value);
void delete_queue(Queue **queue);
bool queue_has_uninitialized_variables(Queue *queue);
bool var_is_exists(char *name);