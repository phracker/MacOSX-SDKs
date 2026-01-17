/*
 File:  AVPlayerItem+AVKitAdditions.h
 
 Framework:  AVKit
 
 Copyright © 2019-2023 Apple Inc. All rights reserved.
 
 */

#import <AVFoundation/AVPlayerItem.h>

@class AVMetadataItem;
@class AVInterstitialTimeRange;


// MARK: -

NS_ASSUME_NONNULL_BEGIN

@interface AVPlayerItem (AVKitAdditions)

/*!
 	@property 	externalMetadata
 	@abstract 	Supplements metadata contained in the asset.
 	@discussion AVPlayerViewController will publish this metadata as now playing info when AVPlayerViewController.updatesNowPlayingInfoCenter is YES. In addition, some metadata items will be displayed in the AVPlayerViewController UI.
 
 				- AVMetadataCommonIdentifierTitle
				- AVMetadataIdentifieriTunesMetadataTrackSubTitle
 				- AVMetadataCommonIdentifierDescription
 */
@property (nonatomic, copy) NSArray<AVMetadataItem *> *externalMetadata API_AVAILABLE(ios(12.2), visionos(1.0));

/*!
	 @property	 interstitialTimeRanges
	 @abstract	 An array of time ranges that identifies interstitial content. Each element specifies the time range of the media occupied by the interstitials.
	 @discussion An interstitial time range identifies a range of an asset that is collapsed into a single dot on the timeline in the user interface. Interstitial content is typically not related to the video being played (e.g. advertisements). On iOS, interstitials must be defined by the stream, or by using an AVPlayerInterstitialEventController.
 */
@property (nonatomic, readonly) NSArray<AVInterstitialTimeRange *> *interstitialTimeRanges API_AVAILABLE(ios(16.0), visionos(1.0)) API_UNAVAILABLE(macCatalyst);

@end

NS_ASSUME_NONNULL_END
