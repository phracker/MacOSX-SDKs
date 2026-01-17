/*
     File:       DiscRecordingEngine/DRCDText.h
 
     Contains:   CD-Text APIs.
 
     Version:    Technology: Mac OS X
                 Release:    Mac OS X
 
     Copyright:  (c) 2002-2003 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

/*!
	@header
	@abstract		CD-Text object used in the DiscRecording APIs.

	@discussion		CD-Text is a system which allows the authors of an audio CD to encode textual
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
	
	Usually each block of CD-Text will be used to contain a different language (English,
	French, Japanese, Chinese, etc).  However, it's possible and permissible to have
	multiple blocks that each contain the same language.
	
	Each block encodes a complete set of information about the disc and its tracks.  This
	information is stored as an array of key-value dictionaries; one per track, with an
	additional dictionary for the disc/album itself (represented by array index 0).
	On a disc with n tracks, there will be n+1 dictionaries.
	
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
	
	Finally, the dictionaries for the individual tracks contain the textual
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
	
	For best compatibility with CD players, individual textual items in the
	dictionaries should be 160 bytes or smaller.  Since the currently supported
	character encodings are all single-byte encodings, this means a maximum of
	160 characters per entry.
*/

#import <Foundation/Foundation.h>
#import <CoreServices/CoreServices.h>
#import <DiscRecordingEngine/DRCoreCDText.h>

#include <AvailabilityMacros.h>



#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
@class DRCDTextBlock;
/* ----------------------------------- */
/* CD-Text encodings */
/*
	These values are special NSStringEncoding values.  Note that
	CD-Text does not support any arbitrary NSStringEncoding; instead,
	strings are limited to the encodings found here.
				
	There is no UTF-8 encoding value defined at the time of this writing.
*/

enum
{
	DRCDTextEncodingISOLatin1Modified			= NSISOLatin1StringEncoding,	/* ISO-Latin-1 ... not quite correct since 5 characters are different, to be changed when TEC adds the new encoding */
	DRCDTextEncodingASCII						= NSASCIIStringEncoding			/* 7-bit ASCII */
};


/* ----------------------------------- */
/* CD-Text genre codes */
/*
	These values are numeric codes for the genre, which is typically used by
	players to automatically assign equalizer settings.  If no genre code is
	specified, a value of DRCDTextGenreCodeUnknown is used.
	
	You can also specify a textual genre description which supplements
	the numeric genre code.  
*/
enum
{
	DRCDTextGenreCodeUnknown				= 0x0001,
	DRCDTextGenreCodeAdultContemporary		= 0x0002,
	DRCDTextGenreCodeAlternativeRock		= 0x0003,
	DRCDTextGenreCodeChildrens				= 0x0004,
	DRCDTextGenreCodeClassical				= 0x0005,
	DRCDTextGenreCodeContemporaryChristian	= 0x0006,
	DRCDTextGenreCodeCountry				= 0x0007,
	DRCDTextGenreCodeDance					= 0x0008,
	DRCDTextGenreCodeEasyListening			= 0x0009,
	DRCDTextGenreCodeErotic					= 0x000A,
	DRCDTextGenreCodeFolk					= 0x000B,
	DRCDTextGenreCodeGospel					= 0x000C,
	DRCDTextGenreCodeHipHop					= 0x000D,
	DRCDTextGenreCodeJazz					= 0x000E,
	DRCDTextGenreCodeLatin					= 0x000F,
	DRCDTextGenreCodeMusical				= 0x0010,
	DRCDTextGenreCodeNewAge					= 0x0011,
	DRCDTextGenreCodeOpera					= 0x0012,
	DRCDTextGenreCodeOperetta				= 0x0013,
	DRCDTextGenreCodePop					= 0x0014,
	DRCDTextGenreCodeRap					= 0x0015,
	DRCDTextGenreCodeReggae					= 0x0016,
	DRCDTextGenreCodeRock					= 0x0017,
	DRCDTextGenreCodeRhythmAndBlues			= 0x0018,
	DRCDTextGenreCodeSoundEffects			= 0x0019,
	DRCDTextGenreCodeSoundtrack				= 0x001A,
	DRCDTextGenreCodeSpokenWord				= 0x001B,
	DRCDTextGenreCodeWorldMusic				= 0x001C
};


/* ------------------------------------ */
/*!
	@class		DRCDTextBlock
	@abstract	Defines a CD-Text block, which holds the CD-Text strings
				for the entire disc in one language.
*/
@interface DRCDTextBlock : NSObject
{
@private
	void*	_ref;
}

/*!
	@method		arrayOfCDTextBlocksFromPacks:
	@abstract	Parses raw CD-Text data from a disc into DRCDTextBlock objects.
	@discussion	This method can be used to parse any data blob containing CD-Text PACKs,
				such as the result of +[DRDevice readCDText], or the data returned by the
				IOKit ioctl DKIOCCDREADTOC with format=5.
				
				The NSData should be sized to fit the exact number of PACKs.  Each PACK
				occupies 18 bytes, and the 4-byte header from a READ TOC command may
				optionally be included.
	@param		packs		NSData containing raw CD-Text PACKs.
	@result		An autoreleased array of DRCDTextBlock objects describing the information
				in the raw PACKs, or nil if the data could not be parsed.
*/
+ (NSArray*) arrayOfCDTextBlocksFromPacks:(NSData*)packs;

/*!
	@method		cdTextBlockWithLanguage:encoding:
	@abstract	Creates a CD-Text block.
	@param		lang		ISO 639 language code describing the language in which the strings
							are provided.  CD-Text allows the concept of an unknown language,
							which can be represented here by an empty string.
	@param		enc			Character encoding into which the strings should be converted.
	@result		An autoreleased DRCDTextBlock object.
*/
+ (DRCDTextBlock*) cdTextBlockWithLanguage:(NSString*)lang encoding:(NSStringEncoding)enc;

/*!
	@method		initWithLanguage:encoding:
	@abstract	Initializes an empty CD-Text block.
	@param		lang		ISO 639 language code describing the language which this block will hold.
							CD-Text allows the concept of an unknown language, which can be represented
							here by an empty string.
	@param		enc			Character encoding into which the strings in this block will be converted.
	@result		A DRCDTextBlock object.
*/
- (id) initWithLanguage:(NSString*)lang encoding:(NSStringEncoding)enc;

/*! 
   	@method 		properties
   	@abstract		Returns the properties dictionary of the CD-Text block.
    @result  		An NSDictionary containing the properties of the block.
*/
- (NSDictionary*) properties;

/*! 
   	@method 		setProperties:
   	@abstract		Sets the properties dictionary of the CD-Text block.
   	@param 			properties	NSDictionary of the properties to set.
*/
- (void) setProperties:(NSDictionary*)properties;

/*!
	@method		trackDictionaries
	@abstract	Returns a copy of the array of track dictionaries for the block.
	@result		An autoreleased NSArray of CFDictionaries of CFStrings, containing the CD-Text information.
	@discussion	Each item in the array is a dictionary, which in turn holds key-value encoded
				information about the track/disc.  Array index 0 holds information about the
				disc, index 1 holds information about track 1, index 2 holds information about
				track 2, etc.
*/
- (NSArray*) trackDictionaries;

/*!
	@method		setTrackDictionaries:
	@abstract	Sets the array of track dictionaries for the block.
	@param		tracks		An NSArray of NSDictionaries of NSStrings, containing the CD-Text information.
	@discussion	Each item in the array is a dictionary, which in turn holds key-value encoded
				information about the track/disc.  Array index 0 holds information about the
				disc, index 1 holds information about track 1, index 2 holds information about
				track 2, etc.
				
				Any incoming strings are automatically modified to conform to the character
				set specified in the language block. Calling -trackDictionaries immediately
				after -setTrackDictionaries: will provide the modified values.  These
				may not be the same as the ones you passed in, but instead correspond to
				what will actually be used.
*/
- (void) setTrackDictionaries:(NSArray*)tracks;

/*!
	@method		objectForKey:ofTrack:
	@abstract	Returns a single value from the block.
	@param		key			Key to get the value of.
	@param		trackIndex	One-based index of the track to query, or 0 to query the disc.
	@result		Autoreleased NSObject for the key, or nil if not present.
*/
- (id) objectForKey:(NSString*)key ofTrack:(unsigned)trackIndex;

/*!
	@method		setObject:forKey:ofTrack:
	@abstract	Changes a single string in the block.
	@param		value		Value - an NSString, NSData, or NSNumber as appropriate.
	@param		key			Key to assign.
	@param		trackIndex	One-based index of the track to modify, or 0 to modify the disc.
*/
- (void) setObject:(id)value forKey:(NSString*)key ofTrack:(unsigned)trackIndex;

/*!
	@method		flatten
	@abstract	Flattens the CD-Text block to determine whether any information will be truncated.
	@discussion	When burning your CD-Text information to a CD, DiscRecording will automatically
				truncate some of the information you've specified if it does not fit. 
				
				The size limit for CD-Text is approximately 3K of strings per block.  This limit
				is only approximate because some of this space is taken up as overhead, and
				duplicate strings can sometimes be combined.  The only way to tell for sure
				how big your CD-Text block is going to be is to ask DiscRecording to try
				flattening it.  You can use this function to determine whether truncation
				will be needed.
				
				Some clients will want to accept DiscRecording's truncation since it preserves
				the most important information and provides the simplest user experience.  If
				you do not wish to use DiscRecording's automatic truncation, it is your
				responsibility to make sure that you specify a CD-Text block that will fit.
				
				Following is a simple algorithm to avoid having your CD-Text data truncated:
				<ol>
				<li>Call -[myCDTextBlock flatten].
				<li>If the result is 0, no truncation is necessary. Stop.
				<li>Otherwise, truncation will occur -- edit or remove some data.
				<li>Repeat.
				</ol>
				
	@result		The number of bytes that will be truncated from the CD-Text block.  If this
				method returns 0, no truncation will occur.
*/
- (unsigned) flatten;

@end


/* ------------------------------------ */
/*!
	@category	DRCDTextBlock(PropertyConvenienceMethods)
	@abstract	Convenience methods for a DRCDTextBlock.
*/
@interface DRCDTextBlock (PropertyConvenienceMethods)

/*!
	@method		language
	@abstract	Returns the ISO 639 language code describing the language associated with the
				CD-Text block.  CD-Text allows the concept of an unknown language, which is
				represented here by an empty string.
	@result		A DRCDTextLanguage.
*/
- (NSString*) language;

/*!
	@method		encoding
	@abstract	Returns the string encoding associated with the CD-Text block.
	@result		A NSStringEncoding.
*/
- (NSStringEncoding) encoding;

@end
#endif



/* ------------------------------------------------------------------------------------ */
/*	CD-Text block properties.															*/

/* Required properties */
/*!
	@const		DRCDTextLanguageKey
	@discussion	Required property key for a CD-Text block.  The value for this property
				is an NSNumber, containing the numeric code for the language.  This
				value is the Red Book language code value for the text of the block.
				
				The language may be changed after the block is created.
*/
extern NSString* const DRCDTextLanguageKey					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const		DRCDTextCharacterCodeKey
	@discussion	Required property key for a CD-Text block.  The value for this property
				is an NSNumber, containing the Red Book character set value for the
				text of the block.  This value is <b>not</b> a CFStringEncoding or
				NSStringEncoding, and should not be used as such.
				
				This property should remain constant once the block is created. If this
				property is changed after the block is created, the results are undefined.
*/
extern NSString* const DRCDTextCharacterCodeKey				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const		DRCDTextNSStringEncodingKey
	@discussion	Required property key for a CD-Text block.  The value for this property
				is an NSNumber, containing the NSStringEncoding for the text of the block.
				
				This property should remain constant once the block is created.  If this
				property is changed after the block is created, the results are undefined.
*/
extern NSString* const DRCDTextNSStringEncodingKey			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Optional properties */
/*!
	@const		DRCDTextCopyrightAssertedForSpecialMessagesKey
	@discussion	Optional property key for a CD-Text block.  The value for this property
				is an NSNumber, containing a BOOL value indicating whether copyright
				is asserted on the messages in the block (@link DRCDTextSpecialMessageKey DRCDTextSpecialMessageKey @/link).
				
				If this value is not specified, no copyright is asserted for these items.
*/
extern NSString* const DRCDTextCopyrightAssertedForSpecialMessagesKey	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const		DRCDTextCopyrightAssertedForNamesKey
	@discussion	Optional property key for a CD-Text block.  The value for this property
				is an NSNumber, containing a BOOL value indicating whether copyright
				is asserted on the names in the block.  (@link DRCDTextPerformerKey DRCDTextPerformerKey @/link,
				@link DRCDTextSongwriterKey DRCDTextSongwriterKey @/link, @link DRCDTextComposerKey DRCDTextComposerKey @/link, @link DRCDTextArrangerKey DRCDTextArrangerKey @/link)
				
				If this value is not specified, no copyright is asserted for these items.
*/
extern NSString* const DRCDTextCopyrightAssertedForNamesKey				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const		DRCDTextCopyrightAssertedForTitlesKey
	@discussion	Optional property key for a CD-Text block.  The value for this property
				is an NSNumber, containing a BOOL value indicating whether copyright
				is asserted on the titles of the disc and tracks.  (@link DRCDTextTitleKey DRCDTextTitleKey @/link)
				
				If this value is not specified, no copyright is asserted for these items.
*/
extern NSString* const DRCDTextCopyrightAssertedForTitlesKey			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* ------------------------------------------------------------------------------------ */
/*	Keys for CD-Text track dictionaries. */
/*!
	@const		DRCDTextTitleKey
	@discussion	One of the keys for the track dictionaries in a CD-Text block.  The value for this
				key is an NSString, containing the track/disc title.
*/
extern NSString* const DRCDTextTitleKey						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const		DRCDTextPerformerKey
	@discussion	One of the keys for the track dictionaries in a CD-Text block.  The value for this
				key is an NSString, containing the track/disc performer.
*/
extern NSString* const DRCDTextPerformerKey					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const		DRCDTextSongwriterKey
	@discussion	One of the keys for the track dictionaries in a CD-Text block.  The value for this
				key is an NSString, containing the track/disc songwriter.
*/
extern NSString* const DRCDTextSongwriterKey				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const		DRCDTextComposerKey
	@discussion	One of the keys for the track dictionaries in a CD-Text block.  The value for this
				key is an NSString, containing the track/disc composer.
*/
extern NSString* const DRCDTextComposerKey					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const		DRCDTextArrangerKey
	@discussion	One of the keys for the track dictionaries in a CD-Text block.  The value for this
				key is an NSString, containing the track/disc arranger.
*/
extern NSString* const DRCDTextArrangerKey					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const		DRCDTextSpecialMessageKey
	@discussion	One of the keys for the track dictionaries in a CD-Text block.  The value for this
				key is an NSString, containing a text message which may be displayed to the
				user by some players.
*/
extern NSString* const DRCDTextSpecialMessageKey			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const		DRCDTextDiscIdentKey
	@discussion	One of the keys for the track dictionaries in a CD-Text block.  The value for this
				key is an NSString, containing disc ID information, such as the catalog number
				and name of the record company, point of sale code, year of sales, etc.  Each
				item shall be separated by a slash ("/").
				
				This key is only valid for the disc (array index 0) and is ignored
				when set in the dictionaries for tracks.
*/
extern NSString* const DRCDTextDiscIdentKey					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const		DRCDTextGenreKey
	@discussion	One of the keys for the track dictionaries in a CD-Text block.  The value for this
				key is an NSString, containing the description of the disc genre.
				
				This key is only valid for the disc (array index 0) and is ignored
				when set in the dictionaries for tracks.
*/
extern NSString* const DRCDTextGenreKey						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const		DRCDTextGenreCodeKey
	@discussion	One of the keys for the track dictionaries in a CD-Text block.  The value for this
				key is an NSNumber, containing the numeric code for the disc genre as
				enumerated above.
				
				This key is only valid for the disc (array index 0) and is ignored
				when set in the dictionaries for tracks.
*/
extern NSString* const DRCDTextGenreCodeKey					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const		DRCDTextClosedKey
	@discussion	One of the keys for the track dictionaries in a CD-Text block.  The value for this
				key is an NSString, containing disc information.  The format of this data is
				arbitrary and is up to the content provider.  This information is private and
				players should not display it to the user of the disc.
*/
extern NSString* const DRCDTextClosedKey					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;				
				
/*!
	@const		DRCDTextMCNISRCKey
	@discussion	One of the keys for the track dictionaries in a CD-Text block.  The value for this
				key is an NSData, containing either 13 bytes of MCN (for the disc) or 12 bytes
				of ISRC (for tracks).
				
				This information can also be specified in the burn and track properties.  CD-Text
				simply provides an alternative, possibly redundant way to encode this information.
				If the MCN or ISRC was specified in the properties for the burn or track, this
				value should be the same.  See the descriptions of @link //apple_ref/occ/data/DRMediaCatalogNumberKey DRMediaCatalogNumberKey @/link
				and @link //apple_ref/occ/data/DRTrackISRCKey DRTrackISRCKey @/link for more details on the precise format of the data.
*/
extern NSString* const DRCDTextMCNISRCKey					AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const		DRCDTextTOCKey
	@discussion	One of the keys for the track dictionaries in a CD-Text block.  The value for this
				key is an NSData, containing table-of-contents information.
				
				This key is provided for output purposes only, when reading CD-Text from an
				existing disc.  It is ignored when specified in a burn.
*/
extern NSString* const DRCDTextTOCKey						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const		DRCDTextTOC2Key
	@discussion	One of the keys for the track dictionaries in a CD-Text block.  The value for this
				key is an NSData, containing additional table-of-contents information.
				
				This key is provided for output purposes only, when reading CD-Text from an
				existing disc.  It is ignored when specified in a burn.
*/
extern NSString* const DRCDTextTOC2Key						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const		DRCDTextSizeKey
	@discussion	One of the keys for the track dictionaries in a CD-Text block.  The value for this
				key is an NSData, containing information about the number of packs and languages
				associated with each block.
				
				This key is provided for output purposes only, when reading CD-Text from an
				existing disc.  It is ignored when specified in a burn.
*/
extern NSString* const DRCDTextSizeKey						AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

