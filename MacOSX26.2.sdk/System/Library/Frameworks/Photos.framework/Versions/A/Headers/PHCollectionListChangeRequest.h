//
//  PHCollectionListChangeRequest.h
//  Photos
//
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Photos/PHChangeRequest.h>
#import <Photos/PHFetchResult.h>

@class PHCollection;
@class PHCollectionList;
@class PHObjectPlaceholder;

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE_BEGIN(macos(10.15), ios(8), tvos(10))

// PHCollectionListChangeRequest can only be created or used within a -[PHPhotoLibrary performChanges:] or -[PHPhotoLibrary performChangesAndWait:] block.
OS_EXPORT
@interface PHCollectionListChangeRequest : PHChangeRequest

#pragma mark - Creating Collection Lists

+ (instancetype)creationRequestForCollectionListWithTitle:(NSString *)title;

// This can be used to fetch the newly created collection list after the change block has completed by using -localIdentifier
// It can also be added directly to collection lists within the current change block
@property (nonatomic, strong, readonly) PHObjectPlaceholder *placeholderForCreatedCollectionList;

#pragma mark - Deleting Collection Lists

// requests that the specified collection lists and all their child collections (recursively) be deleted
+ (void)deleteCollectionLists:(id<NSFastEnumeration>)collectionLists;

#pragma mark - Modifying Collection Lists

// if the collection list does not allow the type of change requested, these methods will raise an exception, call canPerformEditOperation: on the collection list to determine if the type of edit operation is allowed.
+ (nullable instancetype)changeRequestForCollectionList:(PHCollectionList *)collectionList;

// to add, remove or rearrange child collections in a collection list, passing in the fetched collections in that collection list will ensure that the child collection positions are tracked correctly in the case that the collection list has been externally edited after the fetch, but before this change is applied
+ (nullable instancetype)changeRequestForCollectionList:(PHCollectionList *)collectionList childCollections:(PHFetchResult<__kindof PHCollection *> *)childCollections;

// to add, remove or rearrange child collections in the TOP LEVEL collection list, passing in the fetched collections in that collection list will ensure that the child collection positions are tracked correctly in the case that the collection list has been externally edited after the fetch, but before this change is applied
+ (nullable instancetype)changeRequestForTopLevelCollectionListUserCollections:(PHFetchResult<__kindof PHCollection *> *)childCollections API_AVAILABLE(macos(11), ios(14.2), tvos(14));

@property (nonatomic, strong, readwrite) NSString *title;

#pragma mark - Mutating child collections

// A PHCollection can only belong to a single parent PHCollection
- (void)addChildCollections:(id<NSFastEnumeration>)collections;
- (void)insertChildCollections:(id<NSFastEnumeration>)collections atIndexes:(NSIndexSet *)indexes;
- (void)removeChildCollections:(id<NSFastEnumeration>)collections;
- (void)removeChildCollectionsAtIndexes:(NSIndexSet *)indexes;
- (void)replaceChildCollectionsAtIndexes:(NSIndexSet *)indexes withChildCollections:(id<NSFastEnumeration>)collections;

// The move removes the child collections at fromIndexes first then inserts those collections at the toIndex, so toIndex should point to a location based on the updated indexes after having removed the child collections at fromIndexes
- (void)moveChildCollectionsAtIndexes:(NSIndexSet *)indexes toIndex:(NSUInteger)toIndex;

@end

API_AVAILABLE_END
NS_ASSUME_NONNULL_END
