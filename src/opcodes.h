#ifndef OPCODES
#define OPCODES

#include "chip-8.h"

// instructions

// CLS
void OP_00E0(chip8 * c8);

// JP addr
void OP_1NNN(chip8 * c8);

// CALL addr
void OP_2NNN(chip8 * c8); 

// RET
void OP_00EE(chip8 * c8); 

//skip if not
void OP_3XNN(chip8 * c8); 
void OP_4XNN(chip8 * c8); 
void OP_5XY0(chip8 * c8); 
void OP_9XY0(chip8 * c8); 

// LD Vx, byte
void OP_6XNN(chip8 * c8);

// ADD Vx, byte
void OP_7XNN(chip8 * c8);

// logic and arithmetic
void OP_8XY0(chip8 * c8); 
void OP_8XY1(chip8 * c8); 
void OP_8XY2(chip8 * c8); 
void OP_8XY3(chip8 * c8); 
void OP_8XY4(chip8 * c8); 
void OP_8XY5(chip8 * c8); 
void OP_8XY7(chip8 * c8); 
void OP_8XY6(chip8 * c8); 
void OP_8XYE(chip8 * c8); 


// LD I, addr
void OP_ANNN(chip8 * c8);

void OP_BNNN(chip8 * c8);

void OP_CXNN(chip8 * c8);


// DWR Vx, Vy, nibble
void OP_DXYN(chip8 * c8);

// SKIP IF KEY
void OP_EX9E(chip8 * c8); //new
void OP_EXA1(chip8 * c8); //new

//timers
void OP_FX07(chip8 * c8);
void OP_FX15(chip8 * c8);
void OP_FX18(chip8 * c8); //todo

// Add to index
void OP_FX1E(chip8 * c8); // new

// GET KEY
void OP_FX0A(chip8 * c8); // new

// Set the index to the Font character
void OP_FX29(chip8 * c8); //todo


// Binary-coded decimal conversion
void OP_FX33(chip8 * c8);

// Store and load memory
void OP_FX55(chip8 * c8);
void OP_FX65(chip8 * c8);


#endif