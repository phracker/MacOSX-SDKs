
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <sys/errno.h>
#include <unistd.h>

#include <IOBluetooth/Bluetooth.h>
#include <IOKit/IOReturn.h>
#include <IOBluetooth/IOBluetoothUserLib.h>


#ifdef	__cplusplus
	extern "C" {
#endif

#ifdef __OBJC__

#pragma mark === String Functions === 

//---------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothNSStringToDeviceAddress
	@abstract	Convenience routine to take an NSString and turn it into a BluetoothDeviceAddress structure.
	@param		inNameString		Ptr to an NSString that contains the data to turn into the device address.
	@param		outDeviceAddress	Ptr to an address structure that will be returned.
	@result		Returns success (0) or failure code.
	@discussion	Pass in most types of strings, such as "001122334455" or "00-11-22-33-44-55" and the conversion should be successful. Also, you should have 2 characters per byte for the conversion to work properly.
*/

extern	IOReturn	IOBluetoothNSStringToDeviceAddress( NSString * inNameString, BluetoothDeviceAddress * outDeviceAddress );

//---------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothNSStringFromDeviceAddress
	@abstract	Convenience routine to take a device address structure and create an NSString.
	@param		deviceAddress		A valid bluetooth device structure.
	@result		Returns the created address string.
	@discussion	The resultant string will be in this format: "00-11-22-33-44-55"
*/

extern	NSString *	IOBluetoothNSStringFromDeviceAddress( const BluetoothDeviceAddress *deviceAddress );

#pragma mark -
#pragma mark === File Utilities ===

//---------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothIsFileAppleDesignatedPIMData
	@abstract	Apple designated PIM data is classified as: .vcard, .vcal, .vcf, .vnote, .vmsg, .vcs
	@param		inFileName		Name of file - should include extension!
	@result		Yes or no, is it Apple-designated PIM data?
	@discussion	Not much to talk about.
*/

extern	Boolean		IOBluetoothIsFileAppleDesignatedPIMData( NSString* inFileName );

//---------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothGetUniqueFileNameAndPath
	@abstract	
	@param		inName		Name of file that needs unique name in the specified path.
	@param		inPath		Path you are trying to put file into.
	@result		String with a unique name appended on it for the provided path.
	@discussion		When passed a VALID filename and a VALID path, this routine will return you a the path with the name
					appended onto it. If it already exist, it will insert a #1, #2, etc. Example:
					If you pass &#64"TestFile.txt" and &#64"~/Documents", you will get &#64"~Documents/TestFile.txt".
					If one already exists, you will be returned: &#64"~Documents/TestFile #1.txt".
*/

extern	NSString*	IOBluetoothGetUniqueFileNameAndPath( NSString* inName, NSString* inPath );

#else

// C Versions of the above API.

extern	IOReturn	IOBluetoothCFStringToDeviceAddress( CFStringRef inNameString, BluetoothDeviceAddress * outDeviceAddress );
extern	CFStringRef	IOBluetoothCFStringFromDeviceAddress( const BluetoothDeviceAddress *deviceAddress );
extern	Boolean		IOBluetoothIsFileAppleDesignatedPIMDataAtCFStringPath( CFStringRef inFileName );
extern	CFStringRef	IOBluetoothGetUniqueFileNameAndWithCFStringPath( CFStringRef inName, CFStringRef inPath );

#endif /* __OBJC__ */

#pragma mark -
#pragma mark === Data Handling Functions === 

//---------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothPackData
	@abstract	Packs a variable amount of parameters into a buffer according to a printf-style format string.
	@param		ioBuffer	Ptr to buffer to receive packed data.
	@param		inFormat	printf-style format string controlling how the data is packed.
	@param		varArg		Variable number parameters controlled by the printf-style format string (only PackData).
	@param		inArgs		Variable argument list containing data controlled by format string (only PackDataList).
	@result		Number of bytes packed or -1 if an error occurred.
	@discussion	
	Supported format characters:
	<pre>
		'b' 1 byte of data ('b'yte)
		'h' 2 bytes of data ('h'alf-word)
		'H' 2 bytes of data ('h'alf-word) to byte reverse.
		't' 3 bytes of data ('t'riple byte, least significant 24-bits).
		'T' 3 bytes of data ('t'riple byte, least significant 24-bits) to byte reverse.
		'w' 4 bytes of data ('w'ord).
		'W' 4 bytes of data ('w'ord) to byte reverse.
		'1'	Ptr to 1 byte of data.
		'2' Ptr to 2 bytes of data.
		'&#64'	(shift-2) Ptr to 2 bytes of data to byte reverse.
		'3' Ptr to 3 bytes of data.
		'#'	(shift-3) Ptr to 3 bytes of data to byte reverse.
		'4' Ptr to 4 bytes of data.
		'$'	(shift-4) Ptr to 4 bytes of data to byte reverse.
		'5' Ptr to 5 bytes of data.
		'%'	(shift-5) Ptr to 5 bytes of data to byte reverse.
		'6' Ptr to 6 bytes of data.
		'^'	(shift-6) Ptr to 6 bytes of data to byte reverse.
		'7' Ptr to 6 bytes of data.
		'&'	(shift-7) Ptr to 7 bytes of data to byte reverse.
		'8' Ptr to 6 bytes of data.
		'*'	(shift-8) Ptr to 8 bytes of data to byte reverse.
		'9' Ptr to 6 bytes of data.
		'('	(shift-9) Ptr to 9 bytes of data to byte reverse.
		'n' Ptr to n bytes of data (first param is size, second is ptr).
		'N' Ptr to n bytes of data to byte reverse (first param is size, second is ptr).
		's' Ptr to C-string (includes null terminator)
		'p' Ptr to Pascal-string (includes length byte).
	</pre>
	Example usage:
	<pre>
		bytesPacked = PackData( buffer, "bts", 'U', 'XYZ', "This is a C-style string" );
	</pre>
	<b>
		<i>
			Warning:
		</i>
	</b>
	<i>
		Raw values packed with 'b', 'h', 't', and 'w' have their bytes packed into the buffer from left to right
		even on little-endian systems. For example, the value 0x12345678 would be sent out as 0x12 0x34 0x56 0x78.
		This needs to be taken into consideration if the value is expected to be in little-endian format in the 
		buffer. This case requires you byte swap the value on all systems before sending it to this routine.
	</i>
*/

int32_t		IOBluetoothPackData( void *ioBuffer, const char *inFormat, ... );
int32_t		IOBluetoothPackDataList( void *ioBuffer, const char *inFormat, va_list inArgs );

//---------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothUnpackData
	@abstract	Unpacks a variable amount of data from a buffer into a variable number of parameters according to a 
				printf-style format string.
	@param		inBufferSize	Size of buffer to unpack data from.
	@param		inBuffer		Ptr to buffer to unpack data from.
	@param		inFormat		printf-style format string controlling how the data is unpacked.
	@param		varArg			Variable number parameters to receive data, controlled by the format string (only UnpackData).
	@param		inArgs			Variable argument list containing data controlled by format string (only UnpackDataList).
	@result		Number of bytes unpacked or -1 if an error occurred.
	@discussion	
	Supported format characters:
	<pre>
		'b' Ptr to receive 1 byte of data ('b'yte).
		'h' Ptr to receive 2 bytes of data ('h'alf-word).
		'H' Ptr to receive 2 bytes of byte-reversed data ('h'alf-word).
		't' Ptr to receive 3 bytes of data ('t'riple byte, least significant 24-bits).
		'T' Ptr to receive 3 bytes of byte-reversed data ('t'riple byte, least significant 24-bits).
		'w' Ptr to receive 4 bytes of data ('w'ord).
		'W' Ptr to receive 4 bytes of byte-reversed data ('w'ord).
		'1' Ptr to receive 1 byte of data.
		'2' Ptr to receive 2 bytes of data.
		'&#64'	(shift-2) Ptr to 2 bytes of data, byte reversed.
		'3' Ptr to receive 3 bytes of data.
		'#'	(shift-3) Ptr to receive 3 bytes of data, byte reversed.
		'4' Ptr to receive 4 bytes of data.
		'$'	(shift-4) Ptr to receive 4 bytes of data, byte reversed.
		'5' Ptr to receive 5 bytes of data.
		'%'	(shift-5) Ptr to receive 5 bytes of data, byte reversed.
		'6' Ptr to receive 6 bytes of data.
		'^'	(shift-6) Ptr to receive 6 bytes of data, byte reversed.
		'7' Ptr to receive 7 bytes of data.
		'&'	(shift-7) Ptr to receive 7 bytes of data, byte reversed.
		'8' Ptr to receive 8 bytes of data.
		'*'	(shift-8) Ptr to receive 8 bytes of data, byte reversed.
		'9' Ptr to receive 9 bytes of data.
		'('	(shift-9) Ptr to receive 9 bytes of data, byte reversed.
		'n' Ptr to receive n bytes of data (first param is size, second is ptr to receive data).
		'N' Ptr to receive n bytes of data to byte reverse (first param is size, second is ptr to receive data).
		's' Ptr to receive C-string (first param is max size, second is ptr to receive data).
		'p' Ptr to receive Pascal-string (first param is max size including length-byte, second is ptr to receive data).
	</pre>
	Example usage:
	<pre>
		bytesUnpacked = UnpackData( 100, buffer, "bwnsp", &myByte1, &myWord, 50, buffer1, 128, buffer2, 255, pString );
	</pre>
*/

int32_t		IOBluetoothUnpackData( ByteCount inBufferSize, const void *inBuffer, const char *inFormat, ... );
int32_t		IOBluetoothUnpackDataList( ByteCount inBufferSize, const void *inBuffer, const char *inFormat, va_list inArgs );

#pragma mark -
#pragma mark === Registry Stuff ===

// $$$WARNING$$$ These really should be private, so please don't use them - they are likely to change.

int IOBluetoothNumberOfAvailableHIDDevices() AVAILABLE_BLUETOOTH_VERSION_1_3_AND_LATER;
int IOBluetoothNumberOfPointingHIDDevices() AVAILABLE_BLUETOOTH_VERSION_1_3_AND_LATER;
int IOBluetoothNumberOfKeyboardHIDDevices() AVAILABLE_BLUETOOTH_VERSION_1_3_AND_LATER;
int IOBluetoothNumberOfTabletHIDDevices() AVAILABLE_BLUETOOTH_VERSION_1_3_AND_LATER;
int IOBluetoothFindNumberOfRegistryEntriesOfClassName( const char *deviceType ) AVAILABLE_BLUETOOTH_VERSION_1_3_AND_LATER;


#ifdef	__cplusplus
	}
#endif
