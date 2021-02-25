#include <stdio.h>
#include <disassembler.h>

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Invalid number of arguments\n");
    }
    else
    {
        uint16_t bin_size = 0, bytes_disassembled = 0, total_instructions = 0;
        uint8_t *bin = LoadBinary(argv[1], &bin_size);
        while(bytes_disassembled < bin_size)
        {
            bytes_disassembled += DisassembleInstr(bin, bytes_disassembled);
            ++total_instructions;
        }
        printf("Disassembled a total of %u bytes into %u instructions\n",
                bytes_disassembled, total_instructions);
    }
    return 0;
}

