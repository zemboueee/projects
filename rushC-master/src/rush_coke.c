#include <stdio.h>

#include "structs.h"
#include "display.h"
#include "game.h"
#include "input.h"
#include "entity.h"
#include "map.h"
#include "update.h"

int main(void)
{
    struct GameContext *game = init_game();
    struct map *map = game->map;
    struct display *display = init_display(map->width, map->height);

    load_textures(display, map->texture_path);


    struct input input;
    display_menu(display->renderer);

    while(1)
    {
        input = get_inputs();
        if(input.inputs[SPACE])
            break;
        if(input.inputs[QUIT])
            exit(0);
    }

    while (game->is_playing == 1)
    {
        SDL_RenderClear(display->renderer);
        //INPUT
        input = get_inputs();
        if (input.inputs[QUIT])
            exit(0);

        //UPDATE
        if(is_outside_map(map->player, map->width, map->height))
        {

            if (game->cur_map + 1 == game->nb_maps)
            {
                game->is_playing = 3;
                break;
            }

            go_next_map(game);

            map = game->map;
            load_textures(display, map->texture_path);
        }

        update_frame(map);
        update_map_entities(map);
        update_player(&map->player, map, input);
        game->is_playing = get_gamestate();

        //DRAW
        display_map(display, map);
        display_life(display);

        SDL_RenderPresent(display->renderer);
        SDL_Delay(20);
    }

    if(game->is_playing == 2)
    {
        display_gameover(display->renderer);
    }

    if(game->is_playing == 3)
    {
        display_finish(display->renderer);
    }

    while(1)
    {
        input = get_inputs();
        if(input.inputs[QUIT])
            break;
        SDL_Delay(20);
    }
    //free
    //free game
    free(game);
    //free display
    //TODO

    return 0;
}
