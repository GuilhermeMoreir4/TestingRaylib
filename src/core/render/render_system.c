#include "render_system.h"

#define MAX_QUEUE_SIZE 100

typedef struct{
    QueueElement queue[MAX_QUEUE_SIZE];
    int count;
}RenderQueue;

static RenderQueue renderQueue;

void begin_frame(){
    renderQueue.count = 0;
}


void submit(Drawable drawable,KGTransform transform,int layer){
    if(renderQueue.count == MAX_QUEUE_SIZE){
        printf("QUEUE FOR DRAW IS FULL");
        return;
    }

    renderQueue.queue[renderQueue.count] = (QueueElement){
        .drawable=drawable,
        .layer= layer,
        .transform=transform
    };
    
    renderQueue.count++;
};

int queue_comparator(const void* a,const void* b) {
    QueueElement* element_a = (QueueElement*) a;
    QueueElement* element_b = (QueueElement*) b;

  	return element_a->layer - element_b->layer;
}

void sort_queue(){
    qsort(renderQueue.queue, renderQueue.count, sizeof(QueueElement), queue_comparator);
}

void flush(){

    sort_queue();

    for (int draw_index = 0; draw_index < renderQueue.count; draw_index++){
        QueueElement draw = renderQueue.queue[draw_index];
       
		DrawTexturePro(
            draw.drawable.sprite_sheet,
            draw.drawable.source,
            (Rectangle) {0,0,draw.transform.scale.x, draw.transform.scale.y},
            draw.transform.position,
            0,
            WHITE
        );
    }
};

