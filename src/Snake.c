#include "Snake.h"

Snake *Snake_Init(SnakeInitData params)
{
    Snake *snake = (Snake*)malloc(sizeof(Snake));

    if (snake == NULL)
    {
        fprintf(stderr, "Memoty allocation failed when created snake.");
        exit(EXIT_FAILURE);
    }

    uint32_t middle = params.cell_count / 2;
    snake->head = (Vec2){middle, middle + 1};
    snake->velocity = (Vec2){0, -1};
    snake->body_length = 0;
    snake->body_capacity = 0;
    snake->body = NULL;

    for (int i = 0; i < SNAKE_DEFAULT_BODY_SIZE; i++)
        Snake_Enlarge(snake);

    return snake;
}

void Snake_Event(Snake *snake, Inputs *inputs)
{
    if (Input_IsPressed(inputs, INPUT_LEFT) && snake->velocity.x < 1)
        snake->velocity = (Vec2){-1, 0};
    else if (Input_IsPressed(inputs, INPUT_RIGHT) && snake->velocity.x > -1)
        snake->velocity = (Vec2){1, 0};
    else if (Input_IsPressed(inputs, INPUT_UP) && snake->velocity.y < 1)
        snake->velocity = (Vec2){0, -1};
    else if (Input_IsPressed(inputs, INPUT_DOWN) && snake->velocity.y > -1)
        snake->velocity = (Vec2){0, 1};
}

void Snake_Update(Snake *snake)
{
    _Snake_ApplyVelocity(snake);
}

Snake *Snake_Clear(Snake *snake)
{
    free(snake->body);
    free(snake);
    return NULL;
}

void Snake_Enlarge(Snake *snake)
{
    Vec2 normalized_velocity = Vec2_Normalize(snake->velocity);
    Vec2 last_position = snake->body_length > 0 ? snake->body[snake->body_length - 1] : snake->head;

    if (snake->body_length + 1 > snake->body_capacity)
        _Snake_ExtendBodySize(snake);

    snake->body[snake->body_length++] = (Vec2){
        last_position.x - normalized_velocity.x,
        last_position.y - normalized_velocity.y
    };
}

bool Snake_Overscreen(Snake *snake, uint32_t cell_count)
{
    bool is_overflowing_x = (snake->head.x > cell_count - 1) && snake->velocity.x > 0;
    bool is_overflowing_y = (snake->head.y > cell_count - 1) && snake->velocity.y > 0;
    bool is_overflowing_nx = (snake->head.x < 0) && snake->velocity.x < 0;
    bool is_overflowing_ny = (snake->head.y < 0) && snake->velocity.y < 0;
    return  is_overflowing_x || is_overflowing_y || is_overflowing_nx || is_overflowing_ny;
}

bool Snake_CollideWith(Snake *snake, Vec2 target)
{
    return snake->head.x == target.x && snake->head.y == target.y;
}

bool Snake_SelfCollide(Snake *snake)
{
    for (int i = 0; i < snake->body_length; i++)
        if (Snake_CollideWith(snake, snake->body[i]))
            return true;
    return false;
}

void Snake_Draw(Snake *snake, SDL_Renderer *renderer, uint32_t cell_size, uint32_t cell_count)
{
    SDL_Color snake_color = {50, 50, 255, 1};

    for (int i = 0; i < snake->body_length; i++)
    {
        Draw_Cell(renderer, snake->body[i], (DrawCellParams){
            cell_count,
            cell_size,
            snake_color,
            SNAKE_DRAW_OFFSET
        });
    }

    Draw_Cell(renderer, snake->head, (DrawCellParams){
        cell_count,
        cell_size,
        snake_color,
        SNAKE_DRAW_OFFSET
    });
}

void _Snake_ExtendBodySize(Snake *snake)
{
    if (snake->body == NULL)
    {
        Vec2 *new_body = (Vec2*)malloc(sizeof(Vec2) * SNAKE_ALLOCATION_PAD);
        if (new_body == NULL)
        {
            fprintf(stderr, "Memoty allocation failed when initialized snake body size.");
            exit(EXIT_FAILURE);
        }

        snake->body = new_body;
        snake->body_capacity = SNAKE_ALLOCATION_PAD;
    }
    else
    {
        Vec2 *new_body = (Vec2*)realloc(snake->body, sizeof(Vec2) * (snake->body_capacity + SNAKE_ALLOCATION_PAD));
        if (new_body == NULL)
        {
            fprintf(stderr, "Memoty allocation failed when extended snake body size.");
            exit(EXIT_FAILURE);
        }

        snake->body = new_body;
        snake->body_capacity += SNAKE_ALLOCATION_PAD;
    }
}

void _Snake_ApplyVelocity(Snake *snake)
{
    for (int i = snake->body_length - 1; i > 0; i--)
        snake->body[i] = snake->body[i - 1];

    if (snake->body_length > 0)
        snake->body[0] = snake->head;

    Vec2 normalized_velocity = Vec2_Normalize(snake->velocity);
    snake->head.x += normalized_velocity.x;
    snake->head.y += normalized_velocity.y;
}