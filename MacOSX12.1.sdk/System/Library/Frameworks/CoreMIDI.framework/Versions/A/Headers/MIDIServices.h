/*
 	File:   	CoreMIDI/MIDIServices.h
 
 	Contains:   API for communicating with MIDI hardware with Universal MIDI Packets (UMP).
 
 	Copyright:  (c) 2000-2020 by Apple Inc., all rights reserved.
 
 	Bugs?:  	For bug reports, consult the following page on
 				the World Wide Web:
 
 					http://feedbackassistant.apple.com/
 
*/
#ifndef __MIDIServices_h__
#define __MIDIServices_h__

/*!
	@header MIDIServices.h

	This is the header file for Mac OS X's MIDI system services.

	API Overview
	------------
	
	Drivers own and control Devices, e.g. USB interfaces, PCI cards, etc.  A device is defined
	as a physical object that would be represented by a single icon if there were a graphical
	view of the studio.

	Devices may have multiple logically distinct sub-components, e.g. a MIDI synthesizer and a
	pair of MIDI ports, both addressable via a USB port. These are called Entities.

	Entities have any number of Endpoints, sources and destinations of 16-channel MIDI streams.
	By grouping a device's endpoints into entities, the system has enough information for an
	application to make reasonable default assumptions about how to communicate in a
	bi-directional manner with each entity, as is necessary in MIDI librarian applications.

	CoreMIDI attaches a collection of properties to each object it manages. Some properties are
	dynamic characteristics of a device (e.g. MIDI receive channel and system-exclusive ID's),
	and some are a matter of user preference (choice of icon, whether the device should appear
	in lists of possible controllers). Other properties are static and could be looked up in a
	database, using the device's manufacturer and model names as a key.

	Implementation overview
	-----------------------
	
	The client API is implemented as the CoreMIDI framework, which uses IPC to communicate with
	a server process, MIDIServer.

	The server process loads, and manages all communication with, MIDI drivers.

	"Drivers" are not I/O Kit drivers.  They are bundles containing CFPlugins.

	Many MIDI drivers can simply be user-side I/O Kit clients (probably for serial, USB,
	Firewire).

	PCI card drivers will need their MIDI drivers to communicate with a separate kernel
	extension.

	Note about CoreFoundation data types (CFString, CFData, CFDictionary)
	---------------------------------------------------------------------
	
	When passing a CF object to a MIDI function, the MIDI function will never consume a
	reference to the object; the caller always retains a reference which it is responsible for
	releasing with CFRelease().

	When receiving a CF object as a return value from a MIDI function, the caller always
	receives a new reference to the object, and is responsible for releasing it.
*/

//=============================================================================
#pragma mark    Includes

#include <Availability.h>
#include <CoreFoundation/CoreFoundation.h>
#include <stddef.h>

CF_ASSUME_NONNULL_BEGIN

#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================
#pragma mark	Error Constants
/*!
    @enum           Error Constants
    @abstract       The error constants unique to Core MIDI.
    @discussion     These are the error constants that are unique to Core MIDI. Note that Core MIDI
                    functions may return other codes that are not listed here.
 
	@constant		kMIDIInvalidClient
						An invalid MIDIClientRef was passed.
	@constant		kMIDIInvalidPort
						An invalid MIDIPortRef was passed.
	@constant		kMIDIWrongEndpointType
						A source endpoint was passed to a function expecting a destination, or vice versa.
	@constant		kMIDINoConnection
						Attempt to close a non-existant connection.
	@constant		kMIDIUnknownEndpoint
						An invalid MIDIEndpointRef was passed.
	@constant		kMIDIUnknownProperty
						Attempt to query a property not set on the object.
	@constant		kMIDIWrongPropertyType
						Attempt to set a property with a value not of the correct type.
	@constant		kMIDINoCurrentSetup
						Internal error; there is no current MIDI setup object.
	@constant		kMIDIMessageSendErr
						Communication with MIDIServer failed.
	@constant		kMIDIServerStartErr
						Unable to start MIDIServer.
	@constant		kMIDISetupFormatErr
						Unable to read the saved state.
	@constant		kMIDIWrongThread
						A driver is calling a non-I/O function in the server from a thread other than
						the server's main thread.
	@constant		kMIDIObjectNotFound
						The requested object does not exist.
	@constant		kMIDIIDNotUnique
						Attempt to set a non-unique kMIDIPropertyUniqueID on an object.
    @constant       kMIDINotPermitted
	                    The process does not have privileges for the requested operation.
	@constant       kMIDIUnknownError
 						Internal error; unable to perform the requested operation.

*/
CF_ENUM(OSStatus) {
	kMIDIInvalidClient		= -10830,
	kMIDIInvalidPort		= -10831,
	kMIDIWrongEndpointType	= -10832,
	kMIDINoConnection		= -10833,
	kMIDIUnknownEndpoint	= -10834,
	kMIDIUnknownProperty	= -10835,
	kMIDIWrongPropertyType	= -10836,
	kMIDINoCurrentSetup		= -10837,
	kMIDIMessageSendErr		= -10838,
	kMIDIServerStartErr		= -10839,
	kMIDISetupFormatErr		= -10840,
	kMIDIWrongThread		= -10841,
	kMIDIObjectNotFound		= -10842,
	kMIDIIDNotUnique		= -10843,
	kMIDINotPermitted       = -10844,
	kMIDIUnknownError		= -10845
};

//=============================================================================
#pragma mark	Types

/*!
	@typedef		MIDIObjectRef
	@abstract		The base class of many CoreMIDI objects.
	@discussion
		MIDIObject is the base class for many of the objects in CoreMIDI.  They have properties,
		and often an "owner" object, from which they inherit any properties they do not
		themselves have.

		Developers may add their own private properties, whose names must begin with their
		company's inverted domain name, as in Java package names, but with underscores instead
		of dots, e.g.: com_apple_APrivateAppleProperty
*/
typedef UInt32 MIDIObjectRef;

/*!
	@typedef		MIDIClientRef
	@abstract		An object maintaining per-client state.
	@discussion
		Derives from MIDIObjectRef, does not have an owner object.

		To use CoreMIDI, an application creates a MIDIClientRef, to which it can add
		MIDIPortRef's, through which it can send and receive MIDI.
*/
typedef MIDIObjectRef MIDIClientRef;

/*!
	@typedef		MIDIPortRef
	@abstract		A MIDI connection port owned by a client.
	@discussion
		Derives from MIDIObjectRef, owned by a MIDIClientRef.

		A MIDIPortRef, which may be an input port or output port, is an object through which a
		client may communicate with any number of MIDI sources or destinations.
*/
typedef MIDIObjectRef MIDIPortRef;

/*!
	@typedef		MIDIDeviceRef
	@abstract		A MIDI device or external device, containing entities.
	@discussion
		Derives from MIDIObjectRef, does not have an owner object.

		A MIDI device, which either attaches directly to the computer and is controlled by a
		MIDI driver, or which is "external," meaning that it is connected to a driver-controlled
		device via a standard MIDI cable.

		A MIDIDeviceRef has properties and contains MIDIEntityRef's.
*/
typedef MIDIObjectRef MIDIDeviceRef;

/*!
	@typedef		MIDIEntityRef
	@abstract		A MIDI entity, owned by a device, containing endpoints.
	@discussion
		Derives from MIDIObjectRef, owned by a MIDIDeviceRef.

		Devices may have multiple logically distinct sub-components, e.g. a MIDI synthesizer and
		a pair of MIDI ports, both addressable via a USB port.

		By grouping a device's endpoints into entities, the system has enough information for an
		application to make reasonable assumptions about how to communicate in a bi-directional
		manner with each entity, as is desirable in MIDI librarian applications.

		These sub-components are MIDIEntityRef's.
*/
typedef MIDIObjectRef MIDIEntityRef;

/*!
	@typedef		MIDIEndpointRef
	@abstract		A MIDI source or destination, owned by an entity.
	@discussion
		Derives from MIDIObjectRef, owned by a MIDIEntityRef, unless it is a virtual endpoint,
		in which case there is no owning entity.

		Entities have any number of MIDIEndpointRef's, sources and destinations of 16-channel
		MIDI streams.
*/
typedef MIDIObjectRef MIDIEndpointRef;

/*!
	@typedef		MIDITimeStamp
	@abstract		A host clock time.
	@discussion
		A host clock time representing the time of an event, as returned by
		mach_absolute_time() or UpTime().

		Since MIDI applications will tend to do a fair amount of math with the times of events,
		it's more convenient to use a UInt64 than an AbsoluteTime.
 
		See CoreAudio/HostTime.h.
*/
typedef UInt64							MIDITimeStamp;

/*!
	@enum			MIDIObjectType
	@abstract		Signifies the type of a MIDIObject.
	@discussion
		Signifies the real type of a MIDIObjectRef instance.
*/
typedef CF_ENUM(SInt32, MIDIObjectType) {
	kMIDIObjectType_Other				= -1,
	kMIDIObjectType_Device				= 0,
	kMIDIObjectType_Entity				= 1,
	kMIDIObjectType_Source				= 2,
	kMIDIObjectType_Destination			= 3,

	kMIDIObjectType_ExternalDevice		= 0x10 | kMIDIObjectType_Device,
	kMIDIObjectType_ExternalEntity		= 0x10 | kMIDIObjectType_Entity,
	kMIDIObjectType_ExternalSource		= 0x10 | kMIDIObjectType_Source,
	kMIDIObjectType_ExternalDestination	= 0x10 | kMIDIObjectType_Destination
};
static const MIDIObjectType kMIDIObjectType_ExternalMask		= (MIDIObjectType)0x10;

/*!
	@typedef		MIDIUniqueID
	@abstract		A unique identifier for a MIDIObjectRef.
	@discussion
		An integer which uniquely identifies a MIDIObjectRef.
*/
typedef SInt32							MIDIUniqueID;

CF_ENUM(MIDIUniqueID) {
	kMIDIInvalidUniqueID = 0
};

/*!
	@enum		MIDIProtocolID
	@abstract	Specifies a MIDI protocol variant.
	@var		kMIDIProtocol_1_0
					MIDI 1.0.
	@var		kMIDIProtocol_2_0
					MIDI 2.0.
*/
typedef CF_ENUM(SInt32, MIDIProtocolID) {
	kMIDIProtocol_1_0 = 1,
	kMIDIProtocol_2_0 = 2,
};

// forward structure declarations
typedef struct MIDIEventList			MIDIEventList;			// Universal MIDI Packet
typedef struct MIDIPacketList			MIDIPacketList;			// Legacy MIDI 1.0 Packets (deprecated)
typedef struct MIDISysexSendRequest		MIDISysexSendRequest;
typedef struct MIDINotification			MIDINotification;

//=============================================================================
#pragma mark	Callback Functions

/*!
	@typedef		MIDINotifyProc
	@abstract		A callback function for notifying clients of state changes.
	@discussion
		This callback function is called when some aspect of the current MIDI setup changes. It
		is called on the runloop (thread) on which MIDIClientCreate was first called.

	@param			message
						A structure containing information about what changed.
	@param			refCon
						The client's refCon passed to MIDIClientCreate.
*/
typedef void
(*MIDINotifyProc)(const MIDINotification *message, void * __nullable refCon);

/*!
	@typedef		MIDINotifyBlock
	@abstract		A callback block for notifying clients of state changes.
	@discussion
		This block is called when some aspect of the current MIDI setup changes. It
		is called on an arbitrary thread chosen by the implementation; thread-safety
		is the responsibility of the block.

	@param			message
						A structure containing information about what changed.
*/
typedef void
(^MIDINotifyBlock)(const MIDINotification *message);

/*!
	@typedef		MIDIReceiveBlock
	@abstract		A block receiving MIDI input.
	@discussion
		This is a callback block through which a client receives incoming MIDI messages.

		A MIDIReceiveBlock is passed to the MIDIInputPortCreateWithProtocol and
		MIDIDestinationCreateWithProtocol functions.  The CoreMIDI framework will create a
		high-priority receive thread on your client's behalf, and from that thread, your
		MIDIReceiveBlock will be called when incoming MIDI messages arrive.

	@param			evtlist
						The incoming MIDI message(s).
	@param			srcConnRefCon
						A refCon you passed to MIDIPortConnectSource, which
						identifies the source of the data.
*/
typedef void
(^MIDIReceiveBlock)(const MIDIEventList *evtlist, void * __nullable srcConnRefCon);

/*!
	@typedef		MIDIReadProc
	@abstract		A function receiving MIDI input.
	@discussion
		This is a callback function through which a client receives incoming MIDI messages.

		A MIDIReadProc function pointer is passed to the MIDIInputPortCreate and
		MIDIDestinationCreate functions.  The CoreMIDI framework will create a high-priority
		receive thread on your client's behalf, and from that thread, your MIDIReadProc will be
		called when incoming MIDI messages arrive.

	@param			pktlist
						The incoming MIDI message(s).
	@param			readProcRefCon
						The refCon you passed to MIDIInputPortCreate or
						MIDIDestinationCreate
	@param			srcConnRefCon
						A refCon you passed to MIDIPortConnectSource, which
						identifies the source of the data.
*/
typedef void
(*MIDIReadProc)(const MIDIPacketList *pktlist, void * __nullable readProcRefCon, void * __nullable srcConnRefCon) API_DEPRECATED("use MIDIReceiveBlock and MIDIEventLists", macos(10.0, API_TO_BE_DEPRECATED), ios(4.2, API_TO_BE_DEPRECATED)) __TVOS_PROHIBITED __WATCHOS_PROHIBITED;

/*!
	@typedef		MIDIReadBlock
	@abstract		A block receiving MIDI input.
	@discussion
		This is a callback block through which a client receives incoming MIDI messages.

		A MIDIReadBlock is passed to the MIDIInputPortCreateWithBlock and
		MIDIDestinationCreateWithBlock functions.  The CoreMIDI framework will create a
		high-priority receive thread on your client's behalf, and from that thread, your
		MIDIReadProc will be called when incoming MIDI messages arrive.

	@param			pktlist
						The incoming MIDI message(s).
	@param			srcConnRefCon
						A refCon you passed to MIDIPortConnectSource, which
						identifies the source of the data.
*/
typedef void
(^MIDIReadBlock)(const MIDIPacketList *pktlist, void * __nullable srcConnRefCon) API_DEPRECATED("use MIDIReceiveBlock and MIDIEventLists", macos(10.11, API_TO_BE_DEPRECATED), ios(9.0, API_TO_BE_DEPRECATED)) __TVOS_PROHIBITED __WATCHOS_PROHIBITED;

/*!
	@typedef		MIDICompletionProc
	@abstract		A function called when a system-exclusive event has been completely sent.
	@discussion
		Callback function to notify the client of the completion of a call to MIDISendSysex.
 
	@param			request
						The MIDISysexSendRequest which has completed, or been
						aborted.
*/
typedef void
(*MIDICompletionProc)(MIDISysexSendRequest *request);

//=============================================================================
#pragma mark	Structures

#pragma pack(push, 4)
/*!
	@struct			MIDIEventPacket
	@abstract		A series of simultaneous MIDI events in UMP format.
 
	@field			timeStamp
						The time at which the events occurred, if receiving MIDI,
						or, if sending MIDI, the time at which the events are to
						be played.  Zero means "now."  The time stamp applies
						to the first byte or word in the packet.
	@field			wordCount
						The number of valid MIDI 32-bit words which follow, in data. (It
						may be larger than 64 words if the packet is dynamically
						allocated.)
	@field			words
						A variable-length stream of native-endian 32-bit Universal MIDI Packets.
                        Running status is not allowed.  In the case of system-exclusive
                        messages, a packet may only contain a single message, or portion
                        of one, with no other MIDI events.
 
                        Messages must always be syntactically complete; for example, for 64-bit
                        message types, both words must be present in the same packet. The same
                        MIDI message constraints from above apply here.
 
                        (This is declared to be 64 words in length so clients don't have to
                        create custom data structures in simple situations.)
*/
struct MIDIEventPacket
{
	MIDITimeStamp timeStamp;
	UInt32 wordCount;
	UInt32 words[64];
};
typedef struct MIDIEventPacket		MIDIEventPacket;

/*!
	@struct			MIDIEventList
	@abstract		A variable-length list of MIDIEventPackets.

	The timestamps in the list must be in ascending order.

	Note that the packets in the list, while defined as an array, may not be
	accessed as an array, since they are variable-length.  To iterate through
	the packets in an event list, use a loop such as:

	```
	MIDIEventPacket *packet = &packetList->packet[0];
	for (unsigned i = 0; i < packetList->numPackets; ++i) {
		...
		packet = MIDIEventPacketNext(packet);
	}
	```

	@field	protocol
 				The MIDI protocol variant of the events in the list.
	@field	numPackets
				The number of MIDIEventPacket structs in the list.
	@field	packet
				An open-ended array of variable-length MIDIEventPacket structs.
*/
struct MIDIEventList
{
	MIDIProtocolID protocol;
	UInt32 numPackets;
	MIDIEventPacket packet[1];
};
typedef struct MIDIEventList MIDIEventList;

/*!
	@struct			MIDIPacket
	@abstract		A collection of simultaneous MIDI events.
 
	@field			timeStamp
						The time at which the events occurred, if receiving MIDI,
						or, if sending MIDI, the time at which the events are to
						be played.  Zero means "now."  The time stamp applies
						to the first MIDI byte in the packet.
	@field			length
						The number of valid MIDI bytes which follow, in data. (It
						may be larger than 256 bytes if the packet is dynamically
						allocated.)
	@field			data
						A variable-length stream of MIDI messages.  Running status
						is not allowed.  In the case of system-exclusive
						messages, a packet may only contain a single message, or
						portion of one, with no other MIDI events.
 
						The MIDI messages in the packet must always be complete,
						except for system-exclusive.

						(This is declared to be 256 bytes in length so clients
						don't have to create custom data structures in simple
						situations.)
*/
struct MIDIPacket
{
	MIDITimeStamp		timeStamp;
	UInt16				length;
	Byte				data[256];
};
typedef struct MIDIPacket			MIDIPacket;

/*!
	@struct			MIDIPacketList
	@abstract		A list of MIDI events being received from, or being sent to,
					one endpoint.

	The timestamps in the packet list must be in ascending order.

	Note that the packets in the list, while defined as an array, may not be
	accessed as an array, since they are variable-length.  To iterate through
	the packets in a packet list, use a loop such as:
	
	```
	MIDIPacket *packet = &packetList->packet[0];
	for (unsigned i = 0; i < packetList->numPackets; ++i) {
		...
		packet = MIDIPacketNext(packet);
	}
	```
	
	The MIDIPacketNext macro is especially important when considering that
	the alignment requirements of MIDIPacket may differ between CPU architectures.
	On Intel and PowerPC, MIDIPacket is unaligned. On ARM, MIDIPacket must be
	4-byte aligned.
 
	@field			numPackets
						The number of MIDIPackets in the list.
	@field			packet
						An open-ended array of variable-length MIDIPackets.
*/
struct MIDIPacketList
{
	UInt32  			numPackets;
	MIDIPacket  		packet[1];
};
#pragma pack(pop)

/*!
	@struct			MIDISysexSendRequest
	@abstract		A request to transmit a system-exclusive event.
 
	@discussion
		This represents a request to send a single system-exclusive MIDI event to
		a MIDI destination asynchronously.

	@field			destination
						The endpoint to which the event is to be sent.
	@field			data
						Initially, a pointer to the sys-ex event to be sent.
						MIDISendSysex will advance this pointer as bytes are
						sent.
	@field			bytesToSend
						Initially, the number of bytes to be sent.  MIDISendSysex
						will decrement this counter as bytes are sent.
	@field			complete
						The client may set this to true at any time to abort
						transmission.  The implementation sets this to true when
						all bytes have been sent.
	@field			completionProc
						Called when all bytes have been sent, or after the client
						has set complete to true.
	@field			completionRefCon
						Passed as a refCon to completionProc.
*/
struct MIDISysexSendRequest
{
	MIDIEndpointRef		destination;
	const Byte *  		data;
	UInt32				bytesToSend;
	Boolean				complete;
	Byte				reserved[3];
	MIDICompletionProc 	completionProc;
	void * __nullable	completionRefCon;
};

/*!
	@enum		MIDINotificationMessageID
	@abstract	Signifies the type of a MIDINotification.

	@constant	kMIDIMsgSetupChanged
		Some aspect of the current MIDISetup has changed.  No data.  Should ignore this message if
		messages 2-6 are handled.
	@constant	kMIDIMsgObjectAdded
		A device, entity or endpoint was added. Structure is MIDIObjectAddRemoveNotification. New in
		Mac OS X 10.2.
	@constant	kMIDIMsgObjectRemoved
		A device, entity or endpoint was removed. Structure is MIDIObjectAddRemoveNotification. New
		in Mac OS X 10.2.
	@constant	kMIDIMsgPropertyChanged
		An object's property was changed. Structure is MIDIObjectPropertyChangeNotification. New in
		Mac OS X 10.2.
	@constant	kMIDIMsgThruConnectionsChanged
		A persistent MIDI Thru connection was created or destroyed.  No data.  New in Mac OS X 10.2.
	@constant	kMIDIMsgSerialPortOwnerChanged
		No data.  New in Mac OS X 10.2.
	@constant	kMIDIMsgIOError
		A driver I/O error occurred.
*/
typedef CF_ENUM(SInt32, MIDINotificationMessageID) {
	kMIDIMsgSetupChanged			= 1,
	kMIDIMsgObjectAdded				= 2,
	kMIDIMsgObjectRemoved			= 3,
	kMIDIMsgPropertyChanged			= 4,
	kMIDIMsgThruConnectionsChanged	= 5,
	kMIDIMsgSerialPortOwnerChanged	= 6,
	kMIDIMsgIOError					= 7
};


/*!
	@struct			MIDINotification
	@abstract		A message describing a system state change.
	@discussion
		A MIDINotification is a structure passed to a MIDINotifyProc or MIDINotifyBlock, when
		CoreMIDI wishes to inform a client of a change in the state of the system.
 
	@field			messageID
						type of message
	@field			messageSize
						size of the entire message, including messageID and
						messageSize
*/
struct MIDINotification
{
	MIDINotificationMessageID	messageID;
	UInt32						messageSize;
	// additional data may follow, depending on messageID
};

/*!
	@struct			MIDIObjectAddRemoveNotification
	@abstract		A message describing the addition or removal of an object.
 
	@field			messageID
						type of message
	@field			messageSize
						size of the entire message, including messageID and messageSize
	@field			parent
						the parent of the added or removed object (possibly NULL)
	@field			parentType
						the type of the parent object (undefined if parent is NULL)
	@field			child
						the added or removed object
	@field			childType
						the type of the added or removed object
*/
struct MIDIObjectAddRemoveNotification
{
	MIDINotificationMessageID	messageID;
	UInt32						messageSize;
	MIDIObjectRef				parent;
	MIDIObjectType				parentType;
	MIDIObjectRef				child;
	MIDIObjectType				childType;
};
typedef struct MIDIObjectAddRemoveNotification MIDIObjectAddRemoveNotification;

/*!
	@struct			MIDIObjectPropertyChangeNotification
	@abstract		A message describing the addition or removal of an object.
 
	@field			messageID
						type of message
	@field			messageSize
						size of the entire message, including messageID and messageSize
	@field			object
						the object whose property has changed
	@field			objectType
						the type of the object whose property has changed
	@field			propertyName
						the name of the changed property
*/
struct MIDIObjectPropertyChangeNotification
{
	MIDINotificationMessageID	messageID;
	UInt32						messageSize;
	MIDIObjectRef				object;
	MIDIObjectType				objectType;
	CFStringRef					propertyName;
};
typedef struct MIDIObjectPropertyChangeNotification MIDIObjectPropertyChangeNotification;

struct MIDIIOErrorNotification
{
	MIDINotificationMessageID	messageID;
	UInt32						messageSize;
	MIDIDeviceRef				driverDevice;
	OSStatus					errorCode;
};
typedef struct MIDIIOErrorNotification MIDIIOErrorNotification;

//=============================================================================
//	Property name constants
//=============================================================================

/*!
	@constant		kMIDIPropertyName
	@discussion
		device/entity/endpoint property, string
 
		Devices, entities, and endpoints may all have names.  The recommended way to display an
		endpoint's name is to ask for the endpoint name, and display only that name if it is
		unique.  If it is non-unique, prepend the device name.

		A setup editor may allow the user to set the names of both driver-owned and external
		devices.
*/
extern const CFStringRef	kMIDIPropertyName					API_AVAILABLE(macos(10.0), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@constant		kMIDIPropertyManufacturer
	@discussion
		device/endpoint property, string

		Drivers should set this property on their devices.

		Setup editors may allow the user to set this property on external devices.

		Creators of virtual endpoints may set this property on their endpoints.
*/
extern const CFStringRef	kMIDIPropertyManufacturer			API_AVAILABLE(macos(10.0), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@constant		kMIDIPropertyModel
	@discussion
		device/endpoint property, string

		Drivers should set this property on their devices.

		Setup editors may allow the user to set this property on external devices.

		Creators of virtual endpoints may set this property on their endpoints.
*/
extern const CFStringRef	kMIDIPropertyModel					API_AVAILABLE(macos(10.0), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@constant		kMIDIPropertyUniqueID
	@discussion
		devices, entities, endpoints all have unique ID's, integer

		The system assigns unique ID's to all objects.  Creators of virtual endpoints may set
		this property on their endpoints, though doing so may fail if the chosen ID is not
		unique.
*/
extern const CFStringRef	kMIDIPropertyUniqueID				API_AVAILABLE(macos(10.0), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@constant		kMIDIPropertyDeviceID
	@discussion
		device/entity property, integer

		The entity's system-exclusive ID, in user-visible form

		Drivers may set this property on their devices or entities.

		Setup editors may allow the user to set this property on external devices.
*/
extern const CFStringRef	kMIDIPropertyDeviceID				API_AVAILABLE(macos(10.0), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@constant		kMIDIPropertyReceiveChannels
	@discussion
		endpoint property, integer

		The value is a bitmap of channels on which the object receives: 1=ch 1, 2=ch 2, 4=ch 3
		... 0x8000=ch 16.

		Drivers may set this property on their entities or endpoints.

		Setup editors may allow the user to set this property on external endpoints.

		Virtual destination may set this property on their endpoints.
*/
extern const CFStringRef	kMIDIPropertyReceiveChannels		API_AVAILABLE(macos(10.0), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@constant		kMIDIPropertyTransmitChannels
	@discussion
		endpoint property, integer

		The value is a bitmap of channels on which the object transmits: 1=ch 1, 2=ch 2, 4=ch 3
		... 0x8000=ch 16.
*/
extern const CFStringRef	kMIDIPropertyTransmitChannels		API_AVAILABLE(macos(10.2), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@constant		kMIDIPropertyMaxSysExSpeed
	@discussion
		device/entity/endpoint property, integer

		Set by the owning driver; should not be touched by other clients.
		The value is the maximum rate, in bytes/second, at which sysex messages may
		be sent reliably to this object. (The default value is 3125, as with MIDI 1.0)
*/
extern const CFStringRef	kMIDIPropertyMaxSysExSpeed			API_AVAILABLE(macos(10.0), ios(4.2)) API_UNAVAILABLE(tvos, watchos);


/*!
	@constant		kMIDIPropertyAdvanceScheduleTimeMuSec
	@discussion
		device/entity/endpoint property, integer

		Set by the owning driver; should not be touched by other clients. If it is non-zero,
		then it is a recommendation of how many microseconds in advance clients should schedule
		output. Clients should treat this value as a minimum.  For devices with a non-zero
		advance schedule time, drivers will receive outgoing messages to the device at the time
		they are sent by the client, via MIDISend, and the driver is responsible for scheduling
		events to be played at the right times according to their timestamps.

		As of CoreMIDI 1.3, this property may also be set on virtual destinations (but only the
		creator of the destination should do so). When a client sends to a virtual destination
		with an advance schedule time of 0, the virtual destination receives its messages at
		their scheduled delivery time.  If a virtual destination has a non-zero advance schedule
		time, it receives timestamped messages as soon as they are sent, and must do its own
		internal scheduling of received events.
*/
extern const CFStringRef	kMIDIPropertyAdvanceScheduleTimeMuSec	API_AVAILABLE(macos(10.0), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@constant		kMIDIPropertyIsEmbeddedEntity
	@discussion
		entity/endpoint property, integer

		0 if there are external MIDI connectors, 1 if not.
*/
extern const CFStringRef	kMIDIPropertyIsEmbeddedEntity			API_AVAILABLE(macos(10.1), ios(4.2)) API_UNAVAILABLE(tvos, watchos);


/*!
	@constant		kMIDIPropertyIsBroadcast
	@discussion
		entity/endpoint property, integer

		1 if the endpoint broadcasts messages to all of the other endpoints in the device, 0 if
		not.  Set by the owning driver; should not be touched by other clients.
*/
extern const CFStringRef	kMIDIPropertyIsBroadcast				API_AVAILABLE(macos(10.2), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@constant		kMIDIPropertySingleRealtimeEntity
	@discussion
		device property, integer

		Some MIDI interfaces cannot route MIDI realtime messages to individual outputs; they are
		broadcast.  On such devices the inverse is usually also true -- incoming realtime
		messages cannot be identified as originating from any particular source.

		When this property is set on a driver device, it signifies the 0-based index of the
		entity on which incoming realtime messages from the device will appear to have
		originated from.
*/
extern const CFStringRef	kMIDIPropertySingleRealtimeEntity		API_AVAILABLE(macos(10.2), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@constant		kMIDIPropertyConnectionUniqueID
	@discussion
		device/entity/endpoint property, integer or CFDataRef

		UniqueID of an external device/entity/endpoint attached to this one. As of Mac OS X
		10.3, Audio MIDI Setup maintains endpoint-to-external endpoint connections (in 10.2, it
		connected devices to devices).

		The property is non-existant or 0 if there is no connection.
 
		Beginning with CoreMIDI 1.3 (Mac OS X 10.2), this property may also be a CFDataRef containing an array of
		big-endian SInt32's, to allow specifying that a driver object connects to multiple
		external objects (via MIDI thru-ing or splitting).

		This property may also exist for external devices/entities/endpoints, in which case it
		signifies a MIDI Thru connection to another external device/entity/endpoint (again,
		it is strongly recommended that it be an endpoint).
*/
extern const CFStringRef	kMIDIPropertyConnectionUniqueID			API_AVAILABLE(macos(10.1), ios(4.2)) API_UNAVAILABLE(tvos, watchos);


/*!
	@constant		kMIDIPropertyOffline
	@discussion
		device/entity/endpoint property, integer

		1 = device is offline (is temporarily absent), 0 = present. Set by the owning driver, on
		the device; should not be touched by other clients. Property is inherited from the
		device by its entities and endpoints.
*/
extern const CFStringRef	kMIDIPropertyOffline					API_AVAILABLE(macos(10.1), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@constant		kMIDIPropertyPrivate
	@discussion
		device/entity/endpoint property, integer

		1 = endpoint is private, hidden from other clients. May be set on a device or entity,
		but they will still appear in the API; only affects whether the owned endpoints are
		hidden.
*/
extern const CFStringRef	kMIDIPropertyPrivate					API_AVAILABLE(macos(10.2), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@constant		kMIDIPropertyDriverOwner
	@discussion
		device/entity/endpoint property, string

		Name of the driver that owns a device. Set by the owning driver, on the device; should
		not be touched by other clients. Property is inherited from the device by its entities
		and endpoints.
*/
extern const CFStringRef	kMIDIPropertyDriverOwner				API_AVAILABLE(macos(10.1), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@constant		kMIDIPropertyFactoryPatchNameFile
	@discussion
		device/entity/endpoint property, CFData containing AliasHandle.

		An alias to the device's current factory patch name file.

		Added in CoreMIDI 1.1 (Mac OS X 10.1).  DEPRECATED as of CoreMIDI 1.3. Use
		kMIDIPropertyNameConfiguration instead.
*/
extern const CFStringRef	kMIDIPropertyFactoryPatchNameFile		API_DEPRECATED_WITH_REPLACEMENT("kMIDIPropertyNameConfiguration", macos(10.1, 10.2)) API_UNAVAILABLE(ios, tvos, watchos);


/*!
	@constant		kMIDIPropertyUserPatchNameFile
	@discussion
		device/entity/endpoint property, CFData containing AliasHandle

		An alias to the device's current user patch name file.

		Added in CoreMIDI 1.1 (Mac OS X 10.1).  DEPRECATED as of CoreMIDI 1.3. Use
		kMIDIPropertyNameConfiguration instead.
*/
extern const CFStringRef	kMIDIPropertyUserPatchNameFile			API_DEPRECATED_WITH_REPLACEMENT("kMIDIPropertyNameConfiguration", macos(10.1, 10.2)) API_UNAVAILABLE(ios, tvos, watchos);

/*!
	@constant		kMIDIPropertyNameConfiguration
	@discussion
		device/entity/endpoint property, CFDictionary

		This specifies the device's current patch, note and control name values using the
		MIDINameDocument XML format.  This specification requires the use of higher-level,
		OS-specific constructs outside of the specification to fully define the current names
		for a device.

		The MIDINameConfiguration property is implementated as a CFDictionary:

		key "master" maps to a CFDataRef containing an AliasHandle referring to the device's
		master name document. This is deprecated as of Mac OS X 10.10.
 
		key "masterDocumentPath" maps to a CFStringRef containing the filesystem path to the device's
		master name document. (This is new as of Mac OS X 10.10, but since the CoreMIDI
		implementation does not parse this dictionary, the convention can be safely ported
		to earlier versions of Mac OS X.)

		key "banks" maps to a CFDictionaryRef.  This dictionary's keys are CFStringRef names of
		patchBank elements in the master document, and its values are each a CFDictionaryRef:
		key "file" maps to a CFDataRef containing an AliasHandle to a document containing
		patches that override those in the master document, and key "patchNameList" maps to a
		CFStringRef which is the name of the patchNameList element in the overriding document.

		key "currentChannelNameSets" maps to a 16-element CFArrayRef, each element of which is a
		CFStringRef of the name of the current mode for each of the 16 MIDI channels.

		key "currentDeviceMode" maps to a CFStringRef containing the name of the device's mode.

		Clients setting this property must take particular care to preserve dictionary values
		other than the ones they are interested in changing and to properly structure the
		dictionary.
*/
extern const CFStringRef	kMIDIPropertyNameConfiguration			API_DEPRECATED_WITH_REPLACEMENT("kMIDIPropertyNameConfigurationDictionary", macos(10.2, 10.15), ios(4.2, 13.0)) __TVOS_PROHIBITED __WATCHOS_PROHIBITED;

/*!
    @constant        kMIDIPropertyNameConfigurationDictionary
    @discussion
        device/entity/endpoint property, CFDictionary

        This specifies the device's current patch, note and control name values using the
        MIDINameDocument XML format.  This specification requires the use of higher-level,
        OS-specific constructs outside of the specification to fully define the current names
        for a device.

        The MIDINameConfiguration property is implementated as a CFDictionary:

        key "masterDocumentPath" maps to a CFStringRef containing the filesystem path to the device's
        master name document.

        key "banks" maps to a CFDictionaryRef.  This dictionary's keys are CFStringRef names of
        patchBank elements in the master document, and its values are each a CFDictionaryRef:
        key "file" maps to a CFDataRef containing URL bookmark data to a document containing
        patches that override those in the master document, and key "patchNameList" maps to a
        CFStringRef which is the name of the patchNameList element in the overriding document.

        key "currentChannelNameSets" maps to a 16-element CFArrayRef, each element of which is a
        CFStringRef of the name of the current mode for each of the 16 MIDI channels.

        key "currentDeviceMode" maps to a CFStringRef containing the name of the device's mode.

        Clients setting this property must take particular care to preserve dictionary values
        other than the ones they are interested in changing and to properly structure the
        dictionary.
*/
extern const CFStringRef    kMIDIPropertyNameConfigurationDictionary            API_AVAILABLE(macos(10.15), ios(13.0)) API_UNAVAILABLE(tvos, watchos);

/*!
	@constant		kMIDIPropertyImage
	@discussion
		device property, CFStringRef which is a full POSIX path to a device or external device's
		icon, stored in any standard graphic file format such as JPEG, GIF, PNG and TIFF are all
		acceptable.  (See CFURL for functions to convert between POSIX paths and other ways of
		specifying files.)  The image's maximum size should be 128x128.

		Drivers should set the icon on the devices they add.

		A studio setup editor should allow the user to choose icons for external devices.
*/
extern const CFStringRef	kMIDIPropertyImage						API_AVAILABLE(macos(10.2), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@constant		kMIDIPropertyDriverVersion
	@discussion
		device/entity/endpoint property, integer, returns the driver version API of the owning
		driver (only for driver- owned devices).  Drivers need not set this property;
		applications should not write to it.
*/
extern const CFStringRef	kMIDIPropertyDriverVersion				API_AVAILABLE(macos(10.2), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@constant		kMIDIPropertySupportsGeneralMIDI
	@discussion
		device/entity property, integer (0/1). Indicates whether the device or entity implements
		the General MIDI specification.
*/
extern const CFStringRef	kMIDIPropertySupportsGeneralMIDI		API_AVAILABLE(macos(10.2), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@constant		kMIDIPropertySupportsMMC
	@discussion
		device/entity property, integer (0/1). Indicates whether the device or entity implements
		the MIDI Machine Control portion of the MIDI specification.
*/
extern const CFStringRef	kMIDIPropertySupportsMMC				API_AVAILABLE(macos(10.2), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@constant		kMIDIPropertyCanRoute
	@discussion
		device/entity property, integer (0/1). Indicates whether the device or entity can route
		MIDI messages to or from other external MIDI devices (as with MIDI patch bays). This
		should NOT be set on devices which are controlled by drivers.
*/
extern const CFStringRef	kMIDIPropertyCanRoute					API_AVAILABLE(macos(10.0), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@constant		kMIDIPropertyReceivesClock
	@discussion
		device/entity property, integer (0/1). Indicates whether the device or entity  responds
		to MIDI beat clock messages.
*/
extern const CFStringRef	kMIDIPropertyReceivesClock				API_AVAILABLE(macos(10.2), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@constant		kMIDIPropertyReceivesMTC
	@discussion
		device/entity property, integer (0/1). Indicates whether the device or entity responds
		to MIDI Time Code messages.
*/
extern const CFStringRef	kMIDIPropertyReceivesMTC				API_AVAILABLE(macos(10.2), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@constant		kMIDIPropertyReceivesNotes
	@discussion
		device/entity property, integer (0/1). Indicates whether the device or entity responds
		to MIDI Note On messages.
*/
extern const CFStringRef	kMIDIPropertyReceivesNotes				API_AVAILABLE(macos(10.2), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@constant		kMIDIPropertyReceivesProgramChanges
	@discussion
		device/entity property, integer (0/1). Indicates whether the device or entity responds
		to MIDI program change messages.
*/
extern const CFStringRef	kMIDIPropertyReceivesProgramChanges		API_AVAILABLE(macos(10.2), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@constant		kMIDIPropertyReceivesBankSelectMSB
	@discussion
		device/entity property, integer (0/1). Indicates whether the device or entity responds
		to MIDI bank select MSB messages (control 0).
*/
extern const CFStringRef	kMIDIPropertyReceivesBankSelectMSB		API_AVAILABLE(macos(10.2), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@constant		kMIDIPropertyReceivesBankSelectLSB
	@discussion
		device/entity property, integer (0/1). Indicates whether the device or entity responds
		to MIDI bank select LSB messages (control 32).
*/
extern const CFStringRef	kMIDIPropertyReceivesBankSelectLSB		API_AVAILABLE(macos(10.2), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@constant		kMIDIPropertyTransmitsClock
	@discussion
		device/entity property, integer (0/1). Indicates whether the device or entity transmits
		MIDI beat clock messages.
*/
extern const CFStringRef	kMIDIPropertyTransmitsClock				API_AVAILABLE(macos(10.2), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@constant		kMIDIPropertyTransmitsMTC
	@discussion
		device/entity property, integer (0/1). Indicates whether the device or entity transmits
		MIDI Time Code messages.
*/
extern const CFStringRef	kMIDIPropertyTransmitsMTC				API_AVAILABLE(macos(10.2), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@constant		kMIDIPropertyTransmitsNotes
	@discussion
		device/entity property, integer (0/1). Indicates whether the device or entity transmits
		MIDI note messages.
*/
extern const CFStringRef	kMIDIPropertyTransmitsNotes				API_AVAILABLE(macos(10.2), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@constant		kMIDIPropertyTransmitsProgramChanges
	@discussion
		device/entity property, integer (0/1). Indicates whether the device or entity transmits
		MIDI program change messages.
*/
extern const CFStringRef	kMIDIPropertyTransmitsProgramChanges	API_AVAILABLE(macos(10.2), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@constant		kMIDIPropertyTransmitsBankSelectMSB
	@discussion
		device/entity property, integer (0/1). Indicates whether the device or entity transmits
		MIDI bank select MSB messages (control 0).
*/
extern const CFStringRef	kMIDIPropertyTransmitsBankSelectMSB		API_AVAILABLE(macos(10.2), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@constant		kMIDIPropertyTransmitsBankSelectLSB
	@discussion
		device/entity property, integer (0/1). Indicates whether the device or entity transmits
		MIDI bank select LSB messages (control 32).
*/
extern const CFStringRef	kMIDIPropertyTransmitsBankSelectLSB		API_AVAILABLE(macos(10.2), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@constant		kMIDIPropertyPanDisruptsStereo
	@discussion
		device/entity property, integer (0/1). Indicates whether the MIDI pan messages (control
		10), when sent to the device or entity, cause undesirable effects when playing stereo
		sounds (e.g. converting the signal to mono).
*/
extern const CFStringRef	kMIDIPropertyPanDisruptsStereo			API_AVAILABLE(macos(10.2), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@constant		kMIDIPropertyIsSampler
	@discussion
		device/entity property, integer (0/1). Indicates whether the device or entity plays
		audio samples in response to MIDI note messages.
*/
extern const CFStringRef	kMIDIPropertyIsSampler					API_AVAILABLE(macos(10.2), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@constant		kMIDIPropertyIsDrumMachine
	@discussion
		device/entity property, integer (0/1). Indicates whether the device or entity's sound
		presets tend to be collections of non-transposable samples (e.g. drum kits).
*/
extern const CFStringRef	kMIDIPropertyIsDrumMachine				API_AVAILABLE(macos(10.2), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@constant		kMIDIPropertyIsMixer
	@discussion
		device/entity property, integer (0/1). Indicates whether the device or entity mixes
		external audio signals, controlled by MIDI messages.
*/
extern const CFStringRef	kMIDIPropertyIsMixer					API_AVAILABLE(macos(10.2), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@constant		kMIDIPropertyIsEffectUnit
	@discussion
		device/entity property, integer (0/1). Indicates whether the device or entity is
		primarily a MIDI-controlled audio effect unit (i.e. does not generate sound on its own).
*/
extern const CFStringRef	kMIDIPropertyIsEffectUnit				API_AVAILABLE(macos(10.2), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@constant		kMIDIPropertyMaxReceiveChannels
	@discussion
		device/entity property, integer (0-16). Indicates the maximum number of MIDI channels on
		which a device may simultaneously receive MIDI Channel Messages. Common values are 0
		(devices which only respond to System Messages), 1 (non-multitimbral devices), and 16
		(fully multitimbral devices). Other values are possible, for example devices which are
		multi-timbral but have fewer than 16 "parts".
*/
extern const CFStringRef	kMIDIPropertyMaxReceiveChannels			API_AVAILABLE(macos(10.2), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@constant		kMIDIPropertyMaxTransmitChannels
	@discussion
		device/entity property, integer (0/1). Indicates the maximum number of MIDI channels on
		which a device may simultaneously transmit MIDI Channel Messages. Common values are 0, 1
		and 16.
*/
extern const CFStringRef	kMIDIPropertyMaxTransmitChannels		API_AVAILABLE(macos(10.2), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@constant		kMIDIPropertyDriverDeviceEditorApp
	@discussion
		device property, string, contains the full path to an application which knows how to
		configure this driver-owned devices. Drivers may set this property on their owned
		devices. Applications must not write to it.
*/
extern const CFStringRef	kMIDIPropertyDriverDeviceEditorApp		API_AVAILABLE(macos(10.3), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@constant		kMIDIPropertySupportsShowControl
	@discussion
		device/entity property, integer (0/1). Indicates whether the device implements the MIDI
		Show Control specification.
*/
extern const CFStringRef	kMIDIPropertySupportsShowControl		API_AVAILABLE(macos(10.4), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@constant		kMIDIPropertyDisplayName
	@discussion
		device/entity/endpoint property, string.

		Provides the Apple-recommended user-visible name for an endpoint, by combining the
		device and endpoint names.

		For objects other than endpoints, the display name is the same as the name.
*/
extern const CFStringRef	kMIDIPropertyDisplayName				API_AVAILABLE(macos(10.4), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	constant		kMIDIPropertyProtocolID
	@discussion
		device/entity/endpoint property, MIDIProtocolID. Indicates the native protocol in which
		the endpoint communicates. The value is set by the system on endpoints, when they are
		created. Drivers may dynamically change the protocol of an endpoint as a result of a MIDI-CI
		negotiation, by setting this property on the endpoint. Clients can observe changes to
		this property.
*/
extern const CFStringRef	kMIDIPropertyProtocolID					API_AVAILABLE(macos(11.0), ios(14.0)) API_UNAVAILABLE(tvos, watchos);

//==================================================================================================
#pragma mark	Clients

/*!
	@function		MIDIClientCreate

	@abstract 		Creates a MIDIClient object.

	@param			name
						The client's name.
	@param			notifyProc
						An optional (may be NULL) callback function through which the client
						will receive notifications of changes to the system.
	@param			notifyRefCon
						A refCon passed back to notifyRefCon
	@param			outClient
						On successful return, points to the newly-created MIDIClientRef.
	@result			An OSStatus result code.
 
	@discussion
		Note that notifyProc will always be called on the run loop which was current when
		MIDIClientCreate was first called.
 
*/
extern OSStatus
MIDIClientCreate(	CFStringRef					name,
					MIDINotifyProc __nullable	notifyProc,
					void * __nullable			notifyRefCon,
					MIDIClientRef *				outClient )				API_AVAILABLE(macos(10.0), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@function		MIDIClientCreateWithBlock

	@abstract 		Creates a MIDIClient object.

	@param			name
						The client's name.
	@param			outClient
						On successful return, points to the newly-created MIDIClientRef.
	@param			notifyBlock
						An optional (may be NULL) block via which the client
						will receive notifications of changes to the system.
	@result			An OSStatus result code.
 
	@discussion
		Note that notifyBlock is called on a thread chosen by the implementation.
		Thread-safety is the block's responsibility.
*/
extern OSStatus
MIDIClientCreateWithBlock(
					CFStringRef					name,
					MIDIClientRef *				outClient,
					MIDINotifyBlock __nullable	notifyBlock )			API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(tvos, watchos);


/*!
	@function   	MIDIClientDispose

	@abstract   	Disposes a MIDIClient object.
 
	@param  		client
						The client to dispose.
	@result			An OSStatus result code.

	@discussion
		It is not essential to call this function; the CoreMIDI framework will automatically
		dispose all MIDIClients when an application terminates. However, if this method is
		called to dispose the last/only MIDIClient owned by an application, the MIDI server may
		exit if there are no other MIDIClients remaining in the system, causing all subsequent calls
		to MIDIClientCreate and MIDIClientCreateWithBlock by that application to fail. For this reason,
		disposing all of an application's MIDIClients is strongly discouraged.
*/
extern OSStatus
MIDIClientDispose(	MIDIClientRef client )					API_AVAILABLE(macos(10.0), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

//==================================================================================================
#pragma mark	Ports

/*!
	@function		MIDIInputPortCreateWithProtocol

	@abstract 		Creates an input port through which the client may receive
					incoming MIDI messages from any MIDI source.

	@param			client
						The client to own the newly-created port.
	@param			portName
						The name of the port.
	@param			protocol
 						The MIDI protocol variant to be delivered to this port. The system
						will automatically convert to this protocol as needed.
	@param			outPort
						On successful return, points to the newly-created
						MIDIPort.
	@param			receiveBlock
						The MIDIReceiveBlock which will be called with incoming MIDI, from sources
						connected to this port.
	@result			An OSStatus result code.

	@discussion
		After creating a port, use MIDIPortConnectSource to establish an input connection from
		any number of sources to your port.
 
		readBlock will be called on a separate high-priority thread owned by CoreMIDI.
*/
extern OSStatus
MIDIInputPortCreateWithProtocol(MIDIClientRef	client,
								CFStringRef		portName,
								MIDIProtocolID	protocol,
								MIDIPortRef *	outPort,
								MIDIReceiveBlock receiveBlock )	API_AVAILABLE(macos(11.0), ios(14.0)) API_UNAVAILABLE(tvos, watchos);

/*!
	@function		MIDIInputPortCreate

	@abstract 		Creates an input port through which the client may receive
					incoming MIDI messages from any MIDI source.

	@param			client
						The client to own the newly-created port.
	@param			portName
						The name of the port.
	@param			readProc
						The MIDIReadProc which will be called with incoming MIDI,
						from sources connected to this port.
	@param			refCon
						The refCon passed to readHook.
	@param			outPort
						On successful return, points to the newly-created
						MIDIPort.
	@result			An OSStatus result code.

	@discussion
		After creating a port, use MIDIPortConnectSource to establish an input connection from
		any number of sources to your port.
 
		readProc will be called on a separate high-priority thread owned by CoreMIDI.
*/
extern OSStatus
MIDIInputPortCreate(	MIDIClientRef		client,
						CFStringRef			portName,
						MIDIReadProc		readProc,
						void * __nullable	refCon,
						MIDIPortRef * 		outPort )
				API_DEPRECATED_WITH_REPLACEMENT("MIDIInputPortCreateWithProtocol",
												macos(10.0, API_TO_BE_DEPRECATED), ios(4.2, API_TO_BE_DEPRECATED)) __TVOS_PROHIBITED __WATCHOS_PROHIBITED;

/*!
	@function		MIDIInputPortCreateWithBlock

	@abstract 		Creates an input port through which the client may receive
					incoming MIDI messages from any MIDI source.

	@param			client
						The client to own the newly-created port.
	@param			portName
						The name of the port.
	@param			outPort
						On successful return, points to the newly-created
						MIDIPort.
	@param			readBlock
						The MIDIReadBlock which will be called with incoming MIDI, from sources
						connected to this port.
	@result			An OSStatus result code.

	@discussion
		After creating a port, use MIDIPortConnectSource to establish an input connection from
		any number of sources to your port.
 
		readBlock will be called on a separate high-priority thread owned by CoreMIDI.
*/
extern OSStatus
MIDIInputPortCreateWithBlock(	MIDIClientRef	client,
								CFStringRef		portName,
								MIDIPortRef *	outPort,
								MIDIReadBlock	readBlock )
					API_DEPRECATED_WITH_REPLACEMENT("MIDIInputPortCreateWithProtocol",
													macos(10.11, API_TO_BE_DEPRECATED), ios(9.0, API_TO_BE_DEPRECATED)) __TVOS_PROHIBITED __WATCHOS_PROHIBITED;

/*!
	@function		MIDIOutputPortCreate

	@abstract 		Creates an output port through which the client may send
					outgoing MIDI messages to any MIDI destination.

	@param			client
						The client to own the newly-created port
	@param			portName
						The name of the port.
	@param			outPort
						On successful return, points to the newly-created
						MIDIPort.
	@result			An OSStatus result code.

	@discussion
		Output ports provide a mechanism for MIDI merging.  CoreMIDI assumes that each output
		port will be responsible for sending only a single MIDI stream to each destination,
		although a single port may address all of the destinations in the system.

		Multiple output ports are only necessary when an application is capable of directing
		multiple simultaneous MIDI streams to the same destination.
*/
extern OSStatus
MIDIOutputPortCreate(	MIDIClientRef	client,
						CFStringRef		portName,
						MIDIPortRef *	outPort )			API_AVAILABLE(macos(10.0), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@function		MIDIPortDispose

	@abstract 		Disposes a MIDIPort object.

	@param			port
						The port to dispose.
	@result			An OSStatus result code.

	@discussion
		It is not usually necessary to call this function; when an application's MIDIClient's
		are automatically disposed at termination, or explicitly, via MIDIClientDispose, the
		client's ports are automatically disposed at that time.
*/
extern OSStatus
MIDIPortDispose(	MIDIPortRef port )						API_AVAILABLE(macos(10.0), ios(4.2)) API_UNAVAILABLE(tvos, watchos);


/*!
	@function		MIDIPortConnectSource

	@abstract 		Establishes a connection from a source to a client's input port.

	@param			port
						The port to which to create the connection.  This port's
						readProc is called with incoming MIDI from the source.
	@param			source
						The source from which to create the connection.
	@param			connRefCon
						This refCon is passed to the port's MIDIReadProc or MIDIReadBlock, as a way to
						identify the source.
	@result			An OSStatus result code.
*/
extern OSStatus
MIDIPortConnectSource(	MIDIPortRef		port,
						MIDIEndpointRef	source,
						void * __nullable			connRefCon )		API_AVAILABLE(macos(10.0), ios(4.2)) API_UNAVAILABLE(tvos, watchos);


/*!
	@function		MIDIPortDisconnectSource
 
	@abstract 		Closes a previously-established source-to-input port
					connection.

	@param			port
						The port whose connection is being closed.
	@param			source
						The source from which to close a connection to the
						specified port.
	@result			An OSStatus result code.
*/
extern OSStatus
MIDIPortDisconnectSource(	MIDIPortRef		port,
							MIDIEndpointRef	source )		API_AVAILABLE(macos(10.0), ios(4.2)) API_UNAVAILABLE(tvos, watchos);


//==================================================================================================
#pragma mark	Devices

/*!
	@function		MIDIGetNumberOfDevices

	@abstract 		Returns the number of devices in the system.

	@result			The number of devices in the system, or 0 if an error
					occurred.
*/
extern ItemCount
MIDIGetNumberOfDevices(void)								API_AVAILABLE(macos(10.0), ios(4.2)) API_UNAVAILABLE(tvos, watchos);


/*!
	@function		MIDIGetDevice

	@abstract 		Returns one of the devices in the system.

	@param			deviceIndex0
						The index (0...MIDIGetNumberOfDevices()-1) of the device
						to return.
	@result			A reference to a device, or NULL if an error occurred.

	@discussion
		Use this to enumerate the devices in the system.

		To enumerate the entities in the system, you can walk through the devices, then walk
		through the devices' entities.

		Note: If a client iterates through the devices and entities in the system, it will not
		ever visit any virtual sources and destinations created by other clients.  Also, a
		device iteration will return devices which are "offline" (were present in the past but
		are not currently present), while iterations through the system's sources and
		destinations will not include the endpoints of offline devices.

		Thus clients should usually use MIDIGetNumberOfSources, MIDIGetSource,
		MIDIGetNumberOfDestinations and MIDIGetDestination, rather iterating through devices and
		entities to locate endpoints.
*/
extern MIDIDeviceRef
MIDIGetDevice(	ItemCount deviceIndex0 )					API_AVAILABLE(macos(10.0), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@function		MIDIDeviceGetNumberOfEntities

	@abstract 		Returns the number of entities in a given device.
 
	@param			device
						The device being queried.

	@result			The number of entities the device contains, or 0 if an
					error occurred.
*/
extern ItemCount
MIDIDeviceGetNumberOfEntities(	MIDIDeviceRef device )		API_AVAILABLE(macos(10.0), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@function		MIDIDeviceGetEntity

	@abstract 		Returns one of a given device's entities.
 
	@param			device
						The device being queried.
	@param			entityIndex0
						The index (0...MIDIDeviceGetNumberOfEntities(device)-1)
						of the entity to return

	@result			A reference to an entity, or NULL if an error occurred.
*/
extern MIDIEntityRef
MIDIDeviceGetEntity(	MIDIDeviceRef	device,
						ItemCount		entityIndex0 )		API_AVAILABLE(macos(10.0), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

//==================================================================================================
#pragma mark	Entities

/*!
	@function		MIDIEntityGetNumberOfSources
 
	@abstract 		Returns the number of sources in a given entity.
 
	@param			entity
						The entity being queried

	@result			The number of sources the entity contains, or 0 if an
					error occurred.
*/
extern ItemCount
MIDIEntityGetNumberOfSources(	MIDIEntityRef entity )		API_AVAILABLE(macos(10.0), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@function		MIDIEntityGetSource

	@abstract 		Returns one of a given entity's sources.
 
	@param			entity
						The entity being queried.
	@param			sourceIndex0
						The index (0...MIDIEntityGetNumberOfSources(entity)-1) of
						the source to return

	@result			A reference to a source, or NULL if an error occurred.
*/
extern MIDIEndpointRef
MIDIEntityGetSource(	MIDIEntityRef entity,
						ItemCount sourceIndex0 )			API_AVAILABLE(macos(10.0), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@function		MIDIEntityGetNumberOfDestinations

	@abstract 		Returns the number of destinations in a given entity.
 
	@param			entity
						The entity being queried

	@result			The number of destinations the entity contains, or 0
					if an error occurred.
*/
extern ItemCount
MIDIEntityGetNumberOfDestinations(	MIDIEntityRef entity )	API_AVAILABLE(macos(10.0), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@function		MIDIEntityGetDestination

	@abstract 		Returns one of a given entity's destinations.
 
	@param			entity
						The entity being queried.
	@param			destIndex0
						The index (0...MIDIEntityGetNumberOfDestinations(entity)
						- 1) of the destination to return

	@result			A reference to a destination, or NULL if an error occurred.
*/
extern MIDIEndpointRef
MIDIEntityGetDestination(	MIDIEntityRef	entity,
							ItemCount		destIndex0 )	API_AVAILABLE(macos(10.0), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@function		MIDIEntityGetDevice

	@abstract 		Returns an entity's device.
 
	@param			inEntity
						The entity being queried.
	@param			outDevice
						On successful return, the entity's owning device.
*/
extern OSStatus
MIDIEntityGetDevice(		MIDIEntityRef		inEntity,
							MIDIDeviceRef * __nullable		outDevice)	API_AVAILABLE(macos(10.2), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

//==================================================================================================
#pragma mark	Endpoints

/*!
	@function		MIDIGetNumberOfSources

	@abstract 		Returns the number of sources in the system.

	@result			The number of sources in the system, or 0 if an error
					occurred.
*/
extern ItemCount
MIDIGetNumberOfSources(void)								API_AVAILABLE(macos(10.0), ios(4.2)) API_UNAVAILABLE(tvos, watchos);


/*!
	@function		MIDIGetSource

	@abstract 		Returns one of the sources in the system.

	@param			sourceIndex0
						The index (0...MIDIGetNumberOfSources()-1) of the source
						to return
	@result			A reference to a source, or NULL if an error occurred.
*/
extern MIDIEndpointRef
MIDIGetSource(	ItemCount sourceIndex0 )					API_AVAILABLE(macos(10.0), ios(4.2)) API_UNAVAILABLE(tvos, watchos);


/*!
	@function		MIDIGetNumberOfDestinations

	@abstract 		Returns the number of destinations in the system.

	@result			The number of destinations in the system, or 0 if an error
					occurred.
*/
extern ItemCount
MIDIGetNumberOfDestinations(void)							API_AVAILABLE(macos(10.0), ios(4.2)) API_UNAVAILABLE(tvos, watchos);


/*!
	@function		MIDIGetDestination

	@abstract 		Returns one of the destinations in the system.

	@param			destIndex0
						The index (0...MIDIGetNumberOfDestinations()-1) of the
						destination to return
	@result			A reference to a destination, or NULL if an error occurred.
*/
extern MIDIEndpointRef
MIDIGetDestination(	ItemCount destIndex0 )					API_AVAILABLE(macos(10.0), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@function		MIDIEndpointGetEntity

	@abstract 		Returns an endpoint's entity.
 
	@param			inEndpoint
						The endpoint being queried.
	@param			outEntity
						On exit, the endpoint's owning entity, or NULL if none.
 
	@discussion
		Virtual sources and destinations don't have entities.
*/
extern OSStatus
MIDIEndpointGetEntity(		MIDIEndpointRef		inEndpoint,
							MIDIEntityRef * __nullable		outEntity)	API_AVAILABLE(macos(10.2), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@function		MIDIDestinationCreateWithProtocol

	@abstract 		Creates a virtual destination in a client.

	@param			client
						The client owning the virtual destination.
	@param			name
						The name of the virtual destination.
	@param			protocol
 						The MIDI protocol variant to be delivered to this destination. The system
						will automatically convert to this protocol as needed.
	@param			outDest
						On successful return, a pointer to the newly-created
						destination.
	@param			readBlock
						The MIDIReceiveBlock to be called when a client sends MIDI to the virtual
						destination.
	@result			An OSStatus result code.

	@discussion
		The specified readBlock gets called when clients send MIDI to your virtual destination.

		Drivers need not call this; when they create devices and entities, sources and
		destinations are created at that time.
 
		After creating a virtual destination, it's a good idea to assign it the same unique ID
		it had the last time your application created it. (Although you should be prepared for
		this to fail in the unlikely event of a collision.) This will permit other clients
		to retain persistent references to your virtual destination more easily.
 
		See the discussion of kMIDIPropertyAdvanceScheduleTimeMuSec for notes about the
		relationship between when a sender sends MIDI to the destination and when it is
		received.
*/
extern OSStatus
MIDIDestinationCreateWithProtocol(	MIDIClientRef 	client,
									CFStringRef  		name,
									MIDIProtocolID		protocol,
									MIDIEndpointRef *	outDest,
									MIDIReceiveBlock	readBlock ) API_AVAILABLE(macos(11.0), ios(14.0)) API_UNAVAILABLE(tvos, watchos);

/*!
	@function		MIDIDestinationCreate

	@abstract 		Creates a virtual destination in a client.

	@param			client
						The client owning the virtual destination.
	@param			name
						The name of the virtual destination.
	@param			readProc
						The MIDIReadProc to be called when a client sends MIDI to
						the virtual destination.
	@param			refCon
						The refCon to be passed to the readProc.
	@param			outDest
						On successful return, a pointer to the newly-created
						destination.
	@result			An OSStatus result code.

	@discussion
		The specified readProc gets called when clients send MIDI to your virtual destination.

		Drivers need not call this; when they create devices and entities, sources and
		destinations are created at that time.
 
		After creating a virtual destination, it's a good idea to assign it the same unique ID
		it had the last time your application created it. (Although you should be prepared for
		this to fail in the unlikely event of a collision.) This will permit other clients
		to retain persistent references to your virtual destination more easily.
 
		See the discussion of kMIDIPropertyAdvanceScheduleTimeMuSec for notes about the
		relationship between when a sender sends MIDI to the destination and when it is
		received.
*/
extern OSStatus
MIDIDestinationCreate(	MIDIClientRef 		client,
						CFStringRef  		name,
						MIDIReadProc 		readProc,
						void * __nullable	refCon,
						MIDIEndpointRef *	outDest )
				API_DEPRECATED_WITH_REPLACEMENT("MIDIDestinationCreateWithProtocol",
												macos(10.0, API_TO_BE_DEPRECATED), ios(4.2, API_TO_BE_DEPRECATED)) __TVOS_PROHIBITED __WATCHOS_PROHIBITED;

/*!
	@function		MIDIDestinationCreateWithBlock

	@abstract 		Creates a virtual destination in a client.

	@param			client
						The client owning the virtual destination.
	@param			name
						The name of the virtual destination.
	@param			outDest
						On successful return, a pointer to the newly-created
						destination.
	@param			readBlock
						The MIDIReadBlock to be called when a client sends MIDI to the virtual
						destination.
	@result			An OSStatus result code.

	@discussion
		The specified readBlock gets called when clients send MIDI to your virtual destination.

		Drivers need not call this; when they create devices and entities, sources and
		destinations are created at that time.
 
		After creating a virtual destination, it's a good idea to assign it the same unique ID
		it had the last time your application created it. (Although you should be prepared for
		this to fail in the unlikely event of a collision.) This will permit other clients
		to retain persistent references to your virtual destination more easily.
 
		See the discussion of kMIDIPropertyAdvanceScheduleTimeMuSec for notes about the
		relationship between when a sender sends MIDI to the destination and when it is
		received.
*/
extern OSStatus
MIDIDestinationCreateWithBlock(	MIDIClientRef 		client,
								CFStringRef  		name,
								MIDIEndpointRef * 	outDest,
								MIDIReadBlock 		readBlock )
					API_DEPRECATED_WITH_REPLACEMENT("MIDIDestinationCreateWithProtocol",
													macos(10.11, API_TO_BE_DEPRECATED), ios(9.0, API_TO_BE_DEPRECATED)) __TVOS_PROHIBITED __WATCHOS_PROHIBITED;

/*!
	@function		MIDISourceCreateWithProtocol
	 
	@abstract 		Creates a virtual source in a client.
	 
	@param			client
	 					The client owning the virtual source.
	@param			name
						The name of the virtual source.
 	@param			protocol
 						The MIDI protocol variant to be sent from this source. The system
 						will automatically convert from this protocol to the protocol of
 						the destination as needed.
	@param			outSrc
	 					On successful return, a pointer to the newly-created
	 					source.
	@result			An OSStatus result code.
	 
	@discussion
	Drivers need not call this; when they create devices and entities, sources and
	destinations are created at that time.
	 
	After creating a virtual source, use MIDIReceivedEventList to transmit MIDI messages from your
	virtual source to any clients connected to the virtual source.
	 
	After creating a virtual source, it's a good idea to assign it the same unique ID it had
	the last time your application created it. (Although you should be prepared for this to
	fail in the unlikely event of a collision.) This will permit other clients to retain
	persistent references to your virtual source more easily.
*/
	
extern OSStatus
MIDISourceCreateWithProtocol(	MIDIClientRef 		client,
								CFStringRef  		name,
								MIDIProtocolID		protocol,
								MIDIEndpointRef * 	outSrc ) API_AVAILABLE(macos(11.0), ios(14.0)) API_UNAVAILABLE(tvos, watchos);

/*!
	@function		MIDISourceCreate

	@abstract 		Creates a virtual source in a client.

	@param			client
						The client owning the virtual source.
	@param			name
						The name of the virtual source.
	@param			outSrc
						On successful return, a pointer to the newly-created
						source.
	@result			An OSStatus result code.

	@discussion
		Drivers need not call this; when they create devices and entities, sources and
		destinations are created at that time.

		After creating a virtual source, use MIDIReceived to transmit MIDI messages from your
		virtual source to any clients connected to the virtual source.

		After creating a virtual source, it's a good idea to assign it the same unique ID it had
		the last time your application created it. (Although you should be prepared for this to
		fail in the unlikely event of a collision.) This will permit other clients to retain
		persistent references to your virtual source more easily.
*/
extern OSStatus
MIDISourceCreate(	MIDIClientRef 		client,
					CFStringRef  		name,
					MIDIEndpointRef * 	outSrc )
			API_DEPRECATED_WITH_REPLACEMENT("MIDISourceCreateWithProtocol",
											macos(10.0, API_TO_BE_DEPRECATED), ios(4.2, API_TO_BE_DEPRECATED)) __TVOS_PROHIBITED __WATCHOS_PROHIBITED;

/*!
	@function		MIDIEndpointDispose

	@abstract 		Disposes a virtual source or destination your client created.

	@param			endpt
						The endpoint to be disposed.

	@result			An OSStatus result code.
*/
extern OSStatus
MIDIEndpointDispose(	MIDIEndpointRef endpt )				API_AVAILABLE(macos(10.0), ios(4.2)) API_UNAVAILABLE(tvos, watchos);


//==================================================================================================
#pragma mark	External Devices

/*!
	@function		MIDIGetNumberOfExternalDevices

	@abstract 		Returns the number of external MIDI devices in the system.
 
	@result			The number of external devices in the system, or 0 if an error
					occurred.

	@discussion
		External MIDI devices are MIDI devices connected to driver endpoints via a standard MIDI
		cable. Their presence is completely optional, only when a UI (such as Audio MIDI Setup)
		adds them.
*/
extern ItemCount
MIDIGetNumberOfExternalDevices(void)						API_AVAILABLE(macos(10.1), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@function		MIDIGetExternalDevice

	@abstract 		Returns one of the external devices in the system.

	@param			deviceIndex0
						The index (0...MIDIGetNumberOfDevices()-1) of the device
						to return.
	@result			A reference to a device, or NULL if an error occurred.

	@discussion
		Use this to enumerate the external devices in the system.
*/
extern MIDIDeviceRef
MIDIGetExternalDevice(	ItemCount deviceIndex0 )			API_AVAILABLE(macos(10.1), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

//==================================================================================================
#pragma mark	Objects and Properties

/*!
	@function		MIDIObjectGetIntegerProperty

	@abstract 		Gets an object's integer-type property.
 
	@param			obj
						The object whose property is to be returned.
	@param			propertyID
						Name of the property to return.
	@param			outValue
						On successful return, the value of the property.
	@result			An OSStatus result code.

	@discussion
		(See the MIDIObjectRef documentation for information about properties.)
*/
extern OSStatus
MIDIObjectGetIntegerProperty(	MIDIObjectRef	obj,
								CFStringRef		propertyID,
								SInt32 *		outValue )	API_AVAILABLE(macos(10.0), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@function		MIDIObjectSetIntegerProperty

	@abstract 		Sets an object's integer-type property.
 
	@param			obj
						The object whose property is to be altered.
	@param			propertyID
						Name of the property to set.
	@param			value
						New value of the property.
	@result			An OSStatus result code.

	@discussion
		(See the MIDIObjectRef documentation for information about properties.)
*/
extern OSStatus
MIDIObjectSetIntegerProperty(	MIDIObjectRef	obj,
								CFStringRef		propertyID,
								SInt32			value )		API_AVAILABLE(macos(10.0), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@function		MIDIObjectGetStringProperty

	@abstract 		Gets an object's string-type property.

	@param			obj
						The object whose property is to be returned.
	@param			propertyID
						Name of the property to return.
	@param			str
						On successful return, the value of the property.
	@result			An OSStatus result code.

	@discussion
		(See the MIDIObjectRef documentation for information about properties.)
*/
extern OSStatus
MIDIObjectGetStringProperty(	MIDIObjectRef			obj,
								CFStringRef				propertyID,
								CFStringRef __nullable * __nonnull str )		API_AVAILABLE(macos(10.0), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@function		MIDIObjectSetStringProperty

	@abstract 		Sets an object's string-type property.
 
	@param			obj
						The object whose property is to be altered.
	@param			propertyID
						Name of the property to set.
	@param			str
						New value of the property.
	@result			An OSStatus result code.

	@discussion
		(See the MIDIObjectRef documentation for information about properties.)
*/
extern OSStatus
MIDIObjectSetStringProperty(	MIDIObjectRef	obj,
								CFStringRef		propertyID,
								CFStringRef		str )		API_AVAILABLE(macos(10.0), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@function		MIDIObjectGetDataProperty

	@abstract 		Gets an object's data-type property.

	@discussion
(See the MIDIObjectRef documentation for information
					about properties.)
 
	@param			obj
						The object whose property is to be returned.
	@param			propertyID
						Name of the property to return.
	@param			outData
						On successful return, the value of the property.
	@result			An OSStatus result code.
*/
extern OSStatus
MIDIObjectGetDataProperty(		MIDIObjectRef			obj,
								CFStringRef				propertyID,
								CFDataRef __nullable * __nonnull outData )	API_AVAILABLE(macos(10.0), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@function		MIDIObjectSetDataProperty

	@abstract 		Sets an object's data-type property.
 
	@param			obj
						The object whose property is to be altered.
	@param			propertyID
						Name of the property to set.
	@param			data
						New value of the property.
	@result			An OSStatus result code.

	@discussion
		(See the MIDIObjectRef documentation for information about properties.)
*/
extern OSStatus
MIDIObjectSetDataProperty(		MIDIObjectRef	obj,
								CFStringRef		propertyID,
								CFDataRef		data )		API_AVAILABLE(macos(10.0), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@function		MIDIObjectGetDictionaryProperty

	@abstract 		Gets an object's dictionary-type property.

	@param			obj
						The object whose property is to be returned.
	@param			propertyID
						Name of the property to return.
	@param			outDict
						On successful return, the value of the property.
	@result			An OSStatus result code.

	@discussion
		(See the MIDIObjectRef documentation for information about properties.)
*/
extern OSStatus
MIDIObjectGetDictionaryProperty(	MIDIObjectRef					obj,
									CFStringRef						propertyID,
									CFDictionaryRef __nullable * __nonnull outDict )
															API_AVAILABLE(macos(10.2), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@function		MIDIObjectSetDictionaryProperty

	@abstract 		Sets an object's dictionary-type property.
 
	@param			obj
						The object whose property is to be altered.
	@param			propertyID
						Name of the property to set.
	@param			dict
						New value of the property.
	@result			An OSStatus result code.

	@discussion
		(See the MIDIObjectRef documentation for information about properties.)
*/
extern OSStatus
MIDIObjectSetDictionaryProperty(MIDIObjectRef	obj,
								CFStringRef		propertyID,
								CFDictionaryRef dict )		API_AVAILABLE(macos(10.2), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@function		MIDIObjectGetProperties
 
	@abstract		Gets all of an object's properties.

	@param			obj
						The object whose properties are to be returned.
	@param			outProperties
						On successful return, the object's properties.
	@param			deep
						true if the object's child objects are to be included
						(e.g. a device's entities, or an entity's endpoints).
	@result			An OSStatus result code.

	@discussion
		Returns a CFPropertyList of all of an object's properties. The property list may be a
		dictionary or an array. Dictionaries map property names (CFString) to values, which may
		be CFNumber, CFString, or CFData.  Arrays are arrays of such values.

		Properties which an object inherits from its owning object (if any) are not included.
*/
extern OSStatus
MIDIObjectGetProperties(		MIDIObjectRef 		obj,
								CFPropertyListRef __nullable * __nonnull outProperties,
								Boolean				deep )	API_AVAILABLE(macos(10.1), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@function		MIDIObjectRemoveProperty
 
	@abstract		Removes an object's property.

	@param			obj
						The object whose property is to be removed.
	@param			propertyID
						The property to be removed.
	@result			An OSStatus result code.
*/
extern OSStatus
MIDIObjectRemoveProperty(		MIDIObjectRef 		obj,
								CFStringRef			propertyID )
															API_AVAILABLE(macos(10.2), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@function		MIDIObjectFindByUniqueID

	@abstract 		Locates a device, external device, entity, or endpoint
					by its uniqueID.
	@param			inUniqueID
						The uniqueID of the object to search for.  (This should
						be the result of an earlier call to MIDIObjectGetIntegerProperty
						for the property kMIDIPropertyUniqueID).
	@param			outObject
						The returned object, or 0 if the object was not found or
						an error occurred.  This should be cast to the appropriate
						type (MIDIDeviceRef, MIDIEntityRef, MIDIEndpointRef),
						according to *outObjectType.
	@param			outObjectType
						On exit, the type of object which was found; undefined
						if none found.
	@result			An OSStatus error code, including kMIDIObjectNotFound if there
					is no object with the specified uniqueID.
*/
extern OSStatus
MIDIObjectFindByUniqueID(	MIDIUniqueID 		inUniqueID,
							MIDIObjectRef * __nullable outObject,
							MIDIObjectType * __nullable outObjectType)
															API_AVAILABLE(macos(10.2), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

//==================================================================================================
#pragma mark	MIDI I/O

/*!
	@function		MIDISendEventList

	@abstract 		Sends MIDI to a destination.

	@param			port
						The output port through which the MIDI is to be sent.
	@param			dest
						The destination to receive the events.
	@param			evtlist
						The MIDI events to be sent.
	@result			An OSStatus result code.

	@discussion
		Events with future timestamps are scheduled for future delivery.  CoreMIDI performs
		any needed MIDI merging.
*/
extern OSStatus
MIDISendEventList(	MIDIPortRef 				port,
					MIDIEndpointRef 			dest,
					const MIDIEventList *		evtlist )	API_AVAILABLE(macos(11.0), ios(14.0)) API_UNAVAILABLE(tvos, watchos);

/*!
	@function		MIDISend

	@abstract 		Sends MIDI to a destination.

	@param			port
						The output port through which the MIDI is to be sent.
	@param			dest
						The destination to receive the events.
	@param			pktlist
						The MIDI events to be sent.
	@result			An OSStatus result code.

	@discussion
		Events with future timestamps are scheduled for future delivery.  CoreMIDI performs
		any needed MIDI merging.
*/
extern OSStatus
MIDISend(	MIDIPortRef 			port,
			MIDIEndpointRef 		dest,
			const MIDIPacketList *	pktlist )
	API_DEPRECATED_WITH_REPLACEMENT("MIDISendEventList",
									macos(10.0, API_TO_BE_DEPRECATED), ios(4.2, API_TO_BE_DEPRECATED)) __TVOS_PROHIBITED __WATCHOS_PROHIBITED;
    
/*!
	@function		MIDISendSysex

	@abstract 		Sends a single system-exclusive event, asynchronously.

	@param			request
						Contains the destination, and a pointer to the MIDI data to be sent.
	@result			An OSStatus result code.

	@discussion
		request->data must point to a single MIDI system-exclusive message, or portion thereof.
*/
extern OSStatus
MIDISendSysex(	MIDISysexSendRequest *request )				API_AVAILABLE(macos(10.0), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@function		MIDIReceivedEventList

	@abstract 		Distributes incoming MIDI from a source to the client input ports
					which are connected to that source.

	@param			src
						The source which is transmitting MIDI.
	@param			evtlist
						The MIDI events to be transmitted.
	@result			An OSStatus result code.

	@discussion
		Drivers should call this function when receiving MIDI from a source.

		Clients which have created virtual sources, using MIDISourceCreateWithProtocol, should call this
		function when the source is generating MIDI.
 
		Unlike MIDISendEventList(), a timestamp of 0 is not equivalent to "now"; the driver or virtual
		source is responsible for putting proper timestamps in the packets.
*/
extern OSStatus
MIDIReceivedEventList(	MIDIEndpointRef			src,
						const MIDIEventList *	evtlist )	API_AVAILABLE(macos(11.0), ios(14.0)) API_UNAVAILABLE(tvos, watchos);

/*!
	@function		MIDIReceived

	@abstract 		Distributes incoming MIDI from a source to the client input ports
					which are connected to that source.

	@param			src
						The source which is transmitting MIDI.
	@param			pktlist
						The MIDI events to be transmitted.
	@result			An OSStatus result code.

	@discussion
		Drivers should call this function when receiving MIDI from a source.

		Clients which have created virtual sources, using MIDISourceCreate, should call this
		function when the source is generating MIDI.
 
		Unlike MIDISend(), a timestamp of 0 is not equivalent to "now"; the driver or virtual
		source is responsible for putting proper timestamps in the packets.
*/
extern OSStatus
MIDIReceived(	MIDIEndpointRef			src,
				const MIDIPacketList * 	pktlist )
		API_DEPRECATED_WITH_REPLACEMENT("MIDIReceivedEventList",
										macos(10.0, API_TO_BE_DEPRECATED), ios(4.2, API_TO_BE_DEPRECATED)) __TVOS_PROHIBITED __WATCHOS_PROHIBITED;

/*!
	@function		MIDIFlushOutput
 
	@abstract		Unschedules previously-sent packets.
 
	@param			dest
						All pending events scheduled to be sent to this destination
						are unscheduled.  If NULL, the operation applies to
						all destinations.

	@discussion
		Clients may use MIDIFlushOutput to cancel the sending of packets that were previously
		scheduled for future delivery.
*/
extern OSStatus
MIDIFlushOutput(	MIDIEndpointRef		dest )				API_AVAILABLE(macos(10.1), ios(4.2)) API_UNAVAILABLE(tvos, watchos);

/*!
	@function		MIDIRestart

	@abstract 		Stops and restarts MIDI I/O.
 
	@discussion
		This is useful for forcing CoreMIDI to ask its drivers to rescan for hardware.
 
	@result			An OSStatus result code.
*/
extern OSStatus
MIDIRestart(void)											API_AVAILABLE(macos(10.1), ios(4.2)) API_UNAVAILABLE(tvos, watchos);



//==================================================================================================
#pragma mark Event Lists

#ifdef CF_INLINE
    /*!
     @function		MIDIEventPacketNext
     
     @abstract 		Advances a MIDIEventPacket pointer to the MIDIEventPacket which immediately follows it
					in memory if it is part of a MIDIEventList.
     
     @param			pkt
						A pointer to a MIDIEventPacket in a MIDIEventList.
     @result		The subsequent packet in the MIDIEventList.
*/
CF_INLINE MIDIEventPacket *MIDIEventPacketNext(const MIDIEventPacket *pkt)
{
	return	(MIDIEventPacket *)(&pkt->words[pkt->wordCount]);
}
#else
	#define MIDIEventPacketNext(pkt)	(MIDIEventPacket *)(&pkt->words[pkt->wordCount])
#endif

/*!
	@function		MIDIEventListInit

	@abstract 		Prepares a MIDIEventList to be built up dynamically.
 
	@param			evtlist
						The event list to be initialized.

	@result			A pointer to the first MIDIEventPacket in the event list.
*/
extern MIDIEventPacket *
MIDIEventListInit(	MIDIEventList *evtlist,
					MIDIProtocolID protocol)			API_AVAILABLE(macos(11.0), ios(14.0), tvos(15.0), watchos(8.0));

/*!
	@function		MIDIEventListAdd

	@abstract 		Adds a MIDI event to a MIDIEventList.
 
	@param			evtlist
						The event list to which the event is to be added.
	@param			listSize
						The capacity, in bytes, of the event list.
	@param			curPacket
						A packet pointer returned by a previous call to
						MIDIEventListInit or MIDIEventListAdd for this packet
						list.
	@param			time
						The new event's time.
	@param			wordCount
						The number of valid MIDI 32-bit words which follow, in data.
	@param			words
						The new event.  May be a single MIDI event, or a partial
						sys-ex event.  Running status is <b>not</b> permitted.
	@result			Returns null if there was not room in the packet for the
					event; otherwise returns a packet pointer which should be
					passed as curPacket in a subsequent call to this function.

	@discussion
		The maximum size of a event list is 65536 bytes. Large sysex messages must be sent in
		smaller event lists.
 
		Note that events must use the same protocol as was passed to MIDIEventListInit().
*/
extern MIDIEventPacket *
MIDIEventListAdd(	MIDIEventList *		evtlist,
					ByteCount			listSize,
					MIDIEventPacket *	curPacket,
					MIDITimeStamp		time,
					ByteCount			wordCount,
					const UInt32 *		words)			API_AVAILABLE(macos(11.0), ios(14.0), tvos(15.0), watchos(8.0));

//==================================================================================================
#pragma mark Packet Lists (Deprecated in favor of Event Lists)

#ifdef CF_INLINE
/*!
	@function		MIDIPacketNext

	@abstract 		Advances a MIDIPacket pointer to the MIDIPacket which immediately follows it
					in memory if it is part of a MIDIPacketList.

	@param			pkt
						A pointer to a MIDIPacket in a MIDIPacketList.

	@result			The subsequent packet in the MIDIPacketList.
*/
CF_INLINE MIDIPacket *MIDIPacketNext(const MIDIPacket *pkt)
{
	#if TARGET_CPU_ARM || TARGET_CPU_ARM64
		// MIDIPacket must be 4-byte aligned
		return	(MIDIPacket *)(((uintptr_t)(&pkt->data[pkt->length]) + 3) & ~3);
	#else
		return	(MIDIPacket *)&pkt->data[pkt->length];
	#endif
}
#else
	#if TARGET_CPU_ARM || TARGET_CPU_ARM64
		// MIDIPacket must be 4-byte aligned
		#define MIDIPacketNext(pkt)	((MIDIPacket *)(((uintptr_t)(&(pkt)->data[(pkt)->length]) + 3) & ~3))
	#else
		#define MIDIPacketNext(pkt)	((MIDIPacket *)&(pkt)->data[(pkt)->length])
	#endif
#endif

/*!
	@function		MIDIPacketListInit

	@abstract 		Prepares a MIDIPacketList to be built up dynamically.
 
	@param			pktlist
						The packet list to be initialized.

	@result			A pointer to the first MIDIPacket in the packet list.
*/
extern MIDIPacket *
MIDIPacketListInit(	MIDIPacketList *pktlist )
			API_DEPRECATED_WITH_REPLACEMENT("MIDIEventListInit",
											macos(10.0, API_TO_BE_DEPRECATED), ios(4.2, API_TO_BE_DEPRECATED)) __TVOS_PROHIBITED __WATCHOS_PROHIBITED;

/*!
	@function		MIDIPacketListAdd

	@abstract 		Adds a MIDI event to a MIDIPacketList.
 
	@param			pktlist
						The packet list to which the event is to be added.
	@param			listSize
						The size, in bytes, of the packet list.
	@param			curPacket
						A packet pointer returned by a previous call to
						MIDIPacketListInit or MIDIPacketListAdd for this packet
						list.
	@param			time
						The new event's time.
	@param			nData
						The length of the new event, in bytes.
	@param			data
						The new event.  May be a single MIDI event, or a partial
						sys-ex event.  Running status is <b>not</b> permitted.
	@result			Returns null if there was not room in the packet for the
					event; otherwise returns a packet pointer which should be
					passed as curPacket in a subsequent call to this function.

	@discussion
		The maximum size of a packet list is 65536 bytes. Large sysex messages must be sent in
		smaller packet lists.
*/
extern MIDIPacket *
MIDIPacketListAdd(	MIDIPacketList *	pktlist,
					ByteCount			listSize,
					MIDIPacket *		curPacket,
					MIDITimeStamp		time,
					ByteCount			nData,
					const Byte *		data)
			API_DEPRECATED_WITH_REPLACEMENT("MIDIEventListAdd",
											macos(10.0, API_TO_BE_DEPRECATED), ios(4.2, API_TO_BE_DEPRECATED)) __TVOS_PROHIBITED __WATCHOS_PROHIBITED;


#ifdef __cplusplus
}
#endif

CF_ASSUME_NONNULL_END

#endif /* __MIDIServices_h__ */
