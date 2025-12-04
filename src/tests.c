#include "tests.h"

#include <stdio.h>
#include <stdlib.h>

void tests()
{
    chip8 testc8;
    uint16_t addr[5] = {0x2AA,0x000,0xFFF,0x001,0x012};

    // proof of concept
    int flag = 0;
    for(int i = 0; i<5; i++)
    {
        testc8.opcode = 0x1000 | addr[i];
        OP_1NNN(&testc8);

        if(testc8.PC != addr[i])
        {
            flag = 1;
        }
    }

    if(flag != 0)
    {
        printf("1NNN opcode does not work as expected\n");
    }

}

