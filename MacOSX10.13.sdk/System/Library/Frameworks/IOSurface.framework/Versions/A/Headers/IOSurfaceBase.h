/*
 *  IOSurfaceBase.h
 *  IOSurface
 *
 *  Copyright 2006-2017 Apple Inc. All rights reserved.
 *
 */

#ifndef _IOSURFACE_BASE_H
#define _IOSURFACE_BASE_H

#include <sys/cdefs.h>

#include <Availability.h>
#include <TargetConditionals.h>

#if !(defined(MAC_OS_X_VERSION_10_13) || defined(__IPHONE_11_0)) || defined(IOSFC_BUILDING_IOSFC)
#  define IOSFC_DEPRECATED 
#  define IOSFC_DEPRECATED_MSG(s)
#  define IOSFC_IOS_DEPRECATED_MSG(s)
#  define IOSFC_AVAILABLE_STARTING(_mac,_iphone)
#  define IOSFC_AVAILABLE_BUT_DEPRECATED(_mac,_macDep,_iphone,_iphoneDep)
#  define IOSFC_CLASS_AVAILABLE(a, b)
#else /* !defined(IOSFC_BUILDING_IOSFC) */
#  define IOSFC_DEPRECATED DEPRECATED_ATTRIBUTE
#  define IOSFC_DEPRECATED_MSG(s) DEPRECATED_MSG_ATTRIBUTE(s)
#if TARGET_OS_EMBEDDED
#  define IOSFC_IOS_DEPRECATED_MSG(s) DEPRECATED_MSG_ATTRIBUTE(s)
#else
#  define IOSFC_IOS_DEPRECATED_MSG(s)
#endif
#  define IOSFC_AVAILABLE_STARTING __OSX_AVAILABLE_STARTING
#  define IOSFC_AVAILABLE_BUT_DEPRECATED __OSX_AVAILABLE_BUT_DEPRECATED
#  define IOSFC_CLASS_AVAILABLE NS_CLASS_AVAILABLE
#endif /* !defined(IOSFC_BUILDING_IOSFC) */

#if __has_feature(objc_class_property)
#define IOSFC_SWIFT_NAME(name) __attribute__((swift_name(#name)))
#else
#define IOSFC_SWIFT_NAME(name)
#endif

#include <mach/kern_return.h>
#include <CoreFoundation/CoreFoundation.h>
#if !TARGET_OS_EMBEDDED
#include <xpc/xpc.h>
#endif

#endif
