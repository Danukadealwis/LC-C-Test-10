#include "../inc/Interrupt.h"

void regWrite(uint32_t addr, int32_t data){
    uint32_t *regAddr = &addr;
    *regAddr = data;
}

int32_t regRead(uint32_t addr){
    uint32_t *regAddr = &addr;
    return regAddr;
}