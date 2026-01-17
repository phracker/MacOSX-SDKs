/*
	Contains:	An object representation of a Bluetooth host controller (HCI).
	Copyright:	(C) 2006-2007 by Apple Computer, Inc., all rights reserved.
*/

#import <Foundation/Foundation.h>
#import <IOBluetooth/Bluetooth.h>

#if BLUETOOTH_VERSION_MAX_ALLOWED >= BLUETOOTH_VERSION_2_0

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

@interface IOBluetoothHostController : NSObject
{
@private
	
	BluetoothHCIEventMask		_eventCodeMask;
	BluetoothClassOfDevice		_cachedClassOfDevice;
	id							_delegate;
	NSTimer *					_timerClassOfDeviceSetting;
	void *						_eventListener;
	void *						_expansionPtr;

	void *						_expansion[4];
}

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method		controllerWithDelegate
	@abstract	Gets the default HCI controller object.
	@result		A pointer to the created IOBluetoothHostController object.
*/

+ (IOBluetoothHostController *)defaultController;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method		setDelegate
	@abstract   Set the delegate that will receive delegate messages, as defined below.
	@param		id	The object that should receive delegate messages.
	@discussion All delegate methods are optional, although it would be a good idea to implement them all.
*/

- (void)setDelegate:(id)delegate;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method		delegate
	@abstract	Returns the current delegate, if any.
	@result		Returns delegate object, otherwise returns nil.
*/

- (id)delegate;

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
/*!	@method		getAddress
	@abstract	Gets the HCI controller's Bluetooth address.
	@param		sender			Pointer to a BluetoothDeviceAddress structure.
	@result		Returns error, if there was one.
*/

- (IOReturn)getAddress:(BluetoothDeviceAddress*)ioDeviceAddress;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method		addressAsString
	@abstract	Convience routine to get the HCI controller's Bluetooth address as an NSString object.
	@result		Returns NSString *. nil if the address could not be retrieved.
*/

- (NSString *)addressAsString;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method		getSupportedFeatures
	@abstract	Get the HCI controller's supported features. See Bluetooth.h for a list of flags.
	@result		Returns error, if there was one.
*/

- (IOReturn)getSupportedFeatures:(BluetoothHCISupportedFeatures*)features;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method		name
	@abstract	Gets the "friendly" name of HCI controller.
	@result		Returns NSString with the device name, nil if there is not one or it cannot be read.
*/

- (NSString *)name;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method		readRSSIForDevice
	@abstract	Gets the RSSI value for a Bluetooth device.
	@result		Returns noErr if the command was successfully sent to the hardware. Results will be returned on the delegate method -RSSIForDevice.
*/

- (IOReturn)readRSSIForDevice:(IOBluetoothDevice*)device;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method		readRSSIForDevice
	@abstract	Gets the RSSI value for a Bluetooth device.
	@result		Returns noErr if the command was successfully sent to the hardware. Results will be returned on the delegate method -linkQualityForDevice.
*/
- (IOReturn)readLinkQualityForDevice:(IOBluetoothDevice*)device;

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

@interface NSObject( IOBluetoothHostControllerDelegate )

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method			controllerClassOfDeviceReverted
	@discussion 	This delegate gets invoked when the Class of Device has been changed
					with the -setClassOfDevice:forTimeInterval: method, and the specified time interval expires.
	@param			sender			Controller object that sent this delegate message.
*/

- (void)	controllerClassOfDeviceReverted:(id)sender;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@method			RSSIForDevice:device:info:error:
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

#endif /* BLUETOOTH_VERSION_MAX_ALLOWED >= BLUETOOTH_VERSION_2_0 */

