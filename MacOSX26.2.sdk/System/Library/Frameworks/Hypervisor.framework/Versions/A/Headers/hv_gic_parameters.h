//
//  hv_gic_parameters.h
//  Hypervisor
//
//  Copyright © 2023-2024 Apple Inc. All rights reserved.
//

#pragma once

#ifdef __arm64__

#include <Hypervisor/hv_base.h>
#include <Hypervisor/hv_gic_types.h>
#include <arm64/hv/hv_kern_types.h>

OS_ASSUME_NONNULL_BEGIN

__BEGIN_DECLS

/*!
 @abstract Gets the size in bytes of the GIC distributor region.
 @param distributor_size Pointer to GIC distributor region size (written on success).
 @result HV_SUCCESS on success, an error code otherwise.
 */
OS_EXPORT API_AVAILABLE(macos(15.0))
hv_return_t hv_gic_get_distributor_size(size_t *distributor_size);

/*!
 @abstract Gets the alignment in bytes for the base address of the GIC distributor region.
 @param distributor_base_alignment Pointer to GIC distributor base address alignment (written on success).
 @result HV_SUCCESS on success, an error code otherwise.
 */
OS_EXPORT API_AVAILABLE(macos(15.0))
hv_return_t hv_gic_get_distributor_base_alignment(size_t *distributor_base_alignment);

/*!
 @abstract Gets the total size in bytes of the GIC redistributor region.
 @param redistributor_region_size Pointer to GIC redistributor region size (written on success).
 @result HV_SUCCESS on success, an error code otherwise.
 @discussion
    Provides the total size of the GIC redistributor regions supported. Each
    redistributor is two 64 kilobyte frames per vCPU and is contiguously
    placed.
 */
OS_EXPORT API_AVAILABLE(macos(15.0))
hv_return_t hv_gic_get_redistributor_region_size(size_t *redistributor_region_size);

/*!
 @abstract Gets the size in bytes of a single GIC redistributor.
 @param redistributor_size Pointer to GIC redistributor region size (written on success).
 @result HV_SUCCESS on success, an error code otherwise.
 */
OS_EXPORT API_AVAILABLE(macos(15.0))
hv_return_t hv_gic_get_redistributor_size(size_t *redistributor_size);

/*!
 @abstract Gets the alignment in bytes for the base address of the GIC redistributor region.
 @param redistributor_base_alignment Pointer to GIC redistributor base address alignment (written on success).
 @result HV_SUCCESS on success, an error code otherwise.
 */
OS_EXPORT API_AVAILABLE(macos(15.0))
hv_return_t hv_gic_get_redistributor_base_alignment(size_t *redistributor_base_alignment);

/*!
 @abstract Gets the size in bytes of the GIC MSI region.
 @param msi_region_size Pointer to GIC MSI region size (written on success).
 @result HV_SUCCESS on success, an error code otherwise.
 */
OS_EXPORT API_AVAILABLE(macos(15.0))
hv_return_t hv_gic_get_msi_region_size(size_t *msi_region_size);

/*!
 @abstract Gets the alignment in bytes for the base address of the GIC MSI region.
 @param msi_region_base_alignment Pointer to GIC MSI region base address alignment (written on success).
 @result HV_SUCCESS on success, an error code otherwise.
 */
OS_EXPORT API_AVAILABLE(macos(15.0))
hv_return_t hv_gic_get_msi_region_base_alignment(size_t *msi_region_base_alignment);

/*!
 @abstract Gets the range of SPIs supported.
 @param spi_intid_base Pointer to the lowest SPI number (written on success).
 @param spi_intid_count Pointer to the number of SPIs supported (written on success).
 @result HV_SUCCESS on success, an error code otherwise.
 */
OS_EXPORT API_AVAILABLE(macos(15.0))
hv_return_t hv_gic_get_spi_interrupt_range(uint32_t *spi_intid_base, uint32_t *spi_intid_count);

/*!
 @abstract Gets the interrupt id for reserved interrupts.
 @param interrupt Enum value for reserved interrupts.
 @param intid Pointer to the interrupt number (written on success).
 @result HV_SUCCESS on success, an error code otherwise.
 @discussion
    Provides the interrupt id for interrupts that are reserved by the
    hypervisor framework.
 */
OS_EXPORT API_AVAILABLE(macos(15.0))
hv_return_t hv_gic_get_intid(hv_gic_intid_t interrupt, uint32_t *intid);

__END_DECLS

OS_ASSUME_NONNULL_END

#endif
