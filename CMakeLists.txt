cmake_minimum_required(VERSION 3.21)
project(Calc C)

set(CMAKE_C_STANDARD 17)
add_compile_options(-Wall -lm)

include_directories(src/Headers)

add_executable(Calc "src/Search/main.c" "src/Search/stack.c" src/Headers/stack.h "src/Search/operations.c" src/Headers/operations.h
        "src/Search/get_str.c" src/Headers/get_str.h "src/Search/constants_of_functions.c" src/Headers/constants_of_functions.h
        src/Search/queue.c src/Headers/queue.h)

target_link_libraries(Calc m)