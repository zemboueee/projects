#include "structs.h"
#include "entity.h"
#include "map.h"

struct GameContext *init_game()
{
    struct GameContext *game = malloc(sizeof(struct GameContext));

    char *maps[] =
    {
        "maps/lvl0.ez",
        "maps/lvl1.ez",
        "maps/lvl2.ez",
        "maps/lvl3.ez",
        "maps/lvl4.ez",
        "maps/lvl5.ez",
        "maps/lvl6.ez",
        "maps/lvl8.ez",
        "maps/lvl7.ez"
    };

    char *textures[] =
    {
        "maps/lvl0_textures/",
        "maps/lvl1_textures/",
        "maps/lvl2_textures/",
        "maps/lvl3_textures/",
        "maps/lvl4_textures/",
        "maps/lvl5_textures/",
        "maps/lvl6_textures/",
        "maps/lvl8_textures/",
        "maps/lvl7_textures/"
    };

    game->cur_map = 0;
    game->nb_maps = 9;
    game->maps = parse_maps(maps, game->nb_maps, textures);
    game->map = game->maps[game->cur_map];
    game->is_playing = 1;

    return game;
}

void update_frame(struct map *map)
{


    for(int entity_i = 0; entity_i < map->nbentities; entity_i++)
    {
        if(map->entities[entity_i].type == ENEMY)
        {
            apply_gravity(&map->entities[entity_i], 1);
            update_entity(&map->entities[entity_i], 1);
            collision_enemy(&map->entities[entity_i], map);
        }
        else
        {
            update_entity(&map->entities[entity_i], 1);
        }

        if(is_outside_map(map->entities[entity_i], map->width, map->height))
            delete_entity(map, entity_i);
    }
}

void go_next_map(struct GameContext *game)
{
    game->map = game->maps[++game->cur_map];
}
