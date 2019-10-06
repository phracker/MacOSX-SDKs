//
//  parameters.h
//  Network
//
//  Copyright (c) 2014-2019 Apple Inc. All rights reserved.
//

#ifndef __NW_PARAMETERS_H__
#define __NW_PARAMETERS_H__

#ifndef __NW_INDIRECT__
#warning "Please include <Network/Network.h> instead of this file directly."
#endif // __NW_INDIRECT__

#include <Network/protocol_options.h>
#include <Network/interface.h>
#include <Network/endpoint.h>
#include <Network/nw_object.h>

#include <stdint.h>
#include <stdbool.h>
#include <sys/socket.h>


__BEGIN_DECLS

NW_ASSUME_NONNULL_BEGIN

/*!
 * @typedef nw_parameters_t
 * @abstract
 *		A Network Parameters object contains the parameters necessary to create
 *		a network connection or listener. Parameters include any preferences for
 *		network paths (such as requried, prohibited, and preferred networks, and local
 *		endpoint requirements); preferences for data transfer and quality of service;
 *		and the protocols to be used for a connection along with any protocol-specific
 *		options.
 *
 *		This type supports ARC and the -[description] method. In non-ARC files, use
 *		nw_retain() and nw_release() to retain and release the object.
 */
#ifndef NW_PARAMETERS_IMPL
NW_OBJECT_DECL(nw_parameters);
#endif // NW_PARAMETERS_IMPL

/*!
 * @typedef nw_protocol_stack_t
 * @abstract
 *		A Network Protocol Stack contains a list of protocols to use for a connection.
 *		The members of the protocol stack are nw_protocol_options_t objects, each
 *		defining which protocol to use within the stack along with any protocol-specific
 *		options. Each stack includes an array of application-level protocols, a single
 *		transport-level protocol, and an optional internet-level protocol. If the internet-
 *		level protocol is not specified, any available and applicable IP address family
 *		may be used.
 *
 *		This type supports ARC and the -[description] method. In non-ARC files, use
 *		nw_retain() and nw_release() to retain and release the object.
 */
#ifndef NW_PROTOCOL_STACK_IMPL
NW_OBJECT_DECL(nw_protocol_stack);
#endif // NW_PROTOCOL_STACK_IMPL

#pragma mark - Initializers

#ifdef __BLOCKS__

typedef void (^nw_parameters_configure_protocol_block_t)(nw_protocol_options_t options);

#define NW_PARAMETERS_CONFIGURE_PROTOCOL_TYPE_DECL(name) \
	extern const nw_parameters_configure_protocol_block_t _nw_parameters_configure_protocol_##name

#define NW_PARAMETERS_DEFAULT_CONFIGURATION (_nw_parameters_configure_protocol_default_configuration)
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_PARAMETERS_CONFIGURE_PROTOCOL_TYPE_DECL(default_configuration);

#define NW_PARAMETERS_DISABLE_PROTOCOL (_nw_parameters_configure_protocol_disable)
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_PARAMETERS_CONFIGURE_PROTOCOL_TYPE_DECL(disable);

/*!
 * @function nw_parameters_create_secure_tcp
 *
 * @abstract
 *		Creates a parameters object that is configured for TLS and TCP. The caller can use
 *		the default configuration for TLS and TCP, or set specific options for each protocol,
 *		or disable TLS.
 *
 * @param configure_tls
 *		A block to configure TLS. To use the default TLS configuration, pass
 *		NW_PARAMETERS_DEFAULT_CONFIGURATION. To configure specific options, pass a custom
 *		block and operate on the nw_protocol_options_t object. To disable TLS, pass
 *		NW_PARAMETERS_DISABLE_PROTOCOL.
 *
 * @param configure_tcp
 *		A block to configure TCP. To use the default TCP configuration, pass
 *		NW_PARAMETERS_DEFAULT_CONFIGURATION. To configure specific options, pass a custom
 *		block and operate on the nw_protocol_options_t object. It is invalid to try
 *		to disable TCP using NW_PARAMETERS_DISABLE_PROTOCOL.
 *
 * @result
 *		Returns an allocated nw_parameters_t object on success.
 *		Callers are responsible for deallocating using nw_release(obj) or [obj release].
 *		These objects support ARC.
 *		Returns NULL on failure. Fails due to invalid parameters.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED nw_parameters_t
nw_parameters_create_secure_tcp(nw_parameters_configure_protocol_block_t configure_tls,
								nw_parameters_configure_protocol_block_t configure_tcp);

/*!
 * @function nw_parameters_create_secure_udp
 *
 * @abstract
 *		Creates a parameters object that is configured for DTLS and UDP. The caller can use
 *		the default configuration for DTLS and UDP, or set specific options for each protocol,
 *		or disable DTLS.
 *
 * @param configure_dtls
 *		A block to configure DTLS. To use the default DTLS configuration, pass
 *		NW_PARAMETERS_DEFAULT_CONFIGURATION. To configure specific options, pass a custom
 *		block and operate on the nw_protocol_options_t object. To disable DTLS, pass
 *		NW_PARAMETERS_DISABLE_PROTOCOL.
 *
 * @param configure_udp
 *		A block to configure UDP. To use the default UDP configuration, pass
 *		NW_PARAMETERS_DEFAULT_CONFIGURATION. To configure specific options, pass a custom
 *		block and operate on the nw_protocol_options_t object. It is invalid to try
 *		to disable UDP using NW_PARAMETERS_DISABLE_PROTOCOL.
 *
 * @result
 *		Returns an allocated nw_parameters_t object on success.
 *		Callers are responsible for deallocating using nw_release(obj) or [obj release].
 *		These objects support ARC.
 *		Returns NULL on failure. Fails due to invalid parameters.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED nw_parameters_t
nw_parameters_create_secure_udp(nw_parameters_configure_protocol_block_t configure_dtls,
								nw_parameters_configure_protocol_block_t configure_udp);

/*!
 * @function nw_parameters_create_custom_ip
 *
 * @abstract
 *		Creates a parameters object that is configured for a custom IP protocol.
 *		This allows the caller to create connections and listeners that send
 *		and receive IP datagrams where the protocol header contained by the IP
 *		datagram is identified by the provided protocol number. Protocols already
 *		registered by the system, such as TCP and UDP, will not be allowed.
 *
 *		Calling processes must hold the "com.apple.developer.networking.custom-protocol"
 *		entitlement.
 *
 * @param custom_ip_protocol_number
 *		The protocol number identifying a protocol carried by IP, as defined
 *		in RFC 5237.
 *
 * @param configure_ip
 *		A block to configure IP. To use the default IP configuration, pass
 *		NW_PARAMETERS_DEFAULT_CONFIGURATION. To configure specific options, pass a custom
 *		block and operate on the nw_protocol_options_t object. It is invalid to try
 *		to disable IP using NW_PARAMETERS_DISABLE_PROTOCOL.
 *
 * @result
 *		Returns an allocated nw_parameters_t object on success.
 *		Callers are responsible for deallocating using nw_release(obj) or [obj release].
 *		These objects support ARC.
 *		Returns NULL on failure. Fails due to invalid parameters.
 */
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, watchos, tvos)
NW_RETURNS_RETAINED nw_parameters_t
nw_parameters_create_custom_ip(uint8_t custom_ip_protocol_number,
							   nw_parameters_configure_protocol_block_t configure_ip);

#endif // __BLOCKS__

/*!
 * @function nw_parameters_create
 *
 * @abstract
 *		Creates a generic parameters object. Note that in order to use parameters
 *		with an nw_connection_t or an nw_listener_t, the parameters must have protocols
 *		added into the default nw_protocol_stack_t. Clients using standard protocol
 *		configurations should use nw_parameters_create_secure_tcp() or
 *		nw_parameters_create_secure_udp().
 *
 * @result
 *		Returns an allocated nw_parameters_t object on success.
 *		Callers are responsible for deallocating using nw_release(obj) or [obj release].
 *		These objects support ARC.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED nw_parameters_t
nw_parameters_create(void);

/*!
 * @function nw_parameters_copy
 *
 * @abstract
 *		Creates a deep copy of a parameters object that can be modified.
 *
 * @param parameters
 *		The existing parameters object to copy
 *
 * @result
 *		Returns a newly allocated nw_parameters_t object on success.
 *		Callers are responsible for deallocating using nw_release(obj) or [obj release].
 *		These objects support ARC.
 *		Returns NULL on failure. Fails due to invalid parameters.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED nw_parameters_t
nw_parameters_copy(nw_parameters_t parameters);

#pragma mark - Path Selection

/*!
 * @function nw_parameters_require_interface
 *
 * @abstract
 *		Require any connections or listeners using these parameters to use
 *		the provided network interface, or none if NULL is passed.
 *
 * @param parameters
 *		The parameters object to configure
 *
 * @param interface
 *		The interface to require for connections or listeners, or NULL to
 *		allow any interface.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_parameters_require_interface(nw_parameters_t parameters,
								_Nullable nw_interface_t interface);

/*!
 * @function nw_parameters_copy_required_interface
 *
 * @abstract
 *		Access the required network interface set on the parameters.
 *
 * @param parameters
 *		The parameters object to check
 *
 * @result
 *		Returns the interface that is required by the parameters, or
 *		NULL if no interface is required.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED _Nullable nw_interface_t
nw_parameters_copy_required_interface(nw_parameters_t parameters);

/*!
 * @function nw_parameters_prohibit_interface
 *
 * @abstract
 *		Prohibit any connections or listeners using these parameters from using
 *		the provided network interface.
 *
 * @param parameters
 *		The parameters object to configure
 *
 * @param interface
 *		The interface to prohibit for connections or listeners.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_parameters_prohibit_interface(nw_parameters_t parameters,
								 nw_interface_t interface);

/*!
 * @function nw_parameters_clear_prohibited_interfaces
 *
 * @abstract
 *		Clear any interfaces that had been prohibited.
 *
 * @param parameters
 *		The parameters object to modify
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_parameters_clear_prohibited_interfaces(nw_parameters_t parameters);

#ifdef __BLOCKS__

typedef bool (^nw_parameters_iterate_interfaces_block_t)(nw_interface_t interface);

/*!
 * @function nw_parameters_iterate_prohibited_interfaces
 *
 * @abstract
 *		List all prohibited network interfaces.
 *
 * @param parameters
 *		The parameters object to check
 *
 * @param iterate_block
 *		A block that will return the interfaces prohibited by the parameters. Returning
 *		true from the block will continue to iterate, and returning false will stop
 *		iterating.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_parameters_iterate_prohibited_interfaces(nw_parameters_t parameters,
											NW_NOESCAPE nw_parameters_iterate_interfaces_block_t iterate_block);

#endif // __BLOCKS__

/*!
 * @function nw_parameters_set_required_interface_type
 *
 * @abstract
 *		Require any connections or listeners using these parameters to use
 *		the provided network interface type.
 *
 * @param parameters
 *		The parameters object to configure
 *
 * @param interface_type
 *		The interface type to require for connections or listeners.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_parameters_set_required_interface_type(nw_parameters_t parameters,
									 nw_interface_type_t interface_type);

/*!
 * @function nw_parameters_get_required_interface_type
 *
 * @abstract
 *		Access the required network interface type set on the parameters.
 *
 * @param parameters
 *		The parameters object to check
 *
 * @result
 *		Returns the interface type that is required by the parameters, or
 *		nw_interface_type_other_t if no interface type is required.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
nw_interface_type_t
nw_parameters_get_required_interface_type(nw_parameters_t parameters);

/*!
 * @function nw_parameters_prohibit_interface_type
 *
 * @abstract
 *		Prohibit any connections or listeners using these parameters from using
 *		the provided network interface type.
 *
 * @param parameters
 *		The parameters object to configure
 *
 * @param interface_type
 *		The interface type to prohibit for connections or listeners.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_parameters_prohibit_interface_type(nw_parameters_t parameters,
									  nw_interface_type_t interface_type);

/*!
 * @function nw_parameters_clear_prohibited_interface_types
 *
 * @abstract
 *		Clear any interface types that had been prohibited.
 *
 * @param parameters
 *		The parameters object to modify
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_parameters_clear_prohibited_interface_types(nw_parameters_t parameters);

#ifdef __BLOCKS__

typedef bool (^nw_parameters_iterate_interface_types_block_t)(nw_interface_type_t interface_type);

/*!
 * @function nw_parameters_iterate_prohibited_interface_types
 *
 * @abstract
 *		List all prohibited network interface types.
 *
 * @param parameters
 *		The parameters object to check
 *
 * @param iterate_block
 *		A block that will return the interface types prohibited by the parameters. Returning
 *		true from the block will continue to iterate, and returning false will stop
 *		iterating.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_parameters_iterate_prohibited_interface_types(nw_parameters_t parameters,
												 NW_NOESCAPE nw_parameters_iterate_interface_types_block_t iterate_block);

#endif // __BLOCKS__

/*!
 * @function nw_parameters_set_prohibit_expensive
 *
 * @abstract
 *		Prohibit any connections or listeners using these parameters from using
 *		a network interface that is considered expensive by the system.
 *
 * @param parameters
 *		The parameters object to configure
 *
 * @param prohibit_expensive
 *		If true, prohibit the use of any expensive interfaces. If false,
 *		allow expensive interfaces. Defaults to false.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_parameters_set_prohibit_expensive(nw_parameters_t parameters,
									 bool prohibit_expensive);

/*!
 * @function nw_parameters_get_prohibit_expensive
 *
 * @abstract
 *		Check if the parameters prohibit expensive interfaces.
 *
 * @param parameters
 *		The parameters object to check
 *
 * @result
 *		Returns true if expensive interfaces are prohibited, or
 *		false otherwise.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
bool
nw_parameters_get_prohibit_expensive(nw_parameters_t parameters);

/*!
 * @function nw_parameters_set_prohibit_constrained
 *
 * @abstract
 *		Prohibit any connections or listeners using these parameters from using
 *		a network interface that is considered constrained by the system.
 *
 * @param parameters
 *		The parameters object to configure
 *
 * @param prohibit_constrained
 *		If true, prohibit the use of any constrained interfaces. If false,
 *		allow constrained interfaces. Defaults to false.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_parameters_set_prohibit_constrained(nw_parameters_t parameters,
									   bool prohibit_constrained);

/*!
 * @function nw_parameters_get_prohibit_constrained
 *
 * @abstract
 *		Check if the parameters prohibit constrained interfaces.
 *
 * @param parameters
 *		The parameters object to check
 *
 * @result
 *		Returns true if constrained interfaces are prohibited, or
 *		false otherwise.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
bool
nw_parameters_get_prohibit_constrained(nw_parameters_t parameters);

/*!
 * @function nw_parameters_set_reuse_local_address
 *
 * @abstract
 *		Allow any connections using these parameters to reuse
 *		local addresses already in use by other connections.
 *
 * @param parameters
 *		The parameters object to configure
 *
 * @param reuse_local_address
 *		If true, allow the reuse of local addresses. If false,
 *		disallow the reuse of local addresses. Defaults to false.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_parameters_set_reuse_local_address(nw_parameters_t parameters,
									  bool reuse_local_address);

/*!
 * @function nw_parameters_get_reuse_local_address
 *
 * @abstract
 *		Check if the parameters allow local address reuse.
 *
 * @param parameters
 *		The parameters object to check
 *
 * @result
 *		Returns true if local address reuse is allowed, or
 *		false otherwise.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
bool
nw_parameters_get_reuse_local_address(nw_parameters_t parameters);

/*!
 * @function nw_parameters_set_local_endpoint
 *
 * @abstract
 *		Specify a specific endpoint to use as the local endpoint.
 *		For connections, this will be used to initiate traffic;
 *		for listeners, this will be used for receiving incoming
 *		connections.
 *
 * @param parameters
 *		The parameters object to configure
 *
 * @param local_endpoint
 *		The endpoint to set as the local endpoint. Pass NULL to
 *		clear the local endpoint.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_parameters_set_local_endpoint(nw_parameters_t parameters,
								 _Nullable nw_endpoint_t local_endpoint);

/*!
 * @function nw_parameters_copy_local_endpoint
 *
 * @abstract
 *		Extract the local endpoint set on the connection.
 *
 * @param parameters
 *		The parameters object to configure
 *
 * @result
 *		Returns the endpoint that is set in the parameters, or
 *		NULL if no local endpoint is set.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED _Nullable nw_endpoint_t
nw_parameters_copy_local_endpoint(nw_parameters_t parameters);

/*!
 * @function nw_parameters_set_include_peer_to_peer
 *
 * @abstract
 *		Allow the inclusion of peer-to-peer interfaces when
 *		listening or establishing outbound connections. This parameter
 *		will not take effect if a specific interface is required.
 *		This parameter is applicable when advertising a Bonjour service
 *		on a listener, or connecting to a Bonjour service.
 *
 * @param parameters
 *		The parameters object to configure
 *
 * @param include_peer_to_peer
 *		If true, allow advertising, resolving, and connecting over
 *		peer-to-peer interfaces. Defaults to false.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_parameters_set_include_peer_to_peer(nw_parameters_t parameters,
									   bool include_peer_to_peer);

/*!
 * @function nw_parameters_get_include_peer_to_peer
 *
 * @abstract
 *		Check if the parameters allow the inclusion of
 *		peer-to-peer interfaces.
 *
 * @param parameters
 *		The parameters object to check
 *
 * @result
 *		Returns true if peer-to-peer interfaces are allowed,
 *		or false otherwise.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
bool
nw_parameters_get_include_peer_to_peer(nw_parameters_t parameters);

#pragma mark - Data Handling

/*!
 * @function nw_parameters_set_fast_open_enabled
 *
 * @abstract
 *		Use fast open for an outbound connection, which may be done at any
 *		protocol level. Use of fast open requires that the caller send
 *		idempotent data on the connection before the connection may move
 *		into the ready state. As a side effect, this may implicitly enable
 *		fast open for protocols in the stack, even if they did not have
 *		fast open explicitly enabled on them (such as the option to enable
 *		TCP Fast Open).
 *
 * @param parameters
 *		The parameters object to configure
 *
 * @param fast_open_enabled
 *		If true, indicate that fast open is requested and that idempotent data
 *		MUST be sent by the caller on the connection. If false,
 *		disallow the fast open at the top level protocol. Defaults to false.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_parameters_set_fast_open_enabled(nw_parameters_t parameters,
									bool fast_open_enabled);

/*!
 * @function nw_parameters_get_fast_open_enabled
 *
 * @abstract
 *		Check if the parameters allow the use of fast open for the top level
 *		protocol.
 *
 * @param parameters
 *		The parameters object to check
 *
 * @result
 *		Returns true if fast open is allowed for the top level protocol, or
 *		false otherwise.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
bool
nw_parameters_get_fast_open_enabled(nw_parameters_t parameters);

/*!
 * @typedef nw_service_class_t
 * @abstract
 *		The network service class represents the network queuing priority to use
 *		for traffic generated by a connection.
 */
typedef enum {
	/*! @const nw_service_class_best_effort Default priority traffic */
	nw_service_class_best_effort = 0,
	/*! @const nw_service_class_background Bulk traffic, or traffic that can be de-prioritized behind foreground traffic */
	nw_service_class_background = 1,
	/*! @const nw_service_class_interactive_video Interactive video traffic */
	nw_service_class_interactive_video = 2,
	/*! @const nw_service_class_interactive_voice Interactive voice traffic */
	nw_service_class_interactive_voice = 3,
	/*! @const nw_service_class_responsive_data Interactive user data */
	nw_service_class_responsive_data = 4,
	/*! @const nw_service_class_signaling Bursty but short. Intolerant of delay and loss. For example, SIP. */
	nw_service_class_signaling = 5,
} nw_service_class_t;

/*!
 * @function nw_parameters_set_service_class
 *
 * @abstract
 *		Set the data service class to use for connections.
 *
 * @param parameters
 *		The parameters object to configure
 *
 * @param service_class
 *		The service class value to use for connections. Defaults to nw_service_class_best_effort.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_parameters_set_service_class(nw_parameters_t parameters,
								nw_service_class_t service_class);

/*!
 * @function nw_parameters_get_service_class
 *
 * @abstract
 *		Check the service class configured on the parameters.
 *
 * @param parameters
 *		The parameters object to check
 *
 * @result
 *		Returns the effective service class configured on the parameters.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
nw_service_class_t
nw_parameters_get_service_class(nw_parameters_t parameters);

/*!
 * @typedef nw_multipath_service_t
 * @abstract
 *		Multipath services represent the modes of multipath usage that are
 *		allowed for connections.
 */
typedef enum {
	/*! @const nw_multipath_service_disabled No multipath transport will be attempted */
	nw_multipath_service_disabled = 0,
	/*! @const nw_multipath_service_handover Only use the expensive interface when the when the primary one is not available */
	nw_multipath_service_handover = 1,
	/*! @const nw_multipath_service_interactive Use the expensive interface more aggressively to reduce latency */
	nw_multipath_service_interactive = 2,
	/*! @const nw_multipath_service_aggregate Use all available interfaces to provide the highest throughput and lowest latency */
	nw_multipath_service_aggregate = 3,
} nw_multipath_service_t;

/*!
 * @function nw_parameters_set_multipath_service
 *
 * @abstract
 *		Set the multipath service to use for connections.
 *
 * @param parameters
 *		The parameters object to configure
 *
 * @param multipath_service
 *		The multipath service value to use for connections. Defaults to nw_multipath_service_disabled.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_parameters_set_multipath_service(nw_parameters_t parameters,
									nw_multipath_service_t multipath_service);

/*!
 * @function nw_parameters_get_multipath_service
 *
 * @abstract
 *		Check the multipath service mode configured on the parameters.
 *
 * @param parameters
 *		The parameters object to check
 *
 * @result
 *		Returns the multipath service configured on the parameters.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
nw_multipath_service_t
nw_parameters_get_multipath_service(nw_parameters_t parameters);

#pragma mark - Protocol Options

/*!
 * @function nw_parameters_copy_default_protocol_stack
 *
 * @abstract
 *		Retrieve the default protocol stack from a parameters object.
 *		Every parameters object will have a default protocol stack. For
 *		parameters created with a convenience initializer, this protocol
 *		stack will be pre-populated. For parameters created with the generic
 *		initializers, the stack will be empty.
 *
 * @param parameters
 *		The parameters object to check
 *
 * @result
 *		Returns an nw_protocol_stack_t object that can be inspected and modified.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED nw_protocol_stack_t
nw_parameters_copy_default_protocol_stack(nw_parameters_t parameters);

/*!
 * @function nw_protocol_stack_prepend_application_protocol
 *
 * @abstract
 *		Prepend an application-layer protocol onto the top of a protocol stack.
 *
 * @param stack
 *		The protocol stack to modify
 *
 * @param protocol
 *		The protocol options to add to the stack, which contain the definition of the
 *		protocol to add.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_protocol_stack_prepend_application_protocol(nw_protocol_stack_t stack,
											   nw_protocol_options_t protocol);

/*!
 * @function nw_protocol_stack_clear_application_protocols
 *
 * @abstract
 *		Remove all application-layer protocols from a protocol stack.
 *
 * @param stack
 *		The protocol stack to modify
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_protocol_stack_clear_application_protocols(nw_protocol_stack_t stack);

#ifdef __BLOCKS__

typedef void (^nw_protocol_stack_iterate_protocols_block_t)(nw_protocol_options_t protocol);

/*!
 * @function nw_protocol_stack_iterate_application_protocols
 *
 * @abstract
 *		List all application protocols attached to a protocol stack.
 *
 * @param stack
 *		The protocol stack to check
 *
 * @param iterate_block
 *		A block that will return the protocols attached to the stack.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_protocol_stack_iterate_application_protocols(nw_protocol_stack_t stack,
												NW_NOESCAPE nw_protocol_stack_iterate_protocols_block_t iterate_block);

#endif // __BLOCKS__

/*!
 * @function nw_protocol_stack_copy_transport_protocol
 *
 * @abstract
 *		Access the transport-layer protocol used in a protocol stack.
 *
 * @param stack
 *		The protocol stack to check
 *
 * @result
 *		Returns the transport protocol currently set in the protocol stack,
 *		or NULL if no transport protocol is set.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED _Nullable nw_protocol_options_t
nw_protocol_stack_copy_transport_protocol(nw_protocol_stack_t stack);

/*!
 * @function nw_protocol_stack_set_transport_protocol
 *
 * @abstract
 *		Set the transport-layer protocol to use for a protocol stack.
 *
 * @param stack
 *		The protocol stack to modify
 *
 * @param protocol
 *		The protocol options to set into the stack, which contain the definition of the
 *		protocol.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_protocol_stack_set_transport_protocol(nw_protocol_stack_t stack,
										 nw_protocol_options_t protocol);

/*!
 * @function nw_protocol_stack_copy_internet_protocol
 *
 * @abstract
 *		Access the internet-layer protocol used in a protocol stack.
 *
 * @param stack
 *		The protocol stack to check
 *
 * @result
 *		Returns the internet protocol currently set in the protocol stack,
 *		or NULL if no internet protocol is set. Note that this will generally
 *		be NULL, unless a specific IP family is being selected.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED _Nullable nw_protocol_options_t
nw_protocol_stack_copy_internet_protocol(nw_protocol_stack_t stack);

#pragma mark - Listener Options

/*!
 * @function nw_parameters_set_local_only
 *
 * @abstract
 *		Set to true to limit inbound connections to peers attached to the
 *		local link only. Defaults to false.
 *
 * @param parameters
 *		The parameters object to configure
 *
 * @param local_only
 *		True to limit connections to the local link only.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_parameters_set_local_only(nw_parameters_t parameters,
							 bool local_only);

/*!
 * @function nw_parameters_get_local_only
 *
 * @abstract
 *		Indicates whether or not the parameters limit connections to the local
 *		link only.
 *
 * @param parameters
 *		The parameters object to check
 *
 * @result
 *		Returns true if the parameters limit inbound connections to the local link.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
bool
nw_parameters_get_local_only(nw_parameters_t parameters);

#pragma mark - Proxy Options

/*!
 * @function nw_parameters_set_prefer_no_proxy
 *
 * @abstract
 *		Set to true to attempt connections without using proxies, only using any configured proxies if the connections
 * 		cannot otherwise be completed. Defaults to false.
 *
 * @param parameters
 *		The parameters to modify.
 *
 * @param prefer_no_proxy
 *		True to cause connections to be attempted without proxies.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_parameters_set_prefer_no_proxy(nw_parameters_t parameters, bool prefer_no_proxy);

/*!
 * @function nw_parameters_get_prefer_no_proxy
 *
 * @abstract
 *		Indicates whether or not the parameters cause connections to be attempted without proxies, only using proxies
 * 		if connections cannot otherwise be completed.
 *
 * @param parameters
 *		The parameters to get the property from.
 *
 * @result
 *		Returns true if the parameters cause connections to be attempted without proxies, only using proxies if
 *		connections cannot otherwise be completed.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
bool
nw_parameters_get_prefer_no_proxy(nw_parameters_t parameters);

#pragma mark - Resolution Options

/*!
 * @typedef nw_parameters_expired_dns_behavior_t
 * @abstract
 *		Expired DNS behavior defines whether or not a connection will allow the use
 *		of expired DNS answers during connection establishment.
 */
typedef enum {
	/*! @const nw_parameters_expired_dns_behavior_default Let the system determine whether or not to allow expired DNS answers  */
	nw_parameters_expired_dns_behavior_default = 0,
	/*! @const nw_parameters_expired_dns_behavior_allow Explicitly allow the use of expired DNS answers */
	nw_parameters_expired_dns_behavior_allow = 1,
	/*! @const nw_parameters_expired_dns_behavior_allow Explicitly prohibit the use of expired DNS answers */
	nw_parameters_expired_dns_behavior_prohibit = 2,
} nw_parameters_expired_dns_behavior_t;

/*!
 * @function nw_parameters_set_expired_dns_behavior
 *
 * @abstract
 *		Allow or prohibit the use of expired DNS answers during connection establishment.
 *		If allowed, a DNS answer that was previously returned may be re-used for new
 *		connections even after the answers are considered expired. A query for fresh answers
 *		will be sent in parallel, and the fresh answers will be used as alternate addresses
 *		in case the expired answers do not result in successful connections.
 *
 *		By default, this value is nw_parameters_expired_dns_behavior_default, which allows
 *		the system to determine if it is appropriate to use expired answers.
 *
 * @param parameters
 *		The parameters to modify.
 *
 * @param expired_dns_behavior
 *		Allow, prohibit, or use system default behavior for expired DNS answers.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_parameters_set_expired_dns_behavior(nw_parameters_t parameters,
									   nw_parameters_expired_dns_behavior_t expired_dns_behavior);


/*!
 * @function nw_parameters_get_expired_dns_behavior
 *
 * @abstract
 *		Check the effective expired DNS behavior of a connection.
 *		See nw_parameters_set_expired_dns_behavior() for a discussion on the use of expired
 *		DNS answers.
 *
 * @param parameters
 *		The parameters to check.
 *
 * @result
 *		Returns the current effective expired DNS answer behavior.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
nw_parameters_expired_dns_behavior_t
nw_parameters_get_expired_dns_behavior(nw_parameters_t parameters);

NW_ASSUME_NONNULL_END

__END_DECLS

#endif /* defined(__NW_PARAMETERS_H__) */
