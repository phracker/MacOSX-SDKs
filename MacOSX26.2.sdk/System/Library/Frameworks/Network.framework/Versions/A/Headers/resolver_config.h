//
//  resolver_config.h
//  libnetwork
//
//  Copyright (c) 2020-2023 Apple Inc. All rights reserved.
//

#ifndef __NW_RESOLVER_CONFIG_H__
#define __NW_RESOLVER_CONFIG_H__

#ifndef __NW_INDIRECT__
#warning "Please include <Network/Network.h> instead of this file directly."
#endif // __NW_INDIRECT__

#include <Network/nw_object.h>
#include <Network/endpoint.h>


NW_ASSUME_NONNULL_BEGIN

__BEGIN_DECLS

/*!
 * @typedef nw_resolver_config_t
 * @abstract
 *		A Resolver Config object stores a DNS resolver configuration. These can be
 *		used to specify a custom DNS resolver configuration for encrypted DNS protocols,
 *		such as DNS-over-HTTPS and DNS-over-TLS.
 *
 *		This type supports ARC and the -[description] method. In non-ARC files, use
 *		nw_retain() and nw_release() to retain and release the object.
 */
#ifndef NW_RESOLVER_CONFIG_IMPL
NW_OBJECT_DECL(nw_resolver_config);
#endif // NW_RESOLVER_CONFIG_IMPL

/*!
 * @function nw_resolver_config_create_https
 *
 * @abstract
 *		Creates a DNS-over-HTTPS (DoH) resolver configuration. The provided
 *		URL describes the location of the DNS server, such as
 *		"https://dnsserver.example.net/dns-query". See RFC 8484.
 *
 * @param url_endpoint
 *		The URL template of the DoH server as an endpoint.
 *
 * @result
 *		Returns an allocated nw_resolver_config_t object on success.
 */
API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0))
NW_RETURNS_RETAINED nw_resolver_config_t
nw_resolver_config_create_https(nw_endpoint_t url_endpoint);

/*!
 * @function nw_resolver_config_create_tls
 *
 * @abstract
 *		Creates a DNS-over-TLS (DoT) resolver configuration. The hostname
 *		of the provided endpoint will be used to validate the TLS certificate of the server.
 *		See RFC 7858.
 *
 * @param server_endpoint
 *		A host endpoint identifying the DoT server.
 *
 * @result
 *		Returns an allocated nw_resolver_config_t object on success.
 */
API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0))
NW_RETURNS_RETAINED nw_resolver_config_t
nw_resolver_config_create_tls(nw_endpoint_t server_endpoint);

/*!
 * @function nw_resolver_config_add_name_server
 *
 * @abstract
 *		Modifies the resolver configuration by adding a DNS server address as an endpoint.
 *
 * @param config
 *		A resolver config object.
 *
 * @param server_address
 *		A server address to assign to the configuration, as an endpoint.
 */
API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0))
void
nw_resolver_config_add_server_address(nw_resolver_config_t config,
									  nw_endpoint_t server_address);

__END_DECLS

NW_ASSUME_NONNULL_END

#endif // __NW_RESOLVER_CONFIG_H__
