#include "Collectable.h"

void Collectable_Draw(Collectable *collectable, SDL_Renderer *renderer, uint32_t cell_size, uint32_t cell_count)
{
    SDL_Color collectable_color = { 255, 50, 50, 1 };
    Draw_Cell(renderer, collectable->position, (DrawCellParams){
        cell_count,
        cell_size,
        collectable_color,
        COLLECTABLE_DRAW_OFFSET
    });
}

void Collectable_GenerateRandomPosition(Collectable *collectable, uint32_t cell_count)
{
    uint32_t new_position_x = 0 + rand() % (cell_count);
    uint32_t new_position_y = 0 + rand() % (cell_count);
    Vec2 new_position = {(float)new_position_x, (float)new_position_y};

    collectable->position = new_position;
}