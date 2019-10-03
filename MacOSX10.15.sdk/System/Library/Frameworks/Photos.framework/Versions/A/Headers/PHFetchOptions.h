//
//  PHFetchOptions.h
//  Photos
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Photos/PhotosTypes.h>

@class PHObject;

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE_BEGIN(macos(10.13), ios(8), tvos(10))

OS_EXPORT
@interface PHFetchOptions : NSObject <NSCopying>

// Some predicates / sorts may be suboptimal and we will log
@property (nonatomic, strong, nullable) NSPredicate *predicate;
@property (nonatomic, strong, nullable) NSArray<NSSortDescriptor *> *sortDescriptors;

// Whether hidden assets are included in fetch results. Defaults to NO
@property (nonatomic, assign) BOOL includeHiddenAssets;

// Whether hidden burst assets are included in fetch results. Defaults to NO
@property (nonatomic, assign) BOOL includeAllBurstAssets API_AVAILABLE(macos(10.15));

// The asset source types included in the fetch results.  Defaults to PHAssetSourceTypeNone.
// If set to PHAssetSourceTypeNone the asset source types included in the fetch results are inferred from the type of query performed (see PHAsset fetchAssetsWithOptions:)
@property (nonatomic, assign) PHAssetSourceType includeAssetSourceTypes API_AVAILABLE(ios(9));

// Limits the maximum number of objects returned in the fetch result, a value of 0 means no limit.  Defaults to 0.
@property (nonatomic, assign, readwrite) NSUInteger fetchLimit API_AVAILABLE(ios(9));

// Whether the owner of this object is interested in incremental change details for the results of this fetch (see PHChange)
// Defaults to YES
@property (nonatomic, assign) BOOL wantsIncrementalChangeDetails;

@end

API_AVAILABLE_END
NS_ASSUME_NONNULL_END
