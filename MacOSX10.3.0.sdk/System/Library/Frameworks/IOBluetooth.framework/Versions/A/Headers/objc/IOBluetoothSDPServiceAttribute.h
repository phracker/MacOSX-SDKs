/*
    File:		IOBluetoothSDPServiceAttribute.h
    Copyright:	© 2002 by Apple Computer, Inc. All rights reserved.
*/

#import <Foundation/Foundation.h>

#import <IOBluetooth/Bluetooth.h>

@class IOBluetoothSDPDataElement;

/*!
    @class IOBluetoothSDPServiceAttribute
    @abstract IOBluetoothSDPServiceAttribute represents a single SDP service attribute.
    @discussion A service attribute contains two components: an attribute ID and a data element.
*/

@interface IOBluetoothSDPServiceAttribute : NSObject {
    BluetoothSDPServiceAttributeID	mAttributeID;
    IOBluetoothSDPDataElement		*mAttributeDataElement;
    IOBluetoothSDPDataElement		*mAttributeIDDataElement;
    
    void							*_mReserved;
}

/*!
    @method withID:attributeElementValue:
    @abstract Creates a new service attribute with the given ID and element value.
    @discussion See +[IOBluetoothSDPDataElement withElementValue:] for a description of the types that 
                may be passed in as the attributeElementValue.
    @param attributeID The attribute ID of the new service attribute.
    @param attributeElementValue The data element value of the new service attribute
    @result Returns the newly allocated service attribute object.  Returns nil if there was an error parsing the 				element value.  The returned IOBluetoothSDPDataElement object has been autoreleased, so it is not 
            necessary for the caller to release it.  If the object is to be referenced and kept around, retain 
            should be called.
*/

+ (IOBluetoothSDPServiceAttribute *)withID:(BluetoothSDPServiceAttributeID)newAttributeID attributeElementValue:(NSObject *)attributeElementValue;

/*!
    @method withID:attributeElement:
    @abstract Creates a new service attribute with the given ID and data element.
    @param attributeID The attribute ID of the new service attribute.
    @param attributeElement The data element of the new service attribute.
    @result Returns the newly allocated service attribute object.  Returns nil if there was an error.  
            The returned IOBluetoothSDPDataElement object has been autoreleased, so it is not 
            necessary for the caller to release it.  If the object is to be referenced and kept around, retain 
            should be called.
*/

+ (IOBluetoothSDPServiceAttribute *)withID:(BluetoothSDPServiceAttributeID)newAttributeID attributeElement:(IOBluetoothSDPDataElement *)attributeElement;

/*!
    @method initWithID:attributeElementValue:
    @abstract Initializes a new service attribute with the given ID and element value.
    @discussion See +[IOBluetoothSDPDataElement withElementValue:] for a description of the types that 
                may be passed in as the attributeElementValue.
    @param attributeID The attribute ID of the new service attribute.
    @param attributeElementValue The data element value of the new service attribute
    @result Returns self if successful.  Returns nil if there was an error parsing the element value.
*/

- (id)initWithID:(BluetoothSDPServiceAttributeID)newAttributeID attributeElementValue:(NSObject *)attributeElementValue;

/*!
    @method initWithID:attributeElement:
    @abstract Initializes a new service attribute with the given ID and data element.
    @param attributeID The attribute ID of the new service attribute.
    @param attributeElement The data element of the new service attribute.
    @result Returns self if successful.  Returns nil if there was an error.
*/

- (id)initWithID:(BluetoothSDPServiceAttributeID)newAttributeID attributeElement:(IOBluetoothSDPDataElement *)attributeElement;

/*!
    @method getAttributeID
    @abstract Returns the attribute ID for the target service attribute.
    @result Returns the attribute ID for the target service attribute.
*/

- (BluetoothSDPServiceAttributeID)getAttributeID;

/*!
    @method getDataElement
    @abstract Returns the data element for the target service attribute.
    @result Returns the data element for the target service attribute.
*/

- (IOBluetoothSDPDataElement *)getDataElement;

/*!
    @method getIDDataElement
    @abstract Returns the data element representing the attribute ID for the target service attribute.
    @result Returns the data element representing the attribute ID for the target service attribute.
*/

- (IOBluetoothSDPDataElement *)getIDDataElement;

- (id)initWithCoder:(NSCoder *)coder;
- (void)encodeWithCoder:(NSCoder *)coder;

@end
