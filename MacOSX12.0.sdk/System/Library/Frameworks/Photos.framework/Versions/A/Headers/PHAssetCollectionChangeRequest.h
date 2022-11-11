//
//  PHAssetCollectionChangeRequest.h
//  Photos
//
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Photos/PHChangeRequest.h>
#import <Photos/PHFetchResult.h>

@class PHAsset;
@class PHAssetCollection;
@class PHObjectPlaceholder;

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE_BEGIN(macos(10.15), ios(8), tvos(10))

// PHAssetCollectionChangeRequest can only be created or used within a -[PHPhotoLibrary performChanges:] or -[PHPhotoLibrary performChangesAndWait:] block.
OS_EXPORT
@interface PHAssetCollectionChangeRequest : PHChangeRequest

#pragma mark - Creating Asset Collections

+ (instancetype)creationRequestForAssetCollectionWithTitle:(NSString *)title;

// This can be used to fetch the newly created asset collection after the change block has completed by using -localIdentifier
// It can also be added directly to collection lists within the current change block
@property (nonatomic, strong, readonly) PHObjectPlaceholder *placeholderForCreatedAssetCollection;

#pragma mark - Deleting Asset Collections

// requests that the specified asset collections be deleted
+ (void)deleteAssetCollections:(id<NSFastEnumeration>)assetCollections;

#pragma mark - Modifying Asset Collections

// if the asset collection does not allow the type of change requested, these methods will raise an exception, call canPerformEditOperation: on the asset collection to determine if the type of edit operation is allowed.
+ (nullable instancetype)changeRequestForAssetCollection:(PHAssetCollection *)assetCollection;

// to add, remove or rearrange assets in a collection, passing in the fetched assets in that collection will ensure that the asset positions are tracked correctly in the case that the collection has been externally edited after the fetch, but before this change is applied
+ (nullable instancetype)changeRequestForAssetCollection:(PHAssetCollection *)assetCollection assets:(PHFetchResult<PHAsset *> *)assets;

@property (nonatomic, strong, readwrite) NSString *title;

- (void)addAssets:(id<NSFastEnumeration>)assets;
- (void)insertAssets:(id<NSFastEnumeration>)assets atIndexes:(NSIndexSet *)indexes;
- (void)removeAssets:(id<NSFastEnumeration>)assets;
- (void)removeAssetsAtIndexes:(NSIndexSet *)indexes;
- (void)replaceAssetsAtIndexes:(NSIndexSet *)indexes withAssets:(id<NSFastEnumeration>)assets;

// The move removes the assets at fromIndexes first then inserts those assets at the toIndex, so toIndex should point to a location based on the updated indexes after having removed the assets at fromIndexes
- (void)moveAssetsAtIndexes:(NSIndexSet *)fromIndexes toIndex:(NSUInteger)toIndex;

@end

API_AVAILABLE_END
NS_ASSUME_NONNULL_END
