cmake_minimum_required(VERSION 3.23)
project(embedded_test C)
set(CMAKE_C_STANDARD 17)


add_executable(embedded_test main.c inc/StandardInc.h inc/CircularBuffer.h src/CircularBuffer.c src/Interrupt.c inc/Interrupt.h)
add_executable(test_interrupt unit-test/test_interrupt.c inc/CircularBuffer.h src/CircularBuffer.c unit-test/unity/unity.c unit-test/unity/unity.h unit-test/unity/unity_internals.h)