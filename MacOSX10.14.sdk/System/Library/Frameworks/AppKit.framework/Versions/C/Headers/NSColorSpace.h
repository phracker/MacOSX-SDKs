/*
	NSColorSpace.h
	Application Kit
	Copyright (c) 2004-2018, Apple Inc.
	All rights reserved.
*/


#import <Foundation/NSObject.h>
#import <Foundation/NSArray.h>
#import <AppKit/AppKitDefines.h>
#import <ApplicationServices/ApplicationServices.h>

NS_ASSUME_NONNULL_BEGIN

@class NSData;


typedef NS_ENUM(NSInteger, NSColorSpaceModel) {
    NSColorSpaceModelUnknown = -1,
    NSColorSpaceModelGray,
    NSColorSpaceModelRGB,
    NSColorSpaceModelCMYK,
    NSColorSpaceModelLAB,
    NSColorSpaceModelDeviceN,
    NSColorSpaceModelIndexed,
    NSColorSpaceModelPatterned
};


NS_AUTOMATED_REFCOUNT_WEAK_UNAVAILABLE
@interface NSColorSpace : NSObject <NSSecureCoding> {
    id _profile APPKIT_IVAR;
    struct {
	unsigned int colorSpaceID:8;
	unsigned int storageType:3;
	unsigned int replacedDuringUnarchiving:1;
	unsigned int :20;
#if __LP64__
	unsigned int :32;
#endif
    } _flags APPKIT_IVAR;
    void *__cgColorSpace APPKIT_IVAR;
    void *__cgColorTransform APPKIT_IVAR;
    void *_reserved[4] APPKIT_IVAR;
}

- (nullable instancetype)initWithICCProfileData:(NSData *)iccData;
@property (nullable, readonly, strong) NSData *ICCProfileData;

- (nullable instancetype)initWithColorSyncProfile:(void * /* ColorSyncProfileRef */)prof;
@property (nullable, readonly) void * /* ColorSyncProfileRef */colorSyncProfile NS_RETURNS_INNER_POINTER;

/* Create NSColorSpace from a CGColorSpace.  Might return nil if the CGColorSpace is one not supported by NSColorSpace. Internally the NSColorSpace might retain or create a new copy of the provided CGColorSpace; do not rely on pointer equality of the CGColorSpace provided to this function, when later queried. Archiving, for instance, might not persist the pointer equality/identity of the CGColorSpace.
*/
- (nullable instancetype)initWithCGColorSpace:(CGColorSpaceRef)cgColorSpace  NS_AVAILABLE_MAC(10_5);

/* Might return NULL if the NSColorSpace space cannot be represented as a CGColorSpace.
*/
@property (nullable, readonly) CGColorSpaceRef CGColorSpace  NS_AVAILABLE_MAC(10_5);

@property (readonly) NSInteger numberOfColorComponents;		// Does not include alpha
@property (readonly) NSColorSpaceModel colorSpaceModel;
@property (nullable, readonly, copy) NSString *localizedName;	// Will return nil if no localized name

@property (class, strong, readonly) NSColorSpace *sRGBColorSpace NS_AVAILABLE_MAC(10_5);
@property (class, strong, readonly) NSColorSpace *genericGamma22GrayColorSpace NS_AVAILABLE_MAC(10_6);             // The grayscale color space with gamma 2.2, compatible with sRGB

@property (class, strong, readonly) NSColorSpace *extendedSRGBColorSpace NS_AVAILABLE_MAC(10_12);                  // sRGB compatible color space that allows specifying components beyond the range of [0.0, 1.0]
@property (class, strong, readonly) NSColorSpace *extendedGenericGamma22GrayColorSpace NS_AVAILABLE_MAC(10_12);    // sRGB compatible gray color space that allows specifying components beyond the range of [0.0, 1.0]

@property (class, strong, readonly) NSColorSpace *displayP3ColorSpace NS_AVAILABLE_MAC(10_12);     // Standard DCI-P3 primaries, a D65 white point, and the same gamma curve as the sRGB IEC61966-2.1 color space

@property (class, strong, readonly) NSColorSpace *adobeRGB1998ColorSpace NS_AVAILABLE_MAC(10_5);

@property (class, strong, readonly) NSColorSpace *genericRGBColorSpace;		// NSColorSpace corresponding to Cocoa color space name NSCalibratedRGBColorSpace
@property (class, strong, readonly) NSColorSpace *genericGrayColorSpace;	// NSColorSpace corresponding to Cocoa color space name NSCalibratedWhiteColorSpace
@property (class, strong, readonly) NSColorSpace *genericCMYKColorSpace;
@property (class, strong, readonly) NSColorSpace *deviceRGBColorSpace;		// NSColorSpace corresponding to Cocoa color space name NSDeviceRGBColorSpace
@property (class, strong, readonly) NSColorSpace *deviceGrayColorSpace;		// NSColorSpace corresponding to Cocoa color space name NSDeviceWhiteColorSpace
@property (class, strong, readonly) NSColorSpace *deviceCMYKColorSpace;		// NSColorSpace corresponding to Cocoa color space name NSDeviceCMYKColorSpace

/* Return the list of color spaces available on the system that are displayed by the color panel, in the order they are displayed in the color panel. Doesn't return arbitrary color spaces which may have been created on the fly, or spaces without user displayable names. Pass model==NSUnknownColorSpaceModel to get all color spaces. Empty array is returned if no color spaces are available for the specified model.
*/
+ (NSArray<NSColorSpace *> *)availableColorSpacesWithModel:(NSColorSpaceModel)model  NS_AVAILABLE_MAC(10_6);

@end


static const NSColorSpaceModel NSUnknownColorSpaceModel NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSColorSpaceModelUnknown", 10_0, 10_14) = NSColorSpaceModelUnknown;
static const NSColorSpaceModel NSGrayColorSpaceModel NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSColorSpaceModelGray", 10_0, 10_14) = NSColorSpaceModelGray;
static const NSColorSpaceModel NSRGBColorSpaceModel NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSColorSpaceModelRGB", 10_0, 10_14) = NSColorSpaceModelRGB;
static const NSColorSpaceModel NSCMYKColorSpaceModel NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSColorSpaceModelCMYK", 10_0, 10_14) = NSColorSpaceModelCMYK;
static const NSColorSpaceModel NSLABColorSpaceModel NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSColorSpaceModelLAB", 10_0, 10_14) = NSColorSpaceModelLAB;
static const NSColorSpaceModel NSDeviceNColorSpaceModel NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSColorSpaceModelDeviceN", 10_0, 10_14) = NSColorSpaceModelDeviceN;
static const NSColorSpaceModel NSIndexedColorSpaceModel NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSColorSpaceModelIndexed", 10_0, 10_14) = NSColorSpaceModelIndexed;
static const NSColorSpaceModel NSPatternColorSpaceModel NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSColorSpaceModelPatterned", 10_0, 10_14) = NSColorSpaceModelPatterned;

NS_ASSUME_NONNULL_END



