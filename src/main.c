#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"

#include "resource_dir.h"

#include "core/animation_system.h"
#include "game/player.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720



void draw_money(const char* ptr){
	DrawText(ptr, WINDOW_WIDTH - 100, 10,20,WHITE);
};

int main ()
{
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello Raylib");

	SearchAndSetResourceDir("resources");
	Player* player = create_player("character/basic_move_sprite_sheet.png",32,32);

	float elepased_frames = 0;
	
	while (!WindowShouldClose()){
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
