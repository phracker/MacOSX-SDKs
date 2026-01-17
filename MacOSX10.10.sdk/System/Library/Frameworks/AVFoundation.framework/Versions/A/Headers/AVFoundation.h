/*
	File:  AVFoundation.h

	Framework:  AVFoundation
 
	Copyright 2008-2013 Apple Inc. All rights reserved.

	To report bugs, go to:  http://developer.apple.com/bugreporter/

*/

#import <AVFoundation/AVBase.h>

#import <AVFoundation/AVAudioBuffer.h>
#import <AVFoundation/AVAudioChannelLayout.h>
#import <AVFoundation/AVAudioEngine.h>
#import <AVFoundation/AVAudioEnvironmentNode.h>
#import <AVFoundation/AVAudioFile.h>
#import <AVFoundation/AVAudioFormat.h>
#import <AVFoundation/AVAudioIONode.h>
#import <AVFoundation/AVAudioMixerNode.h>
#import <AVFoundation/AVAudioMixing.h>
#import <AVFoundation/AVAudioNode.h>
#import <AVFoundation/AVAudioPlayer.h>
#import <AVFoundation/AVAudioPlayerNode.h>
#import <AVFoundation/AVAudioRecorder.h>
#if TARGET_OS_IPHONE
#import <AVFoundation/AVAudioSession.h>
#endif
#import <AVFoundation/AVAudioSettings.h>
#import <AVFoundation/AVAudioTime.h>
#import <AVFoundation/AVAudioTypes.h>
#import <AVFoundation/AVAudioUnit.h>
#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
#import <AVFoundation/AVAudioUnitComponent.h>
#endif
#import <AVFoundation/AVAudioUnitDelay.h>
#import <AVFoundation/AVAudioUnitDistortion.h>
#import <AVFoundation/AVAudioUnitEQ.h>
#import <AVFoundation/AVAudioUnitEffect.h>
#import <AVFoundation/AVAudioUnitGenerator.h>
#import <AVFoundation/AVAudioUnitMIDIInstrument.h>
#import <AVFoundation/AVAudioUnitReverb.h>
#import <AVFoundation/AVAudioUnitSampler.h>
#import <AVFoundation/AVAudioUnitTimeEffect.h>
#import <AVFoundation/AVAudioUnitTimePitch.h>
#import <AVFoundation/AVAudioUnitVarispeed.h>
#import <AVFoundation/AVMIDIPlayer.h>

#import <AVFoundation/AVAnimation.h>
#import <AVFoundation/AVAsset.h>
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
#import <AVFoundation/AVMediaFormat.h>
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
#import <AVFoundation/AVPlayerItemOutput.h>
#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
#import <AVFoundation/AVPlayerItemProtectedContentAdditions.h>
#endif
#import <AVFoundation/AVPlayerItemTrack.h>
#import <AVFoundation/AVPlayerLayer.h>
#import <AVFoundation/AVPlayerMediaSelectionCriteria.h>
#import <AVFoundation/AVSampleBufferDisplayLayer.h>
#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
#import <AVFoundation/AVSampleBufferGenerator.h>
#import <AVFoundation/AVSampleCursor.h>
#endif
#if TARGET_OS_IPHONE
#import <AVFoundation/AVSpeechSynthesis.h>
#endif
#import <AVFoundation/AVSynchronizedLayer.h>
#import <AVFoundation/AVTextStyleRule.h>
#import <AVFoundation/AVTime.h>
#import <AVFoundation/AVTimedMetadataGroup.h>
#import <AVFoundation/AVUtilities.h>
#import <AVFoundation/AVVideoCompositing.h>
#import <AVFoundation/AVVideoComposition.h>
#import <AVFoundation/AVVideoSettings.h>
