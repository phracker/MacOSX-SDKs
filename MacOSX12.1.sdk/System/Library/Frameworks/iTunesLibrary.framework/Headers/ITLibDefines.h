/*!
	@header
	@copyright 2012-2016 Apple Inc.
 */

#ifndef ITLIB_DEFINES_H
#define ITLIB_DEFINES_H

#import <AvailabilityMacros.h>

#define ITLIB_EXPORT __attribute__((visibility("default")))

#ifdef __cplusplus
	#define ITLIB_EXTERN		extern "C"
#else
	#define ITLIB_EXTERN		extern
#endif

/*!
	Since the iTunesLibrary.framework ships outside of OS release cycles and supports multiple OS versions,
	no existing availability check macro can work.  Instead, the ITLIB_AVAILABLE() macro just marks the symbol
	weak and declares with which version of iTunes it first became available.
*/
#define ITLIB_AVAILABLE( version )		WEAK_IMPORT_ATTRIBUTE

#endif // ITLIB_DEFINES_H
