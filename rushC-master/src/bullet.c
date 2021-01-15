#include "bullet.h"
#include "entity.h"

void shot_bullet(struct map *map, struct entity *player)
{
    struct vector2 speed = {0, 0};

    if(player->dir == DIR_LEFT)
        speed.x = -0.25;
    else
        speed.x = 0.25;

    struct entity bullet =
    {
        .type = BULLET,
        .pos = player->pos,
        .spd = speed,
        .acc = {0, 0},
        .dir = player->dir
    };

    add_entity(map, bullet);
}
