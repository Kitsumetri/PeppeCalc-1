#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_str.h"
#include "operations.h"
#include "constants_of_functions.h"
#include "queue.h"

//#define PRINT_SPACES

const int LIMIT_SIZE = 10000;

char *get_string_from_input()
{
    char *input_str = (char*) calloc(LIMIT_SIZE, sizeof(char));
    fgets(input_str, LIMIT_SIZE, stdin);
    return input_str;
}

VarDef get_variable_from_input()
{
    char *input = get_string_from_input();
    char *token = strtok(input, " =\n");
    VarDef vardef;
    vardef.var = (char*) calloc(strlen(token), sizeof(char));
    strcpy(vardef.var, token);
    token = strtok(NULL, "=\n");
    vardef.def = (char*) calloc(strlen(token), sizeof(char));
    strcpy(vardef.def, token);
    free(input);
    return vardef;
}

char *get_new_str(char *input_str)
{
    const char keys[] = "()+-*/^";
    char *new_str = (char*) calloc(LIMIT_SIZE, sizeof(char));
    int i = 0, j = 0;
    bool unar_minus;
    while (i < strlen(input_str))
    {
        unar_minus = false;
        if (input_str[i] != ',')
            new_str[j++] = input_str[i];
        if (input_str[i] == '-')
            if ((i == 0)
                || (strchr(keys, input_str[i-1]) && !strchr(")", input_str[i-1]))
                || ((input_str[i-1] == ' ') && strchr(keys, input_str[i-2])))
                unar_minus = true;

        if (strchr(keys,input_str[i+1]) || strchr(keys,input_str[i]))
            if (!unar_minus)
                new_str[j++] = ' ';
        i++;
    }
#ifdef PRINT_SPACES
    printf("%s\n", new_str);
#endif
    free(input_str);
    return new_str;
}

void pop_operation_to_string(const char *oper, char *str, Stack *stack)
{
    strcat(str, oper);
    pop_from_stack(stack);
    strcat(str, " ");
}

void print_operations(stack_type oper, char *str, Stack *stack)
{
    funcs[(int) creal(oper)];
    if (oper == O_BRACKET || oper == C_BRACKET)
        pop_from_stack(stack);
    else
        pop_operation_to_string(funcs[(int) creal(oper)], str, stack);
}

int get_priority(stack_type oper)
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
            return 2;
        case SIN:
        case COS:
        case LOG:
        case SQRT:
        case POWER:
        case MAG:
        case ABS:
        case PHASE:
        case EXP:
        case REAL:
        case IMAG:
            return 3;
        case COMPLEX:
        case E:
        case PI:
        case m_E:
        case m_COMPLEX:
        case m_PI:
            return 6;
        default:
            return 0;
    }
}

bool not_func(char *token)
{
    for (int i = 0; i < COMPLEX; ++i)
        if (strcmp(token, funcs[i]) == 0)
            return false;
    return true;
}

char *get_RPN_from_str(char *expression)
{
    char *token = strtok(expression, " \n");

    Stack stake = make_stack();
    char *str_rpn = (char*) calloc(LIMIT_SIZE, sizeof(char));

    while (token != NULL)
    {
        if (check_string_is_digit(token)
            || not_func(token))
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

                    if ((get_priority(previous) >= get_priority(oper)) && (previous != O_BRACKET))
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