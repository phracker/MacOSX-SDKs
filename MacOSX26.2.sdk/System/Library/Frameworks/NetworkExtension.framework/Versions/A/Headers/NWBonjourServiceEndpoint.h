//
//  NWBonjourServiceEndpoint.h
//  Network
//
//  Copyright (c) 2014-2016, 2018 Apple Inc. All rights reserved.
//

#ifndef __NE_TAPI__

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif // __NE_INDIRECT__

#ifndef __NWBonjourServiceEndpoint_h_
#define __NWBonjourServiceEndpoint_h_

/**
 * DEPRECATION NOTICE
 *
 * NW object wrappers are hidden in Swift 6. To continue accessing them, you
 * can prepend double underscores to the symbol name.
 */

NS_ASSUME_NONNULL_BEGIN

/*!
 * @interface NWBonjourServiceEndpoint
 * @discussion NWBonjourServiceEndpoint is a subclass of NWEndpoint. It represents an endpoint
 *		backed by a Bonjour service, specified with a name, type, and domain. For example, the
 *		Bonjour service MyMusicStudio._music._tcp.local. has the name "MyMusicStudio",
 *		the type "_music._tcp", and the domain "local".
 */
API_DEPRECATED("Use `nw_endpoint_t` in Network framework instead, see deprecation notice in <NetworkExtension/NWBonjourServiceEndpoint.h>", macos(10.11, 15.0), ios(9.0, 18.0), tvos(17.0, 18.0), visionos(1.0, 2.0))
API_UNAVAILABLE(watchos)
@interface NWBonjourServiceEndpoint : NWEndpoint

/*!
 * @method endpointWithName:type:domain:
 * @param name The Bonjour service name.
 * @param type The Bonjour service type.
 * @param domain The Bonjour service domain.
 * @return An initialized NWBonjourServiceEndpoint object.
 */
+ (instancetype)endpointWithName:(NSString *)name
							type:(NSString *)type
						  domain:(NSString *)domain
API_DEPRECATED("Use `nw_endpoint_create_bonjour_service` in Network framework instead, see deprecation notice in <NetworkExtension/NWBonjourServiceEndpoint.h>", macos(10.11, 15.0), ios(9.0, 18.0), tvos(17.0, 18.0), visionos(1.0, 2.0))
API_UNAVAILABLE(watchos);

/*!
 * @property name
 * @discussion The endpoint's Bonjour service name.
 */
@property (nonatomic, readonly) NSString *name
API_DEPRECATED("Use `nw_endpoint_get_bonjour_service_name` in Network framework instead, see deprecation notice in <NetworkExtension/NWBonjourServiceEndpoint.h>", macos(10.11, 15.0), ios(9.0, 18.0), tvos(17.0, 18.0), visionos(1.0, 2.0))
API_UNAVAILABLE(watchos);


/*!
 * @property type
 * @discussion The endpoint's Bonjour service type.
 */
@property (nonatomic, readonly) NSString *type
API_DEPRECATED("Use `nw_endpoint_get_bonjour_service_type` in Network framework instead, see deprecation notice in <NetworkExtension/NWBonjourServiceEndpoint.h>", macos(10.11, 15.0), ios(9.0, 18.0), tvos(17.0, 18.0), visionos(1.0, 2.0))
API_UNAVAILABLE(watchos);


/*!
 * @property domain
 * @discussion The endpoint's Bonjour service domain.
 */
@property (nonatomic, readonly) NSString *domain
API_DEPRECATED("Use `nw_endpoint_get_bonjour_service_domain` in Network framework instead, see deprecation notice in <NetworkExtension/NWBonjourServiceEndpoint.h>", macos(10.11, 15.0), ios(9.0, 18.0), tvos(17.0, 18.0), visionos(1.0, 2.0))
API_UNAVAILABLE(watchos);

@end

NS_ASSUME_NONNULL_END

#endif // __NWBonjourServiceEndpoint_h_

#endif // __NE_TAPI__
