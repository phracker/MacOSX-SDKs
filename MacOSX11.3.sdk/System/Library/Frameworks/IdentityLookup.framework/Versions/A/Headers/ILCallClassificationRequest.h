//
//  ILCallClassificationRequest.h
//  IdentityLookup
//
//  Copyright © 2018 Apple. All rights reserved.
//

#import <IdentityLookup/ILClassificationRequest.h>

NS_ASSUME_NONNULL_BEGIN

@class ILCallCommunication;

IL_EXTERN API_AVAILABLE(ios(12.0), macCatalyst(13.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos)
@interface ILCallClassificationRequest : ILClassificationRequest <NSSecureCoding>

// An array of call communications sorted by date received
@property (nonatomic, readonly, copy) NSArray<ILCallCommunication *> *callCommunications;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
