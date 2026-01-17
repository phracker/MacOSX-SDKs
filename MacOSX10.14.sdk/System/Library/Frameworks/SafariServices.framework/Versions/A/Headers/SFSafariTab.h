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

SF_CLASS_AVAILABLE_MAC_SAFARI(10_0)
@interface SFSafariTab : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// This calls the completion handler passing the active page in the tab.
- (void)getActivePageWithCompletionHandler:(void (^)(SFSafariPage * _Nullable activePage))completionHandler;

/// This calls the completion handler passing all the pages in the tab. This includes the active page and any pages being preloaded by Safari.
- (void)getPagesWithCompletionHandler:(void (^)(NSArray <SFSafariPage *> * _Nullable pages))completionHandler;

/// Activates this tab in the window it belongs to.
- (void)activateWithCompletionHandler:(void (^ _Nullable)(void))completionHandler;

@end

NS_ASSUME_NONNULL_END

#endif // __OBJC2__
