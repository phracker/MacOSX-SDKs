//
//  ATSDefines.h
//  ATS
//
//  Copyright (c) 2011-2019 Apple Inc. All rights reserved.
//

#ifndef __ATSDEFINES__
#define __ATSDEFINES__

#if defined(ATS_BUILDING_ATS)
# define ATS_UNAVAILABLE
#elif defined(__has_extension) /* defined(ATS_BUILDING_ATS) */
# if __has_extension(attribute_deprecated_with_message)
#  include <Availability.h>
#  if (!defined(MAC_OS_X_VERSION_MIN_REQUIRED) || !defined(MAC_OS_VERSION_13_0) || MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_VERSION_13_0) && !defined(ATS_BUILDING_ATS) && !defined(CARBON)
#   define ATS_UNAVAILABLE UNAVAILABLE_ATTRIBUTE
#  else
#   define ATS_UNAVAILABLE API_DEPRECATED("ATS is no longer supported", macos(10.0,10.8))
#  endif
# endif /*__has_extension(attribute_deprecated_with_message) */
#endif /* defined(__has_extension)*/ /* defined(ATS_BUILDING_ATS) */

#include <TargetConditionals.h>
#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)) || (TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)
#if defined(ATS_BUILDING_ATS) || defined(CARBON)
# define ATS_LEGACY_API 1
#else
#if TARGET_OS_MAC && (!defined(MAC_OS_X_VERSION_MIN_REQUIRED) || !defined(MAC_OS_VERSION_13_0) || MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_VERSION_13_0)
# define ATS_LEGACY_API 0
#else
# define ATS_LEGACY_API 1
#endif
#endif
#else
# define ATS_LEGACY_API 0
#endif // (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)) || (TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)

#endif //__ATSDEFINES__
