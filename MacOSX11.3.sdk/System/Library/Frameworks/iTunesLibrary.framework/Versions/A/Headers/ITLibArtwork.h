/*!
	@file		ITLibArtwork.h
	@copyright	© 2012-2020 Apple Inc.
 */

#import <Foundation/Foundation.h>
#import <iTunesLibrary/ITLibDefines.h>

@class NSImage;

NS_ASSUME_NONNULL_BEGIN

/*!
	@enum		ITLibArtworkFormat	
    @abstract	These constants specify the possible formats of the data returned by ITLibArtwork's imageData method.
    @constant	ITLibArtworkFormatNone 
					The image data format is unknown.
	@constant	ITLibArtworkFormatBitmap
					The image data format is a bitmap.
	@constant	ITLibArtworkFormatJPEG
					The image data corresponds to a JPEG image.
	@constant	ITLibArtworkFormatJPEG2000
					The image data corresponds to a JPEG2000 image.
	@constant	ITLibArtworkFormatGIF
					The image data corresponds to a GIF image.
	@constant	ITLibArtworkFormatPNG
					The image data corresponds to a PNG image.
	@constant	ITLibArtworkFormatBMP
					The image data corresponds to a BMP image.
	@constant	ITLibArtworkFormatTIFF
					The image data corresponds to a TIFF image.
	@constant	ITLibArtworkFormatPICT
					The image data corresponds to a PICT image.
 */
typedef NS_ENUM( NSUInteger, ITLibArtworkFormat )
{
	ITLibArtworkFormatNone = 0,
	ITLibArtworkFormatBitmap = 1,
	ITLibArtworkFormatJPEG = 2, 
	ITLibArtworkFormatJPEG2000 = 3, 
	ITLibArtworkFormatGIF = 4, 
	ITLibArtworkFormatPNG = 5, 
	ITLibArtworkFormatBMP = 6, 
	ITLibArtworkFormatTIFF = 7, 
	ITLibArtworkFormatPICT = 8

} API_UNAVAILABLE(ios);

/*!
	@abstract The ITLibArtwork class represents a media item artwork.
 */
API_UNAVAILABLE(ios)
ITLIB_EXPORT @interface ITLibArtwork : NSObject
{
	void * _impl;
	NSImage* _cachedImage;
}

/*! @abstract The NSImage formed by calling [[NSImage alloc] initWithData:self.imageData]. */
@property (readonly, nonatomic, retain, nullable) NSImage* image;

/*! @abstract The data (bytes) of this artwork image. */
@property (readonly, nonatomic, retain, nullable) NSData* imageData;

/*! @abstract The fortmat of the data returned by the imageData method. */
@property (readonly, nonatomic, assign) ITLibArtworkFormat imageDataFormat;

@end

NS_ASSUME_NONNULL_END
