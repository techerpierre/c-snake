#include "Game.h"
#include "Vec2.h"

Game *Game_Init(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "SDL initialisation failed: %s.\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    Game *game = (Game*)malloc(sizeof(Game));

    if (game == NULL)
    {
        fprintf(stderr, "Memoty allocation failed when createinitialised the game.\n");
        exit(EXIT_FAILURE);
    }

    game->running = true;
    game->score = 0;
    game->cell_size = CELL_SIZE;
    game->cell_count = CELL_COUNT;
    game->update_snake = true;

    uint16_t screen_size = Game_GetScreenSize(game);

    SDL_Window *window = SDL_CreateWindow("CSnake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_size, screen_size, SDL_WINDOW_SHOWN);

    if (window == NULL)
    {
        fprintf(stderr, "An error occured when initialised window: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL)
    {
        fprintf(stderr, "An error occured when created renderer: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    game->window = window;
    game->renderer = renderer;

    srand(time(NULL));

    return game;
}

void *Game_Run(Game *game)
{
    _Game_Setup(game);
    while (game->running)
    {
        _Game_PreventTick(&game->ticks_handler);
        _Game_Event(game);
        _Game_Update(game);
        _Game_Tick(&game->ticks_handler, &game->update_snake);
    }
    _Game_Clear(game);
}

Game *Game_Quit(Game *game)
{
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);

    free(game);

    return NULL;
}

uint32_t Game_GetScreenSize(Game *game)
{
    return game->cell_size * game->cell_count;
}

void _Game_Setup(Game *game)
{
    SnakeInitData snake_init_params = {game->cell_count};
    Snake *snake = Snake_Init(snake_init_params);
    game->snake = snake;
    _Game_GenerateCollectablePosition(game);
}

void _Game_Event(Game *game)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            game->running = false;
            break;
        case SDL_KEYDOWN:
            Input_SetKey(&game->inputs, _Game_SDLKeyToInputKey(event));
            break;
        case SDL_KEYUP:
            Input_RemoveKey(&game->inputs, _Game_SDLKeyToInputKey(event));
            break;
        default:
            break;
        }
    }

    Snake_Event(game->snake, &game->inputs);

    if (Snake_Overscreen(game->snake, game->cell_count) || Snake_SelfCollide(game->snake))
        game->running = false;

    if (Snake_CollideWith(game->snake, game->collectable.position))
    {
        _Game_GenerateCollectablePosition(game);
        Snake_Enlarge(game->snake);
        game->score++;
    }
}

void _Game_Update(Game *game)
{
    if (!game->running)
        return;

    SDL_RenderClear(game->renderer);

    Draw_Background(game->renderer, game->cell_count, game->cell_size);

    Collectable_Draw(&game->collectable, game->renderer, game->cell_size, game->cell_count);

    if (game->update_snake)
    {
        Snake_Update(game->snake);
    }

    Snake_Draw(game->snake, game->renderer, game->cell_size, game->cell_count);

    SDL_RenderPresent(game->renderer);
}

void _Game_Clear(Game *game)
{
    printf("Ton score est de %d", game->score);
    Snake_Clear(game->snake);
}

void _Game_PreventTick(GameTickshandler *ticks_handler)
{
    ticks_handler->start_time = SDL_GetTicks();
}

void _Game_Tick(GameTickshandler *ticks_handler, bool *update_snake)
{
    uint32_t current_time = SDL_GetTicks();
    ticks_handler->frame_time = current_time - ticks_handler->start_time;

    ticks_handler->accumulated_time += ticks_handler->frame_time;

    if (ticks_handler->accumulated_time >= FRAME_TIME)
    {
        *update_snake = true;
        ticks_handler->accumulated_time = 0;
    } else {
        *update_snake = false;
    }
}

InputKey _Game_SDLKeyToInputKey(SDL_Event event)
{
    switch (event.key.keysym.sym)
    {
    case SDLK_q: return INPUT_LEFT;
    case SDLK_d: return INPUT_RIGHT;
    case SDLK_z: return INPUT_UP;
    case SDLK_s: return INPUT_DOWN;
    }
}

void _Game_GenerateCollectablePosition(Game *game)
{
    do {
        Collectable_GenerateRandomPosition(&game->collectable, game->cell_count);
    } while (
        Vec2_IsOneOf(game->collectable.position, game->snake->body, game->snake->body_length) ||
        Vec2_Is(game->collectable.position, game->snake->head));    
}