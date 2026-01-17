/*
	NSColorSpace.h
	Application Kit
	Copyright (c) 2004-2015, Apple Inc.
	All rights reserved.
*/


#import <Foundation/NSObject.h>
#import <Foundation/NSArray.h>
#import <AppKit/AppKitDefines.h>
#import <ApplicationServices/ApplicationServices.h>

NS_ASSUME_NONNULL_BEGIN

@class NSData;



typedef NS_ENUM(NSInteger, NSColorSpaceModel) {
    NSUnknownColorSpaceModel = -1,
    NSGrayColorSpaceModel,
    NSRGBColorSpaceModel,
    NSCMYKColorSpaceModel,
    NSLABColorSpaceModel,
    NSDeviceNColorSpaceModel,
    NSIndexedColorSpaceModel,
    NSPatternColorSpaceModel
};


NS_AUTOMATED_REFCOUNT_WEAK_UNAVAILABLE
@interface NSColorSpace : NSObject <NSSecureCoding> {
    id _profile;
    struct {
	unsigned int colorSpaceID:8;
	unsigned int storageType:3;
	unsigned int replacedDuringUnarchiving:1;
	unsigned int :20;
#if __LP64__
	unsigned int :32;
#endif
    } _flags;
    void *__cgColorSpace;
    void *__cgColorTransform;
    void *_reserved[4];
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
@property (nullable, readonly, copy) NSString *localizedName;			// Will return nil if no localized name

+ (NSColorSpace *)genericRGBColorSpace;		// NSColorSpace corresponding to Cocoa color space name NSCalibratedRGBColorSpace
+ (NSColorSpace *)genericGrayColorSpace;	// NSColorSpace corresponding to Cocoa color space name NSCalibratedWhiteColorSpace
+ (NSColorSpace *)genericCMYKColorSpace;
+ (NSColorSpace *)deviceRGBColorSpace;		// NSColorSpace corresponding to Cocoa color space name NSDeviceRGBColorSpace
+ (NSColorSpace *)deviceGrayColorSpace;		// NSColorSpace corresponding to Cocoa color space name NSDeviceWhiteColorSpace
+ (NSColorSpace *)deviceCMYKColorSpace;		// NSColorSpace corresponding to Cocoa color space name NSDeviceCMYKColorSpace

+ (NSColorSpace *)sRGBColorSpace  NS_AVAILABLE_MAC(10_5);
+ (NSColorSpace *)genericGamma22GrayColorSpace  NS_AVAILABLE_MAC(10_6);  // The "generic" color space with gamma 2.2.

+ (NSColorSpace *)adobeRGB1998ColorSpace  NS_AVAILABLE_MAC(10_5);

/* Return the list of color spaces available on the system that are displayed by the color panel, in the order they are displayed in the color panel. Doesn't return arbitrary color spaces which may have been created on the fly, or spaces without user displayable names. Pass model==NSUnknownColorSpaceModel to get all color spaces. Empty array is returned if no color spaces are available for the specified model. 
*/
+ (NSArray<NSColorSpace *> *)availableColorSpacesWithModel:(NSColorSpaceModel)model  NS_AVAILABLE_MAC(10_6);

@end

NS_ASSUME_NONNULL_END



