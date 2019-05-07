/*
	File:  AVKit.h
	
	Framework:  AVKit
	
	Copyright © 2013-2016 Apple Inc. All rights reserved.
	
	To report bugs, go to:  http://developer.apple.com/bugreporter/
	
 */

#import <AVKit/AVKitDefines.h>

#if TARGET_OS_IPHONE
#import <AVKit/AVError.h>
#import <AVKit/AVPictureInPictureController.h>
#import <AVKit/AVPlayerViewController.h>
#import <AVKit/AVRoutePickerView.h>
#else
#import <AVKit/AVCaptureView.h>
#import <AVKit/AVPlayerView.h>
#endif // TARGET_OS_IPHONE
