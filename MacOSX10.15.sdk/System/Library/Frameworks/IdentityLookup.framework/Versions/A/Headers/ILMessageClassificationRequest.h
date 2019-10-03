//
//  ILMessageClassificationRequest.h
//  IdentityLookup
//
//  Copyright © 2018 Apple. All rights reserved.
//

#import <IdentityLookup/ILClassificationRequest.h>

NS_ASSUME_NONNULL_BEGIN

@class ILMessageCommunication;

IL_EXTERN API_AVAILABLE(ios(12.0), macCatalyst(13.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos)
@interface ILMessageClassificationRequest : ILClassificationRequest <NSSecureCoding>

// An array of message communications sorted by date received
@property (nonatomic, readonly, copy) NSArray<ILMessageCommunication *> *messageCommunications;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
