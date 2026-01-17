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
@interface SFSafariWindow : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// Calls the completion handler with the active tab in the window.
- (void)getActiveTabWithCompletionHandler:(void (^)(SFSafariTab * _Nullable activeTab))completionHandler;

/// This will open a tab at the end of the tab list. The completion handler is called when the tab has been opened.
- (void)openTabWithURL:(NSURL *)url makeActiveIfPossible:(BOOL)activateTab completionHandler:(void (^ _Nullable)(SFSafariTab * _Nullable tab))completionHandler;

/// Gets the extension’s toolbar item in this window.
- (void)getToolbarItemWithCompletionHandler:(void (^)(SFSafariToolbarItem * _Nullable toolbarItem))completionHandler;

@end

NS_ASSUME_NONNULL_END

#endif // __OBJC2__
