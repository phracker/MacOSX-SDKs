/*	NSExtensionContext.h
        Copyright (c) 2013-2014, Apple Inc. All rights reserved.
*/

#import <Foundation/Foundation.h>

#if __OBJC2__

// Class representing the extension request's context
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface NSExtensionContext : NSObject

// The list of input NSExtensionItems associated with the context. If the context has no input items, this array will be empty.
@property(readonly, copy, NS_NONATOMIC_IOSONLY) NSArray *inputItems;

// Signals the host to complete the app extension request with the supplied result items. The completion handler optionally contains any work which the extension may need to perform after the request has been completed, as a background-priority task. The `expired` parameter will be YES if the system decides to prematurely terminate a previous non-expiration invocation of the completionHandler. Note: calling this method will eventually dismiss the associated view controller.
- (void)completeRequestReturningItems:(NSArray *)items completionHandler:(void(^)(BOOL expired))completionHandler;

// Signals the host to cancel the app extension request, with the supplied error, which should be non-nil. The userInfo of the NSError will contain a key NSExtensionItemsAndErrorsKey which will have as its value a dictionary of NSExtensionItems and associated NSError instances.
- (void)cancelRequestWithError:(NSError *)error;

// Asks the host to open an URL on the extension's behalf
- (void)openURL:(NSURL *)URL completionHandler:(void (^)(BOOL success))completionHandler;

@end

// Key in userInfo. Value is a dictionary of NSExtensionItems and associated NSError instances.
FOUNDATION_EXTERN NSString *const NSExtensionItemsAndErrorsKey NS_AVAILABLE(10_10, 8_0);

#endif
