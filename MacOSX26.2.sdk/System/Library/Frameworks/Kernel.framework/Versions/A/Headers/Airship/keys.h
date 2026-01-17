//
//  keys.hpp
//  Airship
//
//  Created by Jason McElrath on 5/21/23.
//

#if !defined(airship_api_indirect) && !defined(__clang_tapi__)
#error Please #include <Airship/Airship.h> instead of this file directly.
#endif

#ifndef airship__core__api__keys_h
#define airship__core__api__keys_h

/**
 * @file keys.h
 * @brief Public keys definitions.
 */

#include <Airship/base.h>

/*
 * These are #define'd string literals rather than `extern const char *` so that
 * they are usable with `CFSTR`.
 * We can consider adding public preallocated `CFStringRef` or
 * `const OSSymbol *` symbols if rdar://111458607 (ER: add a way to initialize
 * public OSSymbols at dext load) is ever resolved.
 */

#define kAirshipDriverConfigNameKey "AirshipDriverConfigName"
#define kAirshipDeviceCriteriaKey "AirshipDeviceCriteria"
#define kAirshipAutoExitResetKey "AirshipAutoExitReset"
#define kAirshipDriverNameKey "AirshipDriverName"
#define kAirshipDeviceClassKey "AirshipDeviceClass"
#define kAirshipBuiltInKey "AirshipBuiltIn"

#define kAirshipDeviceMatchKey "AirshipDeviceMatch"
#define kAirshipMatchAncestorRegistryID "AncestorRegistryID"
#define kAirshipMatchBuiltIn "BuiltIn"
#define kAirshipMatchVendor kAirshipVendor
#define kAirshipMatchChipset kAirshipChipset
#define kAirshipMatchRole kAirshipRole

#define kAirshipProtocol "Protocol"
#define kAirshipVendor "Vendor"
#define kAirshipChipset "Chipset"
#define kAirshipRole "Role"

#define kAirshipProtocolAcipc "acipc"

#define kAirshipDeviceAttachTimeout "AirshipDeviceAttachTimeoutMS"


#define kAirshipProtocolDaleipc "daleipc"
#define kAirshipVendorDale "Dale"
#define kAirshipChipsetDal25 "dal25"

typedef enum airship_driver_error
{
    kAirshipDriverErrorIpcErrorOccurred = (1 << 0),
    kAirshipDriverErrorIpcSetTransportFailed = (1 << 1),
    kAirshipDriverErrorIpcPowerOffTimedOut = (1 << 2),
    kAirshipDriverErrorIpcPowerOnTimedOut = (1 << 3),
    kAirshipDriverErrorDevicePowerOffTimedOut = (1 << 4),
    kAirshipDriverErrorDevicePowerOnTimedOut = (1 << 5),
} airship_driver_error_t;

typedef enum airship_driver_user_client_type
{
    kAirshipDriverUserClientTypeDaleTraceInterface = 4,
} airship_driver_user_client_type_t;


#endif /* airship__core__api__keys_h */
