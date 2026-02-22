#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "raylib.h"
// that struct going to describe how the object can be drawed, using the Rectangle for the sprite_sheet

typedef struct{
    Rectangle source;
	Texture2D sprite_sheet;
}Drawable;

#endif