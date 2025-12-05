#include "tests.h"

#include <stdio.h>
#include <stdlib.h>

void tests()
{
    chip8 testc8;
    int testflag = 0;


    testflag += test1NNN(&testc8);
    testflag += test2NNNand00EE(&testc8);

    //if any test failed
    if (testflag != 0)
    {
        exit(0);
    }
}

int test1NNN(chip8 * c8)
{
    uint16_t addr[5] = {0x2AA,0x000,0xFFF,0x001,0x012};

    // flags
    int flag = 0;
    int erri = 0;

    // for every value to be tested
    for(int i = 0; i<5; i++)
    {
        // set opcode to a value
        (*c8).opcode = 0x1000 | addr[i];
        
        // execute
        OP_1NNN(c8);

        // check if its the output is as expected
        if((*c8).PC != addr[i])
        {
            flag = 1;
            erri = i;
            break;
        }
    }

    // if the test failed
    if(flag != 0)
    {
        printf("1NNN does not work as expected!\n");
        printf("Value 0x%x set PC to: 0x%x \n", addr[erri], (*c8).PC);
        return 1;
    }
    // if the test passed
    else
    {
        printf("1NNN works as expected.\n");
    }

    return 0;
}

int test2NNNand00EE(chip8 * c8)
{
    uint16_t addr[5] = {0x2AA,0x000,0xFFF,0x001,0x012};
    uint16_t pc[5] = {0x3EE,0x000,0xFFF,0x004,0x013};

    // flags
    int flag = 0;
    int erri = 0;
    int func = 1;
  
    for(int i = 0; i<5; i++)
    {
        // set opcode to a value
        (*c8).opcode = 0x0000 | addr[i];
        
        int orginalsc = (*c8).SC;
        (*c8).PC = pc[i];

        // execute
        OP_2NNN(c8);

        // check if its the output is as expected
        if((*c8).SC != orginalsc+1 && (*c8).PC != addr[i])
        {
            flag = 1;
            erri = i;
            break;
        }

        // execute seccond command
        func = 2;
        OP_00EE(c8);

        //todo
        if((*c8).SC != orginalsc && (*c8).PC != pc[i])
        {
            flag = 1;
            erri = 1;
            break;
        }
    }

    // if the test failed
    if(flag != 0)
    {
        if(func == 1)
        {
            printf("2NNN does not work as expected!\n");
            printf("Value 0x%x set PC to: 0x%x \n", addr[erri], (*c8).PC);
        }
        if(func == 2)
        {
            printf("00EE does not work as expected!\n");
            printf("Value got from the stack 0x%x set PC to: 0x%x \n", pc[erri], (*c8).PC);
        }
        return 1;
    }
    // if the test passed
    else
    {
        printf("2NNN and 00EE work as expected.\n");
    }
    return 0;
}


