/*
 File:       CoreMIDI/MIDICapabilityInquiry.h
 
 Contains:   API for MIDI Capability Inquiry (MIDI-CI)
 
 Copyright:  (c) 2018 by Apple Inc., all rights reserved.
 
 Bugs?:      For bug reports, consult the following page on
 the World Wide Web:
 
 http://developer.apple.com/bugreporter/
 */

// This API requires the modern Objective-C runtime.
#if !defined(MIDICapabilityInquiry_h) && defined(__OBJC2__)
#define MIDICapabilityInquiry_h

#import <CoreMIDI/MIDIServices.h>
#import <Foundation/Foundation.h>
#import <stdint.h>

NS_ASSUME_NONNULL_BEGIN

// Forward declarations.
@class MIDICISession;
@class MIDICIProfile;

/// MIDI Channel, 0~15 (channels 1 through 16, respectively), or MIDIChannelsWholePort. (Per the specifications, this is always a single byte.)
typedef uint8_t MIDIChannelNumber;

/// All MIDI-CI methods involving a channel number use 0x7f to mean "the whole port", i.e. all
/// channels.
static const MIDIChannelNumber MIDIChannelsWholePort = 0x7f;

/*!
 	@struct MIDICIDeviceIdentification
 	@brief  Object describing a MIDI-CI device.
*/
struct MIDICIDeviceIdentification {
	uint8_t manufacturer[3];
	uint8_t family[2];
	uint8_t modelNumber[2];
	uint8_t revisionLevel[4];
	uint8_t reserved[5];		// always zero
};
typedef struct MIDICIDeviceIdentification MIDICIDeviceIdentification;

// =================================================================================================

/*!
 	@class	MIDICIProfile
 	@brief  An NSObject representing Capability Inquiry profile. MIDI-CI profiles describe a mapping
 	of MIDI messages to specific sounds and synthesis behaviors, e.g. General MIDI, a drawbar organ,
 	etc.
*/
OS_EXPORT API_AVAILABLE(macos(10.14), ios(12.0)) API_UNAVAILABLE(watchos, tvos)
@interface MIDICIProfile : NSObject <NSSecureCoding>
@property (nonatomic, readonly) NSString *name;
@property (nonatomic, readonly) NSData *profileID;	// always 5 bytes

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithData:(NSData *)data name:(NSString *)inName;
@end

// =================================================================================================

/*!
 	@class	MIDICIProfileState
 	@brief  Lists the enabled and disabled profiles for a device or one of its MIDI channels.
*/
OS_EXPORT API_AVAILABLE(macos(10.14), ios(12.0)) API_UNAVAILABLE(watchos, tvos)
@interface MIDICIProfileState : NSObject <NSSecureCoding>
@property (nonatomic, readonly) NSArray<MIDICIProfile *> *enabledProfiles;
@property (nonatomic, readonly) NSArray<MIDICIProfile *> *disabledProfiles;

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithEnabledProfiles:(NSArray<MIDICIProfile *> *)enabled disabledProfiles:(NSArray<MIDICIProfile *> *)disabled;
@end

// =================================================================================================

/*!
 	@fn     MIDICIProfileChangedBlock
 	@brief  A block called when a device notifies that a profile has been enabled or disabled.
*/
typedef void (^MIDICIProfileChangedBlock)(
				MIDICISession *session, MIDIChannelNumber channel, MIDICIProfile *profile, BOOL enabled);

/*!
 	@fn     MIDICIPropertyChangedBlock
 	@brief  A block called when a device notifies that property data has changed.
*/
typedef void (^MIDICIPropertyChangedBlock)(
				MIDICISession *session, MIDIChannelNumber channel, NSData *data);

/*!
 	@fn     MIDICIPropertyResponseBlock
 	@brief  The Property Exchange methods are asynchronous; this block is called when an entire
 	response has been received.
*/
typedef void (^MIDICIPropertyResponseBlock)(
				MIDICISession *session, MIDIChannelNumber channel, NSData *response, NSError *error);

// =================================================================================================

/*!
 	@class  MIDICISession
 	@brief  Object representating a MIDI Capability Inquiry session.
 
 	A MIDI Capability Inquiry session is a bidirectional communication path between a MIDI process
 	and a driver entity (i.e., pair of endpoints). Since a driver entity is only able to communicate
 	with the host via MIDIServer, creating a MIDICISession gives the process access to the shared
 	communication path.
 
	Please visit http://www.midi.org/specifications for more information on MIDI Capability Inquiry
	and list of currently defined capabilities.
 
*/
OS_EXPORT API_AVAILABLE(macos(10.14), ios(12.0)) API_UNAVAILABLE(watchos, tvos)
@interface MIDICISession : NSObject

/*!
	 @brief  Begin a MIDI-CI session with the provided entity (pair of endpoints).
 
	 dataReadyHandler will be called when properties of the session have become available.
	 Other methods of this class will not return valid/useful information before the dataReadyHandler
	 is called.
*/
- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithMIDIEntity:(MIDIEntityRef)entity dataReadyHandler:(void (^)(void))handler;

/// The MIDI entity with which the session is communicating.
@property (nonatomic, readonly) MIDIEntityRef entity;

// After CI session data is ready, indicates whether the entity supports the MIDI-CI profile capability.
@property (nonatomic, readonly) BOOL supportsProfileCapability;

// After CI session data is ready, indicates whether the entity supports the MIDI-CI property exchange capability.
@property (nonatomic, readonly) BOOL supportsPropertyCapability;

/// Obtain the device's basic identification. Null before data is ready or if the device does not
/// support MIDI-CI.
@property (nonatomic, readonly) MIDICIDeviceIdentification deviceIdentification;

/// Given a MIDI channel number, return the supported profiles. Note that the
/// arrays will be empty if this property is queried before data is ready.
- (MIDICIProfileState *)profileStateForChannel:(MIDIChannelNumber)channel;

- (BOOL)enableProfile:(MIDICIProfile *)profile
			onChannel:(MIDIChannelNumber)channel
				error:(NSError **)outError;

- (BOOL)disableProfile:(MIDICIProfile *)profile
			 onChannel:(MIDIChannelNumber)channel
				 error:(NSError **)outError;

/// A block called when a device signals that a profile has been enabled or disabled.
@property (nonatomic, nullable) MIDICIProfileChangedBlock profileChangedCallback;

/// Property exchange. The contents of the data blobs are not yet defined by the standard; here we
/// only provide basic plumbing.
- (void)hasProperty:(NSData *)inquiry
		  onChannel:(MIDIChannelNumber)channel
	responseHandler:(MIDICIPropertyResponseBlock)handler;

- (void)getProperty:(NSData *)inquiry
		  onChannel:(MIDIChannelNumber)channel
	responseHandler:(MIDICIPropertyResponseBlock)handler;

- (void)setProperty:(NSData *)inquiry
		  onChannel:(MIDIChannelNumber)channel
	responseHandler:(MIDICIPropertyResponseBlock)handler;

/// A block called when a device notifies that a property has changed.
@property (nonatomic, nullable) MIDICIPropertyChangedBlock propertyChangedCallback;

@end // MIDICISession

NS_ASSUME_NONNULL_END

#endif /* MIDICapabilityInquiry_h */
