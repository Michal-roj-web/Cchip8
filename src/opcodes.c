#include "opcodes.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// instructions

void OP_00E0(chip8 * c8)
{
    memset((*c8).display, 0, sizeof((*c8).display));
    printf("CLS ");
}

//JP addr
void OP_1NNN(chip8 * c8)
{
    // setting counter to new memory point
    (*c8).PC = (*c8).opcode & 0x0FFF;
}

void OP_2NNN(chip8 * c8)
{
    //getting the address from opcode
    uint16_t addr = (*c8).opcode & 0xFFF;

    // setting the stack to the pc
    (*c8).stack[(*c8).SC] = (*c8).PC;
    //increment the stack pointer
    (*c8).SC++;

    (*c8).PC = addr;

}

void OP_00EE(chip8 * c8)
{
    // decrementing the stack pointer
    (*c8).SC--;
    
    // getting the prewius address
    (*c8).PC = (*c8).stack[(*c8).SC];

}

// LD Vx byte
void OP_6XNN(chip8 * c8)
{
    // getting the vars from the opcode
    uint8_t Vx = ((*c8).opcode & 0x0F00) >> 8u;
    uint8_t byte = (*c8).opcode & 0x00FF;

    // setting the register Vx to a value of byte
    (*c8).registers[Vx] = byte;
}

void OP_7XNN(chip8 * c8)
{
    // getting the vars from the opcode
    uint8_t Vx = ((*c8).opcode & 0x0F00) >> 8u;
    uint8_t byte = (*c8).opcode & 0x00FF;

    // setting the register Vx to a value Vx += byte
    (*c8).registers[Vx] += byte;
    printf("ADD Vx, byte ");
}

void OP_3XNN(chip8 * c8)
{
    uint8_t Vx = ((*c8).opcode & 0x0F00u) >> 8u;
    uint8_t byte = (*c8).opcode & 0x00FFu;

    if ((*c8).registers[Vx] == byte)
    {
        (*c8).PC += 2;
    }

}

void OP_4XNN(chip8 * c8)
{
    uint8_t Vx = ((*c8).opcode & 0x0F00u) >> 8u;
    uint8_t byte = (*c8).opcode & 0x00FFu;

    if ((*c8).registers[Vx] != byte)
    {
        (*c8).PC += 2;
    }
}

void OP_5XY0(chip8 * c8)
{
    uint8_t Vx = ((*c8).opcode & 0x0F00u) >> 8u;
    uint8_t Vy = ((*c8).opcode & 0x00F0u) >> 4u;

    if ((*c8).registers[Vx] == (*c8).registers[Vy])
    {
        (*c8).PC += 2;
    }
}

void OP_9XY0(chip8 * c8)
{
    uint8_t Vx = ((*c8).opcode & 0x0F00u) >> 8u;
    uint8_t Vy = ((*c8).opcode & 0x00F0u) >> 4u;

    if ((*c8).registers[Vx] != (*c8).registers[Vy])
    {
        (*c8).PC += 2;
    }
}

void OP_8XY0(chip8 * c8)
{
    uint8_t Vx = ((*c8).opcode & 0x0F00) >> 8u;
    uint8_t Vy = ((*c8).opcode & 0x00F0) >> 4u;

    (*c8).registers[Vx] = (*c8).registers[Vy];
}

void OP_8XY1(chip8 * c8)
{
    uint8_t Vx = ((*c8).opcode & 0x0F00) >> 8u;
    uint8_t Vy = ((*c8).opcode & 0x00F0) >> 4u;

    (*c8).registers[Vx] |= (*c8).registers[Vy];
}

void OP_8XY2(chip8 * c8)
{
    uint8_t Vx = ((*c8).opcode & 0x0F00) >> 8u;
    uint8_t Vy = ((*c8).opcode & 0x00F0) >> 4u;

    (*c8).registers[Vx] &= (*c8).registers[Vy];
}

void OP_8XY3(chip8 * c8)
{
    uint8_t Vx = ((*c8).opcode & 0x0F00) >> 8u;
    uint8_t Vy = ((*c8).opcode & 0x00F0) >> 4u;

    (*c8).registers[Vx] ^= (*c8).registers[Vy];
}

void OP_8XY4(chip8 * c8)
{
    uint8_t Vx = ((*c8).opcode & 0x0F00) >> 8u;
    uint8_t Vy = ((*c8).opcode & 0x00F0) >> 4u;
    int flag = 0;

    if( ((*c8).registers[Vx] + (*c8).registers[Vy]) > 255U)
    {
        flag = 1;
    }

    
    (*c8).registers[Vx] = (*c8).registers[Vx] + (*c8).registers[Vy];


    if(flag == 0)
    {
        (*c8).registers[0xF] = 0;
    }
    else
    {
        (*c8).registers[0xF] = 1;
    }
}

void OP_8XY5(chip8 * c8)
{
	uint8_t Vx = ((*c8).opcode & 0x0F00) >> 8u;
    uint8_t Vy = ((*c8).opcode & 0x00F0) >> 4u;
    uint8_t flag = 0;

    if((*c8).registers[Vy] > (*c8).registers[Vx])
    {
        flag = 1;
    }

    (*c8).registers[Vx] = (*c8).registers[Vx] - (*c8).registers[Vy];

    if(flag == 0)
    {
        (*c8).registers[0xF] = 1;
    }
    else if(Vy != 0xF)
    {
        (*c8).registers[0xF] = 0;
    }
}

void OP_8XY7(chip8 * c8)
{
    uint8_t Vx = ((*c8).opcode & 0x0F00) >> 8u;
    uint8_t Vy = ((*c8).opcode & 0x00F0) >> 4u;
    uint8_t flag = 0;

    if((*c8).registers[Vy] < (*c8).registers[Vx])
    {
        flag = 1;
    }

    (*c8).registers[Vx] = (*c8).registers[Vy] - (*c8).registers[Vx];

    if(flag == 0)
    {
        (*c8).registers[0xF] = 1;
    }
    else
    {
        (*c8).registers[0xF] = 0;
    }
}

void OP_8XY6(chip8 * c8)
{
    uint8_t Vx = ((*c8).opcode & 0x0F00) >> 8u;
    uint8_t Vy = ((*c8).opcode & 0x00F0) >> 4u;

    if((*c8).emuset == 1)
    {
        (*c8).registers[Vx] = (*c8).registers[Vy];
    }

    (*c8).registers[0xF] = ((*c8).registers[Vx] & 0x1u);

    (*c8).registers[Vx] >>= 1;
}

void OP_8XYE(chip8 * c8)
{
    uint8_t Vx = ((*c8).opcode & 0x0F00) >> 8u;
    uint8_t Vy = ((*c8).opcode & 0x00F0) >> 4u;

    if((*c8).emuset == 1)
    {
        (*c8).registers[Vx] = (*c8).registers[Vy];
    }

    (*c8).registers[0xF] = ((*c8).registers[Vx] & 0x80u) >> 7;

    (*c8).registers[Vx] <<= 1;
}


void OP_ANNN(chip8 * c8)
{
    //setting index to memoty defined in opcode
    (*c8).index = (*c8).opcode & 0x0FFF;
    printf("LD I, addr ");
}

void OP_BNNN(chip8 * c8)
{
    (*c8).PC = ((*c8).opcode & 0x0FFF) + (*c8).index;
}

void OP_CXNN(chip8 * c8)
{
    uint8_t Vx = ((*c8).opcode & 0x0F00u) >> 8u;
    uint8_t byte = (*c8).opcode & 0x00FFu;
    uint8_t random = rand() % 0x0100;

    (*c8).registers[Vx] =  random & byte;
}

void OP_DXYN(chip8 * c8)
{
    // getting the variables
    uint8_t height = (*c8).opcode & 0x000F;
    uint16_t y = (*c8).registers[((*c8).opcode & 0x00F0) >> 4u] % 32; 
    uint16_t x = (*c8).registers[((*c8).opcode & 0x0F00) >> 8u] % 64;
    uint8_t pixel;

    // setting the starting memory point to index
    uint16_t start = (*c8).index;

    (*c8).registers[0xF] = 0;


    for (int yline = 0; yline < height; yline++) 
    {

        pixel = (*c8).memory[start + yline];

        for(int xline = 0; xline < 8; xline++) 
        {
            if((pixel & (0b10000000 >> xline)) != 0) 
            {

                if((*c8).display[(x + xline + ((y + yline) * 64))] == 1)
                {
                    (*c8).registers[0xF] = 1;                                   
                }

                (*c8).display[x + xline + ((y + yline) * 64)] ^= 1;
            }

        }

    }


    printf("DRW %x, %x, nibble ", x, y);
}

void OP_EX9E(chip8 * c8) // new
{
    uint8_t Vx = (c8 -> opcode & 0x0F00u) >> 8u;
    uint8_t key = (*c8).registers[Vx];

    if ((*c8).keys[key])
    {
        (*c8).PC += 2;
    }
}

void OP_EXA1(chip8 * c8) // new
{
    uint8_t Vx = (c8 -> opcode & 0x0F00u) >> 8u;
    uint8_t key = (*c8).registers[Vx];

    if (!(*c8).keys[key])
    {
        (*c8).PC += 2;
    }
}

void OP_FX07(chip8 * c8)
{
    uint8_t Vx = ((*c8).opcode & 0x0F00u) >> 8u;
    (*c8).registers[Vx] = (*c8).delay_t;
}
void OP_FX15(chip8 * c8)
{
    uint8_t Vx = ((*c8).opcode & 0x0F00u) >> 8u;
    (*c8).delay_t = (*c8).registers[Vx];
}

void OP_FX1E(chip8 * c8) // new
{
    uint8_t Vx = ((*c8).opcode & 0x0F00u) >> 8u;
    uint16_t sum = (*c8).index + (*c8).registers[Vx];

    (*c8).index = ((*c8).index + (*c8).registers[Vx]) & 0x0FFF;
    
    if(sum < 0x0FFF)
    {
        (*c8).registers[0xF] = 1u;
    }
}

void OP_FX0A(chip8 * c8) // new
{
    	uint8_t Vx = (c8 -> opcode & 0x0F00u) >> 8u;

	if ((*c8).keys[0])
	{
		(*c8).registers[Vx] = 0;
	}
	else if ((*c8).keys[1])
	{
		(*c8).registers[Vx] = 1;
	}
	else if ((*c8).keys[2])
	{
		(*c8).registers[Vx] = 2;
	}
	else if ((*c8).keys[3])
	{
		(*c8).registers[Vx] = 3;
	}
	else if ((*c8).keys[4])
	{
		(*c8).registers[Vx] = 4;
	}
	else if ((*c8).keys[5])
	{
		(*c8).registers[Vx] = 5;
	}
	else if ((*c8).keys[6])
	{
		(*c8).registers[Vx] = 6;
	}
	else if ((*c8).keys[7])
	{
		(*c8).registers[Vx] = 7;
	}
	else if ((*c8).keys[8])
	{
		(*c8).registers[Vx] = 8;
	}
	else if ((*c8).keys[9])
	{
		(*c8).registers[Vx] = 9;
	}
	else if ((*c8).keys[10])
	{
		(*c8).registers[Vx] = 10;
	}
	else if ((*c8).keys[11])
	{
		(*c8).registers[Vx] = 11;
	}
	else if ((*c8).keys[12])
	{
		(*c8).registers[Vx] = 12;
	}
	else if ((*c8).keys[13])
	{
		(*c8).registers[Vx] = 13;
	}
	else if ((*c8).keys[14])
	{
		(*c8).registers[Vx] = 14;
	}
	else if ((*c8).keys[15])
	{
		(*c8).registers[Vx] = 15;
	}
	else
	{
		(*c8).PC -= 2;
	}
}

void OP_FX29(chip8 * c8) // new
{
    uint8_t Vx = (c8 -> opcode & 0x0F00) >> 8u;
    uint8_t digit = (*c8).registers[Vx];

    (*c8).index = FONTSET_START_ADDRESS + (5 * digit);
}


void OP_FX33(chip8 * c8)
{
    uint8_t Vx = ((*c8).opcode & 0x0F00u) >> 8u;
    uint8_t value = (*c8).registers[Vx];

    // Ones-place
    (*c8).memory[(*c8).index + 2] = value % 10;
    value /= 10;

    // Tens-place
    (*c8).memory[(*c8).index + 1] = value % 10;
    value /= 10;

    // Hundreds-place
    (*c8).memory[(*c8).index] = value % 10;
}

void OP_FX55(chip8 * c8)
{
    uint8_t Vx = ((*c8).opcode & 0x0F00u) >> 8u;

    if((*c8).emuset == 0)
    {
        for(uint8_t i = 0; i <= Vx; i++)
        {
            (*c8).memory[(*c8).index + i] = (*c8).registers[i];
        }
    }
    else if((*c8).emuset == 1)
    {
        uint8_t i = 0;
        while(i <= Vx)
        {
            (*c8).memory[(*c8).index] = (*c8).registers[i];
            (*c8).index++;
            i++;
        }
    }
}

void OP_FX65(chip8 * c8)
{
    uint8_t Vx = ((*c8).opcode & 0x0F00u) >> 8u;

    if((*c8).emuset == 0)
    {
        for(uint8_t i = 0; i <= Vx; i++)
        {
            (*c8).registers[i] = (*c8).memory[(*c8).index + i];
        }
    }
    else if((*c8).emuset == 1)
    {
        uint8_t i = 0;
        while(i <= Vx)
        {
            (*c8).registers[i] = (*c8).memory[(*c8).index];
            (*c8).index++;
            i++;
        }
    }
}
