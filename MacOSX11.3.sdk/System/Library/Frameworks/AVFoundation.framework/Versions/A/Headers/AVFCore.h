/*
	File:  AVFCore.h

	Framework:  AVFoundation
 
	Copyright 2019 Apple Inc. All rights reserved.

 */

#import <AVFoundation/AVBase.h>
#import <AVFoundation/AVAnimation.h>
#import <AVFoundation/AVAsset.h>
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

#if TARGET_OS_IPHONE
#if __has_include(<AVFoundation/AVAssetDownloadTask.h>)
#import <AVFoundation/AVAssetDownloadTask.h>
#endif
#if __has_include(<AVFoundation/AVAssetDownloadStorageManager.h>)
#import <AVFoundation/AVAssetDownloadStorageManager.h>
#endif
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
#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
#import <AVFoundation/AVSampleBufferGenerator.h>
#import <AVFoundation/AVSampleCursor.h>
#endif
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
