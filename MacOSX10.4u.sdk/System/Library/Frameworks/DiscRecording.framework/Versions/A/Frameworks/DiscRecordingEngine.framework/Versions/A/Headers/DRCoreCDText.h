/*
     File:       DiscRecordingEngine/DRCoreCDText.h
 
     Contains:   CD-Text interfaces for Disc Recording.
 
     Version:    Technology: Mac OS X
                 Release:    Mac OS X
 
     Copyright:  (c) 2002-2004 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

/*!
	@header
	@abstract		CD-Text object used in the Disc Recording APIs.

	@discussion		CD-Text allows the authors of an audio CD to encode textual
	information about the CD and its tracks onto the disc.  Information such as
	album name, track names, artist, songwriter, performer, and more can be
	encoded this way. When a disc containing CD-Text is inserted into a CD-Text
	aware player, this information is displayed as the CD plays.
	
	CD-Text is only for audio CDs; it does not apply to and does not work on
	data CDs or DVDs.
	
	Here's a conceptual description of how CD-Text works. The CD-Text information for
	a disc can contain up to eight blocks of textual information.  Each block has an
	associated language code and character set, and contains a complete set of
	information about the disc.
	
	<pre>
	+----------------------------+
	| +------------------------+ |
	| | CD-Text block 1        | |
	| |  - language code       | |
	| |  - character set       | |
	| +------------------------+ |
	|            .               |
	|            .               |
	|            .               |
	| +------------------------+ |
	| | CD-Text block 8        | |
	| |  - language code       | |
	| |  - character set       | |
	| +------------------------+ |
	+----------------------------+
	</pre>
	
	In typical use each block of CD-Text contains a different language--English,
	French, Japanese, Chinese, and so on--although only single-byte encodings are 
	currently supported.  It's possible and permissible to have multiple blocks 
	that each contain the same language.
	
	Each block can hold a complete set of information about the disc and its tracks.  This
	information is stored as an array of key-value dictionaries. There is one dictionary
	per track, with an additional dictionary for the disc/album itself (represented by 
	array index 0).	On a disc with n tracks, there will be n+1 dictionaries.
	
	<pre>
	+----------------------------+
	| CD-Text block              |
	|  - language code           |
	|  - character set           |
	| +------------------------+ |
	| | Index 0 - disc info    | |
	| +------------------------+ |
	| +------------------------+ |
	| | Index 1 - track 1 info | |
	| +------------------------+ |
	| +------------------------+ |
	| | Index 2 - track 2 info | |
	| +------------------------+ |
	|            .               |
	|            .               |
	|            .               |
	| +------------------------+ |
	| | Index n - track n info | |
	| +------------------------+ |
	+----------------------------+
	</pre>
	
	Dictionaries for individual tracks contain the textual
	information to be displayed. This information is strictly limited to the
	character set specified by the enclosing block, and is likewise assumed to
	be in the language specified. 
	
	<pre>
	+----------------------------+
	| Track info dictionary      |
	|                            |
	|  Title = "title"           |
	|  Artist = "artist"         |
	|  Performer = "performer"   |
	|            .               |
	|            .               |
	|            .               |
	+----------------------------+
	</pre>
	
	For compatibility with the widest range of CD players, text values in CD-Text
	dictionaries should be 160 bytes or smaller.  Since the currently supported
	character encodings are all single-byte encodings, this means a maximum of
	160 characters per entry.
*/

#ifndef _H_DRCoreCDText
#define _H_DRCoreCDText

#if PRAGMA_ONCE
#pragma once
#endif

#ifndef __COREFOUNDATION__
#include <CoreFoundation/CoreFoundation.h>
#endif

#ifndef _H_DRCoreObject
#include <DiscRecordingEngine/DRCoreObject.h>
#endif

#ifndef __AVAILABILITYMACROS__
#include <AvailabilityMacros.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif


/* ----------------------------------- */
/* CD-Text encodings */
/*
	These values are special CFStringEncoding values.  Note that
	CD-Text does not support any arbitrary CFStringEncoding; instead,
	strings are limited to the encodings found here.
				
	There is no UTF-8 encoding value defined for CD-Text at the
	time of this writing.
*/

/*!
	@enum	CD-Text Encodings
	@abstract	Special CFStringEncoding values supported by the CD-Text format.
	@discussion	The CD-Text format supports only encodings listed here. For now, it 
				does not support the UTF-8 encoding.
*/
enum
{
	kDRCDTextEncodingISOLatin1Modified			= kCFStringEncodingISOLatin1,	/* ISO-Latin-1 ... not quite correct since 5 characters are different, to be changed when TEC adds the new encoding */
	kDRCDTextEncodingASCII						= kCFStringEncodingASCII		/* 7-bit ASCII */
};

/* ----------------------------------- */
/* CD-Text genre codes */
/*
	These values are numeric codes for the genre, which is typically used by
	players to automatically assign equalizer settings.  If no genre code is
	specified, a value of kDRCDTextGenreCodeUnknown is used.
	
	You can also specify a textual genre description, which supplements
	the numeric genre code.  Usually, no matter what the genre code is, the
	textual genre will be visible to the listener.
*/
/*!
	@enum	CD-Text Genres
	@abstract	Numeric values for audio content genres.
	@discussion	CD players can use the numeric codes associated with these
				genres to automatically assign equalizer settings. If no
				genre code is specified, a value of kDRCDTextGenreCodeUnknown 
				is used.
				
				You can also specify a textual genre description, using the
				kDRCDTextGenreKey CD-Text dictionary key, to supplement
				the numeric code.  In typical implementations, the textual genre 
				will be visible to the listener regardless of the genre code.
*/
enum
{
	kDRCDTextGenreCodeUnknown				= 0x0001,
	kDRCDTextGenreCodeAdultContemporary		= 0x0002,
	kDRCDTextGenreCodeAlternativeRock		= 0x0003,
	kDRCDTextGenreCodeChildrens				= 0x0004,
	kDRCDTextGenreCodeClassical				= 0x0005,
	kDRCDTextGenreCodeContemporaryChristian	= 0x0006,
	kDRCDTextGenreCodeCountry				= 0x0007,
	kDRCDTextGenreCodeDance					= 0x0008,
	kDRCDTextGenreCodeEasyListening			= 0x0009,
	kDRCDTextGenreCodeErotic				= 0x000A,
	kDRCDTextGenreCodeFolk					= 0x000B,
	kDRCDTextGenreCodeGospel				= 0x000C,
	kDRCDTextGenreCodeHipHop				= 0x000D,
	kDRCDTextGenreCodeJazz					= 0x000E,
	kDRCDTextGenreCodeLatin					= 0x000F,
	kDRCDTextGenreCodeMusical				= 0x0010,
	kDRCDTextGenreCodeNewAge				= 0x0011,
	kDRCDTextGenreCodeOpera					= 0x0012,
	kDRCDTextGenreCodeOperetta				= 0x0013,
	kDRCDTextGenreCodePop					= 0x0014,
	kDRCDTextGenreCodeRap					= 0x0015,
	kDRCDTextGenreCodeReggae				= 0x0016,
	kDRCDTextGenreCodeRock					= 0x0017,
	kDRCDTextGenreCodeRhythmAndBlues		= 0x0018,
	kDRCDTextGenreCodeSoundEffects			= 0x0019,
	kDRCDTextGenreCodeSoundtrack			= 0x001A,
	kDRCDTextGenreCodeSpokenWord			= 0x001B,
	kDRCDTextGenreCodeWorldMusic			= 0x001C
};


/* ----------------------------------- */
/* CD-Text parsing */
/*!
	@function	DRCDTextBlockCreateArrayFromPackList
	@abstract	Parses raw CD-Text data into DRCDTextBlock objects.
	@discussion	You can use this function to parse any data blob containing CD-Text PACKs,
				such as the result of DRDeviceReadCDText, or the data returned by the
				IOKit ioctl DKIOCCDREADTOC with format=5.  
				
				The CFData should be sized to fit the exact number of PACKs.  Each PACK
				occupies 18 bytes, and the 4-byte header from a READ TOC command may
				optionally be included.
	@param		packs		CFDataRef containing raw CD-Text PACKs.
	@result		A CFArray object containing DRCDTextBlock objects describing the information
				in the raw PACKs, or NULL if the data could not be parsed.  The caller
				is responsible for releasing this array.
*/
extern CFArrayRef
DRCDTextBlockCreateArrayFromPackList(
	CFDataRef	packs)
AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* ----------------------------------- */
/* CD-Text blocks */
/*!
	@typedef 	DRCDTextBlockRef
	@abstract	A reference to DRCDTextBlock instances.
*/
typedef const struct __DRCDTextBlock*		DRCDTextBlockRef;

/*!
	@function	DRCDTextBlockGetTypeID
	@abstract	Returns the type identifier for all DRCDTextBlock instances.
	@result		A Core Foundation type identifier.
*/
extern CFTypeID
DRCDTextBlockGetTypeID(void)
AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@function	DRCDTextBlockCreate
	@abstract	Creates a CD-Text block with the provided contents.
	@param		language	A CFString describing an ISO 639 language code.  CD-Text allows
							the concept of an unknown language, which can be represented here
							by an empty string.
	@param		encoding	A CFStringEncoding value supported by the CD-Text format.
	@result		A new CD-Text block.
*/
extern DRCDTextBlockRef
DRCDTextBlockCreate(
	CFStringRef					language,
	CFStringEncoding			encoding)
AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@function	DRCDTextBlockGetProperties
	@abstract	Returns properties of the CD-Text block.
	@param		block		The CD-Text block to query. If this parameter is not a valid
							CD-Text block object reference, the behavior is undefined.
	@result		A CFDictionary object containing the properties 
				of the specified CD-Text block. The caller does not implicitly retain the reference,
				and is not responsible for releasing it.
*/
extern
CFDictionaryRef DRCDTextBlockGetProperties(
	DRCDTextBlockRef 			block)
AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@function	DRCDTextBlockSetProperties
	@abstract	Sets the properties of the CD-Text block.
	@param		block		The CD-Text block to modify.
	@param		properties	A CFDictionary object containing the CD-Text block 
							properties. If this parameter is not a valid dictionary object
							reference, the behavior is undefined.
*/
extern
void DRCDTextBlockSetProperties(
	DRCDTextBlockRef 			block,
	CFDictionaryRef				properties)
AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@function	DRCDTextBlockGetTrackDictionaries
	@abstract	Returns the array of track dictionaries for a given block.
	@param		block		The CD-Text block to query.
	@result		A CFArray object containing immutable dictionaries of CFString objects, 
				each of which contains CD-Text information.
	@discussion	Each item in the array is a dictionary, which in turn holds key-value encoded
				information about a track or disc.  Array index 0 holds information about the
				disc, index 1 holds information about track 1, index 2 holds information about
				track 2, and so on.  The caller does not implicitly retain the reference,
				and is not responsible for releasing it.
*/
extern CFArrayRef
DRCDTextBlockGetTrackDictionaries(
	DRCDTextBlockRef			block)
AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@function	DRCDTextBlockSetTrackDictionaries
	@abstract	Sets an array of track dictionaries for a given CD-Text block.
	@param		block		The CD-Text block to modify.
	@param		array		A CFArray object containing immutable dictionaries of 
							CFString objects, each of which contains CD-Text information.
	@discussion	Each item in the array is a dictionary, which in turn holds key-value encoded
				information about the track or disc.  Array index 0 holds information about the
				disc, index 1 holds information about track 1, index 2 holds information about
				track 2, and so on.
				
				The incoming strings are automatically modified to conform to the character
				set specified in the language block. Calling the DRCDTextCopyTrackArray()
				function immediately after DRCDTextSetTrackArray() returns the modified values, which
				may not be the same as the ones you passed in but correspond to what
				will actually be used.
*/
extern
void DRCDTextBlockSetTrackDictionaries(
	DRCDTextBlockRef			block,
	CFArrayRef					array)
AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@function	DRCDTextBlockGetValue
	@abstract	Returns one specific value for a track.
	@param		block		The CD-Text block to query.
	@param		trackIndex	The Track index, in the range 0-99, to query. If this value is greater than the number
							of tracks in the language block, the function returns NULL.
	@param		key			The specific key to look for.
	@discussion	This function looks up the value for the specified track index and key, and returns the
				value.  The returned value will be a CFString, CFData, or CFNumber object,
				or will be NULL if no key was found.  The caller does not implicitly retain the
				reference, and is not responsible for releasing it.
	@result		A Core Foundation type reference reference to a copy of the specified CD-Text block value.  
*/
extern
CFTypeRef DRCDTextBlockGetValue(
	DRCDTextBlockRef			block,
	CFIndex						trackIndex,
	CFStringRef					key)
AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@function	DRCDTextBlockSetValue
	@abstract	Sets one specific value for a track.
	@param		block		The CD-Text block to modify.
	@param		trackIndex	The track index, in the range 0-99, to modify. If this value is greater than the number
							of tracks in the language block, the function creates new entries in
							the track array as needed.
	@param		key			A key indicating the value to set.
	@param		value		The new textual value.
	@discussion	The CD-Text value may be a CFString, CFData, or CFNumber object, but should correspond
				to the type defined in the description of the key.
				
				If the incoming value is a string, it is automatically modified to conform to
				the character set of the language block. Calling the  DRCDTextCopyValue() function
				immediately after DRCDTextSetValue() returns the modified value, which
				may not be the same as the one you passed in but corresponds to
				what will actually be used.
				
				Setting a value to NULL removes the key from the specified track dictionary.
*/
extern
void DRCDTextBlockSetValue(
	DRCDTextBlockRef			block,
	CFIndex						trackIndex,
	CFStringRef					key,
	CFTypeRef					value)
AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@function	DRCDTextBlockFlatten
	@abstract	Flattens the CD-Text block to determine whether any information will be truncated.
	@param		block		The CD-Text block to flatten.
	@discussion	When burning your CD-Text information to a CD, Disc Recording will automatically
				truncate some of the information you've specified if it does not fit. 
				
				The size limit for CD-Text is approximately 3K per block.  This limit
				is approximate because of overhead and because duplicate strings can sometimes be 
				combined.  The only way to determine the final byte size of a CD-Text block is to 
				ask Disc Recording to flatten it.  You can then determine whether 
				truncation will be needed.
				
				Disc Recording's truncation preserves the most important information and provides 
				the simplest user experience.  If you do not wish to use Disc Recording's automatic 
				truncation, it is your responsibility to ensure that you provide CD-Text block 
				content that fits.
				
				Following is a simple algorithm to avoid having your CD-Text data truncated:
				<ol>
				<li>Call DRCDTextBlockFlatten.
				<li>If the result is 0, no truncation is necessary. Stop.
				<li>Otherwise, truncation will occur -- edit or remove some data.
				<li>Repeat.
				</ol>
				
	@result		The number of bytes that will be truncated from the CD-Text block.  If this
				function returns 0, no truncation will occur.
*/
extern
UInt32 DRCDTextBlockFlatten(
	DRCDTextBlockRef			block)
AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;



/* ------------------------------------------------------------------------------------ */
/*	CD-Text block properties.															*/

/* Required properties.  These are automatically set in the block upon creation. */
/*!
	@const		kDRCDTextLanguageKey
	@discussion	This is a required property key for a CD-Text block.  Its value is a
				reference to a CFString object containing the ISO 639 language code
				describing the language for the text of the block.  CD-Text allows the
				concept of an unknown language, which is represented here by an empty
				string.
				
				You can change a block's language after creating the block.
*/
extern const CFStringRef kDRCDTextLanguageKey								AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const		kDRCDTextCharacterCodeKey
	@discussion	This is a required property key for a CD-Text block.  Its value 
				is a reference to a CFNumber object containing the Red Book character set value
				for the text of the block.
				
				The value is not a CFStringEncoding or an NSStringEncoding data type and should 
				not be used as such.
				
				This property should remain constant once a block is created.  If you change
				it after creating a block, the results are undefined.
*/
extern const CFStringRef kDRCDTextCharacterCodeKey							AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const		kDRCDTextCFStringEncodingKey
	@discussion	This is a required property key for a CD-Text block.  Its value
				is a reference to a CFNumber object containing the CFStringEncoding value for the 
				text of the block.
				
				This property should remain constant once a block is created.   If you change
				it after creating a block, the results are undefined.
*/
extern const CFStringRef kDRCDTextCFStringEncodingKey						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Optional properties.  These can be set by your application. */
/*!
	@const		kDRCDTextCopyrightAssertedForSpecialMessagesKey
	@discussion	This is an optional property key for a CD-Text block.  Its value
				is a reference to a CFBoolean object that indicates whether copyright is asserted on the
				block text associated with the kDRCDTextSpecialMessageKey key.
				
				If this value is not specified, no copyright is asserted for the text.
*/
extern const CFStringRef kDRCDTextCopyrightAssertedForSpecialMessagesKey	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const		kDRCDTextCopyrightAssertedForNamesKey
	@discussion	This is an optional property key for a CD-Text block.  Its value
				is a reference to a CFBoolean object that indicates whether copyright is asserted on the
				names in the block, which include the values associated with the kDRCDTextPerformerKey, 
				kDRCDTextSongwriterKey, kDRCDTextComposerKey, and kDRCDTextArrangerKey keys.
				
				If this value is not specified, no copyright is asserted for these items.
*/
extern const CFStringRef kDRCDTextCopyrightAssertedForNamesKey				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const		kDRCDTextCopyrightAssertedForTitlesKey
	@discussion	This is an optional property key for a CD-Text block.  Its value
				is a reference to a CFBoolean object that indicates whether copyright is asserted on the
				disc or track title associated with the kDRCDTextTitleKey key.
				
				If this value is not specified, no copyright is asserted for this text.
*/
extern const CFStringRef kDRCDTextCopyrightAssertedForTitlesKey				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* ------------------------------------------------------------------------------------ */
/*	Keys for CD-Text track dictionaries. */
/*!
	@const		kDRCDTextTitleKey
	@discussion	A CD-Text block dictionary key whose value, a CFString object, contains
				the title for a track or, if for the disc info block, 
				for the disc as a whole.
*/
extern const CFStringRef kDRCDTextTitleKey					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const		kDRCDTextPerformerKey
	@discussion	A CD-Text block dictionary key whose value, a CFString object, contains
				the name of the performer for a track or, if for the disc info block, 
				for the disc as a whole.
*/
extern const CFStringRef kDRCDTextPerformerKey				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const		kDRCDTextSongwriterKey
	@discussion	A CD-Text block dictionary key whose value, a CFString object, contains
				the name of the songwriter for a track or, if for the disc info block, 
				for the disc as a whole.
*/
extern const CFStringRef kDRCDTextSongwriterKey				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const		kDRCDTextComposerKey
	@discussion	A CD-Text block dictionary key whose value, a CFString object, contains
				the name of the composer for a track or, if for the disc info block, 
				for the disc as a whole.
*/
extern const CFStringRef kDRCDTextComposerKey				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const		kDRCDTextArrangerKey
	@discussion	A CD-Text block dictionary key whose value, a CFString object, contains
				the name of the arranger for a track or, if for the disc info block, 
				for the disc as a whole.
*/
extern const CFStringRef kDRCDTextArrangerKey				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const		kDRCDTextSpecialMessageKey
	@discussion	A CD-Text block dictionary key whose value, a CFString object, contains
				a text message that may be displayed to the user by some players.
*/
extern const CFStringRef kDRCDTextSpecialMessageKey			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const		kDRCDTextDiscIdentKey
	@discussion	A CD-Text block dictionary key whose value, a CFString object, contains disc 
				identifying information such as the catalog number and name of the record 
				company, point of sale code, year, and so on.  Each item shall be separated by a slash ("/").
				
				In compliance with the CD-Text specifications, this string is always encoded using
				the kDRCDTextEncodingISOLatin1Modified encoding, regardless of the block's encoding.
				
				This key is valid only for the disc as a whole, namely for array index 0. It is ignored
				when set in the dictionaries for tracks.
*/
extern const CFStringRef kDRCDTextDiscIdentKey				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const		kDRCDTextGenreKey
	@discussion	A CD-Text block dictionary key whose value, a CFString object, contains
				the name of the genre for the disc as a whole.

				In compliance with the CD-Text specifications, this string is always encoded using
				the kDRCDTextEncodingISOLatin1Modified encoding, regardless of the block's encoding.
				
				This key is valid only for the disc as a whole, namely for array index 0. It is ignored
				when set in the dictionaries for tracks.
*/
extern const CFStringRef kDRCDTextGenreKey					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const		kDRCDTextGenreCodeKey
	@discussion	A CD-Text block dictionary key whose value, a CFNumber object, contains
				the numeric code of the genre for the disc as a whole as listed in 
				the CD-Text Genres enumeration.
				
				This key is valid only for the disc as a whole, namely for array index 0. It is ignored
				when set in the dictionaries for tracks.
*/
extern const CFStringRef kDRCDTextGenreCodeKey				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const		kDRCDTextClosedKey
	@discussion	A CD-Text block dictionary key whose value, a CFString object, contains  
				arbitrary disc information. The text format is arbitrary and is up to the content 
				provider.  This information is private and players should not display it to the user 
				of the disc.
				
				In compliance with the CD-Text specifications, this string is always encoded using
				the kDRCDTextEncodingISOLatin1Modified encoding, regardless of the block's encoding.
*/
extern const CFStringRef kDRCDTextClosedKey					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;				
				
/*!
	@const		kDRCDTextMCNISRCKey
	@discussion	A CD-Text block dictionary key whose value, a CFData object, contains either 
				13 bytes of Media Catalog Number (MCN, for the disc as a whole) or 12 bytes of 
				International Standard Recording Code (ISRC, for tracks).
				
				This information can also be specified in the burn and track properties.  CD-Text
				simply provides an alternative, possibly redundant, way to encode this information.
				If the MCN or ISRC data was specified in the properties for the burn or track, this
				value should be the same.  See the descriptions of kDRMediaCatalogNumberKey
				and kDRTrackISRCKey for more details on the precise format of the data.
*/
extern const CFStringRef kDRCDTextMCNISRCKey				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const		kDRCDTextTOCKey
	@discussion	A CD-Text block dictionary key whose value, a CFData object, contains
				table-of-contents information.
				
				This key is for output use only, when reading CD-Text from a disc.  
				It is ignored when specified in a burn.
*/
extern const CFStringRef kDRCDTextTOCKey					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const		kDRCDTextTOC2Key
	@discussion	A CD-Text block dictionary key whose value, a CFData object, contains
				additional table-of-contents information.
				
				This key is for output use only, when reading CD-Text from a disc.  
				It is ignored when specified in a burn.
*/
extern const CFStringRef kDRCDTextTOC2Key					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const		kDRCDTextSizeKey
	@discussion	A CD-Text block dictionary key whose value, a CFData object, contains
				information about the number of packs and languages associated with each block.
				
				This key is for output use only, when reading CD-Text from a disc.  
				It is ignored when specified in a burn.
*/
extern const CFStringRef kDRCDTextSizeKey					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


#ifdef __cplusplus
}
#endif

#endif /* _H_DRCoreBurn */
