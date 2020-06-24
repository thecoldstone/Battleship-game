#include <stdio.h>
#include <stdlib.h>
#include "quadtree.h"

QD_NODE* qnode_init(AABB* boundary) {
    QD_NODE* node = (QD_NODE*) malloc(sizeof(QD_NODE));
    
    if(!node) {
        fprintf(stderr, "[ERROR] Failed Allocation");
        exit(EXIT_FAILURE);
    }
    node->type = QDLEAF;
    node->boundary = boundary;

    return node;
}

QD_TREE* qt_init(int size) {
    QD_TREE* qtree = (QD_TREE*) malloc(sizeof(QD_TREE));

    if(!qtree) {
        fprintf(stderr, "[ERROR] Failed Allocation");
        exit(EXIT_FAILURE);
    }

    AABB* boundary = aabb_init(0, 0, size, size);

    qtree->root = qnode_init(boundary);

    return qtree;
}

POINT* point_init(float x, float y) {
    POINT* point = (POINT*) malloc(sizeof(POINT));

    if(!point) {
        fprintf(stderr, "[ERROR] Failed Allocation");
        exit(EXIT_FAILURE);
    }

    point->x = x;
    point->y = y;

    return point;

}

void qt_subdivide(QD_NODE* qt) { 
    float x = qt->boundary->x;
    float y = qt->boundary->y;
    float w = qt->boundary->w;
    float h = qt->boundary->h;
    qt->type = QDNODE;
    
    float offset = (w - x)/2; 

    qt->nw = qnode_init(aabb_init(x, y, x + offset, y + offset));
    printf("[NW] AABB x = %f, y=  %f \n", qt->nw->boundary->x, qt->nw->boundary->y);
    qt->ne = qnode_init(aabb_init(x + offset, y, w, y + offset));
    printf("[NE] AABB x = %f, y=  %f \n", qt->ne->boundary->x, qt->ne->boundary->y);
    qt->sw = qnode_init(aabb_init(x, y + offset, x + offset, h));
    printf("[SW] AABB x = %f, y=  %f \n", qt->sw->boundary->x, qt->sw->boundary->y);
    qt->se = qnode_init(aabb_init(x + offset, y + offset, w, h));
    printf("[SE] AABB x = %f, y=  %f \n", qt->se->boundary->x, qt->se->boundary->y);
}

int qt_is_inserted(QD_NODE* q, POINT* point) {
    return (aabb_contains(q->boundary, point->x, point->y) == 1 ? 1 : 0);
}

int qt_insert(QD_NODE* q, POINT* point){

    int ret = 0;
    
    // Ignore objects that do not belong in this quad tree
    if (!qt_is_inserted(q, point)) {
        return ret;
    }

    // We are assuming that each node can contain at maximum one item (data)

    // We have reached the leaf
    if(q->type == QDLEAF) {
        
        // Empty leaf
        if(q->leaf.point == NULL) {
            q->leaf.point = point;
            ret = 1;
            return ret;
        } else { // Leaf contains some data 
            POINT* old_point = q->leaf.point;
            // CELL * TODO

            qt_subdivide(q);
            // Reinsert old node
            if(qt_insert(q->nw, old_point)) {
                return 1;
            } else if(qt_insert(q->ne, old_point)) {
                return 1;
            } else if(qt_insert(q->sw, old_point)) {
                return 1;
            } else if(qt_insert(q->se, old_point)) {
                return 1;
            }

            // Insert new node
            if(qt_insert(q->nw, point)) {
                return 1;
            } else if(qt_insert(q->ne, point)) {
                return 1;
            } else if(qt_insert(q->sw, point)) {
                return 1;
            } else if(qt_insert(q->se, point)) {
                return 1;
            }

            return ret;
        }
    }

    return 1;
}

int main(){

    BOARD_SIZE = 20;
    QD_TREE* qt = qt_init(BOARD_SIZE);
    
    POINT* p = point_init(2, 20); 

    if(!qt_insert(qt->root, p)) 
        printf("[FAILED]\n");
    else
        printf("Inserted\n");

    return 0;

}
