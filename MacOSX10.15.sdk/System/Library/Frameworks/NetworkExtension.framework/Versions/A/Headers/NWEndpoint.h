//
//  NWEndpoint
//  Network
//
//  Copyright (c) 2014-2016, 2018 Apple Inc. All rights reserved.
//

#ifndef __NE_TAPI__

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif // __NE_INDIRECT__

#ifndef __NWEndpoint_h_
#define __NWEndpoint_h_


NS_ASSUME_NONNULL_BEGIN

/*!
 * @interface NWEndpoint
 * @discussion NWEndpoint is a generic class to represent network endpoints, such as a port on a remote server.
 */
API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos)
@interface NWEndpoint : NSObject <NSSecureCoding, NSCopying>

@end

NS_ASSUME_NONNULL_END

#endif // __NWEndpoint_h_

#endif // __NE_TAPI__
