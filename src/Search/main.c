#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "get_str.h"
#include "operations.h"

//#define PRINT_RPN

Queue *var_queue;

char *GetStringFromExpression(const char *strsrc)
{
    char *str = malloc(strlen(strsrc) * sizeof(char));
    strcpy(str, strsrc);
    char *rpn_string = get_RPN_from_str(get_new_str(str));
#ifdef PRINT_RPN
    printf("RPN Expression: %s\n", rpn_string);
#endif
    return rpn_string;
}

void wait_while_variables_will_empty(Queue *queue)
{
    while (queue_has_uninitialized_variables(queue))
    {
        printf("Print variable for expression:\n");
        const VarDef vardef = get_variable_from_input();

        char *rpn_string = GetStringFromExpression(vardef.def);
        Queue *var_q = get_queue_from_rpn(rpn_string);
        free(rpn_string);

        wait_while_variables_will_empty(var_q);

        Elem *var = find_variable_in_queue(var_queue, vardef.var);
        apply_variable(var, calculate_result_from_queue(&var_q));
    }
}

int main()
{
    // Initialize Global Queue of Variables
    var_queue = create_queue();

    printf("Print expression:\n");
    char *rpn_string = GetStringFromExpression(get_string_from_input());
    Queue *general_queue = get_queue_from_rpn(rpn_string);
    free(rpn_string);

    wait_while_variables_will_empty(general_queue);
    stack_type answer = calculate_result_from_queue(&general_queue);

    // Rounding values
    if (fabsl(cimag(answer)) < 10e-10)
        answer = creal(answer);
    if (fabsl(creal(answer)) < 10e-10)
        answer = cimag(answer)*I;

    // Printing
    if (cimag(answer))
    {
        if (cimag(answer) == -1)
            printf("Answer: %2.4g + -i\n", creal(answer));
        else
            printf("Answer: %2.4g + %2.4gi\n", creal(answer), cimag(answer));
    }
    else
        printf("Answer: %2.4g\n", creal(answer));
    return 0;
}