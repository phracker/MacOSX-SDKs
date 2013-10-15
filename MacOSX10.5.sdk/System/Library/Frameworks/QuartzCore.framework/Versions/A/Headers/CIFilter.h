/* CoreImage - CIFilter.h

   Copyright (c) 2004 Apple Computer, Inc.
   All rights reserved. */

/* Remove these before shipping Leopard. */
#ifndef AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER
# define AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER
#endif
#ifndef DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER
# define DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER
#endif

/*!
    @header CIFilter
	@copyright 2004 Apple Computer, Inc. All rights reserved.
	@availability Coming to a Tiger installation near you
    @abstract   CIFilter are filter objects for CoreImage that encapsulate the filter with its attributes
*/

#import <Foundation/NSObject.h>

@class NSURL;

/* Filter attribute strings. */

/* Keys */
/*!
    @const      kCIAttributeFilterName
    @abstract   CIAttributeFilterName
    @discussion Name of the filter
*/
extern NSString *kCIAttributeFilterName AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*!
    @const      kCIAttributeFilterDisplayName
    @abstract   CIAttributeFilterDisplayName
    @discussion Name of the filter intended for UI display (eg. localized)
*/
extern NSString *kCIAttributeFilterDisplayName AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*!
    @const      kCIAttributeDescription
    @abstract   CIAttributeDescription
    @discussion Description of the filter intended for UI display (eg. localized) - Available in Leopard onwards.
*/
extern NSString *kCIAttributeDescription AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER; 
/*!
    @const      kCIAttributeReferenceDocumentation
    @abstract   CIAttributeReferenceDocumentation
    @discussion URL for the reference documentation of the filter. See localizedReferenceDocumentationForFilterName - Available in Leopard onwards.
*/
extern NSString *kCIAttributeReferenceDocumentation AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER; 
/*!
    @const      kCIAttributeFilterCategories
    @abstract   CIAttributeFilterCategories
    @discussion Array of filter category names (see below)
*/
extern NSString *kCIAttributeFilterCategories AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*!
    @const      kCIAttributeClass
    @abstract   CIAttributeClass
    @discussion Class name of the filter. 
*/
extern NSString *kCIAttributeClass AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*!
    @const      kCIAttributeType
    @abstract   CIAttributeType
    @discussion The type of the attribute e.g. scalar, time, distance, etc. 
*/
extern NSString *kCIAttributeType AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*!
    @const      kCIAttributeMin
    @abstract   CIAttributeMin
    @discussion Minimum value for the attribute. 
*/
extern NSString *kCIAttributeMin AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*!
    @const      kCIAttributeMax
    @abstract   CIAttributeMax
    @discussion Maximum value for the attribute. 
*/
extern NSString *kCIAttributeMax AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*!
    @const      kCIAttributeSliderMin
    @abstract   CIAttributeSliderMin
    @discussion Minimum value for the slider. 
*/
extern NSString *kCIAttributeSliderMin AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*!
    @const      kCIAttributeSliderMax
    @abstract   CIAttributeSliderMax
    @discussion Maximum value for the slider. 
*/
extern NSString *kCIAttributeSliderMax AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*!
    @const      kCIAttributeDefault
    @abstract   CIAttributeDefault
    @discussion Default value for the slider. 
*/
extern NSString *kCIAttributeDefault AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*!
    @const      kCIAttributeIdentity
    @abstract   CIAttributeIdentity
    @discussion The identity value is the value at which the filter has no effect. 
*/
extern NSString *kCIAttributeIdentity AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
    @const      kCIAttributeName
    @abstract   CIAttributeName
    @discussion The non-localized name of the attribute. 
*/
extern NSString *kCIAttributeName AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*!
    @const      kCIAttributeDisplayName
    @abstract   CIAttributeDisplayName
    @discussion The localized name of the attribute to be used for display to the user. 
*/
extern NSString *kCIAttributeDisplayName AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
    @const      kCIUIParameterSet
    @abstract   CIUIParameterSet
    @discussion Key to request the desired set of controls in a filter UIView - defined values are CIUISetBasic, CIUISetIntermediate, CIUISetAdvanced and CIUISetDevelopment.
*/
extern NSString *kCIUIParameterSet AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
    @const      kCIUISetBasic
    @abstract   CIUISetBasic
    @discussion Constant for requesting controls that are appropiate in an basic user scenario, meaning the bare minimum of settings to control the filter.
*/
extern NSString *kCIUISetBasic AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
    @const      kCIUISetIntermediate
    @abstract   CIUISetIntermediate
    @discussion Constant for requesting controls that are appropiate in an intermediate user scenario.
*/
extern NSString *kCIUISetIntermediate AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
    @const      kCIUISetAdvanced
    @abstract   CIUISetAdvanced
    @discussion Constant for requesting controls that are appropiate in an advanced user scenario.
*/
extern NSString *kCIUISetAdvanced AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
    @const      kCIUISetDevelopment
    @abstract   CIUISetDevelopment
    @discussion Constant for requesting controls that should only be visible for development purposes.
*/
extern NSString *kCIUISetDevelopment AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/* Types for numbers */
extern NSString *kCIAttributeTypeTime AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
extern NSString *kCIAttributeTypeScalar AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
extern NSString *kCIAttributeTypeDistance AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
extern NSString *kCIAttributeTypeAngle AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
extern NSString *kCIAttributeTypeBoolean AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*!
    @const      kCIAttributeTypeInteger
    @abstract   CIAttributeTypeInteger
    @discussion Indicates that the key uses integer values.
*/
extern NSString *kCIAttributeTypeInteger AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*!
    @const      kCIAttributeTypeCount
    @abstract   CIAttributeTypeCount
    @discussion Indicates that the key uses non negative integer values.
*/
extern NSString *kCIAttributeTypeCount AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* Types for 2-element vectors */
extern NSString *kCIAttributeTypePosition AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
extern NSString *kCIAttributeTypeOffset AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Types for 3-element vectors */
extern NSString *kCIAttributeTypePosition3 AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Types for 4-element vectors */
extern NSString *kCIAttributeTypeRectangle AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Types for colors */
extern NSString *kCIAttributeTypeOpaqueColor AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Types for images */
extern NSString *kCIAttributeTypeGradient AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Categories */
extern NSString *kCICategoryDistortionEffect AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
extern NSString *kCICategoryGeometryAdjustment AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
extern NSString *kCICategoryCompositeOperation AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
extern NSString *kCICategoryHalftoneEffect AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
extern NSString *kCICategoryColorAdjustment AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
extern NSString *kCICategoryColorEffect AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
extern NSString *kCICategoryTransition AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
extern NSString *kCICategoryTileEffect AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
extern NSString *kCICategoryGenerator AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
extern NSString *kCICategoryReduction AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern NSString *kCICategoryGradient AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
extern NSString *kCICategoryStylize AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
extern NSString *kCICategorySharpen AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
extern NSString *kCICategoryBlur AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

extern NSString *kCICategoryVideo AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
extern NSString *kCICategoryStillImage AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
extern NSString *kCICategoryInterlaced AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
extern NSString *kCICategoryNonSquarePixels AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
extern NSString *kCICategoryHighDynamicRange AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

extern NSString *kCICategoryBuiltIn AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
extern NSString *kCICategoryFilterGenerator AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* Keys for apply: method options. */

extern NSString *kCIApplyOptionExtent AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
extern NSString *kCIApplyOptionDefinition AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
extern NSString *kCIApplyOptionUserInfo AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* common filter parameter keys */

extern NSString *kCIOutputImageKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern NSString *kCIInputBackgroundImageKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern NSString *kCIInputImageKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern NSString *kCIInputTimeKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern NSString *kCIInputTransformKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern NSString *kCIInputScaleKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern NSString *kCIInputAspectRatioKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern NSString *kCIInputCenterKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern NSString *kCIInputRadiusKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern NSString *kCIInputAngleKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern NSString *kCIInputRefractionKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern NSString *kCIInputWidthKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern NSString *kCIInputSharpnessKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern NSString *kCIInputIntensityKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern NSString *kCIInputEVKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern NSString *kCIInputSaturationKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern NSString *kCIInputColorKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern NSString *kCIInputBrightnessKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern NSString *kCIInputContrastKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern NSString *kCIInputGradientImageKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern NSString *kCIInputMaskImageKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern NSString *kCIInputShadingImageKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern NSString *kCIInputTargetImageKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
extern NSString *kCIInputExtentKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


@class NSArray, NSDictionary;
@class CIKernel, CIImage;

/*!
    @class      CIFilter
    @abstract   CIFilter are filter objects for Core Image that encapsulate the filter with its attributes
    @discussion The CIFilter class produces a CIImage object as output. Typically, a filter takes one or more images as input. Some filters, however, generate an image based on other types of input parameters. The parameters of a CIFilter object are set and retrieved through the use of key-value pairs. You use the CIFilter object in conjunction with the CIImage, CIContext, CIVector, CIImageAccumulator, and CIColor objects to take advantage of the built-in Core Image filters when processing images. CIFilter objects are also used along with CIKernel, CISampler, and CIFilterShape objects to create custom filters.
*/
@interface CIFilter : NSObject <NSCoding, NSCopying>
{
    void *_priv[8];
}

/*!
    @method     inputKeys
    @abstract   Returns an array containing the names of all inputs in the filter.
    @result     NSArray of inputKeys
*/
- (NSArray *)inputKeys;
/*!
    @method     outputKeys
    @abstract   Returns an array containing the names of all outputs in the filter.
    @result     NSArray of outputKeys
*/
- (NSArray *)outputKeys;


/*!
    @method     setDefaults
    @abstract   Sets all inputs to their default values (where default values are defined, other inputs are left as-is).
*/
- (void)setDefaults;

/* Returns a dictionary containing key/value pairs describing the filter.
 * (see description of keys below). */

/*!
    @method     attributes
    @abstract   Returns a dictionary containing key/value pairs describing the filter. (see description of keys below)
    @result     NSDictionary with the filter attributes
*/
- (NSDictionary *)attributes;


/*!
    @method     apply:arguments:options:dict
    @abstract   Used by CIFilter subclasses to apply the array of argument values 'args' to the kernel function 'k'. The supplied arguments must be type-compatible with the function signature of the kernel.
    @discussion The key-value pairs defined by 'dict' (if non-nil) are used to control exactly how the kernel is evaluated. Valid keys include:
		kCIApplyOptionExtent: the size of the produced image. Value is a four element NSArray [X Y WIDTH HEIGHT].
 		kCIApplyOptionDefinition: the Domain of Definition of the produced image. Value is either a CIFilterShape object, or a four element NSArray defining a rectangle.
    @param      k   CIKernel of the filter
    @param      args    Array of arguments that are applied to the kernel
    @param      options    Array of additional options
    @return     CIImage
*/
- (CIImage *)apply:(CIKernel *)k arguments:(NSArray *)args
     options:(NSDictionary *)dict;

/* Similar to above except that all argument values and option key-value
 * are specified inline. The list of key-value pairs must be terminated
 * by the 'nil' object. */

/*!
    @method     apply:
    @abstract   Similar to above except that all argument values and option key-value are specified inline. The list of key-value pairs must be terminated by the 'nil' object.
    @return     CIImage
*/
- (CIImage *)apply:(CIKernel *)k, ...;

@end


/*!
    @category   CIFilterRegistry
    @abstract   Methods to register a filter and get access to the list of registered filters
    @discussion Use these methods to create filters and find filters.
*/
@interface CIFilter (CIFilterRegistry)

/*!
    @method     filterWithName
    @abstract   Creates a new filter of type 'name'. All input values will be undefined.
    @param      name    Name of the registered filter
    @result     filter object for the name if found.
*/
+ (CIFilter *)filterWithName:(NSString *)name;

/*!
    @method     filterWithName:keysAndValues
    @abstract   Creates a new filter of type 'name'. 
    @discussion Convenience method that creates a filter objects with the specified key-value pairs set as input values on it; the argument list is terminated by a nil value.
    @param      name    Name of the registered filter
    @param      keysAndValues	key value pairs for the inputKeys to be set on the filter
    @result     filter object for the name if found.
*/
+ (CIFilter *)filterWithName:(NSString *)name keysAndValues:key0, ...;

/*!
    @method     filterNamesInCategory
    @abstract   Returns an array containing all published filter names in a category.
    @param      category    Name of the category.
    @result     array of filters.
*/
+ (NSArray *)filterNamesInCategory:(NSString *)category;

/*!
    @method     filterNamesInCategories
    @abstract   Returns an array containing all published filter names that belong to all listed categories.
    @param      categories  Array of catagory names
    @result     array of filters.
*/
+ (NSArray *)filterNamesInCategories:(NSArray *)categories;


/*!
    @method     registerFilterName
    @abstract   Publishes a new filter called 'name'.
    @discussion The constructor object 'anObject' should implement the filterWithName: method, it will be invoked with the name of the filter to create. The class attributes must have akCIAttributeFilterCategories key associated with a set of categories.
    @param      name  Name of the filter
    @param      constructor Constructor object that responds to filterWithName
    @param      attributes  Dictionary of the registration attributes of the filter. See below for attribute keys.
*/
+ (void)registerFilterName:(NSString *)name constructor:(id)anObject
    classAttributes:(NSDictionary *)attributes;


/*!
    @method     localizedNameForFilterName
    @abstract   Returns the localized name of a filter for display in the UI.
    @param      filterName  Name of the filter
    @result     Localized name of the filter.
*/
+ (NSString *)localizedNameForFilterName: (NSString *)filterName;

/*!
    @method     localizedNameForCategory
    @abstract   Returns the localized name of a category for display in the UI.
    @param      category  Name of the category
    @result     Localized name of the category.
*/
+ (NSString *)localizedNameForCategory: (NSString *)category;

/*!
    @method     localizedDescriptionForFilterName
    @abstract   Returns the localized description of a filter for display in the UI.
    @param      filterName  Name of the filter
    @result     Localized description of the filter.
*/
+ (NSString *)localizedDescriptionForFilterName:(NSString *)filterName;

/*!
    @method     localizedReferenceDocForFilterName
    @abstract   Returns the URL to the localized reference documentation describing the filter.
	@discussion	The URL can be a local file or a remote document on a webserver. It is possible, that this method returns nil (like filters that predate this feature). A client of this API has to handle this case gracefully.
    @param      filterName  Name of the filter
    @result     Localized description of the filter.
*/
+ (NSURL *)localizedReferenceDocumentationForFilterName:(NSString *)filterName;

@end
