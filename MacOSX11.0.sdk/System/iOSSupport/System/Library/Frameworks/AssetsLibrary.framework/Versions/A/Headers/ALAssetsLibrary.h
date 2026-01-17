//
//  ALAssetsLibrary.h
//  AssetsLibrary
//
//  Copyright 2010 Apple Inc. All rights reserved.
//
/*
 *
 * This class represents the set of all videos and photos that are under the control of the Photos application. This includes
 * those that are in the saved photos album and those coming from iTunes.
 * It is used to retrieve the list of all asset groups and to save images and videos into the Saved Photos album.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>

#define AL_DEPRECATED(x,msg) API_DEPRECATED(msg, ios(x,9)) API_UNAVAILABLE(macos)

@class ALAsset;
@class ALAssetsGroup;

typedef NS_ENUM(NSInteger, ALAssetOrientation) {
    ALAssetOrientationUp AL_DEPRECATED(4, "Use UIImageOrientation in the Photos framework instead"),            // default orientation
    ALAssetOrientationDown AL_DEPRECATED(4, "Use UIImageOrientation in the Photos framework instead"),          // 180 deg rotation
    ALAssetOrientationLeft AL_DEPRECATED(4, "Use UIImageOrientation in the Photos framework instead"),          // 90 deg CCW
    ALAssetOrientationRight AL_DEPRECATED(4, "Use UIImageOrientation in the Photos framework instead"),         // 90 deg CW
    ALAssetOrientationUpMirrored AL_DEPRECATED(4, "Use UIImageOrientation in the Photos framework instead"),    // as above but image mirrored along other axis. horizontal flip
    ALAssetOrientationDownMirrored AL_DEPRECATED(4, "Use UIImageOrientation in the Photos framework instead"),  // horizontal flip
    ALAssetOrientationLeftMirrored AL_DEPRECATED(4, "Use UIImageOrientation in the Photos framework instead"),  // vertical flip
    ALAssetOrientationRightMirrored AL_DEPRECATED(4, "Use UIImageOrientation in the Photos framework instead"), // vertical flip
} AL_DEPRECATED(4, "Use UIImageOrientation in the Photos framework instead");

enum {
    ALAssetsGroupLibrary     AL_DEPRECATED(4, "Use PHAssetCollectionType and PHAssetCollectionSubtype in the Photos framework instead") = (1 << 0),         // The Library group that includes all assets.
    ALAssetsGroupAlbum       AL_DEPRECATED(4, "Use PHAssetCollectionType and PHAssetCollectionSubtype in the Photos framework instead") = (1 << 1),         // All the albums synced from iTunes or created on the device.
    ALAssetsGroupEvent       AL_DEPRECATED(4, "Use PHAssetCollectionType and PHAssetCollectionSubtype in the Photos framework instead") = (1 << 2),         // All the events synced from iTunes.
    ALAssetsGroupFaces       AL_DEPRECATED(4, "Use PHAssetCollectionType and PHAssetCollectionSubtype in the Photos framework instead") = (1 << 3),         // All the faces albums synced from iTunes.
    ALAssetsGroupSavedPhotos AL_DEPRECATED(4, "Use PHAssetCollectionType and PHAssetCollectionSubtype in the Photos framework instead") = (1 << 4),         // The Saved Photos album.
    ALAssetsGroupPhotoStream AL_DEPRECATED(5, "Use PHAssetCollectionType and PHAssetCollectionSubtype in the Photos framework instead") = (1 << 5),         // The PhotoStream album.
    ALAssetsGroupAll         AL_DEPRECATED(4, "Use PHAssetCollectionType and PHAssetCollectionSubtype in the Photos framework instead") = 0xFFFFFFFF,       // The same as ORing together all the available group types,
};
typedef NSUInteger ALAssetsGroupType AL_DEPRECATED(4, "Use PHAssetCollectionType and PHAssetCollectionSubtype in the Photos framework instead");

typedef NS_ENUM(NSInteger, ALAuthorizationStatus) {
    ALAuthorizationStatusNotDetermined AL_DEPRECATED(6, "Use PHAuthorizationStatus in the Photos framework instead") = 0, // User has not yet made a choice with regards to this application
    ALAuthorizationStatusRestricted AL_DEPRECATED(6, "Use PHAuthorizationStatus in the Photos framework instead"),        // This application is not authorized to access photo data.
                                                                                                                          // The user cannot change this application’s status, possibly due to active restrictions
                                                                                                                          //  such as parental controls being in place.
    ALAuthorizationStatusDenied AL_DEPRECATED(6, "Use PHAuthorizationStatus in the Photos framework instead"),            // User has explicitly denied this application access to photos data.
    ALAuthorizationStatusAuthorized AL_DEPRECATED(6, "Use PHAuthorizationStatus in the Photos framework instead")         // User has authorized this application to access photos data.
} AL_DEPRECATED(6, "Use PHAuthorizationStatus in the Photos framework instead");


// This block is executed when a match is found during enumeration. The match is passed to the block in the group argument.
// When the enumeration is done, the block will be called with group set to nil.
// Setting the output argument stop to YES will finish the enumeration.
typedef void (^ALAssetsLibraryGroupsEnumerationResultsBlock)(ALAssetsGroup *group, BOOL *stop) AL_DEPRECATED(4, "Use the PHFetchResult returned by fetchAssetCollectionsInCollectionList:options: on PHAssetCollection from the Photos framework to enumerate the asset collections in a collection list instead");

// This block is executed if the user has granted access to the caller to access the data managed by the framework.
// If the asset is not found, asset is nil.
typedef void (^ALAssetsLibraryAssetForURLResultBlock)(ALAsset *asset) AL_DEPRECATED(4, "Use fetchAssetsWithLocalIdentifiers:options: on PHAsset to fetch assets by local identifier (or to lookup PHAssets by a previously known ALAssetPropertyAssetURL use fetchAssetsWithALAssetURLs:options:) from the Photos framework instead");

// This block is executed if the user has granted access to the caller to access the data managed by the framework.
// If the group is not found, group is nil.
typedef void (^ALAssetsLibraryGroupResultBlock)(ALAssetsGroup *group) AL_DEPRECATED(5, "Use fetchAssetCollectionsWithLocalIdentifiers:options: on PHAssetCollection to fetch the asset collections by local identifier (or to lookup PHAssetCollections by a previously known ALAssetsGroupPropertyURL use fetchAssetCollectionsWithALAssetGroupURLs:options:) from the Photos framework instead");

// This block is executed if the user does not grant access to the caller to access the data managed by the framework or if the data is currently unavailable.
typedef void (^ALAssetsLibraryAccessFailureBlock)(NSError *error) AL_DEPRECATED(4, "Use the Photos framework instead");

// This block is executed when saving an image by -writeImageToSavedPhotosAlbum:completionBlock: finishes. The assetURL can later be used to reference the saved image.
typedef void (^ALAssetsLibraryWriteImageCompletionBlock)(NSURL *assetURL, NSError *error) AL_DEPRECATED(4, "Use performChanges:completionHandler: or performChangesAndWait: on the shared PHPhotoLibrary with a PHAssetChangeRequest from the Photos framework instead");
// This block is executed when saving a video by -writeVideoAtPathToSavedPhotosAlbum:completionBlock: finishes. The assetURL can later be used to reference the saved video.
typedef void (^ALAssetsLibraryWriteVideoCompletionBlock)(NSURL *assetURL, NSError *error) AL_DEPRECATED(4, "Use performChanges:completionHandler: or performChangesAndWait: on the shared PHPhotoLibrary with a PHAssetChangeRequest from the Photos framework instead");


OS_EXPORT AL_DEPRECATED(4, "Use PHPhotoLibrary from the Photos framework instead")
@interface ALAssetsLibrary : NSObject {
@package
    id _internal;
    
}

// Get the list of groups that match the given types. Multiple types can be ORed together. The results are passed one by one to the caller by executing the enumeration block.
// When the enumeration is done, 'enumerationBlock' will be called with group set to nil.
// When groups are enumerated, the user may be asked to confirm the application's access to the data. If the user denies access to the application or if no application is allowed to access the data, the failure block will be called.
// If the data is currently unavailable, the failure block will be called.
- (void)enumerateGroupsWithTypes:(ALAssetsGroupType)types usingBlock:(ALAssetsLibraryGroupsEnumerationResultsBlock)enumerationBlock failureBlock:(ALAssetsLibraryAccessFailureBlock)failureBlock AL_DEPRECATED(4, "Use the PHFetchResult returned by one of the fetch... methods on PHAssetCollection from the Photos framework to enumerate asset collections instead");

// Returns an ALAsset object in the result block for a URL previously retrieved from an ALAsset object.
// When the ALAsset is requested, the user may be asked to confirm the application's access to the data. If the user denies access to the application or if no application is allowed to access the data, the failure block will be called.
// If the data is currently unavailable, the failure block will be called.
- (void)assetForURL:(NSURL *)assetURL resultBlock:(ALAssetsLibraryAssetForURLResultBlock)resultBlock failureBlock:(ALAssetsLibraryAccessFailureBlock)failureBlock AL_DEPRECATED(4, "Use fetchAssetsWithLocalIdentifiers:options: on PHAsset to fetch assets by local identifier (or to lookup PHAssets by a previously known ALAssetPropertyAssetURL use fetchAssetsWithALAssetURLs:options:) from the Photos framework instead");

// Returns an ALAssetsGroup object in the result block for a URL previously retrieved from an ALAssetsGroup object.
// When the ALAssetsGroup is requested, the user may be asked to confirm the application's access to the data.  If the user denies access to the application or if no application is allowed to access the data, the failure block will be called.
// If the data is currently unavailable, the failure block will be called.
- (void)groupForURL:(NSURL *)groupURL resultBlock:(ALAssetsLibraryGroupResultBlock)resultBlock failureBlock:(ALAssetsLibraryAccessFailureBlock)failureBlock AL_DEPRECATED(5, "Use fetchAssetCollectionsWithLocalIdentifiers:options: on PHAssetCollection to fetch the asset collections by local identifier (or to lookup PHAssetCollections by a previously known ALAssetsGroupPropertyURL use fetchAssetCollectionsWithALAssetGroupURLs:options:) from the Photos framework instead");

// Add a new ALAssetsGroup to the library.
// The name of the ALAssetsGroup is name and the type is ALAssetsGroupAlbum.  The editable property of this ALAssetsGroup returns YES.
// If name conflicts with another ALAssetsGroup with the same name, then the group is not created and the result block returns a nil group.
// When the ALAssetsGroup is added, the user may be asked to confirm the application's access to the data.  If the user denies access to the application or if no application is allowed to access the data, the failure block will be called.
// If the data is currently unavailable, the failure block will be called.
- (void)addAssetsGroupAlbumWithName:(NSString *)name resultBlock:(ALAssetsLibraryGroupResultBlock)resultBlock failureBlock:(ALAssetsLibraryAccessFailureBlock)failureBlock AL_DEPRECATED(5, "Use creationRequestForAssetCollectionWithTitle: on PHAssetCollectionChangeRequest from the Photos framework to create a new asset collection instead");

// These methods can be used to add photos or videos to the saved photos album.

// With a UIImage, the API user can use -[UIImage CGImage] to get a CGImageRef, and cast -[UIImage imageOrientation] to ALAssetOrientation.
- (void)writeImageToSavedPhotosAlbum:(CGImageRef)imageRef orientation:(ALAssetOrientation)orientation completionBlock:(ALAssetsLibraryWriteImageCompletionBlock)completionBlock AL_DEPRECATED(4, "Use creationRequestForAssetFromImage: on PHAssetChangeRequest from the Photos framework to create a new asset instead");

// The API user will have to specify the orientation key in the metadata dictionary to preserve the orientation of the image
- (void)writeImageToSavedPhotosAlbum:(CGImageRef)imageRef metadata:(NSDictionary *)metadata completionBlock:(ALAssetsLibraryWriteImageCompletionBlock)completionBlock AL_DEPRECATED(4.1, "Use creationRequestForAssetFromImage: on PHAssetChangeRequest from the Photos framework to create a new asset instead");

// If there is a conflict between the metadata in the image data and the metadata dictionary, the image data metadata values will be overwritten
- (void)writeImageDataToSavedPhotosAlbum:(NSData *)imageData metadata:(NSDictionary *)metadata completionBlock:(ALAssetsLibraryWriteImageCompletionBlock)completionBlock AL_DEPRECATED(4.1, "Use creationRequestForAssetFromImageData: on PHAssetChangeRequest from the Photos framework to create a new asset instead");

- (void)writeVideoAtPathToSavedPhotosAlbum:(NSURL *)videoPathURL completionBlock:(ALAssetsLibraryWriteVideoCompletionBlock)completionBlock AL_DEPRECATED(4, "Use creationRequestForAssetFromVideoAtFilePath: on PHAssetChangeRequest from the Photos framework to create a new asset instead");
- (BOOL)videoAtPathIsCompatibleWithSavedPhotosAlbum:(NSURL *)videoPathURL AL_DEPRECATED(5, "Use isCompatibleWithSavedPhotosAlbum on AVAsset instead");

// Returns photo data authorization status for this application
+ (ALAuthorizationStatus)authorizationStatus AL_DEPRECATED(6, "Use authorizationStatus on the shared PHPhotoLibrary from the Photos framework instead");

// Disable retrieval and notifications for Shared Photo Streams
+ (void)disableSharedPhotoStreamsSupport AL_DEPRECATED(6, "Use the Photos framework instead");

@end

// Notifications

// This notification will be sent when the contents of the ALAssetsLibrary have changed from under the app that is using the data.
// The API user should retain the library object to receive this notification.
// The userInfo may include the keys listed below, which identify specific ALAssets or ALAssetGroups that have become invalid and should be discarded. The values are NSSets of NSURLs which match the ALAssetPropertyURL and ALAssetsGroupPropertyURL properties. 
// If the userInfo is nil, all ALAssets and ALAssetGroups should be considered invalid and discarded.
// Modified ALAssets will be identified by the ALAssetLibraryUpdatedAssetsKey, but inserted or deleted ALAssets are identified by invalidating the containing ALAssetGroups.
extern NSString *const ALAssetsLibraryChangedNotification AL_DEPRECATED(4, "Use photoLibraryDidChange: notification from the Photos framework instead");

extern NSString *const ALAssetLibraryUpdatedAssetsKey AL_DEPRECATED(6, "Use changeDetailsForFetchResult: and changeDetailsForObject: to get change details via the PHChange object included on photoLibraryDidChange: from the Photos framework instead");
extern NSString *const ALAssetLibraryInsertedAssetGroupsKey AL_DEPRECATED(6, "Use changeDetailsForFetchResult: and changeDetailsForObject: to get change details via the PHChange object included on photoLibraryDidChange: from the Photos framework instead");
extern NSString *const ALAssetLibraryUpdatedAssetGroupsKey AL_DEPRECATED(6, "Use changeDetailsForFetchResult: and changeDetailsForObject: to get change details via the PHChange object included on photoLibraryDidChange: from the Photos framework instead");
extern NSString *const ALAssetLibraryDeletedAssetGroupsKey AL_DEPRECATED(6, "Use changeDetailsForFetchResult: and changeDetailsForObject: to get change details via the PHChange object included on photoLibraryDidChange: from the Photos framework instead");

// Errors

// Constant used by NSError to distinguish errors belonging to the AssetsLibrary domain
extern NSString *const ALAssetsLibraryErrorDomain AL_DEPRECATED(4, "Use the Photos framework instead");

// AssetsLibrary-related error codes
enum {
    ALAssetsLibraryUnknownError =                 -1,      // Error (reason unknown)
    
    // These errors would be returned in the ALAssetsLibraryWriteImageCompletionBlock and ALAssetsLibraryWriteVideoCompletionBlock completion blocks,
    // as well as in the completion selector for UIImageWriteToSavedPhotosAlbum() and UISaveVideoAtPathToSavedPhotosAlbum()
    ALAssetsLibraryWriteFailedError =           -3300,      // Write error (write failed)
    ALAssetsLibraryWriteBusyError =             -3301,      // Write error (writing is busy, try again)
    ALAssetsLibraryWriteInvalidDataError =      -3302,      // Write error (invalid data)
    ALAssetsLibraryWriteIncompatibleDataError = -3303,      // Write error (incompatible data)
    ALAssetsLibraryWriteDataEncodingError =     -3304,      // Write error (data has invalid encoding)
    ALAssetsLibraryWriteDiskSpaceError =        -3305,      // Write error (out of disk space)

    // This error would be returned in the ALAssetsLibraryAccessFailureBlock, ALAssetsLibraryWriteImageCompletionBlock, and ALAssetsLibraryWriteVideoCompletionBlock completion blocks,
    // as well as in the completion selector for UIImageWriteToSavedPhotosAlbum() and UISaveVideoAtPathToSavedPhotosAlbum()
    ALAssetsLibraryDataUnavailableError =       -3310,      // Data unavailable (data currently unavailable)    
    
    // These errors would be returned in the ALAssetsLibraryAccessFailureBlock
    ALAssetsLibraryAccessUserDeniedError =      -3311,      // Access error (user denied access request)
    ALAssetsLibraryAccessGloballyDeniedError =  -3312,      // Access error (access globally denied)
} AL_DEPRECATED(4, "Use the Photos framework instead");
