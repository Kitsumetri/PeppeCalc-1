#pragma once

#define STACK_TYPE_IS_LONG_DOUBLE
//#define STACK_TYPE_IS_INT

typedef long double stack_type;
typedef struct {
    stack_type *elems;
    int length;
} Stack;

Stack make_stack();
void push_to_stack(Stack *stake, stack_type new_value);
void pop_from_stack(Stack *stake);
stack_type *get_head(Stack *stake);
