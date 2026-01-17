
/*
 *  AXTextAttributedString.h
 *
 *  Copyright (c) 2002 Apple Computer, Inc. All rights reserved.
 *
 */

#ifndef AXTEXTATTRIBUTEDSTRING_H
#define AXTEXTATTRIBUTEDSTRING_H

#ifdef __cplusplus
extern "C" {
#endif

#include <CoreFoundation/CoreFoundation.h>

extern CFStringRef kAXFontTextAttribute			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// CFDictionaryRef - see kAXFontTextAttribute keys below
extern CFStringRef kAXForegroundColorTextAttribute	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// CGColorRef
extern CFStringRef kAXBackgroundColorTextAttribute	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// CGColorRef
extern CFStringRef kAXUnderlineColorTextAttribute	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// CGColorRef
extern CFStringRef kAXStrikethroughColorTextAttribute	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// CGColorRef
extern CFStringRef kAXUnderlineTextAttribute		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// CFNumberRef - AXUnderlineStyle
extern CFStringRef kAXSuperscriptTextAttribute		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// CFNumberRef = + number for superscript - for subscript
extern CFStringRef kAXStrikethroughTextAttribute	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// CFBooleanRef
extern CFStringRef kAXShadowTextAttribute		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// CFBooleanRef

extern CFStringRef kAXAttachmentTextAttribute		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// AXUIElementRef
extern CFStringRef kAXLinkTextAttribute			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// AXUIElementRef

extern CFStringRef kAXNaturalLanguageTextAttribute	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// CFStringRef - the spoken language of the text
extern CFStringRef kAXReplacementStringTextAttribute	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// CFStringRef

extern CFStringRef kAXMisspelledTextAttribute		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// AXUIElementRef

extern CFStringRef kAXAutocorrectedTextAttribute	AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;	// CFBooleanRef

// kAXFontTextAttribute keys
extern CFStringRef kAXFontNameKey			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// CFStringRef - required
extern CFStringRef kAXFontFamilyKey			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// CFStringRef - not required
extern CFStringRef kAXVisibleNameKey			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// CFStringRef - not required
extern CFStringRef kAXFontSizeKey			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// CFNumberRef - required

enum {
    kAXUnderlineStyleNone	= 0x0,
    kAXUnderlineStyleSingle	= 0x1,
    kAXUnderlineStyleThick	= 0x2,
    kAXUnderlineStyleDouble	= 0x9
};
typedef UInt32 AXUnderlineStyle;


// DO NOT USE. This is an old, misspelled version of one of the above constants.
extern CFStringRef kAXForegoundColorTextAttribute	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	// CGColorRef

#ifdef __cplusplus
}
#endif

#endif // AXTEXTATTRIBUTEDSTRING_H
