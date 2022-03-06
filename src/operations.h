#pragma once

#include <stdbool.h>
#include "stack.h"

typedef enum {
    O_BRACKET, //0
    C_BRACKET, //1
    SUM, //2
    SUBSTRACT, //3
    MULTIPLY, //4
    DIVISION, //5
    POWER, //6
    SIN, //7
    COS, //8
    LOG, //9
    SQRT, //10
    ERROR
} OPERATIONS;

OPERATIONS get_operation_from_string(char *str);
stack_type calculate_result_with_rpn(const char *orig_str);

bool check_string_is_digit(char *str);