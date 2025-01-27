#ifndef __SNAKE_H__
#define __SNAKE_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "Vec2.h"
#include "Draw.h"
#include "Inputs.h"

#define SNAKE_ALLOCATION_PAD 10
#define SNAKE_DEFAULT_BODY_SIZE 2
#define SNAKE_DRAW_OFFSET 2

typedef struct SnakeInitData
{
    uint32_t cell_count;
} SnakeInitData;

typedef struct SnakeUpdateData
{
    SDL_Renderer *renderer;
    uint32_t cell_size;
    uint32_t cell_count;
} SnakeUpdateData;


typedef struct Snake
{
    Vec2 head;
    Vec2 *body;
    Vec2 velocity;
    uint32_t body_length;
    size_t body_capacity;
} Snake;

Snake *Snake_Init(SnakeInitData params);
void Snake_Event(Snake *snake, Inputs *inputs);
void Snake_Update(Snake *snake);
Snake *Snake_Clear(Snake *snake);
void Snake_Enlarge(Snake *snake);
bool Snake_Overscreen(Snake *snake, uint32_t cell_count);
bool Snake_CollideWith(Snake *snake, Vec2 target);
bool Snake_SelfCollide(Snake *snake);
void Snake_Draw(Snake *snake, SDL_Renderer *renderer, uint32_t cell_size, uint32_t cell_count);

void _Snake_ExtendBodySize(Snake *snake);
void _Snake_ApplyVelocity(Snake *snake);

#endif // __SNAKE_H__