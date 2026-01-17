/*
    File:		IOBluetoothSDPDataElement.h
    Copyright:	© 2002 by Apple Computer, Inc. All rights reserved.
	Writers:	Eric Brown
*/

#import <Foundation/Foundation.h>

#import <IOBluetooth/Bluetooth.h>
#import <IOBluetooth/IOBluetoothUserLib.h>

@class IOBluetoothSDPUUID;

/*!
    @class IOBluetoothSDPDataElement
    @abstract An instance of this class represents a single SDP data element as defined by the Bluetooth SDP spec.
    @discussion The data types described by the spec have been mapped onto the base Foundation classes NSNumber, 
                NSArray, NSData as well as IOBluetoothSDPUUID.  The number and boolean types (type descriptor 1, 2 
                and 5) are represented as NSNumber objects with the exception of 128-bit numbers which are 
                represented as NSData objects in their raw format.  The UUID type (type descriptor 3) is 
                represented by IOBluetoothSDPUUID.  The string and URL types (type descriptor 4 and 8) are 
                represented by NSString.  The sequence types (type descriptor 6 and 7) are represented by NSArray.
                
                Typically, you will not need to create an IOBluetoothSDPDataElement directly, the system will
                do that automatically for both client and server operations.  However, the current API for adding 
                SDP services to the system does allow the use of an NSDictionary based format for creating new 
                services.  The purpose for that is to allow a service to be built up completely in a text file
                (a plist for example) and then easily imported into an app and added to the system without a 
                lot of tedious code to build up the entire SDP service record.
                
                The basis for that NSDictionary structure comes from the IOBluetoothSDPDataElement.  At its
                simplest, a data element is made up of three parts: the type descriptor, the size (from which
                the size descriptor is generated) and the actual value.  To provide a complete representation
                of a data element, an NSDictionary with three entries can be used.  Each of the three entries
                has a key/value pair representing one of the three attributes of a data element.  The first
                key/value pair has a key 'DataElementType' that contains a number value with the actual
                type descriptor for the data element.  The second pair has a key 'DataElementSize' that
                contains the actual size of the element in bytes.  The size descriptor will be calculated
                based on the size and type of the element.  The third pair is the value itself whose key is
                'DataElementValue' and whose type corresponds to the type mapping above.
                
                In addition to this complete description of a data element, their are some shortcuts that
                can be used for some of the common types and sizes.
                
                If the 'DataElementType' value is one of the numeric types (1, 2), the 'DataElementValue' 
                can be an NSData instead of an NSNumber.  In that case, the numeric data is taken in network 
                byte order (MSB first).  Additionally, the 'DataElementSize' parameter may be omitted and the 
                size will be taken from the length of the data object.
                
                If the 'DataElementType' value is the nil type (0), no 'DataElementSize' or 'DataElementValue'
                entries are needed.
                
                If the 'DataElementType' value is any of the other types, the 'DataElementSize' entry is not
                needed since the size will be taken directly from the value (data, array, string).
                
                In the case where the element is an unsigned, 32-bit integer (type descriptor 1, size descriptor
                2), the value itself may simply be a number (instead of a dictionary as in the previous examples).
                
                In the case where the element is a UUID (type descriptor 3), the value itself may be a data object.  
                The UUID type will be inferred and the size taken from the length of the data object.
                
                In the case where the element is a text string (type descriptor 4), the value may be a string object.
                The text string type will be inferred and the size taken from the length of the string.
                
                In the case where the element is a data element sequence, the value may be an array object.  The
                type will be inferred and the size taken from the length of the array.  Additionally, the array
                must contain sub-elements that will be parsed out individually.
*/

@interface IOBluetoothSDPDataElement : NSObject {
    BluetoothSDPDataElementTypeDescriptor	mTypeDescriptor;
    BluetoothSDPDataElementSizeDescriptor	mSizeDescriptor;
    UInt32									mSize;
    NSObject								*mValue;
    
    void									*_mReserved;
}

/*!
    @method withElementValue:
    @abstract Creates a new IOBluetoothSDPDataElement with the given value.
    @discussion The value must follow the format listed above and must be an instance of NSData, NSString, NSNumber, 
                NSArray, NSDictionary, IOBluetoothSDPUUID.
    @param element	The data element value of one of the specified types. 
    @result Returns the newly allocated data element object.  Returns nil if there was an error parsing the element
            value.  The returned IOBluetoothSDPDataElement object has been autoreleased, so it is not necessary
            for the caller to release it.  If the object is to be referenced and kept around, retain should be
            called.
*/

+ (IOBluetoothSDPDataElement *)withElementValue:(NSObject *)element;

/*!
    @method withType:sizeDescriptor:size:value:
    @abstract Creates a new IOBluetoothSDPDataElement with the given attributes.
    @discussion Warning - be careful using this method.  There is next to no error checking done on the 
                attributes.  It is entirely possible to construct an invalid data element.  It is recommended
                that +withElementValue: be used instead of this one.
    @param typeDescriptor The type descriptor for the data element.
    @param sizeDescriptor The size descriptor for the data element (verify it matches the size parameter).
    @param size The size of the data element in bytes (make sure it is a valid size for the given size descriptor).
    @param value The raw value itself.  This must be the base NSString, NSNumber, NSArray or NSData objects.  It
                    may not be NSDictionary.  If a dictionary format is present, use +withElementValue:.
    @result Returns the newly allocated data element object.  Returns nil if an error is encountered (not likely
                    due to the limited error checking currently done).  The returned IOBluetoothSDPDataElement 
                    object has been autoreleased, so it is not necessary for the caller to release it.  If the 
                    object is to be referenced and kept around, retain should be called.
*/

+ (IOBluetoothSDPDataElement *)withType:(BluetoothSDPDataElementTypeDescriptor)type sizeDescriptor:(BluetoothSDPDataElementSizeDescriptor)newSizeDescriptor size:(UInt32)newSize value:(NSObject *)newValue;

/*!
    @method	withSDPDataElementRef:
	@abstract	Method call to convert an IOBluetoothSDPDataElementRef into an IOBluetoothSDPDataElement *.
        @param	sdpDataElementRef IOBluetoothSDPDataElementRef for which an IOBluetoothSDPDataElement * is desired.
	@result		Returns the IOBluetoothSDPDataElement * for the given IOBluetoothSDPDataElementRef.
*/

+ (IOBluetoothSDPDataElement *)withSDPDataElementRef:(IOBluetoothSDPDataElementRef)sdpDataElementRef;

/*!
    @method initWithElementValue:
    @abstract Initializes a new IOBluetoothSDPDataElement with the given value.
    @discussion The value must follow the format listed above and must be an instance of NSData, NSString, NSNumber, 
                NSArray, NSDictionary, IOBluetoothSDPUUID.
    @param element	The data element value of one of the specified types. 
    @result Returns self if successful.  Returns nil if there was an error parsing the element value.
*/

- (id)initWithElementValue:(NSObject *)element;

/*!
    @method initWithType:sizeDescriptor:size:value:
    @abstract Initializes a new IOBluetoothSDPDataElement with the given attributes.
    @discussion Warning - be careful using this method.  There is next to no error checking done on the 
                attributes.  It is entirely possible to construct an invalid data element.  It is recommended
                that +withElementValue: be used instead of this one.
    @param typeDescriptor The type descriptor for the data element.
    @param sizeDescriptor The size descriptor for the data element (verify it matches the size parameter).
    @param size The size of the data element in bytes (make sure it is a valid size for the given size descriptor).
    @param value The raw value itself.  This must be the base NSString, NSNumber, NSArray or NSData objects.  It
                    may not be NSDictionary.  If a dictionary format is present, use +withElementValue:.
    @result Returns self if successful.  Returns nil if an error is encountered (not likely
                    due to the limited error checking currently done).
*/

- (id)initWithType:(BluetoothSDPDataElementTypeDescriptor)newType sizeDescriptor:(BluetoothSDPDataElementSizeDescriptor)newSizeDescriptor size:(UInt32)newSize value:(NSObject *)newValue;

/*!
    @method	getSDPDataElementRef
	@abstract	Returns an IOBluetoothSDPDataElementRef representation of the target IOBluetoothSDPDataElement object.
	@result		Returns an IOBluetoothSDPDataElementRef representation of the target IOBluetoothSDPDataElement object.
*/

- (IOBluetoothSDPDataElementRef)getSDPDataElementRef;

/*!
    @method getTypeDescriptor
    @abstract Returns the SDP spec defined data element type descriptor for the target data element.
    @result Returns the type descriptor for the target data element.
*/

- (BluetoothSDPDataElementTypeDescriptor)getTypeDescriptor;

/*!
    @method getSizeDescriptor
    @abstract Returns the SDP spec defined data element size descriptor for the target data element.
    @result Returns the size descriptor for the target data element.
*/

- (BluetoothSDPDataElementSizeDescriptor)getSizeDescriptor;

/*!
    @method getSize
    @abstract Returns the size in bytes of the target data element.
    @discussion The size is valid whether the data element has a fixed or variable size descriptor.
    @result Returns the size in bytes of the target data element.
*/

- (UInt32)getSize;

/*!
    @method getNumberValue
    @abstract If the data element is represented by a number, it returns the value as an NSNumber.
    @discussion The data types represented by a number are 1 (unsigned int), 2 (signed int) and 5 (boolean) 
                except for 128-bit versions of 1 and 2.
    @result Returns an NSNumber representation of the data element if it is a numeric type.
*/

- (NSNumber *)getNumberValue;

/*!
    @method getDataValue
    @abstract If the data element is represented by a data object, it returns the value as an NSData.
    @discussion The data types represented by a data object are 128-bit versions of 1 (unsigned int) and 
                2 (signed int).
    @result Returns an NSData representation of the data element if it is a 128-bit number.
*/

- (NSData *)getDataValue;

/*!
    @method getStringValue
    @abstract If the data element is represented by a string object, it returns the value as an NSString.
    @discussion The data types represented by a string object are 4 (text string) and 8 (URL).
    @result Returns an NSString representation of the data element if it is a text or URL type.
*/

- (NSString *)getStringValue;

/*!
    @method getArrayValue
    @abstract If the data element is represented by an array object, it returns the value as an NSArray.
    @discussion The data types represented by an array object are 6 (data element sequence) and 7 (data
                element alternative).
    @result Returns an NSArray representation of the data element if it is a sequence type.
*/

- (NSArray *)getArrayValue;

/*!
    @method getUUIDValue
    @abstract If the data element is a UUID (type 3), it returns the value as an IOBluetoothSDPUUID.
    @result Returns an IOBluetoothSDPUUID representation of the data element if it is a UUID.
*/

- (IOBluetoothSDPUUID *)getUUIDValue;

/*!
    @method getValue
    @abstract Returns the object value of the data element.
    @discussion The value returned may be an NSNumber, NSString, NSData, NSArray or IOBluetoothSDPDataElement
                depending on the type of the data element.
    @result Returns the object value of the target data element.
*/

- (NSObject *)getValue;

/*!
    @method containsDataElement:
    @abstract Checks to see if the target data element is the same as the dataElement parameter or if it contains
                the dataElement parameter (if its a sequence type).
    @discussion If the target data element is not a sequence type, this method simply compares the two data elements.  If
                it is a sequence type, it will search through the sequence (and sub-sequences) for the dataElement
                parameter.
    @param dataElement The data element to compare with (and search for). 
    @result Returns TRUE if the target either matches the given data element or if it contains the given data element.
*/

- (BOOL)containsDataElement:(IOBluetoothSDPDataElement *)dataElement;

/*!
    @method containsValue:
    @abstract Checks to see if the target data element's value is the same as the value parameter or if it contains
                the value parameter.
    @discussion This method works just like -containsDataElement: except that it is comparing the value objects directly.
    @param cmpValue The value to compare with (and search for).
    @result Returns TRUE if the target's value either matches the given value or if it contains the given value.
*/

- (BOOL)containsValue:(NSObject *)cmpValue;

/*!
    @method isEqual:
    @abstract Compares the target data element with the given object.
    @discussion This method will compare a data element with either another data element or a data element value.
    @param cmpObject The object to compare with.
    @result Returns TRUE if the target data element is the same as the given object or if it's value matches the
            given object.
*/

- (BOOL)isEqual:(id)cmpObject;

- (id)initWithCoder:(NSCoder *)coder;
- (void)encodeWithCoder:(NSCoder *)coder;

@end
