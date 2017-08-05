//
//  AUViewController.h
//	Framework: CoreAudioKit
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <AudioUnit/AudioUnit.h>
#import <Foundation/NSExtensionRequestHandling.h>

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
typedef UIViewController AUViewControllerBase;
#else
#import <AppKit/AppKit.h>
typedef NSViewController AUViewControllerBase;
#endif

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_11, 9_0)
@interface AUViewController : AUViewControllerBase <NSExtensionRequestHandling>
@end

@interface AUAudioUnit (AUAudioUnit_ViewController)
/*!	@method	requestViewControllerWithCompletionHandler:
	@brief	Obtains an audio unit's view controller (and thereby a view).
	@discussion
		Asynchronously requests the audio unit's view controller. This method will later call the
		completion handler, in a thread/dispatch queue context internal to the implementation, with
		a view controller, or nil in the case of an audio unit without a custom view controller.
*/
- (void)requestViewControllerWithCompletionHandler:(void (^)(AUViewControllerBase * __nullable viewController))completionHandler;

@end

NS_ASSUME_NONNULL_END
