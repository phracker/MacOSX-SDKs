/*
 File:       CoreMIDI/MIDICapabilityInquiry.h

 Contains:   Deprecated beta API for MIDI Capability Inquiry (MIDI-CI)

 Copyright:  (c) 2024 by Apple Inc., all rights reserved.

 Bugs?:      For bug reports, consult the following page on
 the World Wide Web:

 http://feedbackassistant.apple.com/
*/

#if !defined(MIDICapabilityInquiry_h)
#define MIDICapabilityInquiry_h

/*
	@header MIDICapabilityInquiry.h

	This is the header file for deprecated MIDI Capability Inquiry (MIDI-CI) system services.

	Please visit http://www.midi.org/specifications for more information on MIDI Capability Inquiry
	and a list of currently defined capabilities.
*/

#import "MIDIUMPCI.h"
#import <CoreMIDI/MIDIMessages.h>

/*
 @struct MIDICIDeviceIdentification
 @brief  struct describing a MIDI-CI device.
*/
struct MIDICIDeviceIdentification
{
	uint8_t manufacturer[3];
	uint8_t family[2];
	uint8_t modelNumber[2];
	uint8_t revisionLevel[4];
	uint8_t reserved[5]; // always zero
};
typedef struct MIDICIDeviceIdentification MIDICIDeviceIdentification;

/*!
	@constant 	MIDIChannelsWholePort
	@brief		An outdated MIDI-CI constant indicating "the whole port", i.e. all channels.
 */
static const MIDIChannelNumber MIDIChannelsWholePort = 0x7f;


// This API requires the modern Objective-C runtime.
#if defined(__OBJC2__)
#import <Foundation/Foundation.h>
#import <stdint.h>

NS_ASSUME_NONNULL_BEGIN

@class MIDICISession;
@class MIDICIProfileState;

// The unique MIDI-CI negotiation identifier (MUID) used for a MIDICIResponder connection.
// Per the MIDI-CI specification, this is a randomly assigned 28-bit integer.
typedef NSNumber* MIDICIInitiatiorMUID;

// An array of MIDICIProfileState objects that describes the profile
// configuration for all channels for a reachable MIDI-CI node.
typedef NSArray<MIDICIProfileState*> MIDICIProfileStateList;

#pragma mark MIDICIDeviceInfo (deprecated)

/*
	@class		MIDICIDeviceInfo
	@brief  	An NSObject containing basic information about a MIDI-CI-capable node.
*/
MIDICI1_0_DEPRECATED
@interface MIDICIDeviceInfo : NSObject <NSSecureCoding>

// The MIDI System Exclusive ID of the device manufacturer, 3 bytes long. One-byte SysEx IDs are
// padded with trailing zeroes (e.g., Apple's System Exclusive ID, 0x11, would be expressed as 0x110000).
@property (nonatomic, readonly) NSData* manufacturerID; // 3 bytes

// The group of models to which the device belongs, 2 bytes.
@property (nonatomic, readonly) NSData* family; // 2 bytes

// The specific model from the device manufacturer, 2 bytes.
@property (nonatomic, readonly) NSData* modelNumber; // 2 bytes

// The version number of a device model number, 2 bytes.
@property (nonatomic, readonly) NSData* revisionLevel; // 4 bytes

// The MIDI destination used by device's MIDI entity for capability inquiries.
@property (nonatomic, readonly) MIDIEndpointRef midiDestination;

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithDestination:(MIDIEntityRef)midiDestination manufacturer:(NSData*)manufacturer family:(NSData*)family model:(NSData*)modelNumber revision:(NSData*)revisionLevel;
@end

#pragma mark MIDICIDiscoveredNode (deprecated)

/*
	 @class    MIDICIDiscoveredNode
	 @brief     An object created during MIDI-CI discovery representing a MIDI destination with an
				 associated MIDI source that responds to capability inquiries.
*/
MIDICI1_1_DEPRECATED
@interface MIDICIDiscoveredNode : NSObject <NSSecureCoding>
@property (nonatomic, readonly) MIDIEntityRef destination;
@property (nonatomic, readonly) MIDICIDeviceInfo* deviceInfo;
@property (nonatomic, readonly) BOOL supportsProfiles;
@property (nonatomic, readonly) BOOL supportsProperties;
@property (nonatomic, readonly) NSNumber* maximumSysExSize;

- (instancetype)init NS_UNAVAILABLE;
@end

#pragma mark MIDICIProfile

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
@property (nonatomic, readonly) NSString* name;

/// The unique 5-byte profile identifier representing the profile.
@property (nonatomic, readonly) NSData* profileID; // always 5 bytes

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithData:(NSData*)data MIDICI1_1;
- (instancetype)initWithData:(NSData*)data name:(NSString*)inName;
@end

#pragma mark MIDICIProfileState

/*
	@class	MIDICIProfileState
	@brief  A list of the enabled and/or disabled profiles for a MIDI channel or port on a device.
*/
MIDICI1_0_AVAILABILITY
@interface MIDICIProfileState : NSObject <NSSecureCoding>
@property (nonatomic, readonly) MIDIChannelNumber midiChannel;
@property (nonatomic, readonly) NSArray<MIDICIProfile*>* enabledProfiles;
@property (nonatomic, readonly) NSArray<MIDICIProfile*>* disabledProfiles;

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithChannel:(MIDIChannelNumber)midiChannelNum enabledProfiles:(NSArray<MIDICIProfile*>*)enabled disabledProfiles:(NSArray<MIDICIProfile*>*)disabled API_DEPRECATED_WITH_REPLACEMENT("initWithEnabledProfiles:", macos(10.14, 15.0), ios(12.0, 18.0));
- (instancetype)initWithEnabledProfiles:(NSArray<MIDICIProfile*>*)enabled disabledProfiles:(NSArray<MIDICIProfile*>*)disabled MIDICI1_1;
@end

/*
	@fn     MIDICIProfileChangedBlock
	@brief  A block called when a device notifies that a profile has been enabled or disabled.
*/
typedef void (^MIDICIProfileChangedBlock)(
	MIDICISession* session, MIDIChannelNumber channel, MIDICIProfile* profile, BOOL enabled) MIDICI1_1_DEPRECATED;

/*
	 @fn     MIDICISessionDisconnectBlock
	 @brief  A block called when a MIDICISession has been disconnected. If called, the MIDICISession should be destroyed.
*/
typedef void (^MIDICISessionDisconnectBlock)(
	MIDICISession* session, NSError* error) MIDICI1_1_DEPRECATED;

/*
	 @fn     MIDICIProfileSpecificDataBlock
	 @brief  A block called when a MIDICISession or MIDICIResponder receives profile-specific data.
*/
typedef void (^MIDICIProfileSpecificDataBlock)(
	MIDICISession* session, MIDIChannelNumber channel, MIDICIProfile* profile, NSData* profileSpecificData) MIDICI1_1_DEPRECATED;

/*
	 @fn     MIDICIDiscoveryResponseBlock
	 @brief  A block called when a MIDI-CI node discovery is complete.
*/
typedef void (^MIDICIDiscoveryResponseBlock)(
	NSArray<MIDICIDiscoveredNode*>* discoveredNodes) MIDICI1_1_DEPRECATED;

#pragma mark MIDICISession (deprecated)

/*
	 @class  MIDICISession
	 @brief  Object representating a MIDI Capability Inquiry session.

	 A MIDI Capability Inquiry session is a bidirectional communication path between a MIDI process
	 and a MIDI-CI node (i.e., paired MIDI source and destination) identified using MIDI-CI discovery.
	 A MIDICISession can be used to manipulate MIDI-CI profiles and to discover the MIDI-CI property
	 capability.
*/
MIDICI1_0_DEPRECATED
@interface MIDICISession : NSObject

/*
	@brief  Begin a MIDI-CI session with the provided discovered node.

	dataReadyHandler will be called when properties of the session have become available.
	Other methods of this class will not return valid/useful information before the dataReadyHandler
	is called.

	disconnectHandler will be called if the active MIDICISession is disconnected by the Responder
	or if initial MIDI-CI discovery was unsuccessful.
*/
- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithDiscoveredNode:(MIDICIDiscoveredNode*)discoveredNode dataReadyHandler:(void (^)(void))handler disconnectHandler:(MIDICISessionDisconnectBlock)disconnectHandler;

// The MIDI destination with which the session is communicating.
@property (nonatomic, readonly) MIDIEntityRef midiDestination;

// After CI session data is ready, indicates whether the entity supports the MIDI-CI profile capability.
@property (nonatomic, readonly) BOOL supportsProfileCapability;

// After CI session data is ready, indicates whether the entity supports the MIDI-CI property exchange capability.
@property (nonatomic, readonly) BOOL supportsPropertyCapability;

// Obtain the device's basic identification. Nil before data is ready or if the device does not
// support MIDI-CI.
@property (nonatomic, readonly) MIDICIDeviceInfo* deviceInfo;

// The maximum MIDI system exclusive size reported by the device during discovery
@property (nonatomic, readonly) NSNumber* maxSysExSize; // unsigned long

// The maximum number of simultaneous property exchange requests, if supported
@property (nonatomic, readonly) NSNumber* maxPropertyRequests; // int

// Given a MIDI channel number, return the supported profiles. Note that the
// arrays will be empty if this property is queried before data is ready.
- (MIDICIProfileState*)profileStateForChannel:(MIDIChannelNumber)channel;

// Given a MIDI channel number, asynchronously request that the supplied profile be enabled.
// The result of this operation is sent to the MIDICIProfileChangedBlock.
// Returns YES if the request is valid.
- (BOOL)enableProfile:(MIDICIProfile*)profile
			onChannel:(MIDIChannelNumber)channel
				error:(NSError**)outError;

// Given a MIDI channel number, asynchronously request that the supplied profile be disabled.
// The result of this operation is sent to the MIDICIProfileChangedBlock.
// Returnes YES if the request is valid.
- (BOOL)disableProfile:(MIDICIProfile*)profile
			 onChannel:(MIDIChannelNumber)channel
				 error:(NSError**)outError;

// Given a MIDI channel number, send profile specific data to the MIDICISession.
// Returns YES if the data was successfully sent.
- (BOOL)sendProfile:(MIDICIProfile*)profile onChannel:(MIDIChannelNumber)channel profileData:(NSData*)profileSpecificData MIDICI1_1;

// An optional block called when a device signals that a profile has been enabled or disabled.
@property (nonatomic, copy, nullable) MIDICIProfileChangedBlock profileChangedCallback;

// An optional block called when a device sends profile-specific data to the session.
@property (nonatomic, copy, nullable) MIDICIProfileSpecificDataBlock profileSpecificDataHandler;

@end

#pragma mark MIDICIDiscoveryManager (deprecated)

/*
	 @class  MIDICIDiscoveryManager
	 @brief  Singleton object that performs system-wide MIDI Capability Inquiry discovery

	 MIDICIDiscoveryManager is used to retrieve information about nodes in the MIDI subsystem
	 that are MIDI-CI capable. Only MIDI destinations discovered via this API can be used to
	 create MIDICISessions.
*/
MIDICI1_1_DEPRECATED
@interface MIDICIDiscoveryManager : NSObject
+ (MIDICIDiscoveryManager*)sharedInstance;
- (void)discoverWithHandler:(MIDICIDiscoveryResponseBlock)completedHandler;
@end

/*
	 @protocol  MIDICIProfileResponderDelegate
	 @brief     Protocol for an NSObject that constructs and issues responses for a MIDICIResponder.
				A MIDICIProfileResponderDelegate is required to construct a MIDICIResponder.
*/
MIDICI1_1_DEPRECATED
@protocol MIDICIProfileResponderDelegate <NSObject>

@required
// Allow a new MIDI-CI Initiator to create a session or reject the connection attempt
- (BOOL)connectInitiator:(MIDICIInitiatiorMUID)initiatorMUID withDeviceInfo:(MIDICIDeviceInfo*)deviceInfo;
// Called when an initiator terminates its MIDI-CI connection
- (void)initiatorDisconnected:(MIDICIInitiatiorMUID)initiatorMUID;

@optional
// These methods must be implemented if the associated responder implements MIDI-CI profiles.
- (BOOL)willSetProfile:(MIDICIProfile*)aProfile onChannel:(MIDIChannelNumber)channel enabled:(BOOL)shouldEnable;
- (void)handleDataForProfile:(MIDICIProfile*)aProfile onChannel:(MIDIChannelNumber)channel data:(NSData*)inData;
@end

#pragma mark MIDICIResponder (deprecated)

/*
	 @class     MIDICIResponder
	 @brief     Responds to MIDI-CI inquiries from an initiator on behalf of a MIDIClient and handles profile and property change
				operations for the Responder role.
*/
MIDICI1_1_DEPRECATED
@interface MIDICIResponder : NSObject
@property (nonatomic, readonly) NSArray<MIDICIInitiatiorMUID>* initiators;
@property (nonatomic, readonly, retain) id<MIDICIProfileResponderDelegate> profileDelegate;
@property (nonatomic, readonly) MIDICIDeviceInfo* deviceInfo;

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithDeviceInfo:(MIDICIDeviceInfo*)deviceInfo profileDelegate:(id<MIDICIProfileResponderDelegate>)delegate profileStates:(MIDICIProfileStateList*)profileList supportProperties:(BOOL)propertiesSupported;

// Spontaneously enable or disable a profile and notify all connected Initiators
- (BOOL)notifyProfile:(MIDICIProfile*)aProfile onChannel:(MIDIChannelNumber)channel isEnabled:(BOOL)enabledState;

// Send profile-specific data for a profile to all connected Initiators
- (BOOL)sendProfile:(MIDICIProfile*)aProfile onChannel:(MIDIChannelNumber)channel profileData:(NSData*)profileSpecificData;

// Begin receiving Initiator requests
- (BOOL)start;
// Stop receiving Initiator requests and disconnect all connected Initiators
- (void)stop;

@end

NS_ASSUME_NONNULL_END

#endif /* if defined(__OBJC2__) */
#endif /* MIDICapabilityInquiry_h */
