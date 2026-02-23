#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include <stdio.h>
#include <stdlib.h>

#include "drawable.h"
#include "core/transform/kg_transform.h"


typedef struct{
    Drawable* drawable;
    KGTransform* transform;
    int layer;
}QueueElement;


void begin_frame();

void submit(Drawable* drawable,KGTransform* transform,int layer);

void flush();

#endif