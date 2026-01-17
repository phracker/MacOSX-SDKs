//
//  ILMessageFilterQueryRequest.h
//  IdentityLookup
//
//  Copyright © 2017 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <IdentityLookup/ILBase.h>

NS_ASSUME_NONNULL_BEGIN

/// A request to query a MessageFilter extension about how to interpret a received message.
IL_EXTERN API_AVAILABLE(ios(11.0), macCatalyst(13.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos)
@interface ILMessageFilterQueryRequest : NSObject <NSSecureCoding>

/// The sender of the message the receiver relates to.
@property (nonatomic, readonly, nullable) NSString *sender;

/// The body of the message the receiver relates to.
@property (nonatomic, readonly, nullable) NSString *messageBody;

/// The ISO Country Code of the receiving phone number, in format specified by the ISO 3166-2 standard
@property (nonatomic, readonly, nullable) NSString *receiverISOCountryCode API_AVAILABLE(ios(16.0), macCatalyst(16.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos);

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
