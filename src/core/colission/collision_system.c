#include "core/colission/colission_system.h"
#include <stdio.h>
#include "game_config.h"
#include <stdio.h>
#include "core/colission/kg_colission.h"

#define MAX_COLLIDABLE_RANGE 100

typedef struct{
   KGCollidable* collidable;
   void (*callback)();
}CollisionEvent;

typedef struct 
{
   CollisionEvent queue[MAX_COLLIDABLE_RANGE];
   int count;
}CollisionQueue;

static CollisionQueue collisionQueue;

void init_collision_system(){
    collisionQueue.count = 0;
}

void send_to_collision_queue(KGCollidable* collider, void (*callback)()){
   if(collisionQueue.count >= MAX_COLLIDABLE_RANGE){
      printf("COLLISION QUEUE IS FULL");
      return;
   }

   CollisionEvent event;
   event.collidable = collider;
   event.callback = callback;

   collisionQueue.queue[collisionQueue.count] = event;
   collisionQueue.count++;
}

void handle_all_collisions(){
   if(collisionQueue.count < 2){
      return;
   }

   for(int i = 0; i < collisionQueue.count -1; i++){
      for(int j = i + 1; j <= collisionQueue.count -1; j ++){
         if(check_collision(collisionQueue.queue[i].collidable,collisionQueue.queue[j].collidable)){
            printf("INFO: calling the callback funcs");
            collisionQueue.queue[i].callback();
            collisionQueue.queue[j].callback();
         }
      }
   }

   collisionQueue.count = 0;
}

bool check_collision(KGCollidable* source,KGCollidable* target){
    if( 
        (source->x < target->x + target->width) &&
        (source->x + source->width > target->x) &&
        (source->y < target->y + target->height) &&
        (source->y + source->height > target->y) 
     ){
      return true;
   }

   return false;
}