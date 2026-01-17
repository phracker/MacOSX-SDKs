/*
	Copyright (C) 2021-2022 Apple Inc. All Rights Reserved.
*/

#ifndef DEVICE_DISCOVERY_EXTENSION_INDIRECT_INCLUDES
#error "Please #import <DeviceDiscoveryExtension/DeviceDiscoveryExtension.h> instead of this file directly."
#endif

#pragma once

#import <DeviceDiscoveryExtension/DDCommon.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------------------------------------------------------
/// Manages a session between the extension and host.
DD_EXTERN
@interface DDDiscoverySession : NSObject

/// Reports an event to the host.
- (void) reportEvent:(DDDeviceEvent *) inEvent;

@end

#ifdef __cplusplus
}
#endif

NS_ASSUME_NONNULL_END
