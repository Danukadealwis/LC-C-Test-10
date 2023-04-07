
#include "inc/StandardInc.h"
#include "inc/Interrupt.h"
#include "inc/CircularBuffer.h"
#define UART_READ_ADDR (uint32_t*)0x00FF
#define EXAMPLE_BUFFER_SIZE 32
int main() {
    uint8_t *uart_read_addr = malloc(1);
//    uint8_t *uart_read_addr = UART_READ_ADDR;
    //reg write
    // needs to read on interrupt
    *uart_read_addr = 231;
    printf("Value = %d\n",*uart_read_addr);
    circ_buf_data_type * buffer  = malloc(EXAMPLE_BUFFER_SIZE * sizeof(uint8_t));
    cbuf_handle_t buffer_handle = circular_buf_init(buffer,
                                         EXAMPLE_BUFFER_SIZE);
    circular_buf_init(buffer,EXAMPLE_BUFFER_SIZE);
    circular_buf_put(buffer_handle,*uart_read_addr);

    circ_buf_data_type data;
    circular_buf_get(buffer_handle,&data);
//    assert(output == -1);
    printf("Value = %d\n", data);




//    uint32_t *uart_read_addr = UART_READ_ADDR;
//    regWrite(*uart_read_addr, 231);
//    int32_t my_val = regRead(*uart_read_addr);
//

    return 0;
}
