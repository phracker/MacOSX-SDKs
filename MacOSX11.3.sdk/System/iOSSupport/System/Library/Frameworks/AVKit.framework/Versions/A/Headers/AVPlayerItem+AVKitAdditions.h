/*
 File:  AVPlayerItem+AVKitAdditions.h
 
 Framework:  AVKit
 
 Copyright © 2019 Apple Inc. All rights reserved.
 
 */

#import <AVFoundation/AVPlayerItem.h>

@class AVMetadataItem;

NS_ASSUME_NONNULL_BEGIN

@interface AVPlayerItem (AVKitAdditions)

/*!
 	@property 	externalMetadata
 	@abstract 	Supplements metadata contained in the asset.
 	@discussion AVPlayerViewController will publish this metadata as now playing info when AVPlayerViewController.updatesNowPlayingInfoCenter is YES.
 */
@property (nonatomic, copy) NSArray<AVMetadataItem *> *externalMetadata API_AVAILABLE(ios(12.2));

@end

NS_ASSUME_NONNULL_END
