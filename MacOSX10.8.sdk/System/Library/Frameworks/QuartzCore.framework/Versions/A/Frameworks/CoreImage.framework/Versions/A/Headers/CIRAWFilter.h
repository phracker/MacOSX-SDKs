/* CoreImage - CIKernel.h
 
 Copyright (c) 2006 Apple Computer, Inc.
 All rights reserved. */


#import <CoreImage/CIFilter.h>
#import <CoreImage/CoreImageDefines.h>

@class NSURL;
@class NSDictionary;
@class NSString;
@class NSData;

/** CIRAWFilter is a category of CIFilter which returns a CIFilter initialized with a RAW image. It allows the user to influence key aspects of the raw processing, such as white balance, exposure, sharpening or boost. */

@interface CIFilter (CIRAWFilter)

/** Returns a CIFilter that will in turn return a properly processed CIImage as "outputImage". */
+ (CIFilter *)filterWithImageURL:(NSURL *)url options:(NSDictionary *)options;

/** Returns a CIFilter that will in turn return a properly processed CIImage as "outputImage".

 Note that when using this initializer, you should pass in a source type identifier hint (kCGImageSourceTypeIdentifierHint) key/value pair in order to help the decoder determine the file type, as otherwise confusion and incorrect results are possible. An example of use would be: [opts setObject:(id)CGImageSourceGetTypeWithExtension ((CFStringRef)[[url path] pathExtension]) forKey:kCGImageSourceTypeIdentifierHint]; */
+ (CIFilter *)filterWithImageData:(NSData *)data options:(NSDictionary *)options;

/** NSString: Version string representing the decoder version to be used. A newly initialized object defaults to the newest available decoder version for the given image type. User can request an alternative, older version in order to maintain compatibility with older releases. Must be one of kCISupportedDecoderVersions (below), otherwise a nil output image will be generated. */
CORE_IMAGE_EXPORT NSString *const kCIInputDecoderVersionKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/** NSArray (NSDictionary) : Array of all supported decoder versions for the given image type, sorted in increasingly newer order. Each entry is a NSDictionary with a number of key/value pairs. All entries would represent a valid version identifier to be passed in for kCIInputDecoderVersion. This value can be only read; setting this value will raise an exception. Currently, the only defined key is @"version" which has as a value an NSString uniquely describing a given decoder version. This string may not be suitable for user interface display. */
CORE_IMAGE_EXPORT NSString *const kCISupportedDecoderVersionsKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/** @const      kCIInputEVKey
 NSNumber (float) : Exposure adjustment, default = 0.0. Declared in CIFilter.h */


/** NSNumber (float) : A value in the range of 0...1, controling the amount of boost applied to the image. A value of 0 indicates no boost, i.e. linear response. Default is 1, full boost. */
CORE_IMAGE_EXPORT NSString *const kCIInputBoostKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/** NSNumber (float): The X value of the chromaticity. You can always query this value and you'll get the current X value for neutral X,Y. */
CORE_IMAGE_EXPORT NSString *const kCIInputNeutralChromaticityXKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/** NSNumber (float): The Y value of the chromaticity. You can always query this value and you'll get the current Y value for neutral X,Y. */
CORE_IMAGE_EXPORT NSString *const kCIInputNeutralChromaticityYKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/** NSNumber (float) : The color temperature to be considered neutral. You can always query this value and you'll get the current value for temperature. */
CORE_IMAGE_EXPORT NSString *const kCIInputNeutralTemperatureKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/** NSNumber (float) : The tint to be considered neutral. You can always query this value and you'll get the current value for tint. */
CORE_IMAGE_EXPORT NSString *const kCIInputNeutralTintKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/** CIVector : (x, y) location in geometric coordinates of the unrotated output image that should be used as neutral. You can't query this value - it's undefined for reading. */
CORE_IMAGE_EXPORT NSString *const kCIInputNeutralLocationKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/** NSNumber (float) : The desired scale factor at which the image will be eventually drawn. Setting this value can greatly improve the drawing performance. A value of 1 would mean identity, values smaller than 1 will result in a smaller output image. Changing the Scale Factor with enabled Draft Mode may also improve performance. */
CORE_IMAGE_EXPORT NSString *const kCIInputScaleFactorKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/** NSNumber (BOOL) : If the optional scale factor is smaller than a certain factor, additionally setting Draft Mode to YES can improve image decoding speed without any perceivable loss of quality. Setting this argument to YES will not have any effect if the Scale Factor isn't below a threshold where it would be of benefit. Switching of this value from YES to NO is an expensive operation, and it's not recommended to use Draft Mode if the same image will need to be drawn without Draft Mode at a later time. */
CORE_IMAGE_EXPORT NSString *const kCIInputAllowDraftModeKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/** NSNumber (BOOL) : Normally, an image is loaded in its proper orientation, given the associated metadata gives an indication about the orientation. For special purposes it may be useful to load the image in its physical orientation. The exact meaning of this is dependent on the image in question. The default value is NO. */
CORE_IMAGE_EXPORT NSString *const kCIInputIgnoreImageOrientationKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/**
 @const      kCIInputImageOrientationKey
 @abstract   kCIInputImageOrientationKey
 @discussion NSNumber (int) : Overriding this value allows the user to change the orientation of the image. The valid values are in range 1...8 and follow the EXIF specification. Changing this value makes for instance rotation in 90-degree increments easy. The value is disregarded when the kCIInputIgnoreImageOrientationKey flag is set.
 */
CORE_IMAGE_EXPORT NSString *const kCIInputImageOrientationKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/** NSNumber (BOOL) : Determines if the default sharpening should be on. default = YES. Has no effect if the image used for initialization was not RAW. */
CORE_IMAGE_EXPORT NSString *const kCIInputEnableSharpeningKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/** NSNumber (BOOL) : Determines if progressive chromatic noise tracking (based on ISO and exposure time) should be used. default = YES. Has no effect if the image used for initialization was not RAW. */
CORE_IMAGE_EXPORT NSString *const kCIInputEnableChromaticNoiseTrackingKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/** NSNumber (double) : The amount of noise reduction applied. Range is 0 to 1. */
CORE_IMAGE_EXPORT NSString *const kCIInputNoiseReductionAmountKey AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;

/** NSNumber (float) : The amount to boost the shadow areas of the image. Can be used to lighten details in shadows. Has no effect if the image used for initialization was not RAW. */
CORE_IMAGE_EXPORT NSString *const kCIInputBoostShadowAmountKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/** NSNumber (float) : Simple bias to be used in conjunction with exposure adjustment (kCIInputEVKey). Has no effect if the image used for initialization was not RAW. */
CORE_IMAGE_EXPORT NSString *const kCIInputBiasKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/** CIFilter (id) : CIFilter to be applied to the RAW image while it is in linear space. */
CORE_IMAGE_EXPORT NSString *const kCIInputLinearSpaceFilter AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;

/** CIVector containing the full native size of the unscaled image. The vector's X value is the width, Y is the height. This is not affected by changing either kCIInputIgnoreImageOrientationKey or kCIInputImageOrientationKey. */
CORE_IMAGE_EXPORT NSString *const kCIOutputNativeSizeKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/** Read-only NSSet containing a list of keys that affect the output image. Depending on the RAW decoder version (kCIInputDecoderVersionKey) and the input image type, some input keys might have no effect. */
CORE_IMAGE_EXPORT NSString *const kCIActiveKeys AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;

@end
