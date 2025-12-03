#ifndef CHIP8_H
#define CHIP8_H

#include <stdint.h>

// important consts define
#define FONTSET_SIZE 80
#define FONTSET_START_ADDRESS 0x50 // where in memory fonts start
#define START_ADDRESS 0x200 // starting point for rom instructions
#define KEY_COUNT 16
#define MEMORY_SIZE 4096
#define REGISTER_COUNT 16
#define STACK_LEVELS 16
#define VIDEO_HEIGHT 32
#define VIDEO_WIDTH 64

// chip8 type define
typedef struct
{
    uint8_t registers[REGISTER_COUNT];
    uint8_t memory[MEMORY_SIZE];
    uint16_t index;
    uint16_t PC;
    uint16_t stack[STACK_LEVELS];
    uint8_t SC;
    uint8_t delay_t;
    uint8_t sound_t;
    uint8_t keys[KEY_COUNT];
    uint8_t display[VIDEO_WIDTH * VIDEO_HEIGHT];
    uint16_t opcode;
    uint8_t emuset;
}chip8;

// functions

void c8start(chip8 * chip8);
void cycle(chip8 * chip8);
void execute(chip8 * chip8);
void loadprog(chip8 * chip8, char * filename);

// cases
void case_0(chip8 * chip8);
void case_8(chip8 * chip8);
void case_e (chip8 * chip8);
void case_f(chip8 * chip8);


#endif