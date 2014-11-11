/**********************************************************************************************************************************
*
*   OpenAL cross platform audio library
*   Copyright (c) 2006, Apple Computer, Inc., Copyright (c) 2014, Apple Inc. All rights reserved.
*
*   Redistribution and use in source and binary forms, with or without modification, are permitted provided 
*   that the following conditions are met:
*
*   1.  Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 
*   2.  Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following 
*       disclaimer in the documentation and/or other materials provided with the distribution. 
*   3.  Neither the name of Apple Inc. ("Apple") nor the names of its contributors may be used to endorse or promote 
*       products derived from this software without specific prior written permission. 
*
*   THIS SOFTWARE IS PROVIDED BY APPLE AND ITS CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
*   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE OR ITS 
*   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED 
*   TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
*   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE 
*   USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
**********************************************************************************************************************************/

#ifndef __MAC_OSX_OAL_EXTENSIONS_H__
#define __MAC_OSX_OAL_EXTENSIONS_H__

#include <OpenAL/al.h>
#include <OpenAL/alc.h>

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/*	
	Convert Data When Loading.  
	Default false, currently applies only to monophonic sounds. Use with alEnable()/alDisable()
*/
	#define ALC_MAC_OSX_CONVERT_DATA_UPON_LOADING         	0xF001

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	ALC_EXT_MAC_OSX
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

typedef ALvoid (*alcMacOSXRenderingQualityProcPtr) (ALint value);
typedef ALvoid (*alMacOSXRenderChannelCountProcPtr) (ALint value);
typedef ALvoid (*alcMacOSXMixerMaxiumumBussesProcPtr) (ALint value);
typedef ALvoid (*alcMacOSXMixerOutputRateProcPtr) (ALdouble value);

typedef ALint (*alcMacOSXGetRenderingQualityProcPtr) ();
typedef ALint (*alMacOSXGetRenderChannelCountProcPtr) ();
typedef ALint (*alcMacOSXGetMixerMaxiumumBussesProcPtr) ();
typedef ALdouble (*alcMacOSXGetMixerOutputRateProcPtr) ();

/* Render Quality. Used with alcMacOSXRenderingQuality() */
	
	#define ALC_MAC_OSX_SPATIAL_RENDERING_QUALITY_HIGH      'rqhi'
	#define ALC_MAC_OSX_SPATIAL_RENDERING_QUALITY_LOW		'rdlo'

/*	
	Render Channels. Used with alMacOSXRenderChannelCount()
	Allows a user to force OpenAL to render to stereo, regardless of the audio hardware being used
*/
	#define ALC_MAC_OSX_RENDER_CHANNEL_COUNT_STEREO         'rcst'
	#define ALC_MAC_OSX_RENDER_CHANNEL_COUNT_MULTICHANNEL   'rcmc'


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 AL_EXT_SOURCE_SPATIALIZATION
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*
 Allows the rendering quality to be explicitly set on a source object, overriding the default
 render quality set via alcMacOSXRenderingQuality(). A subsequent call to alcMacOSXRenderingQuality()
 resets the render quality of all source objects.
 
 Uses the same render settings (defined above) as alcMacOSXRenderingQuality():
 
 ALC_MAC_OSX_SPATIAL_RENDERING_QUALITY_HIGH
 ALC_MAC_OSX_SPATIAL_RENDERING_QUALITY_LOW
 ALC_IPHONE_SPATIAL_RENDERING_QUALITY_HEADPHONES
 
 Retrieve functions via alcGetProcAddress() by passing in strings: alSourceRenderingQuality or alSourceGetRenderingQuality
 */

typedef ALvoid (*alSourceRenderingQualityProcPtr) (ALuint sid, ALint value);
typedef ALint (*alSourceGetRenderingQualityProcPtr) (ALuint sid);


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	AL_EXT_STATIC_BUFFER
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

typedef ALvoid	AL_APIENTRY	(*alBufferDataStaticProcPtr) (ALint bid, ALenum format, const ALvoid* data, ALsizei size, ALsizei freq);

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	AL_EXT_SOURCE_NOTIFICATIONS
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*
	Source Notifications

	Eliminates the need for continuous polling for source state by providing a
	mechanism for the application to receive source state change notifications.
	Upon receiving a notification, the application can retrieve the actual state
	corresponding to the notification ID for which the notification was sent.
*/

#define AL_QUEUE_HAS_LOOPED						0x9000

/*
	Notification Proc:	ALSourceNotificationProc
 
		sid		- source id
		notificationID	- id of state that has changed
		userData	- user data provided to alSourceAddNotification()
*/
	
typedef ALvoid (*alSourceNotificationProc)(ALuint sid, ALuint	notificationID, ALvoid*	userData);

/*
	API: alSourceAddNotification

		sid		- source id
		notificationID	- id of state for which caller wants to be notified of a change 					
		notifyProc	- notification proc
		userData	- ptr to applications user data, will be returned in the notification proc

		Returns AL_NO_ERROR if request is successful.

		Valid IDs:
			AL_SOURCE_STATE
			AL_BUFFERS_PROCESSED
			AL_QUEUE_HAS_LOOPED	- notification sent when a looping source has looped to it's start point
*/
typedef ALenum (*alSourceAddNotificationProcPtr) (ALuint sid, ALuint notificationID, alSourceNotificationProc notifyProc, ALvoid* userData);

/*
	API: alSourceRemoveStateNotification

		sid		- source id
		notificationID	- id of state for which caller wants to remove an existing notification 					
		notifyProc	- notification proc
		userData	- ptr to applications user data, will be returned in the notification proc
*/
typedef ALvoid (*alSourceRemoveNotificationProcPtr) (ALuint	sid, ALuint notificationID, alSourceNotificationProc notifyProc, ALvoid* userData);

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	ALC_EXT_ASA : Apple Spatial Audio Extension
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*
	Used with the ASA API calls: alcASAGetSource(), alcASASetSource(), alcASAGetListener(), alcASASetListener()
*/

typedef ALenum  (*alcASAGetSourceProcPtr) (ALuint property, ALuint source, ALvoid *data, ALuint* dataSize);
typedef ALenum  (*alcASASetSourceProcPtr) (ALuint property, ALuint source, ALvoid *data, ALuint dataSize);
typedef ALenum  (*alcASAGetListenerProcPtr) (ALuint property, ALvoid *data, ALuint* dataSize);
typedef ALenum  (*alcASASetListenerProcPtr) (ALuint property, ALvoid *data, ALuint dataSize);

	/* listener properties */
	#define ALC_ASA_REVERB_ON							'rvon'	// type ALuint
	#define ALC_ASA_REVERB_GLOBAL_LEVEL					'rvgl'	// type ALfloat	-40.0 db - 40.0 db

	#define ALC_ASA_REVERB_ROOM_TYPE					'rvrt'	// type ALint	
	
	/* reverb room type presets for the ALC_ASA_REVERB_ROOM_TYPE property */
	#define ALC_ASA_REVERB_ROOM_TYPE_SmallRoom			0
	#define ALC_ASA_REVERB_ROOM_TYPE_MediumRoom			1
	#define ALC_ASA_REVERB_ROOM_TYPE_LargeRoom			2
	#define ALC_ASA_REVERB_ROOM_TYPE_MediumHall			3
	#define ALC_ASA_REVERB_ROOM_TYPE_LargeHall			4
	#define ALC_ASA_REVERB_ROOM_TYPE_Plate				5
	#define ALC_ASA_REVERB_ROOM_TYPE_MediumChamber		6
	#define ALC_ASA_REVERB_ROOM_TYPE_LargeChamber		7
	#define ALC_ASA_REVERB_ROOM_TYPE_Cathedral			8
	#define ALC_ASA_REVERB_ROOM_TYPE_LargeRoom2			9
	#define ALC_ASA_REVERB_ROOM_TYPE_MediumHall2		10
	#define ALC_ASA_REVERB_ROOM_TYPE_MediumHall3		11
	#define ALC_ASA_REVERB_ROOM_TYPE_LargeHall2			12

	#define ALC_ASA_REVERB_PRESET						'rvps'	// type ALchar* - (set only) path to an au preset file

	#define ALC_ASA_REVERB_EQ_GAIN						'rveg'	// type ALfloat
	#define ALC_ASA_REVERB_EQ_BANDWITH					'rveb'	// type ALfloat
	#define ALC_ASA_REVERB_EQ_FREQ						'rvef'	// type ALfloat

	#define ALC_ASA_REVERB_QUALITY					    'rvqt'	// type ALint
	
	/* reverb quality settings for the ALC_ASA_REVERB_QUALITY property */
	#define ALC_ASA_REVERB_QUALITY_Max					0x7F
	#define ALC_ASA_REVERB_QUALITY_High					0x60
	#define ALC_ASA_REVERB_QUALITY_Medium				0x40
	#define ALC_ASA_REVERB_QUALITY_Low					0x20
	#define ALC_ASA_REVERB_QUALITY_Min					0
	
	/* source properties */
	#define ALC_ASA_REVERB_SEND_LEVEL					'rvsl'	// type ALfloat	0.0 (dry) - 1.0 (wet) (0-100% dry/wet mix, 0.0 default)
	#define ALC_ASA_OCCLUSION							'occl'	// type ALfloat	-100.0 db (most occlusion) - 0.0 db (no occlusion, 0.0 default)
	#define ALC_ASA_OBSTRUCTION							'obst'	// type ALfloat	-100.0 db (most obstruction) - 0.0 db (no obstruction, 0.0 default)	

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	ALC_EXT_ASA_ROGER_BEEP : Apple Spatial Audio Extension for Roger Beep Effect
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
	
/*	
	Roger Beep : an effect to simulate effects such as Walkie Talkie noise. It is designed to replace the 
	source audio data with a specific 'tone' when falling below a specified db threshold for a specified time.
	This Extension will be present when the Roger Beep Audio Unit is present on the system (10.5 or greater)
	Use the alcASAGetSource() and alcASASetSource() APIs in the ALC_EXT_ASA extension.
*/

	/* source properties */
	#define ALC_ASA_ROGER_BEEP_ENABLE				'rben'	// type ALboolean	- initializes Roger Beep for use - returns error if source is not in a Stopped or Initial state
	#define ALC_ASA_ROGER_BEEP_ON					'rbon'	// type ALboolean	- set effect on/off (bypass) - default setting is true (on)
	#define ALC_ASA_ROGER_BEEP_GAIN					'rbgn'	// type ALfloat		- 20.0 (db) apply maximum effect :  -80.0(db) apply minimum effect amount
	#define ALC_ASA_ROGER_BEEP_SENSITIVITY			'rbsn'	// type ALint		- specifiy a predefined sensitivity setting
	#define ALC_ASA_ROGER_BEEP_TYPE					'rbtp'	// type ALint		- choose predefined specific Roger Beep tone
	#define ALC_ASA_ROGER_BEEP_PRESET				'rbps'	// type ALchar*		- path to an au preset file (set only) 

	/* settings for the ALC_ASA_ROGER_BEEP_TYPE property */
	#define ALC_ASA_ROGER_BEEP_TYPE_quindartone			0
	#define ALC_ASA_ROGER_BEEP_TYPE_whitenoise			1
	#define ALC_ASA_ROGER_BEEP_TYPE_walkietalkie		2

	/* settings for the ALC_ASA_ROGER_BEEP_SENSITIVITY property */ 

	#define ALC_ASA_ROGER_BEEP_SENSITIVITY_Light		0
	#define ALC_ASA_ROGER_BEEP_SENSITIVITY_Medium		1
	#define ALC_ASA_ROGER_BEEP_SENSITIVITY_Heavy		2

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	ALC_EXT_ASA_DISTORTION : Apple Spatial Audio Extension for Distortion Effect
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* 
	Distortion Effect 
	This Extension will be present when the Distortion Audio Unit is present on the system (10.5 or greater)
	Use the alcASAGetSource() and alcASASetSource() APIs in the ALC_EXT_ASA extension.
*/

	/* source properties */
	#define ALC_ASA_DISTORTION_ENABLE				'dsen'	// type ALboolean	- initializes Distortion for use - returns error if source is not in a Stopped or Initial state
	#define ALC_ASA_DISTORTION_ON					'dson'	// type ALboolean	- set effect on/off (bypass) - default setting is true (on)
	#define ALC_ASA_DISTORTION_MIX					'dsmx'	// type ALfloat		- mix balance between dry signal and distortion effect - 0.0 (no effect) - 100.0 (all effect)
	#define ALC_ASA_DISTORTION_TYPE					'dstp'	// type ALint		- choose predefined distortion settings
	#define ALC_ASA_DISTORTION_PRESET				'dsps'	// type ALchar*		- path to an au preset file (set only)

	/* settings for the ALC_ASA_DISTORTION_TYPE property */
	#define ALC_ASA_DISTORTION_TYPE_BitBrush			0
	#define ALC_ASA_DISTORTION_TYPE_BufferBeats			1
	#define ALC_ASA_DISTORTION_TYPE_LoFi				2
	#define ALC_ASA_DISTORTION_TYPE_BrokenSpeaker		3
	#define ALC_ASA_DISTORTION_TYPE_Cellphone			4
	#define ALC_ASA_DISTORTION_TYPE_Decimated1			5
	#define ALC_ASA_DISTORTION_TYPE_Decimated2			6
	#define ALC_ASA_DISTORTION_TYPE_Decimated3			7
	#define ALC_ASA_DISTORTION_TYPE_Decimated4			8
	#define ALC_ASA_DISTORTION_TYPE_DistortedFunk		9
	#define ALC_ASA_DISTORTION_TYPE_DistortionCubed		10
	#define ALC_ASA_DISTORTION_TYPE_DistortionSquared	11
	#define ALC_ASA_DISTORTION_TYPE_Echo1				12
	#define ALC_ASA_DISTORTION_TYPE_Echo2				13
	#define ALC_ASA_DISTORTION_TYPE_EchoTight1			14
	#define ALC_ASA_DISTORTION_TYPE_EchoTight2			15
	#define ALC_ASA_DISTORTION_TYPE_EverythingBroken	16
	#define ALC_ASA_DISTORTION_TYPE_AlienChatter		17
	#define ALC_ASA_DISTORTION_TYPE_CosmicInteference	18
	#define ALC_ASA_DISTORTION_TYPE_GoldenPi			19
	#define ALC_ASA_DISTORTION_TYPE_RadioTower			20
	#define ALC_ASA_DISTORTION_TYPE_Waves				21

	
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ALC_EXT_OUTPUT_CAPTURER
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*
 Allows an application to capture the rendered output of the current context.
 The application prepares OpenAL for capturing the context output by specifying the data format
 of the captured audio output data. Once capture has been started, the application then queries OpenAL
 for the available number of captured samples, and requests the samples by providing a buffer to fill.
 
 Retrieve functions via alcGetProcAddress() by passing in strings: alcOutputCapturerPrepare, alcOutputCapturerStart,
 alcOutputCapturerStop, alcOutputCapturerAvailableSamples and alcOutputCapturerSamples
 */

/*
 API: alcOutputCapturerPrepare
 
 Prepare output capturing of the current context by specifying the data format desired from OpenAL.
 
 frequency		- Sampling rate of the captured output.
 
 format         - Data format of the captured data. Specified as one of the native OpenAL data format types:
 AL_FORMAT_MONO8
 AL_FORMAT_MONO16
 AL_FORMAT_STEREO8
 AL_FORMAT_STEREO16
 
 maxsamplecount     - The maximum number of samples that will be requested by the application.
 */
typedef ALvoid AL_APIENTRY (*alcOutputCapturerPrepareProcPtr)   (ALCuint frequency, ALCenum format, ALCsizei maxsamplecount);

/*
 API: alcOutputCapturerStart
 
 Start capturing samples rendered by the current context to a maximum of the sample count specified when calling alcOutputCapturerPrepare.
 */
typedef ALvoid AL_APIENTRY (*alcOutputCapturerStartProcPtr) ();

/*
 API: alcOutputCapturerStop
 
 Stop capturing samples rendered by the context. This function resets the captured audio samples to 0.
 */
typedef ALvoid AL_APIENTRY (*alcOutputCapturerStopProcPtr) ();

/*
 API: alcOutputCapturerAvailableSamples
 
 Get the number of captured samples currently available.
 */
typedef ALint  AL_APIENTRY (*alcOutputCapturerAvailableSamplesProcPtr) ();

/*
 API: alcOutputCapturerSamples
 
 Write captured samples to an application provided buffer.
 
 buffer         -   Application provided buffer to be filled with the requested amount of samples and must be of size
 samplecount * size of sample. i.e. 100 samples of AL_FORMAT_STEREO16 data -> 100 * 4 = 400 bytes
 The buffer must NOT be deallocated before the call to alcOutputCapturerSamples returns.
 
 samplecount    -   Number of samples to be copied to the provided buffer.
 Requesting more samples than currently available is an error.
 */
typedef ALvoid AL_APIENTRY (*alcOutputCapturerSamplesProcPtr)   (ALCvoid *buffer, ALCsizei samplecount);


#endif // __MAC_OSX_OAL_EXTENSIONS_H__