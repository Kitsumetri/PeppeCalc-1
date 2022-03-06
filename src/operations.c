#include "operations.h"
#include "stack.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <math.h>

#define eq(str, op) (strcmp(str, op) == 0)

#ifdef STACK_TYPE_IS_LONG_DOUBLE
    #define strtost(op, ptr) strtod(op, ptr)
    #define sin(x) sinl(x)
    #define cos(x) cosl(x)
    #define log(x) logl(x)
    #define sqrt(x) sqrtl(x)
#elif STACK_TYPE_IS_INT
    #define strtost(op, str) strtol(op, ptr)
#endif

OPERATIONS get_operation_from_string(char *str) {
    if eq(str, "+")
        return SUM;
    if eq(str, "-")
        return SUBSTRACT;
    if eq(str, "*")
        return MULTIPLY;
    if eq(str, "/")
        return DIVISION;
    if eq(str, "^")
        return POWER;
    if eq(str, "(")
        return O_BRACKET;
    if eq(str, ")")
        return C_BRACKET;
    if eq(str, "sin")
        return SIN;
    if eq(str, "cos")
        return COS;
    if eq(str, "log")
        return LOG;
    if eq(str, "sqrt")
        return SQRT;
    return ERROR;
}

stack_type apply_operation1(OPERATIONS oper, stack_type v) {
    switch (oper) {
        case SIN:
            return sin(v);
        case COS:
            return cos(v);
        case LOG:
            return log(v);
        case SQRT:
            return sqrt(v);
        default:
            return 0;
    }
}

stack_type apply_operation2(OPERATIONS oper, stack_type v1, stack_type v2) {
    stack_type t_v;
    switch (oper) {
        case SUM:
            return v1+v2;
        case SUBSTRACT:
            return v1-v2;
        case MULTIPLY:
            return v1*v2;
        case DIVISION:
            return v1/v2;
        case POWER:
            t_v = 1;
            for (int i = 0; i < v2; i++)
                t_v *= v1;
            return t_v;
        default:
            return 0;
    }
}

bool check_string_is_digit(char *str) {
    if ((str[0] == '-') && (strlen(str) == 1))
        return false;
    for (int i = 0; i < strlen(str); ++i)
        if (!isdigit(str[i]) && (str[i] != '.') && (str[0] != '-'))
            return false;
    return true;
}

void do_operation(char *token, Stack *stake) {
    stack_type value_1, value_2;
    OPERATIONS oper = get_operation_from_string(token);
    switch (oper) {
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
            value_1 = *get_head(stake);
            pop_from_stack(stake);
            push_to_stack(stake, apply_operation1(oper, value_1));
            break;
        default:
            printf("ERROR: INCORRECT OPERATION\n");
            break;
    }
}

stack_type calculate_result_with_rpn(char *str) {
    Stack stake = make_stack();
    char *end_ptr = NULL;
    char *token = strtok(str, " ,\n");
    while (token != NULL) {
        if (check_string_is_digit(token))
            push_to_stack(&stake, (stack_type) strtost(token, &end_ptr));
        else
            do_operation(token, &stake);
        token = strtok(NULL, " ,\n");
    }
    return *get_head(&stake);
}
