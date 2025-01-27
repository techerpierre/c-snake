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