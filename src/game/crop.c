#include "raylib.h"

#include "crop.h"
#include "core/render/drawable.h"

#include <stdio.h>

#define SPRITE_SIZE 16


static Texture2D texture;

Crop create_crop(CropType type){
    texture = LoadTexture("crops/basic_plants.png");

    switch(type){
        case WHEAT:
            Rectangle texutre_source = {SPRITE_SIZE * 2,0, SPRITE_SIZE ,SPRITE_SIZE};

            printf("INFO: CRIANDO O TRIGO");
            return (Crop) {
                .elapsed_growth_time = 0, 
                .growth_time = 10, 
                .object = create_object(
                    (KGTransform){
                        .position= (Vector2){.x=-20,.y=0},
                        .scale=    (Vector2){.x=4 * SPRITE_SIZE, .y=4 * SPRITE_SIZE},
                        .rotation= (Vector2){.x=0,.y=0}
                    },
                    (Drawable){
                        .source= texutre_source,
                        .sprite_sheet= texture
                    }
                )};
        case BEET:
            return (Crop){
                .elapsed_growth_time = 0, 
                .growth_time = 20, 
                .object = create_object(
                    (KGTransform){
                        .position= (Vector2){.x=10,.y=10},
                        .scale=    (Vector2){.x=4, .y=4},
                        .rotation= (Vector2){.x=0,.y=0}
                    },
                    (Drawable){
                        .source= (Rectangle){.height=0,.width=0,.x=4, .y=4},
                        .sprite_sheet= texture
                    }
                )};
    }
}

void update(Crop* crop,float delta_time){
    if(crop->growth_time >= crop->elapsed_growth_time){
        
    }

}