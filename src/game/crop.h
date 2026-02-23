#ifndef CROP_H
#define CROP_H

#include "core/object.h"

typedef enum{
    WHEAT = 1,
    BEET = 2

}CropType;

typedef struct
{
    Object* object;
    float growth_time;
    float elapsed_growth_time;
}Crop;

Crop create_crop(CropType type,float position_x, float position_y);

void update(Crop* crop,float delta_time);

#endif