/*
	Contains:	API to pair with a Bluetooth device.
	Copyright:	(C) 2008 by Apple, Inc., all rights reserved.
*/

#import <IOKit/IOReturn.h>
#import <IOBluetooth/Bluetooth.h>

//===========================================================================================================================
//	Forwards
//===========================================================================================================================

@class IOBluetoothDevice;
@class NSString;

//--------------------------------------------------------------------------------------------------------------------------
/*!
 	@class		IOBluetoothDevicePair
	@abstract	An instance of IOBluetoothDevicePair represents a pairing attempt to a remote Bluetooth device.
	@discussion	Use the IOBluetoothDevicePair object to attempt to pair with any Bluetooth device. Once -start is invoked
				on it, progress is returned to the delegate via the messages defined below. This object enables you to
				pair with devices within your application without having to use the standard panels provided by the
				IOBluetoothUI framework, allowing you to write custom UI to select devices, and still handle the ability
				to perform device pairings.
				
				Of note is that this object MAY attempt to perform two low-level pairings, depending on the type of device
				you are attempting to pair. This is inconsequential to your code, however, as it occurs automatically and
				does not change the messaging.
				
				Once started, the pairing can be stopped. This will set the delegate to nil and then attempt to disconnect
 				from the device if already connected.
*/

//===========================================================================================================================
//	IOBluetoothDevicePair
//===========================================================================================================================

API_UNAVAILABLE(ios, watchos, tvos)
@interface	IOBluetoothDevicePair : NSObject
{
	id							_delegate;
	IOBluetoothDevice *			_device;
	BOOL						_busy;
	BOOL						_isHandlerSetup;
	BOOL						_triedSpecNULLPIN;
	BOOL						_SDPQueryComplete;
	IOReturn					_connectionCompleteStatus;
	uint32_t					_totalAttempts;
	id                          _expansion;
}

@property(assign) id delegate;

/*!
    @method		pairWithDevice:
	@abstract	Creates an autorelease IOBluetoothDevicePair object with a device as the pairing target.
	@param		device		An IOBluetoothDevice to attept to pair with. The device is retained.
	@result		Returns an IOReturn or Bluetooth error code, if the pairing could not be started.
*/

+ (instancetype)pairWithDevice:(IOBluetoothDevice*)device;

/*!
    @method		start
	@abstract	Kicks off the pairing with the device.
	@result		Returns an IOReturn or Bluetooth error code, if the pairing could not be started.
*/

- (IOReturn)start;

/*!
 @method		stop
 @abstract		Stops the current pairing. Removes the delegate and disconnects if device was connected.
 */

- (void)stop;

/*!
    @method		device
	@abstract	Get the IOBluetoothDevice being used by the object.
	@result		device		The IOBluetoothDevice object that the IOBluetoothDevicePair object is pairing with, as
							specified in -setDevice: or pairWithDevice:
*/

- (IOBluetoothDevice*)device;

/*!
    @method		setDevice:
	@abstract	Set the device object to pair with. It is retained by the object.
	@param		device		The IOBluetoothDevice object that the IOBluetoothDevicePair object with which to perform a pairing.
*/

- (void)setDevice:(IOBluetoothDevice*)inDevice;

/*!
    @method		replyPINCode:
	@abstract	This is the required reply to the devicePairingPINCodeRequest delegate message.
				Set the PIN code to use during pairing if required.
	@param		PINCodeSize	The PIN code length in octets (8 bits).
	@param		PINcode		PIN code for the device.  Can be up to a maximum of 128 bits.
*/

- (void)replyPINCode:(ByteCount)PINCodeSize PINCode:(BluetoothPINCode *)PINCode;

/*!
    @method		replyUserConfirmation:
	@abstract	This is the required reply to the devicePairingUserConfirmationRequest delegate message.
	@param		reply		A yes/no answer provide by the user to the numeric comparison presented.
*/

- (void)replyUserConfirmation:(BOOL)reply;

@end

//===========================================================================================================================
//	Delegate methods
//===========================================================================================================================

API_UNAVAILABLE(ios, watchos, tvos)
@protocol IOBluetoothDevicePairDelegate <NSObject>
@optional

/*!
    @method		devicePairingStarted:
	@abstract	Indicates that the pairing has started.
	@param		sender		The IOBluetoothDevicePair object.
*/

- (void) devicePairingStarted:(id)sender;

/*!
    @method		devicePairingConnecting:
	@abstract	Indicates to the delegate that the pairing object is making the device (baseband) connection.
	@param		sender		The IOBluetoothDevicePair object.
*/

- (void) devicePairingConnecting:(id)sender;

/*!
    @method		devicePairingPINCodeRequest:
	@abstract	Indicates to the delegate that the pairing object has made the device (baseband) connection and is
				awaiting the PIN code (if specified) to be entered on the device. Thus, when you recieve this message,
				you should display to the user that they should enter the PIN code on the device.
				The method replyPINCode must be invoked in response and happen before the timeout period of the device.
	@param		sender		The IOBluetoothDevicePair object.
*/

- (void) devicePairingPINCodeRequest:(id)sender;

/*!
    @method		devicePairingUserConfirmationRequest:numericValue
	@abstract	Indicates to the delegate that the pairing object has made the device (baseband) connection and is
				awaiting the a yes/no answer for the Simple Secure Pairing numeric comparison. Thus, when you recieve this message,
				you should display to the user the numeric value and then accept the yes/no answer if it matches the value
				on the other device.
				The method replyUserConfirmation must be invoked in response and happen before the timeout period of the device.
	@param		sender			The IOBluetoothDevicePair object.
	@param		numericValue	Numeric value to be displayed.
*/

- (void) devicePairingUserConfirmationRequest:(id)sender numericValue:(BluetoothNumericValue)numericValue;

/*!
    @method		devicePairingUserPasskeyNotification:passkey
	@abstract	Indicates to the delegate that the pairing object has made the device (baseband) connection and is
				awaiting the passkey (if specified) to be entered on the device for the Secure Simple Pairing.
				Thus, when you recieve this message, you should display to the user that they should enter
				the passkey on the device.
	@param		sender			The IOBluetoothDevicePair object.
	@param		passkey			Passkey to be displayed.
*/

- (void) devicePairingUserPasskeyNotification:(id)sender passkey:(BluetoothPasskey)passkey;

/*!
    @method		devicePairingFinished:error:
	@abstract	Indicates to the delegate that the pairing object has fully completed the process. Can tell the delegate
				when and error occurred during the attempt to pair with the device.
	@discussion	The error passed to your delegate could be kBluetoothHCIErrorAuthenticationFailure,
				kBluetoothHCIErrorLMPResponseTimeout, etc. See Bluetooth.h for all the possibilities.
	@param		sender		The IOBluetoothDevicePair object.
	@param		error		An IOReturn or Bluetooth error code.
*/

- (void) devicePairingFinished:(id)sender error:(IOReturn)error;

/*!
 @method		deviceSimplePairingComplete:status:
 @abstract	Indicates to the delegate that the pairing object has fully completed the simple pairing process. Can tell the delegate
 when and error occurred during the attempt to pair with the device.
 @discussion	The status passed to your delegate could be BluetoothHCIEventStatus, etc. See Bluetooth.h for all the possibilities.
 @param		sender		The IOBluetoothDevicePair object.
 @param		status		A simple pairing complete error code.
 */

- (void) deviceSimplePairingComplete:(id)sender status:(BluetoothHCIEventStatus)status;

@end
