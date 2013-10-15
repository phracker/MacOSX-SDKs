
/*!
	@header
	@abstract	APIs for managing a remote Headset device
	@copywrite	(C) 2006 by Apple Computer, Inc., all rights reserved.
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
+ (IOBluetoothSDPServiceRecord *) getRequiredSDPServiceRecordForDevice:(IOBluetoothDevice*)device;
//
/*!
	@method		getRequiredSDPRFCOMMChannelIDForDevice
	@abstract	Return the rfcomm channel ID as specified in the Headset SDP record of the device.
	@param		device A valid IOBluetoothDevice
	@result		The SDP specified RFCOMM channel ID for the device on success, 0 on failure
*/
+ (BluetoothRFCOMMChannelID) getRequiredSDPRFCOMMChannelIDForDevice:(IOBluetoothDevice*)device;


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
					 delegate: (id)inDelegate;


/*!
	@method		initForConnectionToDevice:supportedFeatures:delegate:
	@abstract	Create a new IOBluetoothHeadsetDevice for outgoing connect to a device
	@discussion	
	@param		device A valid IOBluetoothDevice
	@param		inDelegate An object to act as delegate
	@result		A newly created IOBluetoothHeadsetDevice object on success, nil on failure
*/
- (id) initForConnectionToDevice: (IOBluetoothDevice *)device
						delegate: (id)inDelegate;

@end

#endif /* BLUETOOTH_VERSION_MAX_ALLOWED >= BLUETOOTH_VERSION_2_0 */
