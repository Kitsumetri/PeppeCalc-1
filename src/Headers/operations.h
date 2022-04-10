#pragma once

#include <stdbool.h>
#include <string.h>
#include "stack.h"
#include "queue.h"

typedef enum
{
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
    MAG,
    PHASE,
    ABS,
    IMAG,
    REAL,
    EXP,
    // Constants
    COMPLEX,
    PI,
    E,
    m_E,
    m_PI,
    ERROR
}OPERATIONS;

OPERATIONS get_operation_from_string(char *str);
stack_type calculate_result_from_queue(Queue **queue);
Queue *get_queue_from_rpn(const char *orig_str);

bool check_string_is_digit(char *str);