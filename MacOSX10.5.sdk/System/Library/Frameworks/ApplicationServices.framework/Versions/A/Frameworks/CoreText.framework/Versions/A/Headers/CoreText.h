/*
 *  CoreText.h
 *	CoreText
 *
 *  Copyright (c) 2006 Apple Computer, Inc. All rights reserved.
 *
 */

#ifndef __CORETEXT__
#define __CORETEXT__

#include <CoreText/CTFont.h>
#include <CoreText/CTFontCollection.h>
#include <CoreText/CTFontDescriptor.h>
#include <CoreText/CTFontTraits.h>
#include <CoreText/CTFrame.h>
#include <CoreText/CTFramesetter.h>
#include <CoreText/CTGlyphInfo.h>
#include <CoreText/CTLine.h>
#include <CoreText/CTParagraphStyle.h>
#include <CoreText/CTRun.h>
#include <CoreText/CTStringAttributes.h>
#include <CoreText/CTTextTab.h>
#include <CoreText/CTTypesetter.h>
#include <AvailabilityMacros.h>

#if defined(__cplusplus)
extern "C" {
#endif

/*!
	@function	CTGetCoreTextVersion
	@abstract	Returns the version of the CoreText framework.

	@discussion	This function returns a number indicating the version of the
				CoreText framework. Note that framework version is not always
				an accurate indicator of feature availability. The recommended
				way to use this function is first to check that the function
				pointer is non-NULL, followed by calling it and comparing its
				result to a defined constant (or constants). For example, to
				determine whether the CoreText API is available:
					if (&CTGetCoreTextVersion != NULL && CTGetCoreTextVersion() >= kCTVersionNumber10_5) {
						// CoreText API is available
					}

	@result		The version number. This value is for comparison with the
				constants beginning with kCTVersionNumber.
*/

uint32_t CTGetCoreTextVersion( void ) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

#define kCTVersionNumber10_5 0x00020000

#if defined(__cplusplus)
}
#endif

#endif
