/*
     File:       AudioToolbox/AudioFormat.h

     Contains:   API for finding things out about audio formats.

     Version:    Technology: Mac OS X
                 Release:    Mac OS X

     Copyright:  (c) 1985-2003 by Apple Computer, Inc., all rights reserved.

     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:

                     http://developer.apple.com/bugreporter/

*/
#if !defined(__AudioFormat_h__)
#define __AudioFormat_h__

//=============================================================================
//	Includes
//=============================================================================

//	System Includes
#include <CoreAudio/CoreAudioTypes.h>

#if defined(__cplusplus)
extern "C"
{
#endif

//=============================================================================
//	Types
//=============================================================================

typedef UInt32	AudioFormatPropertyID;

// Panning Modes
enum {
	kPanningMode_SoundField		 					= 3,
	kPanningMode_VectorBasedPanning					= 4
};

struct AudioPanningInfo {
		// the panning mode to be used for the pan
	UInt32				mPanningMode;
		// these coordinates are specified as in the AudioChannelDescription struct in CoreAudioTypes.h
	UInt32				mCoordinateFlags;
	Float32				mCoordinates[3];
	
		// mGainScale is used to multiply the panning values 
		// - in typical usage you are applying an existing volume
		// value in 0 -> 1 (where 1 is unity gain) to the panned values.
		// 1 would give you panning at unity
		// 0 would give you back a matrix of zeroes:-)
	Float32				mGainScale;
		// This is the channel map that is going to be used to determine channel volumes for this pan
	const AudioChannelLayout*	mOutputChannelMap;
};
typedef struct AudioPanningInfo AudioPanningInfo;

//=============================================================================
//	Properties - for various format structures.
//=============================================================================

enum
{

//=============================================================================
//	The following properties are concerned with the AudioStreamBasicDescription
//=============================================================================
	kAudioFormatProperty_FormatInfo						= 'fmti',
		//	Retrieves general information about a format. The specifier is a
		//	magic cookie, or NULL.
		//	On input, the property value is an AudioStreamBasicDescription which 
		//	should have at least the mFormatID filled out. On output it will be filled out
		//	as much as possible given the information known about the format 
		//	and the contents of the magic cookie (if any is given).
	
	kAudioFormatProperty_FormatIsVBR					= 'fvbr',
		//	Returns whether or not a format has a variable number of bytes per
		//	packet. The specifier is an AudioStreamBasicDescription describing
		//	the format to ask about. The value is a UInt32 where non-zero means
		//	the format is variable bytes pers packet.
	
	kAudioFormatProperty_FormatIsExternallyFramed		= 'fexf',
		//	Returns whether or not a format has a requires external framing information. 
		//  The specifier is an AudioStreamBasicDescription describing
		//	the format to ask about. The value is a UInt32 where non-zero means
		//	the format is externally framed. For instance, AAC is an externally 
		//  framed format, whereas MP3 isn't (for MP3 all the "framing" is in the 
		//  bit stream you pass to the codec).
	
	kAudioFormatProperty_EncodeFormatIDs				= 'acof',
		// No specifier needed. Must be set to NULL.
		// Returns an array of UInt32 format IDs for formats that are valid input formats 
		// for the converter. 
	
	kAudioFormatProperty_DecodeFormatIDs				= 'acif',
		// No specifier needed. Must be set to NULL.
		// Returns an array of UInt32 format IDs for formats that are valid output formats 
		// for the converter. 
	
	kAudioFormatProperty_AvailableEncodeBitRates		= 'aebr',
		//  The specifier is a UInt32 format ID.
		//  The property value is an array of AudioValueRange describing all available bit rates.
		
	kAudioFormatProperty_AvailableEncodeSampleRates		= 'aesr',
		//  The specifier is a UInt32 format ID.
		//  The property value is an array of AudioValueRange describing all available sample rates.
	
	kAudioFormatProperty_AvailableEncodeChannelLayoutTags = 'aecl',
		//  The specifier is an AudioStreamBasicDescription with at least the mFormatID 
		//  and mChannelsPerFrame fields set.
		//  The property value is an array of AudioChannelLayoutTags for the format and number of
		//  channels specified. If mChannelsPerFrame is zero, then all layouts supported by
		//  the format are returned.	
	
	kAudioFormatProperty_AvailableEncodeNumberChannels		= 'avnc',
		//  The specifier is an AudioStreamBasicDescription with at least the mFormatID field set.
		//  The property value is an array of UInt32 indicating the number of channels that can be encoded.
		//	A value of 0xFFFFFFFF indicates that any number of channels may be encoded. 
	
	kAudioFormatProperty_FormatName						= 'fnam',
		//	Returns a name for a given format. The specifier is an
		//	AudioStreamBasicDescription describing the format to ask about.
		//	The value is a CFStringRef. The caller is responsible for releasing the
		//	returned string. For some formats (eg, Linear PCM) you will get back a
		//	descriptive string (for eg. 16-bit, interleaved, etc...)
	
//=============================================================================
//	The following properties concern the AudioChannelLayout struct (speaker layouts)
//=============================================================================
	
	kAudioFormatProperty_ChannelLayoutForTag			= 'cmpl',
		//	Returns the channel descriptions for a standard channel layout.
		//	The specifier is a AudioChannelLayoutTag (the mChannelLayoutTag field 
		//  of the AudioChannelLayout struct) containing the layout constant. 
		//  The value is an AudioChannelLayout structure. In typical use a AudioChannelLayout
		//  can be valid with just a defined AudioChannelLayoutTag (ie, those layouts
		//  have predefined speaker locations and orderings).
		//  Returns an error if the tag is kAudioChannelLayoutTag_UseChannelBitmap 
		
	kAudioFormatProperty_TagForChannelLayout			= 'cmpt',
		// Returns an AudioChannelLayoutTag for a layout, if there is one.
		// The specifier is an AudioChannelLayout containing the layout description.
		// The value is an AudioChannelLayoutTag.
		// This can be used to reduce a layout specified by kAudioChannelLayoutTag_UseChannelDescriptions
		// or kAudioChannelLayoutTag_UseChannelBitmap to a known AudioChannelLayoutTag.

	kAudioFormatProperty_ChannelLayoutForBitmap			= 'cmpb',
		//	Returns the channel descriptions for a standard channel layout.
		//	The specifier is a UInt32 (the mChannelBitmap field 
		//  of the AudioChannelLayout struct) containing the layout bitmap. The value
		//	is an AudioChannelLayout structure. In some uses, an AudioChannelLayout can be 
		//  valid with the layoutTag set to "use bitmap" and the bitmap set appropriately.
		
	kAudioFormatProperty_BitmapForLayoutTag				= 'bmtg',
		// Returns a bitmap for an AudioChannelLayoutTag, if there is one.
		// The specifier is a AudioChannelLayoutTag  containing the layout tag.
		// The value is an UInt32 bitmap.
		// To go in the other direction, i.e. get a layout tag for a bitmap, 
		// use kAudioFormatProperty_TagForChannelLayout where your layout tag 
		// is kAudioChannelLayoutTag_UseChannelBitmap and the bitmap is filled in.

	kAudioFormatProperty_ChannelLayoutName				= 'lonm',
		//	Returns the a name for a particular channel layout. The specifier is
		//	an AudioChannelLayout containing the layout description. The value
		//	is a CFStringRef. The caller is responsible for releasing the
		//	returned string.
		
	kAudioFormatProperty_ChannelName					= 'cnam',
		//	Returns the name for a particular channel. The specifier is an
		//	AudioChannelDescription which has the mChannelLabel field set. The value
		//	is a CFStringRef. The caller is responsible for releasing the
		//	returned string.
	
	kAudioFormatProperty_MatrixMixMap					= 'mmap',
		//	Returns a matrix of scaling coefficients for moving audio from one channel map 
		//  to another in a standard way, if one is known. Otherwise an error is returned.
		//  The specifier is an array of two pointers to AudioChannelLayout structures. 
		//  The first points to the input layout, the second to the output layout.
        //  The value is a two dimensional array of Float32 where the first dimension (rows) 
        //  is the input channel and the second dimension (columns) is the output channel. 
        //  The Float32 at that point represents the attenuation or gain to apply.
	
    kAudioFormatProperty_ChannelMap						= 'chmp',
        //  Returns an array of SInt32 for reordering input channels.
		//  The specifier is an array of two pointers to AudioChannelLayout structures. 
		//  The first points to the input layout, the second to the output layout.
        //  The length of the output array is equal to the number of output channels.
            
	kAudioFormatProperty_NumberOfChannelsForLayout		= 'nchm',
		//  This is a general call for parsing a AudioChannelLayout provided as the specifier,
		//  to determine the number of valid channels that are represented. So, if the
		//  LayoutTag is specified, it returns the number of channels for that layout. If 
		//  the bitmap is specified, it returns the number of channels represented by that bitmap.
		//  If the layout tag is 'kAudioChannelLayoutTag_UseChannelDescriptions' it returns
		// 	the number of channel descriptions.
				
	kAudioFormatProperty_PanningMatrix					= 'panm'
		//  This call will pass in an AudioPanningInfo struct that specifies one of the
		//  kPanningMode_ constants for the panning algorithm and an AudioChannelLayout
		//	to describe the destination channel layout. As in kAudioFormatProperty_MatrixMixMap
		//	the return value is an array of Float32 values of the number of channels
		// 	represented by this specified channel layout. It is presumed that the source 
		//	being panned is mono (thus for a quad channel layout, 4 Float32 values are returned).
		//	The intention of this API is to provide support for panning operations that are
		//	strictly manipulating the respective volumes of the channels. Thus, more
		//	complex panners (like HRTF, distance filtering etc,) will not be represented
		// 	by this API. The resultant volume scalars can then be applied to a mixer
		//	or some other processing code to adapt the individual volumes of the mixed
		//	output.
		//	The volume values will typically be presented within a 0->1 range (where 1 is unity gain)
		//	For stereo formats, vector based panning is equivalent to the equal-power pan mode.
		
};

//=============================================================================
//	Routines
//=============================================================================

//-----------------------------------------------------------------------------
//	AudioFormatGetPropertyInfo
//
//	Retrieve information about the given property. The outPropertyDataSize
//	argument will return the size in bytes of the current value of the property.
//-----------------------------------------------------------------------------
	
extern OSStatus
AudioFormatGetPropertyInfo(	AudioFormatPropertyID	inPropertyID,
							UInt32					inSpecifierSize,
							void*					inSpecifier,
							UInt32*					outPropertyDataSize);

//-----------------------------------------------------------------------------
//	AudioFormatGetProperty
//
//	Retrieve the indicated property data. On input, ioPropertyDataSize has the
//	size of the data pointed to by outPropertyData. On output, it will contain
//	the amount written. If outPropertydata is NULL and ioPropertyDataSize is
//	not, the amount that would have been written will be reported.
//-----------------------------------------------------------------------------
	
extern OSStatus
AudioFormatGetProperty(	AudioFormatPropertyID	inPropertyID,
						UInt32					inSpecifierSize,
						void*					inSpecifier,
						UInt32*					ioPropertyDataSize,
						void*					outPropertyData);



//-----------------------------------------------------------------------------
//  AudioFormat Error Codes
//-----------------------------------------------------------------------------

enum {
        kAudioFormatUnspecifiedError						= 'what',
        kAudioFormatUnsupportedPropertyError 				= 'prop',
        kAudioFormatBadPropertySizeError 					= '!siz',
        kAudioFormatBadSpecifierSizeError 					= '!spc',
        kAudioFormatUnsupportedDataFormatError 				= 'fmt?',
        kAudioFormatUnknownFormatError 						= '!fmt'
};


#if defined(__cplusplus)
}
#endif

#endif
