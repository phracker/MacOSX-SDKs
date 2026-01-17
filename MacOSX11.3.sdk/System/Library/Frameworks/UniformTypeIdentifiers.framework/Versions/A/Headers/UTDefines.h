//
//  UTDefines.h
//
//  Copyright © 2020 Apple. All rights reserved.
//

#ifndef __UNIFORMTYPEIDENTIFIERS_UTDEFINES__
#define __UNIFORMTYPEIDENTIFIERS_UTDEFINES__

#include <Availability.h>

#if !defined(UT_EXPORT)
	#if defined(__cplusplus)
		#define UT_EXPORT extern "C" __attribute__((visibility("default")))
	#else // defined(__cplusplus)
		#define UT_EXPORT extern __attribute__((visibility("default")))
	#endif // defined(__cplusplus)
#endif // !defined(UT_EXPORT)

#if !defined(UT_EXPORT_CLASS)
	#define UT_EXPORT_CLASS __attribute__((visibility("default")))
#endif // !defined(UT_EXPORT_CLASS)

#if !defined(UT_AVAILABLE_BEGIN)
	#define UT_AVAILABLE_BEGIN API_AVAILABLE_BEGIN(macos(11.0), macCatalyst(14.0), ios(14.0), watchos(7.0), tvos(14.0))
#endif // !defined(UT_AVAILABLE_BEGIN)
#if !defined(UT_AVAILABLE_END)
	#define UT_AVAILABLE_END API_AVAILABLE_END
#endif // !defined(UT_AVAILABLE_END)

#if !defined(UT_SUBCLASSING_RESTRICTED)
	#define UT_SUBCLASSING_RESTRICTED __attribute__((__objc_subclassing_restricted__))
#endif // !defined(UT_SUBCLASSING_RESTRICTED)

#endif // __UNIFORMTYPEIDENTIFIERS_UTDEFINES__
