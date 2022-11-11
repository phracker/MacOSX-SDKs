/*!
 *  @header MPSImageConversions.h
 *  @framework MetalPerformanceShaders.framework
 *
 *  @copyright Copyright (c) 2015 Apple Inc. All rights reserved.
 *  @abstract MetalPerformanceShaders conversion filters
 *  @ignorefuncmacro MPS_CLASS_AVAILABLE_STARTING
 */

#ifndef MPS_Conversions_h
#define MPS_Conversions_h

#include <MPSImage/MPSImageKernel.h>
#include <CoreGraphics/CGColorConversionInfo.h>


/*!
 *  @class      MPSImageConversion
 *  @discussion The MPSImageConversion filter performs a conversion from source to destination
 *
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(10.0), macCatalyst(13.0), tvos(10.0))
@interface  MPSImageConversion : MPSUnaryImageKernel

/*! @property   sourceAlpha
 *  @abstract   Premultiplication description for the source texture
 *  @discussion Most colorspace conversion operations can not work directly on premultiplied data.
 *              Use this property to tag premultiplied data so that the source texture can
 *              be unpremultiplied prior to application of these transforms. 
 *              Default: MPSPixelAlpha_AlphaIsOne
 */
@property (readonly, nonatomic) MPSAlphaType sourceAlpha;

/*! @property   destinationAlpha
 *  @abstract   Premultiplication description for the destinationAlpha texture
 *  @discussion Colorspace conversion operations produce non-premultiplied data.
 *              Use this property to tag cases where premultiplied results are required.
 *              If MPSPixelAlpha_AlphaIsOne is used, the alpha channel will be set to 1. 
 *              Default: MPSPixelAlpha_AlphaIsOne
 */
@property (readonly, nonatomic) MPSAlphaType destinationAlpha;



/*!
 *  @abstract   Create a converter that can convert texture colorspace, alpha and texture format
 *  @discussion Create a converter that can convert texture colorspace, alpha and MTLPixelFormat. 
 *              Optimized cases exist for NULL color space converter and no alpha conversion.
 *  @param      device              The device the filter will run on
 *  @param      srcAlpha            The alpha encoding for the source texture
 *  @param      destAlpha           The alpha encoding for the destination texture
 *  @param      backgroundColor     An array of CGFloats giving the background color to use when flattening an image.
 *                                  The color is in the source colorspace.  The length of the array is the number 
 *                                  of color channels in the src colorspace. If NULL, use {0}.
 *  @param      conversionInfo      The colorspace conversion to use. May be NULL, indicating no
 *                                  color space conversions need to be done.
 *
 *  @result     An initialized MPSImageConversion object.
 */
-(nonnull instancetype) initWithDevice:(nonnull id<MTLDevice>)device
                              srcAlpha:(MPSAlphaType) srcAlpha
                             destAlpha:(MPSAlphaType) destAlpha
                       backgroundColor:(nullable CGFloat*) backgroundColor
                        conversionInfo:(nullable CGColorConversionInfoRef) conversionInfo;


@end  /* MPSImageConversion */

#endif
