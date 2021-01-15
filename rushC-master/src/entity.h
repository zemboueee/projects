#ifndef ENTITY_H_
#define ENTITY_H_

#define GRAVITY_FORCE 0.0025
#define JUMP_FORCE 0.25


#include "structs.h"


void update_entity(struct entity *entity, float delta);
int entities_contact(struct entity *ent1, struct entity *ent2);
void collision(struct entity *entity, struct map *map);
void collision_enemy(struct entity *entity, struct map *map);
void apply_gravity(struct entity *entity, float delta);
int is_on_floor(struct entity *entity, struct map *map);

void jump(struct entity *entity, float delta);
void add_entity(struct map *map, struct entity entity);
void update_direction(struct entity *entity);
void delete_entity(struct map *map, int i);
int is_outside_map(struct entity entity, int map_width, int map_height);

#endif /* !ENTITY_H_ */
