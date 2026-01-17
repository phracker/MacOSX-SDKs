
/*!
	@header
	@abstract	APIs for managing a remote Handsfree device
	@copyright	(C) 2006 by Apple Computer, Inc., all rights reserved.
 	@discussion 
				 ***		DEPRECATED IN 10.7
				 ***		You should transition your code to IOBluetoothHandsFree class.
				 ***		This API may be removed any time in the future. 
 
 */


#if BLUETOOTH_VERSION_MAX_ALLOWED >= BLUETOOTH_VERSION_2_0

#import <Foundation/Foundation.h>
#import <IOBluetooth/Bluetooth.h>
#import <IOBluetooth/objc/IOBluetoothRFCOMMAudioController.h>


//====================================================================================================================
//  HandsFree Features
//====================================================================================================================
/*!
	@enum		IOBluetoothHandsFreeFeatures
	@abstract	Constants for HandsFree features.
	@discussion	Hey Developers!  Apple doesn't support any of these features.  Developers will need to override the 
				rfcommChannelData delegate method from the RFCOMMAudioController in a subclass of this object to support 
				the features they would like to implement.  Developers should be aware that all "AT+" commands and 
				responses used in this profile are to be wrapped with the proper terminators show here:  \r\nXX+XXX\r\n
 				
*/
typedef enum IOBluetoothHandsFreeFeatures
{
	kBluetoothHandsFreeFeatureNone						= (0),
	kBluetoothHandsFreeFeatureThreeWayCalling			= (1<<0),
	kBluetoothHandsFreeFeatureECAndOrNRFunction			= (1<<1),
	kBluetoothHandsFreeFeatureVoiceRecognition			= (1<<2),
	kBluetoothHandsFreeFeatureInBandRingTone			= (1<<3),
	kBluetoothHandsFreeFeatureAttachedNumberToVoiceTag	= (1<<4),
	kBluetoothHandsFreeFeatureRejectCallCapability		= (1<<5),
	kBluetoothHandsFreeFeatureEnhancedCallStatus		= (1<<6),
	kBluetoothHandsFreeFeatureEnhancedCallControl		= (1<<7), 
	kBluetoothHandsFreeFeatureExtendedErrorResultCodes	= (1<<8)	
} IOBluetoothHandsFreeFeatures;


//====================================================================================================================
//	IOBluetoothHandsFreeGateway
//====================================================================================================================
/*!
	@class			IOBluetoothHandsFreeGateway
	@abstract		
	@discussion		
					 ***		DEPRECATED IN 10.7
					 ***		You should transition your code to IOBluetoothHandsFree class.
					 ***		This API may be removed any time in the future. 
 
 					In order to use this object with a Bluetooth Handsfree device, developers need to publish a Handsfree
					 Audio Gateway SDP service.  Some devices will be fine without seeing a published HF Gateway service
					 on your machine/device, but a majority of them will not like it and will behave sporadically. Fields
					 in the SDP record are used to tell the device about what features the Gateway supports so its required
					 to have it published.
 
					There are some suggested error checks developers should provide before using this object.  When 
					connecting out to a remote device developers need to check that the device has the Handsfree service in 
					its SDP records. Use the provided class method in this object.
 
					To attach to a device that has connected into the machine, developers need to check for the existence of 
					the service (using the provided class method in this object), that the device is attaching to the RFCOMM 
					channel associated with the Handsfree Gateway SDP record published on the machine, and that the device 
					that is connecting is configured as a headset with the machine.  Developers will need to search the local
					SDP records to find the Gateway record for the machine, the provided APIs are only for the target device.
*/
@interface IOBluetoothHandsFreeGateway : IOBluetoothRFCOMMAudioController {
	
	uint32_t		mDeviceSupportedFeatures;
	uint32_t		mGatewaySupportedFeatures;		
}


// ---------------------------------------------------
// Util's
//
/*!
	@method		getRequiredSDPServiceRecordForDevice
	@abstract	Returns the Handsfree SDP service record for the device.
	@param		device A valid IOBluetoothDevice
	@result		The Handsfree SDP record for the device on success, nil on failure
 */
+ (IOBluetoothSDPServiceRecord *) getRequiredSDPServiceRecordForDevice:(IOBluetoothDevice*)device DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;
//
/*!
	@method		getRequiredSDPRFCOMMChannelIDForDevice
	@abstract	Return the rfcomm channel ID as specified in the Handsfree SDP record of the device.
	@param		device A valid IOBluetoothDevice
	@result		The SDP specified RFCOMM channel ID for the device on success, 0 on failure
*/
+ (BluetoothRFCOMMChannelID) getRequiredSDPRFCOMMChannelIDForDevice:(IOBluetoothDevice*)device DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;


// ---------------------------------------------------
// Init's
//
/*!
	@method		initWithIncomingDevice:incomingRFCOMMChannelID:supportedFeatures:delegate:
	@abstract	Create a new IOBluetoothHandsFreeGateway for a device that is trying to connect in
	@discussion	An incoming connection from a Headset/Handsfree device must be validated against the local Gateway service records 
				to find out what the device is trying to connect to. For example, headsets must be connecting over RFCOMM to a  
				corresponding headset audio gateway rfcomm channel published in the service, handsfree to a handsfree audio gateway 
				service.  If this were L2CAP we could just look at the PSM, but these devices use RFCOMM.  This method will do the 
				proper check internally and will return nil if the incoming channel does not match with a published Handsfree AG record.
	@param		device A valid IOBluetoothDevice with baseband connection
	@param		incomingRFCOMMChannelID The RFCOMM ID the device is trying to connect to
	@param		supportedFeatures A bitmask of IOBluetoothHandsFreeFeatures values.  This object does not support any features
	@param		inDelegate An object to act as delegate
	@result		A newly created IOBluetoothHandsFreeGateway object on success, nil on failure
*/
- (id) initWithIncomingDevice: (IOBluetoothDevice *)device 
	  incomingRFCOMMChannelID: (BluetoothRFCOMMChannelID)incomingRFCOMMChannelID 
			supportedFeatures: (UInt32)supportedFeatures
					 delegate: (id)inDelegate DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
	@method		initForConnectionToDevice:supportedFeatures:delegate:
	@abstract	Create a new IOBluetoothHandsFreeGateway for outgoing connect to a device
	@discussion	
	@param		device A valid IOBluetoothDevice
	@param		supportedFeatures A bitmask of IOBluetoothHandsFreeFeatures values.  This object does not support any features
	@param		inDelegate An object to act as delegate
	@result		A newly created IOBluetoothHandsFreeGateway object on success, nil on failure
*/
- (id) initForConnectionToDevice: (IOBluetoothDevice *)device 
			   supportedFeatures: (UInt32)supportedFeatures
						delegate: (id)inDelegate DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;


// ---------------------------------------------------
//  Gateway Features
//
/*!
	@method		setGatewaySupportedFeatures
	@abstract	Set the supported gateway features
	@discussion	Sets the class variable which is sent to the remote device during connection and setup. 
				Once the setup process is complete, shortly after connecting, calling this method will do 
				nothing. Also note that this object does not support any features, so developers will need to subclass 
				this object, override the rfcomm delegate method from the baseclass, and handle the feature setup on their
				own to make the features work.
	@param		gatewaySupportedFeatures A mask of feature values from the IOBluetoothHandsFreeFeatures enum
*/
- (void) setGatewaySupportedFeatures:(UInt32)gatewaySupportedFeatures DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
	@method		getGatewaySupportedFeatures
	@abstract	Get the supported gateway features
	@discussion	
	@result		A mask of feature values from the IOBluetoothHandsFreeFeatures enum
*/
- (UInt32) getGatewaySupportedFeatures DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;



// ---------------------------------------------------
//  Device Features
//
/*!
	@method		getDeviceSupportedFeatures
	@abstract	Get the supported device features
	@discussion	Get the device features  set during the connection setup process with the device.
	@result		A mask of feature values from the IOBluetoothHandsFreeFeatures enum
*/
- (UInt32) getDeviceSupportedFeatures DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;



@end

#endif /* BLUETOOTH_VERSION_MAX_ALLOWED >= BLUETOOTH_VERSION_2_0 */







