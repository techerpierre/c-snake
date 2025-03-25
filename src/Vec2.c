#include "Vec2.h"

Vec2 Vec2_Normalize(Vec2 vec)
{
    double length = sqrt((double)vec.x * vec.x + (double)vec.y * vec.y);
    if (length == 0) return (Vec2){0.0, 0.0};

    return (Vec2){
        vec.x / length,
        vec.y / length
    };
}

SDL_bool Vec2_Is(Vec2 src_vec, Vec2 target_vec)
{
    return src_vec.x == target_vec.x && src_vec.y == target_vec.y;
}

SDL_bool Vec2_IsOneOf(Vec2 target_vec, Vec2 *vecs, size_t vecs_length)
{
    for (int i = 0; i < vecs_length; i++)
    {
        if (Vec2_Is(vecs[i], target_vec))
            return SDL_TRUE;
    }
    return SDL_FALSE;
}