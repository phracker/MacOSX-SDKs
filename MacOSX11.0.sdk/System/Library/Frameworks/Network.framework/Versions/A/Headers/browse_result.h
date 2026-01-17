//
//  browse_result.h
//  Network
//
//  Copyright (c) 2018-2019 Apple Inc. All rights reserved.
//

#ifndef __NW_BROWSE_RESULT_H__
#define __NW_BROWSE_RESULT_H__

#ifndef __NW_INDIRECT__
#warning "Please include <Network/Network.h> instead of this file directly."
#endif // __NW_INDIRECT__

#include <Network/nw_object.h>
#include <Network/endpoint.h>
#include <Network/interface.h>

NW_ASSUME_NONNULL_BEGIN

__BEGIN_DECLS

/*!
 * @typedef nw_browse_result_t
 * @abstract
 *		A Browse Result represents the outcome of a browse operation. It contains
 *		an endpoint and additional information about the endpoint gathered during
 *		browsing.
 *
 *		For example, a Bonjour service may be advertised on multiple interfaces.
 *		The browser will provide a single browse result object for each collection
 *		of Bonjour endpoints sharing the same service instance name. The browse
 *		result will have an enumerable array of interfaces and the endpoints'
 *		common TXT record value.
 *
 *		Browse results may also be compared using nw_browse_result_get_changes()
 *		which describes the changes that occurred between an old and new browse
 *		result.
 *
 *		This type supports ARC and the -[description] method. In non-ARC files, use
 *		nw_retain() and nw_release() to retain and release the object.
 */
#ifndef NW_BROWSE_RESULT_IMPL
NW_OBJECT_DECL(nw_browse_result);
#endif // NW_BROWSE_RESULT_IMPL

/*!
 * @typedef nw_browse_result_change_t
 * @abstract
 *		A nw_browse_result_change_t describes all changes that occurred between
 *		two browse results. Call nw_browse_result_get_changes() to get the
 *		changes between an old and a new browse result.
 */
typedef uint64_t nw_browse_result_change_t;

enum {
	/*!
	 *	@const nw_browse_result_change_invalid The browse result change is invalid.
	 */
	nw_browse_result_change_invalid = 0x00,

	/*!
	 *	@const nw_browse_result_change_identical The browse results being compared
	 *		are identical.
	 */
	nw_browse_result_change_identical = 0x01,

	/*!
	 *	@const nw_browse_result_change_result_added A browse result was added.
	 */
	nw_browse_result_change_result_added = 0x02,

	/*!
	 *	@const nw_browse_result_change_result_removed A browse result was removed.
	 */
	nw_browse_result_change_result_removed = 0x04,

	/*!
	 *	@const nw_browse_result_change_interface_added An interface became available.
	 */
	nw_browse_result_change_interface_added = 0x08,

	/*!
	 *	@const nw_browse_result_change_interface_removed An interface was removed.
	 */
	nw_browse_result_change_interface_removed = 0x10,

	/*!
	 *	@const nw_browse_result_change_txt_record_changed The TXT record changed.
	 */
	nw_browse_result_change_txt_record_changed = 0x20,
};

/*!
 * @function nw_browse_result_copy_endpoint
 *
 * @abstract
 *		Copies the endpoint associated with the browse result object.
 *
 * @param result
 *		The browse result object.
 *
 * @result
 *		The associated endpoint.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NW_RETURNS_RETAINED nw_endpoint_t
nw_browse_result_copy_endpoint(nw_browse_result_t result);

/*!
 * @function nw_browse_result_get_changes
 *
 * @abstract
 *		Determines the set of all changes that occurred between an old and a new
 *		browse result. For example, if the return value of this function matches
 *		with nw_browse_result_change_interface_added and nw_browse_result_change_txt_record_changed,
 *		the caller can expect new_result to include a new interface and an updated
 *		txt record that was not present in old_result.
 *
 * @param old_result
 *		The old result.
 *
 * @param new_result
 *		The new result.
 *
 * @result
 *		A nw_browse_result_change_t describing all changes that occurred.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
nw_browse_result_change_t
nw_browse_result_get_changes(_Nullable nw_browse_result_t old_result,
							 _Nullable nw_browse_result_t new_result);

/*!
 * @function nw_browse_result_get_interfaces_count
 *
 * @abstract
 *		Returns the number of interfaces on this browse result.
 *
 * @param result
 *		The browse result object.
 *
 * @result
 *		The number of interfaces available.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
size_t
nw_browse_result_get_interfaces_count(nw_browse_result_t result);

/*!
 * @function nw_browse_result_copy_txt_record_object
 *
 * @abstract
 *		Copies the TXT record object from the browse result.
 *
 * @param result
 *		The browse result object.
 *
 * @result
 *		A copy of the TXT record object, or NULL if the browse result does not
 *		have an associated TXT record.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NW_RETURNS_RETAINED _Nullable nw_txt_record_t
nw_browse_result_copy_txt_record_object(nw_browse_result_t result);

#ifdef __BLOCKS__

/*!
 * @typedef nw_browse_result_enumerate_interface_t
 *
 * @abstract
 *		A block that can be applied to every interface in the browse result.
 *
 * @param interface
 *		The interface object.
 *
 * @result
 *		A boolean value that indicating if enumeration should continue.
 */
typedef bool (^nw_browse_result_enumerate_interface_t)(nw_interface_t interface);

/*!
 * @function nw_browse_result_enumerate_interfaces
 *
 * @abstract
 *		Enumerates the list of interfaces on this browse result.
 *
 * @param result
 *		The browse result object.
 *
 * @param enumerator
 *		The enumerator block.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
void
nw_browse_result_enumerate_interfaces(nw_browse_result_t result,
									  NW_NOESCAPE nw_browse_result_enumerate_interface_t enumerator);

#endif // __BLOCKS__


__END_DECLS

NW_ASSUME_NONNULL_END

#endif // __NW_BROWSE_RESULT_H__
