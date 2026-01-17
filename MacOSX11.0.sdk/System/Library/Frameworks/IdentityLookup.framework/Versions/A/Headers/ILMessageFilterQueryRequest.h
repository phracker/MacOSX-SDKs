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

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
