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

    /// Prevent the message from being shown normally, filtered as Junk message.
    ILMessageFilterActionJunk = 2,
    ILMessageFilterActionFilter API_DEPRECATED_WITH_REPLACEMENT("ILMessageFilterActionJunk", ios(11.0, 14.0), macCatalyst(13.0,14.0)) API_UNAVAILABLE(macos, watchos) = ILMessageFilterActionJunk,

    /// Prevent the message from being shown normally, filtered as Promotional message.
    ILMessageFilterActionPromotion API_AVAILABLE(ios(14.0), macCatalyst(14.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos) = 3,

    /// Prevent the message from being shown normally, filtered as Transactional message.
    ILMessageFilterActionTransaction API_AVAILABLE(ios(14.0), macCatalyst(14.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos) = 4,
} API_AVAILABLE(ios(11.0), macCatalyst(13.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos);

NS_ASSUME_NONNULL_END
