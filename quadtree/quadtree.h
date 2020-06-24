#include "src/board.h"
#include "aabb.h"

typedef struct POINT_ {
    float x;
    float y;
} POINT;

typedef enum {
    QDNODE,
    QDLEAF
} QD_TNODE;

typedef struct QD_NODE_ {

    QD_TNODE type;
    AABB* boundary;
    struct QD_NODE_ *nw;
    struct QD_NODE_ *ne;
    struct QD_NODE_ *sw;
    struct QD_NODE_ *se;
    struct {
        Cell* cell;
        POINT* point;
    } leaf;

} QD_NODE;

typedef struct QD_TREE_ {
    QD_NODE* root;
} QD_TREE;

/**
 * 
 */ 
QD_TREE* qt_init(int size);

/**
 * 
 */ 
QD_NODE* qnode_init(AABB* boundary);

/**
 * 
 */ 
void qt_subdivide(QD_NODE* qt);
