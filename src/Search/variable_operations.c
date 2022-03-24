#include <stdlib.h>
#include <string.h>
#include "get_str.h"
#include "operations.h"
#include "variable_operations.h"

VarQueue *var_queue;

Var *create_var(char *name, stack_type *ptr)
{
    Var *var = malloc(sizeof(Var));
    var->name = name;
    var->ptr = ptr;
    return var;
}

VarQueue *create_queue()
{
    VarQueue *queue = malloc(sizeof(VarQueue));
    queue->size = 0;
    queue->vars = malloc(0);
    queue->not_initialized = 0;
    return queue;
}

void *add_to_queue(VarQueue **queue, Var elem)
{
    if (elem.ptr == NULL)
        (*queue)->not_initialized += 1;
    int new_size = (*queue)->size + 1;
    Var *vars = (Var*) calloc(new_size, sizeof(Var));
    for (int i = 0; i < (*queue)->size; ++i)
        vars[i] = (*queue)->vars[i];
    vars[new_size-1] = elem;
    free((*queue)->vars);
    (*queue)->vars = vars;
}

void pop_from_queue(VarQueue **queue, Var *elem)
{
    if (elem == NULL)
        return;
    int i;
    for (i = 0; i < (*queue)->size; ++i)
        if (&(*queue)->vars[i] == elem)
            break;
    VarQueue *new_queue = create_queue();
    for (int j = 0; j < (*queue)->size; ++j)
        if (i != j)
            add_to_queue(&new_queue, (*queue)->vars[j]);
    free((*queue)->vars);
    free((*queue));
    (*queue) = new_queue;
}

Var* find_elem_in_queue(VarQueue *queue, char *name)
{
    for (int i = 0; i < queue->size; ++i)
        if (strcmp(queue->vars[i].name, name) == 0)
            return &queue->vars[i];
    return NULL;
}

void apply_var(Var *var, char *str)
{
    char *rpn_string = get_RPN_from_str(str);
    stack_type answer = calculate_result_with_rpn(rpn_string);
    free(rpn_string);
    *(var->ptr) = answer;
}
