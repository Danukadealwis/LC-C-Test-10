#include "StandardInc.h"
#include "UartDev.h"


uint8_t extract_bits(int input_value,  int start_bit, int num_bits_to_extract);
bool isOddParity(uint8_t data);