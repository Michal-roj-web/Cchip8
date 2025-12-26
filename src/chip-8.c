#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// for reading the rom
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

// for time
#include <sys/time.h>
#include <time.h>
struct timeval end, start;

// my .h files
#include "chip-8.h"
#include "platform.h"
#include "opcodes.h"

const uint8_t fontset[FONTSET_SIZE] =
{
	0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	0x20, 0x60, 0x20, 0x20, 0x70, // 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

// initial setup
void c8start(chip8 * chip8)
{
    // setting tables to zero
    memset((*chip8).memory, 0, sizeof((*chip8).memory));
    memset((*chip8).keys, 0, sizeof((*chip8).keys));
    OP_00E0(chip8);

    //loading fontset into memory
    for (unsigned int i = 0; i < FONTSET_SIZE; ++i)
	{
		(*chip8).memory[FONTSET_START_ADDRESS + i] = fontset[i];
	}

    //setting pointers and timers to defalut value
    chip8->PC = START_ADDRESS;
    chip8->SC = 0b0;
    chip8->delay_t = 0;
    chip8->sound_t = 0;

    srand(time(NULL));


    //starting the sdl platform
    platstart();
    upscr(chip8);

}

void loadprog(chip8 * chip8, char * filename)
{
    
    FILE *fptr;

    // Open a file in read mode
    fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
        printf("Could not open.\n");
        exit(1);
    }

    int size = 5000;

    // Store the content of the file
    char buffer = 0x00;
    
    // Read the content and store it inside myString

    // writing the content of the file
    int i = 0;
    printf("Memory:\n");
    while(fread(&buffer, sizeof(char), 1, fptr) != 0)
    {
        (*chip8).memory[START_ADDRESS + i] = buffer;
        printf("%x ", (*chip8).memory[START_ADDRESS + i]);
        i++;
    }
    printf("\n");
    fclose(fptr);


    printf("funkcje: ");

}

// one procesor cycle
void cycle(chip8 * chip8)
{
    isKey(chip8);
    // setting the opcode to 0x(PC)(PC+1)
    chip8->opcode = 
    ((*chip8).memory[(*chip8).PC] << 8u) | (*chip8).memory[((*chip8).PC) + 1]; 


    // making the Program counter go to the nex instruction
    (*chip8).PC += 2;

    printf("pc: %x, opcode: %x ", (*chip8).PC, chip8->opcode);
    
    upscr(chip8);

    execute(chip8);
}

void execute(chip8 * chip8)
{
    uint16_t opcodesn = (chip8->opcode) >> 12u;

    if(opcodesn == 0x0) case_0(chip8);
    else if(opcodesn == 0x1) OP_1NNN(chip8);
    else if(opcodesn == 0x2) OP_2NNN(chip8);
    else if(opcodesn == 0x6) OP_6XNN(chip8);
    else if(opcodesn == 0x7) OP_7XNN(chip8);
    else if(opcodesn == 0x3) OP_3XNN(chip8);
    else if(opcodesn == 0x4) OP_4XNN(chip8);
    else if(opcodesn == 0x5) OP_5XY0(chip8);
    else if(opcodesn == 0x9) OP_9XY0(chip8);
    else if(opcodesn == 0x8) case_8(chip8);
    else if(opcodesn == 0xA) OP_ANNN(chip8);
    else if(opcodesn == 0xB) OP_BNNN(chip8);
    else if(opcodesn == 0xC) OP_CXNN(chip8);
    else if(opcodesn == 0xD) OP_DXYN(chip8);
    else if(opcodesn == 0xE) case_e(chip8);
    else if(opcodesn == 0xF) case_f(chip8);
    
}

void case_0(chip8 * chip8)
{
    uint16_t opcodesn = ((chip8->opcode) & 0x000F);

    if(opcodesn == 0x0) OP_00E0(chip8);
    if(opcodesn == 0xE) OP_00EE(chip8);

}

void case_8(chip8 * chip8)
{
    uint16_t opcodesn = ((chip8->opcode) & 0x000F);
    if(opcodesn == 0x0) OP_8XY0(chip8);
    else if(opcodesn == 0x1) OP_8XY1(chip8);
    else if(opcodesn == 0x2) OP_8XY2(chip8);
    else if(opcodesn == 0x3) OP_8XY3(chip8);
    else if(opcodesn == 0x4) OP_8XY4(chip8);
    else if(opcodesn == 0x5) OP_8XY5(chip8);
    else if(opcodesn == 0x6) OP_8XY6(chip8);
    else if(opcodesn == 0x7) OP_8XY7(chip8);
    else if(opcodesn == 0xE) OP_8XYE(chip8);
}

void case_e(chip8 * chip8)
{
    uint16_t opcodesn = ((chip8->opcode) & 0x00FF);
    if(opcodesn == 0x9E) OP_EX9E(chip8);
    if(opcodesn == 0xA1) OP_EXA1(chip8);
}

void case_f(chip8 * chip8)
{
    uint16_t opcodesn = ((chip8->opcode) & 0x00FF);

    if(opcodesn == 0x33) OP_FX33(chip8);
    else if(opcodesn == 0x1E) OP_FX1E(chip8);
    else if(opcodesn == 0x07) OP_FX07(chip8);
    else if(opcodesn == 0x29) OP_FX29(chip8);
    else if(opcodesn == 0x15) OP_FX15(chip8);
    else if(opcodesn == 0x55) OP_FX55(chip8);
    else if(opcodesn == 0x65) OP_FX65(chip8);
    else if(opcodesn == 0x0A) OP_FX0A(chip8);
}
