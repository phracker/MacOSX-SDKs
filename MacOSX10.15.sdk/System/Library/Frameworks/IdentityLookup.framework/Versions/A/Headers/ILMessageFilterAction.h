//
//  ILMessageFilterAction.h
//  IdentityLookup
//
//  Copyright © 2017 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// Describes an action to take in response to a received message.
typedef NS_ENUM(NSInteger, ILMessageFilterAction) {
    /// Insufficient information to determine an action to take. In a query response, has the effect of allowing the message to be shown normally.
    ILMessageFilterActionNone = 0,

    /// Allow the message to be shown normally.
    ILMessageFilterActionAllow = 1,

    /// Prevent the message from being shown normally.
    ILMessageFilterActionFilter = 2,
} API_AVAILABLE(ios(11.0), macCatalyst(13.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos);

NS_ASSUME_NONNULL_END
