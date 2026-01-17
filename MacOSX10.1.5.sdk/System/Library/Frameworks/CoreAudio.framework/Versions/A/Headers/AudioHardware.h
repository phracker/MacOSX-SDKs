/*
     File:       CoreAudio/AudioHardware.h

     Contains:   API for communicating with audio hardware.

     Version:    Technology: Mac OS X
                 Release:    Mac OS X

     Copyright:  (c) 1985-2001 by Apple Computer, Inc., all rights reserved.

     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:

                     http://developer.apple.com/bugreporter/

*/
#if !defined(__AudioHardware_h__)
#define __AudioHardware_h__

//=============================================================================
//	Includes
//=============================================================================

#include <CoreAudio/CoreAudioTypes.h>

#if defined(__cplusplus)
extern "C"
{
#endif

//=============================================================================
//	Theory of Operation
//
//	The Audio Hardware API provides multiple clients simultaneous access to
//	all of the audio devices attached to the host, no matter how the
//	connection is made (PCI, USB, Firewire, etc). The goal of this API is to
//	provide as little overhead and as clean a signal path as possible.
//
//	All clients of this API are assumed to take the appropriate precautions
//	against things like page faults or threading priority issues where ever
//	appropriate.
//
//	The basis of this API is the Audio Device. It provides a unit of
//	encapsulation for IO, timing services and properties that describe and
//	control the device. Specifically, an Audio Device represents a single IO
//	cycle, a clock source based on it, and all the buffers synchronized to it.
//
//	An Audio Device is further broken down into Audio Streams. An Audio Stream
//	encapsulates the buffer of memory for transferring the audio data across
//	the user/kernel boundary. Like Audio Devices, the Audio Stream provides
//	properties that describe and control it. Audio Streams always have a single
//	direction, either input or output.
//
//	Audio Devices are addressed in the API by specifying whether the request is
//	for input or output and it's channel number. Channel 0 always represents the
//	"master" channel for a device. The actual channels of the device then use
//	a one-based indexing scheme and are numbered consecutively up to the total
//	number of channels for all the Audio Device's Audio Streams.
//
//	Audio Streams are addressed similarly, only they omit the direction as it is
//	implied in the nature of the stream. The channel numbers for each Audio Stream
//	in an Audio Device always start at 0 and are numbered consecutively up to the
//	total number of channels in that particular Audio Stream. It is important to
//	remember that what is channel 2 for an Audio Stream might not be channel 2 for
//	it's Audio Device, depending on the stream configuration of the device.
//
//	The IO cycle of an Audio Device presents the data for all it's Audio Streams,
//	input and output, in the same call out to the client. It also provides the 
//	timestamp of when the first sample frame of the input data was acquired as well
//	as the timestamp ofwhen the first sample frame of the output data will be
//	consumed. The size of the buffers used for transfer are specified per Audio Device.
//
//	Audio Streams are the gate keepers of format information. Each Audio Stream
//	on an Audio Device may have it's own format. Further, changes to the format
//	of one Audio Stream can and often do affect the format of the other Audio Streams
//	on the Audio Device. This is particularly true of the sample rate aspect of the
//	stream's format, as all streams attached to a device share the same sample rate.
//	It is possible for Audio Streams to provide and consume data in any format
//	including compressed formats. The format proprerties specify the basic format of
//	the data. It can be further specified by other properties such as the compression
//	description property.
//
//	Note that if an Audio Stream presents its format as linear PCM, it will always
//	present its data as 32 bit floating point data. Any necessary conversion to the
//	actual physical hardware format (such as 16 or 24 bit integer) are handled by the
//	driver in order to preserve the headroom of the device's mix bus.
//
//	The format related properties of Audio Devices simply vector the request to the
//	stream containing the requested channel and direction. Format requests for
//	channel 0 always map to the first Audio Stream.
//
//	An Audio Device should, but is not required to, support an arbitrary number of
//	clients. An error will be returned if a given device refuses to accept
//	another client, or the device is in "hog" mode. In hog mode, a device will
//	only allow one client at a time. This is intended to provide a client a way
//	of ensuring that it is getting all of a device's time. Hog mode is a "first
//	come, first served" service.
//
//	As previously stated, Audio Devices and Audio Streams have properties describe
//	that describe or control a some aspect of a their operation such as the current
//	format or its name. There are also global system properties such as the list of
//	available devices. Properties are represented by a unique ID and have conventions
//	about the kind of data they use for a value. Changes to a property's value can be
//	scheduled to happen in real time (if the device supports it) or they can happen
//	immediately. Clients can sign up to be notified when a property's value changes.
//=============================================================================

//=============================================================================
//	Types specific to the Audio Hardware API
//=============================================================================

typedef UInt32	AudioHardwarePropertyID;
typedef UInt32	AudioDeviceID;
typedef UInt32	AudioDevicePropertyID;
typedef UInt32	AudioStreamID;

#define kAudioDeviceUnknown ((AudioDeviceID)0)
#define kAudioStreamUnknown ((AudioStreamID)0)

//=============================================================================
//	Standard Global Properties
//
//	Used with the AudioHardwareXXXXPropertyXXXX family of routines.
//=============================================================================

enum
{
	kAudioHardwarePropertyDevices						= 'dev#',
		//	a array of the AudioDeviceIDs available in the system
		
	kAudioHardwarePropertyDefaultInputDevice			= 'dIn ',
		//	the AudioDeviceID of the default input device
		
	kAudioHardwarePropertyDefaultOutputDevice			= 'dOut',
		//	the AudioDeviceID of the default output device

	kAudioHardwarePropertyDefaultSystemOutputDevice		= 'sOut',
		//	the AudioDeviceID of the default system output device
		//	Services that generate audio as a system service, like
		//	SysBeep() or digial call progress should use this device.
	
	kAudioHardwarePropertyDeviceForUID					= 'duid',
		//	retrieves the AudioDeviceID for the given device
		//	unique identifier previously retrieved with
		//	kAudioDevicePropertyUID (see below) using an
		//	AudioValueTranslation structure. The input is a
		//	CFStringRef containing the UID and the output
		//	is an AudioDeviceID.

	kAudioHardwarePropertySleepingIsAllowed				= 'slep',
		//	A UInt32 where 1 means this process will allow the
		//	machine to sleep and 0 will keep the machine awake.
		//	Note that the machine can still be forced to go to
		//	sleep regardless of the setting of this property.

	kAudioHardwarePropertyRunLoop						= 'rnlp'
		//	a CFRunLoopRef to which the client wishes the HAL to
		//	attach system notifications to. By default the HAL
		//	will attach it's system notifications to the thread
		//	CarbonCore is initialized on. This property can be
		//	used to override this selection. The HAL will move
		//	all it's currently attached notifications to the new
		//	run loop.

};

//=============================================================================
//	Standard Device Properties
//
//	Used with the AudioDeviceXXXXPropertyXXXX and AudioStreamXXXXPropertyXXXX
//	families of routines.
//=============================================================================

enum
{
	kAudioDevicePropertyDeviceName						= 'name',
		//	the name of the device as a null terminated C-string
		
	kAudioDevicePropertyDeviceNameCFString				= 'lnam',
		//	the name of the device as a CFStringRef. The CFStringRef
		//	retrieved via this property must be released by the caller.
		
	kAudioDevicePropertyDeviceManufacturer				= 'makr',
		//	the manufacturer of the device as a null terminated C-string
	
	kAudioDevicePropertyDeviceManufacturerCFString		= 'lmak',
		//	the manufacturer of the device as a CFStringRef. The CFStringRef 
		//	retrieved via this property must be released by the caller.
	
	kAudioDevicePropertyDeviceUID						= 'uid ',
		//	a CFStringRef that contains a unique identifier for the device.
		//	This ID is persistent and can be used from run to run of a process
		//	and across boots. Use kAudioHardwarePropertyDeviceForUID to
		//	retrieve the AudioDeviceID for the ID returned by this property.
		//	The caller is responsible for releasing the returned CFStringRef.
		
	kAudioDevicePropertyDeviceIsAlive					= 'livn',
		//	a UInt32 where 1 means the device is installed and ready
		//	to handle requests and 0 means the device has been removed
		//	or otherwise disconnected and is about to go away completely.
		//	After receiving notification on this property, any AudioDeviceID's
		//	referring to the destroyed device are invalid. It is highly
		//	recommended that all clients listen for this notification.
	
	kAudioDevicePropertyDeviceIsRunning					= 'goin',
		//	a UInt32 where 0 means the device is off and 1 means
		//	the device is running
	
	kAudioDeviceProcessorOverload						= 'over',
		//	This property exists so that clients can be told when
		//	they are overloading the the IO thread. When the HAL dectects
		//	the situation where the combined processing time exceeds the
		//	duration of the buffer, it will notify all listeners on this
		//	property. Overloading also will cause the HAL to resynch itself
		//	and restart the IO cycle to be sure that the IO thread goes
		//	to sleep. The value of this property is a UInt32, but it's
		//	value has no currently defined meaning.
		
	kAudioDevicePropertyHogMode							= 'oink',
		//	An pid_t indicating the process ID that currently owns
		//	hog mode for the device or a -1 indicating that no process
		//	currently owns it. While a process owns hog mode for a device,
		//	no other process on the system can perform IO with the given
		//	device. When calling AudioDeviceSetProperty to acquire hog mode
		//	for a device, the value on input means nothing, but on output
		//	will contain the process ID of the owner of hog which should be
		//	the ID for the current process if the call is successful.
		//	The HAL uses the process IDs acquired from getpid().
	
	kAudioDevicePropertyRegisterBufferList				= 'rbuf',
		//	This property allows clients to register a fully populated
		//	AudioBufferList that matches the topology described by
		//	kAudioDevicePropertyStreamConfiguration for doing IO using
		//	AudioDeviceRead. The AudioBufferList will be registered
		//	with the call the AudioDeviceSetProperty and will be
		//	unregistered with the call to AudioDeceGetProperty.
	
	kAudioDevicePropertyLatency							= 'ltnc',
		//	a UInt32 containing the number of frames of latency in the device
		//	Note that input and output latency may differ.
	
	kAudioDevicePropertyBufferSize						= 'bsiz',
		//	a UInt32 containing the size of the IO buffers in bytes
	
	kAudioDevicePropertyBufferSizeRange					= 'bsz#',
		//	an AudioValueRange specifying the minimum and maximum byte
		//	sizes that will be accepted for the device.

	kAudioDevicePropertyBufferFrameSize					= 'fsiz',
		//	a UInt32 containing the size of the IO buffers in frames
		//	It is highly recommended that all clients listen for this
		//	notification.
	
	kAudioDevicePropertyBufferFrameSizeRange			= 'fsz#',
		//	an AudioValueRange specifying the minimum and maximum frame
		//	sizes that will be accepted for the device.

	kAudioDevicePropertyStreams							= 'stm#',
		//	a array of the AudioStreamIDs available on the device.
		//	Note that if a notification for this property is received,
		//	all of the AudioStreamIDs that refer to streams on this device
		//	are invalid and should be refreshed. Installed listener routines
		//	will continue to be called as appropriate.
		
	kAudioDevicePropertySafetyOffset					= 'saft',
		//	a UInt32 containing the number of frames ahead (for
		//	output) or behind (for input) the head that it is
		//	safe to start reading or writing.
			
	kAudioDevicePropertyStreamConfiguration				= 'slay',
		//	This property returns the stream configuration of the device in
		//	an AudioBufferList (with the buffer pointers set to NULL) which
		//	describes the list of streams and the number of channels in each
		//	stream.	This corresponds to what will be passed into the IOProc.
		//	It is highly recommended that all clients listen for this notification.
	
	kAudioDevicePropertyStreamFormat					= 'sfmt',
		//	The stream format of the stream containing the requested channel
		//	as an AudioStreamBasicDescription. Since formats are stream level
		//	entities, the number of channels returned with this property actually
		//	refers to the number of channels in the stream containing the requested
		//	channel. Consequently, it only gives a partial picture of the overall
		//	number of channels for the device. Use kAudioDevicePropertyStreamConfiguration
		//	to get the information on how the channels are divied up across the streams.
		//	It is highly recommended that all clients listen for this notification.
	
	kAudioDevicePropertyStreamFormats					= 'sfm#',
		//	a array of the AudioStreamBasicDescription's the device supports
	
	kAudioDevicePropertyStreamFormatSupported			= 'sfm?',
		//	An AudioStreamBasicDescription is passed in to query whether or not
		//	the format is supported. A kAudioDeviceUnsupportedFormatError will
		//	be returned if the format is not supported and kAudioHardwareNoError
		//	will be returned if it is supported. AudioStreamBasicDescription
		//	fields set to 0 will be ignored in the query, but otherwise values
		//	must match exactly.
	
	kAudioDevicePropertyStreamFormatMatch				= 'sfmm',
		//	An AudioStreamBasicDescription is passed in which is modified
		//	to describe the closest match to the given format that is
		//	supported by the device. AudioStreamBasicDescription fields set
		//	to 0 should be ignored in the query and the device is free to
		//	substitute any value it sees fit. Note that the device may
		//	return a result that differs dramatically from the requested
		//	format. All matching is at the device's ultimate discretion.
	
	kAudioDevicePropertyVolumeScalar					= 'volm',
		//	a Float32 between 0 and 1 that scales the volume of the device/channel
		//	across the full range of the device.

	kAudioDevicePropertyVolumeDecibels					= 'vold',
		//	a Float32 whose units are decibels where 0 represents unity,
		//	negative values for attenuation and positive values for gain.
	
	kAudioDevicePropertyVolumeRangeDecibels				= 'vdb#',
		//	an AudioValueRange specifying the minimum and maximum db values.
	
	kAudioDevicePropertyVolumeScalarToDecibels			= 'v2db',
		//	convert the Float32 scalar volume to decibels

	kAudioDevicePropertyVolumeDecibelsToScalar			= 'db2v',
		//	convert the Float32 decibel volume to scalar

	kAudioDevicePropertyMute							= 'mute',
		//	a UInt32 where 0 means the device is not muted and 1 means
		//	the device is muted

	kAudioDevicePropertyPlayThru						= 'thru',
		//	a UInt32 where 0 means play through is off and 1 means
		//	play through is on

	kAudioDevicePropertyDataSource						= 'ssrc',
		//	a UInt32 which is the ID of the data source for the given channel
	
	kAudioDevicePropertyDataSources						= 'ssc#',
		//	an array of the available UInt32 data source IDs for the given channel
	
	kAudioDevicePropertyDataSourceNameForID				= 'sscn',
		//	Retrieves the name of a data source for a given data source ID
		//	using an AudioValueTranslation structure. The input data is the
		//	UInt32 holding the data source ID and the output data is a buffer to
		//	hold the name as a null terminated string.
	
	kAudioDevicePropertyDataSourceNameForIDCFString		= 'lscn',
		//	Retrieves the name of a data source for a given data source ID
		//	using an AudioValueTranslation structure. The input data is the
		//	UInt32 holding the data source ID and the output data is a CFStringRef.
		//	The CFStringRef retrieved via this property must be released
		//	by the caller.

	kAudioDevicePropertyClockSource						= 'csrc',
		//	a UInt32 which is the ID of the clock source for the given channel
	
	kAudioDevicePropertyClockSources					= 'csc#',
		//	an array of the available UInt32 clock source IDs for the given channel
	
	kAudioDevicePropertyClockSourceNameForID			= 'cscn',
		//	Retrieves the name of a clock source for a given clock source ID
		//	using an AudioValueTranslation structure. The input data is the
		//	UInt32 holding the clock source ID and the output data is a buffer to
		//	hold the name as a null terminated string.
	
	kAudioDevicePropertyClockSourceNameForIDCFString	= 'lcsn'
		//	Retrieves the name of a clock source for a given clock source ID
		//	using an AudioValueTranslation structure. The input data is the
		//	UInt32 holding the clock source ID and the output data is a CFStringRef.
		//	The CFStringRef retrieved via this property must be released
		//	by the caller.

};

//=============================================================================
//	Standard Stream Properties
//
//	Used with the AudioStreamXXXXPropertyXXXX family of routines.
//=============================================================================

enum
{
	kAudioStreamPropertyOwningDevice					= 'stdv',
		//	the AudioDeviceID of the device that owns this stream

	kAudioStreamPropertyDirection						= 'sdir',
		//	a UInt32 where 0 means output and 1 means input
		
	kAudioStreamPropertyStartingChannel					= 'schn',
		//	a UInt32 that specifies the first device channel number for this stream
		
	kAudioStreamPropertyPhysicalFormat					= 'pft ',
		//	An AudioStreamBasicDescription containing the current physical format
		//	of the stream. The physical properties describe and manipulate the
		//	hardware is actually working in. Note that this may be different from
		//	the format used in the IOProc. A physical format change does not
		//	necessarily imply a change in kAudioDevicePropertyStreamFormat.
	
	kAudioStreamPropertyPhysicalFormats					= 'pft#',
		//	an array of the AudioStreamBasicDescription's the stream supports physically
	
	kAudioStreamPropertyPhysicalFormatSupported			= 'pft?',
		//	An AudioStreamBasicDescription is passed in to query whether or not
		//	the physical format is supported. A kAudioDeviceUnsupportedFormatError
		//	will be returned if the format is not supported and kAudioHardwareNoError
		//	will be returned if it is supported. AudioStreamBasicDescription
		//	fields set to 0 will be ignored in the query, but otherwise values
		//	must match exactly.
	
	kAudioStreamPropertyPhysicalFormatMatch				= 'pftm'
		//	An AudioStreamBasicDescription is passed in which is modified
		//	to describe the closest match to the given physcial format that
		//	is supported by the device. AudioStreamBasicDescription fields set
		//	to 0 will be ignored in the query and the stream is free to
		//	substitute any value it sees fit. Note that the stream may
		//	return a result that differs dramatically from the requested
		//	format. All matching is at the stream's ultimate discretion.

};

//=============================================================================
//	Property Listener Wildcards
//
//	Used when adding/removing the various kinds of listener routines to
//	specify one routine to field many different kinds of notifications.
//=============================================================================

enum
{
	kAudioPropertyWildcardPropertyID					= '****',
		//	a wild card for AudioHardwarePropertyIDs, AudioDevicePropertyIDs,
		//	and AudioDevicePropertyIDs
		
	kAudioPropertyWildcardSection						= 0xFF,
		//	a wild card for specifying the section (aka the isInput parameter)
		
	kAudioPropertyWildcardChannel						= 0xFFFFFFFF
		//	a wild card for the channel
};

//=============================================================================
//	Errors
//=============================================================================

enum
{
	kAudioHardwareNoError								= 0,
	kAudioHardwareNotRunningError						= 'stop',
	kAudioHardwareUnspecifiedError						= 'what',
	kAudioHardwareUnknownPropertyError					= 'who?',
	kAudioHardwareBadPropertySizeError					= '!siz',
	kAudioHardwareIllegalOperationError					= 'nope',
	kAudioHardwareBadDeviceError						= '!dev',
	kAudioHardwareBadStreamError						= '!str',
	kAudioDeviceUnsupportedFormatError					= '!dat',
	kAudioDevicePermissionsError						= '!hog'
};

//=============================================================================
//	General Routines
//=============================================================================

//-----------------------------------------------------------------------------
//	AudioHardwareUnload
//
//	When this routine is called, all IO on all devices within a process will
//	be terminated and all resources capable of being released will be released.
//	This routine essentially returns the HAL to it's uninitialized state.
//-----------------------------------------------------------------------------

extern OSStatus
AudioHardwareUnload();

//=============================================================================
//	Global Property Management
//=============================================================================

//-----------------------------------------------------------------------------
//	AudioHardwareGetPropertyInfo
//
//	Retrieve information about the given property. The outSize argument
//	will return the size in bytes of the current value of the property.
//	The outWritable argument will return whether or not the property
//	in question can be changed.
//-----------------------------------------------------------------------------
	
extern OSStatus
AudioHardwareGetPropertyInfo(	AudioHardwarePropertyID inPropertyID,
								UInt32*					outSize,
								Boolean*				outWritable);

//-----------------------------------------------------------------------------
//	AudioHardwareGetProperty
//
//	Retrieve the indicated property data. On input, ioDataSize has the size
//	of the data pointed to by outPropertyData. On output, it will contain
//	the amount written. If outPropertydata is NULL and ioPropertyDataSize is
//	not, the amount that would have been written will be reported.
//-----------------------------------------------------------------------------
	
extern OSStatus
AudioHardwareGetProperty(	AudioHardwarePropertyID	inPropertyID,
							UInt32*					ioPropertyDataSize,
							void*					outPropertyData);

//-----------------------------------------------------------------------------
//	AudioHardwareSetProperty
//
//	Set the indicated property data. Global properties, by definition, don't
//	directly affect real time, so they don't need a time stamp.
//-----------------------------------------------------------------------------
	
extern OSStatus
AudioHardwareSetProperty(	AudioHardwarePropertyID	inPropertyID,
							UInt32					inPropertyDataSize,
							void*					inPropertyData);

//-----------------------------------------------------------------------------
//	AudioHardwarePropertyListenerProc
//
//	This routine is called when a property's value changes.
//-----------------------------------------------------------------------------

typedef OSStatus
(*AudioHardwarePropertyListenerProc)(	AudioHardwarePropertyID	inPropertyID,
										void*					inClientData);
														
//-----------------------------------------------------------------------------
//	AudioHardwareAddPropertyListener
//
//	Set up a routine that gets called when a property is changed.
//-----------------------------------------------------------------------------

extern OSStatus
AudioHardwareAddPropertyListener(	AudioHardwarePropertyID				inPropertyID,
									AudioHardwarePropertyListenerProc	inProc,
									void*								inClientData);

//-----------------------------------------------------------------------------
//	AudioHardwareRemovePropertyListener
//
//	Remove the given notification.
//-----------------------------------------------------------------------------

extern OSStatus
AudioHardwareRemovePropertyListener(	AudioHardwarePropertyID				inPropertyID,
										AudioHardwarePropertyListenerProc	inProc);


//=============================================================================
//	IO Management
//
//	These routines allow a client to send and receive data on a given device.
//	They also provide support for tracking where in a stream of data the
//	hardware is at currently.
//=============================================================================

//-----------------------------------------------------------------------------
//	AudioDeviceIOProc
//
//	This is a client supplied routine that the hardware calls to do an
//	IO transaction for a given device. All input and output is presented
//	to the client simultaneously for processing. The inNowSamples parameter
//	is the sample time that should be used as the basis of now rather than
//	what might be provided by a query to the device's clock. This is necessary
//	because time will continue to advance while this routine is executing
//	making retrieving the current time from the appropriate parameter
//	unreliable for synch operations. The time stamp for theInputData represents
//	when the data was recorded. For the output, the time stamp represents
//	when the first sample will be played. In all cases, each time stamp is
//	accompanied by its mapping into host time.
//
//	The format of the actual data depends of the sample format
//	of the device as specified by its properties. It may be raw or compressed,
//	interleaved or not interleaved as determined by the requirements of the
//	device and its settings.
//
//	If the data for either the input or the output is invalid, the time stamp
//	will have a value of 0. This happens when a device doesn't have any inputs
//	or outputs.
//-----------------------------------------------------------------------------

typedef OSStatus
(*AudioDeviceIOProc)(	AudioDeviceID			inDevice,
						const AudioTimeStamp*	inNow,
						const AudioBufferList*	inInputData,
						const AudioTimeStamp*	inInputTime,
						AudioBufferList*		outOutputData, 
						const AudioTimeStamp*	inOutputTime,
						void*					inClientData);

//-----------------------------------------------------------------------------
//	AudioDeviceAddIOProc
//
//	Install the given IO proc for the given device. A client may have multiple
//	IO procs for a given device. The device may refuse to accept an IO proc
//	if it is in "hog" mode or it has as many clients as it can handle already.
//-----------------------------------------------------------------------------

extern OSStatus
AudioDeviceAddIOProc(	AudioDeviceID		inDevice,
						AudioDeviceIOProc	inProc,
						void*				inClientData);

//-----------------------------------------------------------------------------
//	AudioDeviceRemoveIOProc
//
//	Remove the given IO proc for the given device.
//-----------------------------------------------------------------------------

extern OSStatus
AudioDeviceRemoveIOProc(AudioDeviceID inDevice, AudioDeviceIOProc inProc);

//-----------------------------------------------------------------------------
//	AudioDeviceStart
//
//	Start up the given IOProc. Note that the IOProc will likely get called
//	for the first time before the call to this routine returns.
//
//	Passing NULL to this routine will start the hardware, even though there
//	may be no IOProcs registered. This is helpful if you plan on using
//	any of the device's services that require it to be running such as
//	AudioDeviceRead or AudioDeviceGetCurrentTime. A balancing call to
//	AudioDeviceStop with a NULL IOProc is required to stop the hardware.
//-----------------------------------------------------------------------------

extern OSStatus
AudioDeviceStart(AudioDeviceID inDevice, AudioDeviceIOProc inProc);

//-----------------------------------------------------------------------------
//	AudioDeviceStop
//
//	Stop the given IOProc.
//-----------------------------------------------------------------------------

extern OSStatus
AudioDeviceStop(AudioDeviceID inDevice, AudioDeviceIOProc inProc);

//-----------------------------------------------------------------------------
//	AudioDeviceRead
//
//	Read some data from a device starting at the given time. The
//	AudioBufferList must be in the same size and shape as the one
//	returned via kAudioDevicePropertyStreamConfiguration and must be
//	registered with the device using kAudioDevicePropertyRegisterBufferList.
//	The number of bytes read into each buffer will be written back to the
//	structure.
//
//	The valid range of time that can be read is from the current time minus
//	the maximum buffer size minus the safety offset to the current time mins
//	the safety offset.
//-----------------------------------------------------------------------------

extern OSStatus
AudioDeviceRead(AudioDeviceID inDevice, const AudioTimeStamp* inStartTime, AudioBufferList* outData);

//=============================================================================
//	Time Management
//
//	Note that time operations are only valid while the device in question
//	is running. Otherwise, a kAudioHardwareNotRunningError will be returned.
//=============================================================================

//-----------------------------------------------------------------------------
//	AudioDeviceGetCurrentTime
//
//	Retrieve the current time.
//-----------------------------------------------------------------------------

extern OSStatus
AudioDeviceGetCurrentTime(AudioDeviceID inDevice, AudioTimeStamp* outTime);

//-----------------------------------------------------------------------------
//	AudioDeviceTranslateTime
//
//	Translate the given time. The output time formats are requested using
//	the flags in the outTime argument. A device may or may not be able to
//	satisfy all requests so be sure to check the flags again on output.
//-----------------------------------------------------------------------------

extern OSStatus
AudioDeviceTranslateTime(	AudioDeviceID			inDevice,
							const AudioTimeStamp*	inTime,
							AudioTimeStamp*			outTime);

//=============================================================================
//	Device Property Management
//
//	When getting and setting a device's properties, it is necessary to always
//	specify exactly which part of the device to interrogate. The section is
//	specified with a boolean argument (generally called isInput) where true
//	refers to the input section and false refers to the output section. The
//	channel is specified with an unsigned integer argument (generally called
//	inChannel) where 0 means the master channel and greater than zero refers to the
//	Nth indexed channel starting with index 1.
//=============================================================================

//-----------------------------------------------------------------------------
//	AudioDeviceGetPropertyInfo
//
//	Retrieve information about the given property on the given
//	channel. The outSize argument will return the size in bytes of the current
//	value of the property. The outWritable argument will return whether or
//	not the property in question can be changed.
//-----------------------------------------------------------------------------
	
extern OSStatus
AudioDeviceGetPropertyInfo(	AudioDeviceID			inDevice,
							UInt32					inChannel,
							Boolean					isInput,
							AudioDevicePropertyID	inPropertyID,
							UInt32*					outSize,
							Boolean*				outWritable);

//-----------------------------------------------------------------------------
//	AudioDeviceGetProperty
//
//	Retrieve the indicated property data for the given device. A property
//	is specified as an ID and a channel number. The channel number allows for
//	access to properties on the channel level. On input, ioDataSize has the size
//	of the data pointed to by outPropertyData. On output, it will contain
//	the amount written. If outPropertydata is NULL and ioPropertyDataSize is
//	not, the amount that would have been written will be reported.
//-----------------------------------------------------------------------------
	
extern OSStatus
AudioDeviceGetProperty(	AudioDeviceID			inDevice,
						UInt32					inChannel,
						Boolean					isInput,
						AudioDevicePropertyID	inPropertyID,
						UInt32*					ioPropertyDataSize,
						void*					outPropertyData);

//-----------------------------------------------------------------------------
//	AudioDeviceSetProperty
//
//	Set the indicated property data for the given device.
//-----------------------------------------------------------------------------
	
extern OSStatus
AudioDeviceSetProperty(	AudioDeviceID			inDevice,
						const AudioTimeStamp*	inWhen,
						UInt32					inChannel,
						Boolean					isInput,
						AudioDevicePropertyID	inPropertyID,
						UInt32					inPropertyDataSize,
						const void*				inPropertyData);

//-----------------------------------------------------------------------------
//	AudioDevicePropertyListenerProc
//
//	This routine is called when a property's value changes.
//-----------------------------------------------------------------------------

typedef OSStatus
(*AudioDevicePropertyListenerProc)(	AudioDeviceID			inDevice,
									UInt32					inChannel,
									Boolean					isInput,
									AudioDevicePropertyID	inPropertyID,
									void*					inClientData);
														
//-----------------------------------------------------------------------------
//	AudioDeviceAddPropertyListener
//
//	Set up a routine that gets called when the property of a device is changed.
//-----------------------------------------------------------------------------

extern OSStatus
AudioDeviceAddPropertyListener(	AudioDeviceID					inDevice,
								UInt32							inChannel,
								Boolean							isInput,
								AudioDevicePropertyID			inPropertyID,
								AudioDevicePropertyListenerProc	inProc,
								void*							inClientData);

//-----------------------------------------------------------------------------
//	AudioDeviceRemovePropertyListener
//
//	Remove the given notification.
//-----------------------------------------------------------------------------

extern OSStatus
AudioDeviceRemovePropertyListener(	AudioDeviceID					inDevice,
									UInt32							inChannel,
									Boolean							isInput,
									AudioDevicePropertyID			inPropertyID,
									AudioDevicePropertyListenerProc	inProc);

//=============================================================================
//	Stream Property Management
//
//	When getting and setting a stream's properties, it is necessary to always
//	specify exactly which part of the stream to interrogate. The channel is specified
//	with an unsigned integer argument (generally called inChannel) where 0 means
//	the master channel and greater than zero refers to the Nth indexed channel
//	starting with index 1.
//=============================================================================

//-----------------------------------------------------------------------------
//	AudioStreamGetPropertyInfo
//
//	Retrieve information about the given property on the given
//	channel. The outSize argument will return the size in bytes of the current
//	value of the property. The outWritable argument will return whether or
//	not the property in question can be changed.
//-----------------------------------------------------------------------------
	
extern OSStatus
AudioStreamGetPropertyInfo(	AudioStreamID			inStream,
							UInt32					inChannel,
							AudioDevicePropertyID	inPropertyID,
							UInt32*					outSize,
							Boolean*				outWritable);

//-----------------------------------------------------------------------------
//	AudioStreamGetProperty
//
//	Retrieve the indicated property data for the given channel. A property
//	is specified as an ID and a channel number. The channel number allows for
//	access to properties on the channel level. On input, ioDataSize has the size
//	of the data pointed to by outPropertyData. On output, it will contain
//	the amount written. If outPropertydata is NULL and ioPropertyDataSize is
//	not, the amount that would have been written will be reported.
//-----------------------------------------------------------------------------
	
extern OSStatus
AudioStreamGetProperty(	AudioStreamID			inStream,
						UInt32					inChannel,
						AudioDevicePropertyID	inPropertyID,
						UInt32*					ioPropertyDataSize,
						void*					outPropertyData);

//-----------------------------------------------------------------------------
//	AudioStreamSetProperty
//
//	Set the indicated property data for the given channel.
//-----------------------------------------------------------------------------
	
extern OSStatus
AudioStreamSetProperty(	AudioStreamID			inStream,
						const AudioTimeStamp*	inWhen,
						UInt32					inChannel,
						AudioDevicePropertyID	inPropertyID,
						UInt32					inPropertyDataSize,
						const void*				inPropertyData);

//-----------------------------------------------------------------------------
//	AudioStreamPropertyListenerProc
//
//	This routine is called when a property's value changes.
//-----------------------------------------------------------------------------

typedef OSStatus
(*AudioStreamPropertyListenerProc)(	AudioStreamID			inStream,
									UInt32					inChannel,
									AudioDevicePropertyID	inPropertyID,
									void*					inClientData);
														
//-----------------------------------------------------------------------------
//	AudioStreamAddPropertyListener
//
//	Set up a routine that gets called when the property of a stream is changed.
//-----------------------------------------------------------------------------

extern OSStatus
AudioStreamAddPropertyListener(	AudioStreamID					inStream,
								UInt32							inChannel,
								AudioDevicePropertyID			inPropertyID,
								AudioStreamPropertyListenerProc	inProc,
								void*							inClientData);

//-----------------------------------------------------------------------------
//	AudioStreamRemovePropertyListener
//
//	Remove the given notification.
//-----------------------------------------------------------------------------

extern OSStatus
AudioStreamRemovePropertyListener(	AudioStreamID					inStream,
									UInt32							inChannel,
									AudioDevicePropertyID			inPropertyID,
									AudioStreamPropertyListenerProc	inProc);

#if defined(__cplusplus)
}
#endif

#endif
