//
//  NSURLSession+Network.h
//  Network
//
//  Copyright (c) 2023 Apple Inc. All rights reserved.
//

#if defined(__OBJC__)

#import <Network/Network.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0))
@interface NSURLSessionConfiguration (Network)

/*!
 * @property proxyConfigurations
 * @discussion An array of `nw_proxy_config_t` objects to apply to all connections in the URL session.
 */
#if OS_OBJECT_USE_OBJC
@property (copy) NSArray<nw_proxy_config_t> *proxyConfigurations NS_REFINED_FOR_SWIFT;
#else
@property (copy) NSArray *proxyConfigurations NS_REFINED_FOR_SWIFT;
#endif

@end

NS_ASSUME_NONNULL_END

#endif // __OBJC__
