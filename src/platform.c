#include <stdio.h>
#include <SDL2/SDL.h>
#include "platform.h"
#include "chip-8.h"

SDL_Window * window = NULL;
SDL_Renderer * renderer = NULL;
SDL_Event ev;
int col = 0;

void platstart()
{
    // initialzing the SDL
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(64*10 + 1,32*10 + 1,0,&window,&renderer);
    SDL_SetWindowTitle(window, "Chip8 Emulator");
}

void isKey(chip8 * c8)
{
    // update the event
    SDL_PollEvent(&ev);

    // if we are trying to close the program
    if(ev.type == SDL_QUIT)
    {
        printf("\n");
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(0);
    }

    // if key is pressed
    if(ev.type == SDL_KEYDOWN)
    {
        switch(ev.key.keysym.sym)
        {
            case SDLK_l:
            {
                col++;
                if(col>3) col = 0;
            } break;

            case SDLK_x:
            {
                (*c8).keys[0] = 1;
            } break;

            case SDLK_1:
            {
                (*c8).keys[1] = 1;
            } break;

            case SDLK_2:
            {
                (*c8).keys[2] = 1;
            } break;

            case SDLK_3:
            {
                (*c8).keys[3] = 1;
            } break;

            case SDLK_q:
            {
                (*c8).keys[4] = 1;
            } break;

            case SDLK_w:
            {
                (*c8).keys[5] = 1;
            } break;

            case SDLK_e:
            {
                (*c8).keys[6] = 1;
            } break;

            case SDLK_a:
            {
                (*c8).keys[7] = 1;
            } break;

            case SDLK_s:
            {
                (*c8).keys[8] = 1;
            } break;

            case SDLK_d:
            {
                (*c8).keys[9] = 1;
            } break;

            case SDLK_z:
            {
                (*c8).keys[0xA] = 1;
            } break;

            case SDLK_c:
            {
                (*c8).keys[0xB] = 1;
            } break;

            case SDLK_4:
            {
                (*c8).keys[0xC] = 1;
            } break;

            case SDLK_r:
            {
                (*c8).keys[0xD] = 1;
            } break;

            case SDLK_f:
            {
                (*c8).keys[0xE] = 1;
            } break;

            case SDLK_v:
            {
                (*c8).keys[0xF] = 1;
            } break;
        }
    }

    // if key is not pressed
    if(ev.type == SDL_KEYUP)
    {
        switch (ev.key.keysym.sym)
        {
            case SDLK_x:
            {
                (*c8).keys[0] = 0;
            } break;

            case SDLK_1:
            {
                (*c8).keys[1] = 0;
            } break;

            case SDLK_2:
            {
                (*c8).keys[2] = 0;
            } break;

            case SDLK_3:
            {
                (*c8).keys[3] = 0;
            } break;

            case SDLK_q:
            {
                (*c8).keys[4] = 0;
            } break;

            case SDLK_w:
            {
                (*c8).keys[5] = 0;
            } break;

            case SDLK_e:
            {
                (*c8).keys[6] = 0;
            } break;

            case SDLK_a:
            {
                (*c8).keys[7] = 0;
            } break;

            case SDLK_s:
            {
                (*c8).keys[8] = 0;
            } break;

            case SDLK_d:
            {
                (*c8).keys[9] = 0;
            } break;

            case SDLK_z:
            {
                (*c8).keys[0xA] = 0;
            } break;

            case SDLK_c:
            {
                (*c8).keys[0xB] = 0;
            } break;

            case SDLK_4:
            {
                (*c8).keys[0xC] = 0;
            } break;

            case SDLK_r:
            {
                (*c8).keys[0xD] = 0;
            } break;

            case SDLK_f:
            {
                (*c8).keys[0xE] = 0;
            } break;

            case SDLK_v:
            {
                (*c8).keys[0xF] = 0;
            } break;
        }
    }
}

void upscr(chip8 * c8)
{
    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255); // rend, r, g, b, alpha 
    SDL_RenderClear(renderer);

    // making and drawing a rectangle
    SDL_Rect rect;

    int8_t table[64 * 32];
    memset(table, 0, sizeof(table));

    table[64/2 + ((32/2)*64)] = 1;

    rect.w = 9;
    rect.h = 9;

    for(int j = 0; j < 32; j++)
    {
        for(int i=0; i < 64; i++)
        {
            rect.x = 1 + (i * 10);
            rect.y = 1 + (j * 10);
            if( (*c8).display[i + (j*64)] == 1)
            {
                if(col == 0)
                {
                    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
                    SDL_RenderFillRect(renderer, &rect);
                }                
                else if(col == 1)
                {
                    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
                    SDL_RenderFillRect(renderer, &rect);
                }
                else if(col == 2)
                {
                    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
                    SDL_RenderFillRect(renderer, &rect);
                }
                else
                {
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    SDL_RenderFillRect(renderer, &rect);
                }
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
    SDL_RenderPresent(renderer);
}