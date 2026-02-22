#include "object.h"
#include <stdlib.h>

Object* create_object(KGTransform transform,Drawable drawable){
    Object* object = malloc(sizeof(Object));
	if(!object) return NULL;

    object->drawable = drawable;
    object->transform = transform;

	return object;
};

void destroy_object(Object* object){
    free(object);
}