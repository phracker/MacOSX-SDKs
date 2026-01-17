/*
 *	CTTextTab.h
 *	CoreText
 *
 *	Copyright (c) 2004-2011 Apple Inc. All rights reserved.
 *
 */

/*!
    @header

    Thread Safety Information

    All functions in this header are thread safe unless otherwise specified.
*/

#ifndef __CTTEXTTAB__
#define __CTTEXTTAB__

#include <CoreText/CTDefines.h>
#include <CoreText/CTParagraphStyle.h>
#include <CoreFoundation/CFCharacterSet.h>
#include <CoreFoundation/CFDictionary.h>
#include <AvailabilityMacros.h>

#if defined(__cplusplus)
extern "C" {
#endif

/* --------------------------------------------------------------------------- */
/* Text Tab Types */
/* --------------------------------------------------------------------------- */

/* A CTTextTab represents a tab in an CTParagraphStyle object, storing an
	alignment type and location.

	CoreText supports four alignment types: left, center, right, and decimal.
	These alignment types are absolute, not based on the line sweep direction
	of text. For example, tabbed text is always positioned to the left of a
	right-aligned tab, whether the line sweep direction is left to right or right
	to left. A tab's location, on the other hand, is relative to the back margin.
	A tab set at 1.5", for example, is at 1.5" from the right in right to left
	text.
*/

typedef const struct __CTTextTab * CTTextTabRef;


/*!
	@function	CTTypesetterGetTypeID
	@abstract	Returns the CFType of the text tab object
*/

CFTypeID CTTextTabGetTypeID( void ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);


/* --------------------------------------------------------------------------- */
/* Text Tab Constants */
/* --------------------------------------------------------------------------- */

/*!
	@const		kCTTabColumnTerminatorsAttributeName
	@abstract	Used to specify the terminating character for a tab column

	@discussion The value associated with this attribute is a CFCharacterSet. The
				character set is used to determine the terminating character for
				a tab column. The tab and newline characters are implied even if
				they don't exist in the character set. This attribute can be used
				to implement decimal tabs, for instance. This attribute is
				optional.
*/

extern const CFStringRef kCTTabColumnTerminatorsAttributeName CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);


/* --------------------------------------------------------------------------- */
/* Text Tab Creation */
/* --------------------------------------------------------------------------- */

/*!
	@function	CTTextTabCreate
	@abstract	Creates and initializes a new text tab.

	@param		alignment
				The tab's alignment. This is used to determine the position of
				text inside the tab column. This parameter must be set to a valid
				CTTextAlignment value or this function will return NULL.

	@param		location
				The tab's ruler location, relative to the back margin.

	@param		options
				Options to pass in when the tab is created. Currently, the only
				option available is kCTTabColumnTerminatorsAttributeName. This
				parameter is optional and can be set to NULL if not needed.

	@result		This function will return a reference to a CTTextTab if the call
				was successful. Otherwise, this function will return NULL.
*/

CTTextTabRef CTTextTabCreate(
	CTTextAlignment alignment,
	double location,
	CFDictionaryRef options ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);


/* --------------------------------------------------------------------------- */
/* Text Tab Access */
/* --------------------------------------------------------------------------- */

/*!
	@function	CTTextTabGetAlignment
	@abstract	Returns the text alignment of the tab.

	@param		tab
				The tab whose text alignment you wish to access.

	@result		The tab's text alignment value.
*/

CTTextAlignment CTTextTabGetAlignment(
	CTTextTabRef tab ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);


/*!
	@function	CTTextTabGetLocation
	@abstract	Returns the tab's ruler location.

	@param		tab
				The tab whose location you wish to access.

	@result		The tab's ruler location relative to the back margin.
*/

double CTTextTabGetLocation(
	CTTextTabRef tab ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);


/*!
	@function	CTTextTabGetOptions
	@abstract	Returns the dictionary of attributes associated with the tab. 

	@param		tab
				The tab whose attributes you wish to access.

	@result		The dictionary of attributes associated with the tab or NULL if
				no dictionary is present.
*/

CFDictionaryRef CTTextTabGetOptions(
	CTTextTabRef tab ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);


#if defined(__cplusplus)
}
#endif

#endif
