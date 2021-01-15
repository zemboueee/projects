#ifndef GAME_H_
#define GAME_H_

#include "structs.h"

struct GameContext *init_game();
void update_frame(struct map *map);
void go_next_map(struct GameContext *game);

#endif /* !GAME_H_ */
