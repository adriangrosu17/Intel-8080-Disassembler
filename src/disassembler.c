#include <disassembler.h>
#include <stdio.h>
#include <stdlib.h>

uint8_t *LoadBinary(const char *binary_name, uint16_t *size)
{
    uint8_t *bin = NULL;
    if((NULL == binary_name) || (NULL == size))
    {
        printf("NULL argument received\n");
        return NULL;
    }
    else
    {
        FILE *file = fopen(binary_name, "rb");
        if(NULL == file)
        {
            printf("Error opening file %s\n", bin);
            *size = 0;
        }
        else
        {
            if(0 == fseek(file, 0L, SEEK_END))
            {
                size_t binary_size = ftell(file);
                rewind(file);
                bin = (uint8_t *)malloc(binary_size);
                if(NULL != bin)
                {
                    *size = fread(bin, sizeof(uint8_t), binary_size, file);
                    printf("Loaded binary %s with size %u bytes\n", binary_name, *size);
                }
                else
                {
                    *size = 0;
                }
            }
            else
            {
                printf("Error seeking to EOF\n");
                *size = 0;
            }
            if(0 != fclose(file))
            {
                printf("Error closing file %s\n", bin);
            }
        }
    }
    return bin;
}

uint8_t DisassembleInstr(uint8_t *bin, uint16_t offset, uint8_t *clk_cycles)
{
    uint8_t instr_size = 1;
    if((NULL == bin) || (NULL == clk_cycles))
    {
        printf("NULL argument received\n");
    }
    else
    {
        printf("0x%04X\t0x%X\t", offset, bin[offset]);
        switch(bin[offset])
        {
            case 0x00: printf("NOP\n"); *clk_cycles = 4; break;
            default: printf("UNKNOWN\n"); *clk_cycles = 0; break;
        }
    }
    return instr_size;
}

