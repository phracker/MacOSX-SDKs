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


NS_ASSUME_NONNULL_BEGIN

/*!
 * @interface NWBonjourServiceEndpoint
 * @discussion NWBonjourServiceEndpoint is a subclass of NWEndpoint. It represents an endpoint
 *		backed by a Bonjour service, specified with a name, type, and domain. For example, the
 *		Bonjour service MyMusicStudio._music._tcp.local. has the name "MyMusicStudio",
 *		the type "_music._tcp", and the domain "local".
 */
API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos)
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
						  domain:(NSString *)domain API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property name
 * @discussion The endpoint's Bonjour service name.
 */
@property (readonly) NSString *name API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property type
 * @discussion The endpoint's Bonjour service type.
 */
@property (readonly) NSString *type API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property domain
 * @discussion The endpoint's Bonjour service domain.
 */
@property (readonly) NSString *domain API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END

#endif // __NWBonjourServiceEndpoint_h_

#endif // __NE_TAPI__
