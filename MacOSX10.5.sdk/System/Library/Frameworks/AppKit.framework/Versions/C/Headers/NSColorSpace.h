/*
	NSColorSpace.h
	Application Kit
	Copyright (c) 2004-2007, Apple Inc.
	All rights reserved.
*/


#import <Foundation/NSObject.h>
#import <AppKit/AppKitDefines.h>
#import <ApplicationServices/ApplicationServices.h>

@class NSData;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4


enum {
    NSUnknownColorSpaceModel = -1,
    NSGrayColorSpaceModel,
    NSRGBColorSpaceModel,
    NSCMYKColorSpaceModel,
    NSLABColorSpaceModel,
    NSDeviceNColorSpaceModel,
    NSIndexedColorSpaceModel,
    NSPatternColorSpaceModel
};
typedef NSInteger NSColorSpaceModel;


@interface NSColorSpace : NSObject <NSCoding> {
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
    void *_reserved[5];    
}

- (id)initWithICCProfileData:(NSData *)iccData;
- (NSData *)ICCProfileData;

- (id)initWithColorSyncProfile:(void * /* CMProfileRef */)prof;
- (void * /* CMProfileRef */)colorSyncProfile;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
/* Create NSColorSpace from a CGColorSpace.  Might return nil if the CGColorSpace is one not supported by NSColorSpace. Internally the NSColorSpace might retain or create a new copy of the provided CGColorSpace; do not rely on pointer equality of the CGColorSpace provided to this function, when later queried. Archiving, for instance, might not persist the pointer equality/identity of the CGColorSpace.
*/
- (id)initWithCGColorSpace:(CGColorSpaceRef)cgColorSpace;

/* Might return NULL if the NSColorSpace space cannot be represented as a CGColorSpace.
*/
- (CGColorSpaceRef)CGColorSpace;
#endif

- (NSInteger)numberOfColorComponents;		// Does not include alpha
- (NSColorSpaceModel)colorSpaceModel;
- (NSString *)localizedName;			// Will return nil if no localized name

+ (NSColorSpace *)genericRGBColorSpace;		// NSColorSpace corresponding to Cocoa color space name NSCalibratedRGBColorSpace
+ (NSColorSpace *)genericGrayColorSpace;	// NSColorSpace corresponding to Cocoa color space name NSCalibratedWhiteColorSpace
+ (NSColorSpace *)genericCMYKColorSpace;
+ (NSColorSpace *)deviceRGBColorSpace;		// NSColorSpace corresponding to Cocoa color space name NSDeviceRGBColorSpace
+ (NSColorSpace *)deviceGrayColorSpace;		// NSColorSpace corresponding to Cocoa color space name NSDeviceWhiteColorSpace
+ (NSColorSpace *)deviceCMYKColorSpace;		// NSColorSpace corresponding to Cocoa color space name NSDeviceCMYKColorSpace

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
+ (NSColorSpace *)sRGBColorSpace;
+ (NSColorSpace *)adobeRGB1998ColorSpace;
#endif

@end



#endif
