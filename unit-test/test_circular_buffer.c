#include "unity/unity.h"
#include "../inc/CircularBuffer.h"
#include "time.h"

static cbuf_handle_t buffer_handle;
static INPUT_DATA_TYPE *uart_read_addr;
void setUp(void)
{
    uart_read_addr = malloc(1);
    // uint8_t *uart_read_addr = UART_READ_ADDR;
    // reg write
    // needs to read on interrupt

    printf("Value = %d\n",*uart_read_addr);
    circ_buf_data_type * buffer  = malloc(EXAMPLE_BUFFER_SIZE * sizeof(uint8_t));
    buffer_handle = circular_buf_init(buffer,
                                                    EXAMPLE_BUFFER_SIZE);
    circular_buf_init(buffer,EXAMPLE_BUFFER_SIZE);

}

void tearDown(void)
{
}

void test_buf_put_get(){

    *uart_read_addr = 231;
    circular_buf_put(buffer_handle,*uart_read_addr);
    circ_buf_data_type data;
    circular_buf_get(buffer_handle,&data);
    TEST_ASSERT_EQUAL(231, data);

    *uart_read_addr = 199;
    circular_buf_put(buffer_handle,*uart_read_addr);
    circular_buf_get(buffer_handle,&data);
    TEST_ASSERT_EQUAL(199,data);

    circular_buf_reset(buffer_handle);
}

void test_buf_capacity_and_full(){
    *uart_read_addr = 163;
    TEST_ASSERT_EQUAL(EXAMPLE_BUFFER_SIZE,circular_buf_capacity(buffer_handle));
    int counter = 0;
    while (counter <= EXAMPLE_BUFFER_SIZE) {
        circular_buf_put(buffer_handle, *uart_read_addr);
        counter++;
    }
    TEST_ASSERT_EQUAL(true, circular_buf_full(buffer_handle));

    circ_buf_data_type data;
    circular_buf_get(buffer_handle,&data);
    TEST_ASSERT_EQUAL(163, data);
    TEST_ASSERT_EQUAL(false, circular_buf_full(buffer_handle));

    circular_buf_reset(buffer_handle);
}

void test_buf_put_speed(){

    *uart_read_addr = 163;

    int counter = 0;
    double time_spent = 0.0;
    clock_t begin = clock();

    while (counter < 115200/(sizeof(INPUT_DATA_TYPE)*8)){
        circular_buf_put(buffer_handle, *uart_read_addr);
        counter++;
    }
    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    TEST_ASSERT_LESS_OR_EQUAL(1, time_spent);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_buf_put_get);
    RUN_TEST(test_buf_capacity_and_full);
    RUN_TEST(test_buf_put_speed);
    return UNITY_END();
}