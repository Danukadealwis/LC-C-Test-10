cmake_minimum_required(VERSION 3.23)
project(embedded_test C)
set(CMAKE_C_STANDARD 17)
set(UNIT_TESTING)
add_library(Application inc/Application.h inc/Semaphore.h inc/Thread.h inc/UartDev.h inc/SerialInterface.h inc/Mutex.h src/Application.c src/Semaphore.c src/Thread.c src/UartDev.c src/SerialInterface.c src/Mutex.c)
add_executable(embedded_test main.c inc/StandardInc.h inc/CircularBuffer.h src/CircularBuffer.c src/Interrupt.c inc/Interrupt.h)


add_executable(test_circular_buffer unit-test/test_circular_buffer.c inc/CircularBuffer.h src/CircularBuffer.c unit-test/unity/unity.c unit-test/unity/unity.h unit-test/unity/unity_internals.h)
add_executable(test_uart_dev unit-test/test_uart_dev.c inc/CircularBuffer.h src/CircularBuffer.c inc/UartDev.h src/UartDev.c inc/Utils.h src/Utils.c unit-test/unity/unity.c unit-test/unity/unity.h unit-test/unity/unity_internals.h)
target_compile_definitions(test_uart_dev PUBLIC UNIT_TESTING=1;)