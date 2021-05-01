//
//  ILMessageCommunication.h
//  IdentityLookup
//
//  Copyright © 2018 Apple. All rights reserved.
//

#import <IdentityLookup/ILCommunication.h>

NS_ASSUME_NONNULL_BEGIN

IL_EXTERN API_AVAILABLE(ios(12.0), macCatalyst(13.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos)
@interface ILMessageCommunication : ILCommunication

// Contains the contents of the message
@property (nonatomic, readonly, copy, nullable) NSString *messageBody;

- (BOOL)isEqualToMessageCommunication:(ILMessageCommunication *)communication NS_SWIFT_UNAVAILABLE("Use == operator instead");

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
