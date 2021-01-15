#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "structs.h"
#include "display.h"

struct display *init_display(int width, int height)
{
    struct display *display = malloc(sizeof(struct display));

    display->window = SDL_CreateWindow("Rush Coke", SDL_WINDOWPOS_UNDEFINED
            , SDL_WINDOWPOS_UNDEFINED, width * BLOCK_SIZE
            , height * BLOCK_SIZE, SDL_WINDOW_SHOWN);
    display->renderer = SDL_CreateRenderer(display->window, -1
            , SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    display->blk_textures = NULL;
    display->ent_textures = NULL;
    return display;
}

void end_display(struct display *display)
{
    SDL_DestroyWindow(display->window);
    SDL_DestroyRenderer(display->renderer);
}


void display_blk(struct display *display, enum blocktype blocktype
        , int x, int y)
{

    SDL_Texture *texture = display->blk_textures[blocktype];
    SDL_Renderer *renderer = display->renderer;

    SDL_Rect texr =
    {
        .x = x,
        .y = y,
        .w = BLOCK_SIZE,
        .h = BLOCK_SIZE,
    };

    SDL_QueryTexture(texture, NULL, NULL, &x, &y);
    SDL_RenderCopy(renderer, texture, NULL, &texr);
}


void display_entity(struct display *display, struct entity entity)
{

    SDL_Texture *texture = display->ent_textures[entity.type];
    SDL_Renderer *renderer = display->renderer;

    float fposx =  entity.pos.x * BLOCK_SIZE;
    float fposy =  entity.pos.y * BLOCK_SIZE;
    int posx = fposx;
    int posy = fposy;
    SDL_Rect texr =
    {
        .x = posx,
        .y = posy,
        .w = BLOCK_SIZE,
        .h = BLOCK_SIZE,
    };

    SDL_QueryTexture(texture, NULL, NULL, &posx, &posy);
    SDL_RenderCopy(renderer, texture, NULL, &texr);
}


void load_blk_texture(struct display *display, enum blocktype blk_type
        , char *textures_path)
{
    char buffer[4096];
    strcpy(buffer, textures_path);

    switch (blk_type) {
        case BLOCK:
            strcat(buffer, "block.png");
            break;
        case AIR:
            return;
        case SPIKE:
            strcat(buffer, "spike.png");
            break;
        case DBLOCK:
            strcat(buffer, "destructible_block.png");
            break;
    }

    display->blk_textures[blk_type]
        = IMG_LoadTexture(display->renderer, buffer);
}

void load_ent_texture(struct display *display, enum entitytype ent_type
        , char *textures_path)
{
    char buffer[4096];
    strcpy(buffer, textures_path);

    switch (ent_type) {
        case PLAYER:
            strcat(buffer, "player.png");
            break;
        case ENEMY:
            strcat(buffer, "enemy.png");
            break;
        case BULLET:
            strcat(buffer, "bullet.png");
            break;
        case GUN_PICKUP:
            strcat(buffer, "gun_pickup.png");
            break;
        case DOUBLE_JUMP_PICKUP:
            strcat(buffer, "double_jump_pickup.png");
            break;
        case COKE:
            strcat(buffer, "coke.png");
            break;
    }

    display->ent_textures[ent_type]
        = IMG_LoadTexture(display->renderer, buffer);
}

void load_background(struct display *display, char *textures_path)
{
    char buffer[4096];
    strcpy(buffer, textures_path);
    strcat(buffer, "background.png");
    display->background = IMG_LoadTexture(display->renderer, buffer);
}

void load_textures(struct display *display, char *textures_path)
{
    display->blk_textures = malloc(sizeof(SDL_Texture*) * NB_BLK_TYPES);
    display->ent_textures = malloc(sizeof(SDL_Texture*) * NB_ENT_TYPES);

    load_background(display, textures_path);

    load_blk_texture(display, BLOCK, textures_path);
    load_blk_texture(display, SPIKE, textures_path);
    load_blk_texture(display, DBLOCK, textures_path);

    load_ent_texture(display, PLAYER, textures_path);
    load_ent_texture(display, ENEMY, textures_path);
    load_ent_texture(display, BULLET, textures_path);
    load_ent_texture(display, GUN_PICKUP, textures_path);
    load_ent_texture(display, DOUBLE_JUMP_PICKUP, textures_path);
    load_ent_texture(display, COKE, textures_path);

    return;
}

void display_background(SDL_Renderer *renderer, SDL_Texture *background
        , int width, int height)
{

    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            int posx = x * BLOCK_SIZE;
            int posy = y * BLOCK_SIZE;
            SDL_Rect texr =
            {
                .x = posx,
                .y = posy,
                .w = BLOCK_SIZE,
                .h = BLOCK_SIZE
            };


            SDL_QueryTexture(background, NULL, NULL, &posx, &posy);
            SDL_RenderCopy(renderer, background, NULL, &texr);
        }
    }
}
void display_life_bar(SDL_Renderer *renderer, int life, int life_max)
{
    SDL_Texture *hearth_full = IMG_LoadTexture(renderer
            , "textures/hearth_full.png");
    SDL_Texture *hearth_empty = IMG_LoadTexture(renderer
            , "textures/hearth_empty.png");
    int i = 0;
    for(; i < life; i++)
    {
        int posx = i * BLOCK_SIZE;
        int posy = 0;
        SDL_Rect texr =
        {
            .x = posx, .y = posy, .w = BLOCK_SIZE, .h = BLOCK_SIZE
        };

        SDL_QueryTexture(hearth_full, NULL, NULL, &posx, &posy);
        SDL_RenderCopy(renderer, hearth_full, NULL, &texr);
    }

    for(; i < life_max; i++)
    {
        int posx = i * BLOCK_SIZE;
        int posy = 0;
        SDL_Rect texr =
        {
            .x = posx, .y = posy, .w = BLOCK_SIZE, .h = BLOCK_SIZE
        };

        SDL_QueryTexture(hearth_empty, NULL, NULL, &posx, &posy);
        SDL_RenderCopy(renderer, hearth_empty, NULL, &texr);
    }


}

void display_menu(SDL_Renderer *renderer)
{
    SDL_Texture *menu = IMG_LoadTexture(renderer, "textures/menu.png");

    SDL_RenderClear(renderer);

    int posx = 0;
    int posy = 0;
    SDL_Rect texr =
    {
        .x = posx,
        .y = posy,
        .w = 768,
        .h = 512
    };


    SDL_QueryTexture(menu, NULL, NULL, &posx, &posy);
    SDL_RenderCopy(renderer, menu, NULL, &texr);
    SDL_RenderPresent(renderer);
}

void display_gameover(SDL_Renderer *renderer)
{
    SDL_Texture *gameover = IMG_LoadTexture(renderer, "textures/gameover.png");

    SDL_RenderClear(renderer);

    int posx = 0;
    int posy = 0;
    SDL_Rect texr =
    {
        .x = posx,
        .y = posy,
        .w = 768,
        .h = 512
    };


    SDL_QueryTexture(gameover, NULL, NULL, &posx, &posy);
    SDL_RenderCopy(renderer, gameover, NULL, &texr);
    SDL_RenderPresent(renderer);
}

void display_finish(SDL_Renderer *renderer)
{
    SDL_Texture *finish = IMG_LoadTexture(renderer, "textures/finish.png");

    SDL_RenderClear(renderer);

    int posx = 0;
    int posy = 0;
    SDL_Rect texr =
    {
        .x = posx,
        .y = posy,
        .w = 768,
        .h = 512
    };


    SDL_QueryTexture(finish, NULL, NULL, &posx, &posy);
    SDL_RenderCopy(renderer, finish, NULL, &texr);
    SDL_RenderPresent(renderer);
}


void display_map(struct display *display, struct map *map)
{
    display_background(display->renderer, display->background
            , map->width, map->height);

    for(int entity_i = 0; entity_i < map->nbentities; entity_i++)
    {
        struct entity entity = map->entities[entity_i];
        display_entity(display, entity);
    }

    for(int y = 0; y < map->height; y++)
    {
        for(int x = 0; x < map->width; x++)
        {
            enum blocktype blocktype = map->block[y * map->width + x];
            display_blk(display, blocktype, x * BLOCK_SIZE, y * BLOCK_SIZE);
        }
    }


    display_entity(display, map->player);
}
