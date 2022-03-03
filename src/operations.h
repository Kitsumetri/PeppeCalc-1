#pragma once

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
    ERROR
} OPERATIONS;

OPERATIONS get_operation_from_string(char *str);
long double calculate_result_with_rpn(char *str);