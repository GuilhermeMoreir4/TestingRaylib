#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "core/animation/animation_system.h"
#include <stdlib.h>
#include "core/object.h"
#include "core/render/drawable.h"
#include "core/transform/kg_transform.h"

typedef struct PlayerTexture{
	Rectangle rectangle;
	Texture2D sprite_sheet;
	Rectangle size;
}PlayerTexture;

typedef enum PlayerDirection{
	BACKWARD = 0,
	FORWARD= 1,
	LEFT = 2,
	RIGHT = 3
}PlayerDirection;


typedef struct Player {
	Object* object;
	Animation* animations;
} Player;

void handle_player_movement(Player* player,float delta_time);

Player create_player(const char* texture_path, int pos_x,int pos_y);

void destroy_player(Player* player);
#endif