/*
 *  hv_vcpu_config.h
 *  Hypervisor Framework
 *
 *  Copyright (c) 2018-2020 Apple Inc. All rights reserved.
 */

#pragma once

#ifdef __arm64__

#include <Hypervisor/hv_base.h>
#include <Hypervisor/hv_vcpu_types.h>

OS_ASSUME_NONNULL_BEGIN

__BEGIN_DECLS

/*!
 * @function   hv_vcpu_config_create
 * @abstract   Creates a vcpu configuration object.
 * @result     A new vcpu configuration object. This should be released with os_release
 *             when no longer used.
 */
API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios)
OS_EXPORT OS_OBJECT_RETURNS_RETAINED OS_WARN_RESULT
hv_vcpu_config_t
hv_vcpu_config_create(void);

/*!
 * @function   hv_feature_reg
 * @abstract   ARM feature register.
 */
OS_ENUM(hv_feature_reg, uint32_t,
    HV_FEATURE_REG_ID_AA64DFR0_EL1,
    HV_FEATURE_REG_ID_AA64DFR1_EL1,
    HV_FEATURE_REG_ID_AA64ISAR0_EL1,
    HV_FEATURE_REG_ID_AA64ISAR1_EL1,
    HV_FEATURE_REG_ID_AA64MMFR0_EL1,
    HV_FEATURE_REG_ID_AA64MMFR1_EL1,
    HV_FEATURE_REG_ID_AA64MMFR2_EL1,
    HV_FEATURE_REG_ID_AA64PFR0_EL1,
    HV_FEATURE_REG_ID_AA64PFR1_EL1,
    HV_FEATURE_REG_CTR_EL0,
    HV_FEATURE_REG_CLIDR_EL1,
    HV_FEATURE_REG_DCZID_EL0,
);

/*!
 * @function  hv_vcpu_config_get_feature_reg
 * @abstract  For a vcpu configuration, return the given feature register value.
 * @param     config Configuration.
 * @param     feature_reg The feature register.
 * @param     value Pointer to the feature register value.
 * @result    0 on success or error code.
 */
API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios)
OS_EXPORT
hv_return_t hv_vcpu_config_get_feature_reg(hv_vcpu_config_t config,
    hv_feature_reg_t feature_reg, uint64_t *value);

/*!
 * @function  hv_vcpu_config_get_ccs_idr_el1_sys_reg
 * @abstract  For a vcpu configuration, return the given CCSIDR_EL1 values for a given cache type
 * @param     config Configuration.
 * @param     cache_type The cache type.
 * @param     value Pointer to the CCSIDR_EL1 register values.
 * @result    0 on success or error code.
 */
API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios)
OS_EXPORT
hv_return_t hv_vcpu_config_get_ccsidr_el1_sys_reg_values(hv_vcpu_config_t config,
    hv_cache_type_t cache_type, uint64_t values[_Nonnull 8]);

__END_DECLS

OS_ASSUME_NONNULL_END

#endif
