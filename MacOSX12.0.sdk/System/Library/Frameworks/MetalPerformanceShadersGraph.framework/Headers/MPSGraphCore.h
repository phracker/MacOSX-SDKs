//
//  MPSGraphCore.h
//  MetalPerformanceShadersGraph
//
//  Created on 11/10/19.
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#ifndef MPSGraphCore_h
#define MPSGraphCore_h

#import <Foundation/Foundation.h>
#import <MetalPerformanceShaders/MetalPerformanceShaders.h>

NS_ASSUME_NONNULL_BEGIN

MPS_CLASS_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))
@interface MPSGraphType: NSObject<NSCopying>

@end

MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraphShapedType: MPSGraphType

/*! @property   shape
 *  @discussion shape of the shapedType
 */
@property (readwrite, nullable, copy, atomic) MPSShape *shape;

/*! @property   dataType
 *  @discussion dataType of the shapedType
 */
@property (readwrite, atomic) MPSDataType dataType;

/*! @abstract   Initialize an MPSGraphShapedType
 *  @param      shape  The MPSShape
 *  @param      dataType  The dataType of the shaped type
 *  @return     A valid MPSGraphShapedType, or nil if allocation failure.
 */
-(instancetype) initWithShape:(MPSShape * _Nullable) shape
                     dataType:(MPSDataType) dataType;

-(BOOL)isEqualTo:(MPSGraphShapedType * _Nullable)object;

@end

/*!
 *  @typedef    MPSGraphTensorNamedDataLayout
 *  @abstract   Tensor Layout
 *
 *  @constant   MPSGraphTensorNamedDataLayoutNCHW           LayoutNCHW
 *  @constant   MPSGraphTensorNamedDataLayoutNHWC           LayoutNHWC
 *  @constant   MPSGraphTensorNamedDataLayoutOIHW            LayoutOIHW
 *  @constant   MPSGraphTensorNamedDataLayoutHWIO            LayoutHWIO
 *  @constant   MPSGraphTensorNamedDataLayoutCHW             LayoutCHW
 *  @constant   MPSGraphTensorNamedDataLayoutHWC             LayoutHWC
 *  @constant   MPSGraphTensorNamedDataLayoutHW                LayoutHW
 */
typedef NS_ENUM(NSUInteger, MPSGraphTensorNamedDataLayout)
{
    MPSGraphTensorNamedDataLayoutNCHW       MPS_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0)) MPS_SWIFT_NAME(NCHW)   =  0L,
    MPSGraphTensorNamedDataLayoutNHWC       MPS_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))                        =  1L,
    MPSGraphTensorNamedDataLayoutOIHW       MPS_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))                        =  2L,
    MPSGraphTensorNamedDataLayoutHWIO       MPS_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))                        =  3L,
    MPSGraphTensorNamedDataLayoutCHW        MPS_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))                        =  4L,
    MPSGraphTensorNamedDataLayoutHWC        MPS_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))                        =  5L,
    MPSGraphTensorNamedDataLayoutHW         MPS_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))                        =  6L,
};

/*!
 *  @typedef    MPSGraphPaddingStyle
 *  @abstract   Tensor Layout
 *
 *  @constant   MPSGraphPaddingStyleExplicit                Explicit
 *  @constant   MPSGraphPaddingStyleTF_SAME           TF_SAME
 *  @constant   MPSGraphPaddingStyleTF_VALID           TF_VALID
 *  @constant   MPSGraphPaddingStyleExplicitOffset       Explicit offsets
 */
typedef NS_ENUM(NSUInteger, MPSGraphPaddingStyle)
{
    MPSGraphPaddingStyleExplicit            MPS_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0)) MPS_SWIFT_NAME(explicit)   =  0L,
    MPSGraphPaddingStyleTF_VALID            MPS_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))                            =  1L,
    MPSGraphPaddingStyleTF_SAME             MPS_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))                            =  2L,
    MPSGraphPaddingStyleExplicitOffset      MPS_ENUM_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))                            =  3L,
};

/*!
 *  @typedef    MPSGraphPaddingMode
 *  @abstract   Tensor Padding mode
 *
 *  @constant   MPSGraphPaddingModeConstant                    Constant
 *  @constant   MPSGraphPaddingModeReflect                       Reflect
 *  @constant   MPSGraphPaddingModeSymmetric                 Symmetric
 *  @constant   MPSGraphPaddingModeClampToEdge           ClampToEdge (PyTorch ReplicationPad)
 *  @constant   MPSGraphPaddingModeZero                           Zero
 *  @constant   MPSGraphPaddingModePeriodic                     Periodic
 *  @constant   MPSGraphPaddingModeAntiPeriodic               Anti Periodic
 */
typedef NS_ENUM(NSInteger, MPSGraphPaddingMode)
{
    MPSGraphPaddingModeConstant          MPS_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0)) MPS_SWIFT_NAME(constant) =  0L,
    MPSGraphPaddingModeReflect           MPS_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))                          =  1L,
    MPSGraphPaddingModeSymmetric         MPS_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))                          =  2L,
    MPSGraphPaddingModeClampToEdge       MPS_ENUM_AVAILABLE_STARTING(macos(11.1), ios(15.0), tvos(15.0))                          =  3L,
    MPSGraphPaddingModeZero              MPS_ENUM_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))                          =  4L,
    MPSGraphPaddingModePeriodic          MPS_ENUM_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))                          =  5L, // x[-2] -> x[L-3], where L is size of x.
    MPSGraphPaddingModeAntiPeriodic      MPS_ENUM_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))                          =  6L, // x[-2] -> -x[L-3]
};

/*!
 *  @typedef    MPSGraphStencilReductionMode
 *  @abstract   Reduction Mode
 *
 *  @constant   MPSGraphReductionModeMin                        Min
 *  @constant   MPSGraphReductionModeMax                       Max
 *  @constant   MPSGraphReductionModeSum                       Sum
 *  @constant   MPSGraphReductionModeProduct                  Product
 *  @constant   MPSGraphReductionModeArgumentMin         Argument Min
 *  @constant   MPSGraphReductionModeArgumentMax        Argument Max
 */
typedef NS_ENUM(NSUInteger, MPSGraphReductionMode)
{
    MPSGraphReductionModeMin             MPS_ENUM_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))     =  0L,
    MPSGraphReductionModeMax             MPS_ENUM_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))     =  1L,
    MPSGraphReductionModeSum             MPS_ENUM_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))     =  2L,
    MPSGraphReductionModeProduct         MPS_ENUM_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))     =  3L,
    MPSGraphReductionModeArgumentMin     MPS_ENUM_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))     =  4L,
    MPSGraphReductionModeArgumentMax     MPS_ENUM_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0))     =  5L
};

NS_ASSUME_NONNULL_END

#endif /* MPSGraphCore_h */
