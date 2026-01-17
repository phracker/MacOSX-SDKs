//
//  SFSafariApplication.h
//  SafariServices
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <SafariServices/SFFoundation.h>

#if __OBJC2__

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

SF_EXTERN NSString * const SFExtensionMessageKey SF_AVAILABLE_MAC_SAFARI(14_0);

@class NSRunningApplication;
@class SFSafariWindow;

SF_CLASS_AVAILABLE_MAC_SAFARI(10_0)
@interface SFSafariApplication : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// Calls the completion handler with the active browser window.
+ (void)getActiveWindowWithCompletionHandler:(void (^)(SFSafariWindow * _Nullable activeWindow))completionHandler;

/// Calls the completion handler with all currently open windows ordered front to back.
+ (void)getAllWindowsWithCompletionHandler:(void (^)(NSArray<SFSafariWindow *> *windows))completionHandler SF_AVAILABLE_MAC_SAFARI(12_1);

/// Opens a new window with a tab containing the URL to pass in.
+ (void)openWindowWithURL:(NSURL *)url completionHandler:(void (^ _Nullable)(SFSafariWindow * _Nullable window))completionHandler;

/// This will cause -validateToolbarItemInWindow:completionHandler: to be called on all windows, to let the extension update enabled states or badges of its toolbar items.
+ (void)setToolbarItemsNeedUpdate;

/// Gets an NSRunningApplication instance with information about the app that this extension is connected to.
+ (void)getHostApplicationWithCompletionHandler:(void (^)(NSRunningApplication *hostApplication))completionHandler SF_AVAILABLE_MAC_SAFARI(11_0);

/// Opens Safari Extensions preferences and selects extension with the identifier.
+ (void)showPreferencesForExtensionWithIdentifier:(NSString *)identifier completionHandler:(void (^ _Nullable)(NSError * _Nullable error))completionHandler NS_EXTENSION_UNAVAILABLE("Not available to extensions");

// Dispatches a message to the Safari Extension with the given identifier.
+ (void)dispatchMessageWithName:(NSString *)messageName toExtensionWithIdentifier:(NSString *)identifier userInfo:(nullable NSDictionary<NSString *, id> *)userInfo completionHandler:(void (^ _Nullable)(NSError * _Nullable error))completionHandler NS_EXTENSION_UNAVAILABLE("Not available to extensions") SF_AVAILABLE_MAC_SAFARI(10_1);

@end

NS_ASSUME_NONNULL_END

#endif // __OBJC2__
