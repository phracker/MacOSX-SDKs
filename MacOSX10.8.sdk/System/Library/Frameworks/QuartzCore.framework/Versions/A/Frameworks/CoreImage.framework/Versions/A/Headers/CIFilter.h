/* CoreImage - CIFilter.h

   Copyright (c) 2004 Apple Computer, Inc.
   All rights reserved. */


#import <Foundation/Foundation.h>
#import <CoreImage/CoreImageDefines.h>
#import <CoreImage/CIFilterConstructor.h>

@class NSURL;



/* Filter attribute strings. */

/* Keys */

/** Name of the filter */
CORE_IMAGE_EXPORT NSString *kCIAttributeFilterName AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/** Name of the filter intended for UI display (eg. localized) */
CORE_IMAGE_EXPORT NSString *kCIAttributeFilterDisplayName AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/** Description of the filter intended for UI display (eg. localized) - Available in Leopard onwards. */
CORE_IMAGE_EXPORT NSString *kCIAttributeDescription AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/** URL for the reference documentation of the filter. See localizedReferenceDocumentationForFilterName - Available in Leopard onwards. */
CORE_IMAGE_EXPORT NSString *kCIAttributeReferenceDocumentation AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/** Array of filter category names (see below) */
CORE_IMAGE_EXPORT NSString *kCIAttributeFilterCategories AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/** Class name of the filter. */
CORE_IMAGE_EXPORT NSString *kCIAttributeClass AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/** The type of the attribute e.g. scalar, time, distance, etc. */
CORE_IMAGE_EXPORT NSString *kCIAttributeType AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/** Minimum value for the attribute. */
CORE_IMAGE_EXPORT NSString *kCIAttributeMin AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/** Maximum value for the attribute. */
CORE_IMAGE_EXPORT NSString *kCIAttributeMax AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/** Minimum value for the slider. */
CORE_IMAGE_EXPORT NSString *kCIAttributeSliderMin AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/** Maximum value for the slider. */
CORE_IMAGE_EXPORT NSString *kCIAttributeSliderMax AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/** Default value for the slider. */
CORE_IMAGE_EXPORT NSString *kCIAttributeDefault AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/** The identity value is the value at which the filter has no effect. */
CORE_IMAGE_EXPORT NSString *kCIAttributeIdentity AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/** The non-localized name of the attribute. */
CORE_IMAGE_EXPORT NSString *kCIAttributeName AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/** The localized name of the attribute to be used for display to the user. */
CORE_IMAGE_EXPORT NSString *kCIAttributeDisplayName AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/** Key to request the desired set of controls in a filter UIView - defined values are CIUISetBasic, CIUISetIntermediate, CIUISetAdvanced and CIUISetDevelopment. */
CORE_IMAGE_EXPORT NSString *kCIUIParameterSet AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/** Constant for requesting controls that are appropiate in an basic user scenario, meaning the bare minimum of settings to control the filter. */
CORE_IMAGE_EXPORT NSString *kCIUISetBasic AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/** Constant for requesting controls that are appropiate in an intermediate user scenario. */
CORE_IMAGE_EXPORT NSString *kCIUISetIntermediate AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/** Constant for requesting controls that are appropiate in an advanced user scenario. */
CORE_IMAGE_EXPORT NSString *kCIUISetAdvanced AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/** Constant for requesting controls that should only be visible for development purposes. */
CORE_IMAGE_EXPORT NSString *kCIUISetDevelopment AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/* Types for numbers */

CORE_IMAGE_EXPORT NSString *kCIAttributeTypeTime AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CORE_IMAGE_EXPORT NSString *kCIAttributeTypeScalar AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CORE_IMAGE_EXPORT NSString *kCIAttributeTypeDistance AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CORE_IMAGE_EXPORT NSString *kCIAttributeTypeAngle AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CORE_IMAGE_EXPORT NSString *kCIAttributeTypeBoolean AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/** Indicates that the key uses integer values. */
CORE_IMAGE_EXPORT NSString *kCIAttributeTypeInteger AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/** Indicates that the key uses non negative integer values. */
CORE_IMAGE_EXPORT NSString *kCIAttributeTypeCount AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* Types for 2-element vectors */
CORE_IMAGE_EXPORT NSString *kCIAttributeTypePosition AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CORE_IMAGE_EXPORT NSString *kCIAttributeTypeOffset AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Types for 3-element vectors */
CORE_IMAGE_EXPORT NSString *kCIAttributeTypePosition3 AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Types for 4-element vectors */
CORE_IMAGE_EXPORT NSString *kCIAttributeTypeRectangle AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Types for colors */
CORE_IMAGE_EXPORT NSString *kCIAttributeTypeOpaqueColor AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Types for images */
CORE_IMAGE_EXPORT NSString *kCIAttributeTypeGradient AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Categories */
CORE_IMAGE_EXPORT NSString *kCICategoryDistortionEffect AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CORE_IMAGE_EXPORT NSString *kCICategoryGeometryAdjustment AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CORE_IMAGE_EXPORT NSString *kCICategoryCompositeOperation AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CORE_IMAGE_EXPORT NSString *kCICategoryHalftoneEffect AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CORE_IMAGE_EXPORT NSString *kCICategoryColorAdjustment AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CORE_IMAGE_EXPORT NSString *kCICategoryColorEffect AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CORE_IMAGE_EXPORT NSString *kCICategoryTransition AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CORE_IMAGE_EXPORT NSString *kCICategoryTileEffect AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CORE_IMAGE_EXPORT NSString *kCICategoryGenerator AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CORE_IMAGE_EXPORT NSString *kCICategoryReduction AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
CORE_IMAGE_EXPORT NSString *kCICategoryGradient AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CORE_IMAGE_EXPORT NSString *kCICategoryStylize AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CORE_IMAGE_EXPORT NSString *kCICategorySharpen AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CORE_IMAGE_EXPORT NSString *kCICategoryBlur AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

CORE_IMAGE_EXPORT NSString *kCICategoryVideo AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CORE_IMAGE_EXPORT NSString *kCICategoryStillImage AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CORE_IMAGE_EXPORT NSString *kCICategoryInterlaced AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CORE_IMAGE_EXPORT NSString *kCICategoryNonSquarePixels AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CORE_IMAGE_EXPORT NSString *kCICategoryHighDynamicRange AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

CORE_IMAGE_EXPORT NSString *kCICategoryBuiltIn AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CORE_IMAGE_EXPORT NSString *kCICategoryFilterGenerator AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* Keys for apply: method options. */

CORE_IMAGE_EXPORT NSString *kCIApplyOptionExtent AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CORE_IMAGE_EXPORT NSString *kCIApplyOptionDefinition AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CORE_IMAGE_EXPORT NSString *kCIApplyOptionUserInfo AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* If used, the value of the kCIApplyOptionColorSpace key be must be an RGB CGColorSpaceRef.
 * Using this option specifies that the output of the kernel is in this color space. 
 * If not specified, the output of the kernel is in the working color space of the rendering CIContext. */
CORE_IMAGE_EXPORT NSString *kCIApplyOptionColorSpace AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* common filter parameter keys */

CORE_IMAGE_EXPORT NSString *kCIOutputImageKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
CORE_IMAGE_EXPORT NSString *kCIInputBackgroundImageKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
CORE_IMAGE_EXPORT NSString *kCIInputImageKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
CORE_IMAGE_EXPORT NSString *kCIInputTimeKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
CORE_IMAGE_EXPORT NSString *kCIInputTransformKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
CORE_IMAGE_EXPORT NSString *kCIInputScaleKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
CORE_IMAGE_EXPORT NSString *kCIInputAspectRatioKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
CORE_IMAGE_EXPORT NSString *kCIInputCenterKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
CORE_IMAGE_EXPORT NSString *kCIInputRadiusKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
CORE_IMAGE_EXPORT NSString *kCIInputAngleKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
CORE_IMAGE_EXPORT NSString *kCIInputRefractionKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
CORE_IMAGE_EXPORT NSString *kCIInputWidthKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
CORE_IMAGE_EXPORT NSString *kCIInputSharpnessKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
CORE_IMAGE_EXPORT NSString *kCIInputIntensityKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
CORE_IMAGE_EXPORT NSString *kCIInputEVKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
CORE_IMAGE_EXPORT NSString *kCIInputSaturationKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
CORE_IMAGE_EXPORT NSString *kCIInputColorKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
CORE_IMAGE_EXPORT NSString *kCIInputBrightnessKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
CORE_IMAGE_EXPORT NSString *kCIInputContrastKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
CORE_IMAGE_EXPORT NSString *kCIInputGradientImageKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
CORE_IMAGE_EXPORT NSString *kCIInputMaskImageKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
CORE_IMAGE_EXPORT NSString *kCIInputShadingImageKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
CORE_IMAGE_EXPORT NSString *kCIInputTargetImageKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
CORE_IMAGE_EXPORT NSString *kCIInputExtentKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


@class NSArray, NSDictionary;
@class CIKernel, CIImage;

/** CIFilter are filter objects for Core Image that encapsulate the filter with its attributes
 
 The CIFilter class produces a CIImage object as output. Typically, a filter takes one or more images as input. Some filters, however, generate an image based on other types of input parameters. The parameters of a CIFilter object are set and retrieved through the use of key-value pairs. You use the CIFilter object in conjunction with the CIImage, CIContext, CIVector, CIImageAccumulator, and CIColor objects to take advantage of the built-in Core Image filters when processing images. CIFilter objects are also used along with CIKernel, CISampler, and CIFilterShape objects to create custom filters. */
CORE_IMAGE_CLASS_EXPORT
@interface CIFilter : NSObject <NSCoding, NSCopying>
{
    void *_priv[8];
}

/** Returns an array containing the names of all inputs in the filter. */
- (NSArray *)inputKeys;

/** Returns an array containing the names of all outputs in the filter. */
- (NSArray *)outputKeys;

/** Sets all inputs to their default values (where default values are defined, other inputs are left as-is). */
- (void)setDefaults;

/** Returns a dictionary containing key/value pairs describing the filter. (see description of keys below) */
- (NSDictionary *)attributes;


/** Used by CIFilter subclasses to apply the array of argument values 'args' to the kernel function 'k'. The supplied arguments must be type-compatible with the function signature of the kernel.
 
 The key-value pairs defined by 'dict' (if non-nil) are used to control exactly how the kernel is evaluated. Valid keys include:
 kCIApplyOptionExtent: the size of the produced image. Value is a four element NSArray [X Y WIDTH HEIGHT].
 kCIApplyOptionDefinition: the Domain of Definition of the produced image. Value is either a CIFilterShape object, or a four element NSArray defining a rectangle.
 @param  k         CIKernel of the filter
 @param  args      Array of arguments that are applied to the kernel
 @param  options   Array of additional options
*/
- (CIImage *)apply:(CIKernel *)k
		 arguments:(NSArray *)args
		   options:(NSDictionary *)dict;

/** Similar to above except that all argument values and option key-value are specified inline. The list of key-value pairs must be terminated by the 'nil' object. */
- (CIImage *)apply:(CIKernel *)k, ... NS_REQUIRES_NIL_TERMINATION;

@end


/** Methods to register a filter and get access to the list of registered filters
 Use these methods to create filters and find filters. */
@interface CIFilter (CIFilterRegistry)

/** Creates a new filter of type 'name'. All input values will be undefined. */
+ (CIFilter *) filterWithName:(NSString *) name;

/** Creates a new filter of type 'name'.
 
 Convenience method that creates a filter objects with the specified key-value pairs set as input values on it; the argument list is terminated by a nil value.*/
+ (CIFilter *)filterWithName:(NSString *)name keysAndValues:key0, ... NS_REQUIRES_NIL_TERMINATION;

/** Returns an array containing all published filter names in a category. */
+ (NSArray *)filterNamesInCategory:(NSString *)category;

/** Returns an array containing all published filter names that belong to all listed categories. */
+ (NSArray *)filterNamesInCategories:(NSArray *)categories;


/** Publishes a new filter called 'name'.
 
 The constructor object 'anObject' should implement the filterWithName: method, it will be invoked with the name of the filter to create. The class attributes must have akCIAttributeFilterCategories key associated with a set of categories.
 @param   attributes    Dictionary of the registration attributes of the filter. See below for attribute keys.
*/
+ (void)registerFilterName:(NSString *)name
			   constructor:(id<CIFilterConstructor>)anObject
		   classAttributes:(NSDictionary *)attributes;


/** Returns the localized name of a filter for display in the UI. */
+ (NSString *)localizedNameForFilterName:(NSString *)filterName;

/** Returns the localized name of a category for display in the UI. */
+ (NSString *)localizedNameForCategory:(NSString *)category;

/** Returns the localized description of a filter for display in the UI. */
+ (NSString *)localizedDescriptionForFilterName:(NSString *)filterName;

/** Returns the URL to the localized reference documentation describing the filter.
    
 The URL can be a local file or a remote document on a webserver. It is possible, that this method returns nil (like filters that predate this feature). A client of this API has to handle this case gracefully. */
+ (NSURL *)localizedReferenceDocumentationForFilterName:(NSString *)filterName;

@end
