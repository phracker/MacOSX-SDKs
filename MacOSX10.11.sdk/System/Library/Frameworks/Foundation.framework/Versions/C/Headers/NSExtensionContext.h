/*	NSExtensionContext.h
        Copyright (c) 2013-2014, Apple Inc. All rights reserved.
*/

#import <Foundation/Foundation.h>

#if __OBJC2__

// Class representing the extension request's context
NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_10, 8_0)
@interface NSExtensionContext : NSObject

// The list of input NSExtensionItems associated with the context. If the context has no input items, this array will be empty.
@property(readonly, copy, NS_NONATOMIC_IOSONLY) NSArray *inputItems;

// Signals the host to complete the app extension request with the supplied result items. The completion handler optionally contains any work which the extension may need to perform after the request has been completed, as a background-priority task. The `expired` parameter will be YES if the system decides to prematurely terminate a previous non-expiration invocation of the completionHandler. Note: calling this method will eventually dismiss the associated view controller.
- (void)completeRequestReturningItems:(nullable NSArray *)items completionHandler:(void(^ __nullable)(BOOL expired))completionHandler;

// Signals the host to cancel the app extension request, with the supplied error, which should be non-nil. The userInfo of the NSError will contain a key NSExtensionItemsAndErrorsKey which will have as its value a dictionary of NSExtensionItems and associated NSError instances.
- (void)cancelRequestWithError:(NSError *)error;

// Asks the host to open an URL on the extension's behalf
- (void)openURL:(NSURL *)URL completionHandler:(void (^ __nullable)(BOOL success))completionHandler;

@end

// Key in userInfo. Value is a dictionary of NSExtensionItems and associated NSError instances.
FOUNDATION_EXTERN NSString * __null_unspecified const NSExtensionItemsAndErrorsKey NS_AVAILABLE(10_10, 8_0);

// The host process will enter the foreground
FOUNDATION_EXTERN NSString * __null_unspecified const NSExtensionHostWillEnterForegroundNotification NS_AVAILABLE_IOS(8_2);

// The host process did enter the background
FOUNDATION_EXTERN NSString * __null_unspecified const NSExtensionHostDidEnterBackgroundNotification NS_AVAILABLE_IOS(8_2);

// The host process will resign active status (stop receiving events), the extension may be suspended
FOUNDATION_EXTERN NSString * __null_unspecified const NSExtensionHostWillResignActiveNotification NS_AVAILABLE_IOS(8_2);

// The host process did become active (begin receiving events)
FOUNDATION_EXTERN NSString * __null_unspecified const NSExtensionHostDidBecomeActiveNotification NS_AVAILABLE_IOS(8_2);

NS_ASSUME_NONNULL_END

#endif
