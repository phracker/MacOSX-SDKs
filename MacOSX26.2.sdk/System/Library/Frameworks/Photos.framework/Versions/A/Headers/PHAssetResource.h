//
//  PHAssetResource.h
//  Photos
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Photos/PhotosTypes.h>

@class PHAsset;
@class PHLivePhoto;
@class UTType;

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE_BEGIN(macos(10.15), ios(9), tvos(10))

OS_EXPORT
@interface PHAssetResource : NSObject

@property (nonatomic, assign, readonly) PHAssetResourceType type;
@property (nonatomic, copy, readonly) NSString *assetLocalIdentifier;
@property (nonatomic, copy, readonly) NSString *originalFilename;

/// The type of data associated with this asset resource (the data can be retrieved via PHAssetResourceManager)
@property (nonatomic, copy, readonly) UTType *contentType API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), visionos(26.0));
@property (nonatomic, copy, readonly) NSString *uniformTypeIdentifier API_DEPRECATED("Use contentType instead", ios(9, API_TO_BE_DEPRECATED), macos(10.15, API_TO_BE_DEPRECATED), tvos(10, API_TO_BE_DEPRECATED), visionos(1, API_TO_BE_DEPRECATED));

@property (nonatomic, assign, readonly) NSInteger pixelWidth API_AVAILABLE(macos(13), ios(16), tvos(16));
@property (nonatomic, assign, readonly) NSInteger pixelHeight API_AVAILABLE(macos(13), ios(16), tvos(16));

#pragma mark - Getting resources

+ (NSArray<PHAssetResource *> *)assetResourcesForAsset:(PHAsset *)asset;
+ (NSArray<PHAssetResource *> *)assetResourcesForLivePhoto:(PHLivePhoto *)livePhoto API_AVAILABLE(ios(9.1));

@end

API_AVAILABLE_END
NS_ASSUME_NONNULL_END
