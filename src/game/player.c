#include "raylib.h"
#include "core/animation_system.h"
#include <stdlib.h>
#include "player.h"

#define PLAYER_VELOCITY 200
#define SPRITE_SIZE 48



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


	my_player->animations[BACKWARD] = *new_animation(1,4,1,SPRITE_SIZE);
	my_player->animations[FORWARD] = *new_animation(2,4,1,SPRITE_SIZE);
	my_player->animations[LEFT]= *new_animation(3,4,1,SPRITE_SIZE);
	my_player->animations[RIGHT] = *new_animation(4,4,1,SPRITE_SIZE);

	return my_player;
}

void destroy_player(Player* player){
	UnloadTexture(player->texture.sprite_sheet);
	free(player->animations);
	free(player);
}




void handle_player_movement(Player* player){
		float delta_time = GetFrameTime();

		if (IsKeyDown(KEY_A)){
			player->position.x += PLAYER_VELOCITY * delta_time;
			play_animation(&player->animations[LEFT],&player->texture.rectangle,&delta_time);
		}

		if (IsKeyDown(KEY_D)){
			player->position.x -= PLAYER_VELOCITY * delta_time;
			play_animation(&player->animations[RIGHT],&player->texture.rectangle,&delta_time);
		}

		if (IsKeyDown(KEY_W)){
			player->position.y += PLAYER_VELOCITY * delta_time;
			play_animation(&player->animations[FORWARD],&player->texture.rectangle,&delta_time);
		}

		if (IsKeyDown(KEY_S)){
			player->position.y -= PLAYER_VELOCITY * delta_time;
			play_animation(&player->animations[BACKWARD],&player->texture.rectangle,&delta_time);
		}

		if(IsKeyReleased(KEY_S)){
		 pause_animation(&player->animations[BACKWARD],&player->texture.rectangle);
		}

		if(IsKeyReleased(KEY_W)){
		 pause_animation(&player->animations[FORWARD],&player->texture.rectangle);
		}

		if(IsKeyReleased(KEY_D)){
		 pause_animation(&player->animations[RIGHT],&player->texture.rectangle);
		}

		if(IsKeyReleased(KEY_A)){
		 pause_animation(&player->animations[LEFT],&player->texture.rectangle);
		}
}
