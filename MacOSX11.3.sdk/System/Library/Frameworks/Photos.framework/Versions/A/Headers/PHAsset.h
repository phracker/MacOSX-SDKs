//
//  PHAsset.h
//  Photos
//
//  Copyright (c) 2017 Apple Inc. All rights reserved.
//

#import <Photos/PHObject.h>
#import <Photos/PhotosTypes.h>
#import <Photos/PHFetchResult.h>
#import <Photos/PHPhotoLibrary.h>

#import <ImageIO/ImageIO.h>
#import <CoreLocation/CLLocation.h>


@class PHFetchOptions;
@class PHAssetCollection;

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE_BEGIN(macos(10.13), ios(8), tvos(10))

OS_EXPORT
@interface PHAsset : PHObject

#pragma mark - Properties

// Playback style describes how the asset should be presented to the user (regardless of the backing media for that asset).  Use this value to choose the type of view and the appropriate APIs on the PHImageManager to display this asset
@property (nonatomic, assign, readonly) PHAssetPlaybackStyle playbackStyle API_AVAILABLE(macos(10.15), ios(11), tvos(11));

@property (nonatomic, assign, readonly) PHAssetMediaType mediaType;
@property (nonatomic, assign, readonly) PHAssetMediaSubtype mediaSubtypes;

@property (nonatomic, assign, readonly) NSUInteger pixelWidth;
@property (nonatomic, assign, readonly) NSUInteger pixelHeight;

@property (nonatomic, strong, readonly, nullable) NSDate *creationDate;
@property (nonatomic, strong, readonly, nullable) NSDate *modificationDate;

@property (nonatomic, strong, readonly, nullable) CLLocation *location;

@property (nonatomic, assign, readonly) NSTimeInterval duration;

// a hidden asset will be excluded from moment collections, but may still be included in other smart or regular album collections
@property (nonatomic, assign, readonly, getter=isHidden) BOOL hidden;

@property (nonatomic, assign, readonly, getter=isFavorite) BOOL favorite;

// deprecated, will always return NO for now.
@property (nonatomic, assign, readonly, getter=isSyncFailureHidden) BOOL syncFailureHidden API_DEPRECATED("No longer supported", macos(10.14, 10.15)) API_UNAVAILABLE(ios, tvos, watchos);

@property (nonatomic, strong, readonly, nullable) NSString *burstIdentifier API_AVAILABLE(macos(10.15));
@property (nonatomic, assign, readonly) PHAssetBurstSelectionType burstSelectionTypes API_AVAILABLE(macos(10.15));
@property (nonatomic, assign, readonly) BOOL representsBurst API_AVAILABLE(macos(10.15));

@property (nonatomic, assign, readonly) PHAssetSourceType sourceType API_AVAILABLE(ios(9));

#pragma mark - Capabilities

- (BOOL)canPerformEditOperation:(PHAssetEditOperation)editOperation API_AVAILABLE(macos(10.15));

#pragma mark - Fetching assets

+ (PHFetchResult<PHAsset *> *)fetchAssetsInAssetCollection:(PHAssetCollection *)assetCollection options:(nullable PHFetchOptions *)options;
+ (PHFetchResult<PHAsset *> *)fetchAssetsWithLocalIdentifiers:(NSArray<NSString *> *)identifiers options:(nullable PHFetchOptions *)options; // includes hidden assets by default
+ (nullable PHFetchResult<PHAsset *> *)fetchKeyAssetsInAssetCollection:(PHAssetCollection *)assetCollection options:(nullable PHFetchOptions *)options;
+ (PHFetchResult<PHAsset *> *)fetchAssetsWithBurstIdentifier:(NSString *)burstIdentifier options:(nullable PHFetchOptions *)options API_AVAILABLE(macos(10.15));

// Fetches PHAssetSourceTypeUserLibrary assets by default (use includeAssetSourceTypes option to override)
+ (PHFetchResult<PHAsset *> *)fetchAssetsWithOptions:(nullable PHFetchOptions *)options API_AVAILABLE(macos(10.15));
+ (PHFetchResult<PHAsset *> *)fetchAssetsWithMediaType:(PHAssetMediaType)mediaType options:(nullable PHFetchOptions *)options API_AVAILABLE(macos(10.15));

// assetURLs are URLs retrieved from ALAsset's ALAssetPropertyAssetURL
+ (PHFetchResult<PHAsset *> *)fetchAssetsWithALAssetURLs:(NSArray<NSURL *> *)assetURLs options:(nullable PHFetchOptions *)options API_DEPRECATED("Will be removed in a future release", ios(8, 11), tvos(8, 11)) API_UNAVAILABLE(macos);

@end

API_AVAILABLE_END
NS_ASSUME_NONNULL_END
