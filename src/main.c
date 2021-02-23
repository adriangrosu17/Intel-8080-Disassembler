#include <stdio.h>
#include <disassembler.h>

int main(int argc, char *argv[])
{
    (void)(argc); (void)(argv);
    if(argc != 2)
    {
        printf("Invalid number of arguments\n");
    }
    else
    {
        uint8_t instr_cycles = 0;
        uint16_t bin_size = 0, bytes_disassembled = 0, total_instructions = 0;
        uint32_t total_cycles = 0;
        uint8_t *bin = LoadBinary(argv[1], &bin_size);
        while(bytes_disassembled < bin_size)
        {
            bytes_disassembled += DisassembleInstr(bin, bytes_disassembled, &instr_cycles);
            total_cycles += instr_cycles;
            ++total_instructions;
        }
        printf("Disassembled a total of %u bytes into %u instructions which take a total of %u cycles to execute\n",
                bytes_disassembled, total_instructions, total_cycles);
    }
    return 0;
}

