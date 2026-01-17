/*
 File:		BluetoothHandsFreeDevice.h
 Copyright:	(c) 2010 by Apple Inc. All rights reserved.
 */

#import <Foundation/Foundation.h>
#import <IOBluetooth/Bluetooth.h>

#import <IOBluetooth/objc/IOBluetoothDevice.h>
#import <IOBluetooth/objc/IOBluetoothHandsFree.h>

@class IOBluetoothDevice;
@class IOBluetoothHandsFreeDeviceExpansion;

/*!
 @header
 @abstract	APIs for managing a hands free device
 @copyright	(c) 2010 by Apple Inc. All rights reserved.
 */
API_AVAILABLE(macos(10.7)) API_UNAVAILABLE(ios, watchos, tvos)
@interface IOBluetoothHandsFreeDevice : IOBluetoothHandsFree {
	BOOL									_rejectSCOConnection;
	int										_ringAttempt;
	BOOL									_outstandingCommand;
	NSTimer *								_outstandingCommandTimer;
	IOBluetoothHandsFreeDeviceExpansion *   _expansion;
	NSMutableArray *						_commandQueue;
}

/*!
 @method		initWithDevice:delegate:
 @abstract		Create a new IOBluetoothHandsFreeDevice to act as a hands free device
 @discussion	This will register a listener for incoming connections.
 @param			device An IOBluetoothDevice
 @param			inDelegate An object to act as delegate
 @result		A newly created IOBluetoothHandsFreeDevice object on success, nil on failure
 */
- (instancetype)initWithDevice:(IOBluetoothDevice *)device delegate:(id)delegate NS_AVAILABLE_MAC(10_7);

/*!
 @method		dialNumber:aNumber
 @abstract		Dial a number
 @discussion	Calls aNumber
 @param			aNumber The number to call - the gateway determines acceptable formats.
 */
- (void)dialNumber:(NSString *)aNumber NS_AVAILABLE_MAC(10_7);

/*!
 @method		memoryDial:memoryLocation
 @abstract		Dial a number from memory
 @discussion	Calls a number from a memory (or speed dial) location.
 @param			memoryLocation The location in memory
 */
- (void)memoryDial:(int)memoryLocation NS_AVAILABLE_MAC(10_7);

/*!
 @method		redial
 @abstract		Redial a number
 @discussion	Redials the previous number stored by the hands free gateway.
 */
- (void)redial NS_AVAILABLE_MAC(10_7);

/*!
 @method		endCall
 @abstract		Hang up a call or reject an incoming call
 @discussion	Hangs up the current call, or rejects an incoming call.
 */
- (void)endCall NS_AVAILABLE_MAC(10_7);

/*!
 @method		acceptCall
 @abstract		Accept an incoming call
 @discussion	Accepts an incoming call.
 */
- (void)acceptCall NS_AVAILABLE_MAC(10_7);

/*!
 @method		acceptCallOnPhone
 @abstract		Accept an incoming call on the phone
 @discussion	Accepts an incoming call and then quickly transfer audio to the phone.
 */
- (void)acceptCallOnPhone NS_AVAILABLE_MAC(10_7);

/*!
 @method		sendDTMF:character
 @abstract		Send a key press
 @discussion	Sends a DTMF tone.
 @param			character A single character in the set 0-9, #,*,A-D
 */
- (void)sendDTMF:(NSString *)character NS_AVAILABLE_MAC(10_7);

/*!
 @method		subscriberNumber
 @abstract		Get the subscriber number(s)
 @discussion	Gets the subscriber number(s) stored on the gateway. Each subscriber number is returned on the delegate method handsFree:subscriberNumber.
				There is no guarantee that the gateway will have a subscriber number.
 */
- (void)subscriberNumber NS_AVAILABLE_MAC(10_7);

/*!
 @method		currentCallList
 @abstract		Get the current call list
 @discussion	Gets the current call list (active, held, and setup in process). Each call is returned on the delegate method handsFree:currentCall.
 */
- (void)currentCallList NS_AVAILABLE_MAC(10_7);

// TODO: Incomplete implementation for call hold features
/*!
 @method		releaseHeldCalls
 @abstract		Release all held calls
 @discussion	Releases all held calls or sets User Determined User Busy for a waiting call.
 */
- (void)releaseHeldCalls NS_AVAILABLE_MAC(10_7);

/*!
 @method		releaseActiveCalls
 @abstract		Release all active calls
 @discussion	Releases all active calls (if any exist) and accepts the other (held or waiting) call.
 */
- (void)releaseActiveCalls NS_AVAILABLE_MAC(10_7);

/*!
 @method		releaseCall:index
 @abstract		Release an active call.
 @discussion	Releases the active call with index.
 @param			index Index of the call to release
 */
- (void)releaseCall:(int)index NS_AVAILABLE_MAC(10_7);

/*!
 @method		holdCall
 @abstract		Place all active calls on hold
 @discussion	Places all active calls (if any exist) on hold and accepts the other (held or waiting) call.
 */
- (void)holdCall NS_AVAILABLE_MAC(10_7);

/*!
 @method		placeAllOthersOnHold:index
 @abstract		Place all other calls on hold.
 @discussion	Places all calls on hold except call with index.
 @param			index Index of the call to not place on hold
 */
- (void)placeAllOthersOnHold:(int)index NS_AVAILABLE_MAC(10_7);

/*!
 @method		addHeldCall
 @abstract		Add a held call to the current conversation
 @discussion	Adds a held call to the current conversation.
 */
- (void)addHeldCall NS_AVAILABLE_MAC(10_7);

/*!
 @method		callTransfer
 @abstract		Release all active calls
 @discussion	Releases all active calls (if any exist) and accepts the other (held or waiting) call.
 */
- (void)callTransfer NS_AVAILABLE_MAC(10_7);

/*!
 @method		transferAudioToComputer
 @abstract		Transfer audio source to the computer.
 @discussion	Transfers audio to the computer.
 */
- (void)transferAudioToComputer NS_AVAILABLE_MAC(10_7);

/*!
 @method		transferAudioToPhone
 @abstract		Transfer audio source to the phone.
 @discussion	Transfers audio to the phone.
 */
- (void)transferAudioToPhone NS_AVAILABLE_MAC(10_7);

/*!
 @method		sendSMS:aNumber:aMessage
 @abstract		Send an SMS to a number.
 @discussion	Sends an SMS to aNumber with content aMessage. Currently this does not handle long SMS (>160 characters) or unicode messages.
 */
- (void)sendSMS:(NSString *)aNumber message:(NSString *)aMessage NS_AVAILABLE_MAC(10_7);

#pragma mark -
/*!
 @method		sendATCommand:atCommand
 @abstract		Send an AT command to the hands free gateway.
 @discussion	Sends an AT command to the hands free gateway with a timeout of 10 seconds and handled by the built-in response handling.
				See sendAtCommand:timeout:selector:target for more details.
 @param			atCommand AT command to send
 */
- (void)sendATCommand:(NSString *)atCommand NS_AVAILABLE_MAC(10_7);

/*!
 @method		sendATCommand:atCommand:timeout:selector:target
 @abstract		Send an AT command to the hands free gateway.
 @discussion	Sends an AT command to the hands free gateway with timeout.
 				On command complete (OK, ERROR, TIMEOUT response or after timeout seconds) will perform selector on target.
 @param			atCommand AT command to send
 */
- (void)sendATCommand:(NSString *)atCommand timeout:(float)timeout selector:(SEL)selector target:(id)target NS_AVAILABLE_MAC(10_7);

@end

API_UNAVAILABLE(ios, watchos, tvos)
@protocol IOBluetoothHandsFreeDeviceDelegate <IOBluetoothHandsFreeDelegate>
@optional

/*!
 @method		handsFree:isServiceAvailable
 @discussion	Tells the delegate the service indicator has changed.
 @param			device The IOBluetoothHandsFreeDevice object
 @param			isServiceAvailable 0 if no service available; 1 otherwise.
 */
- (void)handsFree:(IOBluetoothHandsFreeDevice *)device isServiceAvailable:(NSNumber *)isServiceAvailable NS_AVAILABLE_MAC(10_7);

/*!
 @method		handsFree:isCallActive
 @discussion	Tells the delegate the call indicator has changed.
 @param			device The IOBluetoothHandsFreeDevice object
 @param			isCallActive 0 if no call is active; 1 otherwise.
 */
- (void)handsFree:(IOBluetoothHandsFreeDevice *)device isCallActive:(NSNumber *)isCallActive NS_AVAILABLE_MAC(10_7);

/*!
 @method		handsFree:callSetupMode
 @discussion	Tells the delegate the call setup indicator has changed.
 @param			device The IOBluetoothHandsFreeDevice object
 @param			callSetupMode	0 if not currently in call setup.
 								1 if an incoming call is in call setup.
 								2 if an outgoing call is in call setup.
 								3 if the remote party is being alerted for an outgoing call.
 */
- (void)handsFree:(IOBluetoothHandsFreeDevice *)device callSetupMode:(NSNumber *)callSetupMode NS_AVAILABLE_MAC(10_7);

/*!
 @method		handsFree:callHoldState
 @discussion	Tells the delegate the call held indicator has changed.
 @param			device The IOBluetoothHandsFreeDevice object
 @param			callHoldState	0 if no calls are held.
 								1 if a call is on hold and an active call exists.
								2 if a call is on hold, but no active call exists.
 */
- (void)handsFree:(IOBluetoothHandsFreeDevice *)device callHoldState:(NSNumber *)callHoldState NS_AVAILABLE_MAC(10_7);

/*!
 @method		handsFree:signalStrength
 @discussion	Tells the delegate the signal indicator has changed.
 @param			device The IOBluetoothHandsFreeDevice object
 @param			signalStrength 0-5 where 0 represents a weak signal.
 */
- (void)handsFree:(IOBluetoothHandsFreeDevice *)device signalStrength:(NSNumber *)signalStrength NS_AVAILABLE_MAC(10_7);

/*!
 @method		handsFree:isRoaming
 @discussion	Tells the delegate the roam indicator has changed.
 @param			device The IOBluetoothHandsFreeDevice object
 @param			isRoaming 0 if not roaming; 1 otherwise.
 */
- (void)handsFree:(IOBluetoothHandsFreeDevice *)device isRoaming:(NSNumber *)isRoaming NS_AVAILABLE_MAC(10_7);

/*!
 @method		handsFree:batteryCharge
 @discussion	Tells the delegate the battery charge indicator has changed.
 @param			device The IOBluetoothHandsFreeDevice object
 @param			batteryCharge 0-5 where 0 represents a low battery charge.
 */
- (void)handsFree:(IOBluetoothHandsFreeDevice *)device batteryCharge:(NSNumber *)batteryCharge NS_AVAILABLE_MAC(10_7);

/*!
 @method		handsFree:incomingCallFrom
 @discussion	Tells the delegate of an incoming call
 @param			device The IOBluetoothHandsFreeDevice object
 @param			number The remote caller's phone number
 */
- (void)handsFree:(IOBluetoothHandsFreeDevice *)device incomingCallFrom:(NSString *)number NS_AVAILABLE_MAC(10_7);

/*!
 @method		handsFree:ringAttempt
 @discussion	Tells the delegate of a ring alert
 @param			device The IOBluetoothHandsFreeDevice object
 @param			ringAttempt The number or ring alerts received
 */
- (void)handsFree:(IOBluetoothHandsFreeDevice *)device ringAttempt:(NSNumber *)ringAttempt NS_AVAILABLE_MAC(10_7);

/*!
 @method		handsFree:currentCall
 @discussion	Tells the delegate of a current call.
 @param			device The IOBluetoothHandsFreeDevice object
 @param			currentCall A dictionary representing a call. See "Hands free current call dictionary keys" for the keys and their values.
 */
- (void)handsFree:(IOBluetoothHandsFreeDevice *)device currentCall:(NSDictionary *)currentCall NS_AVAILABLE_MAC(10_7);

/*!
 @method		handsFree:subscriberNumber
 @discussion	Tells the delegate a subscriber number.
 @param			device The IOBluetoothHandsFreeDevice object
 @param			subscriberNumber A subscriber number. Note that a gateway may have multiple subscriber numbers in which case this will be called for each number.
 */
- (void)handsFree:(IOBluetoothHandsFreeDevice *)device subscriberNumber:(NSString *)subscriberNumber NS_AVAILABLE_MAC(10_7);

/*!
 @method		handsFree:incomingSMS
 @discussion	Tells the delegate an incoming SMS has arrived.
 @param			device The IOBluetoothHandsFreeDevice object
 @param			incomingSMS A dictionary representing an SMS. See "Hands free SMS dictionary keys" for the keys and their values.
 */
- (void)handsFree:(IOBluetoothHandsFreeDevice *)device incomingSMS:(NSDictionary *)sms NS_AVAILABLE_MAC(10_7);

/*!
 @method		handsFree:unhandledResultCode
 @discussion	Tells the delegate an unknown result code was received. Use this to add support additional response codes.
 				If a developer needs to change the handling of an implemented result code, they must use a subclass and override processResultCode:(NSString *)resultCode.
 @param			device The IOBluetoothHandsFreeDevice object
 @param			unhandledResultCode The result code.  "/r/n" are stripped from the begining and end of the result code.
 */
- (void)handsFree:(IOBluetoothHandsFreeDevice *)device unhandledResultCode:(NSString *)resultCode NS_AVAILABLE_MAC(10_7);

@end

