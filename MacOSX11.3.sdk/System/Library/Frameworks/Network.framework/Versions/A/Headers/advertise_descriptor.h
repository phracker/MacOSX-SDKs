//
//  advertise_descriptor.h
//  Network
//
//  Copyright (c) 2016-2019 Apple Inc. All rights reserved.
//

#ifndef __NW_ADVERTISE_DESCRIPTOR_H__
#define __NW_ADVERTISE_DESCRIPTOR_H__

#ifndef __NW_INDIRECT__
#warning "Please include <Network/Network.h> instead of this file directly."
#endif // __NW_INDIRECT__

#include <Network/nw_object.h>
#include <Network/txt_record.h>

#include <sys/types.h>
#include <stdbool.h>
#include <stdint.h>

NW_ASSUME_NONNULL_BEGIN
__BEGIN_DECLS

/*!
 * @typedef nw_advertise_descriptor_t
 * @abstract
 *		An Advertise Descriptor is an abstract classification of properties
 *		that may be used to advertise a service, such as a Bonjour service type.
 */
#ifndef NW_ADVERTISE_DESCRIPTOR_IMPL
NW_OBJECT_DECL(nw_advertise_descriptor);
#endif // NW_ADVERTISE_DESCRIPTOR_IMPL

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
 *		Set the TXT record for the advertise descriptor's service. You must call
 *      nw_listener_set_advertise_descriptor to update the listener's advertising
 *      afterwards in order for these changes to take effect.
 *
 * @param advertise_descriptor
 *		The advertise descriptor to modify.
 *
 * @param txt_record
 *		A pointer to the TXT record.
 *
 * @param txt_length
 *		The length of the TXT record. The total size of a typical DNS-SD TXT record
 *		is intended to be small - 200 bytes or less. Using TXT records larger than
 *		1300 bytes is not recommended at this time.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
void
nw_advertise_descriptor_set_txt_record(nw_advertise_descriptor_t advertise_descriptor,
									   const void * _Nullable txt_record,
									   size_t txt_length);

/*!
 * @function nw_advertise_descriptor_set_no_auto_rename
 *
 * @abstract
 *		Disable auto-rename for the Bonjour service registration.
 *		Auto-rename is enabled by default.
 *
 * @param advertise_descriptor
 *		The advertise descriptor to modify.
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
 *		The advertise descriptor object.
 *
 * @result A boolean indicating if auto-rename is disabled.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
bool
nw_advertise_descriptor_get_no_auto_rename(nw_advertise_descriptor_t advertise_descriptor);

/*!
 * @function nw_advertise_descriptor_set_txt_record_object
 *
 * @abstract
 *		Set the TXT record object on the advertise descriptor.
 *
 * @param advertise_descriptor
 *		The advertise descriptor object.
 *
 * @param txt_record
 *		The TXT record object. If txt_record is NULL, the advertise_descriptor's
 *		current TXT record object will be removed.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_advertise_descriptor_set_txt_record_object(nw_advertise_descriptor_t advertise_descriptor,
											  _Nullable nw_txt_record_t txt_record);

/*!
 * @function nw_advertise_descriptor_copy_txt_record_object
 *
 * @abstract
 *		Copies the TXT record object from the advertise descriptor.
 *
 * @param advertise_descriptor
 *		The advertise descriptor object.
 *
 * @result
 *		A copy of the TXT record object, or NULL if the advertise descriptor
 *		does not have an associated TXT record.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NW_RETURNS_RETAINED _Nullable nw_txt_record_t
nw_advertise_descriptor_copy_txt_record_object(nw_advertise_descriptor_t advertise_descriptor);

__END_DECLS
NW_ASSUME_NONNULL_END

#endif /* __NW_ADVERTISE_DESCRIPTOR_H__ */
