/*
	File:  AVFCore.h

	Framework:  AVFoundation
 
	Copyright 2019-2024 Apple Inc. All rights reserved.

 */

#import <TargetConditionals.h>


#import <AVFoundation/AVBase.h>
#import <AVFoundation/AVAnimation.h>
#import <AVFoundation/AVAsset.h>
#import <AVFoundation/AVAssetVariant.h>
#import <AVFoundation/AVAssetCache.h>
#import <AVFoundation/AVAssetExportSession.h>
#import <AVFoundation/AVAssetImageGenerator.h>
#import <AVFoundation/AVAssetReader.h>
#import <AVFoundation/AVAssetReaderOutput.h>
#import <AVFoundation/AVAssetResourceLoader.h>
#import <AVFoundation/AVContentKeySession.h>
#import <AVFoundation/AVAssetTrack.h>
#import <AVFoundation/AVAssetTrackGroup.h>
#import <AVFoundation/AVAssetTrackSegment.h>
#import <AVFoundation/AVAssetWriter.h>
#import <AVFoundation/AVAssetWriterInput.h>
#import <AVFoundation/AVAssetPlaybackAssistant.h>
#import <AVFoundation/AVAssetSegmentReport.h>
#import <AVFoundation/AVAsynchronousKeyValueLoading.h>
#import <AVFoundation/AVAudioMix.h>
#import <AVFoundation/AVAudioProcessingSettings.h>
#import <AVFoundation/AVAssetDownloadTask.h>
#import <AVFoundation/AVAssetDownloadStorageManager.h>
#import <AVFoundation/AVCaption.h>
#import <AVFoundation/AVCaptionGroup.h>
#import <AVFoundation/AVCaptionGrouper.h>
#import <AVFoundation/AVCaptionConversionValidator.h>
#import <AVFoundation/AVCaptionFormatConformer.h>
#import <AVFoundation/AVCaptionRenderer.h>
#import <AVFoundation/AVCaptionSettings.h>
#import <AVFoundation/AVComposition.h>
#import <AVFoundation/AVCompositionTrack.h>
#import <AVFoundation/AVCompositionTrackSegment.h>
#import <AVFoundation/AVError.h>
#import <AVFoundation/AVGeometry.h>
#import <AVFoundation/AVMediaFormat.h>
#import <AVFoundation/AVMediaSelection.h>
#import <AVFoundation/AVMediaSelectionGroup.h>
#import <AVFoundation/AVMetadataFormat.h>
#import <AVFoundation/AVMetadataIdentifiers.h>
#import <AVFoundation/AVMetadataItem.h>
#import <AVFoundation/AVMovie.h>
#import <AVFoundation/AVMovieTrack.h>
#import <AVFoundation/AVOutputSettingsAssistant.h>
#import <AVFoundation/AVPlaybackCoordinator.h>
#import <AVFoundation/AVPlaybackCoordinationMedium.h>
#import <AVFoundation/AVPlayer.h>
#import <AVFoundation/AVPlayerOutput.h>
#import <AVFoundation/AVPlayerItem.h>
#import <AVFoundation/AVPlayerItemMediaDataCollector.h>
#import <AVFoundation/AVPlayerItemOutput.h>
#if ((TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)) || TARGET_OS_MACCATALYST)
#import <AVFoundation/AVPlayerItemProtectedContentAdditions.h>
#endif
#import <AVFoundation/AVPlayerItemTrack.h>
#import <AVFoundation/AVPlayerLayer.h>
#import <AVFoundation/AVPlayerLooper.h>
#import <AVFoundation/AVPlayerMediaSelectionCriteria.h>
#import <AVFoundation/AVPlayerInterstitialEventController.h>
#import <AVFoundation/AVPlayerItemIntegratedTimeline.h>
#import <AVFoundation/AVQueuedSampleBufferRendering.h>
#import <AVFoundation/AVRenderedCaptionImage.h>
#import <AVFoundation/AVRouteDetector.h>
#import <AVFoundation/AVSampleBufferAudioRenderer.h>
#import <AVFoundation/AVSampleBufferDisplayLayer.h>
#import <AVFoundation/AVSampleBufferRenderSynchronizer.h>
#import <AVFoundation/AVSampleBufferGenerator.h>
#import <AVFoundation/AVSampleBufferVideoRenderer.h>
#import <AVFoundation/AVSampleCursor.h>
#import <AVFoundation/AVSynchronizedLayer.h>
#import <AVFoundation/AVTextStyleRule.h>
#import <AVFoundation/AVTime.h>
#import <AVFoundation/AVTimedMetadataGroup.h>
#import <AVFoundation/AVUtilities.h>
#import <AVFoundation/AVSpatialVideoConfiguration.h>
#import <AVFoundation/AVVideoCompositing.h>
#import <AVFoundation/AVVideoComposition.h>
#import <AVFoundation/AVVideoPerformanceMetrics.h>
#import <AVFoundation/AVVideoSettings.h>
#if TARGET_OS_IPHONE && ! TARGET_OS_MACCATALYST
#import <AVFoundation/AVDisplayCriteria.h>
#endif
#import <AVFoundation/AVMetrics.h>
