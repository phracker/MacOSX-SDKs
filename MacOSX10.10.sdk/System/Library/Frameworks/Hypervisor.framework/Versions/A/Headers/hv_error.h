/*
 *  hv_return.h
 *  Hypervisor Framework
 *
 *  Copyright (c) 2013 Apple Inc. All rights reserved.
 */

#ifndef __HYPERVISOR_HV_RETURN__
#define __HYPERVISOR_HV_RETURN__

#include <mach/error.h>

#ifdef __cplusplus
extern "C" {
#endif

#define err_sub_hypervisor err_sub(0xba5)
#define err_common_hypervisor (err_local | err_sub_hypervisor)

/*!
 * @enum       hv_return_t
 * @abstract   Hypervisor Framework return codes
 */
enum {
	HV_SUCCESS		= 0,
	HV_ERROR		= err_common_hypervisor | 0x01, /* (0xfae94001) */
	HV_BUSY			= err_common_hypervisor | 0x02, /* (0xfae94002) */
	HV_BAD_ARGUMENT	= err_common_hypervisor | 0x03, /* (0xfae94003) */
	HV_NO_RESOURCES	= err_common_hypervisor | 0x05, /* (0xfae94005) */
	HV_NO_DEVICE	= err_common_hypervisor | 0x06, /* (0xfae94006) */
	HV_UNSUPPORTED	= err_common_hypervisor | 0x0f  /* (0xfae9400f) */
};

typedef mach_error_t hv_return_t;

#ifdef __cplusplus
}
#endif

#endif /* __HYPERVISOR_HV_RETURN__ */
