/*
     File:       AudioUnitProperties.h
 
     Contains:   Property constants for AudioUnits
 
     Version:    Technology: Mac OS X
                 Release:    Mac OS X
 
     Copyright:  (c) 2001 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#ifndef __AudioUnitProperties
#define __AudioUnitProperties

#if !defined(__COREAUDIO_USE_FLAT_INCLUDES__)
	#include <AudioUnit/AUComponent.h>
	#include <CoreAudio/CoreAudioTypes.h>
	#include <CoreFoundation/CoreFoundation.h>
#else
	#include <AUComponent.h>
	#include <CoreAudioTypes.h>
	#include <CoreFoundation.h>
#endif

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Properties
// Apple reserves property values from 0 -> 63999
// Developers are free to use property IDs above this range at their own discretion

enum
{
// Applicable to all AudioUnits in general	(0 -> 999)
	kAudioUnitProperty_ClassInfo					= 0,
	kAudioUnitProperty_MakeConnection				= 1,
	kAudioUnitProperty_SampleRate					= 2,
	kAudioUnitProperty_ParameterList				= 3,
	kAudioUnitProperty_ParameterInfo				= 4,
	kAudioUnitProperty_FastDispatch					= 5,
	kAudioUnitProperty_CPULoad						= 6,
	//kAudioUnitProperty_SetInputCallback			= 7 -> deprecated - see AUNTComponent.h
	kAudioUnitProperty_StreamFormat					= 8,
	kAudioUnitProperty_SRCAlgorithm					= 9,
	kAudioUnitProperty_ReverbRoomType				= 10,
	kAudioUnitProperty_BusCount						= 11,
	kAudioUnitProperty_ElementCount					= kAudioUnitProperty_BusCount,
	kAudioUnitProperty_Latency						= 12,
	kAudioUnitProperty_SupportedNumChannels			= 13,
	kAudioUnitProperty_MaximumFramesPerSlice		= 14,
	kAudioUnitProperty_SetExternalBuffer			= 15,
	kAudioUnitProperty_ParameterValueStrings		= 16,
	kAudioUnitProperty_MIDIControlMapping			= 17,
	kAudioUnitProperty_GetUIComponentList			= 18,
	kAudioUnitProperty_AudioChannelLayout			= 19,  
	kAudioUnitProperty_TailTime						= 20,
	kAudioUnitProperty_BypassEffect					= 21,
	kAudioUnitProperty_LastRenderError				= 22,
	kAudioUnitProperty_SetRenderCallback			= 23,
	kAudioUnitProperty_FactoryPresets				= 24,
	kAudioUnitProperty_ContextName					= 25,
	kAudioUnitProperty_RenderQuality				= 26,
	kAudioUnitProperty_HostCallbacks				= 27,
	kAudioUnitProperty_CurrentPreset				= 28,
	kAudioUnitProperty_InPlaceProcessing			= 29,
	kAudioUnitProperty_ElementName					= 30,
	kAudioUnitProperty_CocoaUI						= 31,
	kAudioUnitProperty_SupportedChannelLayoutTags	= 32,
	kAudioUnitProperty_ParameterValueName			= 33,
	kAudioUnitProperty_ParameterIDName				= 34,
	kAudioUnitProperty_ParameterClumpName			= 35,
	kAudioUnitProperty_PresentPreset				= 36,
	kAudioUnitProperty_UsesInternalReverb			= 1005,
	kAudioUnitProperty_OfflineRender				= 37,
	kAudioUnitProperty_ParameterStringFromValue		= kAudioUnitProperty_ParameterValueName,
		// this is the new property to retrieve the actual parameter value from a parameter name
	kAudioUnitProperty_ParameterValueFromString		= 38,
	kAudioUnitProperty_IconLocation					= 39,
	
// Applicable to MusicDevices				(1000 -> 1999)
	kMusicDeviceProperty_InstrumentCount 			= 1000,
	kMusicDeviceProperty_InstrumentName				= 1001,
	kMusicDeviceProperty_GroupOutputBus				= 1002,
	kMusicDeviceProperty_SoundBankFSSpec			= 1003,
	kMusicDeviceProperty_InstrumentNumber 			= 1004,
	kMusicDeviceProperty_UsesInternalReverb			= kAudioUnitProperty_UsesInternalReverb,
	kMusicDeviceProperty_MIDIXMLNames				= 1006,
	kMusicDeviceProperty_BankName					= 1007,
	kMusicDeviceProperty_SoundBankData				= 1008,
	kMusicDeviceProperty_PartGroup					= 1010,
	kMusicDeviceProperty_StreamFromDisk				= 1011,
	
	
// Applicable to "output" AudioUnits		(2000 -> 2999)
	kAudioOutputUnitProperty_CurrentDevice			= 2000,
	kAudioOutputUnitProperty_IsRunning				= 2001,
	kAudioOutputUnitProperty_ChannelMap				= 2002, //this will also work with AUConverter
	kAudioOutputUnitProperty_EnableIO				= 2003,
	kAudioOutputUnitProperty_StartTime				= 2004,
	kAudioOutputUnitProperty_SetInputCallback		= 2005,
	kAudioOutputUnitProperty_HasIO					= 2006,

// miscellaneous AudioUnit - specific properties
	kAudioUnitProperty_SpatializationAlgorithm		= 3000,
	kAudioUnitProperty_SpeakerConfiguration			= 3001,
	kAudioUnitProperty_DopplerShift					= 3002,
	kAudioUnitProperty_3DMixerRenderingFlags		= 3003,
	kAudioUnitProperty_3DMixerDistanceAtten			= 3004,
	kAudioUnitProperty_MatrixLevels					= 3006,
	kAudioUnitProperty_MeteringMode					= 3007,
	kAudioUnitProperty_PannerMode					= 3008,
	kAudioUnitProperty_MatrixDimensions				= 3009,
	kAudioUnitProperty_3DMixerDistanceParams		= 3010,

// offline unit properties
	kAudioOfflineUnitProperty_InputSize				= 3020,
	kAudioOfflineUnitProperty_OutputSize			= 3021,
	kAudioUnitOfflineProperty_StartOffset			= 3022,
	kAudioUnitOfflineProperty_PreflightRequirements	= 3023,
	kAudioUnitOfflineProperty_PreflightName			= 3024,

// translation properties when migrating settings from other plugin formats to AU
	kAudioUnitMigrateProperty_FromPlugin			= 4000,
	kAudioUnitMigrateProperty_OldAutomation			= 4001
};

/*
	New Property Values:
	kAudioUnitProperty_ElementName
		Value is a 										CFStringRef
		The Host owns a reference to this property value (as with all other CF properties), and 
		should release the string retrieved or used when setting.
		
	kAudioUnitProperty_CocoaUI
		Value is a										struct AudioUnitCocoaViewInfo
		The Host can determine how big this structure is by querying the size of 
		the property (ie. How many alternate UI classes there are for the AU)
		Typically, most audio units will provide 1 UI class per unit

	kAudioUnitProperty_SupportedChannelLayoutTags		read-only	AudioChannelLayoutTags[kVariableLengthArray]
	 	Used with GetProperty to ascertain what an AudioUnit understands about
		laying out of channel orders. This will normally return one or more of the specified layout tags.
		
		When a specific set of layouts are returned, the client then uses the kAudioUnitProperty_AudioChannelLayout
		property (with one of those layout tags specified) to set the unit to use that layout. In this case
		the client (and the AudioUnit when reporting its AudioChannelLayout) is only expected to have set
		an AudioChannelLayout which only sets the layout tag as the valid field.
		
		Custom Channel Maps:
		Some audio units may return the tag:
			kAudioChannelLayoutTag_UseChannelDescriptions
		
		In this case, the host then can look at supported number of channels on that scope
		(using the kAudioUnitProperty_SupportedNumChannels), and supply an AudioChannelLayout with the 
		kAudioUnitProperty_AudioChannelLayout property to specify the layout, number of channels
		and location of each of those channels. This custom channel map MUST have a channel valence
		that is supported by the Audio Unit.
		
		The UseChannelBitmap field is NOT used within the context of the AudioUnit.
	
	kAudioUnitProperty_AudioChannelLayout				struct AudioChannelLayout read/write
		See above for a general description.

		The AudioChannelLayout property describes for a given scope/element the order of 
		channels within a given stream. This property should be used to set the format
		of that scope and element (as it describes not only the number of channels, but
		the layout of those channels). Using the _StreamFormat property is generally
		not sufficient in this case (as this only describes the number of channels, 
		but not either the ordering of channels, whether the rendering is for speakers
		or headphones (in the stereo case), and so forth). The 3DMixer is one such example
		of an AudioUnit that requires an ACM on its output bus.
		
		Provisional Support for Channel Layouts:
		This property (and some others) may be supported by an AudioUnit but may not
		have been set, and doesn't have a reasonable default value. In that case a
		call to AudioUnitGetProperty will return the following status:
			kAudioUnitErr_PropertyNotInUse
			
		For eg, imagine that you have an AUConverter unit that can convert between
		2 different AudioChannelLayout structures. However, the user has set up this
		unit just with calls to the StreamDescription.. ie, the ACM property has never
		been set. As there are several differenct ACM versions that can represent a
		stream with the same number of channels, there is:
			(1) No means for the AUConverter in this case to make a guess
			(2) The stream itself may just be a N channel stream and have no surround or
				speaker implications.
				
		Thus the need for this status code. The user can interpret this to mean that the 
		property would be valid if it were set, but currently it hasn't been, there is no
		reasonable default (or even need for it), so the unit cannot return a sensible 
		value for that property.
		
		For an AudioUnit where the channel layout is not required (but is optional), the
		user can call AudioUnitSetProperty with this propertyID and a value of NULL
		(size of 0) to clear that setting. 
			-	If this call is successful, the unit would
		then return kAudioUnitErr_PropertyNotInUse in a consequent attempt to get this
		property value, until it is set with a valid value again.
			-	If this call is unsuccessful, a typical result code is 
		kAudioUnitErr_InvalidPropertyValue - that result can be taken to mean that
		the property value cannot be removed
		
		On those AudioUnits that require a channel layout (which is the typical case 
		for an effect unit, for the output of the 3DMixer for example), this "clearing"
		call will fail (invalid property value).

	kAudioOutputUnitProperty_EnableIO				UInt32 read/write
		scope output, element 0 = output
		scope input, element 1 = input
		output units default to output-only; may disable output or enable input, providing
		that the underlying device supports it, with this property. 0=disabled, 1=enabled
		using I/O proc.

	kAudioOutputUnitProperty_HasIO					UInt32 read-only
		scope output, element 0 = output
		scope input, element 1 = input
		see kAudioOutputUnitProperty_EnableIO
		property value is 1 if input or output is enabled on the specified element.
	
	kAudioOutputUnitProperty_StartTime				AudioOutputUnitStartAtTimeParams, write-only
		when this property is set on an output unit, it will cause the next Start request
		(but no subsequent Starts) to use AudioDeviceStartAtTime, using the specified timestamp,
		passing false for inRequestedStartTimeIsInput.
	
	kAudioOutputUnitProperty_SetInputCallback		AURenderCallbackStruct, read/write
		when an output unit has been enabled for input, this callback can be used to provide
		a single callback to the client from the input I/O proc, in order to notify the
		client that input is available and may be obtained by calling AudioUnitRender.

	kAudioUnitProperty_ParameterValueName			AudioUnitParameterValueName read-only
		This property is used with parameters that are marked with the
		kAudioUnitParameterFlag_HasName parameter info flag. This indicates that some
		(or all) of the values represented by the parameter can and should be
		represented by a special display string.
		
		This is NOT to be confused with kAudioUnitProperty_ParameterValueStrings. That property
		is used with parameters that are indexed and is typically used for instance to build
		a menu item of choices for one of several parameter values.
		
		kAudioUnitProperty_ParameterValueName can have a continuous range, and merely states
		to the host that if it is displaying those parameter's values, they should request
		a name any time any value of the parameter is set when displaying that parameter.
		
		For instance (a trivial example), a unit may present a gain parameter in a dB scale,
		and wish to display its minimum value as "negative infinity". In this case, the AU
		will not return names for any parameter value greater than its minimum value - so the host
		will then just display the parameter value as is. For values less than or equal to the 
		minimum value, the AU will return a string for "negative infinity" which the host can
		use to display appropriately.
		
		A less trivial example might be a parameter that presents its values as seconds. However,
		in some situations this value should be better displayed in a SMPTE style of display:
			HH:MM:SS:FF
		In this case, the AU would return a name for any value of the parameter.
		
		The GetProperty call is used in the same scope and element as the inParamID 
		that is declared in the struct passed in to this property.
		
		If the *inValue member is NULL, then the AudioUnit should take the current value
		of the specified parameter. If the *inValue member is NOT NULL, then the AU should
		return the name used for the specified value.
		
		On exit, the outName may point to a CFStringRef (which if so must be released by the caller).
		If the parameter has no special name that should be applied to that parameter value,
		then outName will be NULL, and the host should display the parameter value as
		appropriate.
	
	kAudioUnitProperty_ParameterIDName						AudioUnitParameterNameInfo (read)
		An AudioUnit returns the full parameter name in the GetParameterInfo struct/property.
		In some display situations however, there may only be room for a few characters, and
		truncating this full name may give a less than optimal name for the user. Thus, 
		this property can be used to ask the AU whether it can supply a truncated name, with
		the host suggesting a length (number of characters). If the AU returns a longer
		name than the host requests, that name maybe truncated to the requested characters in display.
		The AU could return a shorter name than requeseted as well. The AU returns a CFString
		that should be released by the host. When using this property, the host asks for
		the name in the same scope and element as the AU publishes the parameter.
	
	kAudioUnitProperty_ParameterClumpName					AudioUnitParameterNameInfo (read)
		This works in a similar manner to the ParameterIDName property, except that the inID
		value is one of the clumpID's that are returned with the AU's ParameterInfo struct.
	
	kMusicDeviceProperty_PartGroup							AudioUnitElement (read/write)
		AudioUnitElement that is the groupID (The Group Scope's Element) the part is (or should be) 
		assigned to. The property is used in the Part Scope, where the element ID is the part
		that is being queried (or assigned). This property may in some cases be read only, it may
		in some cases only be settable if the AU is uninitialized, or it may be completely dynamic/
		These constraints are dependent on the AU's implmentation restrictions, though ideally
		this property should be dynamically assignable at any time. The affect of assigning a new
		group to a part is undefined (though typically it would be expected that all of the existing
		notes would be turned OFF before the re-assignment is made by the AU).
		
	kAudioUnitProperty_PresentPreset						AUPreset (read/write)
		This property replaces the deprecated CurrentPreset property, due to the ambiguity of
		ownership of the CFString of the preset name in the older CurrentPreset property. 
		With PresentPreset the client of the AU owns the CFString when it retrieves the
		preset with PresentPreset and is expected to release this (as with ALL properties 
		that retrieve a CF object from an AU)
	
*/


// these properties are superseded by the AudioUnitQuality settings
enum {
	kAudioUnitSRCAlgorithm_Polyphase			= 'poly',
	kAudioUnitSRCAlgorithm_MediumQuality		= 'csrc'
};

enum {
	kReverbRoomType_SmallRoom	= 0,
	kReverbRoomType_MediumRoom	= 1,
	kReverbRoomType_LargeRoom	= 2,
	kReverbRoomType_MediumHall	= 3,
	kReverbRoomType_LargeHall	= 4,
	kReverbRoomType_Plate		= 8
};

enum {
	kSpatializationAlgorithm_EqualPowerPanning 		= 0,
	kSpatializationAlgorithm_SphericalHead 			= 1,
	kSpatializationAlgorithm_HRTF			 		= 2,
	kSpatializationAlgorithm_SoundField		 		= 3,
	kSpatializationAlgorithm_VectorBasedPanning		= 4,
	kSpatializationAlgorithm_StereoPassThrough		= 5
};
	
	// These property values are deprecated in favour of the newer AudioChannelLayout
	// structure and its supporting property.
	// The Original kSpeakerConfiguration_5_1 was also incorrectly named...
	// That speaker configuration actually represents a 5 channel stream in the order of
	// L, R, SL, SR, C -> there is no LFE or .1 channel in that stream
enum {
	kSpeakerConfiguration_HeadPhones		 		= 0,
	kSpeakerConfiguration_Stereo			 		= 1,
	kSpeakerConfiguration_Quad			 			= 2,
	kSpeakerConfiguration_5_0						= 3,
	kSpeakerConfiguration_5_1				 		= kSpeakerConfiguration_5_0
};

enum {
	k3DMixerRenderingFlags_InterAuralDelay			= (1L << 0),
	k3DMixerRenderingFlags_DopplerShift				= (1L << 1),
	k3DMixerRenderingFlags_DistanceAttenuation		= (1L << 2),
	k3DMixerRenderingFlags_DistanceFilter			= (1L << 3),
	k3DMixerRenderingFlags_DistanceDiffusion		= (1L << 4)
};

	
enum {
	kRenderQuality_Max								= 0x7F,
	kRenderQuality_High								= 0x60,
	kRenderQuality_Medium							= 0x40,
	kRenderQuality_Low								= 0x20,
	kRenderQuality_Min								= 0
};

enum {
	kPannerMode_Normal								= 0,
	kPannerMode_FaderMode							= 1
};

enum {
	kOfflinePreflight_NotRequired 	= 0,
	kOfflinePreflight_Optional		= 1,
	kOfflinePreflight_Required		= 2
};

// Apple reserves usage of scope IDs from 0 to 1024 for system usage
enum {
	kAudioUnitScope_Global	= 0,
	kAudioUnitScope_Input	= 1,
	kAudioUnitScope_Output	= 2,
	kAudioUnitScope_Group	= 3,
	kAudioUnitScope_Part	= 4
};

typedef struct AudioUnitConnection {
	AudioUnit	sourceAudioUnit;
	UInt32		sourceOutputNumber;
	UInt32		destInputNumber;
} AudioUnitConnection;

typedef struct AURenderCallbackStruct {
	AURenderCallback			inputProc;
	void *						inputProcRefCon;
} AURenderCallbackStruct;
	
typedef struct AudioUnitExternalBuffer {
	Byte *		buffer;
	UInt32		size;
} AudioUnitExternalBuffer;

// if one of these channel valences is -1 and the other is positive:
// for eg: in == -1, out == 2
// This means the unit can handle any number of channels on input
// but provids 2 on output
// If in and out channels are different negative numbers, then
// the unit can handle any number of channels in and out:
// for eg: in == -1, out == -2
// If both of these valences are -1, then the unit can handle
// any number of channels in and out PROVIDED they are the same
// number of channels 
// for eg: in == -1, out == -1
// (this is the typical case for an effect unit, and unless the effect unit
// has channel restrictions, it won't publish this property just for the -1->-1 case
typedef struct AUChannelInfo {
	SInt16		inChannels;
	SInt16		outChannels;
} AUChannelInfo;

typedef struct AUPreset {
	SInt32		presetNumber;
	CFStringRef	presetName;
} AUPreset;


// These strings are used as keys in the AUPreset-"classInfo" dictionary
// The actual keys are CFStrings to use these keys you define the key as:
// static const CFStringRef kMyVersionString = CFSTR(kAUPresetVersionKey);
#define kAUPresetVersionKey 		"version"
#define kAUPresetTypeKey 			"type"
#define kAUPresetSubtypeKey 		"subtype"
#define kAUPresetManufacturerKey	"manufacturer"
#define kAUPresetDataKey			"data"
#define kAUPresetNameKey			"name"
#define kAUPresetRenderQualityKey	"render-quality"
#define kAUPresetCPULoadKey			"cpu-load"
#define kAUPresetElementNameKey		"element-name"
#define kAUPresetExternalFileRefs	"file-references"

// these are keys to use when a preset contains data from other plugin formats
#define kAUPresetVSTDataKey			"vstdata"
#define kAUPresetMASDataKey			"masdata"


// this key if present, distinguishes a global preset that is set on the global scope
// with a part-based preset that is set on the part scope. The value of this key is
// audio unit defined
#define kAUPresetPartKey			"part"



// Host Call Backs

// If the host is unable to provide the requested information
// then it can return the kAudioUnitErr_CannotDoInCurrentContext error code

// Any of these parameters when called by the AudioUnit can be NULL
// ie. the AU doesn't want to know about this. 
// (except for the HostUserData which must be supplied by the AU as given to it when the property was set)

typedef OSStatus (*HostCallback_GetBeatAndTempo) (void		*inHostUserData, 
											Float64			*outCurrentBeat, 
											Float64			*outCurrentTempo);

typedef OSStatus (*HostCallback_GetMusicalTimeLocation) (void     *inHostUserData, 
												UInt32            *outDeltaSampleOffsetToNextBeat,
												Float32           *outTimeSig_Numerator,
												UInt32            *outTimeSig_Denominator,
												Float64           *outCurrentMeasureDownBeat);

typedef OSStatus (*HostCallback_GetTransportState) (void 	*inHostUserData,
										Boolean 			*outIsPlaying,
										Boolean 			*outTransportStateChanged,
										Float64 			*outCurrentSampleInTimeLine,
										Boolean 			*outIsCycling,
										Float64 			*outCycleStartBeat,
										Float64 			*outCycleEndBeat);

typedef struct HostCallbackInfo {
	void *									hostUserData;
	HostCallback_GetBeatAndTempo			beatAndTempoProc;
    HostCallback_GetMusicalTimeLocation     musicalTimeLocationProc;
	HostCallback_GetTransportState			transportStateProc;	
} HostCallbackInfo;

// mCocoaAUViewBundleLocation - contains the location of the bundle which the host app can then use to locate the bundle
// mCocoaAUViewClass - contains the names of the classes that implements the required protocol for an AUView

typedef struct AudioUnitCocoaViewInfo {
	CFURLRef	mCocoaAUViewBundleLocation;
	CFStringRef	mCocoaAUViewClass[1];
} AudioUnitCocoaViewInfo;

// this is deprecated see AudioUnitParameterStringFromValue for equivalent struct, but with clearer field names
typedef struct AudioUnitParameterValueName {
	AudioUnitParameterID	inParamID;
	const Float32			*inValue;	// may be NULL if should translate current parameter value
	CFStringRef				outName;  	// see comments for kAudioUnitProperty_ParameterValueName
} AudioUnitParameterValueName;


		// used with kAudioUnitProperty_ParameterStringFromValue property
typedef struct AudioUnitParameterStringFromValue {
	AudioUnitParameterID	inParamID;
	const Float32			*inValue;	
	CFStringRef				outString;  	
} AudioUnitParameterStringFromValue;

		// used with kAudioUnitProperty_ParameterValueFromString property
typedef struct AudioUnitParameterValueFromString {
	AudioUnitParameterID	inParamID;
	CFStringRef				inString;
	Float32					outValue;
} AudioUnitParameterValueFromString;

// AU Developers should *not* use a clumpID of zero - this is a reerved value for system usage
enum {
	kAudioUnitClumpID_System = 0
};

// This is used with the AudioUnitParameterNameInfo.inDesiredLength to signify the full name
// of the paramter information (like its ClumpName, or a "shortened" parameter name, being requeseted
enum {
	kAudioUnitParameterName_Full = -1
};

typedef struct AudioUnitParameterNameInfo {
	UInt32					inID;
	SInt32					inDesiredLength;
	CFStringRef				outName;
} AudioUnitParameterIDName;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Parameters

// assume kAudioUnitParameterUnit_Generic if not found in this enum
enum
{
	kAudioUnitParameterUnit_Generic				= 0,	/* untyped value generally between 0.0 and 1.0 */
	kAudioUnitParameterUnit_Indexed				= 1,	/* takes an integer value (good for menu selections) */
	kAudioUnitParameterUnit_Boolean				= 2,	/* 0.0 means FALSE, non-zero means TRUE */
	kAudioUnitParameterUnit_Percent				= 3,	/* usually from 0 -> 100, sometimes -50 -> +50 */
	kAudioUnitParameterUnit_Seconds				= 4,	/* absolute or relative time */
	kAudioUnitParameterUnit_SampleFrames		= 5,	/* one sample frame equals (1.0/sampleRate) seconds */
	kAudioUnitParameterUnit_Phase				= 6,	/* -180 to 180 degrees */
	kAudioUnitParameterUnit_Rate				= 7,	/* rate multiplier, for playback speed, etc. (e.g. 2.0 == twice as fast) */
	kAudioUnitParameterUnit_Hertz				= 8,	/* absolute frequency/pitch in cycles/second */
	kAudioUnitParameterUnit_Cents				= 9,	/* unit of relative pitch */
	kAudioUnitParameterUnit_RelativeSemiTones	= 10,	/* useful for coarse detuning */
	kAudioUnitParameterUnit_MIDINoteNumber		= 11,	/* absolute pitch as defined in the MIDI spec (exact freq may depend on tuning table) */
	kAudioUnitParameterUnit_MIDIController		= 12,	/* a generic MIDI controller value from 0 -> 127 */
	kAudioUnitParameterUnit_Decibels			= 13,	/* logarithmic relative gain */
	kAudioUnitParameterUnit_LinearGain			= 14,	/* linear relative gain */
	kAudioUnitParameterUnit_Degrees				= 15,	/* -180 to 180 degrees, similar to phase but more general (good for 3D coord system) */
	kAudioUnitParameterUnit_EqualPowerCrossfade = 16,	/* 0 -> 100, crossfade mix two sources according to sqrt(x) and sqrt(1.0 - x) */
	kAudioUnitParameterUnit_MixerFaderCurve1	= 17,	/* 0.0 -> 1.0, pow(x, 3.0) -> linear gain to simulate a reasonable mixer channel fader response */
	kAudioUnitParameterUnit_Pan					= 18,	/* standard left to right mixer pan */
	kAudioUnitParameterUnit_Meters				= 19,	/* distance measured in meters */
	kAudioUnitParameterUnit_AbsoluteCents		= 20,	/* absolute frequency measurement : if f is freq in hertz then 	*/
                                                        /* absoluteCents = 1200 * log2(f / 440) + 6900					*/
	kAudioUnitParameterUnit_Octaves				= 21,	/* octaves in relative pitch where a value of 1 is equal to 1200 cents*/
	kAudioUnitParameterUnit_BPM					= 22,	/* beats per minute, ie tempo */
    kAudioUnitParameterUnit_Beats               = 23,	/* time relative to tempo, ie. 1.0 at 120 BPM would equal 1/2 a second */
	kAudioUnitParameterUnit_Milliseconds		= 24,	/* parameter is expressed in milliseconds */
	kAudioUnitParameterUnit_Ratio				= 25,	/* for compression, expansion ratio, etc. */
	
	kAudioUnitParameterUnit_CustomUnit			= 26	/* this is the parameter unit type for parameters that present a custom unit name */
};

typedef UInt32		AudioUnitParameterUnit;

// if the "unit" field contains a value not in the enum above, then assume kAudioUnitParameterUnit_Generic
typedef struct AudioUnitParameterInfo
{
	char 					name[52];			// UTF8 encoded C string, may be treated as 56 characters
												// if kAudioUnitParameterFlag_HasCFNameString not set
	CFStringRef				unitName;			// only valid if kAudioUnitParameterFlag_HasUnitName
	UInt32					clumpID;			// only valid if kAudioUnitParameterFlag_HasClump
	CFStringRef				cfNameString;		// only valid if kAudioUnitParameterFlag_HasCFNameString

	AudioUnitParameterUnit	unit;						
	Float32					minValue;			
	Float32					maxValue;			
	Float32					defaultValue;		
	UInt32					flags;				
} AudioUnitParameterInfo;

// flags for AudioUnitParameterInfo

// Due to some vagaries about the ways in which Parameter's CFNames have been described, it was
// necessary to add a flag: kAudioUnitParameterFlag_CFNameRelease
// In normal usage a parameter name is essentially a static object, but sometimes an AU will 
// generate parameter names dynamically.. As these are expected to be CFStrings, in that case
// the host should release those names when it is finished with them, but there was no way
// to communicate this distinction in behaviour.
// Thus, if an AU will (or could) generate a name dynamically, it should set this flag in the
// paramter's info.. The host should check for this flag, and if present, release the parameter
// name when it is finished with it.
enum
{
// -------------------------------
// THESE ARE DEPRECATED AS OF 10.2 - these will eventually be reused, so don't use them!
	kAudioUnitParameterFlag_Global		= (1L << 0),	//	parameter scope is global
	kAudioUnitParameterFlag_Input		= (1L << 1),	//	parameter scope is input
	kAudioUnitParameterFlag_Output		= (1L << 2),	//	parameter scope is output
	kAudioUnitParameterFlag_Group		= (1L << 3),	//	parameter scope is group

// THESE ARE THE VALID RANGES OF PARAMETER FLAGS
// -------------------------------
	kAudioUnitParameterFlag_CFNameRelease		= (1L << 4),

	// bit positions 18,17,16 are set aside for display scales. bit 19 is reserved.
	kAudioUnitParameterFlag_DisplayMask			= (7L << 16) | (1L << 22),
	kAudioUnitParameterFlag_DisplaySquareRoot	= (1L << 16),
	kAudioUnitParameterFlag_DisplaySquared		= (2L << 16),
	kAudioUnitParameterFlag_DisplayCubed		= (3L << 16),
	kAudioUnitParameterFlag_DisplayCubeRoot		= (4L << 16),
	kAudioUnitParameterFlag_DisplayExponential	= (5L << 16),


	kAudioUnitParameterFlag_HasClump	 		= (1L << 20),
	kAudioUnitParameterFlag_HasName		 		= (1L << 21),
	// this renames the existing parameter flag _HasName, to _ValuesHaveStrings to be clearer on its intended usage.
	kAudioUnitParameterFlag_ValuesHaveStrings	= kAudioUnitParameterFlag_HasName,
	
	// indicates that a graphical representation should use a  logarithmic scale
	kAudioUnitParameterFlag_DisplayLogarithmic 	= (1L << 22),		
	
	kAudioUnitParameterFlag_IsHighResolution 	= (1L << 23),
	kAudioUnitParameterFlag_NonRealTime 		= (1L << 24),
	kAudioUnitParameterFlag_CanRamp 			= (1L << 25),
	kAudioUnitParameterFlag_ExpertMode 			= (1L << 26),
	kAudioUnitParameterFlag_HasCFNameString 	= (1L << 27),
	kAudioUnitParameterFlag_IsGlobalMeta 		= (1L << 28),
	kAudioUnitParameterFlag_IsElementMeta		= (1L << 29),
	kAudioUnitParameterFlag_IsReadable			= (1L << 30),
	kAudioUnitParameterFlag_IsWritable			= (1L << 31)
};

#define GetAudioUnitParameterDisplayType(flags) \
	((flags) & kAudioUnitParameterFlag_DisplayMask)

#define AudioUnitDisplayTypeIsLogarithmic(flags) \
	(GetAudioUnitParameterDisplayType(flags) == kAudioUnitParameterFlag_DisplayLogarithmic)
	
#define AudioUnitDisplayTypeIsSquareRoot(flags) \
	(GetAudioUnitParameterDisplayType(flags) == kAudioUnitParameterFlag_DisplaySquareRoot)
	
#define AudioUnitDisplayTypeIsSquared(flags) \
	(GetAudioUnitParameterDisplayType(flags) == kAudioUnitParameterFlag_DisplaySquared)
	
#define AudioUnitDisplayTypeIsCubed(flags) \
	(GetAudioUnitParameterDisplayType(flags) == kAudioUnitParameterFlag_DisplayCubed)

#define AudioUnitDisplayTypeIsCubeRoot(flags) \
	(GetAudioUnitParameterDisplayType(flags) == kAudioUnitParameterFlag_DisplayCubeRoot)

#define AudioUnitDisplayTypeIsExponential(flags) \
	(GetAudioUnitParameterDisplayType(flags) == kAudioUnitParameterFlag_DisplayExponential)

#define SetAudioUnitParameterDisplayType(flags, displayType) \
	(((flags) & ~kAudioUnitParameterFlag_DisplayMask) | (displayType))


enum {
	kOtherPluginFormat_Undefined	= 0, //reserving this value for future use
	kOtherPluginFormat_kMAS			= 1,
	kOtherPluginFormat_kVST			= 2
};
/*
struct AudioClassDescription {
    OSType mType;
    OSType mSubType;
    OSType mManufacturer;
};
is defined in <CoreAudio/CoreAudioTypes.h>

How these fields are used varies for each format.
In general, 
	mType specifies a generic, plugin format defined descriptor, 
	mSubType is usually left to the manufacturer to use at their discretion
	mManufacturer is a registered code to identify all plugins from the same manufacturer
*/
typedef struct  AudioUnitOtherPluginDesc
{
	UInt32 						format; //kOtherPluginFormat_kMAS, etc
	AudioClassDescription		plugin;
} AudioUnitOtherPluginDesc;

typedef struct AudioUnitParameterValueTranslation 
{
	AudioUnitOtherPluginDesc	otherDesc;
	UInt32						otherParamID;
	Float32						otherValue;
	AudioUnitParameterID		auParamID;
	Float32						auValue;
} AudioUnitParameterValueTranslation;

// AU-MAS Specific Structs for the data contained in the "masdata" key of an AU Preset dictionary
typedef struct AudioUnitPresetMAS_SettingData
{
	UInt32 				isStockSetting; // zero or 1  i.e. "long bool"
	UInt32 				settingID;
	UInt32 				dataLen; //length of following data
	UInt8 				data[1];
} AudioUnitPresetMAS_SettingData;

typedef struct AudioUnitPresetMAS_Settings
{
	UInt32 							manufacturerID;
	UInt32 							effectID;
	UInt32 							variantID;
	UInt32 							settingsVersion;
	UInt32 							numberOfSettings;
	AudioUnitPresetMAS_SettingData 	settings[1];
} AudioUnitPresetMAS_Settings;

// AU-VST - the CFDataRef data contains VST chunk data with no additional information. 

// new for 10.2
typedef struct AudioUnitMIDIControlMapping
{
	UInt16					midiNRPN;
	UInt8					midiControl;
	UInt8					scope;
	AudioUnitElement		element;
	AudioUnitParameterID	parameter;
} AudioUnitMIDIControlMapping;

// new for 10.3
typedef struct AudioOutputUnitStartAtTimeParams {
	// see AudioDeviceStartAtTime
	AudioTimeStamp			mTimestamp;
	UInt32					mFlags;
} AudioOutputUnitStartAtTimeParams;

typedef struct MixerDistanceParams {
	Float32					mReferenceDistance;
	Float32					mMaxDistance;
	Float32					mMaxAttenuation;	// in decibels
} MixerDistanceParams;


#endif // __AudioUnitProperties
