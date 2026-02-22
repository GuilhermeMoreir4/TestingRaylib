#include "player.h"

#include "raylib.h"

#include <stdlib.h>


#define PLAYER_VELOCITY 200
#define SPRITE_SIZE 48

static Texture2D texture;

Player create_player(const char* texture_path, int pos_x,int pos_y){
	Animation* animation = malloc(4 * sizeof(Animation));
	texture = LoadTexture(texture_path);

	animation[BACKWARD] = new_animation(1,4,1,SPRITE_SIZE);
	animation[FORWARD] = new_animation(2,4,1,SPRITE_SIZE);
	animation[LEFT]= new_animation(3,4,1,SPRITE_SIZE);
	animation[RIGHT] = new_animation(4,4,1,SPRITE_SIZE);

	Rectangle texutre_source = {0,0, SPRITE_SIZE ,SPRITE_SIZE};

	return (Player){
		 .object = create_object(
                    (KGTransform){
                        .position= (Vector2){.x=pos_x,.y=pos_y},
                        .scale=    (Vector2){.x=4 * SPRITE_SIZE,.y=4 * SPRITE_SIZE},
                        .rotation= (Vector2){.x=0,.y=0}
                    },
                    (Drawable){
                        .source= texutre_source,
                        .sprite_sheet= texture
                    }
                ),
		.animations= animation
	};
}

void destroy_player(Player* player){
	UnloadTexture(player->object->drawable.sprite_sheet);
	free(player->animations);
	free(player);
}




void handle_player_movement(Player* player,float delta_time){

		if (IsKeyDown(KEY_A)){
			player->object->transform.position.x += PLAYER_VELOCITY * delta_time;
			play_animation(&player->animations[LEFT],&player->object->drawable.source,delta_time);
		}

		if (IsKeyDown(KEY_D)){
			player->object->transform.position.x -= PLAYER_VELOCITY * delta_time;
			play_animation(&player->animations[RIGHT],&player->object->drawable.source,delta_time);
		}

		if (IsKeyDown(KEY_W)){
			player->object->transform.position.y += PLAYER_VELOCITY * delta_time;
			play_animation(&player->animations[FORWARD],&player->object->drawable.source,delta_time);
		}

		if (IsKeyDown(KEY_S)){
			player->object->transform.position.y -= PLAYER_VELOCITY * delta_time;
			play_animation(&player->animations[BACKWARD],&player->object->drawable.source,delta_time);
		}

		if(IsKeyReleased(KEY_S)){
		 pause_animation(&player->animations[BACKWARD],&player->object->drawable.source);
		}

		if(IsKeyReleased(KEY_W)){
		 pause_animation(&player->animations[FORWARD],&player->object->drawable.source);
		}

		if(IsKeyReleased(KEY_D)){
		 pause_animation(&player->animations[RIGHT],&player->object->drawable.source);
		}

		if(IsKeyReleased(KEY_A)){
		 pause_animation(&player->animations[LEFT],&player->object->drawable.source);
		}
}
