/*
 * ImageIO - ImageIOBase.h
 * Copyright (c) 2009-2010 Apple Inc. 
 * All rights reserved.
 *
 */

#ifndef __IMAGEIOBASE__
#define __IMAGEIOBASE__

#include <CoreFoundation/CoreFoundation.h>

#if defined(IMAGEIO_BUILDING_IMAGEIO)

#   define IMAGEIO_AVAILABLE_STARTING(_mac,_iphone)
#   define IMAGEIO_AVAILABLE_BUT_DEPRECATED(_mac,_macDep,_iphone,_iphoneDep)

#else /* !defined(IMAGEIO_BUILDING_IMAGEIO) */

#   include <Availability.h>
#   define IMAGEIO_AVAILABLE_STARTING __OSX_AVAILABLE_STARTING
#   define IMAGEIO_AVAILABLE_BUT_DEPRECATED __OSX_AVAILABLE_BUT_DEPRECATED

#endif /* !defined(IMAGEIO_BUILDING_IMAGEIO) */


#if !defined(IMAGEIO_EXTERN)
#   if defined(__WIN32__)
#       if defined(IMAGEIO_BUILDING_IMAGEIO)
#           if defined(__cplusplus)
#               define IMAGEIO_EXTERN extern "C" __declspec(dllexport)
#           else /* !defined(__cplusplus) */
#               define IMAGEIO_EXTERN extern __declspec(dllexport)
#           endif /* !defined(__cplusplus) */
#       else /* !defined(IMAGEIO_BUILDING_IMAGEIO) */
#           if defined(__cplusplus)
#               define IMAGEIO_EXTERN extern "C" __declspec(dllimport) 
#           else /* !defined(__cplusplus) */
#               define IMAGEIO_EXTERN extern __declspec(dllimport)
#           endif /* !defined(__cplusplus) */
#       endif /* !defined(IMAGEIO_BUILDING_IMAGEIO) */
#   else /* !defined(__WIN32__) */
#       if defined(__cplusplus)
#           define IMAGEIO_EXTERN extern "C"
#       else /* !defined(__cplusplus) */
#           define IMAGEIO_EXTERN extern
#       endif /* !defined(__cplusplus) */
#   endif /* !defined(__WIN32__) */
#endif /* !defined(IMAGEIO_EXTERN) */


#if !defined(IMAGEIO_EXTERN_C_BEGIN)
#   ifdef __cplusplus
#       define IMAGEIO_EXTERN_C_BEGIN extern "C" {
#       define IMAGEIO_EXTERN_C_END   }
#   else
#       define IMAGEIO_EXTERN_C_BEGIN
#       define IMAGEIO_EXTERN_C_END
#   endif
#endif

#if (TARGET_OS_MAC && !TARGET_IPHONE_SIMULATOR) || TARGET_OS_EMBEDDED
#    define IIO_HAS_IOSURFACE 1
#else
#    define IIO_HAS_IOSURFACE 0
#endif

#if defined(__has_feature) && __has_feature(objc_bridge_id)
#define IIO_BRIDGED_TYPE(type)       CF_BRIDGED_TYPE(type)
#else
#define IIO_BRIDGED_TYPE(type)
#endif


#endif  /* __IMAGEIOBASE__ */
