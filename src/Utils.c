//
// Created by Danuka De Alwis on 10/04/23.
//

#include "../inc/Utils.h"

uint8_t extract_bits(int value, int start_bit, int num_bits_to_extract){

    uint16_t bit_mask = ((1 << num_bits_to_extract) - 1) << start_bit;
    uint16_t extracted_bits = (value & bit_mask) >> start_bit;
    return extracted_bits;
}


bool isOddParity(uint8_t data) {
    int count = 0;
    for (int i = 0; i < 8; i++) {
        if (data & (1 << i)) {
            count++;
        }
    }
    return (count % 2 != 0);
}