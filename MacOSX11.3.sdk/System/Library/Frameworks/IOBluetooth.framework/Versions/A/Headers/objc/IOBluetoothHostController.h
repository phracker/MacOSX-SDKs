/*
	Contains:	An object representation of a Bluetooth host controller (HCI).
	Copyright:	(C) 2006-2007 by Apple Computer, Inc., all rights reserved.
*/

#import <Foundation/Foundation.h>
#import <IOBluetooth/Bluetooth.h>

//===========================================================================================================================
//	Forward Declarations
//===========================================================================================================================

@class IOBluetoothDevice;

//===========================================================================================================================
//	IOBluetoothHostController
//===========================================================================================================================

//---------------------------------------------------------------------------------------------------------------------------
/*!	@class			IOBluetoothHostController
	@abstract		This class is a representation of a Bluetooth Host Controller Interface that is present on the
					local computer (either plugged in externally or available internally).
	@discussion		This object can be used to ask a Bluetooth HCI for certain pieces of information, and be used to make
					it perform certain functions.
*/

API_UNAVAILABLE(ios, watchos, tvos)
@interface IOBluetoothHostController : NSObject
{
@private
	
	BluetoothHCIEventMask		_eventCodeMask;
	BluetoothClassOfDevice		_cachedClassOfDevice;
	id							_delegate;
	NSTimer *					_timerClassOfDeviceSetting;
	void *						_eventListener;

    id                          _mReserved;
    id                          _mUnused000;
    id                          _mUnused001;
    id                          _mUnused002;
}

@property(assign) id delegate;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method		defaultController
	@abstract	Gets the default HCI controller object.
	@result		A (autoreleased) pointer to the created IOBluetoothHostController object.
*/

+ (instancetype)defaultController;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method		powerState
	@abstract	Gets the controller power state
	@result		The current controller's power state.  This will be 1 for on, or 0 for off.  Only Apple Bluetooth adapters support power off
 */
@property(readonly) BluetoothHCIPowerState powerState;


//---------------------------------------------------------------------------------------------------------------------------
/*!	@method		classOfDevice
	@abstract	Gets the current class of device value.
	@result		Returns the current class of device value.
*/

- (BluetoothClassOfDevice)classOfDevice;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method		setClassOfDevice:forTimeInterval:
	@abstract	Sets the current class of device value, for the specified amount of time. Note that the time interval *must*
				be set and valid. The range of acceptable values is 30-120 seconds. Anything above or below will be rounded
				up, or down, as appropriate.
	@result		Returns the whether setting the class of device value was successful. 0 if success, error code otherwise.
*/

- (IOReturn)setClassOfDevice:(BluetoothClassOfDevice)classOfDevice		forTimeInterval:(NSTimeInterval)seconds;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method		addressAsString
	@abstract	Convience routine to get the HCI controller's Bluetooth address as an NSString object.
	@result		Returns NSString *. nil if the address could not be retrieved.
*/

- (NSString *)addressAsString;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method		nameAsString
 @abstract	Gets the "friendly" name of HCI controller.
 @result		Returns NSString with the device name, nil if there is not one or it cannot be read.
 */

- (NSString *)nameAsString;

@end

#if 0
#pragma mark -
#endif

//===========================================================================================================================
//	IOBluetoothHostControllerDelegate
//===========================================================================================================================

/*!
    @category 		IOBluetoothHostControllerDelegate
    @discussion		This category on NSObject describes the delegate methods for the IOBluetoothHostController object. All
					methods are optional, but it is highly recommended you implement them all. Do NOT invoke remote name
					requests on found IOBluetoothDevice objects unless the controller object has been stopped. Doing so may
					deadlock your process.
*/

API_UNAVAILABLE(ios, watchos, tvos)
@interface NSObject( IOBluetoothHostControllerDelegate )

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method			readRSSIForDeviceComplete:device:info:error:
	@discussion 	This delegate gets invoked when an RSSI command complete event occurs. This could occur because you
					invoked it by issuing an -readRSSIForDevice: command, or someone else did from another app on the
					same controller.
	@param			sender			Controller object that sent this delegate message.
*/

- (void)	readRSSIForDeviceComplete:(id)controller device:(IOBluetoothDevice*)device	info:(BluetoothHCIRSSIInfo*)info	error:(IOReturn)error;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method			readLinkQualityForDeviceComplete:device:info:error:
	@discussion 	This delegate gets invoked when an read link quality command complete event occurs. This could occur because you
					invoked it by issuing an -readLinkQualityForDevice: command, or someone else did from another app on the
					same controller.
	@param			sender			Controller object that sent this delegate message.
*/

- (void)	readLinkQualityForDeviceComplete:(id)controller device:(IOBluetoothDevice*)device	info:(BluetoothHCILinkQualityInfo*)info	error:(IOReturn)error;

@end

extern NSString * const IOBluetoothHostControllerPoweredOnNotification;
extern NSString * const IOBluetoothHostControllerPoweredOffNotification;
