#ifndef __DRAW_H__
#define __DRAW_H__

#include <SDL2/SDL.h>
#include <math.h>
#include "Vec2.h"

typedef struct DrawCellParams
{
    uint32_t cell_count;
    uint32_t cell_size;
    SDL_Color color;
    uint32_t offset;
} DrawCellParams;


void Draw_Cell(SDL_Renderer *renderer, Vec2 pos, DrawCellParams params);
void Draw_Background(SDL_Renderer *renderer, uint32_t cell_count, uint32_t cell_size);

#endif // __DRAW_H__