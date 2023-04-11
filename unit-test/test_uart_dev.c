#include "unity/unity.h"
#include "../inc/UartDev.h"
#include "../inc/Utils.h"
void setUp(void)
{

}

void tearDown(void)
{

}

void test_extract_bits(){
    uint8_t bits = extract_bits(45,3,3);
    TEST_ASSERT_EQUAL(5,bits);
    bits = extract_bits(128,7,1);
    TEST_ASSERT_EQUAL(1,bits);
    bits = extract_bits(127,7,1);
    TEST_ASSERT_EQUAL(0,bits);
    bits = extract_bits(0xFFEF,0,8);
    TEST_ASSERT_EQUAL(0XEF,bits);
    bits = extract_bits(0b1011110111110000,7,8);
    TEST_ASSERT_EQUAL(123,bits);

}
void test_odd_parity(){
    TEST_ASSERT_EQUAL(0,isOddParity(0b11110000));
    TEST_ASSERT_EQUAL(0,isOddParity(0b01111011));
}

void test_irq_handler(){
    UART_DEV_TYPE * uart = UartDev_New();
    UartDev_Construct(uart, UART_FLAG_RX_NOT_READY);
    UartDev_Open(uart,115200,UART_ODD_PARITY,UART_DATA_BITS_SIZE,UART_STOP_BITS);
    uart->DR = 0b10111101;
    _UartDev_IRQHandler(uart);
    uart->DR = 0b11110000;
    _UartDev_IRQHandler(uart);
    uint8_t data = 0x00;
    UartDev_Get(uart,&data);
    TEST_ASSERT_EQUAL(0b01111011, data);
}
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_extract_bits);
    RUN_TEST(test_odd_parity);
    RUN_TEST(test_irq_handler);
    return UNITY_END();
}