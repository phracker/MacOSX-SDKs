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

+ (instancetype)uuidWithBytes:(const void *)bytes length:(unsigned)length;

/*!
    @method uuidWithData:
    @abstract Creates a new IOBluetoothSDPUUID object from the given NSData.
    @discussion If the length of the NSData is invalid for a UUID, nil is returned.
    @param data The NSData containing the UUID bytes.
    @result Returns the new IOBluetoothSDPUUID object or nil on failure.
*/

+ (instancetype)uuidWithData:(NSData *)data;

/*!
    @method uuid16:
    @abstract Creates a new 16-bit IOBluetoothSDPUUID with the given UUID16
    @param uuid16 A scalar representing a 16-bit UUID
    @result Returns the new IOBluetoothSDPUUID object.
*/

+ (instancetype)uuid16:(BluetoothSDPUUID16)uuid16;

/*!
    @method uuid32:
    @abstract Creates a new 32-bit IOBluetoothSDPUUID with the given UUID32
    @param uuid32 A scalar representing a 32-bit UUID
    @result Returns the new IOBluetoothSDPUUID object.
*/

+ (instancetype)uuid32:(BluetoothSDPUUID32)uuid32;

/*!	@method	withSDPUUIDRef:
	@abstract	Method call to convert an IOBluetoothSDPUUIDRef into an IOBluetoothSDPUUID *.
        @param	sdpUUIDRef IOBluetoothSDPUUIDRef for which an IOBluetoothSDPUUID * is desired.
	@result		Returns the IOBluetoothSDPUUID * for the given IOBluetoothSDPUUIDRef.
*/
+ (instancetype)withSDPUUIDRef:(IOBluetoothSDPUUIDRef)sdpUUIDRef DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
    @method initWithUUID16:
    @abstract Initializes a new 16-bit IOBluetoothSDPUUID with the given UUID16
    @param uuid16 A scalar representing a 16-bit UUID
    @result Returns self.
*/

- (instancetype)initWithUUID16:(BluetoothSDPUUID16)uuid16;

/*!
    @method initWithUUID32:
    @abstract Creates a new 32-bit IOBluetoothSDPUUID with the given UUID32
    @param uuid32 A scalar representing a 32-bit UUID
    @result Returns self.
*/

- (instancetype)initWithUUID32:(BluetoothSDPUUID32)uuid32;

/*!	@method	getSDPUUIDRef
	@abstract	Returns an IOBluetoothSDPUUIDRef representation of the target IOBluetoothSDPUUID object.
	@result		Returns an IOBluetoothSDPUUIDRef representation of the target IOBluetoothSDPUUID object.
*/
- (IOBluetoothSDPUUIDRef)getSDPUUIDRef DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

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

- (instancetype)getUUIDWithLength:(unsigned)newLength;

/*!
    @method isEqualToUUID:
    @abstract Compares the target IOBluetoothSDPUUID object with the given otherUUID object.
    @discussion This method will compare the two UUID values independent of their length.
    @param otherUUID The UUID object to be compared with the target.
    @result Returns true if the UUID values of each object are equal.  This includes the case where the sizes are different
            but the data itself is the same when the Bluetooth UUID base is applied.
*/

- (BOOL)isEqualToUUID:(IOBluetoothSDPUUID *)otherUUID;

- (Class)classForCoder;
- (Class)classForArchiver;
- (Class)classForPortCoder;

@end
