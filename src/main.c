#include <stdio.h>
#include "get_str.h"
#include "operations.h"

int main()
{
    char *rpn_string = get_RPN_from_str();
    printf("RPN Expression: %s\n", rpn_string);
    long double answer = calculate_result_with_rpn(rpn_string);
    printf("Answer: %2.4Lf", answer);
    return 0;
}
