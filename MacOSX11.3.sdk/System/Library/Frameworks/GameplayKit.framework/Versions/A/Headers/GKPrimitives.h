//
//  GKPrimitives.h
//  GameplayKit
//
//  Copyright © 2016 Apple. All rights reserved.
//

#include <simd/vector_types.h>

/**
 * Representation of an axis aligned box via its min corner (lower-left) and max corner (upper-right) 
 */
struct GKBox
{
    vector_float3 boxMin;
    vector_float3 boxMax;
};
typedef struct GKBox GKBox;

/**
 * Representation of an axis aligned quad via its min corner (lower-left) and max corner (upper-right)
 */
struct GKQuad
{
    vector_float2 quadMin;
    vector_float2 quadMax;
};
typedef struct GKQuad GKQuad;

struct GKTriangle
{
    vector_float3 points[3];
};
typedef struct GKTriangle GKTriangle;
