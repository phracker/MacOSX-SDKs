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
	kAudioUnitProperty_MIDIControlMapping			= 17, // deprecated see ParameterMIDIMapping Properties
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
	kAudioUnitProperty_PresentationLatency			= 40,
	kAudioUnitProperty_AllParameterMIDIMappings		= 41,
	kAudioUnitProperty_AddParameterMIDIMapping		= 42,
	kAudioUnitProperty_RemoveParameterMIDIMapping   = 43,
	kAudioUnitProperty_HotMapParameterMIDIMapping   = 44,
	kAudioUnitProperty_DependentParameters			= 45,
	
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
	kMusicDeviceProperty_SoundBankFSRef				= 1012,
	
	
// Applicable to "output" AudioUnits		(2000 -> 2999)
	kAudioOutputUnitProperty_CurrentDevice			= 2000,
	kAudioOutputUnitProperty_IsRunning				= 2001,
	kAudioOutputUnitProperty_ChannelMap				= 2002, // this will also work with AUConverter
	kAudioOutputUnitProperty_EnableIO				= 2003,
	kAudioOutputUnitProperty_StartTime				= 2004,
	kAudioOutputUnitProperty_SetInputCallback		= 2005,
	kAudioOutputUnitProperty_HasIO					= 2006,
	kAudioOutputUnitProperty_StartTimestampsAtZero  = 2007, // this will also work with AUConverter

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
	kAudioUnitProperty_MeterClipping				= 3011, // matrix mixer returns an AudioUnitMeterClipping struct

// offline unit properties
	kAudioOfflineUnitProperty_InputSize				= 3020,
	kAudioOfflineUnitProperty_OutputSize			= 3021,
	kAudioUnitOfflineProperty_StartOffset			= 3022,
	kAudioUnitOfflineProperty_PreflightRequirements	= 3023,
	kAudioUnitOfflineProperty_PreflightName			= 3024,

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
	// For AUScheduledSoundPlayer:
	
	kAudioUnitProperty_ScheduleAudioSlice			= 3300,		// ScheduledAudioSlice
	kAudioUnitProperty_ScheduleStartTimeStamp		= 3301,		// AudioTimeStamp, with either
																// sample time or host time valid. Sample time
																// takes precedence, -1 means "now". Host time
																// of 0 means "now."
	kAudioUnitProperty_CurrentPlayTime				= 3302,		// AudioTimeStamp, relative to start time,
																// sample time of -1 if not yet started.

	// For AUAudioFilePlayer:
	
	kAudioUnitProperty_ScheduledFileIDs				= 3310,		// Array of AudioFileIDs
		// must set this property on scheduled file player for all files to be played
	kAudioUnitProperty_ScheduledFileRegion			= 3311,		// struct ScheduledAudioFileRegion
	kAudioUnitProperty_ScheduledFilePrime			= 3312,		// UInt32
		// the number of frames to read from disk before returning, or 0 to specify use of a default value
	kAudioUnitProperty_ScheduledFileBufferSizeFrames = 3313,	// UInt32
	kAudioUnitProperty_ScheduledFileNumberBuffers   = 3314,		// UInt32

	// For AUDeferredRenderer:
	
	kAudioUnitProperty_DeferredRendererPullSize		= 3320,		// UInt32
	kAudioUnitProperty_DeferredRendererExtraLatency	= 3321,		// UInt32
	kAudioUnitProperty_DeferredRendererWaitFrames   = 3322,		// UInt32

	// For AUNetReceive:
	kAUNetReceiveProperty_Hostname = 3511,
	kAUNetReceiveProperty_Password = 3512,
	
	// For AUNetSend:
	kAUNetSendProperty_PortNum = 3513,
	kAUNetSendProperty_TransmissionFormat = 3514,
	kAUNetSendProperty_TransmissionFormatIndex = 3515,
	kAUNetSendProperty_ServiceName = 3516,
	kAUNetSendProperty_Disconnect = 3517,
	kAUNetSendProperty_Password = 3518,
#endif


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
			
		For example, imagine that you have an AUConverter unit that can convert between
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
	
	kAudioOutputUnitProperty_StartTimestampsAtZero  UInt32, read/write, defaults to true
		Apple output units typically begin their stream of timestamps presented to their
		inputs at sample time 0. Some applications may wish to receive the HAL's timestamps
		directly instead. When this property is set to false, the output unit's sample times
		will be direct reflections of the HAL's -- except when a sample rate conversion
		makes this impossible.
	
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
		
	kAudioUnitProperty_PresentationLatency					(Input/Output Scope) Float64 (write only)
		This property is set by a host to describe to the AU the presentation latency of both
		any of its input and/or output audio data. 
		It describes this latency in seconds. A value of zero means either no latency
		or an unknown latency.
		
		This is a write only property because the host is telling the AU the latency of both the data it provides
		it for input and the latency from getting the data from the AU until it is presented.
		
		The property is should be set on each active input and output bus (Scope/Element pair). For example, an
		AU with multiple outputs will have the output data it produces processed by different AU's, etc before it
		is mixed and presented. Thus, in this case, each output element could have a different presentation latency.
		
		This should not be confused with the Latency property, where the AU describes to the host any processing latency
		it introduces between its input and its output.
		
		For input:
			Describes how long ago the audio given to an AU was acquired. For instance, when reading from 
			a file to the first AU, then its input presentation latency will be zero. When processing audio input from a 
			device, then this initial input latency will be the presentation latency of the device itself
			- , the device's safety offset and latency.
			
			The next AU's (connected to that first AU) input presentation latency will be the input presentation latency 
			of the first AU, plus the processing latency (as expressed by kAudioUnitProperty_Latency) of the first AU.
			
		For output:
			Describes how long before the output audio of an AU is to be presented. For instance, when writing
			to a file, then the last AU's output presentation latency will be zero. When the audio from that AU
			is to be played to an AudioDevice, then that initial presentation latency will be the latency of
			the device itself - which is the I/O buffer size, and the device's safety offset and latency
			
			The previous AU's (connected to this last AU) output presenation latency will be that initial presentation
			latency plus the processing latency (as expressed by kAudioUnitProperty_Latency) of the last AU.
			
		Thus, for a given AU anywhere within a mixing graph, the input and output presentation latencies describe
		to that AU how long from the moment of generation it will take for its input to arrive, and how long
		it will take for its output to be presented. 
		
		An example usage for this property is for an AU to provide accurate metering for its output, 
		where it is generating output that will be presented at some future time (as presented by the output 
		presentation latency time) to the user.
*/

/*
	Parameter To MIDI Mapping Properties
		These properties are used to:
			Describe a current set of mappings between MIDI messages and Parameter value setting
			Create a mapping between a parameter and a MIDI message through either:
				- explicitly adding (or removing) the mapping
				- telling the AU to hot-map the next MIDI message to a specified Parameter
			The same MIDI Message can map to one or more parameters
			
		In general usage, these properties only apply to AU's that implement the MIDI API
		AU Instruments (type=='aumu') and Music Effects (type == 'aumf')

		These properties are used in the Global scope. The scope and element members of the structure describe
		the scope and element of the parameter. In all usages, mScope, mElement and mParameterID must be
		correctly specified.

		
		* The AUParameterMIDIMapping Structure

		Command				mStatus			mData1			
		Note Off			0x8n			Note Num		
		Note On				0x9n			Note Num		
		Key Pressure		0xAn			Note Num		
		Control Change		0xBn			ControllerID	
		Patch Change		0xCn			Patch Num		
		Channel Pressure	DxDn			0 (Unused)		
		Pitch Bend			0xEn			0 (Unused)		
		
		(where n is 0-0xF to correspond to MIDI channels 1-16)
		
		Details:

		In general MIDI Commands can be mapped to either a specific channel as specified in the mStatus bit.
		If the kAUParameterMIDIMapping_AnyChannelFlag bit is set mStatus is a MIDI channel message, then the 
		MIDI channel number in the status byte is ignored; the mapping is from the specified MIDI message on ANY channel.
		
		For note commands (note on, note off, key pressure), the MIDI message can trigger either with just a specific
		note number, or any note number if the kAUParameterMIDIMapping_AnyNoteFlag bit is set. In these instances, the
		note number is used as the trigger value (for instance, a note message could be used to set the 
		cut off frequency of a filter).
		
		When the parameter mapping list changes through addition/replace, removal, the implementation should
		fire a notification on the kAudioUnitProperty_AllParameterMIDIMappings property. The host can then
		retrieve the full set of mappings for the AU
		
		When a hot mapping is made, the notification should just be delivered for the HotMap property. The host can
		retrieve the last current hot mapping made through getting the value of that property.
		
		The Properties:								
		
		kAudioUnitProperty_AllParameterMIDIMappings							array of AUParameterMIDIMapping (read/write)
			This property is used to both retreive and set the current mapping state between (some/many/all of) its parameters
			and MIDI messages. When set, it should replace any previous mapped settings the AU had.
		
			If this property is implemented by a non-MIDI capable AU (such as an 'aufx' type), then the property is
			read only, and recommends a suggested set of mappings for the host to perform. In this case, it is the 
			host's responsibility to map MIDI message to the AU parameters. As described previously, there are a set
			of default mappings (see AudioToolbox/AUMIDIController.h) that the host can recommend to the user 
			in this circumstance.
			
			This property's size will be very dynamic, depending on the number of mappings currently in affect, so the 
			caller should always get the size of the property first before retrieving it. The AU should return an error
			if the caller doesn't provide enough space to return all of the current mappings.
			
		kAudioUnitProperty_AddParameterMIDIMapping							array of AUParameterMIDIMapping (write only)
			This property is used to Add mappings to the existing set of mappings the AU possesses. It will replace
			an existing mapping for the scope/element/paramID (so the feature only allows one mapping for a given parameter).
		
		kAudioUnitProperty_RemoveParameterMIDIMapping						array of AUParameterMIDIMapping (write only)
			This property is used to remove the specified mappings from the AU. If a mapping is specified that does not
			currently exist in the AU, then it should just be ignored. The Scope/Element/ParameterID is used to find the
			mapping to remove.

		kAudioUnitProperty_HotMapParameterMIDIMapping								AUParameterMIDIMapping (read/write)
			This property is used in two ways, determined by the value supplied by the caller.
			(1) If a mapping struct is provided, then that struct provides *all* of the information that the AU should
			use to map the parameter, *except* for the MIDI message. The AU should then listen for the next MIDI message
			and associate that MIDI message with the supplied AUParameter mapping. When this MIDI message is received and
			the mapping made, the AU should also issue a notification on this property 
			(kAudioUnitProperty_HotMapParameterMIDIMapping) to indicate to the host that the mapping has been made. The host
			can then retrieve the mapping that was made by getting the value of this property.
			
			To avoid possible confusion, it is recommended that once the host has retrieved this mapping (if it is 
			presenting a UI to describe the mappings for example), that it then clears the mapping state as described next.
			
			Thus, the only time this property will return a valid value is when the AU has made a mapping. If the AU's mapping
			state has been cleared (or it has not been asked to make a mapping), then the AU should return 
			kAudioUnitErr_InvalidPropertyValue if the host tries to read this value.
			
			(2) If the value passed in is NULL, then if the AU had a parameter that it was in the process of mapping, it
			should disregard that (stop listening to the MIDI messages to create a mapping) and discard the partially 
			mapped struct. If the value is NULL and the AU is not in the process of mapping, the AU can ignore the request.
			
			At all times, the _AllMappings property will completely describe the current known state of the AU's mappings
			of MIDI messages to parameters.
		
		kAudioUnitProperty_DependentParameters								array of AUDependentParameter (read only)
		
			This property is used for parameters with the kAudioUnitParameterFlag_IsGlobalMeta 
			or kAudioUnitParameterFlag_IsElementMeta flags set. AU hosts (and the AudioUnitParameterListener
			mechanism) can interrogate this property to determine which parameters are dependent on a
			meta-parameter.
			
			For parameters marked with kAudioUnitParameterFlag_IsGlobalMeta, any non-global
			dependent parameters are assumed to be dependent in every element of their scope.
			
			For parameters marked with kAudioUnitParameterFlag_IsElementMeta, then its dependent
			parameters must all be the same scope, and are assumed to apply only within a single element,
			not to other instances of the same parameter in other elements.
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
	k3DMixerRenderingFlags_DistanceDiffusion		= (1L << 4),
	k3DMixerRenderingFlags_LinearDistanceAttenuation	= (1L << 5)
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

enum {
	kAUNetSendPresetFormat_PCMFloat32 = 0,		// 1411 kilobits per second per channel @ 44100KHz (kilo == 1000 not 1024)
	kAUNetSendPresetFormat_PCMInt24 = 1,		// 1058 kilobits per second per channel @ 44100KHz
	kAUNetSendPresetFormat_PCMInt16 = 2,		//  706 kilobits per second per channel @ 44100KHz
	kAUNetSendPresetFormat_Lossless24 = 3,		// ~650 kilobits per second per channel @ 44100KHz
	kAUNetSendPresetFormat_Lossless16 = 4,		// ~350 kilobits per second per channel @ 44100KHz
	kAUNetSendPresetFormat_ULaw = 5,			//  353 kilobits per second per channel @ 44100KHz
	kAUNetSendPresetFormat_IMA4 = 6,			//  176 kilobits per second per channel @ 44100KHz
	kAUNetSendPresetFormat_AAC_128kbpspc = 7,	//  128 kilobits per second per channel
	kAUNetSendPresetFormat_AAC_96kbpspc = 8,	//   96 kilobits per second per channel
	kAUNetSendPresetFormat_AAC_80kbpspc = 9,	//   80 kilobits per second per channel
	kAUNetSendPresetFormat_AAC_64kbpspc = 10,	//   64 kilobits per second per channel
	kAUNetSendPresetFormat_AAC_48kbpspc = 11,	//   48 kilobits per second per channel
	kAUNetSendPresetFormat_AAC_40kbpspc = 12,	//   40 kilobits per second per channel
	kAUNetSendPresetFormat_AAC_32kbpspc = 13,	//   32 kilobits per second per channel
	kAUNetSendNumPresetFormats = 14
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
// e.g.: in == -1, out == 2
// This means the unit can handle any number of channels on input
// but provids 2 on output
// If in and out channels are different negative numbers, then
// the unit can handle any number of channels in and out:
// e.g.: in == -1, out == -2
// If both of these valences are -1, then the unit can handle
// any number of channels in and out PROVIDED they are the same
// number of channels 
// e.g.: in == -1, out == -1
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
	char 					name[52];			// UTF8 encoded C string (originally). 
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

	kAudioUnitParameterFlag_MeterReadOnly		= (1L << 15),
	
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
	kOtherPluginFormat_kVST			= 2,
	kOtherPluginFormat_AU			= 3
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

// AU - AU - this allows manufacturers to deprecate older AU's and replace them with new ones. The data
// for the older AU is the aupreset CFDictionary that that AU generated.

// new for 10.2 - this usage is deprecated... see AUParameterMIDIMapping
typedef struct AudioUnitMIDIControlMapping
{
	UInt16					midiNRPN;
	UInt8					midiControl;
	UInt8					scope;
	AudioUnitElement		element;
	AudioUnitParameterID	parameter;
} AudioUnitMIDIControlMapping;

enum {
	kAUParameterMIDIMapping_AnyChannelFlag		= (1L << 0),
		// If this flag is set and mStatus is a MIDI channel message, then the MIDI channel number 
		// in the status byte is ignored; the mapping is from the specified MIDI message on ANY channel.

	kAUParameterMIDIMapping_AnyNoteFlag			= (1L << 1),
		// If this flag is set and mStatus is a Note On, Note Off, or Polyphonic Pressure message,
		// the message's note number is ignored; the mapping is from ANY note number.

	kAUParameterMIDIMapping_SubRange			= (1L << 2),
		// set this flag if the midi control should map only to a sub-range of the parameter's value
		// then specify that range in the mSubRangeMin and mSubRangeMax members

	kAUParameterMIDIMapping_Toggle				= (1L << 3),
		// this is only useful for boolean typed parameters. When set, it means that the parameter's
		// value should be toggled (if true, become false and vice versa) when the represented MIDI message
		// is received
	
	kAUParameterMIDIMapping_Bipolar				= (1L << 4),
		// this can be set to when mapping a MIDI Controller to indicate that the parameter (typically a boolean
		// style parameter) will only have its value changed to either the on or off state of a MIDI controller message
		// (0 < 64 is off, 64 < 127 is on) such as the sustain pedal. The seeting of the next flag
		// (kAUParameterMIDIMapping_Bipolar_On) determine whether the parameter is mapped to the on or off
		// state of the controller
	kAUParameterMIDIMapping_Bipolar_On			= (1L << 5)
		// only a valid flag if kAUParameterMIDIMapping_Bipolar is set
};

// The reserved fields here are being used to reserve space (as well as align to 64 bit size) for future use
// When/If these fields are used, the names of the fields will be changed to reflect their functionality
// so, apps should NOT refer to these reserved fields directly by name
typedef struct AUParameterMIDIMapping
{
	AudioUnitScope			mScope;
	AudioUnitElement		mElement;
	AudioUnitParameterID	mParameterID;
	UInt32					mFlags;
	Float32					mSubRangeMin;
	Float32					mSubRangeMax;
	UInt8					mStatus;
	UInt8					mData1;
	UInt8					reserved1; // MUST be set to zero
	UInt8					reserved2; // MUST be set to zero
	UInt32					reserved3; // MUST be set to zero
} AUParameterMIDIMapping;

typedef struct AUDependentParameter {
	AudioUnitScope			mScope;
	AudioUnitParameterID	mParameterID;
} AUDependentParameter;

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

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
// returned by kAudioUnitProperty_MeterClipping
typedef struct AudioUnitMeterClipping
{
	// the maximum value seen on the channel since the last time the property was retrieved
	Float32 peakValueSinceLastCall; 
	
	// true if there was an infinite value on this channel.
	Boolean sawInfinity;
	
	// true if there was a floating point Not-A-Number value on this channel.
	Boolean sawNotANumber;
} AudioUnitMeterClipping;
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
/*
	Using AUScheduledSoundPlayer
	----------------------------
	
	This AudioUnit provides a way for a client to schedule audio buffers for
	future playback, with sample-accurate timing.
	
	
	Elements and Formats
	
	This unit has one output element, and no input elements. The output's format
	should be a canonical AudioUnit stream format (native Float32,
	deinterleaved).


	Scheduling

	To schedule slices of audio for future playback, set the
	kAudioUnitProperty_ScheduleAudioSlice property, with a ScheduledAudioSlice
	structure as the property value. The slice's mTimeStamp.mSampleTime
	determines when the slice will be played. This sample number is relative to
	the unit's start time, which you must set using the
	kAudioUnitProperty_ScheduleStartTimeStamp property before playback will
	begin.

	You must retain, unmodified, the ScheduledAudioSlice structure, including
	its mBufferList and the buffers to which it points, until the slice has been
	completely played, or until you stop playback by uninitializing or resetting
	the unit. The format of the slice's buffer list must match the unit's output
	stream format.
	
	(The members other than mSampleTime and mFlags in mTimestamp are currently
	ignored.)
	
	
	Completion
	
	To receive a callback when the slice has been played, store a pointer to a
	callback function in mCompletionProc. This function will be called (from the
	unit's rendering thread) when the slice has been completely played -- or
	determined to be unplayable due to an error. As an alternative, you may also
	poll the slice's (mFlags & kScheduledAudioSliceFlag_Complete).

	Upon completion, you can test (mFlags &
	kScheduledAudioSliceFlag_BeganToRenderLate) to determine whether some
	portion of the slice was not played due to its having been scheduled too
	late relative to the current playback time.
	
	
	Start Time
	
	The unit will not play any slices following initialization or reset -- until
	its start time has been set. The start time establishes the beginning of a
	timeline: the timestamps of all slices in the schedule are relative to the
	start time.

	Set a start time by setting kAudioUnitProperty_ScheduleStartTimeStamp with
	an AudioTimeStamp structure. If the timestamp contains a valid sample time
	(timestamp.mFlags & kAudioTimeStampSampleTimeValid), then playback begins
	when the timestamp passed to AudioUnitRender reaches the specified sample
	time. If the specified sample time is -1, playback begins on the next render
	cycle.
	
	If the start timestamp does not contain a valid sample time, but does contain a
	valid host time (timestamp.mFlags & kAudioTimeStampHostTimeValid), then the
	specified host time is translated to the sample time at which playback will
	begin. A host time of 0 means "start on the next render cycle."
	
	kAudioUnitProperty_ScheduleStartTimeStamp may be queried to obtain the time
	at which playback has actually begun. If the start time has not yet been reached,
	the timestamp returned will be whatever the client last set.
	
	
	Current play time
	
	kAudioUnitProperty_CurrentPlayTime may be queried to determine the unit's current
	time offset from its start time (useful, for example, to monitor playback progress).
	
	
	Unscheduling events
	
	To clear the unit's play schedule, call AudioUnitReset. The completion proc
	(if any) for each slice in the schedule will called. Playback will not
	resume until a new start time has been set. This also happens when the unit
	is uninitialized.
*/
enum {  // bits in ScheduledAudioSlice.mFlags
	kScheduledAudioSliceFlag_Complete				= 1,		// set if the unit is done with this slice
	kScheduledAudioSliceFlag_BeganToRender			= 2,		// set if any portion of the buffer has been played
	kScheduledAudioSliceFlag_BeganToRenderLate		= 4			// set if any portion of the buffer was not played
																// because it was scheduled late
};

typedef struct ScheduledAudioSlice ScheduledAudioSlice;
typedef void (*ScheduledAudioSliceCompletionProc)(void *userData, 
				ScheduledAudioSlice *bufferList);
				
struct ScheduledAudioSlice {
	AudioTimeStamp			mTimeStamp;
	ScheduledAudioSliceCompletionProc  mCompletionProc;	// may be null
	void *					mCompletionProcUserData;
	UInt32					mFlags;
	UInt32					mReserved;		// must be 0
	void *					mReserved2;		// for internal use
	UInt32					mNumberFrames;  // must be consistent with byte count of mBufferList
	AudioBufferList *		mBufferList;	// must contain deinterleaved Float32
};



/*
	Using AUAudioFilePlayer
	-----------------------

	This AudioUnit lets you schedule regions of audio files for future playback,
	with sample-accurate timing.

	The unit is a subclass of AUScheduledSoundPlayer and inherits all of its
	behavior, in particular the kAudioUnitProperty_ScheduleStartTimeStamp and
	kAudioUnitProperty_CurrentPlayTime. Instead of scheduling slices (buffers)
	of audio to be played (via kAudioUnitProperty_ScheduleAudioSlice), however,
	you schedule regions of audio files to be played. The unit reads and
	converts audio file data into its own internal buffers. It performs disk I/O
	on a high-priority thread shared among all instances of this unit within a
	process. Upon completion of a disk read, the unit internally schedules
	buffers for playback.


	Elements and Formats
	
	This unit has one output element, and no input elements. The output's format
	should be a canonical AudioUnit stream format (native Float32,
	deinterleaved). This format should have at least as many channels are in the
	audio file(s) to be played (otherwise channels will be dropped). During
	playback, all audio file data is converted to the unit's output format.
	

	Audio Files

	Before starting playback, you must first open all audio files to be played
	using the AudioFile API's (see AudioToolbox/AudioFile.h), and pass their
	AudioFileIDs to the unit by setting the kAudioUnitProperty_ScheduledFileIDs
	propery. This property must not be set during playback. The audio files must
	be kept open for the duration of playback.


	Scheduling Regions
	
	To schedule the playback of a region of an audio file, set the
	kAudioUnitProperty_ScheduledFileRegion property. This is a
	ScheduledAudioFileRegion structure. mTimeStamp.mSampleTime must be valid and
	is interpreted relative to the unit's start time -- the start time semantics
	(using kAudioUnitProperty_ScheduleStartTimeStamp) are identical to those of
	AUScheduledSoundPlayer. Unlike the ScheduledAudioSlice structures, the unit
	makes copies of ScheduledAudioFileRegions, so you may create them on the
	stack or otherwise reuse/dispose of them immediately after scheduling them.
	
	
	Priming
	
	You should set kAudioUnitProperty_ScheduledFilePrime after scheduling
	initial file regions to be played and before starting playback. This SetProperty call
	will begin reading the audio files and not return until the number of frames
	specifed by the property value have been read.
	
	
	Completion Callbacks
	
	A region's completion callback (mCompletionProc) is called when it has been
	completely scheduled for reading from disk. This callback is issued on the disk 
	read thread. If the region is not read from disk in time to play at its
	scheduled time, mCompletionProc is called a second time with an error code,
	also from the read thread. Note that the region passed to the callback will not
	be the same memory object as was passed by the client (since the unit copies the region).
	
	
	Start Time and Current Time
	
	These properties work identically as in AUScheduledSoundPlayer.
	
	
	Unscheduling regions
	
	To clear the unit's play schedule, call AudioUnitReset. The completion proc
	(if any) for each file region in the schedule will be called. Playback will
	not resume until a new start time has been set. This also happens when the
	unit is uninitialized.
	
	
	Customization
	
	The size and number of the player's disk read buffers default to "sensible"
	values, but may be configured with the properties:
		kAudioUnitProperty_ScheduledFileBufferSizeFrames
		kAudioUnitProperty_ScheduledFileNumberBuffers
	

	Bugs
	
	kAudioUnitProperty_ScheduledFileBufferSizeFrames
	kAudioUnitProperty_ScheduledFileNumberBuffers
		are currently unimplemented

	An option to make the unit not perform conversion from the audio file sample
	rate to the unit's output rate may be desirable.
*/

typedef struct ScheduledAudioFileRegion ScheduledAudioFileRegion;
typedef void (*ScheduledAudioFileRegionCompletionProc)(void *userData, 
				ScheduledAudioFileRegion *fileRegion, OSStatus result);

// defined in AudioToolbox/AudioFile.h:
//		typedef	struct OpaqueAudioFileID	*AudioFileID;
struct ScheduledAudioFileRegion {
	AudioTimeStamp			mTimeStamp;
	ScheduledAudioFileRegionCompletionProc  mCompletionProc;	// may be NULL
	void *					mCompletionProcUserData;
	struct OpaqueAudioFileID *mAudioFile;   // must be a valid and open AudioFileID
	UInt32					mLoopCount;		// 0 = don't loop
	SInt64					mStartFrame;	// offset into file
	UInt32					mFramesToPlay;	// number of frames to play
};

/*
	Using AUDeferredRenderer
	------------------------
	
	This unit has one input element and one output element. They must both have
	the same format, which must be canonical (Float32 deinterleaved) with the
	same number of channels.

	The unit creates a high-priority producer thread, on which calls to
	PullInput are performed, at a constant buffer size. This buffer size may be
	set with kAudioUnitProperty_DeferredRendererPullSize. The deferred renderer
	may be asked to render at different buffer sizes by a downstream unit or
	host application, but it always pulls upstream at its constant buffer size.
	The upstream pull size MUST be greater than or equal to the downstream pull
	size.

	The upstream producer thread runs in advance of calls to its Render
	function, with respect to the timestamps being passed to Render and
	PullInput. The difference between these timestamps is the unit's "latency",
	which is always at least one upstream pull buffer. The client may specify
	additional latency with the property
	kAudioUnitProperty_DeferredRendererExtraLatency, which is a number of sample
	frames.

	It is possible, at Render time, for the producer thread to have not yet
	finished rendering the necessary data. This generates an error. In order to
	give the producer a small amount of extra time to finish rendering, the
	client may set the unit's property
	kAudioUnitProperty_DeferredRendererWaitFrames. If this property is non-zero,
	then when Render finds that insufficient data has been produced, it will
	sleep for the amount of realtime corresponding to the number of wait frames.
	It will then check again to see if the required amount of data has been
	produced, and fail if it hasn't.
*/
#endif // MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4


#endif // __AudioUnitProperties
