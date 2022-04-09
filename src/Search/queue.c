#include <stdlib.h>
#include <string.h>
#include "get_str.h"
#include "operations.h"
#include "queue.h"

Elem *create_elem(char *name, stack_type value, TypeOfElem type) {
    Elem *elem = malloc(sizeof(Elem));
    elem->name = malloc(sizeof(name));
    strcpy(elem->name, name);
    elem->value = value;
    elem->type = type;
    return elem;
}

Queue *create_queue() {
    Queue *queue = malloc(sizeof(Queue));
    queue->size = 0;
    queue->elems = malloc(0);
    return queue;
}

void *add_to_queue(Queue *queue, Elem *elem) {
    int new_size = queue->size + 1;
    Elem **elems = (Elem**) calloc(new_size, sizeof(Elem*));
    for (int i = 0; i < queue->size; ++i)
        elems[i] = queue->elems[i];
    elems[new_size-1] = elem;
    free(queue->elems);
    queue->elems = elems;
    queue->size = new_size;
}

void delete_queue(Queue **queue) {
    if (!queue)
        return;
    free((*queue)->elems);
    free(*queue);
    *queue = NULL;
}

void pop_from_queue(Queue *queue, Elem *elem) {
    if (elem == NULL)
        return;
    int i;
    int new_size = queue->size - 1;
    for (i = 0; i < queue->size; ++i)
        if (queue->elems[i] == elem)
            break;
    Elem **elems = (Elem**) calloc(new_size, sizeof(Elem*));
    for (int j = 0; j < queue->size; ++j)
        if (i != j)
            elems[(j < i) ? j : j - 1] = queue->elems[j];
    free(queue->elems);
    queue->elems = elems;
    queue->size = new_size;
}

Elem* find_variable_in_queue(Queue *queue, char *name) {
    for (int i = 0; i < queue->size; ++i)
        if (strcmp(queue->elems[i]->name, name) == 0)
            return queue->elems[i];
    return NULL;
}

void apply_variable(Elem *elem, stack_type value) {
    elem->type = NUMBER;
    elem->value = value;
}

bool var_is_exists(char *name) {
    extern Queue *var_queue;
    for (int i = 0; i < var_queue->size; ++i)
    {
        Elem *elem = var_queue->elems[i];
        if (strcmp(elem->name, name) == 0)
            return true;
    }
    return false;
}

bool queue_has_uninitialized_variables(Queue *queue) {
    for (int i = 0; i < queue->size; ++i)
        if (queue->elems[i]->type == VARIABLE)
            return true;
    return false;
}