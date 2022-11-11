/*
	File:  AVFCore.h

	Framework:  AVFoundation
 
	Copyright 2019 Apple Inc. All rights reserved.

 */

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
#import <AVFoundation/AVAsynchronousKeyValueLoading.h>
#import <AVFoundation/AVAudioMix.h>
#import <AVFoundation/AVAudioProcessingSettings.h>

#import <AVFoundation/AVAssetDownloadTask.h>
#import <AVFoundation/AVAssetDownloadStorageManager.h>
#if TARGET_OS_OSX
#import <AVFoundation/AVCaption.h>
#import <AVFoundation/AVCaptionGroup.h>
#import <AVFoundation/AVCaptionGrouper.h>
#import <AVFoundation/AVCaptionConversionValidator.h>
#import <AVFoundation/AVCaptionFormatConformer.h>
#import <AVFoundation/AVCaptionRenderer.h>
#endif

#import <AVFoundation/AVComposition.h>
#import <AVFoundation/AVCompositionTrack.h>
#import <AVFoundation/AVCompositionTrackSegment.h>
#import <AVFoundation/AVError.h>
#import <AVFoundation/AVMediaFormat.h>
#import <AVFoundation/AVMediaSelection.h>
#import <AVFoundation/AVMediaSelectionGroup.h>
#import <AVFoundation/AVMetadataFormat.h>
#import <AVFoundation/AVMetadataIdentifiers.h>
#import <AVFoundation/AVMetadataItem.h>
#if (TARGET_OS_MAC && ! TARGET_OS_TV)
#import <AVFoundation/AVMovie.h>
#import <AVFoundation/AVMovieTrack.h>
#endif
#import <AVFoundation/AVOutputSettingsAssistant.h>
#import <AVFoundation/AVPlaybackCoordinator.h>
#import <AVFoundation/AVPlayer.h>
#import <AVFoundation/AVPlayerItem.h>
#import <AVFoundation/AVPlayerItemMediaDataCollector.h>
#import <AVFoundation/AVPlayerItemOutput.h>
#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
#import <AVFoundation/AVPlayerItemProtectedContentAdditions.h>
#endif
#import <AVFoundation/AVPlayerItemTrack.h>
#import <AVFoundation/AVPlayerLayer.h>
#import <AVFoundation/AVPlayerLooper.h>
#import <AVFoundation/AVPlayerMediaSelectionCriteria.h>
#import <AVFoundation/AVPlayerInterstitialEventController.h>
#import <AVFoundation/AVQueuedSampleBufferRendering.h>
#import <AVFoundation/AVRouteDetector.h>
#import <AVFoundation/AVSampleBufferAudioRenderer.h>
#import <AVFoundation/AVSampleBufferDisplayLayer.h>
#import <AVFoundation/AVSampleBufferRenderSynchronizer.h>
#import <AVFoundation/AVSampleBufferGenerator.h>
#import <AVFoundation/AVSampleCursor.h>
#import <AVFoundation/AVSynchronizedLayer.h>
#import <AVFoundation/AVTextStyleRule.h>
#import <AVFoundation/AVTime.h>
#import <AVFoundation/AVTimedMetadataGroup.h>
#import <AVFoundation/AVUtilities.h>
#import <AVFoundation/AVVideoCompositing.h>
#import <AVFoundation/AVVideoComposition.h>
#import <AVFoundation/AVVideoSettings.h>
#if TARGET_OS_IPHONE && ! TARGET_OS_MACCATALYST
#import <AVFoundation/AVDisplayCriteria.h>
#endif
