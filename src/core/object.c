#include "object.h"
#include <stdlib.h>
#include <stdio.h>

Object* create_object(KGTransform transform,Drawable drawable){
    Object* object = malloc(sizeof(Object));
	if(object == NULL){
        printf("Allocation error");
        exit(1);
    };

    object->drawable = drawable;
    object->transform = transform;

	return object;
};

void destroy_object(Object* object){
    free(object);
}