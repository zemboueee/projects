#include "vector2.h"

struct vector2 add_vect(struct vector2 vec1, struct vector2 vec2)
{
    struct vector2 vec =
    {
        vec1.x + vec2.x,
        vec1.y + vec2.y
    };
    return vec;
}

struct vector2 scale_vect(float scalar, struct vector2 vec)
{
    struct vector2 scaled =
    {
        scalar * vec.x,
        scalar * vec.y
    };
    return scaled;
}
