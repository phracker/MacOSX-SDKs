//
//  browse_descriptor.h
//  Network
//
//  Copyright (c) 2016-2019,2022 Apple Inc. All rights reserved.
//

#ifndef __NW_BROWSE_DESCRIPTOR_H__
#define __NW_BROWSE_DESCRIPTOR_H__

#ifndef __NW_INDIRECT__
#warning "Please include <Network/Network.h> instead of this file directly."
#endif // __NW_INDIRECT__

#include <Network/nw_object.h>
#include <dispatch/dispatch.h>

NW_ASSUME_NONNULL_BEGIN

__BEGIN_DECLS

/*!
 * @typedef nw_browse_descriptor_t
 * @abstract
 *		A Browse Descriptor describes the service for which to browse. Examples
 *		include Bonjour service types, or devices owned by the same account.
 *
 *		This type supports ARC and the -[description] method. In non-ARC files, use
 *		nw_retain() and nw_release() to retain and release the object.
 */
#ifndef NW_BROWSE_DESCRIPTOR_IMPL
NW_OBJECT_DECL(nw_browse_descriptor);
#endif // NW_BROWSE_DESCRIPTOR_IMPL

/*!
 * @function nw_browse_descriptor_create_bonjour_service
 *
 * @abstract
 *		Creates a new browse descriptor object on a Bonjour service type and
 *		domain.
 *
 * @param type
 *		A Bonjour service type.
 *
 * @param domain
 *		An optional Bonjour service domain. If the domain is unspecified, the
 *		default domains for browsing will be used.
 *
 * @result
 *		An instantiated browse descriptor object.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NW_RETURNS_RETAINED nw_browse_descriptor_t
nw_browse_descriptor_create_bonjour_service(const char *type,
											const char * _Nullable domain);

/*!
 * @function nw_browse_descriptor_get_bonjour_service_type
 *
 * @abstract
 *		Returns the service type of a browse descriptor.
 *
 * @param descriptor
 *		A browse descriptor object.
 *
 * @result
 *		The service type.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
const char *
nw_browse_descriptor_get_bonjour_service_type(nw_browse_descriptor_t descriptor);

/*!
 * @function nw_browse_descriptor_get_bonjour_service_domain
 *
 * @abstract
 *		Returns the service domain of a browse descriptor, or NULL if NULL was
 *		provided while creating the descriptor.
 *
 * @param descriptor
 *		A browse descriptor object.
 *
 * @result
 *		The service domain.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
const char * _Nullable
nw_browse_descriptor_get_bonjour_service_domain(nw_browse_descriptor_t descriptor);

/*!
 * @function nw_browse_descriptor_set_include_txt_record
 *
 * @abstract
 *		Set a flag to allow or prohibit the browser from querying for TXT records
 *		while browsing. This flag should only be set if the client needs information
 *		from the TXT record during browsing, and may increase network traffic. By
 *		default, the browser will not automatically query for TXT records.
 *
 * @param descriptor
 *		The browse descriptor object.
 *
 * @param include_txt_record
 *		A flag indicating whether results should include a TXT record. If true,
 *		the browser will query for TXT records. If false, the browser will not
 *		query for TXT records.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_browse_descriptor_set_include_txt_record(nw_browse_descriptor_t descriptor, bool include_txt_record);

/*!
 * @function nw_browse_descriptor_get_include_txt_record
 *
 * @abstract
 *		Check whether the browser is allowed to query for TXT records.
 *
 * @param descriptor
 *		The browse descriptor to check.
 *
 * @result
 *		Whether the browser is allowed to query for TXT records.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
bool
nw_browse_descriptor_get_include_txt_record(nw_browse_descriptor_t descriptor);

/*!
 * @function nw_browse_descriptor_create_application_service
 *
 * @abstract
 *		Creates a browse descriptor for application service discovery.
 *
 * @param application_service_name
 *		The service name to browse for.
 *
 * @result
 *		An instantiated browse descriptor object.
 */
API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0))
NW_RETURNS_RETAINED nw_browse_descriptor_t
nw_browse_descriptor_create_application_service(const char *application_service_name);

/*!
 * @function nw_browse_descriptor_get_application_service_name
 *
 * @abstract
 *		Returns the service name of an application service browse descriptor.
 *
 * @param descriptor
 *		A browse descriptor object.
 *
 * @result
 *		The service name.
 */
API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0), tvos(16.0))
const char * _Nullable
nw_browse_descriptor_get_application_service_name(nw_browse_descriptor_t descriptor);

__END_DECLS

NW_ASSUME_NONNULL_END

#endif // __NW_BROWSE_DESCRIPTOR_H__
