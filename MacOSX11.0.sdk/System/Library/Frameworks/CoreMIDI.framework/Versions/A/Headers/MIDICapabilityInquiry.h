/*
 File:       CoreMIDI/MIDICapabilityInquiry.h
 
 Contains:   API for MIDI Capability Inquiry (MIDI-CI)
 
 Copyright:  (c) 2018-2020 by Apple Inc., all rights reserved.
 
 Bugs?:      For bug reports, consult the following page on
 the World Wide Web:
 
 http://feedbackassistant.apple.com/
 */

// This API requires the modern Objective-C runtime.
#if !defined(MIDICapabilityInquiry_h)
#define MIDICapabilityInquiry_h

/*!
    @header MIDICapabilityInquiry.h

    This is the header file for MIDI Capability Inquiry (MIDI-CI) system services.

	API Overview
	------------
	
    MIDI-CI is the portion of MIDI 2.0 that allows for the selection of data protocol and the
    advertisement and manipulation of profiles and properties. These three capabilities are
    sometimes referred to as the three P's. MIDI 2.0 (and specifically MIDI-CI) are bidirectional
    protocols, unlike MIDI 1.0 which could be unidirectional or bidirectional.

    The two sides of MIDI-CI communication are the Initiator and Responder. Most MIDI-CI messages
    can only be sent from the Initiator or from the Responder, but a small number of messages could
    originate from the Initiator or the Responder.

    MIDI client processes playing the Initiator roles of a MIDI-CI connection use the MIDICISession
    API, which allows for profile and property manipulation on the associated responder. MIDI client
    processes that wish to advertise their own profile and property capabilities use the MIDICIResponder
    API, which is capable of sending Responder-originated MIDI-CI messages to Initiators.

	Implementation overview
	-----------------------
	
    With MIDI-CI beta enabled, Universal MIDI System Exclusive (SysEx) messages are filtered from the
    I/O stream and sent to the MIDI-CI subsystem for routing and handling. Other SysEx messages are
    untouched. In the release API, filtering will be on by default, and Universal MIDI SysEx messages
    with associated CoreMIDI API will only be received and routed by the MIDI-CI subsystem.
 
    Discovering MIDI-CI capable nodes managed by CoreMIDI is accomplished with MIDICIDiscoveryManager,
    which sends a MIDI-CI discovery message to all MIDI destinations in the system and aggregates the
    respondents as MIDICIDiscoveredNode objects.
        
    After MIDI-CI discovery has been performed, a MIDI client process may act as Initiator by creating
    a MIDICISession using a MIDICIDiscoveredNode. The MIDICISession is synchronously returned prior to
    capability inquiry, and the supplied handler is invoked once the results are received or after
    timeout. Any available profiles may then be examined/toggled for each channel and the whole port
    (represented  by MIDI channel 0x7F).
    
    No API for protocol negotiation is currently supplied. CoreMIDI is MIDI 2.0-capable system-wide
    and will not only select the appropriate protocol for connected hardware but will also automatically
    convert between MIDI 1.0 and MIDI 2.0 protocol as needed. See MIDIServices.h for API guidelines and
    usage for MIDI 2.0 protocol and Universal MIDI Packets (UMP).
    
    Additionally, no explicit property exchange API is provided. However, property exchange can be
    accomplished by performing first performing MIDI-CI discovery and then sending the appropriate
    Universal MIDI SysEx messages to the supplied destination and monitoring the MIDICISession's
    supplied source. Responses to Has Property, Get Property, Set Property, and Subscribe to
    Property messages are not filtered by the MIDI-CI subsystem and can be received by any MIDI client.
    However, Property Exchange capabilities must still be discovered using API first since the
    Inquiry: Property Exchange Capabilities (msg ID 0x30) and Reply to Property Exchange Capabilities
    (msg ID 0x31) are reserved by CoreMIDI.
     
    A MIDI client process may also/instead play the role of responder by creating a MIDICIResponderDelegate
    and then a MIDICIResponder. Similarly to MIDICISession, a MIDICIResponder may advertise property
    capabilities, but the details of property exchange rely on the implementation.
 
    Please visit http://www.midi.org/specifications for more information on MIDI Capability Inquiry
    and a list of currently defined capabilities.
*/


#import <CoreMIDI/MIDIServices.h>

/// MIDI Channel, 0~15 (channels 1 through 16, respectively), or MIDIChannelsWholePort.
/// Per the MIDI-CI specification, this is always a single byte.
typedef uint8_t MIDIChannelNumber;

/// All MIDI-CI methods involving a channel number use 0x7f to mean "the whole port", i.e. all
/// channels.
static const MIDIChannelNumber MIDIChannelsWholePort = 0x7f;

/*!
 @struct MIDICIDeviceIdentification
 @brief  struct describing a MIDI-CI device.
 */
struct MIDICIDeviceIdentification {
    uint8_t manufacturer[3];
    uint8_t family[2];
    uint8_t modelNumber[2];
    uint8_t revisionLevel[4];
    uint8_t reserved[5];		// always zero
};
typedef struct MIDICIDeviceIdentification MIDICIDeviceIdentification;

#if defined(__OBJC2__)
#import <Foundation/Foundation.h>
#import <stdint.h>

#define MIDICI1_0_AVAILABILITY API_AVAILABLE(macos(10.14), ios(12.0)) API_UNAVAILABLE(watchos, tvos)
#define MIDICI1_1_AVAILABILITY API_AVAILABLE(macos(11.0), ios(14.0)) API_UNAVAILABLE(watchos, tvos)

NS_ASSUME_NONNULL_BEGIN

// Forward declarations.
@class MIDICISession;
@class MIDICIProfile;
@class MIDICIProfileState;
@class MIDICIResponder;
@class MIDICIDiscoveredNode;

//! The unique MIDI-CI negotiation identifier (MUID) used for a MIDICIResponder connection.
//! Per the MIDI-CI specification, this is a randomly assigned 28-bit integer.
typedef NSNumber * MIDICIInitiatiorMUID;

//! An array of MIDICIProfileState objects that describes the profile
//! configuration for all channels for a reachable MIDI-CI node.
typedef NSArray<MIDICIProfileState *> MIDICIProfileStateList;

// =================================================================================================

/*!
 	@class		MIDICIDeviceInfo
 	@brief  	An NSObject containing basic information about a MIDI-CI-capable node.
*/
MIDICI1_1_AVAILABILITY
@interface MIDICIDeviceInfo : NSObject <NSSecureCoding>

/// The MIDI System Exclusive ID of the device manufacturer, 3 bytes long. One-byte SysEx IDs are
/// padded with trailing zeroes (e.g., Apple's System Exclusive ID, 0x11, would be expressed as 0x110000).
@property (nonatomic, readonly) NSData *manufacturerID;		// 3 bytes

/// The group of models to which the device belongs, 2 bytes.
@property (nonatomic, readonly) NSData *family;				// 2 bytes

/// The specific model from the device manufacturer, 2 bytes.
@property (nonatomic, readonly) NSData *modelNumber;		// 2 bytes

/// The version number of a device model number, 2 bytes.
@property (nonatomic, readonly) NSData *revisionLevel;		// 4 bytes

/// The MIDI destination used by device's MIDI entity for capability inquiries.
@property (nonatomic, readonly) MIDIEndpointRef midiDestination;

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithDestination:(MIDIEntityRef)midiDestination manufacturer:(NSData *)manufacturer family:(NSData *)family model:(NSData *)modelNumber revision:(NSData *)revisionLevel;
@end

// =================================================================================================

/*!
 	@class		MIDICIProfile
 	@abstract  	An NSObject representing Capability Inquiry profile. MIDI-CI profiles describe a mapping
				of MIDI messages to specific sounds and synthesis behaviors, e.g. General MIDI, a drawbar organ,
				etc. A MIDI-CI profile may be a standard registered profile or vendor-specific.
 
								Standard Profile				Vendor-Specific Profile
				Profile ID Byte 1:	0x7E Standard Profile			Manufacturer SysEx ID 1 Profile
				Profile ID Byte 2:	Profile Bank				Manufacturer SysEx ID 2 Profile
				Profile ID Byte 3:	Profile Number				Manufacturer SysEx ID 3 Profile
				Profile ID Byte 4:	Profile Version				Manufacturer-specific Info
				Profile ID Byte 5:	Profile Level				Manufacturer-specific Info
*/
MIDICI1_0_AVAILABILITY
@interface MIDICIProfile : NSObject <NSSecureCoding>

/// An NSString describing the profile.
@property (nonatomic, readonly) NSString *name;

/// The unique 5-byte profile identifier representing the profile.
@property (nonatomic, readonly) NSData *profileID;	// always 5 bytes

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithData:(NSData *)data MIDICI1_1_AVAILABILITY;
- (instancetype)initWithData:(NSData *)data name:(NSString *)inName;
@end

// =================================================================================================

/*!
 	@class	MIDICIProfileState
 	@brief  Lists the enabled and disabled profiles for a MIDI channel or port on a device.
*/
MIDICI1_0_AVAILABILITY
@interface MIDICIProfileState : NSObject <NSSecureCoding>
@property (nonatomic, readonly) MIDIChannelNumber midiChannel;
@property (nonatomic, readonly) NSArray<MIDICIProfile *> *enabledProfiles;
@property (nonatomic, readonly) NSArray<MIDICIProfile *> *disabledProfiles;

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithChannel:(MIDIChannelNumber)midiChannelNum enabledProfiles:(NSArray<MIDICIProfile *> *)enabled disabledProfiles:(NSArray<MIDICIProfile *> *)disabled MIDICI1_1_AVAILABILITY;
- (instancetype)initWithEnabledProfiles:(NSArray<MIDICIProfile *> *)enabled disabledProfiles:(NSArray<MIDICIProfile *> *)disabled API_DEPRECATED_WITH_REPLACEMENT("initWithChannel:enabledProfiles:disabledProfiles", macos(10.14, API_TO_BE_DEPRECATED), ios(12.0, API_TO_BE_DEPRECATED));
@end

// =================================================================================================

/*!
     @class    MIDICIDiscoveredNode
     @brief     An object created during MIDI-CI discovery representing a MIDI destination with an
                 associated MIDI source that responds to capability inquiries.
*/
MIDICI1_1_AVAILABILITY
@interface MIDICIDiscoveredNode : NSObject <NSSecureCoding>
@property (nonatomic, readonly) MIDIEntityRef 		destination;
@property (nonatomic, readonly) MIDICIDeviceInfo *	deviceInfo;
@property (nonatomic, readonly) BOOL 				supportsProfiles;
@property (nonatomic, readonly) BOOL 				supportsProperties;
@property (nonatomic, readonly) NSNumber *          maximumSysExSize;

-(instancetype)init NS_UNAVAILABLE;
@end

// =================================================================================================

/*!
 	@fn     MIDICIProfileChangedBlock
 	@brief  A block called when a device notifies that a profile has been enabled or disabled.
*/
typedef void (^MIDICIProfileChangedBlock)(
				MIDICISession *session, MIDIChannelNumber channel, MIDICIProfile *profile, BOOL enabled);

/*!
     @fn     MIDICISessionDisconnectBlock
     @brief  A block called when a MIDICISession has been disconnected. If called, the MIDICISession should be destroyed.
*/
typedef void (^MIDICISessionDisconnectBlock)(
                MIDICISession *session, NSError *error);

/*!
     @fn     MIDICIProfileSpecificDataBlock
     @brief  A block called when a MIDICISession or MIDICIResponder receives profile-specific data.
*/
typedef void (^MIDICIProfileSpecificDataBlock)(
                MIDICISession *session, MIDIChannelNumber channel, MIDICIProfile *profile, NSData *profileSpecificData);

/*!
     @fn     MIDICIDiscoveryResponseBlock
     @brief  A block called when a MIDI-CI node discovery is complete.
*/
typedef void (^MIDICIDiscoveryResponseBlock)(
                NSArray<MIDICIDiscoveredNode *> *discoveredNodes);

// =================================================================================================

/*!
     @class  MIDICISession
     @brief  Object representating a MIDI Capability Inquiry session.
 
     A MIDI Capability Inquiry session is a bidirectional communication path between a MIDI process
     and a MIDI-CI node (i.e., paired MIDI source and destination) identified using MIDI-CI discovery.
     A MIDICISession can be used to manipulate MIDI-CI profiles and to discover the MIDI-CI property
     capability.
*/
MIDICI1_0_AVAILABILITY
@interface MIDICISession : NSObject

/*!
	@brief  Begin a MIDI-CI session with the provided discovered node.
 
	dataReadyHandler will be called when properties of the session have become available.
	Other methods of this class will not return valid/useful information before the dataReadyHandler
	is called.
 
	disconnectHandler will be called if the active MIDICISession is disconnected by the Responder
    or if initial MIDI-CI discovery was unsuccessful.
*/
- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithDiscoveredNode:(MIDICIDiscoveredNode *)discoveredNode dataReadyHandler:(void (^)(void))handler disconnectHandler:(MIDICISessionDisconnectBlock)disconnectHandler;

/// The MIDI destination with which the session is communicating.
@property (nonatomic, readonly) MIDIEntityRef midiDestination;

// After CI session data is ready, indicates whether the entity supports the MIDI-CI profile capability.
@property (nonatomic, readonly) BOOL supportsProfileCapability;

// After CI session data is ready, indicates whether the entity supports the MIDI-CI property exchange capability.
@property (nonatomic, readonly) BOOL supportsPropertyCapability;

/// Obtain the device's basic identification. Nil before data is ready or if the device does not
/// support MIDI-CI.
@property (nonatomic, readonly) MIDICIDeviceInfo *deviceInfo;

// The maximum MIDI system exclusive size reported by the device during discovery
@property (nonatomic, readonly) NSNumber *maxSysExSize; // unsigned long

// The maximum number of simultaneous property exchange requests, if supported
@property (nonatomic, readonly) NSNumber *maxPropertyRequests; // int

/// Given a MIDI channel number, return the supported profiles. Note that the
/// arrays will be empty if this property is queried before data is ready.
- (MIDICIProfileState *)profileStateForChannel:(MIDIChannelNumber)channel;

/// Given a MIDI channel number, asynchronously request that the supplied profile be enabled.
/// The result of this operation is sent to the MIDICIProfileChangedBlock.
/// Returns YES if the request is valid.
- (BOOL)enableProfile:(MIDICIProfile *)profile
			onChannel:(MIDIChannelNumber)channel
				error:(NSError **)outError;

/// Given a MIDI channel number, asynchronously request that the supplied profile be disabled.
/// The result of this operation is sent to the MIDICIProfileChangedBlock.
/// Returnes YES if the request is valid.
- (BOOL)disableProfile:(MIDICIProfile *)profile
			 onChannel:(MIDIChannelNumber)channel
				 error:(NSError **)outError;

/// Given a MIDI channel number, send profile specific data to the MIDICISession.
/// Returns YES if the data was successfully sent.
- (BOOL)sendProfile:(MIDICIProfile *)profile onChannel:(MIDIChannelNumber)channel profileData:(NSData *)profileSpecificData MIDICI1_1_AVAILABILITY;

/// An optional block called when a device signals that a profile has been enabled or disabled.
@property (nonatomic, copy, nullable) MIDICIProfileChangedBlock profileChangedCallback;

/// An optional block called when a device sends profile-specific data to the session.
@property (nonatomic, copy, nullable) MIDICIProfileSpecificDataBlock profileSpecificDataHandler;

@end // MIDICISession

// =================================================================================================

/*!
     @class  MIDICIDiscoveryManager
     @brief  Singleton object that performs system-wide MIDI Capability Inquiry discovery
 
     MIDICIDiscoveryManager is used to retrieve information about nodes in the MIDI subsystem
     that are MIDI-CI capable. Only MIDI destinations discovered via this API can be used to
     create MIDICISessions.
*/
MIDICI1_1_AVAILABILITY
@interface MIDICIDiscoveryManager : NSObject
+ (MIDICIDiscoveryManager *)sharedInstance;
- (void)discoverWithHandler:(MIDICIDiscoveryResponseBlock)completedHandler;
@end

// =================================================================================================

/*!
     @protocol  MIDICIProfileResponderDelegate
     @brief     Protocol for an NSObject that constructs and issues responses for a MIDICIResponder.
                A MIDICIProfileResponderDelegate is required to construct a MIDICIResponder.
*/
MIDICI1_1_AVAILABILITY
@protocol MIDICIProfileResponderDelegate <NSObject>

@required
// Allow a new MIDI-CI Initiator to create a session or reject the connection attempt
- (BOOL)connectInitiator:(MIDICIInitiatiorMUID)initiatorMUID withDeviceInfo:(MIDICIDeviceInfo *)deviceInfo;
// Called when an initiator terminates its MIDI-CI connection
- (void)initiatorDisconnected:(MIDICIInitiatiorMUID)initiatorMUID;

@optional
// These methods must be implemented if the associated responder implements MIDI-CI profiles.
- (BOOL)willSetProfile:(MIDICIProfile *)aProfile onChannel:(MIDIChannelNumber)channel enabled:(BOOL)shouldEnable;
- (void)handleDataForProfile:(MIDICIProfile *)aProfile onChannel:(MIDIChannelNumber)channel data:(NSData *)inData;
@end // MIDICIProfileResponderDelegate

// =================================================================================================

/*!
     @class     MIDICIResponder
     @brief     Responds to MIDI-CI inquiries from an initiator on behalf of a MIDIClient and handles profile and property change
                operations for the Responder role.
*/
MIDICI1_1_AVAILABILITY
@interface MIDICIResponder : NSObject
@property (nonatomic, readonly) NSArray<MIDICIInitiatiorMUID> *initiators;
@property (nonatomic, readonly, retain) id<MIDICIProfileResponderDelegate>profileDelegate;
@property (nonatomic, readonly) MIDICIDeviceInfo *deviceInfo;

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithDeviceInfo:(MIDICIDeviceInfo *)deviceInfo profileDelegate:(id<MIDICIProfileResponderDelegate>)delegate profileStates:(MIDICIProfileStateList *)profileList supportProperties:(BOOL)propertiesSupported;

// Spontaneously enable or disable a profile and notify all connected Initiators
- (BOOL)notifyProfile:(MIDICIProfile *)aProfile onChannel:(MIDIChannelNumber)channel isEnabled:(BOOL)enabledState;

// Send profile-specific data for a profile to all connected Initiators
- (BOOL)sendProfile:(MIDICIProfile *)aProfile onChannel:(MIDIChannelNumber)channel profileData:(NSData *)profileSpecificData;

// Begin receiving Initiator requests
- (BOOL)start;
// Stop receiving Initiator requests and disconnect all connected Initiators
- (void)stop;

@end // MIDICIResponder

NS_ASSUME_NONNULL_END

#endif /* if defined(__OBJC2__) */
#endif /* MIDICapabilityInquiry_h */
