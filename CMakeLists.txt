cmake_minimum_required(VERSION 3.23)
project(embedded_test C)

set(CMAKE_C_STANDARD 17)

add_executable(embedded_test main.c src/CircularBuffer.c)
