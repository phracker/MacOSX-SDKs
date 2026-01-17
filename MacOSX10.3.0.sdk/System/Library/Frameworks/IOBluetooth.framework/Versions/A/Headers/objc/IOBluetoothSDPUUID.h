/*
    File:		IOBluetoothSDPUUID.h
    Copyright:	© 2002 by Apple Computer, Inc. All rights reserved.
	Writers:	Eric Brown
*/

#import <Foundation/Foundation.h>

#import <IOBluetooth/Bluetooth.h>
#import <IOBluetooth/IOBluetoothUserLib.h>

/*!
    @class IOBluetoothSDPUUID
    @abstract An NSData subclass that represents a UUID as defined in the Bluetooth SDP spec.
    @discussion The IOBluetoothSDPUUID class can represent a UUID of any valid size (16, 32 or 128 bits).
            It provides the ability to compare two UUIDs no matter what their size as well as the ability
            to promote the size of a UUID to a larger one.
*/

@interface IOBluetoothSDPUUID : NSData {
    NSData	*mUUIDData;
    
    void	*_mReserved;
}

/*!
    @method uuidWithBytes:length:
    @abstract Creates a new IOBluetoothSDPUUID object with the given bytes of the given length.
    @discussion If the length is invalid for a UUID, nil is returned.
    @param bytes An array of bytes representing the UUID.
    @param length The length of the array of bytes.
    @result Returns the new IOBluetoothSDPUUID object or nil on failure.
*/

+ (IOBluetoothSDPUUID *)uuidWithBytes:(const void *)bytes length:(unsigned)length;

/*!
    @method uuidWithData:
    @abstract Creates a new IOBluetoothSDPUUID object from the given NSData.
    @discussion If the length of the NSData is invalid for a UUID, nil is returned.
    @param data The NSData containing the UUID bytes.
    @result Returns the new IOBluetoothSDPUUID object or nil on failure.
*/

+ (IOBluetoothSDPUUID *)uuidWithData:(NSData *)data;

/*!
    @method uuid16:
    @abstract Creates a new 16-bit IOBluetoothSDPUUID with the given UUID16
    @param uuid16 A scalar representing a 16-bit UUID
    @result Returns the new IOBluetoothSDPUUID object.
*/

+ (IOBluetoothSDPUUID *)uuid16:(BluetoothSDPUUID16)uuid16;

/*!
    @method uuid32:
    @abstract Creates a new 32-bit IOBluetoothSDPUUID with the given UUID32
    @param uuid32 A scalar representing a 32-bit UUID
    @result Returns the new IOBluetoothSDPUUID object.
*/

+ (IOBluetoothSDPUUID *)uuid32:(BluetoothSDPUUID32)uuid32;

/*!	@method	withSDPUUIDRef:
	@abstract	Method call to convert an IOBluetoothSDPUUIDRef into an IOBluetoothSDPUUID *.
        @param	sdpUUIDRef IOBluetoothSDPUUIDRef for which an IOBluetoothSDPUUID * is desired.
	@result		Returns the IOBluetoothSDPUUID * for the given IOBluetoothSDPUUIDRef.
*/
+ (IOBluetoothSDPUUID *)withSDPUUIDRef:(IOBluetoothSDPUUIDRef)sdpUUIDRef;

/*!
    @method initWithBytes:length:
    @abstract Initializes a new IOBluetoothSDPUUID object with the given bytes of the given length.
    @discussion If the length is invalid for a UUID, nil is returned.
    @param bytes An array of bytes representing the UUID.
    @param length The lenght of the array of bytes.
    @result Returns self on success or nil on failure.
*/

- (id)initWithBytes:(const void *)bytes length:(unsigned)length;

/*!
    @method initWithData:
    @abstract Initializes a new IOBluetoothSDPUUID object with the bytes in the given NSData.
    @discussion If the length of the NSData is invalid for a UUID, nil is returned.
    @param data The NSData containing the UUID bytes.
    @result Returns self on success or nil on failure.
*/

- (id)initWithData:(NSData *)data;

/*!
    @method initWithUUID16:
    @abstract Initializes a new 16-bit IOBluetoothSDPUUID with the given UUID16
    @param uuid16 A scalar representing a 16-bit UUID
    @result Returns self.
*/

- (id)initWithUUID16:(BluetoothSDPUUID16)uuid16;

/*!
    @method initWithUUID32:
    @abstract Creates a new 32-bit IOBluetoothSDPUUID with the given UUID32
    @param uuid32 A scalar representing a 32-bit UUID
    @result Returns self.
*/

- (id)initWithUUID32:(BluetoothSDPUUID32)uuid32;

/*!	@method	getSDPUUIDRef
	@abstract	Returns an IOBluetoothSDPUUIDRef representation of the target IOBluetoothSDPUUID object.
	@result		Returns an IOBluetoothSDPUUIDRef representation of the target IOBluetoothSDPUUID object.
*/
- (IOBluetoothSDPUUIDRef)getSDPUUIDRef;

// NSData primitive methods

/*!
    @method bytes
    @abstract Returns a pointer to the array of UUID bytes.
    @discussion This is one of the required NSData primitive methods.
    @result Returns a pointer to the array of UUID bytes.
*/

- (const void *)bytes;

/*!
    @method length
    @abstract Returns the length (in bytes) of the UUID.
    @discussion This is one of the required NSData primitive methods.
    @result Returns the length (in bytes) of the UUID.
*/

- (unsigned)length;

/*!
    @method getUUIDWithLength:
    @abstract Returns an IOBluetoothSDPUUID object matching the target UUID, but with the given number of bytes.
    @discussion If the target object is the same length as newLength, it returns self.  If newLength is greater
                it creates a new IOBluetoothSDPUUID object with the correct value for the given length.  If
                newLength is smaller, it will attempt to create a new IOBluetoothSDPUUID that is smaller if
                the data matches the Bluetooth UUID base.  This downconversion is currently unimplemented.
    @param newLength The desired length for the UUID. 
    @result Returns an IOBluetoothSDPUUID object with the same data as the target but with the given length if it
            is possible to do so.  Otherwise, nil is returned.
*/

- (IOBluetoothSDPUUID *)getUUIDWithLength:(unsigned)newLength;

/*!
    @method isEqualToData:
    @abstract Compares the target IOBluetoothSDPUUID data with that of the given NSData parameter.
    @discussion This method will compare the bytes of the two objects even if the otherData parameter is
                not an IOBluetoothSDPUUID object.
    @param otherData An NSData object to be compared with the target.
    @result Returns true if the UUID values of each object are equal.  This includes the case where the sizes are different
            but the data itself is the same when the Bluetooth UUID base is applied.
*/

- (BOOL)isEqualToData:(NSData *)otherData;

/*!
    @method isEqualToUUID:
    @abstract Compares the target IOBluetoothSDPUUID object with the given otherUUID object.
    @discussion This method will compare the two UUID values independent of their length.
    @param otherUUID The UUID object to be compared with the target.
    @result Returns true if the UUID values of each object are equal.  This includes the case where the sizes are different
            but the data itself is the same when the Bluetooth UUID base is applied.
*/

- (BOOL)isEqualToUUID:(IOBluetoothSDPUUID *)otherUUID;

- (id)initWithCoder:(NSCoder *)coder;
- (void)encodeWithCoder:(NSCoder *)coder;
- (Class)classForCoder;
- (Class)classForArchiver;
- (Class)classForPortCoder;

@end
