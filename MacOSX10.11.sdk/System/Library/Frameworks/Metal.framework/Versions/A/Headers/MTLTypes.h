//
//  MTLTypes.h
//  Metal
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Metal/MTLDefines.h>

/*!
 @struct MTLOrigin
 @abstract Identify a pixel in an image. MTLOrigin is ususally used as the upper-left corner of a region of a texture.
 */
typedef struct {
    NSUInteger x, y, z;
} MTLOrigin;

MTL_INLINE MTLOrigin MTLOriginMake(NSUInteger x, NSUInteger y, NSUInteger z)
{
    MTLOrigin origin = {x, y, z};
    return origin;
}

/*!
 @typedef MTLSize
 @abstract A set of dimensions to declare the size of an object such as a compute kernel work group or grid.
 */
typedef struct {
    NSUInteger width, height, depth;
} MTLSize;

MTL_INLINE MTLSize MTLSizeMake(NSUInteger width, NSUInteger height, NSUInteger depth)
{
    MTLSize size = {width, height, depth};
    return size;
}

/*!
 @struct MTLRegion
 @abstract Identify a region in an image or texture.
 */

typedef struct
{
    MTLOrigin origin;
    MTLSize   size;
} MTLRegion;

MTL_INLINE MTLRegion MTLRegionMake1D(NSUInteger x, NSUInteger width)
{
    MTLRegion region;
    region.origin.x = x; region.origin.y = 0; region.origin.z = 0;
    region.size.width = width; region.size.height = 1; region.size.depth = 1;
    return region;
}

MTL_INLINE MTLRegion MTLRegionMake2D(NSUInteger x, NSUInteger y, NSUInteger width, NSUInteger height)
{
    MTLRegion region;
    region.origin.x = x; region.origin.y = y; region.origin.z = 0;
    region.size.width = width; region.size.height = height; region.size.depth = 1;
    return region;
}

MTL_INLINE MTLRegion MTLRegionMake3D(NSUInteger x, NSUInteger y, NSUInteger z, NSUInteger width, NSUInteger height, NSUInteger depth)
{
    MTLRegion region;
    region.origin.x = x; region.origin.y = y; region.origin.z = z;
    region.size.width = width; region.size.height = height; region.size.depth = depth;
    return region;
}

