//------------------------------------------------------------------------------------------------------------------------------
//
//  ICScannerBandData.h
//  ImageCaptureCore
//
//  Copyright (c) 2011 Apple Inc., all rights reserved.
//
//  Best viewed with the following settings: Tab width 4, Indent width 2, Wrap lines, Indent wrapped lines by 3, Page guide 128.
//
//------------------------------------------------------------------------------------------------------------------------------

#pragma once

#import <ImageCaptureCore/ICScannerFunctionalUnits.h>
#import <ImageCaptureCore/ImageCapturePlatform.h>

IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios)
@interface ICScannerBandData : NSObject

/*!
 @property fullImageWidth
 @abstract Describes the full image width of the banded image.
*/
@property (readonly) NSUInteger fullImageWidth IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @property fullImageHeight
 @abstract Describes the full image height of the banded image.
*/
@property (readonly) NSUInteger fullImageHeight IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @property bitsPerPixel
 @abstract Describes the number of bits per pixel for banded the image.
*/
@property (readonly) NSUInteger bitsPerPixel IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @property bitsPerComponent
 @abstract Describes the number of bits per component for the banded image.
*/
@property (readonly) NSUInteger bitsPerComponent IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @property numComponents
 @abstract Describes how many components are contained within the banded image.
*/
@property (readonly) NSUInteger numComponents IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @property bigEndian
 @abstract Describes if the banded image data is reported in big endian.
*/
@property (readonly, getter = isBigEndian) BOOL bigEndian IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @property pixelDataType
 @abstract Type of pixel data that is contained in the band.
*/
@property (readonly) ICScannerPixelDataType pixelDataType IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @property colorSyncProfilePath
 @abstract Returns the path to the color profile matching the banded data.
*/
@property (readonly, strong, nullable) NSString* colorSyncProfilePath IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @property bytesPerRow
 @abstract Descries how many bytes are in each image band row.
*/
@property (readonly) NSUInteger bytesPerRow IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @property dataStartRow
 @abstract Describes the start row of the image band.
*/
@property (readonly) NSUInteger dataStartRow IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @property dataNumRows
 @abstract Describes the number of rows contained in the image band.
*/
@property (readonly) NSUInteger dataNumRows IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @property dataSize
 @abstract Describes the actual data size of the image band buffer.
*/
@property (readonly) NSUInteger dataSize IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

/*!
 @property dataBuffer
 @abstract The pointer to the data buffer object.
*/
@property (readonly, strong, nullable) NSData* dataBuffer IC_AVAILABLE(macos(10.4)) IC_UNAVAILABLE(ios);

@end
