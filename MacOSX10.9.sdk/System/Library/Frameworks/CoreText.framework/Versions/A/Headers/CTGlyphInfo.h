/*
 *	CTGlyphInfo.h
 *	CoreText
 *
 *	Copyright (c) 2006-2012 Apple Inc. All rights reserved.
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

CF_IMPLICIT_BRIDGING_ENABLED

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

CFTypeID CTGlyphInfoGetTypeID( void ) CT_AVAILABLE(10_5, 3_2);


/* --------------------------------------------------------------------------- */
/* Glyph Info Values */
/* --------------------------------------------------------------------------- */

/*!
	@enum		CTCharacterCollection
	@abstract	These constants specify character collections.

	@constant	kCTCharacterCollectionIdentityMapping
				Indicates that the character identifier is equal to the CGGlyph
				glyph index.

	@constant	kCTCharacterCollectionAdobeCNS1
				Indicates the Adobe-CNS1 mapping.

	@constant	kCTCharacterCollectionAdobeGB1
				Indicates the Adobe-GB1 mapping.

	@constant	kCTCharacterCollectionAdobeJapan1
				Indicates the Adobe-Japan1 mapping.

	@constant	kCTCharacterCollectionAdobeJapan2
				Indicates the Adobe-Japan2 mapping.

	@constant	kCTCharacterCollectionAdobeKorea1
				Indicates the Adobe-Korea1 mapping.
*/

typedef CF_ENUM(uint16_t, CTCharacterCollection) {
	kCTCharacterCollectionIdentityMapping   = 0,
	kCTCharacterCollectionAdobeCNS1         = 1,
	kCTCharacterCollectionAdobeGB1          = 2,
	kCTCharacterCollectionAdobeJapan1       = 3,
	kCTCharacterCollectionAdobeJapan2       = 4,
	kCTCharacterCollectionAdobeKorea1       = 5,

	kCTIdentityMappingCharacterCollection = kCTCharacterCollectionIdentityMapping,
	kCTAdobeCNS1CharacterCollection = kCTCharacterCollectionAdobeCNS1,
	kCTAdobeGB1CharacterCollection = kCTCharacterCollectionAdobeGB1,
	kCTAdobeJapan1CharacterCollection = kCTCharacterCollectionAdobeJapan1,
	kCTAdobeJapan2CharacterCollection = kCTCharacterCollectionAdobeJapan2,
	kCTAdobeKorea1CharacterCollection = kCTCharacterCollectionAdobeKorea1
};


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
	CFStringRef baseString ) CT_AVAILABLE(10_5, 3_2);


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
	CFStringRef baseString ) CT_AVAILABLE(10_5, 3_2);


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
	CFStringRef baseString ) CT_AVAILABLE(10_5, 3_2);


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
	CTGlyphInfoRef glyphInfo ) CT_AVAILABLE(10_5, 3_2);


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
	CTGlyphInfoRef glyphInfo ) CT_AVAILABLE(10_5, 3_2);


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
	CTGlyphInfoRef glyphInfo ) CT_AVAILABLE(10_5, 3_2);


#if defined(__cplusplus)
}
#endif

CF_IMPLICIT_BRIDGING_DISABLED

#endif
