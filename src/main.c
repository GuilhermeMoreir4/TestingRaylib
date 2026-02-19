/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"

#include "resource_dir.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define PLAYER_VELOCITY 200

#define SPRITE_SIZE 48

void draw_money(const char* ptr){
	DrawText(ptr, WINDOW_WIDTH - 100, 10,20,WHITE);
};

typedef struct PlayerTexture{
	Rectangle rectangle;
	Texture2D sprite_sheet;
}PlayerTexture;

typedef enum PlayerDirection{
	BACKWARD = 0,
	FORWARD= 1,
	LEFT = 2,
	RIGHT = 3
}PlayerDirection;

typedef struct PlayerAnimation{
	bool is_moving;
	PlayerDirection direction; 
	float animation_duration;
	float elapsed_time;
}PlayerAnimation;

typedef struct Player {
	Vector2 position;
	PlayerTexture texture;
	PlayerAnimation animation;
} Player;

Player* create_player(const char* texture_path, int pos_x,int pos_y){
	Player* my_player = malloc(sizeof(Player));
	int frame = 1;
	int* frame_ptr = &frame;

	if(!my_player)return NULL;
	

	Rectangle player_texture_rec = {0,0, SPRITE_SIZE ,SPRITE_SIZE};

	my_player->position.x = pos_x;
	my_player->position.y = pos_y;
	my_player->texture.sprite_sheet = LoadTexture(texture_path);
	my_player->texture.rectangle = player_texture_rec;
	my_player->animation.elapsed_time = 0;
	my_player->animation.animation_duration = .5;

	return my_player;
}

void destroy_player(Player* player){
	UnloadTexture(player->texture.sprite_sheet);
	free(player);
}

void handle_player_movement(Player* player){
		float delta_time = GetFrameTime();

		if (IsKeyDown(KEY_A)){
			player->position.x += PLAYER_VELOCITY * delta_time;

			player->animation.is_moving = true;
			player->animation.direction = LEFT;
			return;
		}

		if (IsKeyDown(KEY_D)){
			player->position.x -= PLAYER_VELOCITY * delta_time;

			player->animation.is_moving = true;
			player->animation.direction = RIGHT;
			return;
		}

		if (IsKeyDown(KEY_W)){
			player->position.y += PLAYER_VELOCITY * delta_time;

			player->animation.is_moving = true;
			player->animation.direction = FORWARD;
			return;

		}

		if (IsKeyDown(KEY_S)){
			player->position.y -= PLAYER_VELOCITY * delta_time;

			player->animation.is_moving = true;
			player->animation.direction = BACKWARD;
			return;

		}

		player->animation.is_moving = false;	
}


void animate_player_movement(Player* player){
	if(player->animation.is_moving){
		float time = GetFrameTime();
		player->texture.rectangle.y = SPRITE_SIZE * player->animation.direction;

		if(player->texture.rectangle.x < SPRITE_SIZE * 3){
			if (player->animation.elapsed_time > player->animation.animation_duration){
				player->texture.rectangle.x += SPRITE_SIZE;
				player->animation.elapsed_time = 0;
			}else{
				player->animation.elapsed_time += time;
			}
		}else{
			player->texture.rectangle.x = 0;
		}
		return;
	}
	player->texture.rectangle.y = SPRITE_SIZE * player->animation.direction;
	player->texture.rectangle.x = 0;
}

int main ()
{
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello Raylib");

	SearchAndSetResourceDir("resources");
	Player* player = create_player("character/basic_move_sprite_sheet.png",32,32);

	float elepased_frames = 0;
	
	while (!WindowShouldClose())			{
		handle_player_movement(player);
		animate_player_movement(player);
		BeginDrawing();

		ClearBackground(BLACK);

		DrawText("Hello Raylib", 200,200,20,WHITE);
		draw_money("R$ + 250");
		Rectangle size = {0,0, SPRITE_SIZE * 4,SPRITE_SIZE * 4};
		DrawTexturePro(player->texture.sprite_sheet, player->texture.rectangle,size,player->position,0,WHITE);
		
		EndDrawing();
	}

	destroy_player(player);
	CloseWindow();
	return 0;
}
