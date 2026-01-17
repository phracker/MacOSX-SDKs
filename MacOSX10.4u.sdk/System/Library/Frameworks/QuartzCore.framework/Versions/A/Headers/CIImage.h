/* CoreImage - CIImage.h

   Copyright (c) 2004 Apple Computer, Inc.
   All rights reserved. */

#import <Foundation/NSObject.h>
#import <ApplicationServices/ApplicationServices.h>
#import <QuartzCore/CVImageBuffer.h>

@class NSData, NSURL, NSDictionary, CIContext, CIFilterShape;

@interface CIImage : NSObject <NSCoding, NSCopying>
{
    void *_state;
    void *_priv;
}

/* Pixel formats. */

typedef int CIFormat;

extern CIFormat kCIFormatARGB8	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
extern CIFormat kCIFormatRGBA16	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
extern CIFormat kCIFormatRGBAf	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Image dictionary keys. */

/* A CGColorSpaceRef defining the color space of the image. This value
 * overrides the image's implicit color space. */

extern NSString *kCIImageColorSpace AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Creates a new image from the contents of 'image'. */

+ (CIImage *)imageWithCGImage:(CGImageRef)image;
+ (CIImage *)imageWithCGImage:(CGImageRef)image options:(NSDictionary *)d;

/* Creates a new image from the contents of 'layer'. */

+ (CIImage *)imageWithCGLayer:(CGLayerRef)layer;
+ (CIImage *)imageWithCGLayer:(CGLayerRef)layer options:(NSDictionary *)d;

/* Creates a new image whose bitmap data is from 'd'. Each row contains 'bpr'
 * bytes. The dimensions of the image are defined by 'size'. 'f' defines
 * the format and size of each pixel. 'cs' defines the color space
 * that the image is defined in, if nil, the image is not color matched. */

+ (CIImage *)imageWithBitmapData:(NSData *)d bytesPerRow:(size_t)bpr
    size:(CGSize)size format:(CIFormat)f colorSpace:(CGColorSpaceRef)cs;

/* Creates a new image referencing the contents of the GL texture object
 * with identifier 'name'. The texture should have dimensions as defined
 * by 'size'. If 'flag' is true, then the contents of the texture are
 * flipped vertically when referenced. 'cs' defines the color space
 * that the image is defined in, if nil, the texture is not color matched.*/

+ (CIImage *)imageWithTexture:(unsigned int)name size:(CGSize)size
    flipped:(BOOL)flag colorSpace:(CGColorSpaceRef)cs;

+ (CIImage *)imageWithContentsOfURL: (NSURL *)url;
+ (CIImage *)imageWithContentsOfURL: (NSURL *)url options:(NSDictionary *)d;

+ (CIImage *)imageWithData: (NSData *)data;
+ (CIImage *)imageWithData: (NSData *)data options:(NSDictionary *)d;

/* Creates a new image whose data is from the contents of a CVImageBuffer. */

+ (CIImage *)imageWithCVImageBuffer:(CVImageBufferRef)imageBuffer;
+ (CIImage *)imageWithCVImageBuffer:(CVImageBufferRef)imageBuffer
    options:(NSDictionary *)dict;

/* Initializers. */

- (id)initWithCGImage:(CGImageRef)image;
- (id)initWithCGImage:(CGImageRef)image options:(NSDictionary *)d;

- (id)initWithCGLayer:(CGLayerRef)layer;
- (id)initWithCGLayer:(CGLayerRef)layer options:(NSDictionary *)d;

- (id)initWithData:(NSData *)data;
- (id)initWithData:(NSData *)data  options:(NSDictionary *)d;

- (id)initWithBitmapData:(NSData *)d bytesPerRow:(size_t)bpr size:(CGSize)size
    format:(CIFormat)f colorSpace:(CGColorSpaceRef)c;

- (id)initWithTexture:(unsigned int)name size:(CGSize)size flipped:(BOOL)flag
    colorSpace:(CGColorSpaceRef)cs;

- (id)initWithContentsOfURL: (NSURL *)url;
- (id)initWithContentsOfURL: (NSURL *)url options:(NSDictionary *)d;

- (id)initWithCVImageBuffer:(CVImageBufferRef)imageBuffer;
- (id)initWithCVImageBuffer:(CVImageBufferRef)imageBuffer
    options:(NSDictionary *)dict;

/* Returns a new image representing the original image with the transform
 * 'matrix' appended to it. */

- (CIImage *)imageByApplyingTransform:(CGAffineTransform)matrix;

/* The extent of the image in world coordinates. */

- (CGRect)extent;

/* Return the Domain of Definition of the image. */

- (CIFilterShape *)definition;

@end
