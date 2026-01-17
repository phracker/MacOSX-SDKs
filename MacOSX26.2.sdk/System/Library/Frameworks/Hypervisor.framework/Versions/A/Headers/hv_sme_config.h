//
//  hv_sme_config.h
//  Hypervisor
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#pragma once

#ifdef __arm64__

#include <Hypervisor/hv_base.h>
#include <arm64/hv/hv_kern_types.h>

OS_ASSUME_NONNULL_BEGIN

__BEGIN_DECLS

/*!
 @abstract Returns the value of the maximum Streaming Vector Length (SVL) in bytes.
 @param value Pointer to the value.
 @result HV_SUCCESS on success, an error code otherwise.
 @discussion
    This is the maximum SVL that guests may use and separate from the effective SVL that
    guests may set using SMCR_EL1.

    Returns HV_UNSUPPORTED if SME is not supported.
 */
OS_EXPORT API_AVAILABLE(macos(15.2))
hv_return_t hv_sme_config_get_max_svl_bytes(size_t *value);

__END_DECLS

OS_ASSUME_NONNULL_END

#endif
