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

//------------------------------------------------------------------------------------------------------------ ICScannerBandData

@interface ICScannerBandData : NSObject
{
    NSUInteger              _fullImageWidth;
    NSUInteger              _fullImageHeight;
    NSUInteger              _bitsPerPixel;
    NSUInteger              _bitsPerComponent;
    NSUInteger              _numComponents;
    BOOL                    _bigEndian;
    ICScannerPixelDataType  _pixelDataType;
    NSString*               _colorSyncProfilePath;
    NSUInteger              _bytesPerRow;
    NSUInteger              _dataStartRow;
    NSUInteger              _dataNumRows;
    NSUInteger              _dataSize;
    NSData*                 _dataBuffer;
}

/*!
 @property fullImageWidth
 @abstract Describes the full image width of the banded image.
 
 */
@property(readonly)                         NSUInteger              fullImageWidth;

/*!
 @property fullImageHeight
 @abstract Describes the full image height of the banded image.
 
 */
@property(readonly)                         NSUInteger              fullImageHeight;

/*!
 @property bitsPerPixel
 @abstract Describes the number of bits per pixel for banded the image.
 
 */
@property(readonly)                         NSUInteger              bitsPerPixel;

/*!
 @property bitsPerComponent
 @abstract Describes the number of bits per component for the banded image.
 
 */
@property(readonly)                         NSUInteger              bitsPerComponent;

/*!
 @property numComponents
 @abstract Describes how many components are contained within the banded image.
 
 */
@property(readonly)                         NSUInteger              numComponents;

/*!
 @property bigEndian
 @abstract Describes if the banded image data is reported in big endian.
 
 */
@property(readonly,getter=isBigEndian)      BOOL                    bigEndian;

/*!
 @property pixelDataType
 @abstract Type of pixel data that is contained in the band.
 
 */
@property(readonly)                         ICScannerPixelDataType  pixelDataType;

/*!
 @property colorSyncProfilePath
 @abstract Returns the path to the color profile matching the banded data.
 
 */
@property(readonly, retain, nullable)       NSString*               colorSyncProfilePath;

/*!
 @property bytesPerRow
 @abstract Descries how many bytes are in each image band row.
 
 */
@property(readonly)                         NSUInteger              bytesPerRow;

/*!
 @property dataStartRow
 @abstract Describes the start row of the image band.
 
 */
@property(readonly)                         NSUInteger              dataStartRow;

/*!
 @property dataNumRows
 @abstract Describes the number of rows contained in the image band.
 
 */
@property(readonly)                         NSUInteger              dataNumRows;

/*!
 @property dataSize
 @abstract Describes the actual data size of the image band buffer.
 
 */
@property(readonly)                         NSUInteger              dataSize;

/*!
 @property dataBuffer
 @abstract The pointer to the data buffer object.
 
 */
@property(readonly, retain, nullable)       NSData*                 dataBuffer;

@end

//------------------------------------------------------------------------------------------------------------------------------
