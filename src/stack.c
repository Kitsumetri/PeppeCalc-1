#include "stack.h"
#include <stdlib.h>

Stack make_stack() {
    Stack new_stack;
    new_stack.length = 0;
    new_stack.elems = (stack_type *)calloc(0, sizeof(stack_type));
    return new_stack;
}

void push_to_stack(Stack *stake, stack_type new_value) {
    stake->length += 1;
    stack_type *temp = (stack_type *)malloc(stake->length * sizeof(stack_type));
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
    stake->elems = (stack_type *) realloc(stake->elems, stake->length * sizeof(stack_type));
}

const stack_type * get_head(Stack *stake) {
    return ((stake->length == 0) ? NULL : &stake->elems[stake->length - 1]);
}