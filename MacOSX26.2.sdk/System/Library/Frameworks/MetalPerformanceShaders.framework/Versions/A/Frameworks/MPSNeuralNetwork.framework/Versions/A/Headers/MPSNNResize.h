//
//  MPSResize.h
//  MPS
//
//  Copyright © 2018 Apple. All rights reserved.
//

#ifndef MPSNNResize_h
#define MPSNNResize_h

#import <MPSNeuralNetwork/MPSCNNKernel.h>

#ifdef __cplusplus
extern "C" {
#endif
    
#pragma mark -
#pragma mark MPSNNResizeBilinear

/*!
 *  @class      MPSNNResizeBilinear
 *  @dependency This depends on Metal.framework
 *  @discussion The MPSNNResizeBilinear filter resizes the source image  using bilinear interpolation to
 *              a destination whose dimensions are given by resizeWidth and resizeHeight
 *
 *              The number of output feature channels remains the same as the number of input feature
 *              channels.
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0))
@interface MPSNNResizeBilinear : MPSCNNKernel

/*! @property   resizeWidth
 *  @abstract   The resize width.
 */
@property(readonly, nonatomic) NSUInteger   resizeWidth;

/*! @property   resizeHeight
 *  @abstract   The resize height.
 */
@property(readonly, nonatomic) NSUInteger   resizeHeight;

/*! @property   alignCorners
 *  @abstract   If YES, the centers of the 4 corner pixels of the input and output regions are aligned,
 *              preserving the values at the corner pixels.
 *              The default is NO.
 */
@property(readonly, nonatomic) BOOL      alignCorners;

/*
 * You must use initWithDevice:resizeWidth:resizeHeight instead.
 * You must use one of the sub-classes of MPSCNNUpsampling.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

/*!
 *  @abstract  Initialize the resize bilinear filter.
 *  @param     device                   The device the filter will run on.
 *  @param     resizeWidth              The destination resize width in pixels
 *  @param     resizeHeight             The destination resize height in pixels
 *  @param     alignCorners             Specifier whether the centers of the 4 corner pixels of the input and output regions are aligned,
 *                                      preserving the values at the corner pixels.
 *  @return    A valid MPSNNResizeBilinear object or nil, if failure.
 */

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                           resizeWidth: (NSUInteger) resizeWidth
                          resizeHeight: (NSUInteger) resizeHeight
                          alignCorners: (BOOL) alignCorners NS_DESIGNATED_INITIALIZER;

/*! @abstract NSSecureCoding compatability
 *  @discussion See @ref MPSKernel#initWithCoder.
 *  @param      aDecoder    The NSCoder subclass with your serialized MPSNNResizeBilinear
 *  @param      device      The MTLDevice on which to make the MPSNNResizeBilinear
 *  @return     A new MPSNNResizeBilinear object, or nil if failure.
 */
-(nullable instancetype) initWithCoder:(NSCoder * __nonnull)aDecoder
                                device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;


@end /* MPSNNResizeBilinear */
    

/*!
 *  @class      MPSNNCropAndResizeBilinear
 *  @dependency This depends on Metal.framework
 *  @discussion The MPSNNCropAndResizeBilinear filter resizes the source image  using bilinear interpolation to
 *              a destination whose dimensions are given by resizeWidth and resizeHeight
 *
 *              The number of output feature channels remains the same as the number of input feature
 *              channels.
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0))
@interface MPSNNCropAndResizeBilinear : MPSCNNKernel

/*! @property   resizeWidth
 *  @abstract   The resize width.
 */
@property(readonly, nonatomic) NSUInteger   resizeWidth;

/*! @property   resizeHeight
 *  @abstract   The resize height.
 */
@property(readonly, nonatomic) NSUInteger   resizeHeight;

/*! @property   numberOfRegions
 *  @abstract   the number of bounding box i.e. regions to resize.
 */
@property(readonly, nonatomic) NSUInteger   numberOfRegions;

/*! @property   regions
 *  @abstract   This is a pointer to "numberOfRegions" boxes which specify the locations in the
 *              source image to use for each box/region to perform the resize operation.
 *              The coordinates specified are normalized values.  A normalized region outside the
 *              [0, 1] range is allowed, in which case we use extrapolation_value to extrapolate
 *              the input image values.
 */
@property (readonly, nonatomic, nonnull) const MPSRegion *regions;

/*
 * You must use initWithDevice:resizeWidth:resizeHeight instead.
 * You must use one of the sub-classes of MPSCNNUpsampling.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

/*!
 *  @abstract  Initialize the crop and resize bilinear filter.
 *  @param     device                   The device the filter will run on.
 *  @param     resizeWidth              The destination resize width in pixels
 *  @param     resizeHeight             The destination resize height in pixels
 *  @param     numberOfRegions          Specifies the number of bounding box i.e. regions to resize
 *  @param     regions                  This is a pointer to "numberOfRegions" boxes which specify the locations in the
 *                                      source image to use for each box/region to perform the resize operation.
 *  @return    A valid MPSNNCropAndResizeBilinear object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                           resizeWidth: (NSUInteger) resizeWidth
                          resizeHeight: (NSUInteger) resizeHeight
                       numberOfRegions: (NSUInteger) numberOfRegions
                               regions: (const MPSRegion * __nonnull) regions NS_DESIGNATED_INITIALIZER;

/*! @abstract NSSecureCoding compatability
 *  @discussion See @ref MPSKernel#initWithCoder.
 *  @param      aDecoder    The NSCoder subclass with your serialized MPSNNCropAndResizeBilinear
 *  @param      device      The MTLDevice on which to make the MPSNNCropAndResizeBilinear
 *  @return     A new MPSNNResizeBilinear object, or nil if failure.
 */
-(nullable instancetype) initWithCoder:(NSCoder * __nonnull)aDecoder
                                device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;


@end /* MPSNNCropAndResizeBilinear */

#ifdef __cplusplus
}
#endif

#endif /* MPSNNResize_h */

