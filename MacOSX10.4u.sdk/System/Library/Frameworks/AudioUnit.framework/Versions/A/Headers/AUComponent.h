/*
	File:		AUComponent.h

	Contains:	AudioUnit Interfaces

	Version:	Mac OS X

	Copyright:	© 2002-2004 by Apple Computer, Inc., all rights reserved.

	Bugs?:		For bug reports, consult the following page on
				the World Wide Web:

					http://developer.apple.com/bugreporter/
*/

#ifndef __AUCOMPONENT__
#define __AUCOMPONENT__

#include <AvailabilityMacros.h>
#if !defined(__COREAUDIO_USE_FLAT_INCLUDES__)
	#include <CoreServices/CoreServices.h>
	#include <CoreAudio/CoreAudioTypes.h>
#else
	#include <Components.h>
	#include <CoreAudioTypes.h>
#endif

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if PRAGMA_IMPORT
#pragma import on
#endif

#if PRAGMA_STRUCT_ALIGN
	#pragma options align=mac68k
#elif PRAGMA_STRUCT_PACKPUSH
	#pragma pack(push, 2)
#elif PRAGMA_STRUCT_PACK
	#pragma pack(2)
#endif


//-----------------------------------------------------------------------------
//	An AudioUnit is a ComponentInstance.
//-----------------------------------------------------------------------------
typedef ComponentInstance				AudioUnit;


//-----------------------------------------------------------------------------
//	AudioUnit component types and subtypes
//-----------------------------------------------------------------------------

enum
{
	kAudioUnitType_Output					= 'auou',
	kAudioUnitSubType_HALOutput				= 'ahal',
	kAudioUnitSubType_DefaultOutput			= 'def ',
	kAudioUnitSubType_SystemOutput			= 'sys ',
	kAudioUnitSubType_GenericOutput			= 'genr',

	kAudioUnitType_MusicDevice				= 'aumu',
	kAudioUnitSubType_DLSSynth				= 'dls ',

	kAudioUnitType_MusicEffect				= 'aumf',

	kAudioUnitType_FormatConverter			= 'aufc',
	kAudioUnitSubType_AUConverter			= 'conv',
	kAudioUnitSubType_Varispeed				= 'vari',
	kAudioUnitSubType_DeferredRenderer		= 'defr',
	kAudioUnitSubType_TimePitch				= 'tmpt',
	kAudioUnitSubType_Splitter				= 'splt',
	kAudioUnitSubType_Merger				= 'merg',
	
	kAudioUnitType_Effect					= 'aufx',
	kAudioUnitSubType_Delay					= 'dely',
	kAudioUnitSubType_LowPassFilter			= 'lpas',
	kAudioUnitSubType_HighPassFilter		= 'hpas',
	kAudioUnitSubType_BandPassFilter		= 'bpas',
	kAudioUnitSubType_HighShelfFilter		= 'hshf',
	kAudioUnitSubType_LowShelfFilter		= 'lshf',
	kAudioUnitSubType_ParametricEQ			= 'pmeq',
	kAudioUnitSubType_GraphicEQ				= 'greq',
	kAudioUnitSubType_PeakLimiter			= 'lmtr',
	kAudioUnitSubType_DynamicsProcessor		= 'dcmp',
	kAudioUnitSubType_MultiBandCompressor	= 'mcmp',
	kAudioUnitSubType_MatrixReverb			= 'mrev',
	kAudioUnitSubType_SampleDelay			= 'sdly',
	kAudioUnitSubType_Pitch					= 'pitc',
	kAudioUnitSubType_AUFilter				= 'filt',
	kAudioUnitSubType_NetSend				= 'nsnd',
	
	kAudioUnitType_Mixer					= 'aumx',
	kAudioUnitSubType_StereoMixer			= 'smxr',
	kAudioUnitSubType_3DMixer				= '3dmx',
	kAudioUnitSubType_MatrixMixer			= 'mxmx',

	kAudioUnitType_Panner					= 'aupn',

	kAudioUnitType_OfflineEffect			= 'auol',

	kAudioUnitType_Generator				= 'augn',
	kAudioUnitSubType_ScheduledSoundPlayer	= 'sspl',
	kAudioUnitSubType_AudioFilePlayer		= 'afpl',
	kAudioUnitSubType_NetReceive			= 'nrcv',

	kAudioUnitManufacturer_Apple			= 'appl'
};

//-----------------------------------------------------------------------------
//	Render flags
//-----------------------------------------------------------------------------

enum
{
								/* these are obsolete, were never implemented: */
								/*	kAudioUnitRenderAction_Accumulate			= (1 << 0) */
								/*	kAudioUnitRenderAction_UseProvidedBuffer	= (1 << 1) */
	kAudioUnitRenderAction_PreRender		= (1 << 2),
	kAudioUnitRenderAction_PostRender		= (1 << 3),
	kAudioUnitRenderAction_OutputIsSilence	= (1 << 4),
		/* provides hint on return from Render(): if set the buffer contains all zeroes */
	kAudioOfflineUnitRenderAction_Preflight	= (1 << 5),
	kAudioOfflineUnitRenderAction_Render	= (1 << 6),
	kAudioOfflineUnitRenderAction_Complete	= (1 << 7)
};

typedef UInt32							AudioUnitRenderActionFlags;

//-----------------------------------------------------------------------------
//	Errors
//-----------------------------------------------------------------------------

enum
{
	kAudioUnitErr_InvalidProperty			= -10879,
	kAudioUnitErr_InvalidParameter			= -10878,
	kAudioUnitErr_InvalidElement			= -10877,
	kAudioUnitErr_NoConnection				= -10876,
	kAudioUnitErr_FailedInitialization		= -10875,
	kAudioUnitErr_TooManyFramesToProcess	= -10874,
	kAudioUnitErr_IllegalInstrument			= -10873,
	kAudioUnitErr_InstrumentTypeNotFound	= -10872,
	kAudioUnitErr_InvalidFile				= -10871,
	kAudioUnitErr_UnknownFileType			= -10870,
	kAudioUnitErr_FileNotSpecified			= -10869,
	kAudioUnitErr_FormatNotSupported		= -10868,
	kAudioUnitErr_Uninitialized				= -10867,
	kAudioUnitErr_InvalidScope				= -10866,
	kAudioUnitErr_PropertyNotWritable		= -10865,
	kAudioUnitErr_CannotDoInCurrentContext	= -10863,
		/*
			same error code but different calling context
			as kAUGraphErr_CannotDoInCurrentContext	
		*/
	kAudioUnitErr_InvalidPropertyValue		= -10851,
	kAudioUnitErr_PropertyNotInUse			= -10850,
	kAudioUnitErr_Initialized				= -10849,
		/* returned if the operation cannot be performed because the AU is initialized */
	kAudioUnitErr_InvalidOfflineRender		= -10848,
	kAudioUnitErr_Unauthorized				= -10847
};


//-----------------------------------------------------------------------------
//	Types specific to the AudioUnit API
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Properties, parameters, scopes, elements
//
//	NOTE:
//	A value of 0xFFFFFFFF should never be used for a real scope,
//	element, or parameter ID, as this value is reserved for use with the
//	AUParameterListener APIs to do wild card searches.
//
//	Apple reserves the range of 0-1023 for specifying scopes; any custom
//	scope values should lie outside of this range.
//-----------------------------------------------------------------------------

typedef UInt32							AudioUnitPropertyID;
typedef UInt32							AudioUnitParameterID;
typedef UInt32							AudioUnitScope;
typedef UInt32							AudioUnitElement;


//-----------------------------------------------------------------------------
//	AudioUnitParameterEvent
//-----------------------------------------------------------------------------
enum
{
	kParameterEvent_Immediate	= 1,
	kParameterEvent_Ramped		= 2
};

typedef UInt32							AUParameterEventType;

struct AudioUnitParameterEvent
{
	AudioUnitScope			scope;
	AudioUnitElement		element;
	AudioUnitParameterID	parameter;
	
	AUParameterEventType	eventType;
	
	union
	{
		struct
		{
			SInt32			startBufferOffset;
			UInt32			durationInFrames;
			Float32			startValue;
			Float32			endValue;
		}					ramp;
		
		struct
		{
			UInt32			bufferOffset;
			Float32			value;
		}					immediate;		

	}						eventValues;
};

typedef struct AudioUnitParameterEvent	AudioUnitParameterEvent;


//-----------------------------------------------------------------------------
//	These are actually not used in the AudioUnit framework, but are used by 
//	AudioUnit/AudioUnitCarbonView and AudioToolbox/AudioUnitUtilities.
//-----------------------------------------------------------------------------

struct AudioUnitParameter
{
	AudioUnit				mAudioUnit;
	AudioUnitParameterID	mParameterID;
	AudioUnitScope			mScope;
	AudioUnitElement		mElement;
};

typedef struct AudioUnitParameter	AudioUnitParameter;

struct AudioUnitProperty
{
	AudioUnit				mAudioUnit;
	AudioUnitPropertyID		mPropertyID;
	AudioUnitScope			mScope;
	AudioUnitElement		mElement;
};

typedef struct AudioUnitProperty	AudioUnitProperty;

//-----------------------------------------------------------------------------

typedef OSStatus
(*AURenderCallback)(	void *							inRefCon,
						AudioUnitRenderActionFlags *	ioActionFlags,
						const AudioTimeStamp *			inTimeStamp,
						UInt32							inBusNumber,
						UInt32							inNumberFrames,
						AudioBufferList *				ioData);

typedef void
(*AudioUnitPropertyListenerProc)(	void *				inRefCon,
									AudioUnit			ci,
									AudioUnitPropertyID	inID,
									AudioUnitScope		inScope,
									AudioUnitElement	inElement);

//=============================================================================
//	API
//=============================================================================

extern ComponentResult
AudioUnitInitialize(				AudioUnit				ci)						AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


extern ComponentResult
AudioUnitUninitialize(				AudioUnit				ci)						AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



extern ComponentResult
AudioUnitGetPropertyInfo(			AudioUnit				ci,
									AudioUnitPropertyID 	inID,
									AudioUnitScope			inScope,
									AudioUnitElement		inElement,
									UInt32 *				outDataSize,
									Boolean *				outWritable)			AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

//-----------------------------------------------------------------------------
//	AudioUnitGetProperty
//
//	outData may be NULL, to determine how much memory to allocate for
//	variable size properties. ioDataSize must be a pointer to a UInt32
//	value containing the size of the expected result. Upon return this
//	value will contain the real size copied.
//-----------------------------------------------------------------------------
extern ComponentResult
AudioUnitGetProperty(				AudioUnit				ci,
									AudioUnitPropertyID		inID,
									AudioUnitScope			inScope,
									AudioUnitElement		inElement,
									void *					outData,
									UInt32 *				ioDataSize)				AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


extern ComponentResult
AudioUnitSetProperty(				AudioUnit				ci,
									AudioUnitPropertyID		inID,
									AudioUnitScope			inScope,
									AudioUnitElement		inElement,
									const void *			inData,
									UInt32					inDataSize)				AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

extern ComponentResult
AudioUnitAddPropertyListener(		AudioUnit						ci,
									AudioUnitPropertyID				inID,
									AudioUnitPropertyListenerProc	inProc,
									void *							inProcRefCon)   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

extern ComponentResult
AudioUnitRemovePropertyListener(	AudioUnit						ci,
									AudioUnitPropertyID				inID,
									AudioUnitPropertyListenerProc	inProc)			AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



extern ComponentResult
AudioUnitAddRenderNotify(			AudioUnit				ci,
									AURenderCallback		inProc,
									void *					inProcRefCon)			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


extern ComponentResult
AudioUnitRemoveRenderNotify(		AudioUnit				ci,
									AURenderCallback		inProc,
									void *					inProcRefCon)			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

extern ComponentResult
AudioUnitGetParameter(				AudioUnit				ci,
									AudioUnitParameterID	inID,
									AudioUnitScope			inScope,
									AudioUnitElement		inElement,
									Float32 *				outValue)				AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



extern ComponentResult
AudioUnitSetParameter(				AudioUnit				ci,
									AudioUnitParameterID	inID,
									AudioUnitScope			inScope,
									AudioUnitElement		inElement,
									Float32					inValue,
									UInt32					inBufferOffsetInFrames) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


extern ComponentResult
AudioUnitScheduleParameters(		AudioUnit						ci,
									const AudioUnitParameterEvent *	inParameterEvent,
									UInt32							inNumParamEvents) AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



extern ComponentResult
AudioUnitRender(					AudioUnit						ci,
									AudioUnitRenderActionFlags *	ioActionFlags,
									const AudioTimeStamp *			inTimeStamp,
									UInt32							inOutputBusNumber,
									UInt32							inNumberFrames,
									AudioBufferList *				ioData)			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


extern ComponentResult
AudioUnitReset(						AudioUnit			ci,
									AudioUnitScope		inScope,
									AudioUnitElement	inElement)					AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


//-----------------------------------------------------------------------------
//	Selectors for component calls
//-----------------------------------------------------------------------------
enum
{
	kAudioUnitRange							= 0x0000,	// range of selectors for AudioUnits
	kAudioUnitInitializeSelect				= 0x0001,
	kAudioUnitUninitializeSelect			= 0x0002,
	kAudioUnitGetPropertyInfoSelect			= 0x0003,
	kAudioUnitGetPropertySelect				= 0x0004,
	kAudioUnitSetPropertySelect				= 0x0005,
	kAudioUnitAddPropertyListenerSelect		= 0x000A,
	kAudioUnitRemovePropertyListenerSelect	= 0x000B,
	kAudioUnitAddRenderNotifySelect			= 0x000F,
	kAudioUnitRemoveRenderNotifySelect		= 0x0010,
	kAudioUnitGetParameterSelect			= 0x0006,
	kAudioUnitSetParameterSelect			= 0x0007,
	kAudioUnitScheduleParametersSelect		= 0x0011,
	kAudioUnitRenderSelect					= 0x000E,
	kAudioUnitResetSelect					= 0x0009
};


//-----------------------------------------------------------------------------
//	Fast-dispatch function pointer types
//	
//	For functions where performance may be an issue, a client may use
//	the kAudioUnitProperty_FastDispatch property to get a function
//	pointer pointing directly to the AudioUnit's implementation, to
//	avoid the cost of dispatching through the Component Manager. (Note
//	that AudioUnits are not required to implement this, but should.)
//-----------------------------------------------------------------------------
typedef ComponentResult
(*AudioUnitGetParameterProc)(	void *					inComponentStorage,
								AudioUnitParameterID	inID,
								AudioUnitScope			inScope,
								AudioUnitElement		inElement,
								Float32 *				outValue);
								
typedef ComponentResult
(*AudioUnitSetParameterProc)(	void *					inComponentStorage,
								AudioUnitParameterID	inID,
								AudioUnitScope			inScope,
								AudioUnitElement		inElement,
								Float32					inValue,
								UInt32					inBufferOffsetInFrames);
								
typedef ComponentResult
(*AudioUnitRenderProc)(			void *							inComponentStorage,
								AudioUnitRenderActionFlags *	ioActionFlags,
								const AudioTimeStamp *			inTimeStamp,
								UInt32							inOutputBusNumber,
								UInt32							inNumberFrames,
								AudioBufferList *				ioData);

#if PRAGMA_STRUCT_ALIGN
	#pragma options align=reset
#elif PRAGMA_STRUCT_PACKPUSH
	#pragma pack(pop)
#elif PRAGMA_STRUCT_PACK
	#pragma pack()
#endif

#ifdef PRAGMA_IMPORT_OFF
#pragma import off
#elif PRAGMA_IMPORT
#pragma import reset
#endif

#ifdef __cplusplus
}
#endif

#endif /* __AUCOMPONENT__ */

