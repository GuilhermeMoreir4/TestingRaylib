#ifndef COLLISSION_SYSTEM_H
#define COLLISION_SYSTEM_H

#include "kg_colission.h"

bool check_collision(KGCollidable* source,KGCollidable* target);
void send_to_collision_queue(KGCollidable* collider, void (*callback)());
void handle_all_collisions();
void init_collision_system();

#endif