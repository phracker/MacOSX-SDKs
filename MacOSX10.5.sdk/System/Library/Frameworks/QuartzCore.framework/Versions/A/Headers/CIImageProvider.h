/* CoreImage - CIImageProvider.h

   Copyright (c) 2004 Apple Computer, Inc.
   All rights reserved. */

#import <QuartzCore/CIImage.h>

@class NSDictionary;

@interface CIImage (CIImageProvider)

/* Create a new CIImage lazily populated with with data provided by 'p' when
 * required. 'p' is retained until the image is deallocated. */

+ (CIImage *)imageWithImageProvider:(id)p size:(size_t)width:(size_t)height
    format:(CIFormat)f colorSpace:(CGColorSpaceRef)cs
    options:(NSDictionary *)dict;

- (id)initWithImageProvider:(id)p size:(size_t)width:(size_t)height
    format:(CIFormat)f colorSpace:(CGColorSpaceRef)cs
    options:(NSDictionary *)dict;

@end

/* Informal protocol used to lazily supply image data. */

@interface NSObject (CIImageProvider)

/* Callee should initialize the given bitmap with the subregion x,y
 * width,height of the image. (this subregion is defined in the image's
 * local coordinate space, i.e. the origin is the top left corner of
 * the image).
 *
 * Changing the virtual memory mapping of the supplied buffer (e.g. using
 * vm_copy () to modify it) will give undefined behavior. */

- (void)provideImageData:(void *)data bytesPerRow:(size_t)rowbytes
    origin:(size_t)x:(size_t)y size:(size_t)width:(size_t)height
    userInfo:(id)info;

@end

/* Options that may be supplied to image providers through the
 * dictionary. */

/* Either a single NSNumber of an NSArray containing two NSNumbers.
 * These values define the dimensions of the image tiles that will be
 * requested from the provider object. */

extern NSString *kCIImageProviderTileSize AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* The object passed to the provider object as the 'info' parameter of
 * methods. */

extern NSString *kCIImageProviderUserInfo AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
