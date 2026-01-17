//
//  ATSAvailability.h
//  ATSUI
//
//  Copyright (c) 2018-2022 Apple Inc. All rights reserved.
//

#ifndef __ATS_AVAILIBILITY__
#define __ATS_AVAILIBILITY__

#if ATS_BUILDING_ATS || defined(CARBON)

#define ATSUI_UNAVAILABLE

#else

#if MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_VERSION_13_0
#define ATSUI_UNAVAILABLE	UNAVAILABLE_ATTRIBUTE
#else
#define ATSUI_UNAVAILABLE	API_DEPRECATED("No longer supported", macos(10.0,10.6))
#endif


#endif


#endif /* __ATS_AVAILIBILITY__ */
