//
//  ILNetworkResponse.h
//  IdentityLookup
//
//  Copyright © 2017 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <IdentityLookup/ILBase.h>

NS_ASSUME_NONNULL_BEGIN

/// A response to an HTTPS network request.
IL_EXTERN API_AVAILABLE(ios(11.0), macCatalyst(13.0)) API_UNAVAILABLE( tvos) API_UNAVAILABLE(macos, watchos)
@interface ILNetworkResponse : NSObject <NSSecureCoding>

/// Represents the URL response itself. See documentation for NSHTTPURLResponse.
@property (nonatomic, readonly) NSHTTPURLResponse *urlResponse;

/// Data returned in the HTTPS response.
@property (nonatomic, readonly) NSData *data;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
