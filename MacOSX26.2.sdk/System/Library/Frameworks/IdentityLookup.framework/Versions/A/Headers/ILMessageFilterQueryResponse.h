//
//  ILMessageFilterQueryResponse.h
//  IdentityLookup
//
//  Copyright © 2017 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <IdentityLookup/ILBase.h>
#import <IdentityLookup/ILMessageFilterAction.h>

NS_ASSUME_NONNULL_BEGIN

/// A response to an ILMessageFilterQueryRequest.
IL_EXTERN API_AVAILABLE(ios(11.0), macCatalyst(13.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos)
@interface ILMessageFilterQueryResponse : NSObject <NSSecureCoding>

/// Action to take for the received message.
@property (nonatomic) ILMessageFilterAction action;

/// SubAction to take for the received message.
@property (nonatomic) ILMessageFilterSubAction subAction API_AVAILABLE(ios(16.0), macCatalyst(16.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos);

@end

NS_ASSUME_NONNULL_END
