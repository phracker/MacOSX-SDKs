/*
	NSBitmapImageRep.h
	Application Kit
	Copyright (c) 1994-2007, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSImageRep.h>
#import <ApplicationServices/ApplicationServices.h>

@class CIImage;
@class NSColor;

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
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
    NSJPEG2000FileType
#endif
};
typedef NSUInteger NSBitmapImageFileType;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2
enum {
    NSImageRepLoadStatusUnknownType     = -1, // not enough data to determine image format. please feed me more data
    NSImageRepLoadStatusReadingHeader   = -2, // image format known, reading header. not yet valid. more data needed
    NSImageRepLoadStatusWillNeedAllData = -3, // can't read incrementally. will wait for complete data to become avail.
    NSImageRepLoadStatusInvalidData     = -4, // image decompression encountered error.
    NSImageRepLoadStatusUnexpectedEOF   = -5, // ran out of data before full image was decompressed.
    NSImageRepLoadStatusCompleted       = -6  // all is well, the full pixelsHigh image is valid.
};
typedef NSInteger NSImageRepLoadStatus;
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
enum {
    NSAlphaFirstBitmapFormat            = 1 << 0,       // 0 means is alpha last (RGBA, CMYKA, etc.)
    NSAlphaNonpremultipliedBitmapFormat = 1 << 1,       // 0 means is premultiplied
    NSFloatingPointSamplesBitmapFormat  = 1 << 2	// 0 is integer
};
typedef NSUInteger NSBitmapFormat;
#endif

APPKIT_EXTERN NSString* NSImageCompressionMethod;	// TIFF input/output (NSTIFFCompression in NSNumber)
APPKIT_EXTERN NSString* NSImageCompressionFactor;	// TIFF/JPEG input/output (float in NSNumber)
APPKIT_EXTERN NSString* NSImageDitherTransparency;	// GIF output (BOOL in NSNumber)
APPKIT_EXTERN NSString* NSImageRGBColorTable;		// GIF input/output (packed RGB in NSData)
APPKIT_EXTERN NSString* NSImageInterlaced;		// PNG output (BOOL in NSNumber)
APPKIT_EXTERN NSString* NSImageColorSyncProfileData;	// TIFF,GIF input/output (NSData)
APPKIT_EXTERN NSString* NSImageFrameCount            AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;	// GIF input (int in NSNumber) (read-only)
APPKIT_EXTERN NSString* NSImageCurrentFrame          AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;	// GIF input (int in NSNumber)
APPKIT_EXTERN NSString* NSImageCurrentFrameDuration  AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;	// GIF input (float in NSNumber) (read-only)
APPKIT_EXTERN NSString* NSImageLoopCount             AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;	// GIF input (int in NSNumber) (read-only)
APPKIT_EXTERN NSString* NSImageGamma                 AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// PNG input/output (float in NSNumber)
APPKIT_EXTERN NSString* NSImageProgressive           AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// JPEG input/output (BOOL in NSNumber)
APPKIT_EXTERN NSString* NSImageEXIFData              AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// JPEG input/output (NSDictionary)
APPKIT_EXTERN NSString* NSImageFallbackBackgroundColor  AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER; // JPEG output (NSColor)

@interface NSBitmapImageRep : NSImageRep {
    /*All instance variables are private*/
    struct __bitmapRepFlags {
        unsigned int bitsPerPixel:8;	
	unsigned int isPlanar:1;
	unsigned int explicitPlanes:1;
	unsigned int isUnpacked:1;
	unsigned int dataLoaded:1;
        unsigned int numColors:4;	/* Cache */
        unsigned int memory:2;
        unsigned int compressionFactor:14;
        unsigned int imageNumber:8;
        unsigned int bitmapFormat:3;
        unsigned int cgImageIsPrimary:1;
	unsigned int compression:20;
    } _moreRepFlags;
    unsigned int _bytesPerRow;
    unsigned char *_data;
    NSData *_tiffData;
    id _properties;
}

- (id)initWithFocusedViewRect:(NSRect)rect;

- (id)initWithBitmapDataPlanes:(unsigned char **)planes pixelsWide:(NSInteger)width pixelsHigh:(NSInteger)height bitsPerSample:(NSInteger)bps samplesPerPixel:(NSInteger)spp hasAlpha:(BOOL)alpha isPlanar:(BOOL)isPlanar colorSpaceName:(NSString *)colorSpaceName bytesPerRow:(NSInteger)rBytes bitsPerPixel:(NSInteger)pBits; 
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
- (id)initWithBitmapDataPlanes:(unsigned char **)planes pixelsWide:(NSInteger)width pixelsHigh:(NSInteger)height bitsPerSample:(NSInteger)bps samplesPerPixel:(NSInteger)spp hasAlpha:(BOOL)alpha isPlanar:(BOOL)isPlanar colorSpaceName:(NSString *)colorSpaceName  bitmapFormat:(NSBitmapFormat)bitmapFormat bytesPerRow:(NSInteger)rBytes bitsPerPixel:(NSInteger)pBits; 
#endif
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
- (id)initWithCGImage:(CGImageRef)cgImage;
- (id)initWithCIImage:(CIImage *)ciImage;
#endif

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
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
- (NSBitmapFormat)bitmapFormat;
#endif

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

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2
- (id)initForIncrementalLoad;
- (NSInteger)incrementalLoadFromData:(NSData*)data complete:(BOOL)complete;
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
- (void)setColor:(NSColor*)color atX:(NSInteger)x y:(NSInteger)y;
- (NSColor*)colorAtX:(NSInteger)x y:(NSInteger)y;

- (void)getPixel:(NSUInteger[])p atX:(NSInteger)x y:(NSInteger)y;
- (void)setPixel:(NSUInteger[])p atX:(NSInteger)x y:(NSInteger)y;
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
- (CGImageRef)CGImage;
#endif
@end


@interface NSBitmapImageRep (NSBitmapImageFileTypeExtensions)

+ (NSData *)representationOfImageRepsInArray:(NSArray *)imageReps usingType:(NSBitmapImageFileType)storageType properties:(NSDictionary *)properties;

- (NSData *)representationUsingType:(NSBitmapImageFileType)storageType properties:(NSDictionary *)properties;

- (void)setProperty:(NSString *)property withValue:(id)value;
- (id)valueForProperty:(NSString *)property;

@end
