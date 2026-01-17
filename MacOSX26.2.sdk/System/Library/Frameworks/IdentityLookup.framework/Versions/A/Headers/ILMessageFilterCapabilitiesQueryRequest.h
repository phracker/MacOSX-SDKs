//
//  ILMessageFilterCapabilitiesQueryRequest.h
//  IdentityLookup
//
//  Copyright © 2021 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <IdentityLookup/ILBase.h>

NS_ASSUME_NONNULL_BEGIN

/// A request to query a MessageFilter extension about how to interpret a received message.
IL_EXTERN API_AVAILABLE(ios(16.0), macCatalyst(16.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos)
@interface ILMessageFilterCapabilitiesQueryRequest : NSObject <NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

@end
NS_ASSUME_NONNULL_END
