#include <stdbool.h>
#include "operations.h"
#include "constants_of_functions.h"

const char* funcs[] = {
        "(",
        ")",
        "+",
        "-",
        "*",
        "/",
        "^",
        "sin",
        "cos",
        "log",
        "sqrt",
        "mag",
        "phase",
        "abs",
        "imag",
        "real",
        "exp",
        "j",
        "PI",
        "e",
        "-e",
        "-PI",
        "\0"
};

bool is_variable(char *token)
{
    for (int i = 0; i < ERROR; ++i)
        if (strcmp(token, funcs[i]) == 0)
            return false;
    return true;
}