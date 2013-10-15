/*
     File:       CoreAudio/AudioHardware.h

     Contains:   API for communicating with audio hardware.

     Version:    Technology: Mac OS X
                 Release:    Mac OS X

     Copyright:  (c) 1985-2003 by Apple Computer, Inc., all rights reserved.

     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:

                     http://developer.apple.com/bugreporter/

*/
#if !defined(__AudioHardware_h__)
#define __AudioHardware_h__

//=============================================================================
//	Includes
//=============================================================================

#include <AvailabilityMacros.h>
#include <CoreAudio/CoreAudioTypes.h>

#if PRAGMA_ENUM_ALWAYSINT
	#pragma enumsalwaysint off
#endif

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
//	the data.
//
//	If an Audio Stream presents its format as linear PCM, it will always present
//	its data as 32 bit floating point data. Any necessary conversion to the actual
//	physical hardware format (such as 16 or 24 bit integer) is handled by the
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
//
//	Changing the value of most properties of a device or stream is an asynchronous
//	operation. The change should not be considered in effect until the notification
//	for the change is received. This is particularly true for changing the format
//	of a device, but also for control changes like volume, mute, data source, etc.
//	as well.
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

//	This struct is used to indicate the stream usage of a given IOProc
struct	AudioHardwareIOProcStreamUsage
{
	void*	mIOProc;
	UInt32	mNumberStreams;
	UInt32	mStreamIsOn[1];
};
typedef struct AudioHardwareIOProcStreamUsage	AudioHardwareIOProcStreamUsage;

//=============================================================================
//	Standard Global Properties
//
//	Used with the AudioHardwareXXXXPropertyXXXX family of routines.
//=============================================================================

enum
{
	kAudioHardwarePropertyDevices							= 'dev#',
		//	a array of the AudioDeviceIDs available in the system
		
	kAudioHardwarePropertyDefaultInputDevice				= 'dIn ',
		//	the AudioDeviceID of the default input device
		
	kAudioHardwarePropertyDefaultOutputDevice				= 'dOut',
		//	the AudioDeviceID of the default output device

	kAudioHardwarePropertyDefaultSystemOutputDevice			= 'sOut',
		//	the AudioDeviceID of the default system output device
		//	Services that generate audio as a system service, like
		//	PlayAlertSound() or digial call progress should use this device.
	
	kAudioHardwarePropertyDeviceForUID						= 'duid',
		//	retrieves the AudioDeviceID for the given device
		//	unique identifier previously retrieved with
		//	kAudioDevicePropertyUID (see below) using an
		//	AudioValueTranslation structure. The input is a
		//	CFStringRef containing the UID and the output
		//	is an AudioDeviceID. If a device that matches the
		//	given UID isn't present, kAudioDeviceUnknown will
		//	be returned as the AudioDeviceID.

	kAudioHardwarePropertySleepingIsAllowed					= 'slep',
		//	A UInt32 where 1 means this process will allow the
		//	machine to sleep and 0 will keep the machine awake.
		//	Note that the machine can still be forced to go to
		//	sleep regardless of the setting of this property.

	kAudioHardwarePropertyUnloadingIsAllowed				= 'unld',
		//	A UInt32 where 1 means this process will allow the
		//	HAL to unload after a period of inactivity if and
		//	only if there are no listeners or IOProcs registered
		//	anywhere.

	kAudioHardwarePropertyRunLoop							= 'rnlp',
		//	a CFRunLoopRef to which the client wishes the HAL to
		//	attach system notifications to. By default the HAL
		//	will attach it's system notifications to a thread
		//	that it creates and manages itself. This property can
		//	be used to override this selection. The HAL will move
		//	all it's currently attached notifications to the new
		//	run loop.
	
	kAudioHardwarePropertyBootChimeVolumeScalar				= 'bbvs',
		//	a Float32 between 0 and 1 that scales the volume of the boot chime
		//	across the full range of the device.

	kAudioHardwarePropertyBootChimeVolumeDecibels			= 'bbvd',
		//	a Float32 whose units are decibels where 0 represents unity,
		//	negative values for attenuation and positive values for gain.
	
	kAudioHardwarePropertyBootChimeVolumeRangeDecibels		= 'bbd#',
		//	an AudioValueRange specifying the minimum and maximum db values.
	
	kAudioHardwarePropertyBootChimeVolumeScalarToDecibels	= 'bv2d',
		//	convert the Float32 scalar volume to decibels

	kAudioHardwarePropertyBootChimeVolumeDecibelsToScalar	= 'bd2v'
		//	convert the Float32 decibel volume to scalar

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
		
	kAudioDevicePropertyPlugIn							= 'plug',
		//	a OSStatus containing any error codes generated from loading the driver
		//	plug-in or kAudioHardwareNoError if the plug-in loaded successfully.
		//	If the device/engine doesn't have a plug-in, then this property won't
		//	be present.
	
	kAudioDevicePropertyConfigurationApplication		= 'capp',
		//	a CFStringRef containing the bundle identifier to an application for 
		//	configuring the device. By default, this will be the Audio MIDI Setup
		//	application. Upon return, the caller is responsible for releasing the
		//	returned CFStringRef.
	
	kAudioDevicePropertyDeviceUID						= 'uid ',
		//	a CFStringRef that contains a unique identifier for the device.
		//	This ID is persistent and can be used from run to run of a process
		//	and across boots. Use kAudioHardwarePropertyDeviceForUID to
		//	retrieve the AudioDeviceID for the ID returned by this property.
		//	The caller is responsible for releasing the returned CFStringRef.
	
	kAudioDevicePropertyTransportType					= 'tran',
		//	a UInt32 holding a constant that indicates how the device is connected
		//	to the system. The constants returned here are defined in
		//	<IOKit/audio/IOAudioTypes.h>.
	
	kAudioDevicePropertyRelatedDevices					= 'akin',
		//	an array of AudioDeviceIDs for devices related to the given device.
		//	Note that this property won't exist for devices with no related devices.
		//	For IOAudio based devices, a device is "related" to another if they have
		//	the same IOAudioDevice object.
	
	kAudioDevicePropertyDeviceIsAlive					= 'livn',
		//	a UInt32 where 1 means the device is installed and ready
		//	to handle requests and 0 means the device has been removed
		//	or otherwise disconnected and is about to go away completely.
		//	After receiving notification on this property, any AudioDeviceID's
		//	referring to the destroyed device are invalid. It is highly
		//	recommended that all clients listen for this notification.
		
	kAudioDevicePropertyDeviceHasChanged				= 'diff',
		//	This property exists so that clients can be told when the configuration
		//	of a device has changed in ways that cannot be conveyed by notifications
		//	on other properties. An example is when a device reconfigures it's
		//	controls and makes them appear or disappear. In response to a notification
		//	on this property, a client should re-evaluate everything about the device,
		//	paricularly the layout and values of the controls. The value of this
		//	property is a UInt32, but it's value has no currently defined meaning.
	
	kAudioDevicePropertyDeviceIsRunning					= 'goin',
		//	a UInt32 where 0 means the device has no active IO procs
		//	in the process and 1 means the device has at least 1
		//	active IO proc in the process. The value of this property
		//	can be set. Setting the value to 0 equates to calling AudioDeviceStop(NULL)
		//	while setting the value to something other than one is equivalent to
		//	calling AudioDeviceStart(NULL).
	
	kAudioDevicePropertyDeviceIsRunningSomewhere		= 'gone',
		//	a UInt32 where 0 means the device is off and 1 means
		//	the device is running somewhere in the system
	
	kAudioDevicePropertyDeviceCanBeDefaultDevice		= 'dflt',
		//	a UInt32 where 0 means that the device cannot be selected as the default
		//	device and 1 menas that it can. The isInput argument selects which kind
		//	of default device is being queried.
	
	kAudioDevicePropertyDeviceCanBeDefaultSystemDevice	= 'sflt',
		//	a UInt32 where 0 means that the device cannot be selected as the default
		//	system device and 1 menas that it can. The isInput argument selects which
		//	kind of default system device is being queried. Note that this property can
		//	only be queried for output.
	
	kAudioDevicePropertyIOCycleUsage							= 'ncyc',
		//	A Float32 whose range is from 0 to 1. This value indicates how
		//	much of the client portion of the IO cycle the process will
		//	use. The client portion of the IO cycle is the portion of the
		//	cycle in which the device calls the IOProcs so this property does
		//	not the apply to the duration of the entire cycle.
		
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
		//	Note that input and output latency may differ. Further, streams
		//	may have additional latency so they should be queried as well.
		//	If both the device and the stream say they have latency, then
		//	the total latency for the stream is the device latency summed with
		//	the stream latency.
	
	kAudioDevicePropertyBufferSize						= 'bsiz',
		//	a UInt32 containing the size of the IO buffers in bytes
		//	This property is deprecated in favor of kAudioDevicePropertyBufferFrameSize
	
	kAudioDevicePropertyBufferSizeRange					= 'bsz#',
		//	an AudioValueRange specifying the minimum and maximum byte
		//	sizes that will be accepted for the device.
		//	This property is deprecated in favor of kAudioDevicePropertyBufferFrameSizeRange

	kAudioDevicePropertyBufferFrameSize					= 'fsiz',
		//	a UInt32 containing the size of the IO buffers in frames
		//	It is highly recommended that all clients listen for this
		//	notification.
	
	kAudioDevicePropertyBufferFrameSizeRange			= 'fsz#',
		//	an AudioValueRange specifying the minimum and maximum frame
		//	sizes that will be accepted for the device.
	
	kAudioDevicePropertyUsesVariableBufferFrameSizes	= 'vfsz',
		//	a UInt32 that, if implemented by a device, indicates that the sizes of the
		//	buffers passed to an IOProc will vary by a small amount. The value of this
		//	property will indicate the largest buffer that will be passed and 
		//	kAudioDevicePropertyBufferFrameSize will indicate the smallest buffer that
		//	will get passed to the IOProc.
		//	The usage of this property is narrowed to only allow for devices whose buffer
		//	sizes vary by small amounts greater than kAudioDevicePropertyBufferFrameSize.
		//	It is not intended to be a liscense for devices to be able to send buffers
		//	however they please. Rather, it is intended to allow for hardware whose
		//	natural rhythms lead to this necessity.
	
	kAudioDevicePropertyChannelName						= 'chnm',
		//	the name of the channel as a null terminated C-string
		
	kAudioDevicePropertyChannelNameCFString				= 'lchn',
		//	the name of the channel as a CFStringRef. The CFStringRef
		//	retrieved via this property must be released by the caller.
	
	kAudioDevicePropertyChannelCategoryName				= 'ccnm',
		//	the name of the channel's category as a null terminated C-string
		
	kAudioDevicePropertyChannelCategoryNameCFString		= 'lccn',
		//	the name of the channel's category as a CFStringRef. The CFStringRef
		//	retrieved via this property must be released by the caller.
	
	kAudioDevicePropertyChannelNumberName				= 'cnnm',
		//	the name of the channel's number as a null terminated C-string.
		
	kAudioDevicePropertyChannelNumberNameCFString		= 'lcnn',
		//	the name of the channel's number as a CFStringRef. The CFStringRef
		//	retrieved via this property must be released by the caller.
	
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
	
	kAudioDevicePropertySupportsMixing					= 'mix?',
		//	a UInt32 where a 1 means the device supports mixing and therefore
		//	can have any number of IOProcs attached to it. A 0 means that
		//	mixing is not supported and the device will only allow a single
		//	client to perform IO with it in the physical format of the device.
		//	Important! The value of this property is dynamic. Typically, the
		//	value will change according to the stream format(s) of the device
		//	as compressed formats, like AC-3, don't typically allow for mixing.
		//	When the value of this property changes, all current IOProcs will
		//	be removed from the device and the device will be stopped.
			
	kAudioDevicePropertyStreamConfiguration				= 'slay',
		//	This property returns the stream configuration of the device in
		//	an AudioBufferList (with the buffer pointers set to NULL) which
		//	describes the list of streams and the number of channels in each
		//	stream.	This corresponds to what will be passed into the IOProc.
		//	It is highly recommended that all clients listen for this notification.
	
	kAudioDevicePropertyIOProcStreamUsage				= 'suse',
		//	An AudioHardwareIOProcStreamUsage structure which details the
		//	stream usage of a given IO proc. If a stream is marked as not
		//	being used, the given IOProc will see a corresponding NULL buffer
		//	pointer in the AudioBufferList passed to it's IO proc. Note that
		//	the number of streams detailed in the AudioHardwareIOProcStreamUsage
		//	must include all the streams of that direction on the device. Also,
		//	when getting the value of the property, one must fill out the mIOProc
		//	field of the AudioHardwareIOProcStreamUsage with the address of the
		//	of the IOProc whose stream usage is to be retrieved.
	
	kAudioDevicePropertyPreferredChannelsForStereo		= 'dch2',
		//	An array of two UInt32s where the first UInt32 indicates the device
		//	channel number to use for the left channel and the second one
		//	indicates the device channel number to use for the right channel.
		//	This property applies to both the input and the output and the
		//	channels can be different for each. Further, there are no
		//	guarantees about the relationship between the two channels (ie.
		//	they may not be consecutive and may be in separate streams).
		//	This property won't be implemented for devices that have only
		//	a single channel.
	
	kAudioDevicePropertyPreferredChannelLayout			= 'srnd',
		//	an AudioChannelLayout that indicates how each channel of a device should
		//	be used.
			
	kAudioDevicePropertyNominalSampleRate				= 'nsrt',
		//	A Float64 that indicates the current nominal sample rate of the device.
	
	kAudioDevicePropertyAvailableNominalSampleRates		= 'nsr#',
		//	An array of AudioValueRange inidicating the valid ranges for the
		//	nominal sample rate of the device.
	
	kAudioDevicePropertyActualSampleRate				= 'asrt',
		//	A Float64 that indicates the current actual sample rate of the device
		//	as measured from it's time stamp stream. Note that the nominal sample
		//	rate will be returned when the device isn't running.
	
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
	
	kAudioDevicePropertyJackIsConnected					= 'jack',
		//	a UInt32 where 0 means the device/stream has nothing plugged into
		//	it's jack, and 1 means that it does.
		
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
	
	kAudioDevicePropertyStereoPan						= 'span',
		//	a Float32 where 0.0 is full "left", 1.0 is full "right" and 0.5 is center.
	
	kAudioDevicePropertyStereoPanChannels				= 'spn#',
		//	two UInt32s that indicate what channels are being panned between.

	kAudioDevicePropertyMute							= 'mute',
		//	a UInt32 where 0 means the device is not muted and 1 means
		//	the device is muted

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
	
	kAudioDevicePropertyClockSourceNameForIDCFString	= 'lcsn',
		//	Retrieves the name of a clock source for a given clock source ID
		//	using an AudioValueTranslation structure. The input data is the
		//	UInt32 holding the clock source ID and the output data is a CFStringRef.
		//	The CFStringRef retrieved via this property must be released
		//	by the caller.
	
	kAudioDevicePropertyPlayThru						= 'thru',
		//	a UInt32 where 0 means play through is off and 1 means
		//	play through is on

	kAudioDevicePropertyPlayThruVolumeScalar			= 'mvsc',
		//	a Float32 between 0 and 1 that scales the volume of the device/channel
		//	across the full range of the device.

	kAudioDevicePropertyPlayThruVolumeDecibels			= 'mvdb',
		//	a Float32 whose units are decibels where 0 represents unity,
		//	negative values for attenuation and positive values for gain.
	
	kAudioDevicePropertyPlayThruVolumeRangeDecibels		= 'mvd#',
		//	an AudioValueRange specifying the minimum and maximum db values.
	
	kAudioDevicePropertyPlayThruVolumeScalarToDecibels	= 'mv2d',
		//	convert the Float32 scalar volume to decibels

	kAudioDevicePropertyPlayThruVolumeDecibelsToScalar	= 'mv2s',
		//	convert the Float32 decibel volume to scalar
	
	kAudioDevicePropertyPlayThruStereoPan				= 'mspn',
		//	a Float32 where 0.0 is full "left", 1.0 is full "right" and 0.5 is center.
	
	kAudioDevicePropertyPlayThruStereoPanChannels		= 'msp#',
		//	two UInt32s that indicate what channels are being panned between.

	kAudioDevicePropertyPlayThruDestination				= 'mdds',
		//	a UInt32 which is the ID of the data source for the given channel
	
	kAudioDevicePropertyPlayThruDestinations			= 'mdd#',
		//	an array of the available UInt32 data source IDs for the given channel
	
	kAudioDevicePropertyPlayThruDestinationNameForID	= 'mddn',
		//	Retrieves the name of a data source for a given data source ID
		//	using an AudioValueTranslation structure. The input data is the
		//	UInt32 holding the data source ID and the output data is a buffer to
		//	hold the name as a null terminated string.
	
	kAudioDevicePropertyPlayThruDestinationNameForIDCFString	= 'mddc',
		//	Retrieves the name of a data source for a given data source ID
		//	using an AudioValueTranslation structure. The input data is the
		//	UInt32 holding the data source ID and the output data is a CFStringRef.
		//	The CFStringRef retrieved via this property must be released
		//	by the caller.

	kAudioDevicePropertyChannelNominalLineLevel				= 'nlvl',
		//	a UInt32 which is the ID of the nominal line level item for the given channel
	
	kAudioDevicePropertyChannelNominalLineLevels			= 'nlv#',
		//	an array of the available UInt32 nominal line level item IDs for the given channel
	
	kAudioDevicePropertyChannelNominalLineLevelNameForID	= 'cnlv',
		//	Retrieves the name of a channel nominal line level for a given nominal line level ID
		//	using an AudioValueTranslation structure. The input data is the UInt32 holding the
		//	nominal line level ID and the output data is a buffer to hold the name as a null
		//	terminated string.
	
	kAudioDevicePropertyChannelNominalLineLevelNameForIDCFString	= 'lcnl',
		//	Retrieves the name of a channel nominal line level for a given nominal line level ID
		//	using an AudioValueTranslation structure. The input data is the UInt32 holding the
		//	nominal line level ID and the output data is a CFStringRef. The CFStringRef retrieved
		//	via this property must be released by the caller.
	
	kAudioDevicePropertyDriverShouldOwniSub				= 'isub',
		//	a UInt32 where 0 means the driver should not claim ownership of any
		//	attached iSub and 1 means the driver should claim ownership. Note that
		//	this property is only valid for the built-in device and USB Audio devices.

	kAudioDevicePropertySubVolumeScalar					= 'svlm',
		//	a Float32 between 0 and 1 that scales the volume across the full range
		//	of the subwoofer for the given channel.

	kAudioDevicePropertySubVolumeDecibels				= 'svld',
		//	a Float32 indicating the volume of the subwoofer whose units are decibels
		//	 where 0 represents unity, negative values for attenuation and positive
		//	values for gain.
	
	kAudioDevicePropertySubVolumeRangeDecibels			= 'svd#',
		//	an AudioValueRange specifying the minimum and maximum db values in the
		//	subwoofer's range.
	
	kAudioDevicePropertySubVolumeScalarToDecibels		= 'sv2d',
		//	convert the Float32 scalar volume to decibels in the subwoofer's range

	kAudioDevicePropertySubVolumeDecibelsToScalar		= 'sd2v',
		//	convert the Float32 decibel volume to scalar in the subwoofer's range

	kAudioDevicePropertySubMute							= 'smut'
		//	a UInt32 where 0 means the subwoofer is not muted and 1 means
		//	the device is muted

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
		
	kAudioStreamPropertyTerminalType					= 'term',
		//	a UInt32 holding a constant that describes the general kind of functionality
		//	attached to the stream. The constants returned here are defined in
		//	<IOKit/audio/IOAudioTypes.h>.
		
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
		
	kAudioPropertyWildcardChannel						= 0xFFFFFFFFUL
		//	a wild card for the channel
};

//=============================================================================
//	Flags used for AudioDeviceStartAtTime and AudioDeviceGetNearestStartTime
//=============================================================================

enum
{
	kAudioDeviceStartTimeIsInputFlag					= (1L << 0),
		//	Set to indicate that the requested time refers to an input time.
		//	Clear to indicate that the requested time refers to an output time.

	kAudioDeviceStartTimeDontConsultDeviceFlag			= (1L << 1)
		//	Set to indicate that the device should not be consulted when determining
		//	the start time. Clear to indicate that the device should be consulted.
};


//=============================================================================
//	Errors
//
//  Note that the errors listed below are only a partial listing of the error
//  codes that the HAL API might return. The API can and will return other
//  codes that are not listed here from any API call.
//
//  Further, the HAL does not attach any specific meaning to any of the error
//  codes listed below unless specifically mentioned in the documentation for
//  a specific API call. Consequently, it is an application programming
//  mistake to write code that checks for a specific error code and to attach
//  any meaning to it other than the call that was made has failed unless the
//  documentation for that call says otherwise.
//
//  There are two exceptions to this: kAudioHardwareBadDeviceError and
//  kAudioHardwareBadStreamError. These two codes will be returned from a
//  call if and only if the AudioDeviceID or AudioStreamID passed to an API
//  call was invalid. 
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
	kAudioHardwareUnsupportedOperationError				= 'unop',
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
AudioHardwareUnload()																			AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;

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
								Boolean*				outWritable)							AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

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
							void*					outPropertyData)							AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

//-----------------------------------------------------------------------------
//	AudioHardwareSetProperty
//
//	Set the indicated property data. Global properties, by definition, don't
//	directly affect real time, so they don't need a time stamp.
//-----------------------------------------------------------------------------
	
extern OSStatus
AudioHardwareSetProperty(	AudioHardwarePropertyID	inPropertyID,
							UInt32					inPropertyDataSize,
							void*					inPropertyData)								AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

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
									void*								inClientData)			AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

//-----------------------------------------------------------------------------
//	AudioHardwareRemovePropertyListener
//
//	Remove the given notification.
//-----------------------------------------------------------------------------

extern OSStatus
AudioHardwareRemovePropertyListener(	AudioHardwarePropertyID				inPropertyID,
										AudioHardwarePropertyListenerProc	inProc)				AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
//	This is a client supplied routine that the HAL calls to do an
//	IO transaction for a given device. All input and output is presented
//	to the client simultaneously for processing. The inNow parameter
//	is the time that should be used as the basis of now rather than
//	what might be provided by a query to the device's clock. This is necessary
//	because time will continue to advance while this routine is executing
//	making retrieving the current time from the appropriate parameter
//	unreliable for synch operations. The time stamp for theInputData represents
//	when the data was recorded. For the output, the time stamp represents
//	when the first sample will be played. In all cases, each time stamp is
//	accompanied by its mapping into host time.
//
//	The format of the actual data depends of the sample format of the streams
//	on the device as specified by its properties. It may be raw or compressed,
//	interleaved or not interleaved as determined by the requirements of the
//	device and its settings.
//
//	If the data for either the input or the output is invalid, the time stamp
//	will have a value of 0. This happens when a device doesn't have any inputs
//	or outputs.
//
//	On exiting, the IOProc should set the mDataByteSize field of each AudioBuffer
//	(if any) in the output AudioBufferList. On input, this value is set to the
//	size of the buffer, so it will only need to be changed for cases where
//	the number of bytes for the buffer size (kAudioDevicePropertyBufferFrameSize)
//	of the IO transaction. This may be the case for compressed formats like AC-3.
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
						void*				inClientData)										AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

//-----------------------------------------------------------------------------
//	AudioDeviceRemoveIOProc
//
//	Remove the given IO proc for the given device.
//-----------------------------------------------------------------------------

extern OSStatus
AudioDeviceRemoveIOProc(AudioDeviceID inDevice, AudioDeviceIOProc inProc)						AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

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
AudioDeviceStart(AudioDeviceID inDevice, AudioDeviceIOProc inProc)								AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

//-----------------------------------------------------------------------------
//	AudioDeviceStartAtTime
//
//	Start up the given IOProc and align the IO cycle of the device with the
//	given time.
//
//	On entry, ioRequestedStartTime is the requested time for the first sample of output for
//	the given IOProc. On exit, ioRequestedStartTime is the time that will actually be the
//	first sample of the given IOProc.
//
//	If the kAudioDeviceStartTimeIsInputFlag is set in the inFlags argument, then
//	ioRequestedStartTime refers to an input time. If kAudioDeviceStartTimeIsInputFlag is
//	clear in the inFlags argument, then ioRequestedStartTime refers to an output time.
//
//	The HAL and the device's driver reserve the right to modify the requested
//	time to an equal or later time, as dictated by the constraints of the system.
//	For instance, the driver of a device that provides both audio and video data
//	may only allow start times that coincide with the edge of a video frame. Also,
//	if the device already has one or more active IOProcs, the start time will be
//	shifted to the beginning of the next IOCycle so as not to cause discontinuities
//	in the existing IOProcs. Another reason the start time may shift is to allow for
//	aligning the buffer accesses in an optimal fashion (i.e. for Altivec).
//
//	Clients that wish to not involved the device's driver in determining the start time
//	can set the kAudioDeviceStartTimeDontConsultDeviceFlag in the inFlags argument.
//
//	Clients intending to make use of this call must have previously started the
//	hardware (usually by passing NULL for the IOProc to AudioDeviceStart or
//	AudioDeviceStartAtTime) in order to engage the timing services of the device.
//
//	Passing NULL for ioRequestedStartTime, is equivalent to calling AudioDeviceStart.
//
//	Passing NULL for inProc will start the hardware, even though there
//	may be no IOProcs registered.
//
//	The HAL will return the error code, kAudioHardwareUnsupportedOperationError, if
//	the device in question does not support starting at a specific time and inProc
//	and ioRequestedStartTime are not NULL.
//-----------------------------------------------------------------------------

extern OSStatus
AudioDeviceStartAtTime(	AudioDeviceID		inDevice,
						AudioDeviceIOProc	inProc,
						AudioTimeStamp*		ioRequestedStartTime,
						UInt32				inFlags)											AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

//-----------------------------------------------------------------------------
//	AudioDeviceStop
//
//	Stop the given IOProc.
//-----------------------------------------------------------------------------

extern OSStatus
AudioDeviceStop(AudioDeviceID inDevice, AudioDeviceIOProc inProc)								AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

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
//
//	The HAL will return the error code, kAudioHardwareUnsupportedOperationError, if
//	the device in question does not support starting at a specific time.
//-----------------------------------------------------------------------------

extern OSStatus
AudioDeviceRead(	AudioDeviceID			inDevice,
					const AudioTimeStamp*   inStartTime,
					AudioBufferList*		outData)											AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;

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
AudioDeviceGetCurrentTime(AudioDeviceID inDevice, AudioTimeStamp* outTime)						AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

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
							AudioTimeStamp*			outTime)									AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

//-----------------------------------------------------------------------------
//	AudioDeviceGetNearestStartTime
//
//	On entry, ioRequestedStartTime is the requested time for the first sample of output for
//	the given IOProc. On exit, ioRequestedStartTime is the time that will actually be the
//	first sample of the given IOProc.
//
//	If the kAudioDeviceStartTimeIsInputFlag is set in the inFlags argument, then
//	ioRequestedStartTime refers to an input time. If kAudioDeviceStartTimeIsInputFlag is
//	clear in the inFlags argument, then ioRequestedStartTime refers to an output time.
//
//	The HAL and the device's driver reserve the right to modify the requested
//	time to an equal or later time, as dictated by the constraints of the system.
//	For instance, the driver of a device that provides both audio and video data
//	may only allow start times that coincide with the edge of a video frame. Also,
//	if the device already has one or more active IOProcs, the start time will be
//	shifted to the beginning of the next IOCycle so as not to cause discontinuities
//	in the existing IOProcs. Another reason the start time may shift is to allow for
//	aligning the buffer accesses in an optimal fashion (i.e. for Altivec).
//
//	Clients that wish to not involved the device's driver in determining the start time
//	can set the kAudioDeviceStartTimeDontConsultDeviceFlag in the inFlags argument.
//
//	Clients intending to make use of this call must have previously started the
//	hardware (usually by passing NULL for the IOProc to AudioDeviceStart or
//	AudioDeviceStartAtTime) in order to engage the timing services of the device.
//
//	The HAL will return the error code, kAudioHardwareUnsupportedOperationError, if
//	the device in question does not support starting at a specific time.
//-----------------------------------------------------------------------------

extern OSStatus
AudioDeviceGetNearestStartTime(	AudioDeviceID	inDevice,
								AudioTimeStamp*	ioRequestedStartTime,
								UInt32			inFlags)										AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

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
							Boolean*				outWritable)								AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

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
						void*					outPropertyData)								AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

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
						const void*				inPropertyData)									AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

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
								void*							inClientData)					AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

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
									AudioDevicePropertyListenerProc	inProc)						AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

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
							Boolean*				outWritable)								AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;

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
						void*					outPropertyData)								AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;

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
						const void*				inPropertyData)									AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;

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
								void*							inClientData)					AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;

//-----------------------------------------------------------------------------
//	AudioStreamRemovePropertyListener
//
//	Remove the given notification.
//-----------------------------------------------------------------------------

extern OSStatus
AudioStreamRemovePropertyListener(	AudioStreamID					inStream,
									UInt32							inChannel,
									AudioDevicePropertyID			inPropertyID,
									AudioStreamPropertyListenerProc	inProc)						AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;

#if defined(__cplusplus)
}
#endif

#if PRAGMA_ENUM_ALWAYSINT
	#pragma enumsalwaysint reset
#endif

#endif
