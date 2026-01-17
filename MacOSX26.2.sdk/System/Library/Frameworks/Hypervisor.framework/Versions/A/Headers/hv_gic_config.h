//
//  hv_gic_config.h
//  Hypervisor
//
//  Copyright © 2023-2024 Apple Inc. All rights reserved.
//

#pragma once

#ifdef __arm64__

#include <Hypervisor/hv_gic_types.h>
#include <Hypervisor/hv_vm_types.h>

OS_ASSUME_NONNULL_BEGIN

__BEGIN_DECLS

/*!
 @abstract Create a GIC configuration object
 @result hv_gic_config_t A new GIC configuration object. Release with os_release
    when no longer needed.
 @discussion
    Create the GIC configuration after the virtual machine has been created.
 */
OS_EXPORT API_AVAILABLE(macos(15.0))
OS_OBJECT_RETURNS_RETAINED OS_WARN_RESULT
hv_gic_config_t hv_gic_config_create(void);

/*!
 @abstract Set the GIC distributor region base address.
 @param config GIC configuration object.
 @param distributor_base_address Guest physical address for distributor.
 @result HV_SUCCESS on success, an error code otherwise.
 @discussion
    Guest physical address for distributor base aligned to byte value
    returned by hv_gic_get_distributor_base_alignment.
 */
OS_EXPORT API_AVAILABLE(macos(15.0))
hv_return_t hv_gic_config_set_distributor_base(hv_gic_config_t config, hv_ipa_t distributor_base_address);

/*!
 @abstract Set the GIC redistributor region base address.
 @param config GIC configuration object.
 @param redistributor_base_address Guest physical address for redistributor.
 @result HV_SUCCESS on success, an error code otherwise.
 @discussion
    Guest physical address for redistributor base aligned to byte value
    returned by hv_gic_get_redistributor_base_alignment. The redistributor
    region will contain redistributors for all vCPUs supported by the
    virtual machine.
 */
OS_EXPORT API_AVAILABLE(macos(15.0))
hv_return_t hv_gic_config_set_redistributor_base(hv_gic_config_t config, hv_ipa_t redistributor_base_address);

/*!
 @abstract Set the GIC MSI region base address.
 @param config GIC configuration object.
 @param msi_region_base_address Guest physical address for MSI region.
 @result HV_SUCCESS on success, an error code otherwise.
 @discussion
    Guest physical address for MSI region base aligned to byte value
    returned by hv_gic_get_msi_region_base_alignment.

    For MSI support, you also need to set the interrupt range with
    hv_gic_config_set_msi_interrupt_range().
 */
OS_EXPORT API_AVAILABLE(macos(15.0))
hv_return_t hv_gic_config_set_msi_region_base(hv_gic_config_t config, hv_ipa_t msi_region_base_address);

/*!
 @abstract Sets the range of MSIs supported.
 @param config GIC configuration object.
 @param msi_intid_base Lowest MSI interrupt number.
 @param msi_intid_count Number of MSIs.
 @result HV_SUCCESS on success, an error code otherwise.
 @discussion
    Configures the range of identifiers supported for MSIs. If it is outside of
    the range given by hv_gic_get_spi_interrupt_range() an error will be
    returned.

    For MSI support, you also need to set the region base address with
    hv_gic_config_set_msi_region_base().
 */
OS_EXPORT API_AVAILABLE(macos(15.0))
hv_return_t hv_gic_config_set_msi_interrupt_range(hv_gic_config_t config, uint32_t msi_intid_base, uint32_t msi_intid_count);

__END_DECLS

OS_ASSUME_NONNULL_END

#endif
