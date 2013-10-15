/*
	File:  AVFoundation.h

	Framework:  AVFoundation
 
	Copyright 2008-2010 Apple Inc. All rights reserved.

	To report bugs, go to:  http://developer.apple.com/bugreporter/

*/

#import <AVFoundation/AVBase.h>

#import <AVFoundation/AVAudioPlayer.h>
#import <AVFoundation/AVAudioRecorder.h>
#import <AVFoundation/AVAudioSettings.h>

#import <AVFoundation/AVAnimation.h>
#import <AVFoundation/AVAsset.h>
#import <AVFoundation/AVAssetExportSession.h>
#import <AVFoundation/AVAssetImageGenerator.h>
#import <AVFoundation/AVAssetReader.h>
#import <AVFoundation/AVAssetReaderOutput.h>
#import <AVFoundation/AVAssetTrack.h>
#import <AVFoundation/AVAssetTrackSegment.h>
#import <AVFoundation/AVAssetWriter.h>
#import <AVFoundation/AVAssetWriterInput.h>
#import <AVFoundation/AVAsynchronousKeyValueLoading.h>
#import <AVFoundation/AVAudioMix.h>
#import <AVFoundation/AVComposition.h>
#import <AVFoundation/AVCompositionTrack.h>
#import <AVFoundation/AVCompositionTrackSegment.h>
#import <AVFoundation/AVError.h>
#import <AVFoundation/AVMediaFormat.h>
#import <AVFoundation/AVMetadataFormat.h>
#import <AVFoundation/AVMetadataItem.h>
#import <AVFoundation/AVPlayer.h>
#import <AVFoundation/AVPlayerItem.h>
#import <AVFoundation/AVPlayerItemTrack.h>
#import <AVFoundation/AVPlayerLayer.h>
#import <AVFoundation/AVSynchronizedLayer.h>
#import <AVFoundation/AVTime.h>
#import <AVFoundation/AVTimedMetadataGroup.h>
#import <AVFoundation/AVUtilities.h>
#import <AVFoundation/AVVideoComposition.h>
#import <AVFoundation/AVVideoSettings.h>

#if TARGET_OS_IPHONE
#import <AVFoundation/AVAudioSession.h>
#endif

#if (TARGET_OS_IPHONE || defined(__MAC_10_7))
#import <AVFoundation/AVCaptureSession.h>
#import <AVFoundation/AVCaptureDevice.h>
#import <AVFoundation/AVCaptureInput.h>
#import <AVFoundation/AVCaptureOutput.h>
#import <AVFoundation/AVCaptureVideoPreviewLayer.h>
#endif

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
#import <AVFoundation/AVPlayerItemProtectedContentAdditions.h>
#endif
