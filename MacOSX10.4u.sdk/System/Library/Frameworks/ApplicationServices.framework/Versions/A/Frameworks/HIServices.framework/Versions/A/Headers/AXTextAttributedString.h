
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

extern CFStringRef kAXFontTextAttribute;		// CFDictionaryRef - see kAXFontTextAttribute keys below
extern CFStringRef kAXForegroundColorTextAttribute;	// CGColorRef
extern CFStringRef kAXBackgroundColorTextAttribute;	// CGColorRef
extern CFStringRef kAXUnderlineColorTextAttribute;	// CGColorRef
extern CFStringRef kAXStrikethroughColorTextAttribute;	// CGColorRef
extern CFStringRef kAXUnderlineTextAttribute;		// CFNumberRef - AXUnderlineStyle
extern CFStringRef kAXSuperscriptTextAttribute;		// CFNumberRef = + number for superscript - for subscript
extern CFStringRef kAXStrikethroughTextAttribute;	// CFBooleanRef
extern CFStringRef kAXShadowTextAttribute;		// CFBooleanRef

extern CFStringRef kAXAttachmentTextAttribute;		// AXUIElementRef
extern CFStringRef kAXLinkTextAttribute;		// AXUIElementRef

extern CFStringRef kAXNaturalLanguageTextAttribute;	// CFStringRef - the spoken language of the text
extern CFStringRef kAXReplacementStringTextAttribute;	// CFStringRef

extern CFStringRef kAXMisspelledTextAttribute;		// AXUIElementRef

// kAXFontTextAttribute keys
extern CFStringRef kAXFontNameKey;		// CFStringRef - required
extern CFStringRef kAXFontFamilyKey;		// CFStringRef - not required
extern CFStringRef kAXVisibleNameKey;		// CFStringRef - not required
extern CFStringRef kAXFontSizeKey;		// CFNumberRef - required

enum {
    kAXUnderlineStyleNone	= 0x0,
    kAXUnderlineStyleSingle	= 0x1,
    kAXUnderlineStyleThick	= 0x2,
    kAXUnderlineStyleDouble	= 0x9
};
typedef UInt32 AXUnderlineStyle;


// DO NOT USE. This is an old, misspelled version of one of the above constants.
extern CFStringRef kAXForegoundColorTextAttribute;	// CGColorRef

#ifdef __cplusplus
}
#endif

#endif // AXTEXTATTRIBUTEDSTRING_H
