#include "get_str.h"
#include "operations.h"
#include "stack.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

const int LIMIT_SIZE = 1000;

char *get_string_from_input() {
    char *input_str = (char*) calloc(LIMIT_SIZE, sizeof(char));
    fgets(input_str, LIMIT_SIZE, stdin);
    return input_str;
}

char *get_new_str() {
    const char keys[] = "()+-*^/";
    char *input_str = get_string_from_input();
    char *new_str = (char*) calloc(LIMIT_SIZE, sizeof(char));
    int i = 0; int j = 0;

    while (i < strlen(input_str))
    {
        new_str[j++] = input_str[i];
        if (strchr(keys,input_str[i+1]) || strchr(keys,input_str[i]))
            new_str[j++] = ' ';
        i++;
    }
    free(input_str);
    return new_str;
}

void print_operations(stack_type oper, char *str, Stack *stack)
{
    int a = (int)oper;
    switch (a)
    {
        case O_BRACKET:
        case C_BRACKET:
        {
            pop_from_stack(stack);
        }
            break;
        case SUM:
        {
            strcat(str, "+");
            pop_from_stack(stack);
            strcat(str, " ");
            break;
        }
        case SUBSTRACT:
        {
            strcat(str, "-");
            pop_from_stack(stack);
            strcat(str, " ");
            break;
        }
        case MULTIPLY:
        {
            strcat(str, "*");
            pop_from_stack(stack);
            strcat(str, " ");
            break;
        }
        case DIVISION:
        {
            strcat(str, "/");
            pop_from_stack(stack);
            strcat(str, " ");
            break;
        }
        case POWER:
        {
            strcat(str, "^");
            pop_from_stack(stack);
            strcat(str, " ");
            break;
        }
        case SIN:
        {
            strcat(str, "sin");
            pop_from_stack(stack);
            strcat(str, " ");
            break;
        }
        case COS:
        {
            strcat(str, "cos");
            pop_from_stack(stack);
            strcat(str, " ");
            break;
        }
        case LOG:
        {
            strcat(str, "log");
            pop_from_stack(stack);
            strcat(str, " ");
            break;
        }
        case SQRT:
        {
            strcat(str, "sqrt");
            pop_from_stack(stack);
            strcat(str, " ");
            break;
        }
        default:
            break;
    }
}

int priority(int oper)
{
    if (oper == O_BRACKET || oper == C_BRACKET)
        return 4;
    if (oper == SUM || oper == SUBSTRACT)
        return 1;
    if (oper == MULTIPLY || oper == DIVISION || oper == SIN || oper == COS || oper == LOG || oper == SQRT)
        return 2;
    if (oper == POWER)
        return 3;
    return 0;
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
                if (stake.length== 0)
                    push_to_stack(&stake, oper);
                else
                {
                    int previous = (int) *get_head(&stake);

                    if (priority(previous) >= priority((int)oper))
                    {
                        print_operations(previous, str_rpn, &stake);
                        push_to_stack(&stake, (int)oper);
                    }
                    else
                        push_to_stack(&stake, (int)oper);
                }
            }
            else
            {
                while (get_head(&stake) != O_BRACKET && stake.length >= 0)
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