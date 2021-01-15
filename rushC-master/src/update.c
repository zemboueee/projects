#include "update.h"
#include "entity.h"
#include "bullet.h"
#include "map.h"
#include "utils.h"
#include "vector2.h"
#include "display.h"

#define RELOAD_LIFE 40

static int invulnerability = RELOAD_LIFE;
static int jump_value = 1;
static int jump_count = 0;
static int reload = RELOAD_TIME;
static int life = 3;
static int life_max = 10;
static int gun = 0;

int get_gamestate()
{
    if(life == 0)
        return 2;
    return 1;
}
void display_life(struct display *display)
{
    display_life_bar(display->renderer, life, life_max);
}

void update_player(struct entity *player, struct map *map, struct input input)
{
    life = fmax(0, life);
    player->spd.x = 0;
    if (input.inputs[RIGHT])
        player->spd.x = 0.15;
    if (input.inputs[LEFT])
        player->spd.x = -0.15;
    apply_gravity(player, 1);
    update_entity(player, 1);
    collision(player, map);

    if (is_on_floor(player, map))
        jump_count = jump_value;

    if (input.inputs[SPACE] && jump_count > 0)
    {
        jump(player, 1);
        jump_count--;
    }

    if (get_block(map, player->pos) == SPIKE && invulnerability >= RELOAD_LIFE)
    {
        life--;
        invulnerability = 0;
    }
    invulnerability++;

    reload -= 1;
    if(reload < 0)
    {
        reload = RELOAD_TIME;
        if (gun && input.inputs[SHOOT])
            shot_bullet(map, player);
    }

    update_direction(player);

    if (input.inputs[NEXT])
    {
        player->pos.x = map->width;
        player->pos.y = map->height;
    }

}

void update_map_entities(struct map *map)
{
    for (int i = 0; i < map->nbentities; i++)
    {
        int xp = map->player.pos.x;
        int yp = map->player.pos.y;
        int x = map->entities[i].pos.x;
        int y = map->entities[i].pos.y;
        enum blocktype block = get_block(map, map->entities[i].pos);
        struct vector2 right =
        {
            map->entities[i].pos.x + 1,
            map->entities[i].pos.y
        };
        enum blocktype block_right = get_block(map, right);

        switch (map->entities[i].type)
        {
            case BULLET:
                if (block == DBLOCK)
                    map->block[x + map->width * y] = AIR;
                if (block != AIR)
                    delete_entity(map, i);
                for (int j = 0; j < map->nbentities; j++)
                {
                    if (entities_contact(&map->entities[i], &map->entities[j]))
                    {
                        if (map->entities[j].type == ENEMY)
                        {
                            map->entities[j].type = COKE;
                            map->entities[j].spd.x = 0;
                            map->entities[j].spd.y = 0;
                            delete_entity(map, i);
                        }
                    }
                }
                break;
            case ENEMY:
                if (block != AIR)
                    map->entities[i].spd.x = 0.1;
                if (block_right != AIR)
                    map->entities[i].spd.x = -0.1;
                if (invulnerability >= RELOAD_LIFE
                        && entities_contact(&map->entities[i], &map->player))
                {
                    life--;
                    invulnerability = 0;
                }
                break;
            case GUN_PICKUP:
                if (fti(map->entities[i].pos.x == xp
                            && fti(map->entities[i].pos.y == yp)))
                {
                    delete_entity(map, i);
                    gun = 1;
                }
                break;
            case DOUBLE_JUMP_PICKUP:
                if (fti(map->entities[i].pos.x == xp
                            && fti(map->entities[i].pos.y == yp)))
                {
                    delete_entity(map, i);
                    jump_value = 2;
                }
                break;
            case COKE:
                if (entities_contact(&map->entities[i], &map->player))
                {
                    delete_entity(map, i);
                    life++;
                }
                break;

            default:
                break;
        }
    }
}
