//
//  advertise_descriptor.h
//  Network
//
//  Copyright (c) 2016-2018 Apple Inc. All rights reserved.
//

#ifndef __NW_ADVERTISE_DESCRIPTOR_H__
#define __NW_ADVERTISE_DESCRIPTOR_H__

#include <Network/nw_object.h>

#include <sys/types.h>
#include <stdbool.h>

NW_ASSUME_NONNULL_BEGIN
__BEGIN_DECLS

/*!
 * @typedef nw_advertise_descriptor_t
 * @abstract
 *		An Advertise Descriptor is an abstract classification of properties
 *		that may be used to advertise a service, such as a Bonjour service type.
 */
#ifndef NW_SERVICE_DESCRIPTOR_IMPL
NW_OBJECT_DECL(nw_advertise_descriptor);
#endif // NW_SERVICE_DESCRIPTOR_IMPL

/*!
 * @function nw_advertise_descriptor_create_bonjour_service
 *
 * @abstract
 *		Creates a new advertise descriptor object based on a Bonjour service type
 *		and optional domain. This object can be used with listener objects to
 *      specify the service the listener should advertise.
 *
 *      If the name is unspecified, the default name for the device will be used.
 *      If the domain is unspecified, the default domains for registration will be
 *      used. If the listener is local only, the domain 'local.' will be used
 *      regardless of the parameter passed to domain.
 *
 * @param name
 *		An optional Bonjour service name.
 *
 * @param type
 *		A Bonjour service type.
 *
 * @param domain
 *		An optional Bonjour service domain.
 *
 * @result
 *		An instantiated browse descriptor object.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
NW_RETURNS_RETAINED nw_advertise_descriptor_t _Nullable
nw_advertise_descriptor_create_bonjour_service(const char * _Nullable name, const char * type, const char * _Nullable domain);

/*!
 * @function nw_advertise_descriptor_set_txt_record
 *
 * @abstract
 *		Set the TXT record to use when initially registering the service.
 *
 * @param advertise_descriptor
 *		The advertise descriptor to modify
 *
 * @param txt_record
 *		A pointer to the TXT record.
 *
 * @param txt_length
 *		The length of the TXT record.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_advertise_descriptor_set_txt_record(nw_advertise_descriptor_t advertise_descriptor,
									   const void *txt_record,
									   size_t txt_length);

/*!
 * @function nw_advertise_descriptor_set_no_auto_rename
 *
 * @abstract
 *		Disable auto-rename for the Bonjour service registration.
 *		Auto-rename is enabled by default.
 *
 * @param advertise_descriptor
 *		The advertise descriptor to modify
 *
 * @param no_auto_rename
 *		A boolean indicating if auto-rename should be disabled.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_advertise_descriptor_set_no_auto_rename(nw_advertise_descriptor_t advertise_descriptor,
										   bool no_auto_rename);

/*!
 * @function nw_advertise_descriptor_get_no_auto_rename
 *
 * @abstract
 *		Check if auto-rename has been disabled for the Bonjour service
 *		registration.
 *
 * @param advertise_descriptor
 *		The advertise descriptor to modify
 *
 * @result A boolean indicating if auto-rename is disabled.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
bool
nw_advertise_descriptor_get_no_auto_rename(nw_advertise_descriptor_t advertise_descriptor);

__END_DECLS
NW_ASSUME_NONNULL_END

#endif /* __NW_ADVERTISE_DESCRIPTOR_H__ */
