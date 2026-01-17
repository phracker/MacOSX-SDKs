/*
 File:       CoreMIDI/MIDIUMPMutableEndpoint.h

 Contains:   API for MIDI Universal MIDI Packet (UMP) endpoints

 Copyright:  (c) 2024 by Apple Inc., all rights reserved.

 Bugs?:      For bug reports, consult the following page on
 the World Wide Web:

 http://feedbackassistant.apple.com/
 */

#if !defined(MIDIUMPMutableEndpoint_h)
#define MIDIUMPMutableEndpoint_h

/*!
	@header MIDIUMPMutableEndpoint.h

	This is the header file for Univeral MIDI Packet (UMP) endpoint system services.

	API Overview
	------------
	MIDI 2.0 is inherently bidirectional, and an endpoint that communicates using the Universal MIDI Packet
	(UMP) format (a UMP Endpoint) must be capable of acting as a source of and destination for UMP data.
	The MIDIUMPMutableEndpoint class defines an explicit relationship between a UMP-capable source and
	UMP-capable destination and encapsulates its stream configuration.

	A MIDIUMPEndpoint is a local cached object copied from the system-wide UMP Endpoint cache into the
	client process instance of MIDIUMPEndpointManager. Any UMP Endpoint may declare up to 32
	Function Blocks, cached as MIDIUMPFunctionBlock objects associated with a MIDIUMPEndpoint. These
	Function Blocks may also be used as MIDI-CI devices.

	Implementation overview
	-----------------------
	A MIDIUMPEndpoint may have zero or more MIDIUMPFunctionBlock objects that parcel the UMP
	datastream into collections of one or more UMP Groups performing a singular device function. In some
	cases, Function Block configurations can change spontaneously, and the UMP groups spanned by
	the Function Block may also change. Updates to the Function Block state are received from the
	MIDIUMPEndpoint source, which are captured by the UMP subsystem and subsequently reflected in
	the cache and in callbacks registered by interested client processes.

	If virtual destination creation is allowed, a client process may also create mutable UMP Endpoint and
	Function block objects. MIDIUMPMutableEndpoint objects are instantiated in an inactive state, allowing
	the owning client process to create or update the Function Block configuration on the
	MIDIUMPMutableEndpoint. Once enabled, the MIDIUMPMutableEndpoint and its Function Block
	configuration (if any) will be added to the system-wide UMP Endpoint cache.

	The singleton object MIDIUMPEndpointManager maintains a local copy of the UMP Endpoint cache and
	may also be used to observe notifications which are posted in response common UMP subsystem
	cache updates.

	Please visit http://www.midi.org/specifications for more information on MIDI 2.0 and UMP.
*/

#import <CoreMIDI/MIDIUMPCI.h>
#import <CoreMIDI/MIDIUMPEndpoint.h>

// This API requires the modern Objective-C runtime.
#if defined(__OBJC2__)
#import <Foundation/Foundation.h>
#import <stdint.h>

NS_ASSUME_NONNULL_BEGIN

@class MIDIUMPMutableFunctionBlock;

#pragma mark MIDIUMPMutableEndpoint

/*!
	@class		MIDIUMPMutableEndpoint
	@brief		A mutable MIDIUMPEndpoint object.

	@discussion	It is not necessary to create a MIDIUMPEndpoint or other MIDI endpoint in order to
				use UMP natively. Any standard MIDI endpoint created with a specified MIDIProtocolID
				is assumed to use all 16 UMP groups for the same unspecified function and to neither
				transmit nor receive jitter-reduction timestamps.

				This API is not realtime-safe, all interaction with the mutable endpoint should be done on the
				main thread.
*/
MIDI_AVAILABLE_UMP1_1
@interface MIDIUMPMutableEndpoint : MIDIUMPEndpoint

///	@property	mutableFunctionBlocks
///	@brief		The Function Blocks associated with the UMP endpoint, if any.
@property (nonatomic, copy) NSArray<MIDIUMPMutableFunctionBlock*>* mutableFunctionBlocks;

/// @property   isEnabled
/// @brief      The enable state of the endpoint.
@property (nonatomic, readonly) BOOL isEnabled;

/*!
	@method		initWithName:deviceInfo:productInstanceID:MIDIProtocol:destinationCallback
	@brief		Initializer for creating a new MIDIUMPEndpoint.

	@param		name			        The UMP endpoint name.
	@param		deviceInfo		        The MIDI 2 device ID info for the UMP endpoint.
	@param		productInstanceID      The product instance ID, up to 42 characters.
	@param		MIDIProtocol	        The MIDI protocol.
	@param		destinationCallback The receive callback used to create the UMP endpoint's MIDI
									destination associated, which can be used to observe or process
									incoming MIDI traffic.

	@discussion	This operation will fail if the device ID information is malformed or if virtual MIDI endpoint creation
				is not allowed (for example, on iOS, if your app doesn't list 'audio' in UIBackgroundModes).
 */
- (instancetype _Nullable)initWithName:(NSString*)name
							deviceInfo:(MIDI2DeviceInfo*)deviceInfo
					 productInstanceID:(NSString*)productInstanceID
						  MIDIProtocol:(MIDIProtocolID)MIDIProtocol
				   destinationCallback:(MIDIReceiveBlock)destinationCallback;

/*!
	@method       setName:error:
	@brief        Set the endpoints name.

	@param        name                      A string representing the name of the endpoint.
	@param        error             The out-error used if an error occurs.

	@return       YES for success. NO in the event of a failure, in which case the error is returned in error.

	@discussion   This operation will fail if the name could not be set.
 */
- (BOOL)setName:(nonnull NSString*)name
		  error:(NSError* _Nullable*)error;

/*!
	@method		registerFunctionBlocks:markAsStatic:error:
	@brief		Register or replace Function Blocks for a disabled client-created MIDIUMPEndpoint.

	@param		functionBlocks			A list of client-created Function Blocks to register.
	@param		markAsStatic			Whether the Function Block configuration may be updated.
	@param		error					The out-error used if an error occurs.

	@return     YES for success. NO in the event of a failure, in which case the error is returned in error.

	@discussion	This operation will fail if the array contains any disabled Function Blocks but the
				MIDIUMPEndpoint Function Block configuration is static.
				Returns YES if the Function Block configuration was set successfully.
 */
- (BOOL)registerFunctionBlocks:(nonnull NSArray<MIDIUMPMutableFunctionBlock*>*)functionBlocks
				  markAsStatic:(BOOL)markAsStatic
						 error:(NSError* _Nullable*)error;

/*!
	@method		setEnabled:error:
	@brief		Enable a mutable UMP endpoint in the system-wide UMP endpoint cache.

	@param		isEnabled               The enable state of the UMP endpoint.
	@param		error		        The out-error used if an error occurred.

	@return     YES for success. NO in the event of a failure, in which case the error is returned in error.

	@discussion	A MIDIUMPMutableEndpoint must be cache enabled before it is visible via API.
				Note that Function Blocks may only be registered to uncached MIDIUMPMutableEndpoint
				objects.
 */
- (BOOL)setEnabled:(BOOL)isEnabled
			 error:(NSError* _Nullable*)error;

@end

NS_ASSUME_NONNULL_END

#endif
#endif
