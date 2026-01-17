/*
	File:  AVFoundation.h

	Framework:  AVFoundation
 
	Copyright 2010-2015 Apple Inc. All rights reserved.

	To report bugs, go to:  http://developer.apple.com/bugreporter/

*/

#import <TargetConditionals.h>
#if TARGET_OS_WATCH
#if ! __has_include(<AVFoundation/AVAnimation.h>)
#define AVF_IS_WATCHOS_SDK 1
#endif
#endif

#import <AVFoundation/AVBase.h>

#if ! AVF_IS_WATCHOS_SDK
#import <AVFoundation/AVAnimation.h>
#import <AVFoundation/AVAsset.h>
#import <AVFoundation/AVAssetCache.h>
#import <AVFoundation/AVAssetExportSession.h>
#import <AVFoundation/AVAssetImageGenerator.h>
#import <AVFoundation/AVAssetReader.h>
#import <AVFoundation/AVAssetReaderOutput.h>
#import <AVFoundation/AVAssetResourceLoader.h>
#import <AVFoundation/AVAssetTrack.h>
#import <AVFoundation/AVAssetTrackGroup.h>
#import <AVFoundation/AVAssetTrackSegment.h>
#import <AVFoundation/AVAssetWriter.h>
#import <AVFoundation/AVAssetWriterInput.h>
#import <AVFoundation/AVAsynchronousKeyValueLoading.h>
#import <AVFoundation/AVAudioMix.h>
#import <AVFoundation/AVAudioProcessingSettings.h>

#if TARGET_OS_IPHONE
#import <AVFoundation/AVAssetDownloadTask.h>
#endif

#if (TARGET_OS_IPHONE || defined(__MAC_10_7))
#import <AVFoundation/AVCaptureDevice.h>
#import <AVFoundation/AVCaptureInput.h>
#import <AVFoundation/AVCaptureOutput.h>
#import <AVFoundation/AVCaptureSession.h>
#import <AVFoundation/AVCaptureVideoPreviewLayer.h>
#endif

#import <AVFoundation/AVComposition.h>
#import <AVFoundation/AVCompositionTrack.h>
#import <AVFoundation/AVCompositionTrackSegment.h>
#import <AVFoundation/AVError.h>
#endif

#import <AVFoundation/AVFAudio.h>

#if ! AVF_IS_WATCHOS_SDK
#import <AVFoundation/AVMediaFormat.h>
#import <AVFoundation/AVMediaSelection.h>
#import <AVFoundation/AVMediaSelectionGroup.h>
#import <AVFoundation/AVMetadataFormat.h>
#import <AVFoundation/AVMetadataIdentifiers.h> 
#import <AVFoundation/AVMetadataItem.h>
#import <AVFoundation/AVMetadataObject.h>
#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
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
#import <AVFoundation/AVSampleBufferDisplayLayer.h>
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
#endif
