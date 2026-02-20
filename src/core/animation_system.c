#include <stdlib.h>
#include "raylib.h"
#include "animation_system.h"

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
	rectangle->y = animation->sprite_line * animation->sprite_size;
	rectangle->x = 0;
}
