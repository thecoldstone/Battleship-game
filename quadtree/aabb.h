/**
 * @file aabb.h 
 * @brief AABB (Axis-aligned bounding box) library
 * @author Nikita Zhukov
 * @date 24.06.20
 * 
*/

#ifndef _AABB_H
#define _AABB_H

typedef struct AABB_ {
    float x;
    float y;
    float w;
    float h;
} AABB;

/**
 * @brief Initialize Axis-aligned bounding box
 * 
 * @param x - x axe coordinate (left upper point of the bounding box)
 * @param y - y axe coordinate (left upper point of the bounding box)
 * @param w - width of the bounding box (the most right point of the bounding box)
 * @param y - height of the bounding box (the lowest most right point of the bounding box)
 * @return bounding box
 */ 
AABB* aabb_init(float x, float y, float w, float h);

/**
 * 
 */ 
int aabb_contains(AABB* a, float x, float y);

/**
 * 
 */
void aabb_free(AABB* a);

#endif
