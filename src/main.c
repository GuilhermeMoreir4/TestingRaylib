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
	Rectangle size;
}PlayerTexture;

typedef enum PlayerDirection{
	BACKWARD = 0,
	FORWARD= 1,
	LEFT = 2,
	RIGHT = 3
}PlayerDirection;

typedef struct Animation{
	int sprite_line;
	int frames;
	int current_frame;
	int sprite_size; 
	float animation_duration;
	float elapsed_time;
}Animation;

Animation* new_animation(int sprite_line,int frames,float animation_duration, int sprite_size){
	Animation* animation = malloc(sizeof(Animation));
	animation->animation_duration = animation_duration;
	animation->elapsed_time = 0;
	animation->frames = frames - 1;
	animation->sprite_line = sprite_line - 1;
	animation->sprite_size = sprite_size;
	animation->current_frame = 0;
	return animation;
}

typedef struct Player {
	Vector2 position;
	PlayerTexture texture;
	Animation* animations;
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
	Rectangle size = {0,0, SPRITE_SIZE * 4,SPRITE_SIZE * 4};
	my_player->texture.size = size;
	
	my_player->animations = malloc(4*sizeof(Animation));


	my_player->animations[0] = *new_animation(1,4,1,SPRITE_SIZE);
	my_player->animations[1] = *new_animation(2,4,1,SPRITE_SIZE);
	my_player->animations[2]= *new_animation(3,4,1,SPRITE_SIZE);
	my_player->animations[3] = *new_animation(4,4,1,SPRITE_SIZE);

	return my_player;
}

void destroy_player(Player* player){
	UnloadTexture(player->texture.sprite_sheet);
	free(player);
}



void play_animation(Animation* animation,Rectangle* rectangle,float* delta_time){
	rectangle->y = animation->sprite_line * animation->sprite_size;

	if(animation->current_frame < animation->frames){
		if (animation->elapsed_time > animation->animation_duration){
			animation->current_frame ++;
			rectangle->x += animation->sprite_size;
			animation->elapsed_time = 0;
		}else{
			animation->elapsed_time += *delta_time;
		}
	}else{
		animation->current_frame = 0;
		rectangle->x = 0;
	}
};

void pause_animation(Animation* animation,Rectangle* rectangle){
	rectangle->y = animation->sprite_line;
	rectangle->x = 0;
}


void handle_player_movement(Player* player){
		float delta_time = GetFrameTime();

		if (IsKeyDown(KEY_A)){
			player->position.x += PLAYER_VELOCITY * delta_time;
			play_animation(&player->animations[2],&player->texture.rectangle,&delta_time);
		}

		if (IsKeyDown(KEY_D)){
			player->position.x -= PLAYER_VELOCITY * delta_time;
			play_animation(&player->animations[3],&player->texture.rectangle,&delta_time);
		}

		if (IsKeyDown(KEY_W)){
			player->position.y += PLAYER_VELOCITY * delta_time;
			play_animation(&player->animations[1],&player->texture.rectangle,&delta_time);
		}

		if (IsKeyDown(KEY_S)){
			player->position.y -= PLAYER_VELOCITY * delta_time;
			play_animation(&player->animations[0],&player->texture.rectangle,&delta_time);
		}

		if(IsKeyReleased(KEY_S)){
		 pause_animation(&player->animations[0],&player->texture.rectangle);
		}
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
		BeginDrawing();
		ClearBackground(BLACK);

		DrawText("Hello Raylib", 200,200,20,WHITE);
		draw_money("R$ + 250");
		
		DrawTexturePro(player->texture.sprite_sheet, player->texture.rectangle,player->texture.size,player->position,0,WHITE);
		
		EndDrawing();
	}

	destroy_player(player);
	CloseWindow();
	return 0;
}
