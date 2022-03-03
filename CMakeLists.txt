cmake_minimum_required(VERSION 3.21)
project(Calc C)

set(CMAKE_C_STANDARD 17)
add_compile_options(-Wall -lm)

add_executable(Calc src/main.c src/stack.c src/stack.h src/operations.c src/operations.h src/get_str.c src/get_str.h)

target_link_libraries(Calc m)