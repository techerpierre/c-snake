#ifndef __COLLECTABLE_H__
#define __COLLECTABLE_H__

#include <SDL2/SDL.h>
#include <time.h>
#include "Vec2.h"
#include "Draw.h"
#include "stdio.h"

#define COLLECTABLE_DRAW_OFFSET 2

typedef struct Collectable
{
    Vec2 position;
} Collectable;

void Collectable_Draw(Collectable *collectable, SDL_Renderer *renderer, uint32_t cell_size, uint32_t cell_count);
void Collectable_GenerateRandomPosition(Collectable *collectable, uint32_t cell_count);

#endif // __COLLECTABLE_H__