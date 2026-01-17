//
//  SFSafariPage.h
//  SafariServices
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <SafariServices/SFFoundation.h>

#if __OBJC2__

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class SFSafariPageProperties;
@class SFSafariTab;

SF_CLASS_AVAILABLE_MAC_SAFARI(10_0)
@interface SFSafariPage : NSObject <NSCopying, NSSecureCoding>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// Dispatches a message to the content script injected in this page.
- (void)dispatchMessageToScriptWithName:(NSString *)messageName userInfo:(nullable NSDictionary<NSString *, id> *)userInfo;

/// Reloads the page.
- (void)reload;

/// This calls the completion handler with the properties of the page.
- (void)getPagePropertiesWithCompletionHandler:(void (^)(SFSafariPageProperties * _Nullable properties))completionHandler;

/// This calls the completion handler with the tab containing this page. This will return a non-nil tab for any pages being preloaded by Safari.
- (void)getContainingTabWithCompletionHandler:(void (^)(SFSafariTab *tab))completionHandler SF_AVAILABLE_MAC_SAFARI(12_1);

/// Gets a screenshot of the currently visible area of the page.
- (void)getScreenshotOfVisibleAreaWithCompletionHandler:(void (^)(NSImage * _Nullable image))completionHandler SF_AVAILABLE_MAC_SAFARI(12_1);

@end

NS_ASSUME_NONNULL_END

#endif // __OBJC2__
