/*
 *  hv_error.h
 *  Hypervisor Framework
 *
 *  Copyright (c) 2013 Apple Inc. All rights reserved.
 */

#ifndef __HYPERVISOR_HV_RETURN__
#define __HYPERVISOR_HV_RETURN__

#ifdef __x86_64__

#include <Hypervisor/hv_base.h>
#include <mach/error.h>

OS_ASSUME_NONNULL_BEGIN

__BEGIN_DECLS

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
	HV_DENIED		= err_common_hypervisor | 0x07, /* (0xfae94007) */
	HV_UNSUPPORTED	= err_common_hypervisor | 0x0f  /* (0xfae9400f) */
};

typedef mach_error_t hv_return_t;

__END_DECLS

OS_ASSUME_NONNULL_END

#endif /* __x86_64__ */

#endif /* __HYPERVISOR_HV_RETURN__ */
