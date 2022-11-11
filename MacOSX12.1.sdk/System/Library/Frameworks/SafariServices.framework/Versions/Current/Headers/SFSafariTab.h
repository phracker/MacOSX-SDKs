//
//  SFSafariTab.h
//  SafariServices
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <SafariServices/SFFoundation.h>

#if __OBJC2__

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class SFSafariPage;
@class SFSafariWindow;

SF_CLASS_AVAILABLE_MAC_SAFARI(10_0)
@interface SFSafariTab : NSObject <NSCopying, NSSecureCoding>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// This calls the completion handler passing the active page in the tab.
- (void)getActivePageWithCompletionHandler:(void (^)(SFSafariPage * _Nullable activePage))completionHandler;

/// This calls the completion handler passing all the pages in the tab. This includes the active page and any pages being preloaded by Safari.
- (void)getPagesWithCompletionHandler:(void (^)(NSArray <SFSafariPage *> * _Nullable pages))completionHandler;

/// This calls completion handler with the window containing this tab. If the tab is pinned, the window is nil.
- (void)getContainingWindowWithCompletionHandler:(void (^)(SFSafariWindow * _Nullable window))completionHandler SF_AVAILABLE_MAC_SAFARI(12_1);

/// Activates this tab in the window it belongs to.
- (void)activateWithCompletionHandler:(void (^ _Nullable)(void))completionHandler;

/// Navigates this tab to the given URL. The extension doesn't need permission to access the URL to navigate to it.
- (void)navigateToURL:(NSURL *)url SF_AVAILABLE_MAC_SAFARI(12_1);

/// Closes this tab. If this is the last tab in its window, the window is also closed.
- (void)close SF_AVAILABLE_MAC_SAFARI(12_1);

@end

NS_ASSUME_NONNULL_END

#endif // __OBJC2__
