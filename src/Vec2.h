#ifndef __VEC2_H__
#define __VEC2_H__

#include <stdint.h>
#include <math.h>
#include <SDL2/SDL.h>

#define SCALE 65535

typedef struct Vec2
{
    float_t x;
    float_t y;
} Vec2;

Vec2 Vec2_Normalize(Vec2 vec);
SDL_bool Vec2_Is(Vec2 target_vec, Vec2 src_vec);
SDL_bool Vec2_IsOneOf(Vec2 target_vec, Vec2 *vecs, size_t vecs_length);

#endif // __VEC2_H__