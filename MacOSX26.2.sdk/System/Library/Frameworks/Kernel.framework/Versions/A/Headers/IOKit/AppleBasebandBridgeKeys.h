//
//  AppleBasebandBridgeKeys.h
//  AppleBaseband
//
//  Created by Saran Krishnaswamy
//

#ifndef __AppleBaseband__AppleBasebandBridgeKeys__
#define __AppleBaseband__AppleBasebandBridgeKeys__

#include <IOKit/IOMessage.h>

#define kAppleBasebandBridgeControl "AppleBasebandBridgeControl"
#define kAppleBasebandBridge        "AppleBasebandBridgeControl" // for backward compatibility -- remove after updating ABS project

#define kAppleBasebandBridgeUserEvent_WarmReset iokit_vendor_specific_msg(0)
#define kAppleBasebandBridgeUserEvent_ColdReset iokit_vendor_specific_msg(1)

enum AppleBasebandBridgeUserRequest {
    // Maintain strict order as it is used as index to function call
    kAppleBasebandBridgeUserRequest_BridgeReady,
    kAppleBasebandBridgeUserRequest_BasebandInReset,
    kAppleBasebandBridgeUserRequest_BasebandHostWake,

    // Last entry
    kAppleBasebandBridgeUserRequest_MAX
};

#endif /* __AppleBaseband__AppleBasebandBridgeKeys__ */
