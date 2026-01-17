//
// ReplayKit.h
// ReplayKit
//
// Copyright © 2015 Apple Inc. All rights reserved.
//

#import <TargetConditionals.h>

#if TARGET_OS_OSX
#import <AppKit/AppKit.h>
#else
#import <UIKit/UIKit.h>
#endif

#import <ReplayKit/RPPreviewViewController.h>
#import <ReplayKit/RPScreenRecorder.h>
#import <ReplayKit/RPBroadcast.h>
#import <ReplayKit/RPBroadcastExtension.h>
#import <ReplayKit/RPError.h>
