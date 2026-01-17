/*
	File:  AVKit.h
	
	Framework:  AVKit
	
	Copyright © 2013-2023 Apple Inc. All rights reserved.
	
	To report bugs, go to:  http://developer.apple.com/bugreporter/

 */

#import <Availability.h>
#import <TargetConditionals.h>


#if TARGET_OS_OSX || TARGET_OS_MACCATALYST
#import <AVKit/AVKitDefines.h>
#if __has_include(<AVKit/AVKitCore.h>)
#import <AVKit/AVKitCore.h>
#else
#import <AVKit/AVKitCore.h>
#endif // __has_include(<AVKit/AVKitCore.h>)

#else
#import <AVKit/AVKitDefines.h>
#import <AVKit/AVKitTypes.h>

#endif // TARGET_OS_OSX || TARGET_OS_MACCATALYST


#if TARGET_OS_OSX
#import <AVKit/AVCaptureView.h>
#import <AVKit/AVPictureInPictureController.h>
#import <AVKit/AVPictureInPictureController_AVSampleBufferDisplayLayerSupport.h>
#import <AVKit/AVPlayerView.h>
#import <AVKit/AVRoutePickerView.h>

#endif // TARGET_OS_OSX

#if TARGET_OS_IOS
#import <AVKit/AVInputPickerInteraction.h>
#endif // TARGET_OS_IOS

#if TARGET_OS_IOS && !TARGET_OS_VISION
#import <AVKit/AVCaptureEvent.h>
#import <AVKit/AVCaptureEventInteraction.h>
#import <AVKit/AVCaptureEventSound.h>
#import <AVKit/AVError.h>
#import <AVKit/AVPictureInPictureController.h>
#import <AVKit/AVPictureInPictureController_AVSampleBufferDisplayLayerSupport.h>
#import <AVKit/AVPictureInPictureController_VideoCallSupport.h>
#import <AVKit/AVPlaybackRouteSelecting.h>
#import <AVKit/AVPlayerItem+AVKitAdditions.h>
#import <AVKit/AVPlayerViewController.h>
#import <AVKit/AVRoutePickerView.h>

// Catalyst excluded headers
#if !TARGET_OS_MACCATALYST
#import <AVKit/AVInterstitialTimeRange.h>
// Included in AVKitCore on catalyst
#import <AVKit/AVPlaybackSpeed.h>
#endif

#endif // TARGET_OS_IOS && !TARGET_OS_VISION


#if TARGET_OS_TV
#import <AVKit/AVContentProposal.h>
#import <AVKit/AVContentProposalViewController.h>
#import <AVKit/AVContinuityDevicePickerViewController.h>
#import <AVKit/AVDisplayManager.h>
#import <AVKit/AVError.h>
#import <AVKit/AVInterstitialTimeRange.h>
#import <AVKit/AVNavigationMarkersGroup.h>
#import <AVKit/AVPictureInPictureController.h>
#import <AVKit/AVPictureInPictureController_AVSampleBufferDisplayLayerSupport.h>
#import <AVKit/AVPlaybackSpeed.h>
#import <AVKit/AVPlayerItem.h>
#import <AVKit/AVPlayerViewController.h>
#import <AVKit/AVRoutePickerView.h>
#import <AVKit/UIWindow.h>

#endif // TARGET_OS_TV


#if TARGET_OS_VISION
#import <AVKit/AVDisplayManager.h>
#import <AVKit/AVCaptureEventInteraction.h>
#import <AVKit/AVCaptureEvent.h>
#import <AVKit/AVError.h>
#import <AVKit/AVInterstitialTimeRange.h>
#import <AVKit/AVPictureInPictureController.h>
#import <AVKit/AVPictureInPictureController_AVSampleBufferDisplayLayerSupport.h>
#import <AVKit/AVPictureInPictureController_VideoCallSupport.h>
#import <AVKit/AVPlaybackRouteSelecting.h>
#import <AVKit/AVPlaybackSpeed.h>
#import <AVKit/AVPlayerItem+AVKitAdditions.h>
#import <AVKit/AVPlayerViewController.h>
#import <AVKit/AVRoutePickerView.h>
#import <AVKit/UIWindow_AVAdditions.h>

#endif // TARGET_OS_VISION
