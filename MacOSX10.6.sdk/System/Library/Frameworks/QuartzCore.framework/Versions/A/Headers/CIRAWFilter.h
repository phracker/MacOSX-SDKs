
#import "CIFilter.h"

@class NSURL;
@class NSDictionary;
@class NSString;
@class NSData;

/*!
 @header CIRAWFilter
 @copyright 2006 Apple Computer, Inc. All rights reserved.
 @availability Coming to a Leopard installation near you
 @abstract   CIRAWFilter is a category of CIFilter which returns a CIFilter initialized with a RAW image. It allows the user to influence key aspects of the raw processing, such as white balance, exposure, sharpening or boost.
 @discussion Forthcoming
*/

@interface CIFilter (CIRAWFilter)

/*!
 @method     filterWithImageURL:options:
 @abstract   Returns a CIFilter that will in turn return a properly processed CIImage as "outputImage".
 @result     CIFilter
 @discussion 
 */
+ (CIFilter *)filterWithImageURL:(NSURL *)url options:(NSDictionary *)options;

/*!
 @method     filterWithImageData:options:
 @abstract   Returns a CIFilter that will in turn return a properly processed CIImage as "outputImage".
 @result     CIFilter
 @discussion Note that when using this initializer, you should pass in a source type identifier hint (kCGImageSourceTypeIdentifierHint) key/value pair in order to help the decoder determine the file type, as otherwise confusion and incorrect results are possible. An example of use would be: [opts setObject:(id)CGImageSourceGetTypeWithExtension ((CFStringRef)[[url path] pathExtension]) forKey:kCGImageSourceTypeIdentifierHint];
 */
+ (CIFilter *)filterWithImageData:(NSData *)data options:(NSDictionary *)options;

/*!
 @const      kCIInputDecoderVersionKey
 @abstract   kCIInputDecoderVersionKey
 @discussion NSString : Version string representing the decoder version to be used. A newly initialized object defaults to the newest available decoder version for the given image type. User can request an alternative, older version in order to maintain compatibility with older releases. Must be one of kCISupportedDecoderVersions (below), otherwise a nil output image will be generated.
 */
extern NSString * const kCIInputDecoderVersionKey  AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*!
 @const      kCISupportedDecoderVersionsKey
 @abstract   kCISupportedDecoderVersionsKey
 @discussion NSArray (NSDictionary) : Array of all supported decoder versions for the given image type, sorted in increasingly newer order. Each entry is a NSDictionary with a number of key/value pairs. All entries would represent a valid version identifier to be passed in for kCIInputDecoderVersion. This value can be only read; setting this value will raise an exception. Currently, the only defined key is @"version" which has as a value an NSString uniquely describing a given decoder version. This string may not be suitable for user interface display.
 */
extern NSString * const kCISupportedDecoderVersionsKey  AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*!
 @const      kCIInputEVKey
 @abstract   kCIInputEVKey
 @discussion NSNumber (float) : Exposure adjustment, default = 0.0. Declared in CIFilter.h
 */


/*!
 @const      kCIInputBoostKey
 @abstract   kCIInputBoostKey
 @discussion NSNumber (float) : A value in the range of 0...1, controling the amount of boost applied to the image. A value of 0 indicates no boost, i.e. linear response. Default is 1, full boost.
 */
extern NSString * const kCIInputBoostKey  AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
 @const      kCIInputNeutralChromaticityXKey
 @abstract   kCIInputNeutralChromaticityXKey
 @discussion NSNumber (float): The X value of the chromaticity. You can always query this value and you'll get the current X value for neutral X,Y.
 */
extern NSString * const kCIInputNeutralChromaticityXKey  AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
 @const      kCIInputNeutralChromaticityYKey
 @abstract   kCIInputNeutralChromaticityYKey
 @discussion NSNumber (float): The Y value of the chromaticity. You can always query this value and you'll get the current Y value for neutral X,Y.
 */
extern NSString * const kCIInputNeutralChromaticityYKey  AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
 @const      kCIInputNeutralTemperatureKey
 @abstract   kCIInputNeutralTemperatureKey
 @discussion NSNumber (float) : The color temperature to be considered neutral. You can always query this value and you'll get the current value for temperature.
 */
extern NSString * const kCIInputNeutralTemperatureKey  AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
 @const      kCIInputNeutralTintKey
 @abstract   kCIInputNeutralTintKey
 @discussion NSNumber (float) : The tint to be considered neutral. You can always query this value and you'll get the current value for tint.
 */
extern NSString * const kCIInputNeutralTintKey  AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
 @const      kCIInputNeutralLocationKey
 @abstract   kCIInputNeutralLocationKey
 @discussion CIVector : (x, y) location in geometric coordinates of the unrotated output image that should be used as neutral. You can't query this value - it's undefined for reading.
 */
extern NSString * const kCIInputNeutralLocationKey  AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
 @const      kCIInputScaleFactorKey
 @abstract   kCIInputScaleFactorKey
 @discussion NSNumber (float) : The desired scale factor at which the image will be eventually drawn. Setting this value can greatly improve the drawing performance. A value of 1 would mean identity, values smaller than 1 will result in a smaller output image. Changing the Scale Factor with enabled Draft Mode may also improve performance.
 */
extern NSString * const kCIInputScaleFactorKey  AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
 @const      kCIInputAllowDraftModeKey
 @abstract   kCIInputAllowDraftModeKey
 @discussion NSNumber (BOOL) : If the optional scale factor is smaller than a certain factor, additionally setting Draft Mode to YES can improve image decoding speed without any perceivable loss of quality. Setting this argument to YES will not have any effect if the Scale Factor isn't below a threshold where it would be of benefit. Switching of this value from YES to NO is an expensive operation, and it's not recommended to use Draft Mode if the same image will need to be drawn without Draft Mode at a later time.
 */
extern NSString * const kCIInputAllowDraftModeKey  AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*!
 @const      kCIInputIgnoreImageOrientationKey
 @abstract   kCIInputIgnoreImageOrientationKey
 @discussion NSNumber (BOOL) : Normally, an image is loaded in its proper orientation, given the associated metadata gives an indication about the orientation. For special purposes it may be useful to load the image in its physical orientation. The exact meaning of this is dependent on the image in question. The default value is NO.
 */
extern NSString * const kCIInputIgnoreImageOrientationKey  AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*!
 @const      kCIInputImageOrientationKey
 @abstract   kCIInputImageOrientationKey
 @discussion NSNumber (int) : Overriding this value allows the user to change the orientation of the image. The valid values are in range 1...8 and follow the EXIF specification. Changing this value makes for instance rotation in 90-degree increments easy. The value is disregarded when the kCIInputIgnoreImageOrientationKey flag is set.
 */
extern NSString * const kCIInputImageOrientationKey  AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
 @const      kCIInputEnableSharpeningKey
 @abstract   kCIInputEnableSharpeningKey
 @discussion NSNumber (BOOL) : Determines if the default sharpening should be on. default = YES. Has no effect if the image used for initialization was not RAW.
 */
extern NSString * const kCIInputEnableSharpeningKey  AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
 @const      kCIInputEnableChromaticNoiseTrackingKey
 @abstract   kCIInputEnableChromaticNoiseTrackingKey
 @discussion NSNumber (BOOL) : Determines if progressive chromatic noise tracking (based on ISO and exposure time) should be used. default = YES. Has no effect if the image used for initialization was not RAW.
 */
extern NSString * const kCIInputEnableChromaticNoiseTrackingKey  AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
 @const      kCIInputBoostShadowAmountKey
 @abstract   kCIInputBoostShadowAmountKey
 @discussion NSNumber (float) : The amount to boost the shadow areas of the image. Can be used to lighten details in shadows. Has no effect if the image used for initialization was not RAW.
 */
extern NSString * const kCIInputBoostShadowAmountKey  AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
 @const      kCIInputBiasKey
 @abstract   kCIInputBiasKey
 @discussion NSNumber (float) : Simple bias to be used in conjunction with exposure adjustment (kCIInputEVKey). Has no effect if the image used for initialization was not RAW.
 */
extern NSString * const kCIInputBiasKey  AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
 @const      kCIOutputNativeSizeKey
 @abstract   kCIOutputNativeSizeKey
 @discussion CIVector containing the full native size of the unscaled image. The vector's X value is the width, Y is the height. This is not affected by changing either kCIInputIgnoreImageOrientationKey or kCIInputImageOrientationKey.
 */
extern NSString * const kCIOutputNativeSizeKey  AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

@end
