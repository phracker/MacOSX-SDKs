/* CoreImage - CIKernel.h
 
 Copyright (c) 2006 Apple, Inc.
 All rights reserved. */


#import <CoreImage/CIFilter.h>
#import <CoreImage/CoreImageDefines.h>
#import <CoreVideo/CoreVideo.h>


@class NSURL;
@class NSDictionary;
@class NSData;

/** CIRAWFilter is a category of CIFilter which returns a CIFilter initialized with a RAW image. It allows the user to influence key aspects of the raw processing, such as white balance, exposure, sharpening or boost. */

@interface CIFilter (CIRAWFilter)

/** Returns a CIFilter that will in turn return a properly processed CIImage as "outputImage". */
+ (CIFilter *)filterWithImageURL:(NSURL *)url options:(NSDictionary *)options NS_AVAILABLE(10_5, 10_0);

/** Returns a CIFilter that will in turn return a properly processed CIImage as "outputImage".

 Note that when using this initializer, you should pass in a source type identifier hint (kCGImageSourceTypeIdentifierHint) key/value pair in order to help the decoder determine the file type, as otherwise confusion and incorrect results are possible. */
+ (CIFilter *)filterWithImageData:(NSData *)data options:(NSDictionary *)options NS_AVAILABLE(10_5, 10_0);

/** Returns a CIFilter that will in turn return a properly processed CIImage as "outputImage".
 
 Note that when using this initializer, you should pass in a CVPixelBufferRef with one of the following Raw pixel format types
    kCVPixelFormatType_14Bayer_GRBG, kCVPixelFormatType_14Bayer_RGGB, kCVPixelFormatType_14Bayer_BGGR, kCVPixelFormatType_14Bayer_GBRG
 as well as the root properties attachment from the CMSampleBufferRef. */
+ (CIFilter *)filterWithCVPixelBuffer:(CVPixelBufferRef)pixelBuffer properties:(NSDictionary *)properties options:(NSDictionary *)options NS_AVAILABLE(10_12, 10_0);

/** NSNumber (BOOL) : Setting Draft Mode to YES can improve image decoding speed without minimal loss of quality.
    The default value is NO. */
CORE_IMAGE_EXPORT NSString *const kCIInputAllowDraftModeKey NS_AVAILABLE(10_5, 10_0);

/** NSString: Version string representing the decoder version to be used. A newly initialized object defaults to the newest available decoder version for the given image type. User can request an alternative, older version in order to maintain compatibility with older releases. Must be one of kCISupportedDecoderVersions (below), otherwise a nil output image will be generated. */
CORE_IMAGE_EXPORT NSString *const kCIInputDecoderVersionKey NS_AVAILABLE(10_5, 10_0);

/** NSArray (NSDictionary) : Array of all supported decoder versions for the given image type, sorted in increasingly newer order. Each entry is a NSDictionary with a number of key/value pairs. All entries would represent a valid version identifier to be passed in for kCIInputDecoderVersion. This value can be only read; setting this value will raise an exception. Currently, the only defined key is @"version" which has as a value an NSString uniquely describing a given decoder version. This string may not be suitable for user interface display. */
CORE_IMAGE_EXPORT NSString *const kCISupportedDecoderVersionsKey NS_AVAILABLE(10_5, 10_0);



/** @const      kCIInputEVKey
 NSNumber (float) : Exposure adjustment, default = 0.0. Declared in CIFilter.h */

/** NSNumber (float) : A value controlling the amount of baseline exposure applied to the image.
 A value of 0 indicates no baseline exposure, i.e. linear response. Default varies from with camera settings. */
CORE_IMAGE_EXPORT NSString *const kCIInputBaselineExposureKey NS_AVAILABLE(10_12, 10_0);

/** NSNumber (float) : A value in the range of 0...1, controlling the amount of boost applied to the image.
    A value of 0 indicates no boost, i.e. linear response. Default is 1, full boost. */
CORE_IMAGE_EXPORT NSString *const kCIInputBoostKey NS_AVAILABLE(10_5, 10_0);

/** NSNumber (float) : The amount to boost the shadow areas of the image. Can be used to lighten details in shadows. 
    Has no effect if the image used for initialization was not RAW. */
CORE_IMAGE_EXPORT NSString *const kCIInputBoostShadowAmountKey NS_AVAILABLE(10_5, 10_0);

/** NSNumber (BOOL) : Setting DisableGamutMap to YES disables gamut mapping.
    The default value is NO. */
CORE_IMAGE_EXPORT NSString *const kCIInputDisableGamutMapKey NS_AVAILABLE(10_12, 10_0);

/** NSNumber (float): The X value of the chromaticity. You can always query this value and you'll get the current X value for neutral X,Y. */
CORE_IMAGE_EXPORT NSString *const kCIInputNeutralChromaticityXKey NS_AVAILABLE(10_5, 10_0);

/** NSNumber (float): The Y value of the chromaticity. You can always query this value and you'll get the current Y value for neutral X,Y. */
CORE_IMAGE_EXPORT NSString *const kCIInputNeutralChromaticityYKey NS_AVAILABLE(10_5, 10_0);

/** NSNumber (float) : The color temperature to be considered neutral. You can always query this value and you'll get the current value for temperature. */
CORE_IMAGE_EXPORT NSString *const kCIInputNeutralTemperatureKey NS_AVAILABLE(10_5, 10_0);

/** NSNumber (float) : The tint to be considered neutral. You can always query this value and you'll get the current value for tint. */
CORE_IMAGE_EXPORT NSString *const kCIInputNeutralTintKey NS_AVAILABLE(10_5, 10_0);

/** CIVector : (x, y) location in geometric coordinates of the unrotated output image that should be used as neutral. 
    You can't query this value - it's undefined for reading. */
CORE_IMAGE_EXPORT NSString *const kCIInputNeutralLocationKey NS_AVAILABLE(10_5, 10_0);

/** NSNumber (float) : The desired scale factor at which the image will be eventually drawn. Setting this value can greatly improve the drawing performance. A value of 1 would mean identity, values smaller than 1 will result in a smaller output image. Changing the Scale Factor with enabled Draft Mode may also improve performance. */
CORE_IMAGE_EXPORT NSString *const kCIInputScaleFactorKey NS_AVAILABLE(10_5, 10_0);




/** NSNumber (BOOL) : Normally, an image is loaded in its proper orientation, given the associated metadata gives an indication about the orientation. For special purposes it may be useful to load the image in its physical orientation. The exact meaning of this is dependent on the image in question. The default value is NO. */
CORE_IMAGE_EXPORT NSString *const kCIInputIgnoreImageOrientationKey NS_AVAILABLE(10_5, 10_0);


/** NSNumber (int) : Overriding this value allows the user to change the orientation of the image. The valid values are in range 1...8 and follow the EXIF specification. Changing this value makes for instance rotation in 90-degree increments easy. The value is disregarded when the kCIInputIgnoreImageOrientationKey flag is set.
 */
CORE_IMAGE_EXPORT NSString *const kCIInputImageOrientationKey NS_AVAILABLE(10_5, 10_0);



/** NSNumber (BOOL) : Determines if the default sharpening should be on. default = YES. Has no effect if the image used for initialization was not RAW. */
CORE_IMAGE_EXPORT NSString *const kCIInputEnableSharpeningKey NS_AVAILABLE(10_5, 10_0);

/** NSNumber (BOOL) : Determines if progressive chromatic noise tracking (based on ISO and exposure time) should be used. default = YES. Has no effect if the image used for initialization was not RAW. */
CORE_IMAGE_EXPORT NSString *const kCIInputEnableChromaticNoiseTrackingKey NS_AVAILABLE(10_5, 10_0);

/** NSNumber (double) : The amount of noise reduction applied. Range is 0 to 1. */
CORE_IMAGE_EXPORT NSString *const kCIInputNoiseReductionAmountKey NS_AVAILABLE(10_7, 10_0);

/** NSNumber (double) : The amount of moire reduction applied. Range is 0 to 1. */
CORE_IMAGE_EXPORT NSString *const kCIInputMoireAmountKey NS_AVAILABLE(10_13, 11_0);

/** NSNumber (BOOL) : Determines if the default vendor lens correction be on. default = YES if raw image used for initialization contains lens distortion parameters. */
CORE_IMAGE_EXPORT NSString *const kCIInputEnableVendorLensCorrectionKey NS_AVAILABLE(10_10, 10_0);

/** NSNumber (double) : The amount of luminance noise reduction applied. Range is 0 to 1. */
CORE_IMAGE_EXPORT NSString *const kCIInputLuminanceNoiseReductionAmountKey NS_AVAILABLE(10_10, 10_0);

/** NSNumber (double) : The amount of color noise reduction applied. Range is 0 to 1. */
CORE_IMAGE_EXPORT NSString *const kCIInputColorNoiseReductionAmountKey NS_AVAILABLE(10_10, 10_0);

/** NSNumber (double) : The amount of noise reduction sharpness applied. Range is 0 to 1. */
CORE_IMAGE_EXPORT NSString *const kCIInputNoiseReductionSharpnessAmountKey NS_AVAILABLE(10_10, 10_0);

/** NSNumber (double) : The amount of noise reduction contrast applied. Range is 0 to 1. */
CORE_IMAGE_EXPORT NSString *const kCIInputNoiseReductionContrastAmountKey NS_AVAILABLE(10_10, 10_0);

/** NSNumber (double) : The amount of noise reduction detail applied. Range is 0 to 1. */
CORE_IMAGE_EXPORT NSString *const kCIInputNoiseReductionDetailAmountKey NS_AVAILABLE(10_10, 10_0);



/** CIFilter (id) : CIFilter to be applied to the RAW image while it is in linear space. */
CORE_IMAGE_EXPORT NSString *const kCIInputLinearSpaceFilter NS_AVAILABLE(10_7, 10_0);

/** CIVector containing the full native size of the unscaled image. The vector's X value is the width, Y is the height. 
    This is not affected by changing either kCIInputIgnoreImageOrientationKey or kCIInputImageOrientationKey. */
CORE_IMAGE_EXPORT NSString *const kCIOutputNativeSizeKey NS_AVAILABLE(10_5, 10_0);

/** Read-only NSSet containing a list of keys that affect the output image. 
    Depending on the RAW decoder version (kCIInputDecoderVersionKey) and the input image type, 
    some input keys might have no effect. */
CORE_IMAGE_EXPORT NSString *const kCIActiveKeys NS_AVAILABLE(10_7, 10_0);

@end
