/*!
 @header MDLTypes.h
 @framework ModelIO
 @abstract A variety of types used in representing 3d assets
 @copyright Copyright © 2015 Apple, Inc. All rights reserved.
 */

#define MDL_INLINE __attribute__((__always_inline__))
#define MDL_CONST_INLINE __attribute__((__always_inline__,__const__))

#import <ModelIO/ModelIOExports.h>
#import <Foundation/Foundation.h>
#include <simd/simd.h>
#include <math.h>

NS_ASSUME_NONNULL_BEGIN
typedef NS_ENUM(NSUInteger, MDLIndexBitDepth)
{
    MDLIndexBitDepthInvalid = 0,
    MDLIndexBitDepthUInt8 = 8,
    MDLIndexBitDepthUint8 = 8,
    MDLIndexBitDepthUInt16 = 16,
    MDLIndexBitDepthUint16 = 16,
    MDLIndexBitDepthUInt32 = 32,
    MDLIndexBitDepthUint32 = 32,
};

typedef NS_ENUM(NSInteger, MDLGeometryKind) {
    MDLGeometryKindPoints = 0,
    MDLGeometryKindLines,
    MDLGeometryKindTriangles,
    MDLGeometryKindTriangleStrips,
    MDLGeometryKindQuads
};

NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@protocol MDLNamed
@required
@property (nonatomic, copy, nullable) NSString *name;
@end

NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@protocol MDLComponent <NSObject>
@end

@class MDLObject;

NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@protocol MDLObjectContainerComponent <MDLComponent, NSFastEnumeration>

- (void)addObject:(MDLObject*)object;
- (void)removeObject:(MDLObject*)object;

// returns an array of this object's contained objects, aka children
@property (nonatomic, readonly, retain) NSArray<MDLObject*> *objects;

@end

typedef struct MDL_EXPORT_CPPCLASS {
    vector_float3 maxBounds;
    vector_float3 minBounds;
} MDLAxisAlignedBoundingBox;

NS_ASSUME_NONNULL_END
