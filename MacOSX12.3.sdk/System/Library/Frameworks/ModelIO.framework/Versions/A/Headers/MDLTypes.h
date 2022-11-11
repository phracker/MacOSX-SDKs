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

/* Alembic file format, file extension ABC, UTI public.alembic */
MDL_EXPORT NSString * __nonnull const kUTTypeAlembic API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0));

/* 3d Object file format, file extension OBJ, UTI public.geometry-definition-format */
MDL_EXPORT NSString * __nonnull const kUTType3dObject API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0));

/* Polygon file format, file extension PLY, UTI public.polygon-file-format */
MDL_EXPORT NSString * __nonnull const kUTTypePolygon API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0));

/* Stereolithography file format, file extension STL, UTI public.standard-tesselated-geometry-format */
MDL_EXPORT NSString * __nonnull const kUTTypeStereolithography API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0));

/* Universal Scene Description file format, file extension USDA or USDC, UTI com.pixar.universal-scene-description */
MDL_EXPORT NSString * __nonnull const kUTTypeUniversalSceneDescription API_AVAILABLE(macos(10.12), ios(10.0), tvos(9.0));

/* Universal Scene Description Mobile file format, file extension USDZ, UTI com.pixar.universal-scene-description-mobile */
MDL_EXPORT NSString * __nonnull const kUTTypeUniversalSceneDescriptionMobile API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0)); 

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

typedef NS_ENUM(NSInteger, MDLGeometryType) {
    MDLGeometryTypePoints = 0,
    MDLGeometryTypeLines,
    MDLGeometryTypeTriangles,
    MDLGeometryTypeTriangleStrips,
    MDLGeometryTypeQuads,
    MDLGeometryTypeVariableTopology
};

typedef NS_ENUM(NSInteger, MDLProbePlacement) {
    MDLProbePlacementUniformGrid = 0,
    MDLProbePlacementIrradianceDistribution
};

typedef NS_ENUM(NSUInteger, MDLDataPrecision) {
    MDLDataPrecisionUndefined,
    MDLDataPrecisionFloat,
    MDLDataPrecisionDouble
} API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));

API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0))
MDL_EXPORT
@protocol MDLNamed
@required
@property (nonatomic, copy) NSString *name;
@end

API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0))
MDL_EXPORT
@protocol MDLComponent <NSObject>
@end

@class MDLObject;

API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0))
MDL_EXPORT
@protocol MDLObjectContainerComponent <MDLComponent, NSFastEnumeration>

- (void)addObject:(MDLObject*)object;
- (void)removeObject:(MDLObject*)object;
- (MDLObject *)objectAtIndexedSubscript:(NSUInteger)index API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));

@property (readonly) NSUInteger count API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));

// returns an array of this object's contained objects, aka children
@property (nonatomic, readonly, retain) NSArray<MDLObject*> *objects;

@end

typedef struct MDL_CLASS_EXPORT {
    vector_float3 maxBounds;
    vector_float3 minBounds;
} MDLAxisAlignedBoundingBox;

NS_ASSUME_NONNULL_END
