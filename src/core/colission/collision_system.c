#include "core/colission/colission_system.h"
#include <stdio.h>
#include "game_config.h"


void check_collision(KGCollidable* source,KGCollidable* target){
  
    // printf("Collidable1:{x: %f, y: %f, width: %d, height: %d}, Collidable2:{x: %f, y: %f, width: %d, height: %d}",source->x,source->y, source->width, source->height, target->x,target->y, target->width, target->height);
  
    if( 
        (source->x < target->x + target->width) &&
        (source->x + source->width > target->x) &&
        (source->y < target->y + target->height) &&
        (source->y + source->height > target->y) 
     ){
      DrawText("COLIDING", WINDOW_WIDTH/2 - 500, 10,20,WHITE);
      return;
   }
      DrawText("NOT COLIDING", WINDOW_WIDTH/2 - 500, 10,20,WHITE);

}