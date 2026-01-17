//
//  SFSafariWindow.h
//  SafariServices
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <SafariServices/SFFoundation.h>

#if __OBJC2__

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class SFSafariTab;
@class SFSafariToolbarItem;

SF_CLASS_AVAILABLE_MAC_SAFARI(10_0)
@interface SFSafariWindow : NSObject <NSCopying, NSSecureCoding>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// Calls the completion handler with the active tab in the window.
- (void)getActiveTabWithCompletionHandler:(void (^)(SFSafariTab * _Nullable activeTab))completionHandler;

/// Calls the completion handler with all of the tabs in this window ordered left to right.
- (void)getAllTabsWithCompletionHandler:(void (^)(NSArray<SFSafariTab *> *tabs))completionHandler SF_AVAILABLE_MAC_SAFARI(12_1);

/// This will open a tab at the end of the tab list. The completion handler is called when the tab has been opened.
- (void)openTabWithURL:(NSURL *)url makeActiveIfPossible:(BOOL)activateTab completionHandler:(void (^ _Nullable)(SFSafariTab * _Nullable tab))completionHandler;

/// Gets the extension’s toolbar item in this window.
- (void)getToolbarItemWithCompletionHandler:(void (^)(SFSafariToolbarItem * _Nullable toolbarItem))completionHandler;

/// Closes this window.
- (void)close SF_AVAILABLE_MAC_SAFARI(12_1);

@end

NS_ASSUME_NONNULL_END

#endif // __OBJC2__
