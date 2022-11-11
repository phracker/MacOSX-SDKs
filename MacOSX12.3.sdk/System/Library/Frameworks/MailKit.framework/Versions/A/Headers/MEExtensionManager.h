//
//  MEExtensionManager.h
//  MailKit
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// @brief Methods in this class allow the host app to interact with their Mail extension.
API_AVAILABLE(macos(12.0)) API_UNAVAILABLE(ios, watchos, tvos, macCatalyst)
@interface MEExtensionManager : NSObject
+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;
/// @brief This will call on Mail to reload the content rule list associated with the given identifier. Mail May throttle reloading the content blocker to once every few minutes.
+ (void)reloadContentBlockerWithIdentifier:(NSString *)identifier completionHandler:(void (^ _Nullable)(NSError * _Nullable error))completionHandler;
/// @brief This will call on Mail to reload the currently visible messages.  Mail may throttle reloading visible messages.
+ (void)reloadVisibleMessagesWithCompletionHandler:(void (^ _Nullable)(NSError * _Nullable error))completionHandler;

@end

NS_ASSUME_NONNULL_END
