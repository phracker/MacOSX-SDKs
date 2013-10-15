/*
	NSBitmapImageRep.h
	Application Kit
	Copyright (c) 1994-2011, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSImageRep.h>
#import <ApplicationServices/ApplicationServices.h>

@class CIImage;
@class NSColor;
@class NSColorSpace;

enum {
    NSTIFFCompressionNone		= 1,
    NSTIFFCompressionCCITTFAX3		= 3,		/* 1 bps only */
    NSTIFFCompressionCCITTFAX4		= 4,		/* 1 bps only */
    NSTIFFCompressionLZW		= 5,
    NSTIFFCompressionJPEG		= 6,		/* No longer supported for input or output */
    NSTIFFCompressionNEXT		= 32766,	/* Input only */
    NSTIFFCompressionPackBits		= 32773,
    NSTIFFCompressionOldJPEG		= 32865		/* No longer supported for input or output */
};
typedef NSUInteger NSTIFFCompression;

enum {
    NSTIFFFileType,
    NSBMPFileType,
    NSGIFFileType,
    NSJPEGFileType,
    NSPNGFileType,
    NSJPEG2000FileType
};
typedef NSUInteger NSBitmapImageFileType;

enum {
    NSImageRepLoadStatusUnknownType     = -1, // not enough data to determine image format. please feed me more data
    NSImageRepLoadStatusReadingHeader   = -2, // image format known, reading header. not yet valid. more data needed
    NSImageRepLoadStatusWillNeedAllData = -3, // can't read incrementally. will wait for complete data to become avail.
    NSImageRepLoadStatusInvalidData     = -4, // image decompression encountered error.
    NSImageRepLoadStatusUnexpectedEOF   = -5, // ran out of data before full image was decompressed.
    NSImageRepLoadStatusCompleted       = -6  // all is well, the full pixelsHigh image is valid.
};
typedef NSInteger NSImageRepLoadStatus;

enum {
    NSAlphaFirstBitmapFormat            = 1 << 0,       // 0 means is alpha last (RGBA, CMYKA, etc.)
    NSAlphaNonpremultipliedBitmapFormat = 1 << 1,       // 0 means is premultiplied
    NSFloatingPointSamplesBitmapFormat  = 1 << 2	// 0 is integer
};
typedef NSUInteger NSBitmapFormat;

APPKIT_EXTERN NSString* NSImageCompressionMethod;	// TIFF input/output (NSTIFFCompression in NSNumber)
APPKIT_EXTERN NSString* NSImageCompressionFactor;	// TIFF/JPEG input/output (float in NSNumber)
APPKIT_EXTERN NSString* NSImageDitherTransparency;	// GIF output (BOOL in NSNumber)
APPKIT_EXTERN NSString* NSImageRGBColorTable;		// GIF input/output (packed RGB in NSData)
APPKIT_EXTERN NSString* NSImageInterlaced;		// PNG output (BOOL in NSNumber)
APPKIT_EXTERN NSString* NSImageColorSyncProfileData;	// TIFF,GIF input/output (NSData)
APPKIT_EXTERN NSString* NSImageFrameCount;	// GIF input (int in NSNumber) (read-only)
APPKIT_EXTERN NSString* NSImageCurrentFrame;	// GIF input (int in NSNumber)
APPKIT_EXTERN NSString* NSImageCurrentFrameDuration;	// GIF input (float in NSNumber) (read-only)
APPKIT_EXTERN NSString* NSImageLoopCount            ;	// GIF input (int in NSNumber) (read-only)
APPKIT_EXTERN NSString* NSImageGamma                ;	// PNG input/output (float in NSNumber)
APPKIT_EXTERN NSString* NSImageProgressive          ;	// JPEG input/output (BOOL in NSNumber)
APPKIT_EXTERN NSString* NSImageEXIFData             ;	// JPEG input/output (NSDictionary)
APPKIT_EXTERN NSString* NSImageFallbackBackgroundColor  NS_AVAILABLE_MAC(10_5); // JPEG output (NSColor)

@interface NSBitmapImageRep : NSImageRep {
    /*All instance variables are private*/
    struct __bitmapRepFlags {
        unsigned int bitsPerPixel:8;	
	unsigned int isPlanar:1;
	unsigned int explicitPlanes:1;
	unsigned int imageSourceIsIndexed:1;
	unsigned int dataLoaded:1;
        unsigned int colorModel:4;
        unsigned int tierTwoInfoIsLoaded:1;
        unsigned int respectO:1;
        unsigned int compressionFactor:14;
        unsigned int imageNumber:8;
        unsigned int bitmapFormat:3;
        unsigned int cgImageIsPrimary:1;
	unsigned int compression:20;
    } _moreRepFlags;
    unsigned int _bytesPerRow;
    volatile id _dataObj;
    NSData *_tiffData;
    id _properties;
}

- (id)initWithFocusedViewRect:(NSRect)rect;

- (id)initWithBitmapDataPlanes:(unsigned char **)planes pixelsWide:(NSInteger)width pixelsHigh:(NSInteger)height bitsPerSample:(NSInteger)bps samplesPerPixel:(NSInteger)spp hasAlpha:(BOOL)alpha isPlanar:(BOOL)isPlanar colorSpaceName:(NSString *)colorSpaceName bytesPerRow:(NSInteger)rBytes bitsPerPixel:(NSInteger)pBits;
- (id)initWithBitmapDataPlanes:(unsigned char **)planes pixelsWide:(NSInteger)width pixelsHigh:(NSInteger)height bitsPerSample:(NSInteger)bps samplesPerPixel:(NSInteger)spp hasAlpha:(BOOL)alpha isPlanar:(BOOL)isPlanar colorSpaceName:(NSString *)colorSpaceName  bitmapFormat:(NSBitmapFormat)bitmapFormat bytesPerRow:(NSInteger)rBytes bitsPerPixel:(NSInteger)pBits;
- (id)initWithCGImage:(CGImageRef)cgImage NS_AVAILABLE_MAC(10_5);
- (id)initWithCIImage:(CIImage *)ciImage NS_AVAILABLE_MAC(10_5);

+ (NSArray *)imageRepsWithData:(NSData *)data;	/* some file formats can contain multiple images */

+ (id)imageRepWithData:(NSData *)data;	/* Convenience of initWithData: */
- (id)initWithData:(NSData *)data;

- (unsigned char *)bitmapData;
- (void)getBitmapDataPlanes:(unsigned char **)data;
- (BOOL)isPlanar;
- (NSInteger)samplesPerPixel;
- (NSInteger)bitsPerPixel;
- (NSInteger)bytesPerRow;
- (NSInteger)bytesPerPlane;
- (NSInteger)numberOfPlanes;
- (NSBitmapFormat)bitmapFormat;

- (void)getCompression:(NSTIFFCompression *)compression factor:(float *)factor;
- (void)setCompression:(NSTIFFCompression)compression factor:(float)factor;

- (NSData *)TIFFRepresentation;
- (NSData *)TIFFRepresentationUsingCompression:(NSTIFFCompression)comp factor:(float)factor;

+ (NSData *)TIFFRepresentationOfImageRepsInArray:(NSArray *)array;
+ (NSData *)TIFFRepresentationOfImageRepsInArray:(NSArray *)array usingCompression:(NSTIFFCompression)comp factor:(float)factor;

+ (void)getTIFFCompressionTypes:(const NSTIFFCompression **)list count:(NSInteger *)numTypes;
+ (NSString *)localizedNameForTIFFCompressionType:(NSTIFFCompression)compression;
- (BOOL)canBeCompressedUsing:(NSTIFFCompression)compression;

/* Support for colorization of grayscale images.  Maps the image such that:
Gray value of midPoint -> midPointColor, black -> shadowColor, white -> lightColor.
Works on images with 8-bit SPP; thus either 8-bit gray or 24-bit color (with optional alpha).
*/
- (void)colorizeByMappingGray:(CGFloat)midPoint toColor:(NSColor *)midPointColor blackMapping:(NSColor *)shadowColor whiteMapping:(NSColor *)lightColor;

- (id)initForIncrementalLoad;
- (NSInteger)incrementalLoadFromData:(NSData*)data complete:(BOOL)complete;

- (void)setColor:(NSColor*)color atX:(NSInteger)x y:(NSInteger)y;
- (NSColor*)colorAtX:(NSInteger)x y:(NSInteger)y;

- (void)getPixel:(NSUInteger[])p atX:(NSInteger)x y:(NSInteger)y;
- (void)setPixel:(NSUInteger[])p atX:(NSInteger)x y:(NSInteger)y;

- (CGImageRef)CGImage NS_AVAILABLE_MAC(10_5);


- (NSColorSpace *)colorSpace NS_AVAILABLE_MAC(10_6);

- (NSBitmapImageRep *)bitmapImageRepByConvertingToColorSpace:(NSColorSpace *)targetSpace renderingIntent:(NSColorRenderingIntent)renderingIntent NS_AVAILABLE_MAC(10_6);
- (NSBitmapImageRep *)bitmapImageRepByRetaggingWithColorSpace:(NSColorSpace *)newSpace NS_AVAILABLE_MAC(10_6);

@end


@interface NSBitmapImageRep (NSBitmapImageFileTypeExtensions)

+ (NSData *)representationOfImageRepsInArray:(NSArray *)imageReps usingType:(NSBitmapImageFileType)storageType properties:(NSDictionary *)properties;

- (NSData *)representationUsingType:(NSBitmapImageFileType)storageType properties:(NSDictionary *)properties;

- (void)setProperty:(NSString *)property withValue:(id)value;
- (id)valueForProperty:(NSString *)property;

@end
