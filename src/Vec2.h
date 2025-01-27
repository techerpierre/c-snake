#ifndef __VEC2_H__
#define __VEC2_H__

#include <stdint.h>
#include <math.h>

#define SCALE 65535

typedef struct Vec2
{
    float_t x;
    float_t y;
} Vec2;

Vec2 Vec2_Normalize(Vec2 vec);


#endif // __VEC2_H__