//
//  PHContentEditingInput.h
//  Photos
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Photos/PhotosTypes.h>

@class PHAdjustmentData;
@class PHLivePhoto;
@class AVAsset;
@class CLLocation;

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_11, 8_0)
@interface PHContentEditingInput : NSObject

@property (readonly, assign) PHAssetMediaType mediaType;
@property (readonly, assign) PHAssetMediaSubtype mediaSubtypes;
@property (readonly, assign) PHAssetPlaybackStyle playbackStyle;
@property (readonly, copy, nullable) NSDate *creationDate;
@property (readonly, copy, nullable) CLLocation *location;
@property (readonly, copy, nullable) NSString *uniformTypeIdentifier;

// Adjustments to be applied onto the provided input image or video.
@property (readonly, strong, nullable) PHAdjustmentData *adjustmentData;

// Input image:
@property (readonly, strong, nullable) NSImage *displaySizeImage;
@property (readonly, copy, nullable) NSURL *fullSizeImageURL;
@property (readonly, assign) int fullSizeImageOrientation; // EXIF value

// Input video:
@property (readonly, strong, nullable) AVAsset *avAsset NS_DEPRECATED_IOS(8_0, 9_0);
@property (readonly, strong, nullable) AVAsset *audiovisualAsset NS_AVAILABLE(10_11, 9_0);

// Input Live Photo:
@property (readonly, strong, nullable) PHLivePhoto *livePhoto NS_AVAILABLE(10_12, 10_0);

@end

NS_ASSUME_NONNULL_END
