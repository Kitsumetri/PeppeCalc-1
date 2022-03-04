#pragma once

#include <stdbool.h>
#include "stack.h"

typedef enum {
    O_BRACKET,
    C_BRACKET,
    SUM,
    SUBSTRACT,
    MULTIPLY,
    DIVISION,
    POWER,
    SIN,
    COS,
    LOG,
    SQRT,
    ERROR
} OPERATIONS;

OPERATIONS get_operation_from_string(char *str);
long double calculate_result_with_rpn(char *str);

bool check_string_is_digit(char *str);