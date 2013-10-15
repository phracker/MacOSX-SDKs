/*
 *	CTGlyphInfo.h
 *	CoreText
 *
 *	Copyright (c) 2006-2011 Apple Inc. All rights reserved.
 *
 */

/*!
    @header

    Thread Safety Information

    All functions in this header are thread safe unless otherwise specified.
*/

#ifndef __CTGLYPHINFO__
#define __CTGLYPHINFO__

#include <CoreText/CTDefines.h>
#include <CoreText/CTFont.h>

#if defined(__cplusplus)
extern "C" {
#endif

/* --------------------------------------------------------------------------- */
/* Glyph Info Types */
/* --------------------------------------------------------------------------- */

typedef const struct __CTGlyphInfo * CTGlyphInfoRef;

/*!
	@function	CTGlyphInfoGetTypeID
	@abstract	Returns the CFType of the glyph info object
*/

CFTypeID CTGlyphInfoGetTypeID( void ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);


/* --------------------------------------------------------------------------- */
/* Glyph Info Values */
/* --------------------------------------------------------------------------- */

/*!
	@enum		CTCharacterCollection
	@abstract	These constants specify character collections.

	@constant	kCTIdentityMappingCharacterCollection
				Indicates that the character identifier is equal to the CGGlyph
				glyph index.

	@constant	kCTAdobeCNS1CharacterCollection
				Indicates the Adobe-CNS1 mapping.

	@constant	kCTAdobeGB1CharacterCollection
				Indicates the Adobe-GB1 mapping.

	@constant	kCTAdobeJapan1CharacterCollection
				Indicates the Adobe-Japan1 mapping.

	@constant	kCTAdobeJapan2CharacterCollection
				Indicates the Adobe-Japan2 mapping.

	@constant	kCTAdobeKorea1CharacterCollection
				Indicates the Adobe-Korea1 mapping.
*/

enum
{
	kCTIdentityMappingCharacterCollection = 0,
	kCTAdobeCNS1CharacterCollection = 1,
	kCTAdobeGB1CharacterCollection = 2,
	kCTAdobeJapan1CharacterCollection = 3,
	kCTAdobeJapan2CharacterCollection = 4,
	kCTAdobeKorea1CharacterCollection = 5
};
typedef uint16_t CTCharacterCollection;


/* --------------------------------------------------------------------------- */
/* Glyph Info Creation */
/* --------------------------------------------------------------------------- */

/*!
	@function	CTGlyphInfoCreateWithGlyphName
	@abstract	Creates an immutable glyph info object.

	@discussion This function creates an immutable glyph info object for a glyph
				name such as "copyright" and a specified font.

	@param		glyphName
				The name of the glyph.

	@param		font
				The font to be associated with the returned CTGlyphInfo object.

	@param		baseString
				The part of the string the returned object is intended
				to override.

	@result		If glyph info creation was successful, this function will return
				a valid reference to an immutable CTGlyphInfo object. Otherwise,
				this function will return NULL.
*/

CTGlyphInfoRef CTGlyphInfoCreateWithGlyphName(
	CFStringRef glyphName,
	CTFontRef font,
	CFStringRef baseString ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);


/*!
	@function	CTGlyphInfoCreateWithGlyph
	@abstract	Creates an immutable glyph info object.

	@discussion This function creates an immutable glyph info object for a glyph
				index and a specified font.

	@param		glyph
				The glyph identifier.

	@param		font
				The font to be associated with the returned CTGlyphInfo object.

	@param		baseString
				The part of the string the returned object is intended
				to override.

	@result		If glyph info creation was successful, this function will return
				a valid reference to an immutable CTGlyphInfo object. Otherwise,
				this function will return NULL.
*/

CTGlyphInfoRef CTGlyphInfoCreateWithGlyph(
	CGGlyph glyph,
	CTFontRef font,
	CFStringRef baseString ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);


/*!
	@function	CTGlyphInfoCreateWithCharacterIdentifier
	@abstract	Creates an immutable glyph info object.

	@discussion This function creates an immutable glyph info object for a
				character identifier and a character collection.

	@param		cid
				A character identifier.

	@param		collection
				A character collection identifier.

	@param		baseString
				The part of the string the returned object is intended
				to override.

	@result		If glyph info creation was successful, this function will return
				a valid reference to an immutable CTGlyphInfo object. Otherwise,
				this function will return NULL.
*/

CTGlyphInfoRef CTGlyphInfoCreateWithCharacterIdentifier(
	CGFontIndex cid,
	CTCharacterCollection collection,
	CFStringRef baseString ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);


/* --------------------------------------------------------------------------- */
/* Glyph Info Access */
/* --------------------------------------------------------------------------- */

/*!
	@function	CTGlyphInfoGetGlyphName
	@abstract	Gets the glyph name for a glyph info, if applicable.

	@discussion This function will return the glyph name.

	@param		glyphInfo
				The glyph info for which you would like the glyph name. This
				parameter may not be set to NULL.

	@result		If the glyph info object was created with a glyph name, it will
				be returned. Otherwise, this function will return NULL.
*/

CFStringRef CTGlyphInfoGetGlyphName(
	CTGlyphInfoRef glyphInfo ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);


/*!
	@function	CTGlyphInfoGetCharacterIdentifier
	@abstract	Gets the character identifier for a glyph info.

	@discussion This function will return the character identifier.

	@param		glyphInfo
				The glyph info for which you would like the character identifier.
				This parameter may not be set to NULL.

	@result		If the glyph info object was created with a character identifier,
				it will be returned. Otherwise, this function will return 0.
*/

CGFontIndex CTGlyphInfoGetCharacterIdentifier(
	CTGlyphInfoRef glyphInfo ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);


/*!
	@function	CTGlyphInfoGetCharacterCollection
	@abstract	Gets the character collection for a glyph info.

	@discussion This function will return the character collection. If the glyph
				info object was created with a glyph name or a glyph index, its
				character collection will be
				kCTIdentityMappingCharacterCollection.

	@param		glyphInfo
				The glyph info for which you would like the character collection.
				This parameter may not be set to NULL.

	@result		This function will return the character collection of the given
				glyph info.
*/

CTCharacterCollection CTGlyphInfoGetCharacterCollection(
	CTGlyphInfoRef glyphInfo ) CT_AVAILABLE_STARTING( __MAC_10_5, __IPHONE_3_2);


#if defined(__cplusplus)
}
#endif

#endif
