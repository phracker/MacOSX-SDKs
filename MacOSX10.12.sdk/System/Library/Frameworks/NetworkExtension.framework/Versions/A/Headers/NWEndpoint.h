//
//  NWEndpoint
//  Network
//
//  Copyright (c) 2014-2016 Apple Inc. All rights reserved.
//

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
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NWEndpoint : NSObject <NSSecureCoding, NSCopying>

@end

NS_ASSUME_NONNULL_END

#endif // __NWEndpoint_h_
