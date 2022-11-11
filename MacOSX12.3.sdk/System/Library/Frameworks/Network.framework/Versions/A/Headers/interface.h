//
//  interface.h
//  Network
//
//  Copyright (c) 2017-2019 Apple Inc. All rights reserved.
//
#ifndef __NW_INTERFACE_H__
#define __NW_INTERFACE_H__

#ifndef __NW_INDIRECT__
#warning "Please include <Network/Network.h> instead of this file directly."
#endif // __NW_INDIRECT__

#include <Network/nw_object.h>

#include <stdbool.h>
#include <stdint.h>


__BEGIN_DECLS

NW_ASSUME_NONNULL_BEGIN

/*!
 * @typedef nw_interface_t
 * @abstract
 *		A Network Interface is an object that represents a static snapshot of an interface
 *		that provides network connectivity, such as a Wi-Fi link, an Ethernet connection,
 *		a Cellular service, a VPN, or the loopback interface.
 *
 *		This type supports ARC and the -[description] method. In non-ARC files, use
 *		nw_retain() and nw_release() to retain and release the object.
 */
#ifndef NW_INTERFACE_IMPL
NW_OBJECT_DECL(nw_interface);
#endif // NW_INTERFACE_IMPL

/*!
 * @typedef nw_interface_type_t
 * @abstract
 *		Interface types represent the underlying media for a network link, such as Wi-Fi or
 *		Cellular.
 */
typedef enum {
	/*! @const nw_interface_type_other A virtual or otherwise unknown interface type */
	nw_interface_type_other = 0,
	/*! @const nw_interface_type_wifi A Wi-Fi link */
	nw_interface_type_wifi = 1,
	/*! @const nw_interface_type_wifi A Cellular link */
	nw_interface_type_cellular = 2,
	/*! @const nw_interface_type_wired A Wired Ethernet link */
	nw_interface_type_wired = 3,
	/*! @const nw_interface_type_loopback The loopback interface */
	nw_interface_type_loopback = 4,
} nw_interface_type_t;

/*!
 * @function nw_interface_get_type
 *
 * @abstract
 *		Retrieves the type of an interface. This only accesses the type of the specific
 *		interface being queried, and will not take into account types used by interfaces
 *		that traffic will eventually be routed through. That is, if the interface is a virtual
 *		interface (such as a VPN) that eventually forwards traffic through Wi-Fi, the type
 *		will be nw_interface_type_other, not nw_interface_type_wifi.
 *
 * @param interface
 *		The interface object to check.
 *
 * @result
 *		Returns the type of the interface.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
nw_interface_type_t
nw_interface_get_type(nw_interface_t interface);

/*!
 * @typedef nw_interface_radio_type_t
 * @abstract
 *		Interface radio types represent the radio technology for a network link.
 */
typedef enum {
	nw_interface_radio_type_unknown = 0,
	nw_interface_radio_type_wifi_b = 1,
	nw_interface_radio_type_wifi_a = 2,
	nw_interface_radio_type_wifi_g = 3,
	nw_interface_radio_type_wifi_n = 4,
	nw_interface_radio_type_wifi_ac = 5,
	nw_interface_radio_type_wifi_ax = 6,

	// 4G LTE
	nw_interface_radio_type_cell_lte = 0x80,
	// 5G Dual LTE & New Radio Sub6
	nw_interface_radio_type_cell_endc_sub6 = 0x81,
	// 5G Dual LTE & New Radio mmWave
	nw_interface_radio_type_cell_endc_mmw = 0x82,
	// 5G Stand Alone New Radio Sub6
	nw_interface_radio_type_cell_nr_sa_sub6 = 0x83,
	// 5G Stand Alone New Radio mmWave
	nw_interface_radio_type_cell_nr_sa_mmw = 0x84,
	// 3G WCDMA
	nw_interface_radio_type_cell_wcdma = 0x85,
	// 2G GSM
	nw_interface_radio_type_cell_gsm = 0x86,
	// 1x data
	nw_interface_radio_type_cell_cdma = 0x87,
	// HDR data
	nw_interface_radio_type_cell_evdo = 0x88,
} nw_interface_radio_type_t;

/*!
 * @function nw_interface_get_name
 *
 * @abstract
 *		Retrieves the name of an interface, to be used for reference or logging
 *		purposes.
 *
 * @param interface
 *		The interface object to check.
 *
 * @result
 *		Returns the name of the interface as a NULL-terminated C string,
 *		or NULL if the interface is NULL.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
const char *
nw_interface_get_name(nw_interface_t interface);

/*!
 * @function nw_interface_get_index
 *
 * @abstract
 *		Retrieves the index of an interface, to be used for reference or logging
 *		purposes. This is the same value as provided by if_nametoindex.
 *
 * @param interface
 *		The interface object to check.
 *
 * @result
 *		Returns the index of the interface, or 0 if the interface is NULL.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
uint32_t
nw_interface_get_index(nw_interface_t interface);

NW_ASSUME_NONNULL_END

__END_DECLS

#endif /* __NW_INTERFACE_H__ */
