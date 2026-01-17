//
//  ILCommunication.h
//  IdentityLookup
//
//  Copyright © 2018 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <IdentityLookup/ILBase.h>

NS_ASSUME_NONNULL_BEGIN

/// An incident of communication via some medium.
IL_EXTERN API_AVAILABLE(ios(12.0), macCatalyst(13.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos)
@interface ILCommunication : NSObject <NSSecureCoding>

/// The phone number or e-mail address of the sender.  The value will be nil if the sender is unknown.
@property (nonatomic, readonly, copy, nullable) NSString *sender;

@property (nonatomic, readonly, copy) NSDate *dateReceived;

- (BOOL)isEqualToCommunication:(ILCommunication *)communication NS_SWIFT_UNAVAILABLE("Use == operator instead");

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
