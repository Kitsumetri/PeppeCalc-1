#pragma once

#include "stack.h"

char *get_string_from_input();
char *get_new_str();
char *get_RPN_from_str();

int priority_of_operation(int oper);