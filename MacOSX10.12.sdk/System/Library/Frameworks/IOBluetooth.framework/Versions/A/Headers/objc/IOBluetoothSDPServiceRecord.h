/*
    File:		IOBluetoothSDPServiceRecord.h
    Copyright:	© 2002 by Apple Computer, Inc. All rights reserved.
	Writers:	Eric Brown
*/

#import <Foundation/Foundation.h>

#import <IOBluetooth/Bluetooth.h>
#import <IOBluetooth/IOBluetoothUserLib.h>

@class IOBluetoothDevice;
@class IOBluetoothSDPDataElement;

/*!
    @class IOBluetoothSDPServiceRecord
    @abstract An instance of this class represents a single SDP service record.
    @discussion As a service record, an instance of this class has an NSDictionary of service attributes.
                It also has a link to the IOBluetoothDevice that the service belongs to.  The service
                dictionary is keyed off of the attribute ID of each attribute represented as an NSNumber.
*/

@interface IOBluetoothSDPServiceRecord : NSObject <NSCoding> {
    NSDictionary		*mAttributeDictionary;
    IOBluetoothDevice	*mDeviceForService;
    
    NSArray *sortedAttributes;
}

/*!
 @method		publishedServiceRecordWithDictionary:
 @abstract      Adds a service to the local SDP server.
 @result		Returns an IOBluetoothSDPServiceRecord * with the attributes specified in the provided dictionary.

 @discussion	Each entry in the dictionary representing the service contains the individual attributes.  Each
 attribute in the dict is keyed by a string that must begin with a hex number representing the
 attribute ID.  The key string may contain additional characters if desired as long as they
 follow a space after the ID hex string.  The attribute value must follow the dictionary format
 described by IOBluetoothSDPDataElement.  This dictionary format allows a service dict to be
 created as a plist file and then loaded into the system rather than built up in code.  See the
 example code for an example of how can be done.
 
 If the service record handle, L2CAP PSM or RFCOMM channel ID specified in the dictionary are in
 use, an alternate one will be assigned.
 
 In addition to attributes that represent the service itself, additional attributes may be specified
 that control the local behavior of the service.  To specify these local attributes, an additional
 property titled "LocalAttributes" may be added to the root of the service dict.  The value of this
 property must be a dictionary that contains the individual local attributes.
 
 Currently, only two local attributes are supported: "Persistent" and "TargetApplication".
 
 The "Persistent" local attribute must be either a boolean or number representing whether the service
 should be persistent.  A persistent service will be saved off and restored any time the Bluetooth
 hardware is present.  It will persist through reboots and can only be removed by calling
 IOBluetoothRemoveServiceWithRecordHandle().  This attribute is optional.  By default, if no
 "Persistent" local property is present,	the service will only exist temporarily.  It will
 be removed either when IOBluetoothRemoveServiceWithRecordHandle() is called or when the client
 application exits.
 
 The "TargetApplication" local attribute is used to specify an application to be launched when a
 remote device attempts to connect to the service (by opening either an L2CAP or RFCOMM channel of
 the type specified in the service).  This value must be a string representing the absolute path to
 the target executable (not just the .app wrapper - i.e.
 /System/Library/CoreServices/OBEXAgent.app/Contents/MacOS/OBEXAgent).  This attribute is optional.
 If no "TargetApplication" local attribute is specified, no special action will take place when an
 incoming connection to the service is created.  It is up to the client to be monitoring for the
 connection and to do the right thing when one appears.
 
 The "LocalAttributes" property is optional.  If it is not specified, by default the created service
 is transient and will be removed when the client exits.
 
 Additional local attributes to further control incoming services will be added in the future.
 
 @param		serviceDict	A dictionary containing the attributes for the new service 
*/

+ (instancetype)publishedServiceRecordWithDictionary:(NSDictionary *)serviceDict;

//--------------------------------------------------------------------------------------------------------------------------
/*!	@function	removeServiceRecord
 @abstract	Removes the service from the local SDP server.
 @result		Returns kIOReturnSuccess if successful.
 */

- (IOReturn) removeServiceRecord;

/*!
    @method		withServiceDictionary:device:
	@abstract	Returns an IOBluetoothSDPServiceRecord * with the attributes specified in the provided service dictionary. Provide
				a pointer to an IOBlueotothDevice if you wish to associate the record to a specific IOBluetoothDevice.
	@result		Returns an IOBluetoothSDPServiceRecord * with the attributes specified in the provided dictionary.
*/

+ (instancetype)withServiceDictionary:(NSDictionary *)serviceDict	device:(IOBluetoothDevice *)device;

/*!
    @method		initWithServiceDictionary
	@abstract	Returns an initialized IOBluetoothSDPServiceRecord * with the attributes specified in the provided service dictionary. Provide
				a pointer to an IOBlueotothDevice if you wish to associate the record to a specific IOBluetoothDevice.
	@result		Returns an initialized IOBluetoothSDPServiceRecord * with the attributes specified in the provided dictionary.
*/

- (instancetype) initWithServiceDictionary:(NSDictionary *)serviceDict device:(IOBluetoothDevice *)device;

/*!
    @method		withSDPServiceRecordRef:
	@abstract	Method call to convert an IOBluetoothSDPServiceRecordRef into an IOBluetoothSDPServiceRecord *.
	@param		sdpServiceRecordRef IOBluetoothSDPServiceRecordRef for which an IOBluetoothSDPServiceRecord * is desired.
	@result		Returns the IOBluetoothSDPServiceRecord * for the given IOBluetoothSDPServiceRecordRef.
*/

+ (instancetype)withSDPServiceRecordRef:(IOBluetoothSDPServiceRecordRef)sdpServiceRecordRef;

/*!
    @method	getSDPServiceRecordRef
	@abstract	Returns an IOBluetoothSDPServiceRecordRef representation of the target IOBluetoothSDPServiceRecord object.
	@result		Returns an IOBluetoothSDPServiceRecordRef representation of the target IOBluetoothSDPServiceRecord object.
*/

- (IOBluetoothSDPServiceRecordRef)getSDPServiceRecordRef;

/*!
    @method		device
    @abstract	Returns the IOBluetoothDevice that the target service belongs to.
    @discussion If the service is a local service (i.e. one the current host is vending out), then nil is returned.
    @result		Returns the IOBluetoothDevice that the target service belongs to.  If the service is one the local host
				is vending, then nil is returned.
*/

@property(readonly, retain) IOBluetoothDevice *device;
- (IOBluetoothDevice *)getDevice DEPRECATED_IN_MAC_OS_X_VERSION_10_6_AND_LATER;

/*!
    @method		attributes
    @abstract	Returns an NSDictionary containing the attributes for the service.
    @discussion	The attribute dictionary is keyed off of the attribute id represented as an NSNumber.  The values
                in the NSDictionary are IOBluetoothSDPDataElement objects representing the data element for the
                given attribute.
    @result Returns an NSDictionary containing the attributes for the target service.
*/

@property(readonly, copy) NSDictionary *attributes;
- (NSDictionary *)getAttributes DEPRECATED_IN_MAC_OS_X_VERSION_10_6_AND_LATER;

/*!
    @method		getAttributeDataElement:
    @abstract	Returns the data element for the given attribute ID in the target service.
    @param		attributeID The attribute ID of the desired attribute.	 
    @result		Returns the data element for the given attribute ID in the target service.  If the service does not
				contain an attribute with the given ID, then nil is returned.
*/

- (IOBluetoothSDPDataElement *)getAttributeDataElement:(BluetoothSDPServiceAttributeID)attributeID;

/*!
    @method		getServiceName
    @abstract	Returns the name of the service.
    @discussion This is currently implemented to simply return the attribute with an id of 0x0100.  In
                the future, it will be extended to allow name localization based on the user's chosen
                language or other languages.
    @result		Returns the name of the target service.
*/

- (NSString *)getServiceName;

/*!
    @method		getRFCOMMChannelID:
    @abstract	Allows the discovery of the RFCOMM channel ID assigned to the service.
    @discussion This method will search through the ProtoclDescriptorList attribute to find an entry
                with the RFCOMM UUID (UUID16: 0x0003).  If one is found, it gets the second element of
                the data element sequence and sets the rfcommChannelID pointer to it.  The channel ID
                only gets set when kIOReturnSuccess is returned.
    @param		rfcommChannelID A pointer to the location that will get the found RFCOMM channel ID.
    @result		Returns kIOReturnSuccess if the channel ID is found.
*/

- (IOReturn)getRFCOMMChannelID:(BluetoothRFCOMMChannelID *)rfcommChannelID;

/*!
    @method		getL2CAPPSM:
    @abstract	Allows the discovery of the L2CAP PSM assigned to the service.
    @discussion This method will search through the ProtoclDescriptorList attribute to find an entry
                with the L2CAP UUID (UUID16: 0x0100).  If one is found, it gets the second element of
                the data element sequence and sets the outPSM pointer to it.  The PSM value
                only gets set when kIOReturnSuccess is returned.
    @param		outPSM A pointer to the location that will get the found L2CAP PSM.
    @result		Returns kIOReturnSuccess if the PSM is found.
*/

- (IOReturn)getL2CAPPSM:(BluetoothL2CAPPSM *)outPSM;

/*!
    @method		getServiceRecordHandle:
    @abstract	Allows the discovery of the service record handle assigned to the service.
    @discussion This method will search through the attributes to find the one representing the 
                service record handle.  If one is found the outServiceRecordHandle param is set
                with the value.  The outServiceRecordHandle value only gets set when kIOReturnSuccess 
                is returned.
    @param		outServiceRecordHandle A pointer to the location that will get the found service record handle.
    @result		Returns kIOReturnSuccess if the service record handle is found.
*/

- (IOReturn)getServiceRecordHandle:(BluetoothSDPServiceRecordHandle *)outServiceRecordHandle;

/*!
 @method		matchesUUID16:
 @abstract	Returns TRUE the UUID16 is found in the target service.
 
 			NOTE: This method is only available in Mac OS X 10.7 or later.
 @param uuid16 A BluetoothSDPUUID16 to search for in the target service.	 
 @result Returns TRUE if the UUID16 is present in the service.
 */
- (BOOL)matchesUUID16:(BluetoothSDPUUID16)uuid16;

/*!
    @method		matchesUUIDArray:
    @abstract	Returns TRUE if ALL of the UUIDs in the given array is found in the target service.
    @discussion The given array should contain IOBluetoothSDPUUID objects.  It only returns TRUE if all of
                the UUIDs are found.  This method is like hasServiceFromArray: except that it requires that
                all UUIDs match instead of any of them matching.

				NOTE: This method is only available in Mac OS X 10.2.4 (Bluetooth v1.1) or later.
    @param array An NSArray of IOBluetoothSDPUUID objects to search for in the target service.	 
    @result Returns TRUE if all of the given UUIDs are present in the service.
*/
- (BOOL)matchesUUIDArray:(NSArray *)uuidArray;

/*!
    @method		matchesSearchArray:
    @abstract	Returns TRUE any of the UUID arrays in the search array match the target service.
    @discussion The given array should contain NSArray objects.  Each sub-NSArray should contain
                IOBluetoothSDPUUID objects.  In turn, each sub-NSArray gets passed to -matchesUUIDArray:
                If any of those returns TRUE, then the search stops and TRUE is returned.
                Essentially the master NSArray contains the OR operations and each sub-array contains
                the AND operations.

				NOTE: This method is only available in Mac OS X 10.2.4 (Bluetooth v1.1) or later.
    @param		array An NSArray of NSArrays of IOBluetoothSDPUUID objects.	 
    @result		Returns TRUE if any of the UUID arrays match.
*/
- (BOOL)matchesSearchArray:(NSArray *)searchArray;

/*!
    @method		hasServiceFromArray:
    @abstract	Returns TRUE if any one of the UUIDs in the given array is found in the target service.
    @discussion The given array should contain IOBluetoothSDPUUID objects.  It is currently implemented
                such that it returns TRUE if any of the UUIDs are found.  However in the future, it is likely
                that this will change to more closely match the functionality in the SDP spec so that it only
                returns TRUE if all of the given UUIDs are present.  That way, both AND and OR comparisons
                can be implemented.  Please make a note of this potential change.
    @param		array An NSArray of IOBluetoothSDPUUID objects to search for in the target service.	 
    @result		Returns TRUE if any of the given UUIDs are present in the service.
*/

- (BOOL)hasServiceFromArray:(NSArray *)array;

/*!
 @method		sortedAttributes:
 @abstract		Returns a sorted array of SDP attributes
 @discussion	This method will walk all the elements of the service record and return an array of 
				IOBluetoothSDPServiceAttribute objects sorted by attributeID
 @result		Returns a sorted array of SDP attributes
 */

@property(readonly, copy) NSArray *sortedAttributes;

@end
