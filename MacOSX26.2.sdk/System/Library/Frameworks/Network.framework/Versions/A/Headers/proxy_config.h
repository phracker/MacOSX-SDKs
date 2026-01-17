//
//  proxy_config.h
//  libnetwork
//
//  Copyright (c) 2023 Apple Inc. All rights reserved.
//

#ifndef __NW_PROXY_CONFIG_H__
#define __NW_PROXY_CONFIG_H__

#ifndef __NW_INDIRECT__
#warning "Please include <Network/Network.h> instead of this file directly."
#endif // __NW_INDIRECT__

#include <Network/nw_object.h>
#include <Network/endpoint.h>
#include <Network/protocol_options.h>


NW_ASSUME_NONNULL_BEGIN

__BEGIN_DECLS

/*!
 * @typedef nw_proxy_config_t
 * @abstract
 *		A Proxy Config object stores a proxy configuration. These can be used to specify custom
 *		proxies, such as ones that use HTTP CONNECT.
 *
 *		This type supports ARC and the -[description] method. In non-ARC files, use
 *		nw_retain() and nw_release() to retain and release the object.
 */
#ifndef NW_PROXY_CONFIG_IMPL
NW_OBJECT_DECL(nw_proxy_config);
#endif // NW_PROXY_CONFIG_IMPL

#pragma mark - Secure Relays

/*!
 * @typedef nw_relay_hop_t
 * @abstract
 *		A Relay Hop object represents a single hop in a multi-hop relay configuration.
 *
 *		This type supports ARC and the -[description] method. In non-ARC files, use
 *		nw_retain() and nw_release() to retain and release the object.
 */
#ifndef NW_RELAY_HOP_IMPL
NW_OBJECT_DECL(nw_relay_hop);
#endif // NW_RELAY_HOP_IMPL

/*!
 * @function nw_relay_hop_create
 *
 * @abstract
 *		Creates a configuration for a secure relay. A relay is a proxy that is accessible using
 *		HTTP/3, HTTP/2, or both, and uses the CONNECT method to proxy TCP or UDP
 *		connections. At least one of `http3_relay_endpoint` and
 *		`http2_relay_endpoint` must be non-null.
 *
 * @param http3_relay_endpoint
 *		A URL or host endpoint identifying the relay server accessible using HTTP/3.
 *
 * @param http2_relay_endpoint
 *		A URL or host endpoint identifying the relay server accessible using HTTP/2.
 *
 * @param relay_tls_options
 *		Optional TLS options to use for the TLS handshake to the relay. If this is null, default
 *		TLS options will be used.
 *
 * @result
 *		Returns an allocated `nw_relay_hop_t` object on success.
 */
API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0))
NW_RETURNS_RETAINED nw_relay_hop_t
nw_relay_hop_create(nw_endpoint_t _Nullable http3_relay_endpoint,
					nw_endpoint_t _Nullable http2_relay_endpoint,
					nw_protocol_options_t _Nullable relay_tls_options);

/*!
 * @function nw_relay_hop_add_additional_http_header_field
 *
 * @abstract
 *		Adds additional HTTP headers to send as part of CONNECT requests to the
 *		relay.
 *
 * @param relay_hop
 *		The proxy hop object.
 *
 * @param field_name
 *		The HTTP header field name.
 *
 * @param field_value
 *		The HTTP header field value.
 */
API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0))
void
nw_relay_hop_add_additional_http_header_field(nw_relay_hop_t relay_hop,
											  const char *field_name,
											  const char *field_value);

/*!
 * @function nw_proxy_config_create_relay
 *
 * @abstract
 *		Creates a proxy configuration with one or two secure relay hops.
 *
 * @param first_hop
 *		The first or only relay hop.
 *
 * @param second_hop
 *		An optional second relay hop.
 *
 * @result
 *		Returns an allocated `nw_proxy_config_t` object on success.
 */
API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0))
NW_RETURNS_RETAINED nw_proxy_config_t
nw_proxy_config_create_relay(nw_relay_hop_t first_hop,
							 nw_relay_hop_t _Nullable second_hop);

#pragma mark - Oblivious HTTP

/*!
 * @function nw_proxy_config_create_oblivious_http
 *
 * @abstract
 *		Creates a proxy configuration for an Oblivious HTTP relay and gateway. Note that
 *		Oblivious HTTP proxy configurations must also have specific match domains specified
 *		using `nw_proxy_config_add_match_domain`.
 *
 * @param relay
 *		The Oblivious HTTP relay hop.
 *
 * @param relay_resource_path
 *		The HTTP path to use for requests to the Oblivious HTTP relay that will forward requests to the gateway.
 *
 * @param gateway_key_config
 *		The key configuration for the Oblivious HTTP gateway, or a list of key configurations where each configuration
 *		is prefixed with a two-byte length in network byte order.
 *
 * @param gateway_key_config_length
 *		The length of the buffer in `gateway_key_config`.
 *
 * @result
 *		Returns an allocated `nw_proxy_config_t` object on success.
 */
API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0))
NW_RETURNS_RETAINED nw_proxy_config_t
nw_proxy_config_create_oblivious_http(nw_relay_hop_t relay,
									  const char *relay_resource_path,
									  const uint8_t *gateway_key_config,
									  size_t gateway_key_config_length);

#pragma mark - HTTP CONNECT Proxies

/*!
 * @function nw_proxy_config_create_http_connect
 *
 * @abstract
 *		Creates a legacy HTTP CONNECT proxy configuration for a proxy server accessible
 *		using HTTP/1.1. This proxy will only relay TCP connections.
 *
 * @param proxy_endpoint
 *		A host endpoint identifying the proxy server accessible using HTTP/1.1.
 *
 * @param proxy_tls_options
 *		Optional TLS options to use for a TLS handshake to the relay. If no options are provided,
 *		the proxy will be accessed using cleartext HTTP.
 *
 * @result
 *		Returns an allocated `nw_proxy_config_t` object on success.
 */
API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0))
NW_RETURNS_RETAINED nw_proxy_config_t
nw_proxy_config_create_http_connect(nw_endpoint_t proxy_endpoint,
									nw_protocol_options_t _Nullable proxy_tls_options);

#pragma mark - SOCKS Proxies

/*!
 * @function nw_proxy_config_create_socksv5
 *
 * @abstract
 *		Creates a SOCKSv5 proxy configuration.
 *
 * @param proxy_endpoint
 *		A host endpoint identifying the SOCKS proxy server.
 *
 * @result
 *		Returns an allocated `nw_proxy_config_t` object on success.
 */
API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0))
NW_RETURNS_RETAINED nw_proxy_config_t
nw_proxy_config_create_socksv5(nw_endpoint_t proxy_endpoint);

#pragma mark - Generic Proxy Options

/*!
 * @function nw_proxy_config_set_username_and_password
 *
 * @abstract
 *		Configures a username and password to use with a proxy configuration.
 *
 * @param proxy_config
 *		The proxy configuration object.
 *
 * @param username
 *		A proxy authentication username.
 *
 * @param password
 *		A proxy authentication password.
 */
API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0))
void
nw_proxy_config_set_username_and_password(nw_proxy_config_t proxy_config,
										  const char *username,
										  const char * _Nullable password);

/*!
 * @function nw_proxy_config_set_failover_allowed
 *
 * @abstract
 *		Set whether or not a proxy configuration allows failover to non-proxied connections.
 *		Failover is not allowed by default.
 *
 * @param proxy_config
 *		The proxy configuration object.
 *
 * @param failover_allowed
 *		A Boolean indicating if failover is allowed.
 */
API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0))
void
nw_proxy_config_set_failover_allowed(nw_proxy_config_t proxy_config,
									 bool failover_allowed);

/*!
 * @function nw_proxy_config_get_failover_allowed
 *
 * @abstract
 *		Check whether or not a proxy configuration allows failover to non-proxied connections.
 *
 * @param proxy_config
 *		The proxy configuration object.
 *
 * @result
 *		A Boolean indicating if failover is allowed.
 */
API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0))
bool
nw_proxy_config_get_failover_allowed(nw_proxy_config_t proxy_config);

/*!
 * @function nw_proxy_config_add_match_domain
 *
 * @abstract
 *		Adds a domain to define which hosts should use the proxy.
 *
 * @param config
 *		The proxy configuration object.
 *
 * @param match_domain
 *		The domain suffix to match hostnames against, as a string.
 */
API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0))
void
nw_proxy_config_add_match_domain(nw_proxy_config_t config,
								 const char *match_domain);

/*!
 * @function nw_proxy_config_clear_match_domains
 *
 * @abstract
 *		Clears all match domains defined for the proxy.
 *
 * @param config
 *		The proxy configuration object.
 */
API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0))
void
nw_proxy_config_clear_match_domains(nw_proxy_config_t config);

/*!
 * @function nw_proxy_config_add_excluded_domain
 *
 * @abstract
 *		Adds a domain to define which hosts should not use the proxy.
 *
 * @param config
 *		The proxy configuration object.
 *
 * @param excluded_domain
 *		The domain suffix to match hostnames against, as a string.
 */
API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0))
void
nw_proxy_config_add_excluded_domain(nw_proxy_config_t config,
									const char *excluded_domain);

/*!
 * @function nw_proxy_config_clear_excluded_domains
 *
 * @abstract
 *		Clears all excluded domains defined for the proxy.
 *
 * @param config
 *		The proxy configuration object.
 */
API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0))
void
nw_proxy_config_clear_excluded_domains(nw_proxy_config_t config);

#ifdef __BLOCKS__

typedef void (^nw_proxy_domain_enumerator_t)(const char *);

/*!
 * @function nw_proxy_config_enumerate_match_domains
 *
 * @abstract
 *		Enumerate all match domains set on the proxy configuration.
 *
 * @param config
 *		The proxy configuration object.
 *
 * @param enumerator
 *		A block that will get invoked for every domain that was added to the proxy configuration.
 */
API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0))
void
nw_proxy_config_enumerate_match_domains(nw_proxy_config_t config,
										NW_NOESCAPE nw_proxy_domain_enumerator_t enumerator);

/*!
 * @function nw_proxy_config_enumerate_excluded_domains
 *
 * @abstract
 *		Enumerate all excluded domains set on the proxy configuration.
 *
 * @param config
 *		The proxy configuration object.
 *
 * @param enumerator
 *		A block that will get invoked for every domain that was added to the proxy configuration.
 */
API_AVAILABLE(macos(14.0), ios(17.0), watchos(10.0), tvos(17.0))
void
nw_proxy_config_enumerate_excluded_domains(nw_proxy_config_t config,
										   NW_NOESCAPE nw_proxy_domain_enumerator_t enumerator);

#endif // __BLOCKS__

__END_DECLS

NW_ASSUME_NONNULL_END

#endif // __NW_PROXY_CONFIG_H__
