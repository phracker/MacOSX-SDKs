//
//  NWBonjourServiceEndpoint.h
//  Network
//
//  Copyright (c) 2014-2016 Apple Inc. All rights reserved.
//

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
NS_CLASS_AVAILABLE(10_11, 9_0)
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
						  domain:(NSString *)domain NS_AVAILABLE(10_11, 9_0);

/*!
 * @property name
 * @discussion The endpoint's Bonjour service name.
 */
@property (readonly) NSString *name NS_AVAILABLE(10_11, 9_0);

/*!
 * @property type
 * @discussion The endpoint's Bonjour service type.
 */
@property (readonly) NSString *type NS_AVAILABLE(10_11, 9_0);

/*!
 * @property domain
 * @discussion The endpoint's Bonjour service domain.
 */
@property (readonly) NSString *domain NS_AVAILABLE(10_11, 9_0);

@end

NS_ASSUME_NONNULL_END

#endif // __NWBonjourServiceEndpoint_h_
