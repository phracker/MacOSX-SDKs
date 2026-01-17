//
//  ALAssetRepresentation.h
//  AssetsLibrary
//
//  Copyright 2010 Apple Inc. All rights reserved.
//
/*
 *
 * An ALAssetRepresentation encapsulates one of the representations of a given ALAsset.
 * For example: in the case of a camera shooting RAW + JPEG, the resulting asset will have two representations,
 *              one for the RAW file and one for the JPEG file.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <AssetsLibrary/AssetsLibrary.h>

OS_EXPORT AL_DEPRECATED(4, "Use PHImageRequestOptions with the PHImageManager from the Photos framework instead")
@interface ALAssetRepresentation : NSObject {
@package
    id _internal;
}

// Returns the representation's UTI.
- (NSString *)UTI AL_DEPRECATED(4, "Use requestImageDataForAsset:options:resultHandler: on PHImageManager for a PHAsset to request image data from the Photos framework and check the dataUTI passed to your result handler instead");

// Returns the dimensions of this representation.  If the representation does not have valid dimensions, this method will return CGSizeZero.
- (CGSize)dimensions AL_DEPRECATED(4, "Use requestImageForAsset:targetSize:contentMode:options:resultHandler: on PHImageManager to request a targetSize of image for a PHAsset from the Photos framework instead");

// Returns the size of the file for this representation. Callers can use this to allocate buffers of the right size for -getBytes:fromOffset:length:error:
- (long long)size AL_DEPRECATED(4, "Use requestImageDataForAsset:options:resultHandler: on PHImageManager to request image data for a PHAsset from the Photos framework instead");

// Copies the specified range of bytes into the buffer given by the caller.
// The method returns the number of bytes actually written to the buffer. The number of bytes read will be 
// less than the requested range if the range exceeds the file's size.
// If an error occurs, the method returns 0 and upon return contains an NSError object that describes the problem. Pass NULL if you do not want error information.
- (NSUInteger)getBytes:(uint8_t *)buffer fromOffset:(long long)offset length:(NSUInteger)length error:(NSError **)error AL_DEPRECATED(4, "Use requestImageDataForAsset:options:resultHandler: on PHImageManager to request image data for a PHAsset from the Photos framework instead");

// This is a convenience method for -[ALAssetRepresentation CGImageWithOptions:] where options is nil.
- (CGImageRef)fullResolutionImage AL_DEPRECATED(4, "Use requestImageForAsset:targetSize:contentMode:options:resultHandler: on PHImageManager to request a targetSize PHImageManagerMaximumSize for a PHAsset from the Photos framework instead");

// This is a convenience method that returns a full resolution CGImage of the representation. It takes a dictionary
// of options as described for CGImageSourceCreateWithData() or CGImageSourceCreateWithURL()
- (CGImageRef)CGImageWithOptions:(NSDictionary *)options AL_DEPRECATED(4, "Use requestImageForAsset:targetSize:contentMode:options:resultHandler: on PHImageManager to request a targetSize of image for a PHAsset from the Photos framework instead");

// Returns a CGImage of the representation that is appropriate for displaying full screen.
// The dimensions of this image will be dependent on the hardware that the application is running on and does not mean it will match the dimensions of the screen.
- (CGImageRef)fullScreenImage AL_DEPRECATED(4, "Use requestImageForAsset:targetSize:contentMode:options:resultHandler: on PHImageManager to request a targetSize of image for a PHAsset from the Photos framework instead");

// Returns a persistent URL uniquely identifying the representation
- (NSURL *)url AL_DEPRECATED(4, "Use PHImageRequestOptions with the PHImageManager instead");

// Returns a dictionary of dictionaries of metadata for the representation.
// If the representation is one that the system cannot interpret, nil is returned.
- (NSDictionary *)metadata AL_DEPRECATED(4, "Use CGImageSourceCopyPropertiesAtIndex() to retrieve metadata from an image returned by the PHImageManager from the Photos framework instead");

// Returns the representation's orientation as defined in ALAssetOrientation.
- (ALAssetOrientation)orientation AL_DEPRECATED(4, "Use the orientation of the UIImage returned for a PHAsset from the PHImageManager from the Photos framework instead");

// Returns the representation's scale.
- (float)scale AL_DEPRECATED(4, "Use requestImageForAsset:targetSize:contentMode:options:resultHandler: on PHImageManager to request a targetSize of image for a PHAsset from the Photos framework instead");

// Returns a string representing the filename of the representation on disk.  
// For representations synced from iTunes, this will be the filename of the representation on the host.
- (NSString *)filename AL_DEPRECATED(5, "Use the Photos framework instead");

@end
