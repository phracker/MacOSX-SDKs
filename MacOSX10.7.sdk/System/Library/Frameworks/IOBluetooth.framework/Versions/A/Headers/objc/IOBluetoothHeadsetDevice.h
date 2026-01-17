
/*!
	@header
	@abstract	APIs for managing a remote Headset device
	@copywrite	(C) 2006 by Apple Computer, Inc., all rights reserved.
 	@discussion
				 ***		DEPRECATED IN 10.7
				 ***		You should transition your code to IOBluetoothHandsFreeDevice class.
				 ***		This API may be removed any time in the future. 

 */

#if BLUETOOTH_VERSION_MAX_ALLOWED >= BLUETOOTH_VERSION_2_0


#import <Foundation/Foundation.h>
#import <IOBluetooth/Bluetooth.h>
#import <IOBluetooth/objc/IOBluetoothRFCOMMAudioController.h>


//====================================================================================================================
//	IOBluetoothHeadsetDevice
//====================================================================================================================
/*!
	@class			IOBluetoothHeadsetDevice
	@abstract		
	@discussion		There are some suggested error checks developers should provide before using this object.  When 
					connecting out to a remote device developers need to check that the device has the Headset service in 
					its SDP records. Use the provided class method in this object.

					To attach to a device that has connected into the machine, developers need to check for the existence of 
					the service (using the provided class method in this object), that the device is attaching to the RFCOMM 
					channel associated with the Headset Gateway SDP record published on the machine, and that the device 
					that is connecting is configured as a headset with the machine.  Developers will need to search the local
					SDP records to find the Gateway record for the machine, the provided APIs are only for the target device.
*/
@interface IOBluetoothHeadsetDevice : IOBluetoothRFCOMMAudioController {

}

/*!
	@method		getRequiredSDPServiceRecordForDevice
	@abstract	Returns the Headset SDP service record for the device.
	@param		device A valid IOBluetoothDevice
	@result		The Headset SDP record for the device on success, nil on failure
 */
+ (IOBluetoothSDPServiceRecord *) getRequiredSDPServiceRecordForDevice:(IOBluetoothDevice*)device DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;
//
/*!
	@method		getRequiredSDPRFCOMMChannelIDForDevice
	@abstract	Return the rfcomm channel ID as specified in the Headset SDP record of the device.
	@param		device A valid IOBluetoothDevice
	@result		The SDP specified RFCOMM channel ID for the device on success, 0 on failure
*/
+ (BluetoothRFCOMMChannelID) getRequiredSDPRFCOMMChannelIDForDevice:(IOBluetoothDevice*)device DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;


/*!
	@method		initWithIncomingDevice:incomingRFCOMMChannelID:delegate:
	@abstract	Create a new IOBluetoothHeadsetDevice for a device that is trying to connect in
	@discussion	An incoming connection from a Headset/Handsfree device must be validated against the local Gateway service records 
				to find out what the device is trying to connect to. For example, headsets must be connecting over RFCOMM to a  
				corresponding headset audio gateway rfcomm channel published in the service, handsfree to a handsfree audio gateway 
				service.  If this were L2CAP we could just look at the PSM, but these devices use RFCOMM.  This method will do the 
				proper check internally and will return nil if the incoming channel does not match with a published Headset AG record.
	@param		device A valid IOBluetoothDevice with baseband connection
	@param		incomingRFCOMMChannelID The RFCOMM ID the device is trying to connect to
	@param		inDelegate An object to act as delegate
	@result		A newly created IOBluetoothHeadsetDevice object on success, nil on failure
 */
- (id) initWithIncomingDevice: (IOBluetoothDevice *)device 
	  incomingRFCOMMChannelID: (BluetoothRFCOMMChannelID)incomingRFCOMMChannelID
					 delegate: (id)inDelegate DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;


/*!
	@method		initForConnectionToDevice:supportedFeatures:delegate:
	@abstract	Create a new IOBluetoothHeadsetDevice for outgoing connect to a device
	@discussion	
	@param		device A valid IOBluetoothDevice
	@param		inDelegate An object to act as delegate
	@result		A newly created IOBluetoothHeadsetDevice object on success, nil on failure
*/
- (id) initForConnectionToDevice: (IOBluetoothDevice *)device
						delegate: (id)inDelegate DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

@end

@interface IOBluetoothDevice ( HeadsetAdditions )
/*!
 @method		headsetAudioGatewayServiceRecord
 @abstract		Return the headset gateway SDP record
 @discussion	Returns the headsetgateway SDP record.
 @result		The headset gateway SDP record
 */
- (IOBluetoothSDPServiceRecord *)headsetAudioGatewayServiceRecord DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
 @method		isHeadsetAudioGateway
 @abstract		Return the devices support for headset gateway
 @discussion	Returns the devices support for headset gateway (obtained from the devices SDP record).
 @result		YES if the device supports headset gateway; otherwise, NO.
 */
- (BOOL)isHeadsetAudioGateway DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
 @method		headsetDeviceServiceRecord
 @abstract		Return the headset device SDP record
 @discussion	Returns the headset device SDP record.
 @result		The headset device SDP record
 */
- (IOBluetoothSDPServiceRecord *)headsetDeviceServiceRecord DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
 @method		isHeadsetDevice
 @abstract		Return the devices support for headset device
 @discussion	Returns the devices support for headset device (obtained from the devices SDP record).
 @result		YES if the device supports headset device; otherwise, NO.
 */
- (BOOL)isHeadsetDevice DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

@end


#endif /* BLUETOOTH_VERSION_MAX_ALLOWED >= BLUETOOTH_VERSION_2_0 */
