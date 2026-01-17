//
//  ALAssetsFilter.h
//  AssetsLibrary
//
//  Copyright 2010 Apple Inc. All rights reserved.
//
/*
 *
 * This class encapsulates filtering criteria to be used when retrieving assets from a group.
 *
 */

#import <Foundation/Foundation.h>
#import <AssetsLibrary/ALAssetsLibrary.h>

OS_EXPORT AL_DEPRECATED(4, "Use fetchAssetsInAssetCollection:options: on PHAsset and set a mediaType predicate on the PHFetchOptions from the Photos framework instead")
@interface ALAssetsFilter : NSObject {
@package
    id _internal;
}

// Get all photos assets in the assets group.
+ (ALAssetsFilter *)allPhotos;
// Get all video assets in the assets group.
+ (ALAssetsFilter *)allVideos;
// Get all assets in the group.
+ (ALAssetsFilter *)allAssets;

@end
