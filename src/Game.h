#ifndef __GAME_H__
#define __GAME_H__

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include "Snake.h"
#include "Inputs.h"
#include "Collectable.h"

#define CELL_SIZE 20
#define CELL_COUNT 25
#define TARGET_FPS 8
#define FRAME_TIME (1000 / TARGET_FPS)

typedef struct GameTickshandler
{
    uint32_t start_time, frame_time, accumulated_time;
} GameTickshandler;


typedef struct Game
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool running;
    uint32_t score;
    uint32_t cell_size;
    uint32_t cell_count;
    Snake *snake;
    bool update_snake;
    GameTickshandler ticks_handler;
    Inputs inputs;
    Collectable collectable;
} Game;

Game *Game_Init(void);
void *Game_Run(Game *game);
Game *Game_Quit(Game *game);

uint32_t Game_GetScreenSize(Game *game);

void _Game_Setup(Game *game);
void _Game_Event(Game *game);
void _Game_Update(Game *game);
void _Game_Clear(Game *game);
void _Game_PreventTick(GameTickshandler *ticks_handler);
void _Game_Tick(GameTickshandler *ticks_handler, bool *update_snake);
InputKey _Game_SDLKeyToInputKey(SDL_Event event);
void _Game_GenerateCollectablePosition(Game *game);

#endif // __GAME_H__