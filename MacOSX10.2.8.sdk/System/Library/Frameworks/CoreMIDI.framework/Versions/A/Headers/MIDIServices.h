/*
 	File:   	CoreMIDI/MIDIServices.h
 
 	Contains:   API for communicating with MIDI hardware
 
 	Version:	Technology: Mac OS X
 				Release:	Mac OS X
 
 	Copyright:  (c) 2000-2002 by Apple Computer, Inc., all rights reserved.
 
 	Bugs?:  	For bug reports, consult the following page on
 				the World Wide Web:
 
 					http://developer.apple.com/bugreporter/
 
*/

#ifndef __MIDIServices_h__
#define __MIDIServices_h__

//  -----------------------------------------------------------------------------
/*!
	@header MIDIServices

	This is the header file for Mac OS X's MIDI system services.

<h2>History</h2>
	Apple's MIDI Manager (ca. 1990) had a simple model of the world.  There were
	application and driver clients, which had MIDI in/out ports, which could be
	interconnected in arbitrary ways.  This model failed to provide a way for
	applications to make reasonable assumptions about how to make bi-directional
	connections to a MIDI device.  MIDI Manager also had limitations on the
	number of ports per client, and became very unwieldy with the advent of
	large studios and multi-port MIDI interfaces such as the MIDI Time Piece and
	Studio 5.

	Opcode's OMS (1991) addressed some of the shortcomings of MIDI Manager. 
	There was the concept of a studio setup document, where drivers detected
	their devices, and the user could define the characteristics of additional
	devices connected to the MIDI ports. Applications could view the studio both
	as a collection of MIDI source and destination "nodes", but also as a
	collection of devices.  OMS collected information about, and made available
	to its clients, useful characteristics of the devices in the studio, such as
	their system-exclusive IDs, MIDI channels on which they were listening,
	which were controllers (as opposed to simple tone generators), etc.

<h2>API Overview</h2>
	This design expands slightly on OMS's device/node hierarchy, inspired by the
	USB MIDI spec.

	Drivers own and control devices, e.g. USB interfaces, PCI cards, etc.  A
	device is defined as a physical object that would be represented by a single
	icon if there were a graphical view of the studio.

	Devices may have multiple logically distinct sub-components, e.g. a MIDI
	synthesizer and a pair of MIDI ports, both addressable via a USB port. 
	These are called Entities.

	Entities have any number of Endpoints, sources and destinations of
	16-channel MIDI streams.  By grouping a device's endpoints into entities,
	the system has enough information for an application to make reasonable
	assumptions about how to communicate in a bi-directional manner with each
	entity, as is necessary in MIDI librarian applications.

	Third-party services like FreeMIDI or OMS can collect and report interesting
	properties of a device by attaching those properties to the devices'
	entities -- CoreMIDI provides a central database, but no user interfaces..
	It's worth noting that some device characteristics are dynamic
	(e.g. MIDI receive channel and system-exclusive ID's), or a matter of user
	preference (choice of icon, whether the device should appear in lists of
	possible controllers), while other properties are static and could be looked
	up in a database, using the device's manufacturer and model names as a key.

<h2>Persistent configurations / Device Information</h2>
	There are a number of reasons why CoreMIDI has a persistent state.

	Endpoints must have persistent ID's.  When a user assigns events in a
	sequencing application to an endpoint, the application needs a way to retain
	a permanent reference to the selected endpoint.  A brute-force method of
	generating a persistent ID would be to combine the driver name, device name,
	entity name, and endpoint type and index into a string, but this is not very
	friendly to clients even if the system provides services to generate and
	decode these strings.

	Consider a USB MIDI interface driver, in the case where there are two
	instances of one model of interface present.  The driver needs a way to
	permanently distinguish, to the system and its clients, between the two
	interfaces.  Which is #1 and which is #2? If #1 gets unplugged, #2 should
	not automatically become #1; the user's documents may be referring to
	devices which were attached to #2.

	The system needs a persistent concept of which driver's device is attached
	to a serial port.

	Some drivers will need to store configuration information about the devices
	they control.  For example, the driver for a standard MIDI interface on a
	serial port needs to remember which external clocking speed to use (this is
	a simple, slightly obscure, but hardly unique example).  The Alesis QS7 is
	capable of communicating at a variety of speeds, so its driver needs to
	remember the correct speed.

	These needs for persistent configuration information provide a rationale for
	having something akin to OMS's studio setup document, a saved configuration
	for the system. Mobile users who work in multiple environments could select
	between multiple saved configurations in a Location Manager-compatible
	manner.

	Given services with which to store driver configuration information, we then
	have built the groundwork for a client studio setup editor application. 
	Such an application can define external MIDI devices (not to
	be confused with the driver-owned cards/ interfaces/etc whose presence in
	the configuration is determined by the driver).

	Moreover, since a driver knows exactly what device it is communicating with,
	it is capable of supplying information to the system about the
	characteristics of the device, such as its system-exclusive ID, whether it
	is General MIDI or DLS-compatible, etc.

	But unlike OMS, the system is able to begin functioning immediately,
	using only the MIDI devices/endpoints detected by the drivers, without
	forcing the user to go through a somewhat lengthy and confusing intial
	configuration process. Definition of external MIDI devices can be a
	completely optional step, only made possible when a client application
	requests that they be added to the configuration.

<h2>Implementation overview</h2>
	The client API is implemented as the CoreMIDI framework, which uses IPC to
	communicate with a server process, MIDIServer.

	The server process loads, and manages all communication with, MIDI drivers.
	Most of its implementation is in the CoreMIDIServer framework, which drivers 
	may import in order to access the API.

	"Drivers" are not I/O Kit drivers.  They are dynamic libraries, using
	CFPlugin.

	Many MIDI drivers can simply be user-side I/O Kit clients (probably for
	serial, USB, Firewire).

	PCI card drivers will need their MIDI drivers to communicate with a separate
	kernel extension.

<h2>Note about CoreFoundation data types (CFString, CFData, CFDictionary)</h2>
	When passing a CF object to a MIDI function, the MIDI function will never
	consume a reference to the object; the caller always retains a reference
	which it is responsible for releasing with CFRelease().

	When receiving a CF object as a return value from a MIDI function, the caller
	always receives a new reference to the object, and is responsible for
	releasing it.
*/

//=============================================================================
//	Includes
//=============================================================================

#include <CoreServices/CoreServices.h>
#include <CoreFoundation/CoreFoundation.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif


//=============================================================================
//	Types
//=============================================================================

// opaque types

//  -----------------------------------------------------------------------------
/*!
	@typedef		MIDIObjectRef
	
	@discussion		MIDIObject is the base class for many of the objects in 
					CoreMIDI.  They have properties, and often an "owner" object, 
					from which they inherit any properties they do not themselves 
					have.

					Developers may add their own private properties, whose names 
					must begin with their company's inverted domain name, as in 
					Java package names, but with underscores instead of dots, e.g.:
						com_apple_APrivateAppleProperty
*/
typedef void *							MIDIObjectRef;
//  -----------------------------------------------------------------------------
/*!
	@typedef		MIDIClientRef
	
	@discussion		Derives from MIDIObjectRef, does not have an owner object.
	
					To use CoreMIDI, an application creates a MIDIClientRef,
					to which it can add MIDIPortRef's, through which it can
					send and receive MIDI.
*/
typedef struct OpaqueMIDIClient *		MIDIClientRef;
//  -----------------------------------------------------------------------------
/*!
	@typedef		MIDIPortRef
	
	@discussion		Derives from MIDIObjectRef, owned by a MIDIClientRef.

					A MIDIPortRef, which may be an input port or output port,
					is an object through which a client may communicate with any 
					number of MIDI sources or destinations.
*/
typedef struct OpaqueMIDIPort *			MIDIPortRef;
//  -----------------------------------------------------------------------------
/*!
	@typedef		MIDIDeviceRef
	
	@discussion		Derives from MIDIObjectRef, does not have an owner object.
	
					A MIDI device, which either attaches directly to the 
					computer and is controlled by a MIDI driver, or which is
					"external," meaning that it is connected to a driver-controlled
					device via a standard MIDI cable.  
					
					A MIDIDeviceRef has properties and contains MIDIEntityRef's.
*/
typedef struct OpaqueMIDIDevice *		MIDIDeviceRef;
//  -----------------------------------------------------------------------------
/*!
	@typedef		MIDIEntityRef
	
	@discussion		Derives from MIDIObjectRef, owned by a MIDIDeviceRef.
	
					Devices may have multiple logically distinct sub-components, 
					e.g. a MIDI synthesizer and a pair of MIDI ports, both 
					addressable via a USB port.
					
					By grouping a device's endpoints into entities, the system 
					has enough information for an application to make reasonable
					assumptions about how to communicate in a bi-directional 
					manner with each entity, as is desirable in MIDI librarian
					applications.

					These sub-components are MIDIEntityRef's.
*/
typedef struct OpaqueMIDIEntity *		MIDIEntityRef;
//  -----------------------------------------------------------------------------
/*!
	@typedef		MIDIEndpointRef
	
	@discussion		Derives from MIDIObjectRef, owned by a MIDIEntityRef,
					unless it is a virtual endpoint.
					
					Entities have any number of MIDIEndpointRef's, sources
					and destinations of 16-channel MIDI streams.				
*/
typedef struct OpaqueMIDIEndpoint *		MIDIEndpointRef;


// forward structure declarations

typedef struct MIDIPacketList			MIDIPacketList;
typedef struct MIDISysexSendRequest		MIDISysexSendRequest;
typedef struct MIDINotification			MIDINotification;

//  -----------------------------------------------------------------------------
/*!
	@typedef		MIDITimeStamp
	
	@discussion		A host clock time representing the time of an event, as
					returned by AudioGetCurrentHostTime() (or UpTime()).
	
					Since MIDI applications will tend to do a fair amount of
					math with the times of events, it's more convenient to use a
					UInt64 than an AbsoluteTime.
					
					See CoreAudio/HostTime.h.
*/
typedef UInt64							MIDITimeStamp;


//  -----------------------------------------------------------------------------
/*!
	@enum			MIDIObjectType's
	
	@discussion		Provides information about the actual type of a MIDIObjectRef.
*/
enum {
	kMIDIObjectType_Other				= -1,
	kMIDIObjectType_Device				= 0,
	kMIDIObjectType_Entity				= 1,
	kMIDIObjectType_Source				= 2,
	kMIDIObjectType_Destination			= 3,

	kMIDIObjectType_ExternalMask		= 0x10,
	kMIDIObjectType_ExternalDevice		= kMIDIObjectType_ExternalMask | kMIDIObjectType_Device,
	kMIDIObjectType_ExternalEntity		= kMIDIObjectType_ExternalMask | kMIDIObjectType_Entity,
	kMIDIObjectType_ExternalSource		= kMIDIObjectType_ExternalMask | kMIDIObjectType_Source,
	kMIDIObjectType_ExternalDestination	= kMIDIObjectType_ExternalMask | kMIDIObjectType_Destination
};

/*!
	@typedef		MIDIObjectType
	
	@discussion		Values are kMIDIObjectType_Device etc.
*/
typedef SInt32							MIDIObjectType;

/*!
	@typedef		MIDIUniqueID
	
	@discussion		An integer which uniquely identifies a MIDIObjectRef.
*/
typedef SInt32							MIDIUniqueID;


//=============================================================================
//	Callback functions
//=============================================================================

//  -----------------------------------------------------------------------------
/*!
	@typedef		MIDINotifyProc

	@discussion		This callback function is called when some aspect of the  
					current MIDI setup changes.  Currently the only defined 
					message is kMIDIMsgSetupChanged, which simply means, 
					"something changed."  msgData is null in this case.  It
					is called on the runloop (thread) on which MIDIClientCreate 
					was first called.

	@param			message	
						A structure containing information about what changed.
	@param			refCon
						The client's refCon passed to MIDIClientCreate.
*/
typedef void
(*MIDINotifyProc)(const MIDINotification *message, void *refCon);

//  -----------------------------------------------------------------------------
/*!
	@typedef		MIDIReadProc

	@discussion		This is a callback function through which a client receives
					incoming MIDI messages.
	
					A MIDIReadProc function pointer is passed to the
					MIDIInputPortCreate and MIDIDestinationCreate functions.  The
					CoreMIDI framework will create a high-priority receive
					thread on your client's behalf, and from that thread, your
					MIDIReadProc will be called when incoming MIDI messages
					arrive.  Because this function is called from a separate
					thread, be aware of the synchronization issues when accessing
					data in this callback.

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
(*MIDIReadProc)(const MIDIPacketList *pktlist, void *readProcRefCon, void *srcConnRefCon);

//  -----------------------------------------------------------------------------
/*!
	@typedef		MIDICompletionProc

	@discussion		Callback function to notify the client of the completion of
					a call to MIDISendSysex.
	
	@param			request
						The MIDISysexSendRequest which has completed, or been
						aborted.
*/
typedef void
(*MIDICompletionProc)(MIDISysexSendRequest *request);

//=============================================================================
//	Structs
//=============================================================================

//  -----------------------------------------------------------------------------
/*!
	@struct			MIDIPacket

	@discussion		One or more MIDI events occuring at a particular time.
	
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

//  -----------------------------------------------------------------------------
/*!
	@struct			MIDIPacketList

	@discussion		A list of MIDI events being received from, or being sent to,
					one endpoint.  Note that the packets, while defined as an
					array, may not be accessed as an array, since they are 
					variable-length.  To iterate through the packets in a packet
					list, use a loop such as:
					
					<pre>
					MIDIPacket *packet = &packetList->packet[0];
					for (int i = 0; i < packetList->numPackets; ++i) {
						...
						packet = MIDIPacketNext(packet);
					}
					</pre>
	
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

//  -----------------------------------------------------------------------------
/*!
	@struct			MIDISysexSendRequest
	
	@discussion		An asynchronous request to send a single system-exclusive
					MIDI event to a MIDI destination.
	
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
	Byte *				data;
	UInt32				bytesToSend;
	Boolean				complete;
	Byte				reserved[3];
	MIDICompletionProc	completionProc;
	void *				completionRefCon;
};

//  -----------------------------------------------------------------------------
/*!
	@typedef		MIDINotificationMessageID
	
	@discussion		
*/
typedef SInt32			MIDINotificationMessageID;

/*!
	@enum		MIDINotificationMessageID's

	@constant	kMIDIMsgSetupChanged	Some aspect of the current MIDISetup
										has changed.  No data.  Should ignore this
										message if messages 2-6 are handled.
	@constant	kMIDIMsgObjectAdded		A device, entity or endpoint was added.
										Structure is MIDIObjectAddRemoveNotification.
										New for CoreMIDI 1.3.
	@constant	kMIDIMsgObjectRemoved	A device, entity or endpoint was removed.
										Structure is MIDIObjectAddRemoveNotification.
										New for CoreMIDI 1.3.
	@constant	kMIDIMsgPropertyChanged	An object's property was changed.
										Structure is MIDIObjectPropertyChangeNotification.
										New for CoreMIDI 1.3.
	@constant	kMIDIMsgThruConnectionsChanged	A persistent MIDI Thru connection was created
										or destroyed.  No data.  New for CoreMIDI 1.3.
	@constant	kMIDIMsgSerialPortOwnerChanged	A persistent MIDI Thru connection was created
										or destroyed.  No data.  New for CoreMIDI 1.3.
*/
enum {
	kMIDIMsgSetupChanged		= 1,
	kMIDIMsgObjectAdded			= 2,
	kMIDIMsgObjectRemoved		= 3,
	kMIDIMsgPropertyChanged		= 4,
	kMIDIMsgThruConnectionsChanged = 5,
	kMIDIMsgSerialPortOwnerChanged = 6
};

/*!
	@struct			MIDINotification
	
	@discussion		A MIDINotification is a structure passed to a MIDINotifyProc,
					when CoreMIDI wishes to inform a client of a change in
					the state of the system.
	
	@field			messageID
						type of message
	@field			messageSize
						size of the entire message, including messageID and
						messageSize
*/
struct MIDINotification
{
	MIDINotificationMessageID	messageID;
	ByteCount					messageSize;
	// additional data may follow, depending on messageID
};

typedef struct MIDIObjectAddRemoveNotification
{
	MIDINotificationMessageID	messageID;
	ByteCount					messageSize;
	MIDIObjectRef				parent;		// parent of added/removed object, or NULL
	MIDIObjectType				parentType;	// undefined if parent is NULL
	MIDIObjectRef				child;		// added/removed object
	MIDIObjectType				childType;
} MIDIObjectAddRemoveNotification;

typedef struct MIDIObjectPropertyChangeNotification
{
	MIDINotificationMessageID	messageID;
	ByteCount					messageSize;
	MIDIObjectRef				object;
	MIDIObjectType				objectType;
	CFStringRef					propertyName;
} MIDIObjectPropertyChangeNotification;

//=============================================================================
//	Error codes
//=============================================================================
enum {
	kMIDIInvalidClient		= -10830,
	kMIDIInvalidPort		= -10831,
	kMIDIWrongEndpointType	= -10832,		// want source, got destination, or vice versa
	kMIDINoConnection		= -10833,		// attempt to close a non-existant connection
	kMIDIUnknownEndpoint	= -10834,
	kMIDIUnknownProperty	= -10835,
	kMIDIWrongPropertyType	= -10836,
	kMIDINoCurrentSetup		= -10837,		// there is no current setup, or it contains no
											// 		devices
	kMIDIMessageSendErr		= -10838,		// communication with server failed
	kMIDIServerStartErr		= -10839,		// couldn't start the server
	kMIDISetupFormatErr		= -10840,		// unparseable saved state
	kMIDIWrongThread		= -10841,		// driver is calling non I/O function in server
											//		 from a thread other than server's main one
	kMIDIObjectNotFound		= -10842,
	kMIDIIDNotUnique		= -10843
};


//=============================================================================
//	Property name constants
//=============================================================================

/*!
	@constant		kMIDIPropertyName
	@discussion		device/entity/endpoint property, string
	
		Devices, entities, and endpoints may all have names.  The recommended way
		to display an endpoint's name is to ask for the endpoint name, and display
		only that name if it is unique.  If it is non-unique, prepend the device
		name.
		
		A setup editor may allow the user to set the names of both driver-owned 
		and external devices.
*/
extern const CFStringRef	kMIDIPropertyName;		

/*!
	@constant		kMIDIPropertyManufacturer
	@discussion		device/endpoint property, string
	
		Drivers should set this property on their devices.
		
		Setup editors may allow the user to set this property on external devices.
		
		Creators of virtual endpoints may set this property on their endpoints.
*/
extern const CFStringRef	kMIDIPropertyManufacturer;

/*!
	@constant		kMIDIPropertyModel
	@discussion		device/endpoint property, string

		Drivers should set this property on their devices.
		
		Setup editors may allow the user to set this property on external devices.
		
		Creators of virtual endpoints may set this property on their endpoints.
*/
extern const CFStringRef	kMIDIPropertyModel;

/*!
	@constant		kMIDIPropertyUniqueID
	@discussion		devices, entities, endpoints all have unique ID's, integer
	
		The system assigns unique ID's to all objects.  Creators of virtual
		endpoints may set this property on their endpoints, though doing so
		may fail if the chosen ID is not unique.
*/
extern const CFStringRef	kMIDIPropertyUniqueID;

/*!
	@constant		kMIDIPropertyDeviceID
	@discussion		device/entity property, integer
	
		The entity's system-exclusive ID, in user-visible form
		
		Drivers may set this property on their devices or entities.
		
		Setup editors may allow the user to set this property on
		external devices.
*/
extern const CFStringRef	kMIDIPropertyDeviceID;

/*!
	@constant		kMIDIPropertyReceiveChannels
	@discussion		endpoint property, integer

		The value is a bitmap of channels on which the object receives, (1<<0)=ch 1...(1<<15)=ch 16.
		
		Drivers may set this property on their entities or endpoints.
		
		Setup editors may allow the user to set this property on external
		endpoints.
		
		Virtual destination may set this property on their endpoints.
*/
extern const CFStringRef	kMIDIPropertyReceiveChannels;

/*!
	@constant		kMIDIPropertyTransmitChannels
	@discussion		endpoint property, integer

		The value is a bitmap of channels on which the object transmits, (1<<0)=ch 1...(1<<15)=ch 16
		
		New for CoreMIDI 1.3.
*/
extern const CFStringRef	kMIDIPropertyTransmitChannels;

/*!
	@constant		kMIDIPropertyMaxSysExSpeed
	@discussion		device/entity/endpoint property, integer

		Set by the owning driver; should not be touched by other clients.
		maximum bytes/second of sysex messages sent to it
		(default is 3125, as with MIDI 1.0)
*/
extern const CFStringRef	kMIDIPropertyMaxSysExSpeed;


/*!
	@constant		kMIDIPropertyAdvanceScheduleTimeMuSec
	@discussion		device/entity/endpoint property, integer

		Set by the owning driver; should not be touched by other clients.
		If it is > 0, then it is a recommendation of how many microseconds 
		in advance clients should schedule output.  Clients should treat this
		value as a minimum.  For devices with a > 0 advance schedule time, 
		drivers will receive outgoing messages to the device at the time they 
		are sent by the client, via MIDISend, and the driver is responsible 
		for scheduling events to be played at the right times according to their
		timestamps.
		
		As of CoreMIDI 1.3, this property may also be set on virtual destinations
		(but only the creator of the destination should do so).
		When a client sends to a virtual destination with an advance schedule time
		of 0, the virtual destination receives its messages at their scheduled
		delivery time.  If a virtual destination has a non-zero advance schedule time,
		it receives timestamped messages as soon as they are sent, and must do its
		own scheduling of the events.
*/
extern const CFStringRef	kMIDIPropertyAdvanceScheduleTimeMuSec;

/*!
	@constant		kMIDIPropertyIsEmbeddedEntity
	@discussion		entity/endpoint property, integer

		0 if there are external MIDI connectors, 1 if not.

		New for CoreMIDI 1.1.
*/
extern const CFStringRef	kMIDIPropertyIsEmbeddedEntity;


/*!
	@constant		kMIDIPropertyIsBroadcast
	@discussion		entity/endpoint property, integer

		1 if the endpoint broadcasts messages to all of the other endpoints
		in the device, 0 if not.  Set by the owning driver; should not be touched
		by other clients.

		New for CoreMIDI 1.3.
*/
extern const CFStringRef	kMIDIPropertyIsBroadcast;

/*!
	@constant		kMIDIPropertySingleRealtimeEntity
	@discussion		device property, integer

		Some MIDI interfaces cannot route MIDI realtime messages to individual
		outputs; they are broadcast.  On such devices the inverse is usually
		also true -- incoming realtime messages cannot be identified as originating
		from any particular source.
		
		When this property is set on a driver device, it signifies the 0-based index of
		the entity on which incoming realtime messages from the device will appear
		to have originated from.

		New for CoreMIDI 1.3.
*/
extern const CFStringRef	kMIDIPropertySingleRealtimeEntity;

/*!
	@constant		kMIDIPropertyConnectionUniqueID
	@discussion		device/entity/endpoint property, integer or CFDataRef

		UniqueID of an external device/entity/endpoint attached to this one
		(strongly recommended that it be an endpoint).
		This is for the use of a setup editor UI; not currently used internally.
		A driver-owned entity or endpoint has this property to refer
		to an external MIDI device that is connected to it.
		
		The property is non-existant or 0 if there is no connection.

		New for CoreMIDI 1.1.
		
		Beginning with CoreMIDI 1.3, this property may be a CFDataRef containing
		an array of big-endian SInt32's, to allow specifying that a driver object connects
		to multiple external objects (via MIDI thru-ing or splitting).
		
		This property may also exist for external devices/entities/endpoints,
		in which case it signifies a MIDI Thru connection to another external
		device/entity/endpoint (again, strongly recommended that it be an edpoint).
*/
extern const CFStringRef	kMIDIPropertyConnectionUniqueID;


/*!
	@constant		kMIDIPropertyOffline
	@discussion		device/entity/endpoint property, integer

		1 = device is offline (is temporarily absent), 0 = present
		Set by the owning driver, on the device; should not be touched by other clients.
		Property is inherited from the device by its entities and endpoints.

		New for CoreMIDI 1.1.
*/
extern const CFStringRef	kMIDIPropertyOffline;

/*!
	@constant		kMIDIPropertyPrivate
	@discussion		device/entity/endpoint property, integer

		1 = endpoint is private, hidden from other clients.
		May be set on a device or entity, but they will still appear in the API; only
		affects whether the owned endpoints are hidden.

		New for CoreMIDI 1.3.
*/
extern const CFStringRef	kMIDIPropertyPrivate;

/*!
	@constant		kMIDIPropertyDriverOwner
	@discussion		device/entity/endpoint property, string

		Name of the driver that owns a device.
		Set by the owning driver, on the device; should not be touched by other clients.
		Property is inherited from the device by its entities and endpoints.

		New for CoreMIDI 1.1.
*/
extern const CFStringRef	kMIDIPropertyDriverOwner;

/*!
	@constant		kMIDIPropertyFactoryPatchNameFile
	@discussion		device/entity/endpoint property, CFData containing AliasHandle

		An alias to the device's current factory patch name file.

		Added in CoreMIDI 1.1.  DEPRECATED as of CoreMIDI 1.3.
		Use kMIDIPropertyNameConfiguration instead.
*/
extern const CFStringRef	kMIDIPropertyFactoryPatchNameFile;


/*!
	@constant		kMIDIPropertyUserPatchNameFile
	@discussion		device/entity/endpoint property, CFData containing AliasHandle

		An alias to the device's current user patch name file.

		Added in CoreMIDI 1.1.  DEPRECATED as of CoreMIDI 1.3.
		Use kMIDIPropertyNameConfiguration instead.
*/
extern const CFStringRef	kMIDIPropertyUserPatchNameFile;

/*!
	@constant		kMIDIPropertyNameConfiguration
	@discussion		device/entity/endpoint property, CFDictionary

					This specifies the device's current patch, note and control
					name values using the MIDINameDocument XML format.  This
					specification requires the use of higher-level, OS-specific constructs
					outside of the specification, to fully define the current
					names for a device.
					
					The MIDINameConfiguration property is implementated as a CFDictionary:
					
					key "master" maps to a CFDataRef containing an AliasHandle
					referring to the device's master name document.
					
					key "banks" maps to a CFDictionaryRef.  This dictionary's keys
					are CFStringRef names of patchBank elements in the master document,
					and its values are each a CFDictionaryRef: key "file" maps to a CFDataRef
					containing an AliasHandle to a document containing patches
					that override those in the master document, and key "patchNameList"
					maps to a CFStringRef which is the name of the patchNameList
					element in the overriding document.
					
					key "currentModes" maps to a 16-element CFArrayRef, each element
					of which is a CFStringRef of the name of the current mode for
					each of the 16 MIDI channels.
					
					Clients setting this property must take particular care to preserve dictionary
					values other than the ones they are interested in changing, and
					to properly structure the dictionary.
					
					New for CoreMIDI 1.3.
*/
extern const CFStringRef	kMIDIPropertyNameConfiguration;

/*!
	@constant		kMIDIPropertyImage
	@discussion		device property, CFStringRef which is a full POSIX path to a device
					or external device's icon, stored in any standard graphic file format such as
					JPEG, GIF, PNG and TIFF are all acceptable.  (See CFURL
					for functions to convert between POSIX paths and other ways
					of specifying files.)  The image's maximum size should be 128x128.
					
					Drivers should set the icon on the devices they add.
					
					A studio setup editor should allow the user to choose icons
					for external devices.
					
					New for CoreMIDI 1.3.
*/
extern const CFStringRef	kMIDIPropertyImage;

/*!
	@constant		kMIDIPropertyDriverVersion
	@discussion		device/entity/endpoint property, integer, returns the
					driver version API of the owning driver (only for driver-
					owned devices).  Drivers need not set this property;
					applications should not write to it.
					
					New for CoreMIDI 1.3.
*/
extern const CFStringRef	kMIDIPropertyDriverVersion;

// New for CoreMIDI 1.3, not yet documented
// these are all set on devices/entities, and are all integer properties, 0/1
extern const CFStringRef	kMIDIPropertySupportsGeneralMIDI;
extern const CFStringRef	kMIDIPropertySupportsMMC;	// MIDI Machine Control
extern const CFStringRef	kMIDIPropertyCanRoute;		// e.g. is patch bay

extern const CFStringRef	kMIDIPropertyReceivesClock;
extern const CFStringRef	kMIDIPropertyReceivesMTC;	// MIDI Time Code
extern const CFStringRef	kMIDIPropertyReceivesNotes;
extern const CFStringRef	kMIDIPropertyReceivesProgramChanges;
extern const CFStringRef	kMIDIPropertyReceivesBankSelectMSB;
extern const CFStringRef	kMIDIPropertyReceivesBankSelectLSB;

extern const CFStringRef	kMIDIPropertyTransmitsClock;
extern const CFStringRef	kMIDIPropertyTransmitsMTC;	// MIDI Time Code
extern const CFStringRef	kMIDIPropertyTransmitsNotes;
extern const CFStringRef	kMIDIPropertyTransmitsProgramChanges;
extern const CFStringRef	kMIDIPropertyTransmitsBankSelectMSB;
extern const CFStringRef	kMIDIPropertyTransmitsBankSelectLSB;

extern const CFStringRef	kMIDIPropertyPanDisruptsStereo;
extern const CFStringRef	kMIDIPropertyIsSampler;
extern const CFStringRef	kMIDIPropertyIsDrumMachine;
extern const CFStringRef	kMIDIPropertyIsMixer;
extern const CFStringRef	kMIDIPropertyIsEffectUnit;

// these are integers, 0-16, also set on devices/entities
extern const CFStringRef	kMIDIPropertyMaxReceiveChannels;
extern const CFStringRef	kMIDIPropertyMaxTransmitChannels;


// ______________________________________________________________________________
//	MIDIClient
// ______________________________________________________________________________

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIClientCreate

	@abstract 		Create a MIDIClient object.
	
	@discussion		All clients must be created and disposed on the same thread.
	
	@param			name
						The client's name.
	@param			notifyProc	
						An optional (may be NULL) callback function through which
						the client will receive notifications of changes to the
						system.
	@param			notifyRefCon 
						A refCon passed back to notifyRefCon
	@param			outClient	
						On successful return, points to the newly-created
						MIDIClientRef.
	@result			An OSStatus result code.
*/
extern OSStatus
MIDIClientCreate(	CFStringRef		name, 
					MIDINotifyProc	notifyProc, 
					void *			notifyRefCon, 
					MIDIClientRef *	outClient );


//  -----------------------------------------------------------------------------
/*!
	@function   	MIDIClientDispose

	@abstract   	Dispose a MIDIClient object.

	@discussion 	It is not essential to call this function; the CoreMIDI
					framework will automatically dispose all MIDIClients when an
					application terminates.
	
	@param  		client
						The client to dispose.
	@result			An OSStatus result code.
*/
extern OSStatus
MIDIClientDispose(	MIDIClientRef client );

// ______________________________________________________________________________
//	MIDIPort
// ______________________________________________________________________________

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIInputPortCreate

	@abstract 		Create an input port through which the client may receive
					incoming MIDI messages from any MIDI source.

	@discussion		After creating a port, use MIDIPortConnectSource to establish
					an input connection from any number of sources to your port.

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
*/
extern OSStatus 
MIDIInputPortCreate(	MIDIClientRef	client, 
						CFStringRef		portName, 
						MIDIReadProc	readProc, 
						void *			refCon, 
						MIDIPortRef *	outPort );

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIOutputPortCreate

	@abstract 		Create an output port through which the client may send
					outgoing MIDI messages to any MIDI destination.

	@discussion		Output ports provide a mechanism for MIDI merging.  The
					system assumes that each output port will be responsible for
					sending only a single MIDI stream to each destination, although
					a single port may address all of the destinations in the
					system.

	@param			client
						The client to own the newly-created port
	@param			portName
						The name of the port.
	@param			outPort
						On successful return, points to the newly-created
						MIDIPort.
	@result			An OSStatus result code.
*/
extern OSStatus
MIDIOutputPortCreate(	MIDIClientRef	client, 
						CFStringRef		portName, 
						MIDIPortRef *	outPort );

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIPortDispose

	@abstract 		Dispose a MIDIPort object.

	@discussion		It is not usually necessary to call this function; when an 
					application's MIDIClient's are automatically disposed at
					termination, or explicitly, via MIDIClientDispose, the
					client's ports are automatically disposed at this time.

	@param			port
						The port to dispose.
	@result			An OSStatus result code.
*/
extern OSStatus
MIDIPortDispose(	MIDIPortRef port );


//  -----------------------------------------------------------------------------
/*!
	@function		MIDIPortConnectSource

	@abstract 		Establish a connection from a source to a client's input port.

	@discussion		

	@param			port
						The port to which to create the connection.  This port's
						readProc is called with incoming MIDI from the source.
	@param			source
						The source from which to create the connection.
	@param			connRefCon	
						This refCon is passed to the MIDIReadProc, as a way to
						identify the source.
	@result			An OSStatus result code.
*/
extern OSStatus
MIDIPortConnectSource(	MIDIPortRef		port, 
						MIDIEndpointRef	source, 
						void *			connRefCon );


//  -----------------------------------------------------------------------------
/*!
	@function		MIDIPortDisconnectSource
	
	@abstract 		Close a previously-established source-to-input port 
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
							MIDIEndpointRef	source );


// ______________________________________________________________________________
//	System information
// ______________________________________________________________________________

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIGetNumberOfDevices

	@abstract 		Returns the number of devices in the system.

	@result			The number of devices in the system, or 0 if an error 
					occurred.
*/
extern ItemCount
MIDIGetNumberOfDevices();


//  -----------------------------------------------------------------------------
/*!
	@function		MIDIGetDevice

	@abstract 		Return one of the devices in the system.

	@discussion		Use this to enumerate the devices in the system.
	
					To enumerate the entities in the system, you can walk through
					the devices, then walk through the devices' entities.

					Note: If a client iterates through the devices and entities
					in the system, it will not ever visit any virtual sources and
					destinations created by other clients.  Also, a device
					iteration will return devices which are "offline"
					(were present in the past but are not currently present),
					while iterations through the system's sources and destinations 
					will not include the endpoints of offline devices.
					
					Thus clients should usually prefer MIDIGetNumberOfSources, 
					MIDIGetSource, MIDIGetNumberOfDestinations and MIDIGetDestination to
					iterating through devices and entities to locate endpoints.

	@param			deviceIndex0
						The index (0...MIDIGetNumberOfDevices()-1) of the device
						to return.
	@result			A reference to a device, or NULL if an error occurred.
*/
extern MIDIDeviceRef
MIDIGetDevice(	ItemCount deviceIndex0 );

			
//  -----------------------------------------------------------------------------
/*!
	@function		MIDIGetNumberOfSources

	@abstract 		Returns the number of sources in the system.

	@result			The number of sources in the system, or 0 if an error
					occurred.
*/
extern ItemCount
MIDIGetNumberOfSources();


//  -----------------------------------------------------------------------------
/*!
	@function		MIDIGetSource

	@abstract 		Return one of the sources in the system.

	@param			sourceIndex0	
						The index (0...MIDIGetNumberOfSources()-1) of the source
						to return
	@result			A reference to a source, or NULL if an error occurred.
*/
extern MIDIEndpointRef
MIDIGetSource(	ItemCount sourceIndex0 );


//  -----------------------------------------------------------------------------
/*!
	@function		MIDIGetNumberOfDestinations

	@abstract 		Returns the number of destinations in the system.

	@result			The number of destinations in the system, or 0 if an error 
					occurred.
*/
extern ItemCount
MIDIGetNumberOfDestinations();


//  -----------------------------------------------------------------------------
/*!
	@function		MIDIGetDestination

	@abstract 		Return one of the destinations in the system.

	@param			destIndex0	
						The index (0...MIDIGetNumberOfDestinations()-1) of the
						destination to return
	@result			A reference to a destination, or NULL if an error occurred.
*/
extern MIDIEndpointRef
MIDIGetDestination(	ItemCount destIndex0 );


//  -----------------------------------------------------------------------------
/*!
	@function		MIDIGetNumberOfExternalDevicees

	@abstract 		Returns the number of external MIDI devices in the system.

	@discussion		External MIDI devices are MIDI devices connected to endpoints 
					via a standard MIDI cable.  Their presence is completely 
					optional, only when a UI somewhere adds them.
					
					New for CoreMIDI 1.1.

	@result			The number of external devices in the system, or 0 if an error 
					occurred.
*/
extern ItemCount
MIDIGetNumberOfExternalDevices();

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIGetExternalDevice

	@abstract 		Return one of the external devices in the system.

	@discussion		Use this to enumerate the external devices in the system.

					New for CoreMIDI 1.1.

	@param			deviceIndex0
						The index (0...MIDIGetNumberOfDevices()-1) of the device
						to return.
	@result			A reference to a device, or NULL if an error occurred.
*/
extern MIDIDeviceRef
MIDIGetExternalDevice(	ItemCount deviceIndex0 );

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIObjectFindByUniqueID

	@abstract 		Locate a device, external device, entity, or endpoint
					by its uniqueID.

	@discussion		New for CoreMIDI 1.3.

	@param			inUniqueID
						The uniqueID of the object to search for.  (This should
						be the result of an earlier call to MIDIObjectGetIntegerProperty
						for the property kMIDIPropertyUniqueID).
	@param			outObject
						The returned object, or NULL if the object was not found or
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
							MIDIObjectRef *		outObject,
							MIDIObjectType *	outObjectType);

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIEntityGetDevice

	@abstract 		Returns an entity's device.
	@discussion		New for CoreMIDI 1.3.
*/
extern OSStatus
MIDIEntityGetDevice(		MIDIEntityRef		inEntity,
							MIDIDeviceRef *		outDevice);

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIEndpointGetEntity

	@abstract 		Returns an endpoint's entity.
	@discussion		Virtual sources and destinations don't have entities.
	
					New for CoreMIDI 1.3.
*/
extern OSStatus
MIDIEndpointGetEntity(		MIDIEndpointRef		inEndpoint,
							MIDIEntityRef *		outEntity);

// ______________________________________________________________________________
//	Virtual endpoints
// ______________________________________________________________________________

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIDestinationCreate

	@abstract 		Create a virtual destination in a client.

	@discussion		Clients may use this to create virtual destinations.
				
					The specified readProc gets called when clients send MIDI to
					your virtual destination.

					Drivers need not call this; when they create devices and
					entities, sources and destinations are created at that time.
					
					See the discussion of kMIDIPropertyAdvanceScheduleTimeMuSec
					for notes about the relationship between when a sender sends
					MIDI to the destination and when it is received.
	
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
*/
extern OSStatus
MIDIDestinationCreate(	MIDIClientRef 		client, 
						CFStringRef 		name, 
						MIDIReadProc 		readProc, 
						void *				refCon, 
						MIDIEndpointRef *	outDest );


//  -----------------------------------------------------------------------------
/*!
	@function		MIDISourceCreate

	@abstract 		Create a virtual source in a client.

	@discussion		Clients may use this to create virtual sources.
				
					Drivers need not call this; when they create devices and
					entities, sources and destinations are created at that time.

					After creating a virtual source, use MIDIReceived to transmit
					MIDI messages from your virtual source to any clients
					connected to the virtual source.
	
	@param			client
						The client owning the virtual source.
	@param			name
						The name of the virtual source.
	@param			outSrc
						On successful return, a pointer to the newly-created
						source.
	@result			An OSStatus result code.
*/
extern OSStatus
MIDISourceCreate(	MIDIClientRef 		client, 
					CFStringRef 		name, 
					MIDIEndpointRef *	outSrc );


//  -----------------------------------------------------------------------------
/*!
	@function		MIDIEndpointDispose

	@abstract 		Dispose a virtual source or destination your client created.

	@param			endpt	The endpoint to be disposed.

	@result			An OSStatus result code.
*/
extern OSStatus
MIDIEndpointDispose(	MIDIEndpointRef endpt );


// ______________________________________________________________________________
//	I/O
// ______________________________________________________________________________

//  -----------------------------------------------------------------------------
/*!
	@function		MIDISend

	@abstract 		Send MIDI to a destination.

	@discussion		Events with future timestamps are scheduled for future
					delivery.  The system performs any needed MIDI merging.

	@param			port
						The output port through which the MIDI is to be sent.
	@param			dest
						The destination to receive the events.
	@param			pktlist
						The MIDI events to be sent.
	@result			An OSStatus result code.
*/
extern OSStatus
MIDISend(	MIDIPortRef 			port, 
			MIDIEndpointRef 		dest, 
			const MIDIPacketList *	pktlist );
				
//  -----------------------------------------------------------------------------
/*!
	@function		MIDISendSysex

	@abstract 		Send a single system-exclusive event, asynchronously.

	@discussion		request->data must point to a single MIDI system-exclusive 
					message, or portion thereof.

	@param			request	
						Contains the destination, and the MIDI data to be sent.
	@result			An OSStatus result code.
*/
extern OSStatus 
MIDISendSysex(	MIDISysexSendRequest *request );

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIReceived

	@abstract 		Distribute MIDI from a source to the client input ports
					which are connected to that source.

	@discussion		Drivers should call this function when receiving MIDI from
					a source.

					Clients which have created virtual sources, using
					MIDISourceCreate, should call this function when the source
					is generating MIDI.
					
	@param			src
						The source which is transmitting MIDI.
	@param			pktlist
						The MIDI events to be transmitted.
	@result			An OSStatus result code.
*/
extern OSStatus 
MIDIReceived(	MIDIEndpointRef			src, 
				const MIDIPacketList *	pktlist );

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIFlushOutput
	
	@abstract		Unschedule previously-sent packets.

	@discussion		Clients may use MIDIFlushOutput to cancel the sending of 
					packets that were previously scheduled for future delivery.
					
					New for CoreMIDI 1.1.

	@param			dest
						All pending events scheduled to be sent to this destination
						are unscheduled.  If NULL, the operation applies to
						all destinations.
*/
extern OSStatus
MIDIFlushOutput(	MIDIEndpointRef		dest );

// ______________________________________________________________________________
//	MIDIObject
// ______________________________________________________________________________

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIObjectGetIntegerProperty

	@abstract 		Get an object's integer-type property.

	@discussion		(See the MIDIObjectRef documentation for information
					about properties.)
	
	@param			obj
						The object whose property is to be returned.
	@param			propertyID
						Name of the property to return.
	@param			outValue
						On successful return, the value of the property.
	@result			An OSStatus result code.
*/
extern OSStatus
MIDIObjectGetIntegerProperty(	MIDIObjectRef	obj, 
								CFStringRef		propertyID, 
								SInt32 *		outValue );

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIObjectSetIntegerProperty

	@abstract 		Set an object's integer-type property.
	
	@discussion		(See the MIDIObjectRef documentation for information
					about properties.)
	
	@param			obj
						The object whose property is to be altered.
	@param			propertyID
						Name of the property to set.
	@param			value
						New value of the property.
	@result			An OSStatus result code.
*/
extern OSStatus
MIDIObjectSetIntegerProperty(	MIDIObjectRef	obj, 
								CFStringRef		propertyID, 
								SInt32			value );

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIObjectGetStringProperty

	@abstract 		Get an object's string-type property.

	@discussion		(See the MIDIObjectRef documentation for information
					about properties.)
		
	@param			obj
						The object whose property is to be returned.
	@param			propertyID
						Name of the property to return.
	@param			str
						On successful return, the value of the property.
	@result			An OSStatus result code.
*/
extern OSStatus
MIDIObjectGetStringProperty(	MIDIObjectRef	obj, 
								CFStringRef		propertyID, 
								CFStringRef *	str );

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIObjectSetStringProperty

	@abstract 		Set an object's string-type property.
	
	@discussion		(See the MIDIObjectRef documentation for information
					about properties.)
	
	@param			obj
						The object whose property is to be altered.
	@param			propertyID
						Name of the property to set.
	@param			str
						New value of the property.
	@result			An OSStatus result code.
*/
extern OSStatus
MIDIObjectSetStringProperty(	MIDIObjectRef	obj, 
								CFStringRef		propertyID,
								CFStringRef		str );

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIObjectGetDataProperty

	@abstract 		Get an object's data-type property.

	@discussion		(See the MIDIObjectRef documentation for information
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
MIDIObjectGetDataProperty(		MIDIObjectRef	obj, 
								CFStringRef		propertyID, 
								CFDataRef *		outData );

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIObjectSetDataProperty

	@abstract 		Set an object's data-type property.
	
	@discussion		(See the MIDIObjectRef documentation for information
					about properties.)
	
	@param			obj
						The object whose property is to be altered.
	@param			propertyID
						Name of the property to set.
	@param			data
						New value of the property.
	@result			An OSStatus result code.
*/
extern OSStatus
MIDIObjectSetDataProperty(		MIDIObjectRef	obj, 
								CFStringRef		propertyID, 
								CFDataRef		data );

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIObjectGetDictionaryProperty

	@abstract 		Get an object's dictionary-type property.

	@discussion		(See the MIDIObjectRef documentation for information
					about properties.)
					
					New for CoreMIDI 1.3.
		
	@param			obj
						The object whose property is to be returned.
	@param			propertyID
						Name of the property to return.
	@param			outDict
						On successful return, the value of the property.
	@result			An OSStatus result code.
*/
extern OSStatus
MIDIObjectGetDictionaryProperty(	MIDIObjectRef		obj, 
									CFStringRef			propertyID, 
									CFDictionaryRef *	outDict );

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIObjectSetDictionaryProperty

	@abstract 		Set an object's dictionary-type property.
	
	@discussion		(See the MIDIObjectRef documentation for information
					about properties.)
	
					New for CoreMIDI 1.3.
		
	@param			obj
						The object whose property is to be altered.
	@param			propertyID
						Name of the property to set.
	@param			dict
						New value of the property.
	@result			An OSStatus result code.
*/
extern OSStatus
MIDIObjectSetDictionaryProperty(MIDIObjectRef	obj, 
								CFStringRef		propertyID, 
								CFDictionaryRef	data );

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIObjectGetProperties
	
	@abstract		Get all of an object's properties.

	@param			obj
						The object whose properties are to be returned.
	@param			outProperties
						On successful return, the object's properties.
	@param			deep
						true if the object's child objects are to be included
						(e.g. a device's entities, or an entity's endpoints).
	@result			An OSStatus result code.

	@discussion		Returns a CFPropertyList of all of an object's properties.
					The property list may be a dictionary or an array.
					Dictionaries map property names (CFString) to values, 
					which may be CFNumber, CFString, or CFData.  Arrays are
					arrays of such values.
					
					Properties which an object inherits from its owning object (if
					any) are not included.

					New for CoreMIDI 1.1.
*/
extern OSStatus
MIDIObjectGetProperties(		MIDIObjectRef 		obj, 
								CFPropertyListRef *	outProperties,
								Boolean				deep );

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIObjectRemoveProperty
	
	@abstract		Remove an object's property.

	@param			obj
						The object whose property is to be removed.
	@param			propertyID
						The property to be removed.
	@result			An OSStatus result code.

	@discussion		New for CoreMIDI 1.3.
*/
extern OSStatus
MIDIObjectRemoveProperty(		MIDIObjectRef 		obj, 
								CFStringRef			propertyID );


// ______________________________________________________________________________

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIRestart

	@abstract 		Stops and restarts MIDI I/O.
	
	@discussion		This is useful for forcing the system to have drivers
					rescan hardware, especially in the case of serial MIDI
					interfaces.
	
					New for CoreMIDI 1.1.

	@result			An OSStatus result code.	
*/
extern OSStatus
MIDIRestart();

// ______________________________________________________________________________
//	MIDIDevice
// ______________________________________________________________________________

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIDeviceGetNumberOfEntities

	@abstract 		Return the number of entities in a given device.
	
	@param			device
						The device being queried.

	@result			The number of entities the device contains, or 0 if an
					error occurred.
*/
extern ItemCount 
MIDIDeviceGetNumberOfEntities(	MIDIDeviceRef device );

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIDeviceGetEntity

	@abstract 		Return one of a given device's entities.
	
	@param			device
						The device being queried.
	@param			entityIndex0
						The index (0...MIDIDeviceGetNumberOfEntities(device)-1)
						of the entity to return

	@result			A reference to an entity, or NULL if an error occurred.
*/
extern MIDIEntityRef
MIDIDeviceGetEntity(	MIDIDeviceRef	device,
						ItemCount		entityIndex0 );

// ______________________________________________________________________________
//	MIDIEntity
// ______________________________________________________________________________

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIEntityGetNumberOfSources
	
	@abstract 		Return the number of sources in a given entity.
	
	@param			entity
						The entity being queried

	@result			The number of sources the entity contains, or 0 if an
					error occurred.
*/
extern ItemCount
MIDIEntityGetNumberOfSources(	MIDIEntityRef entity );

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIEntityGetSource

	@abstract 		Return one of a given entity's sources.
	
	@param			entity
						The entity being queried.
	@param			sourceIndex0
						The index (0...MIDIEntityGetNumberOfSources(entity)-1) of
						the source to return

	@result			A reference to a source, or NULL if an error occurred.
*/
extern MIDIEndpointRef
MIDIEntityGetSource(	MIDIEntityRef entity, 
						ItemCount sourceIndex0 );

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIEntityGetNumberOfDestinations

	@abstract 		Return the number of destinations in a given entity.
	
	@param			entity	The entity being queried

	@result			The number of destinations the entity contains, or 0
					if an error occurred.
*/
extern ItemCount
MIDIEntityGetNumberOfDestinations(	MIDIEntityRef entity );

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIEntityGetDestination

	@abstract 		Return one of a given entity's destinations.
	
	@param			entity
						The entity being queried.
	@param			destIndex0
						The index (0...MIDIEntityGetNumberOfDestinations(entity)
						- 1) of the destination to return

	@result			A reference to a destination, or NULL if an error occurred.
*/
extern MIDIEndpointRef
MIDIEntityGetDestination(	MIDIEntityRef	entity,
							ItemCount		destIndex0 );


// ______________________________________________________________________________
//	MIDIPacketList utilities
// ______________________________________________________________________________

#if I_WANT_HEADERDOC_TO_THINK_THIS_IS_A_FUNCTION_NOT_A_MACRO
//  -----------------------------------------------------------------------------
/*!
	@function		MIDIPacketNext

	@abstract 		Advance a MIDIPacket pointer to the MIDIPacket which
					immediately follows it in memory if it is part of a
					MIDIPacketList.

	@discussion		This is implemented as a macro for efficiency and to avoid
					const problems.

	@param			pkt
						A pointer to a MIDIPacket in a MIDIPacketList.

	@result			The subsequent packet.
*/
extern MIDIPacket *
MIDIPacketNext(	MIDIPacket *pkt );
#endif

#define MIDIPacketNext(pkt)	((MIDIPacket *)&(pkt)->data[(pkt)->length])


//  -----------------------------------------------------------------------------
/*!
	@function		MIDIPacketListInit

	@abstract 		Prepare a MIDIPacketList to be built up dynamically.
	
	@param			pktlist
						The packet list to be initialized.

	@result			A pointer to the first MIDIPacket in the packet list.
*/
extern MIDIPacket *
MIDIPacketListInit(	MIDIPacketList *pktlist );


//  -----------------------------------------------------------------------------
/*!
	@function		MIDIPacketListAdd

	@abstract 		Add a MIDI event to a MIDIPacketList.
	
	@discussion
	
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
*/
extern MIDIPacket *
MIDIPacketListAdd(	MIDIPacketList *	pktlist,
					ByteCount			listSize,
					MIDIPacket *		curPacket,
					MIDITimeStamp		time,
					ByteCount			nData,
					const Byte *		data);


#ifdef __cplusplus
}
#endif

#endif /* __MIDIServices_h__ */
