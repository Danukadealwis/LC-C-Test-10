#include "unity/unity.h"
#include "../inc/CircularBuffer.h"
#define EXAMPLE_BUFFER_SIZE 32

static cbuf_handle_t buffer_handle;
static uint8_t *uart_read_addr;
void setUp(void)
{
    uart_read_addr = malloc(1);
//    uint8_t *uart_read_addr = UART_READ_ADDR;
    //reg write
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
//    assert(output == -1);
    printf("Value = %d\n", data);
    TEST_ASSERT_EQUAL(231, data);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_buf_put_get);
    return UNITY_END();
}