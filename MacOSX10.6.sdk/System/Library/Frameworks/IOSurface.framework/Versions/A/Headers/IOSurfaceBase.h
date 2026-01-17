/*
 *  IOSurfaceBase.h
 *  IOSurface
 *
 *  Copyright 2006-2008 Apple, Inc. All rights reserved.
 *
 */

#ifndef _IOSURFACE_BASE_H
#define _IOSURFACE_BASE_H

#include <sys/cdefs.h>

#  include <AvailabilityMacros.h>
#  if defined(MAC_OS_X_VERSION_10_6)
#    include <Availability.h>
#  endif /* defined(MAC_OS_X_VERSION_10_6) */

#if !defined(MAC_OS_X_VERSION_10_6) || defined(IOSFC_BUILDING_IOSFC)
#  define IOSFC_DEPRECATED 
#  define IOSFC_AVAILABLE_STARTING(_mac,_iphone)
#  define IOSFC_AVAILABLE_BUT_DEPRECATED(_mac,_macDep,_iphone,_iphoneDep)
#else /* !defined(IOSFC_BUILDING_IOSFC) */
#  define IOSFC_DEPRECATED DEPRECATED_ATTRIBUTE
#  define IOSFC_AVAILABLE_STARTING __OSX_AVAILABLE_STARTING
#  define IOSFC_AVAILABLE_BUT_DEPRECATED __OSX_AVAILABLE_BUT_DEPRECATED
#endif /* !defined(IOSFC_BUILDING_IOSFC) */

#include <CoreFoundation/CFBase.h>

#endif
