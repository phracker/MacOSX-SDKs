//
//  ALAsset.h
//  AssetsLibrary
//
//  Copyright 2010 Apple Inc. All rights reserved.
//
/*
 *
 * An ALAsset represents a photo or a video managed by the Photos application. Assets can have multiple representations, like
 * a photo which has been shot in RAW and JPG. Furthermore, representations of the same asset may have different dimensions.
 *
 */

#import <Foundation/Foundation.h>
#import <AssetsLibrary/ALAssetsLibrary.h>
#import <CoreGraphics/CoreGraphics.h>

extern NSString *const ALErrorInvalidProperty AL_DEPRECATED(4, "Use PHAsset class properties from the Photos framework instead");

// Properties
extern NSString *const ALAssetPropertyType AL_DEPRECATED(4, "Use the mediaType property on a PHAsset from the Photos framework instead");             // An NSString that encodes the type of asset. One of ALAssetTypePhoto, ALAssetTypeVideo or ALAssetTypeUnknown.
extern NSString *const ALAssetPropertyLocation AL_DEPRECATED(4, "Use the location property on a PHAsset from the Photos framework instead");         // CLLocation object with the location information of the asset. Only available if location services are enabled for the caller.
extern NSString *const ALAssetPropertyDuration AL_DEPRECATED(4, "Use the duration property on a PHAsset from the Photos framework instead");         // Play time duration of a video asset expressed as a double wrapped in an NSNumber. For photos, kALErrorInvalidProperty is returned.
extern NSString *const ALAssetPropertyOrientation AL_DEPRECATED(4, "Use the orientation of the UIImage returned for a PHAsset via the PHImageManager from the Photos framework instead");      // NSNumber containing an asset's orientation as defined by ALAssetOrientation.
extern NSString *const ALAssetPropertyDate AL_DEPRECATED(4, "Use the creationDate property on a PHAsset from the Photos framework instead");             // An NSDate with the asset's creation date.

// Properties related to multiple photo representations
extern NSString *const ALAssetPropertyRepresentations AL_DEPRECATED(4, "Use PHImageRequestOptions with the PHImageManager from the Photos framework instead");  // Array with all the representations available for a given asset (e.g. RAW, JPEG). It is expressed as UTIs.
extern NSString *const ALAssetPropertyURLs AL_DEPRECATED(4, "Use PHImageRequestOptions with the PHImageManager from the Photos framework instead");             // Dictionary that maps asset representation UTIs to URLs that uniquely identify the asset.
extern NSString *const ALAssetPropertyAssetURL AL_DEPRECATED(4, "Use the localIdentifier property on a PHAsset (or to lookup PHAssets by a previously known ALAssetPropertyAssetURL use fetchAssetsWithALAssetURLs:options:) from the Photos framework instead");         // An NSURL that uniquely identifies the asset

// Asset types
extern NSString *const ALAssetTypePhoto AL_DEPRECATED(4, "Use PHAssetMediaTypeImage from the Photos framework instead");                // The asset is a photo
extern NSString *const ALAssetTypeVideo AL_DEPRECATED(4, "Use PHAssetMediaTypeVideo from the Photos framework instead");                // The asset is a video
extern NSString *const ALAssetTypeUnknown AL_DEPRECATED(4, "Use PHAssetMediaTypeAudio for audio or PHAssetMediaTypeUnknown for unknown media types from the Photos framework instead");              // The asset's type cannot be determined. It could be a sound file, a video or photo file that we don't know about, or something else. This is possible only for assets imported from a camera onto the device.

@class ALAssetRepresentation;

OS_EXPORT AL_DEPRECATED(4, "Use PHAsset from the Photos framework instead")
@interface ALAsset : NSObject {
@package
    id _internal;
}

// Returns the value for a given property (as defined above). Calling it with an invalid property returns a ALErrorInvalidProperty error.
- (id)valueForProperty:(NSString *)property AL_DEPRECATED(4, "Use PHAsset class properties from the Photos framework instead");

// Returns an ALAssetRepresentation object for the default representation of the ALAsset
- (ALAssetRepresentation *)defaultRepresentation AL_DEPRECATED(4, "Use PHImageRequestOptions with the PHImageManager from the Photos framework instead");

// Returns an ALAssetRepresentation object for the given representation UTI. If the ALAsset does not
// support the representation, nil is returned.
- (ALAssetRepresentation *)representationForUTI:(NSString *)representationUTI AL_DEPRECATED(4, "Use PHImageRequestOptions with the PHImageManager from the Photos framework instead");

// Returns a CGImage with a square thumbnail of the asset.  The size of the thumbnail is the appropriate size for the platform.  The thumbnail will be in the correct orientation.
- (CGImageRef)thumbnail AL_DEPRECATED(4, "Use requestImageForAsset:targetSize:contentMode:options:resultHandler: on PHImageManager to request a thumbnail sized image for a PHAsset from the Photos framework instead");

// Returns a CGImage with an aspect ratio thumbnail of the asset.  The size of the thumbnail is the appropriate size for the platform.  The thumbnail will be in the correct orientation.
- (CGImageRef)aspectRatioThumbnail AL_DEPRECATED(5, "Use the PHImageContentMode options to request thumbnail aspect ratio in PHImageRequestOptions with the PHImageManager");

// Saves image data to the saved photos album as a new ALAsset that is considered a modified version of the calling ALAsset.
- (void)writeModifiedImageDataToSavedPhotosAlbum:(NSData *)imageData metadata:(NSDictionary *)metadata completionBlock:(ALAssetsLibraryWriteImageCompletionBlock)completionBlock AL_DEPRECATED(5, "Use creationRequestForAssetFromImage: on PHAssetChangeRequest from the Photos framework to create a new asset instead");

// Saves the video at the specified path to the saved photos album as a new ALAsset that is considered a modified version of the calling ALAsset.
- (void)writeModifiedVideoAtPathToSavedPhotosAlbum:(NSURL *)videoPathURL completionBlock:(ALAssetsLibraryWriteVideoCompletionBlock)completionBlock AL_DEPRECATED(5, "Use creationRequestForAssetFromVideoAtFileURL: on PHAssetChangeRequest from the Photos framework to create a new asset instead");

// Returns the original asset if the caller was saved as a modified version of an asset.
// Returns nil if the caller was not saved as a modified version of an asset.
@property (nonatomic, readonly) ALAsset *originalAsset AL_DEPRECATED(5, "Use the PHImageRequestOptionsVersionOriginal or PHImageRequestOptionsVersionUnadjusted option in PHImageRequestOptions with the PHImageManager from the Photos framework instead");

// Returns YES if the application is able to edit the asset.  Returns NO if the application is not able to edit the asset.
// Applications are only allowed to edit assets that they originally wrote.
@property (nonatomic, readonly, getter=isEditable) BOOL editable AL_DEPRECATED(5, "Use canPerformEditOperation: on a PHAsset from the Photos framework instead");

// Replaces the image data in the calling asset with the supplied image data.
// The caller should check the editable property of the asset to see if it is possible to replace the image data.
// If the application is able to edit the asset, the completion block will return the same assetURL as the calling asset, since a new asset is not being created.
// If the application is not able to edit the asset, the completion block will return a nil assetURL and an ALAssetsLibraryWriteFailedError.
- (void)setImageData:(NSData *)imageData metadata:(NSDictionary *)metadata completionBlock:(ALAssetsLibraryWriteImageCompletionBlock)completionBlock AL_DEPRECATED(5, "Use contentEditingOutput on a PHAssetChangeRequest from the Photos framework instead");

// Replaces the video data in the calling asset with the video at the specified path.
// The caller should check the editable property of the asset to see if it is possible to replace the video data.
// If the application is able to edit the asset, the completion block will return the same assetURL as the calling asset, since a new asset is not being created.
// If the application is not able to edit the asset (see the editable property on ALAsset), the completion block will return a nil assetURL and an ALAssetsLibraryWriteFailedError.
- (void)setVideoAtPath:(NSURL *)videoPathURL completionBlock:(ALAssetsLibraryWriteVideoCompletionBlock)completionBlock AL_DEPRECATED(5, "Use contentEditingOutput on a PHAssetChangeRequest from the Photos framework instead");

@end
