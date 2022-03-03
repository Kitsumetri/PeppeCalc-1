#include "stack.h"
#include <stdlib.h>

Stack make_stack() {
    Stack new_stack;
    new_stack.length = 0;
    new_stack.elems = (int*)calloc(0, sizeof(int));
    return new_stack;
}

void push_to_stack(Stack *stake, int new_value) {
    stake->length += 1;
    int *temp = (int*)malloc(stake->length * sizeof(int));
    for (int i = 0; i < stake->length - 1; i++)
        temp[i] = stake->elems[i];
    temp[stake->length - 1] = new_value;
    free(stake->elems);
    stake->elems = temp;
}

void pop_from_stack(Stack *stake) {
    if (stake->length == 0)
        return;
    stake->length -= 1;
    stake->elems = (int *) realloc(stake->elems, stake->length * sizeof(int));
}

int get_head(Stack *stake) {
    return ((stake->length == 0) ? -1 : stake->elems[stake->length - 1]);
}