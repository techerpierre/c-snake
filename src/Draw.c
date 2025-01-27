#include "Draw.h"

#include <stdio.h>

void Draw_Cell(SDL_Renderer *renderer, Vec2 pos, DrawCellParams params)
{
    if (
        pos.x < params.cell_count &&
        pos.x >= 0 &&
        pos.y < params.cell_count &&
        pos.y >= 0
    )
    {
        uint32_t pos_offset = params.offset != 0 ? params.offset / 2 : 0;

        SDL_Rect cell = {
            (int)round(pos.x) * params.cell_size + pos_offset,
            (int)round(pos.y) * params.cell_size + pos_offset,
            params.cell_size - params.offset,
            params.cell_size - params.offset
        };

        SDL_SetRenderDrawColor(
            renderer,
            params.color.r,
            params.color.g,
            params.color.b,
            params.color.a
        );
        SDL_RenderFillRect(renderer, &cell);
    }
}

void Draw_Background(SDL_Renderer *renderer, uint32_t cell_count, uint32_t cell_size)
{
    for (int y = 0; y < cell_count; y++)
       for (int x = 0; x < cell_count; x++)
       {
           SDL_Color color = {0, 0, 0, 1};
           if ((y % 2 == 0 && x % 2 != 0) || (y % 2 != 0 && x % 2 == 0))
               color = (SDL_Color){10, 10, 15, 1};
           else
               color = (SDL_Color){17 ,17 ,22, 1};

               Draw_Cell(renderer, (Vec2){x, y}, (DrawCellParams){
                   cell_count,
                   cell_size,
                   color,
               });
       }
}