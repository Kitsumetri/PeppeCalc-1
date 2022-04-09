#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <math.h>
#include "operations.h"
#include "constants_of_functions.h"

#define eq(str, op) (strcmp(str, op) == 0)

#ifdef STACK_TYPE_IS_LONG_DOUBLE
#define strtost(op, ptr) strtod(op, ptr)
#define sin(x) sinl(x)
#define cos(x) cosl(x)
#define log(x) logl(x)
#define pow(x, y) powl(x, y)
#define sqrt(x) sqrtl(x)
#elif STACK_TYPE_IS_INT
#define strtost(op, str) strtol(op, ptr)
#endif

stack_type comp_log(stack_type x);

#ifdef STACK_TYPE_IS_COMPLEX
#define strtost(op, ptr) strtod(op, ptr)
#define pow(x, y) cpowl(x, y)
#define sqrt(x) csqrtl(x)
#define log(x) comp_log(x)
#define exp(x) cexpl(x)
#define sin(x) (exp(I*x) - exp(-I*x)) / (2*I) //casinl(x)
#define cos(x) (exp(I*x) + exp(-I*x)) / 2 //cacosl(x)
#endif

stack_type mag(stack_type x)
{
    return sqrt(pow(creal(x), 2) + pow(cimag(x), 2));
}

stack_type phase(stack_type x)
{
    return atan2(creal(x), cimag(x));
}

stack_type comp_log(stack_type x)
{
    return logl(mag(x)) + I*phase(x);
}

OPERATIONS get_operation_from_string(char *str)
{
    for (int i = 0; i < ERROR; ++i)
        if eq(str, funcs[i])
            return i;
    return ERROR;
}

stack_type get_constant(OPERATIONS oper)
{
    switch (oper)
    {
        case COMPLEX:
            return I;
        case PI:
            return M_PI;
        case E:
            return M_E;
        default:
            return 0;
    }
}

stack_type apply_operation1(OPERATIONS oper, stack_type v)
{
    switch (oper)
    {
        case SIN:
            return sin(v);
        case COS:
            return cos(v);
        case LOG:
            return (fabsl(cimag(v)) < 1e-7) ? logl(creal(v)) : log(v);
        case SQRT:
            return sqrt(v);
        case MAG:
        case ABS:
            return mag(v);
        case PHASE:
            return phase(v);
        case IMAG:
            return cimag(v);
        case REAL:
            return creal(v);
        case EXP:
            return exp(v);
        default:
            return 0;
    }
}

stack_type apply_operation2(OPERATIONS oper, stack_type v1, stack_type v2)
{
    switch (oper)
    {
        case SUM:
            return v1+v2;
        case SUBSTRACT:
            return v1-v2;
        case MULTIPLY:
            return v1*v2;
        case DIVISION:
            return v1/v2;
        case POWER:
            return pow(v1,v2);
        default:
            return 0;
    }
}

bool check_string_is_digit(char *str)
{
    if ((str[0] == '-') && (strlen(str) == 1))
        return false;
    for (int i = 0; i < strlen(str); ++i)
        if (!isdigit(str[i]) && (str[i] != '.') && (str[0] != '-'))
            return false;
    return true;
}

void do_operation(Stack *stake, OPERATIONS oper)
{
    stack_type value_1, value_2;
    switch (oper)
    {
        case SUM:
        case SUBSTRACT:
        case MULTIPLY:
        case DIVISION:
        case POWER:
            value_2 = *get_head(stake);
            pop_from_stack(stake);
            value_1 = *get_head(stake);
            pop_from_stack(stake);
            push_to_stack(stake, apply_operation2(oper, value_1, value_2));
            break;
        case SIN:
        case COS:
        case LOG:
        case SQRT:
        case PHASE:
        case ABS:
        case MAG:
        case IMAG:
        case REAL:
        case EXP:
            value_1 = *get_head(stake);
            pop_from_stack(stake);
            push_to_stack(stake, apply_operation1(oper, value_1));
            break;
        case COMPLEX:
        case PI:
        case E:
            push_to_stack(stake, get_constant(oper));
            break;
        default:
            printf("ERROR: INCORRECT OPERATION %s\n", funcs[(int) creal(oper)]);
            break;
    }
}

Queue *get_queue_from_rpn(const char *orig_str)
{
    char *str = (char*) calloc(strlen(orig_str), sizeof(char));
    strncpy(str, orig_str, strlen(orig_str));

    Queue *queue = create_queue();
    char *end_ptr = NULL;
    char *token = strtok(str, " ,\n");
    while ((token != NULL) && (strchr(orig_str, token[0])))
    {
        if (check_string_is_digit(token))
        {
            Elem *elem = create_elem(token,
                                     (stack_type) strtost(token, &end_ptr),
                                     NUMBER);
            add_to_queue(queue, elem);
        }
        else if (is_variable(token))
        {
            Elem *elem;
            extern Queue *var_queue;

            if (var_is_exists(token))
                elem = find_variable_in_queue(var_queue, token);
            else
            {
                elem = create_elem(token,
                                   0,
                                   VARIABLE);
                add_to_queue(var_queue, elem);
            }
            add_to_queue(queue, elem);
        }
        else
        {
            Elem *elem = create_elem(token,
                                     get_operation_from_string(token),
                                     OPERATION);
            add_to_queue(queue, elem);
        }
        token = strtok(NULL, " ,\n");
    }
    free(str);
    return queue;
}

stack_type calculate_result_from_queue(Queue **queue)
{
    Stack stake = make_stack();
    for (int i = 0; i < (*queue)->size; ++i)
    {
        Elem *elem = (*queue)->elems[i];
        switch (elem->type)
        {
            case NUMBER:
                push_to_stack(&stake, elem->value);
                break;
            case OPERATION:
                do_operation(&stake, elem->value);
                break;
            default:
                printf("Something went wrong!\n");
        }
    }
    delete_queue(queue);
    return *get_head(&stake);
}