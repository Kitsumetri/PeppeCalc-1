#include <stdio.h>
#include <stdlib.h>
#include "operations.h"

const int LIMIT_SIZE = 1000;

char *get_string_from_input() {
    char *input_str = (char*) calloc(LIMIT_SIZE, sizeof(char));
    fgets(input_str, LIMIT_SIZE, stdin);
    return input_str;
}

int main() {
    char *input_str = get_string_from_input();
    printf("Output: %2.2Lf\n", calculate_result_with_rpn(input_str));
    return 0;
}
