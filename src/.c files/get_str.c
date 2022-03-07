#include "../Headers/get_str.h"
#include "../Headers/operations.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

const int LIMIT_SIZE = 1000;

char *get_string_from_input()
{
    char *input_str = (char*) calloc(LIMIT_SIZE, sizeof(char));
    fgets(input_str, LIMIT_SIZE, stdin);
    return input_str;
}

char *get_new_str()
{
    const char keys[] = "()+-*^/";
    char *input_str = get_string_from_input();
    char *new_str = (char*) calloc(LIMIT_SIZE, sizeof(char));
    int i = 0, j = 0;
    bool unar_minus;
    while (i < strlen(input_str))
    {
        unar_minus = false;
        new_str[j++] = input_str[i];
        if (input_str[i] == '-')
            if ((i == 0)
                || (strchr(keys, input_str[i-1]))
                || ((input_str[i-1] == ' ') && strchr(keys, input_str[i-2])))
                unar_minus = true;

        if (strchr(keys,input_str[i+1]) || strchr(keys,input_str[i]))
            if (!unar_minus)
                new_str[j++] = ' ';
        i++;
    }
    free(input_str);
    return new_str;
}

void pop_operation_to_string(char *oper, char *str, Stack *stack)
{
    strcat(str, oper);
    pop_from_stack(stack);
    strcat(str, " ");
}

void print_operations(stack_type oper, char *str, Stack *stack)
{
    switch ((int) oper)
    {
        case O_BRACKET:
        case C_BRACKET:
            pop_from_stack(stack);
            break;
        case SUM:
            pop_operation_to_string("+", str, stack);
            break;
        case SUBSTRACT:
            pop_operation_to_string("-", str, stack);
            break;
        case MULTIPLY:
            pop_operation_to_string("*", str, stack);
            break;
        case DIVISION:
            pop_operation_to_string("/", str, stack);
            break;
        case POWER:
            pop_operation_to_string("^", str, stack);
            break;
        case SIN:
            pop_operation_to_string("sin", str, stack);
            break;
        case COS:
            pop_operation_to_string("cos", str, stack);
            break;
        case LOG:
            pop_operation_to_string("log", str, stack);
            break;
        case SQRT:
            pop_operation_to_string("sqrt", str, stack);
            break;
        default:
            break;
    }
}

int priority(stack_type oper)
{
    switch ((int) oper)
    {
        case O_BRACKET:
        case C_BRACKET:
            return 5;
        case SUM:
        case SUBSTRACT:
            return 1;
        case MULTIPLY:
        case DIVISION:
        case SIN:
        case COS:
        case LOG:
        case SQRT:
            return 2;
        case POWER:
            return 3;
        default:
            return 0;
    }
}

char *get_RPN_from_str()
{
    char *expression = get_new_str();
    char *token = strtok(expression, " \n");

    Stack stake = make_stack();
    char *str_rpn = (char*) calloc(LIMIT_SIZE, sizeof(char));

    while (token != NULL)
    {
        if (check_string_is_digit(token))
        {
            strcat(str_rpn, token);
            strcat(str_rpn, " ");
        }
        else
        {
            OPERATIONS oper = get_operation_from_string(token);

            if (oper != C_BRACKET)
            {
                if (stake.length == 0)
                    push_to_stack(&stake, oper);
                else
                {
                    stack_type previous = *get_head(&stake);

                    if ((priority(previous) >= priority(oper)) && (previous != O_BRACKET))
                        print_operations(previous, str_rpn, &stake);
                    push_to_stack(&stake, oper);
                }
            }
            else
            {
                while (*get_head(&stake) != O_BRACKET && stake.length >= 0)
                    print_operations(*get_head(&stake), str_rpn, &stake);
                pop_from_stack(&stake);
            }
        }
        token = strtok(NULL, " \n");
    }

    while (stake.length != 0)
        print_operations(*get_head(&stake), str_rpn, &stake);

    free(expression);
    return str_rpn;
}