cmake_minimum_required(VERSION 3.9)
project(maturita C)

set(CMAKE_C_STANDARD 11)

add_executable(maturita main.c sjl.c functions.h mat.c anj.c)