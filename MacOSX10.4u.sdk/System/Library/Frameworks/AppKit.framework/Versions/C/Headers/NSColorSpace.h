/*
	NSColorSpace.h
	Application Kit
	Copyright (c) 2004-2005, Apple Computer, Inc.
	All rights reserved.
*/


#import <Foundation/NSObject.h>
#import <AppKit/AppKitDefines.h>

@class NSData;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4


typedef enum {
    NSUnknownColorSpaceModel = -1,
    NSGrayColorSpaceModel,
    NSRGBColorSpaceModel,
    NSCMYKColorSpaceModel,
    NSLABColorSpaceModel,
    NSDeviceNColorSpaceModel
} NSColorSpaceModel;


@interface NSColorSpace : NSObject <NSCoding> {
    id _profile;
    struct {
	unsigned int colorSpaceID:8;
	unsigned int storageType:3;
	unsigned int replacedDuringUnarchiving:1;
	unsigned int :20;
    } _flags;
    void *__cgColorSpace;
    void *_reserved[5];    
}

- (id)initWithICCProfileData:(NSData *)iccData;
- (NSData *)ICCProfileData;

- (id)initWithColorSyncProfile:(void * /* CMProfileRef */)prof;
- (void * /* CMProfileRef */)colorSyncProfile;

- (int)numberOfColorComponents;			// Does not include alpha
- (NSColorSpaceModel)colorSpaceModel;
- (NSString *)localizedName;			// Will return nil if no localized name

+ (NSColorSpace *)genericRGBColorSpace;		// NSColorSpace corresponding to Cocoa color space name NSCalibratedRGBColorSpace
+ (NSColorSpace *)genericGrayColorSpace;	// NSColorSpace corresponding to Cocoa color space name NSCalibratedWhiteColorSpace
+ (NSColorSpace *)genericCMYKColorSpace;
+ (NSColorSpace *)deviceRGBColorSpace;		// NSColorSpace corresponding to Cocoa color space name NSDeviceRGBColorSpace
+ (NSColorSpace *)deviceGrayColorSpace;		// NSColorSpace corresponding to Cocoa color space name NSDeviceWhiteColorSpace
+ (NSColorSpace *)deviceCMYKColorSpace;		// NSColorSpace corresponding to Cocoa color space name NSDeviceCMYKColorSpace

@end



#endif
