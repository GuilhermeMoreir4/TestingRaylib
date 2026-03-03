#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"

#include "resource_dir.h"

#include "game/player.h"

#include "core/render/render_system.h"

#include "game_config.h"

#include "game/crop.h"


#include "core/colission/colission_system.h"

void draw_money(const char* ptr){
	DrawText(ptr, WINDOW_WIDTH - 100, 10,20,WHITE);
};


void draw_collider_box(KGCollidable* collidable,Color color){
	DrawRectangleLines(collidable->x,collidable->y,collidable->width,collidable->height,color);
};


void player_collision_func(){
	printf("INFO: PLAYER HAS COLLIDED");
};

void crop_collision_func(){
	printf("INFO: CROP HAS COLLIDED");
};

int main ()
{
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello Raylib");

	SearchAndSetResourceDir("resources");

	float elepased_frames = 0;
	
	Crop wheat = create_crop(WHEAT,100, WINDOW_HEIGHT/2);
	// Crop wheat_2 = create_crop(WHEAT,-130,-40);
	
	Player player = create_player("character/basic_move_sprite_sheet.png",100, WINDOW_HEIGHT/2);

	printf("Transform:{%d,%d}", player.object->transform.position.x, player.object->transform.position.y);

	Crop beet = create_crop(BEET, 140,-100);
	

	while (!WindowShouldClose()){
		float delta_time = GetFrameTime();

		handle_player_movement(&player,delta_time);
		BeginDrawing();
		ClearBackground((Color){ 164, 194, 99, 255 });
		
		init_collision_system();
		send_to_collision_queue(&player.collider,player_collision_func);
		send_to_collision_queue(&wheat.collider,crop_collision_func);

		handle_all_collisions();


		begin_frame();

		submit(&wheat.object->drawable,&wheat.object->transform,1);
		// submit(&wheat_2.object->drawable,&wheat_2.object->transform,1);


		// submit(beet.object->drawable);

		submit(&player.object->drawable,&player.object->transform,0);
		

		DrawText("Hello Raylib", 200,200,20,WHITE);
		DrawText(TextFormat("x: %f, y: %f",player.object->transform.position.x, player.object->transform.position.y), WINDOW_WIDTH - 500, 10,20,WHITE);
		
		
		
		draw_money("R$ + 250");
		
		flush();

		draw_collider_box(&player.collider,(Color){ 34, 100, 34, 255 });
		draw_collider_box(&wheat.collider,(Color){ 34, 100, 34, 255 });

		EndDrawing();
	}

	destroy_player(&player);
	CloseWindow();
	return 0;
}
