#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "get_str.h"
#include "operations.h"
#include "variable_operations.h"

int main()
{
    // Initialize Variables Queue
    extern VarQueue *var_queue;
    var_queue = create_queue();

    // Calculate General Expression
    char *rpn_string = get_RPN_from_str(get_new_str(get_string_from_input()));
    printf("RPN Expression: %s\n", rpn_string);
    stack_type answer = calculate_result_with_rpn(rpn_string);
    free(rpn_string);

    // Rounding values
    if (fabsl(cimag(answer)) < 10e-10)
        answer = creal(answer);
    if (fabsl(creal(answer)) < 10e-10)
        answer = cimag(answer)*I;

    // Printing
    if (cimag(answer))
        printf("Answer: %2.4g + %2.4gi\n", creal(answer), cimag(answer));
    else
        printf("Answer: %2.4g\n", creal(answer));
    return 0;
}