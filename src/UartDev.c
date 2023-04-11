/*
 * UartDev.h
 *
 *  Created on:
 *      Author:
 * 
 * Last Modified:
 */
#include "../inc/UartDev.h"

UART_DEV_TYPE *pUartDev[2];

UART_DEV_TYPE* UartDev_New() {
    UART_DEV_TYPE * uart_instance = malloc(sizeof(UART_DEV_TYPE));
    memset(uart_instance,0,sizeof(*uart_instance));
    *pUartDev = uart_instance;
    return uart_instance;
}
void UartDev_Construct(UART_DEV_TYPE *obj, UART_FLAG flag) {

    //Create Receive or Transmit FIFO Buffer
    circ_buf_data_type *buffer = malloc(EXAMPLE_BUFFER_SIZE * sizeof(uint8_t));
    obj->_circular_buffer_handle = circular_buf_init(buffer,
                                                     EXAMPLE_BUFFER_SIZE);
    obj->_flag = flag;
    obj->processingSecondByte = false;
    obj->packet = 0;
}

bool UartDev_Open(UART_DEV_TYPE *obj, int baud, char parity, int bits, int stopbits){
    if(obj == NULL)return false;
    obj->opened = true;
    obj->baud_rate = baud;
    obj->parity = parity;
    obj->bits = bits;
    obj->stopbits = stopbits;
    if(obj->_flag == UART_FLAG_RX_NOT_READY) obj -> _flag = UART_FLAG_RX_READY;
    if(obj->_flag == UART_FLAG_TX_NOT_READY) obj -> _flag = UART_FLAG_TX_READY;
    return true;
}
bool UartDev_Close(UART_DEV_TYPE *obj){
    if(obj == NULL)return false;
//    obj->opened = false;
    if(obj->_flag == UART_FLAG_RX_READY) obj -> _flag = UART_FLAG_RX_NOT_READY;
    if(obj->_flag == UART_FLAG_TX_READY) obj -> _flag = UART_FLAG_TX_NOT_READY;
    return true;
}
void UartDev_Destroy(UART_DEV_TYPE *obj){
    free(obj);
}
#ifdef  UNIT_TESTING
int _UartDev_IRQHandler(UART_DEV_TYPE *p){
#else
static  void * _UartDev_IRQHandler(UART_DEV_TYPE *p){
#endif
    if (p == NULL)return (0);
    int start_bit = 16 - 1 - p->bits - 1 - p->stopbits;
    if (p->_flag == UART_FLAG_RX_READY)
    {
        if (!p->processingSecondByte){

            if(extract_bits(p->DR,7,1)) // Check for start bit to go low.
            {
                p->packet = p->DR << 8;
                p->processingSecondByte = true;
            }

        }else{
            p->packet = p->packet | (uint16_t) p->DR;
            BYTE frame = extract_bits(p->packet, start_bit + 1 + p->stopbits, 8);
            if (isOddParity(frame) != p->parity) { // Ensure odd parity if parity bit is set
                if (extract_bits(p->packet, start_bit, p->stopbits) == 0b11) { // Checks if stop bits 11
                    circular_buf_put(p->_circular_buffer_handle, frame);
                }
            }
            p->packet = 0;
            p->processingSecondByte = false;
        }
    }
    if (p->_flag == UART_FLAG_TX_READY)
    {
        BYTE data = 0;
        circular_buf_get(p->_circular_buffer_handle, &data);
        BYTE parity_bit = isOddParity(&data) != p->parity;
        BYTE stop_bits = 0b11;
        p->data_frame = 1 | data | parity_bit | stop_bits;
    }
    p->DR = 0;
}

// This routine has to be a timed blocking call until
// either data received (return true) or 1000ms time(return false).
// This is used for the external source to read what the uart has gathered in either one of its buffers
bool UartDev_Get(UART_DEV_TYPE *obj,  BYTE *ch)
{
    if (obj == NULL)return (false);
    if (!obj->opened) return false;
    circular_buf_get(obj->_circular_buffer_handle, ch);
    return(true);
}

// This is for the serial interface to place a BYTE in its buffer.
// returns number of bytes sent to tx buf.
int UartDev_Put(UART_DEV_TYPE *obj, BYTE data)
{
    if (obj == NULL)return (false);
    if (!obj->opened) return false;
    circular_buf_put(obj->_circular_buffer_handle, data);
    return (int)circular_buf_size(obj->_circular_buffer_handle);
}


