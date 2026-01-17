/*
	NSBitmapImageRep.h
	Application Kit
	Copyright (c) 1994-2018, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>
#import <AppKit/NSImageRep.h>
#import <ApplicationServices/ApplicationServices.h>

NS_ASSUME_NONNULL_BEGIN

@class CIImage;
@class NSColor;
@class NSColorSpace;

typedef NS_ENUM(NSUInteger, NSTIFFCompression) {
    NSTIFFCompressionNone		= 1,
    NSTIFFCompressionCCITTFAX3		= 3,		/* 1 bps only */
    NSTIFFCompressionCCITTFAX4		= 4,		/* 1 bps only */
    NSTIFFCompressionLZW		= 5,
    NSTIFFCompressionJPEG		= 6,		/* No longer supported for input or output */
    NSTIFFCompressionNEXT		= 32766,	/* Input only */
    NSTIFFCompressionPackBits		= 32773,
    NSTIFFCompressionOldJPEG		= 32865		/* No longer supported for input or output */
};

typedef NS_ENUM(NSUInteger, NSBitmapImageFileType) {
    NSBitmapImageFileTypeTIFF,
    NSBitmapImageFileTypeBMP,
    NSBitmapImageFileTypeGIF,
    NSBitmapImageFileTypeJPEG,
    NSBitmapImageFileTypePNG,
    NSBitmapImageFileTypeJPEG2000
};

typedef NS_ENUM(NSInteger, NSImageRepLoadStatus) {
    NSImageRepLoadStatusUnknownType     = -1, // not enough data to determine image format. please feed me more data
    NSImageRepLoadStatusReadingHeader   = -2, // image format known, reading header. not yet valid. more data needed
    NSImageRepLoadStatusWillNeedAllData = -3, // can't read incrementally. will wait for complete data to become avail.
    NSImageRepLoadStatusInvalidData     = -4, // image decompression encountered error.
    NSImageRepLoadStatusUnexpectedEOF   = -5, // ran out of data before full image was decompressed.
    NSImageRepLoadStatusCompleted       = -6  // all is well, the full pixelsHigh image is valid.
};

typedef NS_OPTIONS(NSUInteger, NSBitmapFormat) {
    NSBitmapFormatAlphaFirst            = 1 << 0,       // 0 means is alpha last (RGBA, CMYKA, etc.)
    NSBitmapFormatAlphaNonpremultiplied = 1 << 1,       // 0 means is premultiplied
    NSBitmapFormatFloatingPointSamples  = 1 << 2,  // 0 is integer

    NSBitmapFormatSixteenBitLittleEndian NS_ENUM_AVAILABLE_MAC(10_10) = (1 << 8),
    NSBitmapFormatThirtyTwoBitLittleEndian NS_ENUM_AVAILABLE_MAC(10_10) = (1 << 9),
    NSBitmapFormatSixteenBitBigEndian NS_ENUM_AVAILABLE_MAC(10_10) = (1 << 10),
    NSBitmapFormatThirtyTwoBitBigEndian NS_ENUM_AVAILABLE_MAC(10_10) = (1 << 11)
};

typedef NSString * NSBitmapImageRepPropertyKey NS_TYPED_EXTENSIBLE_ENUM;

APPKIT_EXTERN NSBitmapImageRepPropertyKey NSImageCompressionMethod;       // TIFF input/output (NSTIFFCompression in NSNumber)
APPKIT_EXTERN NSBitmapImageRepPropertyKey NSImageCompressionFactor;	// TIFF/JPEG input/output (float in NSNumber)
APPKIT_EXTERN NSBitmapImageRepPropertyKey NSImageDitherTransparency;	// GIF output (BOOL in NSNumber)
APPKIT_EXTERN NSBitmapImageRepPropertyKey NSImageRGBColorTable;		// GIF input/output (packed RGB in NSData)
APPKIT_EXTERN NSBitmapImageRepPropertyKey NSImageInterlaced;                     // PNG output (BOOL in NSNumber)
APPKIT_EXTERN NSBitmapImageRepPropertyKey NSImageColorSyncProfileData; // TIFF,GIF input/output (NSData)
APPKIT_EXTERN NSBitmapImageRepPropertyKey NSImageFrameCount;                     // GIF input (int in NSNumber) (read-only)
APPKIT_EXTERN NSBitmapImageRepPropertyKey NSImageCurrentFrame;                 // GIF input (int in NSNumber)
APPKIT_EXTERN NSBitmapImageRepPropertyKey NSImageCurrentFrameDuration; // GIF input (float in NSNumber) (read-only)
APPKIT_EXTERN NSBitmapImageRepPropertyKey NSImageLoopCount;                       // GIF input (int in NSNumber) (read-only)
APPKIT_EXTERN NSBitmapImageRepPropertyKey NSImageGamma;                               // PNG input/output (float in NSNumber)
APPKIT_EXTERN NSBitmapImageRepPropertyKey NSImageProgressive;                   // JPEG input/output (BOOL in NSNumber)
APPKIT_EXTERN NSBitmapImageRepPropertyKey NSImageEXIFData;                         // JPEG input/output (NSDictionary)
APPKIT_EXTERN NSBitmapImageRepPropertyKey NSImageFallbackBackgroundColor NS_AVAILABLE_MAC(10_5); // JPEG output (NSColor)

@interface NSBitmapImageRep : NSImageRep <NSSecureCoding> {
    /*All instance variables are private*/
#if __OBJC2__
    unsigned int _bytesPerRow;
#endif /* __OBJC2__ */
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
    } _moreRepFlags APPKIT_IVAR;
#if !__OBJC2__
    unsigned int _bytesPerRow APPKIT_IVAR;
#endif /* !__OBJC2__ */
    volatile id _dataObj APPKIT_IVAR;
    NSData *_tiffData APPKIT_IVAR;
    id _properties APPKIT_IVAR;
}

- (nullable instancetype)initWithFocusedViewRect:(NSRect)rect NS_DEPRECATED_MAC(10_0, 10_14, "Use -[NSView cacheDisplayInRect:toBitmapImageRep:] to snapshot a view.");

- (nullable instancetype)initWithBitmapDataPlanes:(unsigned char *__nullable *__nullable)planes pixelsWide:(NSInteger)width pixelsHigh:(NSInteger)height bitsPerSample:(NSInteger)bps samplesPerPixel:(NSInteger)spp hasAlpha:(BOOL)alpha isPlanar:(BOOL)isPlanar colorSpaceName:(NSColorSpaceName)colorSpaceName bytesPerRow:(NSInteger)rBytes bitsPerPixel:(NSInteger)pBits;
- (nullable instancetype)initWithBitmapDataPlanes:(unsigned char *__nullable *__nullable)planes pixelsWide:(NSInteger)width pixelsHigh:(NSInteger)height bitsPerSample:(NSInteger)bps samplesPerPixel:(NSInteger)spp hasAlpha:(BOOL)alpha isPlanar:(BOOL)isPlanar colorSpaceName:(NSColorSpaceName)colorSpaceName  bitmapFormat:(NSBitmapFormat)bitmapFormat bytesPerRow:(NSInteger)rBytes bitsPerPixel:(NSInteger)pBits;
- (instancetype)initWithCGImage:(CGImageRef)cgImage NS_AVAILABLE_MAC(10_5);
- (instancetype)initWithCIImage:(CIImage *)ciImage NS_AVAILABLE_MAC(10_5);

+ (NSArray<NSImageRep *> *)imageRepsWithData:(NSData *)data;	/* some file formats can contain multiple images */

+ (nullable instancetype)imageRepWithData:(NSData *)data;	/* Convenience of initWithData: */
- (nullable instancetype)initWithData:(NSData *)data;

@property (nullable, readonly) unsigned char *bitmapData NS_RETURNS_INNER_POINTER;
- (void)getBitmapDataPlanes:(unsigned char *__nullable *__nonnull)data;

@property (getter=isPlanar, readonly) BOOL planar;
@property (readonly) NSInteger samplesPerPixel;
@property (readonly) NSInteger bitsPerPixel;
@property (readonly) NSInteger bytesPerRow;
@property (readonly) NSInteger bytesPerPlane;
@property (readonly) NSInteger numberOfPlanes;
@property (readonly) NSBitmapFormat bitmapFormat;

- (void)getCompression:(nullable NSTIFFCompression *)compression factor:(nullable float *)factor;
- (void)setCompression:(NSTIFFCompression)compression factor:(float)factor;

@property (nullable, readonly, copy) NSData *TIFFRepresentation;
- (nullable NSData *)TIFFRepresentationUsingCompression:(NSTIFFCompression)comp factor:(float)factor;

+ (nullable NSData *)TIFFRepresentationOfImageRepsInArray:(NSArray<NSImageRep *> *)array;
+ (nullable NSData *)TIFFRepresentationOfImageRepsInArray:(NSArray<NSImageRep *> *)array usingCompression:(NSTIFFCompression)comp factor:(float)factor;

+ (void)getTIFFCompressionTypes:(const NSTIFFCompression * __nullable * __nonnull)list count:(NSInteger *)numTypes;
+ (nullable NSString *)localizedNameForTIFFCompressionType:(NSTIFFCompression)compression;
- (BOOL)canBeCompressedUsing:(NSTIFFCompression)compression;

/* Support for colorization of grayscale images.  Maps the image such that:
Gray value of midPoint -> midPointColor, black -> shadowColor, white -> lightColor.
Works on images with 8-bit SPP; thus either 8-bit gray or 24-bit color (with optional alpha).
*/
- (void)colorizeByMappingGray:(CGFloat)midPoint toColor:(nullable NSColor *)midPointColor blackMapping:(nullable NSColor *)shadowColor whiteMapping:(nullable NSColor *)lightColor;

- (instancetype)initForIncrementalLoad;
- (NSInteger)incrementalLoadFromData:(NSData*)data complete:(BOOL)complete;

- (void)setColor:(NSColor*)color atX:(NSInteger)x y:(NSInteger)y;
- (nullable NSColor *)colorAtX:(NSInteger)x y:(NSInteger)y;

- (void)getPixel:(NSUInteger[__nonnull])p atX:(NSInteger)x y:(NSInteger)y;
- (void)setPixel:(NSUInteger[__nonnull])p atX:(NSInteger)x y:(NSInteger)y;

@property (nullable, readonly) CGImageRef CGImage NS_AVAILABLE_MAC(10_5);


@property (readonly, strong) NSColorSpace *colorSpace NS_AVAILABLE_MAC(10_6);

- (nullable NSBitmapImageRep *)bitmapImageRepByConvertingToColorSpace:(NSColorSpace *)targetSpace renderingIntent:(NSColorRenderingIntent)renderingIntent NS_AVAILABLE_MAC(10_6);
- (nullable NSBitmapImageRep *)bitmapImageRepByRetaggingWithColorSpace:(NSColorSpace *)newSpace NS_AVAILABLE_MAC(10_6);

@end


@interface NSBitmapImageRep (NSBitmapImageFileTypeExtensions)

+ (nullable NSData *)representationOfImageRepsInArray:(NSArray<NSImageRep *> *)imageReps usingType:(NSBitmapImageFileType)storageType properties:(NSDictionary<NSBitmapImageRepPropertyKey, id> *)properties;

- (nullable NSData *)representationUsingType:(NSBitmapImageFileType)storageType properties:(NSDictionary<NSBitmapImageRepPropertyKey, id> *)properties;

- (void)setProperty:(NSBitmapImageRepPropertyKey)property withValue:(nullable id)value;
- (nullable id)valueForProperty:(NSBitmapImageRepPropertyKey)property;

@end


static const NSBitmapImageFileType NSTIFFFileType NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSBitmapImageFileTypeTIFF", 10_0, 10_14) = NSBitmapImageFileTypeTIFF;
static const NSBitmapImageFileType NSBMPFileType NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSBitmapImageFileTypeBMP", 10_0, 10_14) = NSBitmapImageFileTypeBMP;
static const NSBitmapImageFileType NSGIFFileType NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSBitmapImageFileTypeGIF", 10_0, 10_14) = NSBitmapImageFileTypeGIF;
static const NSBitmapImageFileType NSJPEGFileType NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSBitmapImageFileTypeJPEG", 10_0, 10_14) = NSBitmapImageFileTypeJPEG;
static const NSBitmapImageFileType NSPNGFileType NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSBitmapImageFileTypePNG", 10_0, 10_14) = NSBitmapImageFileTypePNG;
static const NSBitmapImageFileType NSJPEG2000FileType NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSBitmapImageFileTypeJPEG2000", 10_0, 10_14) = NSBitmapImageFileTypeJPEG2000;

static const NSBitmapFormat NSAlphaFirstBitmapFormat NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSBitmapFormatAlphaFirst", 10_5, 10_14) = NSBitmapFormatAlphaFirst;
static const NSBitmapFormat NSAlphaNonpremultipliedBitmapFormat NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSBitmapFormatAlphaNonpremultiplied", 10_0, 10_14) = NSBitmapFormatAlphaNonpremultiplied;
static const NSBitmapFormat NSFloatingPointSamplesBitmapFormat NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSBitmapFormatFloatingPointSamples", 10_0, 10_14) = NSBitmapFormatFloatingPointSamples;
static const NSBitmapFormat NS16BitLittleEndianBitmapFormat NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSBitmapFormatSixteenBitLittleEndian", 10_5, 10_14) = NSBitmapFormatSixteenBitLittleEndian;
static const NSBitmapFormat NS32BitLittleEndianBitmapFormat NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSBitmapFormatThirtyTwoBitLittleEndian", 10_0, 10_14) = NSBitmapFormatThirtyTwoBitLittleEndian;
static const NSBitmapFormat NS16BitBigEndianBitmapFormat NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSBitmapFormatSixteenBitBigEndian", 10_0, 10_14) = NSBitmapFormatSixteenBitBigEndian;
static const NSBitmapFormat NS32BitBigEndianBitmapFormat NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSBitmapFormatThirtyTwoBitBigEndian", 10_0, 10_14) = NSBitmapFormatThirtyTwoBitBigEndian;


NS_ASSUME_NONNULL_END
