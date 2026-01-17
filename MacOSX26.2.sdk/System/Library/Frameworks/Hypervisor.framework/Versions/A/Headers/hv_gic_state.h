//
//  hv_gic_state.h
//  Hypervisor
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#pragma once

#ifdef __arm64__

#include <Hypervisor/hv_gic_types.h>

OS_ASSUME_NONNULL_BEGIN

__BEGIN_DECLS

/*!
 @abstract Create a GIC state object.
 @result hv_gic_state_t A new GIC state object that is representative of the current GIC state.
    This should be released with os_release when no longer used.
 @discussion
    The function returns no object if the current GIC state can not be represented in a GIC
    state object, or if there is no GIC present in the virtual machine.

    The virtual machine must be in a stopped state prior to calling this function.
 */
OS_EXPORT API_AVAILABLE(macos(15.0))
OS_OBJECT_RETURNS_RETAINED OS_WARN_RESULT
hv_gic_state_t hv_gic_state_create(void);

/*!
 @abstract Get size of buffer required for GIC state.
 @param state GIC state object.
 @param gic_state_size Pointer to GIC data size (written on success).
 @result HV_SUCCESS on success, an error code otherwise.
 */
OS_EXPORT API_AVAILABLE(macos(15.0))
hv_return_t hv_gic_state_get_size(hv_gic_state_t state, size_t *gic_state_size);

/*!
 @abstract Get the state data for GIC.
 @param state GIC state object.
 @param gic_state_data Pointer to GIC state buffer (written on success).
 @result HV_SUCCESS on success, an error code otherwise.
 @discussion
    The function returns an opaque data buffer that contains the complete
    serialized state of the device, except for the GIC cpu registers. The data
    can be written to a file and is stable. It is also versioned for detecting
    incompatibilities on restore of the state. The size of this GIC state buffer
    must be at least as large as the size returned by hv_gic_state_get_size().

    GIC CPU system registers can be read separately, and saved to restore the
    cpu state for the virtual machine.
 */
OS_EXPORT API_AVAILABLE(macos(15.0))
hv_return_t hv_gic_state_get_data(hv_gic_state_t state, void *gic_state_data);

__END_DECLS

OS_ASSUME_NONNULL_END

#endif
