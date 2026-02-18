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
#define PLAYER_VELOCITY 2

void draw_money(const char* ptr){
	DrawText(ptr, WINDOW_WIDTH - 100, 10,20,WHITE);
};

typedef struct player {
	int pos_x;
	int pos_y;
	Texture texture;

} Player;

Player* create_player(const char* texture_path, int pos_x,int pos_y){
	Player* my_player = malloc(sizeof(Player));

	if(!my_player )return NULL;

	my_player->pos_x = pos_x;
	my_player->pos_y = pos_y;
	my_player->texture = LoadTexture(texture_path);


	return my_player;
}

void destroy_player(Player* player){
	UnloadTexture(player->texture);
	free(player);
}

void handle_player_movement(Player* player){
		if (IsKeyDown(KEY_A)){
			player->pos_x -= PLAYER_VELOCITY;
		}

		if (IsKeyDown(KEY_D)){
			player->pos_x += PLAYER_VELOCITY;
		}

		if (IsKeyDown(KEY_W)){
			player->pos_y -= PLAYER_VELOCITY;
		}
		if (IsKeyDown(KEY_S)){
			player->pos_y += PLAYER_VELOCITY;
		}
}

int main ()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello Raylib");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");
	Player* player = create_player("wabbit_alpha.png",20,20);

	// Load a texture from the resources directory

	// game loop
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);

		// draw some text using the default font
		DrawText("Hello Raylib", 200,200,20,WHITE);
		draw_money("R$ + 250");
		// draw our texture to the screen
		handle_player_movement(player);
		DrawTexture(player->texture, player->pos_x, player->pos_y, WHITE);
		
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up
	destroy_player(player);

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
