/*
	File:  AVKit.h
	
	Framework:  AVKit
	
	Copyright © 2013-2016 Apple Inc. All rights reserved.
	
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

#endif // TARGET_OS_OSX || TARGET_OS_MACCATALYST


#if TARGET_OS_IPHONE
#import <AVKit/AVError.h>
#import <AVKit/AVPictureInPictureController.h>
#import <AVKit/AVPictureInPictureController_AVSampleBufferDisplayLayerSupport.h>
#import <AVKit/AVPictureInPictureController_VideoCallSupport.h>
#import <AVKit/AVPlayerItem+AVKitAdditions.h>
#import <AVKit/AVPlayerViewController.h>
#import <AVKit/AVPlaybackRouteSelecting.h>
#import <AVKit/AVRoutePickerView.h>

#else

#import <AVKit/AVCaptureView.h>
#import <AVKit/AVPictureInPictureController.h>
#import <AVKit/AVPictureInPictureController_AVSampleBufferDisplayLayerSupport.h>
#import <AVKit/AVPlayerView.h>
#import <AVKit/AVRoutePickerView.h>

#endif // TARGET_OS_IPHONE
