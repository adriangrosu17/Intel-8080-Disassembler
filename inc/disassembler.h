#ifndef _INC_DISASSEMBLER_H_
#define _INC_DISASSEMBLER_H_

#include <stdint.h>

uint8_t *LoadBinary(const char *bin, uint16_t *size);
uint8_t DisassembleInstr(uint8_t *bin, uint16_t offset, uint8_t *clk_cycles);

#endif // _INC_DISASSEMBLER_H_

