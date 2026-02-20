#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "core/animation_system.h"
#include <stdlib.h>


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
	Vector2 position;
	PlayerTexture texture;
	Animation* animations;
} Player;

void handle_player_movement(Player* player);

Player* create_player(const char* texture_path, int pos_x,int pos_y);

void destroy_player(Player* player);
#endif