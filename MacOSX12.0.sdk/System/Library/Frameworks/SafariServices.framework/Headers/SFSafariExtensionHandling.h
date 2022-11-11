//
//  SFSafariExtensionHandling.h
//  SafariServices
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#if __OBJC2__

#import <Foundation/Foundation.h>
#import <SafariServices/SFFoundation.h>

@class SFSafariExtensionViewController;
@class SFSafariPage;
@class SFSafariWindow;

NS_ASSUME_NONNULL_BEGIN

@protocol SFSafariExtensionHandling <NSObject>

@optional
/// This is called when a content script from an extension dispatches a message to the app extension.
- (void)messageReceivedWithName:(NSString *)messageName fromPage:(SFSafariPage *)page userInfo:(nullable NSDictionary<NSString *, id> *)userInfo;

/// This is called when the extension's containing app dispatches a message to the app extension.
- (void)messageReceivedFromContainingAppWithName:(NSString *)messageName userInfo:(nullable NSDictionary<NSString *, id> *)userInfo SF_AVAILABLE_MAC_SAFARI(10_1);

/// This is called when the extension's toolbar item is clicked.
- (void)toolbarItemClickedInWindow:(SFSafariWindow *)window;

/// This is called when Safari's state changed in some way that would require the extension's toolbar item to be validated again.
- (void)validateToolbarItemInWindow:(SFSafariWindow *)window validationHandler:(void (^)(BOOL enabled, NSString *badgeText))validationHandler;

/// This is called when one of the extension's context menu items is selected.
- (void)contextMenuItemSelectedWithCommand:(NSString *)command inPage:(SFSafariPage *)page userInfo:(nullable NSDictionary<NSString *, id> *)userInfo;

/// This is called before context menu is shown, and provides a way to validate individual context menu items.
- (void)validateContextMenuItemWithCommand:(NSString *)command inPage:(SFSafariPage *)page userInfo:(nullable NSDictionary<NSString *, id> *)userInfo validationHandler:(void (^)(BOOL shouldHide, NSString * _Nullable text))validationHandler SF_AVAILABLE_MAC_SAFARI(10_1);

/// This is called when the extension's popover is about to be opened.
- (void)popoverWillShowInWindow:(SFSafariWindow *)window;

/// This is called after the extension's popover is closed.
- (void)popoverDidCloseInWindow:(SFSafariWindow *)window;

/// Returns the extension popover's view controller.
- (SFSafariExtensionViewController *)popoverViewController;

/// This is called when Safari is about to load a page that the extension has stated it wants to add additional headers for.
- (void)additionalRequestHeadersForURL:(NSURL *)url completionHandler:(void (^)(NSDictionary<NSString *, NSString *> * _Nullable))completionHandler SF_AVAILABLE_MAC_SAFARI(11_1);

/// This is called when a content blocker associated with this Safari App Extension performs a blocking action.
- (void)contentBlockerWithIdentifier:(NSString *)contentBlockerIdentifier blockedResourcesWithURLs:(NSArray<NSURL *> *)urls onPage:(SFSafariPage *)page SF_AVAILABLE_MAC_SAFARI(13_0);

/// This is called when a page in Safari navigates to a URL. The URL will be nil when the extension doesn't have access to it.
- (void)page:(SFSafariPage *)page willNavigateToURL:(nullable NSURL *)url SF_AVAILABLE_MAC_SAFARI(13_0);

@end

NS_ASSUME_NONNULL_END

#endif // __OBJC2__
