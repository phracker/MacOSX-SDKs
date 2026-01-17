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


// Describes a sub-action to take in response to a received message.
typedef NS_ENUM(NSInteger, ILMessageFilterSubAction) {
    /// Insufficient information to determine an action to take. In a query response, has the effect of allowing the message to be shown normally.
    ILMessageFilterSubActionNone = 0,
    
    /// TRANSACTIONAL SUB-ACTIONS
    
    /// Prevent the message from being shown normally, filtered as Other message.
    ILMessageFilterSubActionTransactionalOthers = 10000,

    /// Prevent the message from being shown normally, filtered as Finance message.
    ILMessageFilterSubActionTransactionalFinance = 10001,
    
    /// Prevent the message from being shown normally, filtered as Orders (eCommerce) message.
    ILMessageFilterSubActionTransactionalOrders = 10002,

    /// Prevent the message from being shown normally, filtered as Reminder message.
    ILMessageFilterSubActionTransactionalReminders = 10003,

    /// Prevent the message from being shown normally, filtered as Health message.
    ILMessageFilterSubActionTransactionalHealth = 10004,

    /// Prevent the message from being shown normally, filtered as Weather message.
    ILMessageFilterSubActionTransactionalWeather = 10005,

    /// Prevent the message from being shown normally, filtered as Carrier message.
    ILMessageFilterSubActionTransactionalCarrier = 10006,
    
    /// Prevent the message from being shown normally, filtered as Rewards message.
    ILMessageFilterSubActionTransactionalRewards = 10007,

    /// Prevent the message from being shown normally, filtered as Government message.
    ILMessageFilterSubActionTransactionalPublicServices = 10008,

    /// PROMOTIONAL SUB-ACTIONS

    /// Prevent the message from being shown normally, filtered as Others message.
    ILMessageFilterSubActionPromotionalOthers = 20000,

    /// Prevent the message from being shown normally, filtered as Offers message.
    ILMessageFilterSubActionPromotionalOffers = 20001,

    /// Prevent the message from being shown normally, filtered as Coupons message.
    ILMessageFilterSubActionPromotionalCoupons = 20002,
        
} API_AVAILABLE(ios(16.0), macCatalyst(16.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos);

NS_ASSUME_NONNULL_END
