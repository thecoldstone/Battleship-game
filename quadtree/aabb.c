/**
 * @file aabb.c
 * @brief AABB (Axis-aligned bounding box) implementation
 * @author Nikita Zhukov
 * @date 24.06.20
 * 
*/

#include <stdio.h>
#include <stdlib.h>

#include "aabb.h"

AABB* aabb_init(float x, float y, float w, float h) {
    AABB* a = (AABB*) malloc(sizeof(AABB));

    if(!a) {
        fprintf(stderr, "[ERROR] Failed Allocation");
        exit(EXIT_FAILURE);
    }

    a->x = x;
    a->y = y;
    a->w = w;
    a->h = h;

    return a;
}

int aabb_contains(AABB* a, float x, float y) {
    return ((x >= a->x && x <= a->w) && 
                (y >= a->y && y <= a->h));
}

void aabb_free(AABB* a) {
    free(a);
}
