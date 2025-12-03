#include <SDL2/SDL.h>
#include "chip-8.h"
#ifndef PLATFORM
#define PLATFORM

void drawscreen(SDL_Renderer * renderer);
void platstart();
void upscr(chip8 * c8);
void isKey(chip8 * c8);

#endif