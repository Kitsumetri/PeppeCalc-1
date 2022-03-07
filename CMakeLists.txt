cmake_minimum_required(VERSION 3.21)
project(Calc C)

set(CMAKE_C_STANDARD 17)
add_compile_options(-Wall -lm)

add_executable(Calc "src/.c files/main.c" "src/.c files/stack.c" src/Headers/stack.h "src/.c files/operations.c" src/Headers/operations.h "src/.c files/get_str.c" src/Headers/get_str.h)

target_link_libraries(Calc m)