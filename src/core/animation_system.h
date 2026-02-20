#ifndef ANIMATION_SYSTEM_H
#define ANIMATION_SYSTEM_H

typedef struct Animation{
	int sprite_line;
	int frames;
	int current_frame;
	int sprite_size; 
	float animation_duration;
	float elapsed_time;
}Animation;

Animation* new_animation(int sprite_line,int frames,float animation_duration, int sprite_size);

void pause_animation(Animation* animation,Rectangle* rectangle);

void play_animation(Animation* animation,Rectangle* rectangle,float* delta_time);

#endif