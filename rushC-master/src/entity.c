#include <math.h>
#include "entity.h"
#include "vector2.h"
#include "utils.h"
#include "map.h"

void update_entity(struct entity *entity, float delta)
{

    entity->pos = add_vect(entity->pos, scale_vect(delta, entity->spd));
    entity->spd = add_vect(entity->spd, scale_vect(delta, entity->acc));

    update_direction(entity);
}

int entities_contact(struct entity *ent1, struct entity *ent2)
{
    struct vector2 vect1 = {ent1->pos.x, ent1->pos.y};
    struct vector2 vect2 = {ent2->pos.x, ent2->pos.y};

    return fti(vect1.x) == fti(vect2.x) && fti(vect1.y) == fti(vect2.y);
}

int entity_collide(struct entity *entity, struct map *map)
{
    int res = 0;

    struct vector2 pos = entity->pos;
    float half = 0.5;

    pos.x += half;
    pos.y += half;


    struct vector2 top = {pos.x, pos.y - half};
    struct vector2 right = {pos.x + half , pos.y};
    struct vector2 down = {pos.x, pos.y + half};
    struct vector2 left = {pos.x - half, pos.y};



    enum blocktype top_blk = get_block(map, top);
    enum blocktype right_blk = get_block(map, right);
    enum blocktype down_blk = get_block(map, down);
    enum blocktype left_blk = get_block(map, left);

    if(top_blk == BLOCK || top_blk == DBLOCK)
        res += COL_UP;
    if(right_blk == BLOCK || right_blk == DBLOCK)
        res += COL_RIGHT;
    if(down_blk == BLOCK || down_blk == DBLOCK)
        res += COL_DOWN;
    if(left_blk == BLOCK || left_blk == DBLOCK)
        res += COL_LEFT;

    return res;
}


void collision_enemy(struct entity *entity, struct map *map)
{
    int collider = entity_collide(entity, map);


    if (collider & COL_DOWN)
    {
        entity->acc.y = 0;
        entity->spd.y = 0;
        entity->pos.y = fti(entity->pos.y);
    }
}

void collision(struct entity *entity, struct map *map)
{
    int collider = entity_collide(entity, map);

    if (collider & COL_LEFT)
    {
        entity->acc.x = fmax(entity->acc.x, 0);
        entity->spd.x = fmax(entity->spd.x, 0);
        entity->pos.x = fti(entity->pos.x) + 1;
    }
    if (collider & COL_DOWN)
    {
        entity->acc.y = 0;
        entity->spd.y = 0;
        entity->pos.y = fti(entity->pos.y);
    }
    if (collider & COL_RIGHT)
    {
        entity->acc.x = fmin(entity->acc.x, 0);
        entity->spd.x = fmin(entity->spd.x, 0);
        entity->pos.x = fti(entity->pos.x);
    }

    if (collider & COL_UP)
    {
        entity->spd.y = 0;
        entity->pos.y = fti(entity->pos.y) + 1;
    }
}

void apply_gravity(struct entity *entity, float delta)
{
    struct vector2 gravity =
    {
        0,
        GRAVITY_FORCE
    };
    entity->acc = add_vect(entity->acc, scale_vect(delta, gravity));
}

int is_on_floor(struct entity *entity, struct map *map)
{
    return entity_collide(entity, map) & COL_DOWN;
}

void jump(struct entity *entity, float delta)
{
    struct vector2 jump =
    {
        0,
        -JUMP_FORCE
    };
    //entity->spd = scale_vect(delta, jump);
    entity->spd = add_vect(entity->spd, scale_vect(delta, jump));

}

void add_entity(struct map *map, struct entity entity)
{
    map->entities = realloc(map->entities, sizeof(struct entity)
            * (map->nbentities + 1));
    map->entities[map->nbentities++] = entity;
}

void delete_entity(struct map *map, int i)
{

    for(; i < map->nbentities - 1; i++)
        map->entities[i] = map->entities[i+1];

    map->nbentities--;
    map->entities = realloc(map->entities, sizeof(struct entity)
            * map->nbentities);
}

void update_direction(struct entity *entity)
{
    if(entity->spd.x < 0)
        entity->dir = DIR_LEFT;
    if(entity->spd.x > 0)
        entity->dir = DIR_RIGHT;
}

int is_outside_map(struct entity entity, int map_width, int map_height)
{
    float x = entity.pos.x;
    float y = entity.pos.y;
    if(x < 0 || y < 0)
        return 1;
    if(x + 0.5 >= map_width || y + 0.5 >= map_height)
        return 1;
    return 0;
}
