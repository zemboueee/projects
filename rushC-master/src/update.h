#ifndef UPDATE_H_
#define UPDATE_H_
#include "structs.h"


void display_life(struct display *display);
void update_player(struct entity *player, struct map *map, struct input input);
void update_map_entities(struct map *map);
int get_gamestate();

#endif /* !UPDATE_H_ */
