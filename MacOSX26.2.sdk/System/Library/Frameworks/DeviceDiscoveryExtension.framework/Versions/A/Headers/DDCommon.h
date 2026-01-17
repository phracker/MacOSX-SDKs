/*
	Copyright (C) 2021-2022 Apple Inc. All Rights Reserved.
*/

#ifndef DEVICE_DISCOVERY_EXTENSION_INDIRECT_INCLUDES
#error "Please #import <DeviceDiscoveryExtension/DeviceDiscoveryExtension.h> instead of this file directly."
#endif

#pragma once

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#ifdef __cplusplus
extern "C" {
#endif

/// Marks an API as exported.
#ifndef DD_EXTERN
#ifdef __cplusplus
#define DD_EXTERN extern "C" __attribute__((visibility("default")))
#else
#define DD_EXTERN extern __attribute__((visibility("default")))
#endif
#endif

/// Work around some projects disabling OS_OBJECT_USE_OBJC by mapping to strong/assign as needed.
#if defined( OS_OBJECT_USE_OBJC ) && OS_OBJECT_USE_OBJC
	#define dd_os_ownership		strong
#else
	#define dd_os_ownership		assign
#endif

#ifdef __cplusplus
}
#endif

NS_ASSUME_NONNULL_END
