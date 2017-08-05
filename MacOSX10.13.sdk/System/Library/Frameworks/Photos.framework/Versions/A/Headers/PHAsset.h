//
//  PHAsset.h
//  Photos
//
//  Copyright © 2017 Apple, Inc. All rights reserved.
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

NS_CLASS_AVAILABLE(10_13, 8_0) @interface PHAsset : PHObject

#pragma mark - Properties

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

// for UI to hide the failure
@property (nonatomic, assign, readonly, getter=isSyncFailureHidden) BOOL syncFailureHidden;

@property (nonatomic, assign, readonly, getter=isFavorite) BOOL favorite;

@property (nonatomic, assign, readonly) PHAssetSourceType sourceType NS_AVAILABLE(10_13, 9_0);

#pragma mark - Fetching assets

+ (PHFetchResult<PHAsset *> *)fetchAssetsInAssetCollection:(PHAssetCollection *)assetCollection options:(nullable PHFetchOptions *)options;
+ (PHFetchResult<PHAsset *> *)fetchAssetsWithLocalIdentifiers:(NSArray<NSString *> *)identifiers options:(nullable PHFetchOptions *)options;
+ (nullable PHFetchResult<PHAsset *> *)fetchKeyAssetsInAssetCollection:(PHAssetCollection *)assetCollection options:(nullable PHFetchOptions *)options;

@end

NS_ASSUME_NONNULL_END
