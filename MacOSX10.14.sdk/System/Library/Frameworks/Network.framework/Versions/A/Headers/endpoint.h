//
//  endpoint.h
//  Network
//
//  Copyright (c) 2014-2018 Apple Inc. All rights reserved.
//

#ifndef __NW_ENDPOINT_H__
#define __NW_ENDPOINT_H__

#include <Network/nw_object.h>

#include <stdint.h>
#include <sys/socket.h>

NW_ASSUME_NONNULL_BEGIN

__BEGIN_DECLS

/*!
 * @typedef nw_endpoint_t
 * @abstract
 *		A Network Endpoint is an abstract static representation of a local or remote
 *		network entity. Endpoints indicate specific instances that connections may
 *		be created between, such as Hostname + Port pairs, IP Address + Port pairs,
 *		and named Bonjour Services.
 *
 *		This type supports ARC and the -[description] method. In non-ARC files, use
 *		nw_retain() and nw_release() to retain and release the object.
 */
#ifndef NW_ENDPOINT_IMPL
NW_OBJECT_DECL(nw_endpoint);
#endif // NW_ENDPOINT_IMPL

/*!
 * @typedef nw_endpoint_type_t
 * @abstract
 *		Endpoint types represent a well-known form of endpoint. Values may be
 *		added to this enumeration, and some custom endpoint types may used
 *		values not defined in this enumeration.
 */
typedef enum {
	/*! @const nw_endpoint_type_invalid An invalid endpoint */
	nw_endpoint_type_invalid = 0,
	/*! @const nw_endpoint_type_invalid An IP Address + Port */
	nw_endpoint_type_address = 1,
	/*! @const nw_endpoint_type_invalid A Hostname + Port */
	nw_endpoint_type_host = 2,
	/*! @const nw_endpoint_type_invalid A Bonjour Service Name + Type + Domain */
	nw_endpoint_type_bonjour_service = 3,
} nw_endpoint_type_t;

/*!
 * @function nw_endpoint_get_type
 *
 * @abstract
 *		Retrieves the type of a network endpoint.
 *
 * @param endpoint
 *		The endpoint object for which to get the type.
 *
 * @result
 *		Returns the type of the network endpoint.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
nw_endpoint_type_t
nw_endpoint_get_type(nw_endpoint_t endpoint);

#pragma mark - Host Endpoints

/*!
 * @function nw_endpoint_create_host
 *
 * @abstract
 *		Creates a network endpoint with a hostname and port. The hostname
 *		may be a string-encoding of an IP address, in which case the
 *		the endpoint will be treated as an endpoint with the type
 *		nw_endpoint_type_address. Otherwise, the endpoint will have the
 *		type nw_endpoint_type_host.
 *
 * @param hostname
 *		A hostname, such as "www.example.com", or "2607:ffff::1234:abcd".
 *
 * @param port
 *		A port number as a C string, such as "443", or a service
 *		name, such as "https".
 *
 * @result
 *		Returns an allocated nw_endpoint_t object on success.
 *		Callers are responsible for deallocating using nw_release(obj) or [obj release].
 *		These objects support ARC.
 *		Returns NULL on failure. Fails due to invalid parameters.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED nw_endpoint_t
nw_endpoint_create_host(const char *hostname, const char *port);

/*!
 * @function nw_endpoint_get_hostname
 *
 * @abstract
 *		Retrieves the hostname string for a network endpoint with
 *		the type nw_endpoint_type_host.
 *
 * @param endpoint
 *		The endpoint object.
 *
 * @result
 *		Returns the hostname string for the endpoint, or NULL
 *		if the endpoint is not of type nw_endpoint_type_host.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
const char *
nw_endpoint_get_hostname(nw_endpoint_t endpoint);

/*!
 * @function nw_endpoint_copy_port_string
 *
 * @abstract
 *		Returns an allocated port string for a network endpoint with
 *		the type nw_endpoint_type_host or nw_endpoint_type_address.
 *
 * @param endpoint
 *		The endpoint object.
 *
 * @result
 *		Returns the port string for the endpoint, or NULL
 *		if the endpoint is not of type nw_endpoint_type_host or
 *		nw_endpoint_type_address. This string must be freed with free().
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
char *
nw_endpoint_copy_port_string(nw_endpoint_t endpoint);

/*!
 * @function nw_endpoint_get_port
 *
 * @abstract
 *		Retrieves the port for a network endpoint with
 *		the type nw_endpoint_type_host or nw_endpoint_type_address.
 *		The port will be returned in Host Byte Order.
 *
 * @param endpoint
 *		The endpoint object.
 *
 * @result
 *		Returns the port for the endpoint, or 0 if the endpoint is not
 *		of type nw_endpoint_type_host or nw_endpoint_type_address.
 *		The port will be returned in Host Byte Order.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
uint16_t
nw_endpoint_get_port(nw_endpoint_t endpoint);

#pragma mark - Address Endpoints

/*!
 * @function nw_endpoint_create_address
 *
 * @abstract
 *		Creates a network endpoint with a sockaddr struct. The endpoint
 *		will have the type nw_endpoint_type_address.
 *
 * @param address
 *		An address stored as a sockaddr.
 *
 * @result
 *		Returns an allocated nw_endpoint_t object on success.
 *		Callers are responsible for deallocating using nw_release(obj) or [obj release].
 *		These objects support ARC.
 *		Returns NULL on failure. Fails due to invalid parameters.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED nw_endpoint_t
nw_endpoint_create_address(const struct sockaddr *address);

/*!
 * @function nw_endpoint_copy_address_string
 *
 * @abstract
 *		Returns an allocated IP address string for a network endpoint with
 *		the type nw_endpoint_type_address.
 *
 * @param endpoint
 *		The endpoint object.
 *
 * @result
 *		Returns the IP address string for the endpoint, or NULL
 *		if the endpoint is not of type nw_endpoint_type_address.
 *		This string must be freed with free().
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
char *
nw_endpoint_copy_address_string(nw_endpoint_t endpoint);

/*!
 * @function nw_endpoint_get_address
 *
 * @abstract
 *		Retrieves the sockaddr struct for a network endpoint with
 *		the type nw_endpoint_type_address.
 *
 * @param endpoint
 *		The endpoint object.
 *
 * @result
 *		Returns the sockaddr struct for the endpoint, or NULL
 *		if the endpoint is not of type nw_endpoint_type_address.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
const struct sockaddr *
nw_endpoint_get_address(nw_endpoint_t endpoint);

#pragma mark - Bonjour Service Endpoints

/*!
 * @function nw_endpoint_create_bonjour_service
 *
 * @abstract
 *		Creates a network endpoint for a Bonjour Service name, type, and
 *		domain. The endpoint will have the type nw_endpoint_type_bonjour_service.
 *
 * @param name
 *		The Bonjour Service name, such as "example".
 *
 * @param type
 *		The Bonjour Service type, such as "_http._tcp".
 *
 * @param domain
 *		The Bonjour Service domain, such as "local".
 *
 * @result
 *		Returns an allocated nw_endpoint_t object on success.
 *		Callers are responsible for deallocating using nw_release(obj) or [obj release].
 *		These objects support ARC.
 *		Returns NULL on failure. Fails due to invalid parameters.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED nw_endpoint_t
nw_endpoint_create_bonjour_service(const char *name, const char *type, const char *domain);

/*!
 * @function nw_endpoint_get_bonjour_service_name
 *
 * @abstract
 *		Retrieves the Bonjour Service name string for a network
 *		endpoint with the type nw_endpoint_type_bonjour_service.
 *
 * @param endpoint
 *		The endpoint object.
 *
 * @result
 *		Returns the Bonjour Service name string for the endpoint, or NULL
 *		if the endpoint is not of type nw_endpoint_type_bonjour_service.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
const char *
nw_endpoint_get_bonjour_service_name(nw_endpoint_t endpoint);

/*!
 * @function nw_endpoint_get_bonjour_service_type
 *
 * @abstract
 *		Retrieves the Bonjour Service type string for a network
 *		endpoint with the type nw_endpoint_type_bonjour_service.
 *
 * @param endpoint
 *		The endpoint object.
 *
 * @result
 *		Returns the Bonjour Service type string for the endpoint, or NULL
 *		if the endpoint is not of type nw_endpoint_type_bonjour_service.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
const char *
nw_endpoint_get_bonjour_service_type(nw_endpoint_t endpoint);

/*!
 * @function nw_endpoint_get_bonjour_service_domain
 *
 * @abstract
 *		Retrieves the Bonjour Service domain string for a network
 *		endpoint with the type nw_endpoint_type_bonjour_service.
 *
 * @param endpoint
 *		The endpoint object.
 *
 * @result
 *		Returns the Bonjour Service domain string for the endpoint, or NULL
 *		if the endpoint is not of type nw_endpoint_type_bonjour_service.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
const char *
nw_endpoint_get_bonjour_service_domain(nw_endpoint_t endpoint);

__END_DECLS

NW_ASSUME_NONNULL_END

#endif // __NW_ENDPOINT_H__
