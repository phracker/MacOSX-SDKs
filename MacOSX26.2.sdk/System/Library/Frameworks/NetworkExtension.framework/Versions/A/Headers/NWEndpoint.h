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

/**
 * DEPRECATION NOTICE
 *
 * NW object wrappers are hidden in Swift 6. To continue accessing them, you
 * can prepend double underscores to the symbol name.
 */

NS_ASSUME_NONNULL_BEGIN

/*!
 * @interface NWEndpoint
 * @discussion NWEndpoint is a generic class to represent network endpoints, such as a port on a remote server.
 */
API_DEPRECATED("Use nw_endpoint_t in Network framework instead, see deprecation notice in <NetworkExtension/NWEndpoint.h>", macos(10.11, 15.0), ios(9.0, 18.0), tvos(17.0, 18.0), visionos(1.0, 2.0))
API_UNAVAILABLE(watchos)
@interface NWEndpoint : NSObject <NSSecureCoding, NSCopying>

@end

NS_ASSUME_NONNULL_END

#endif // __NWEndpoint_h_

#endif // __NE_TAPI__
