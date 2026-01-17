// =================================================================================================
// AUGenericViewController.h
// =================================================================================================
/*
 File:         AUGenericViewController.h
 Framework:    CoreAudioKit
 
 Copyright (c) 2022 Apple Inc. All Rights Reserved.
 */

#import <CoreAudioKit/AUViewController.h>
#import <AVFoundation/AVFoundation.h>

#if TARGET_OS_IPHONE
typedef UIColor AUViewColor;
#else
typedef NSColor AUViewColor;
#endif

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(13.0), ios(16.0))
@interface AUGenericViewController : AUViewControllerBase

@property (nonatomic, strong, nullable) AUAudioUnit *auAudioUnit;

@end

NS_ASSUME_NONNULL_END
