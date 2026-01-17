/*
 *	CTStringAttributes.h
 *	CoreText
 *
 *	Copyright (c) 2004-2008 Apple Inc. All rights reserved.
 *
 */

#ifndef __CTSTRINGATTRIBUTES__
#define __CTSTRINGATTRIBUTES__

#include <CoreFoundation/CFNumber.h>
#include <CoreFoundation/CFString.h>
#include <CoreGraphics/CGColor.h>

#if defined(__cplusplus)
extern "C" {
#endif

/* The purpose of this file is to define all the attributes to which
	CoreText will respond when placed in a CFAttributedString. These
	are left out of other header file on purpose in order to avoid
	layering problems. This file is allowed to include any other header
	file it wants to. */

/* --------------------------------------------------------------------------- */
/* CFAttributedStringRef Attribute Prototypes */
/* --------------------------------------------------------------------------- */

/*!
	@const		kCTFontAttributeName
	@abstract	The font.

	@discussion Value must be a CTFontRef. Default is Helvetica 12.
*/

extern const CFStringRef kCTFontAttributeName AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*!
	@const		kCTForegroundColorFromContextAttributeName
	@abstract	Never set a foreground color in the CGContext; use what is set as
				the context's fill color.

	@discussion Value must be a CFBooleanRef. Default is false. The reason
				why this exists is because an NSAttributedString defaults to a
				black color if no color attribute is set. This forces CoreText to
				set the color in the context. This will allow developers to
				sidestep this, making CoreText set nothing but font information
				in the CGContext. If set, this attribute also determines the
				color used by kCTUnderlineStyleAttributeName, in which case it
				overrides the foreground color.
*/

extern const CFStringRef kCTForegroundColorFromContextAttributeName AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*!
	@const		kCTKernAttributeName
	@abstract	A kerning adjustment.

	@discussion Value must be a CFNumberRef float. Default is standard kerning.
				The kerning attribute indicate how many points the following
				character should be shifted from its default offset as defined
				by the current character's font in points; a positive kern
				indicates a shift farther along and a negative kern indicates a
				shift closer to the current character. If this attribute is not
				present, standard kerning will be used. If this attribute is
				set to 0.0, no kerning will be done at all.
*/

extern const CFStringRef kCTKernAttributeName AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*!
	@const		kCTLigatureAttributeName
	@abstract	Controls ligature formation.

	@discussion Value must be a CFNumberRef. Default is int value 1. The ligature
				attribute determines what kinds of ligatures should be used when
				displaying the string. A value of 0 indicates that only ligatures
				essential for proper rendering of text should be used, 1
				indicates that standard ligatures should be used, and 2 indicates
				that all available ligatures should be used. Which ligatures are
				standard depends on the script and possibly the font. Arabic
				text, for example, requires ligatures for many character
				sequences, but has a rich set of additional ligatures that
				combine characters. English text has no essential ligatures, and
				typically has only two standard ligatures, those for "fi" and
				"fl" -- all others being considered more advanced or fancy.
*/

extern const CFStringRef kCTLigatureAttributeName AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*!
	@const		kCTForegroundColorAttributeName
	@abstract	The foreground color.

	@discussion Value must be a CGColorRef. Default value is black.
*/

extern const CFStringRef kCTForegroundColorAttributeName AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*!
	@const		kCTParagraphStyleAttributeName
	@abstract	A CTParagraphStyle object which is used to specify things like
				line alignment, tab rulers, writing direction, etc.

	@discussion Value must be a CTParagraphStyleRef. Default is an empty
				CTParagraphStyle object. See CTParagraphStyle.h for more
				information.
*/

extern const CFStringRef kCTParagraphStyleAttributeName AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*!
	@const		kCTStrokeWidthAttributeName
	@abstract	The stroke width.

	@discussion Value must be a CFNumberRef. Default value is 0.0, or no stroke.
				This attribute, interpreted as a percentage of font point size,
				controls the text drawing mode: positive values effect drawing
				with stroke only; negative values are for stroke and fill. A
				typical value for outlined text is 3.0.
*/

extern const CFStringRef kCTStrokeWidthAttributeName AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;


/*!
	@const		kCTStrokeColorAttributeName
	@abstract	The stroke color.

	@discussion Value must be a CGColorRef. Default is the foreground color.
*/

extern const CFStringRef kCTStrokeColorAttributeName AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;


/*!
	@const		kCTUnderlineStyleAttributeName
	@abstract	Allows the setting of an underline to be applied at render
				time.

	@discussion Value must be a CFNumberRef. Default is kCTUnderlineStyleNone.
				Set a value of something other than kCTUnderlineStyleNone to draw
				an underline. In addition, the CTUnderlineStyleModifiers can be
				used to modify the look of the underline. The underline color
				will be determined by the text's foreground color.
*/

extern const CFStringRef kCTUnderlineStyleAttributeName AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*!
	@const		kCTSuperscriptAttributeName
	@abstract	Controls vertical text positioning.

	@discussion Value must be a CFNumberRef. Default is int value 0. If supported
				by the specified font, a value of 1 enables superscripting and a
				value of -1 enables subscripting.
*/

extern const CFStringRef kCTSuperscriptAttributeName AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*!
	@const		kCTUnderlineColorAttributeName
	@abstract	The underline color.

	@discussion Value must be a CGColorRef. Default is the foreground color.
*/

extern const CFStringRef kCTUnderlineColorAttributeName AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*!
	@const		kCTVerticalFormsAttributeName
	@abstract	Controls glyph orientation.

	@discussion	Value must be a CFBooleanRef. Default is false. A value of false
				indicates that horizontal glyph forms are to be used, true
				indicates that vertical glyph forms are to be used.
*/

extern const CFStringRef kCTVerticalFormsAttributeName AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*!
	@const		kCTGlyphInfoAttributeName
	@abstract	Allows the use of unencoded glyphs.

	@discussion Value must be a CTGlyphInfoRef. The glyph specified by this
				CTGlyphInfo object is assigned to the entire attribute range,
				provided that its contents match the specified base string and
				that the specified glyph is available in the font specified by
				kCTFontAttributeName. See CTGlyphInfo.h for more information.
*/

extern const CFStringRef kCTGlyphInfoAttributeName AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*!
	@const		kCTCharacterShapeAttributeName
	@abstract	Controls glyph selection.

	@discussion	Value must be a CFNumberRef. Default is value is 0 (disabled).
				A non-zero value is interpreted as Apple Type Services
				kCharacterShapeType selector + 1; see <ATS/SFNTLayoutTypes.h>
				for selectors. For example, an attribute value of 1 corresponds
				to kTraditionalCharactersSelector.
*/

extern const CFStringRef kCTCharacterShapeAttributeName AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*!
	@enum		CTUnderlineStyle
	@abstract	Underline style specifiers.

	@discussion These underline type specifiers can be applied to the value set
				with the kCTUnderlineStyleAttributeName attribute to tell
				CoreText that you want a different underline style.
*/

enum
{
	kCTUnderlineStyleNone				 = 0x00,
	kCTUnderlineStyleSingle				 = 0x01,
	kCTUnderlineStyleThick				 = 0x02,
	kCTUnderlineStyleDouble				 = 0x09
};
typedef int32_t CTUnderlineStyle;


/*!
	@enum		CTUnderlineStyleModifiers
	@abstract	Underline style modifiers.

	@discussion Set these bits with the CTUnderlineStyle that you set with the
				kCTUnderlineStyleAttributeName attribute to modify how the
				underline will be drawn.
*/

enum
{
	kCTUnderlinePatternSolid			 = 0x0000,
	kCTUnderlinePatternDot				 = 0x0100,
	kCTUnderlinePatternDash				 = 0x0200,
	kCTUnderlinePatternDashDot			 = 0x0300,
	kCTUnderlinePatternDashDotDot		 = 0x0400
};
typedef int32_t CTUnderlineStyleModifiers;


#if defined(__cplusplus)
}
#endif

#endif
