#ifndef OBJECT_H
#define OBJECT_H

#include"raylib.h"
#include "core/render/drawable.h"
#include "core/transform/kg_transform.h"


typedef struct{
    KGTransform transform;
	Drawable drawable;
}Object;

Object* create_object(KGTransform transform,Drawable drawable);

void destroy_object(Object* object);
#endif