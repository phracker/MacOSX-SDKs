/*
 File:		IOBluetoothHandsFreeAudioGateway.h
 Copyright:	(c) 2010 by Apple Inc. All rights reserved.
 */

#import <IOBluetooth/objc/IOBluetoothHandsFree.h>

@class IOBluetoothHandsFreeAudioGatewayExpansion;

/*!
 @header
 @abstract	APIs for managing a hands free audio gateway
 @copyright	(c) 2010 by Apple Inc. All rights reserved.
 */
API_AVAILABLE(macos(10.7)) API_UNAVAILABLE(ios, watchos, tvos)
@interface IOBluetoothHandsFreeAudioGateway : IOBluetoothHandsFree {
	BOOL				_indicatorMode;
	BOOL				_indicatorEventReporting;
    IOBluetoothHandsFreeAudioGatewayExpansion *	_expansion;
}

/*!
 @method		initWithDevice:delegate:
 @abstract		Create a new IOBluetoothHandsFreeAudioGateway to act as a hands free gateway
 @discussion	This will register a listener for incoming connections.
 @param			device An IOBluetoothDevice
 @param			inDelegate An object to act as delegate
 @result		A newly created IOBluetoothHandsFreeAudioGateway object on success, nil on failure
 */
- (instancetype)initWithDevice:(IOBluetoothDevice *)device delegate: (id)inDelegate NS_AVAILABLE_MAC(10_7);

/*!
 @method		createIndicator:indicatorName:min:max:currentValue
 @abstract		Create an indicator
 @discussion	Creates an indicator with min and max values and sets the current value. The current value must be valid.
 @param			indicatorName  See  ÒHands free indicator constants," for standard indicator names.
 @param			minValue Minimum value allowed for the indicator
 @param			maxValue Maximum value allowed for the indicator
 @param			currentValue The current indicator value. Must be within the min and max values passed in or the indicator will not be created.
 */
- (void)createIndicator:(NSString *)indicatorName min:(int)minValue max:(int)maxValue currentValue:(int)currentValue NS_AVAILABLE_MAC(10_7);

/*!
 @method		processATCommand:atCommand
 @abstract		Handles AT commands sent from the hands free device
 @discussion	Implement this in a subclass if you wish to respond to additional AT commands or to change the default response.
 @param			atCommand The at command from the hands free device
 */
- (void)processATCommand:(NSString *)atCommand NS_AVAILABLE_MAC(10_7);

/*!
 @method		sendOKResponse
 @abstract		Sends an OK response
 @discussion	Use this to respond OK.
 */
- (void)sendOKResponse NS_AVAILABLE_MAC(10_7);

/*!
 @method		sendResponse:response
 @abstract		Sends a response to the hands free device
 @discussion	Use this to send a response followed by an OK. Equivalent to [sendResponse:response withOK:YES].
 @param			response The response to send to the hands free device
 */
- (void)sendResponse:(NSString *)response NS_AVAILABLE_MAC(10_7);

/*!
 @method		sendResponse:response:withOK
 @abstract		Sends a response to the hands free device
 @discussion	Use this to send a response and optionally followed by an OK.
 @param			response The response to send to the hands free device
 @param			withOK If yes, an OK response will also be sent.
 */
- (void)sendResponse:(NSString *)response withOK:(BOOL)withOK NS_AVAILABLE_MAC(10_7);

@end

API_UNAVAILABLE(ios, watchos, tvos)
@protocol IOBluetoothHandsFreeAudioGatewayDelegate
@optional

/*!
 @method		handsFree:hangup
 @discussion	Tells the delegate that the device is sending a hangup.
 @param			device The IOBluetoothHandsFreeAudioGateway object
 @param			redial Always 1.
 */
- (void)handsFree:(IOBluetoothHandsFreeAudioGateway *)device hangup:(NSNumber *)hangup NS_AVAILABLE_MAC(10_7);

/*!
 @method		handsFree:redial
 @discussion	Tells the delegate that the device is trying to redial.
 @param			device The IOBluetoothHandsFreeAudioGateway object
 @param			redial Always 1.
 */
- (void)handsFree:(IOBluetoothHandsFreeAudioGateway *)device redial:(NSNumber *)redial NS_AVAILABLE_MAC(10_7);

@end
