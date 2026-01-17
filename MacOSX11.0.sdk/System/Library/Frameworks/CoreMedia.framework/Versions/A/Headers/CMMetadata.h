/*
    File:  CMMetadata.h
	
	Framework:  CoreMedia
 
    Copyright © 2013-2015 Apple Inc. All rights reserved.
 
*/

#ifndef CMMETADATA_H
#define CMMETADATA_H

/*!
	@header
	@abstract	API for creating and manipulating metadata.
	@discussion	This API covers two services:  Metadata Identifier Services,
				and the Metadata Data Type Registry.
	
				Metadata Identifier Services provide a means of encoding the
				metadata identifying tuple (four byte key namespace and n-byte
				key value) into CFString, and back again.
				
				The Metadata Data Type Registry allows a process to register
				metadata data types that conform to a base data type
				and (optionally) other registered data types.  The registry
				simplifies the process of creating format descriptions for
				non-trivial metadata values, as well as allowing clients to
				indicate how metadata can be interpreted.
*/

#include <CoreMedia/CMBase.h>
#include <CoreFoundation/CoreFoundation.h>
#include <CoreMedia/CMFormatDescription.h>
#include <CoreMedia/CMBlockBuffer.h>

#ifdef __cplusplus
extern "C" {
#endif
    
#pragma pack(push, 4)
	
CF_IMPLICIT_BRIDGING_ENABLED

/*! 
	@group	Errors
*/

/*!
	@enum CMMetadata Identifier Errors
	@discussion The errors returned from the CMMetadata Identifier APIs
	@constant	kCMMetadataIdentifierError_AllocationFailed An allocation failed.
	@constant	kCMMetadataIdentifierError_RequiredParameterMissing NULL or 0 was passed for a required parameter.
	@constant	kCMMetadataIdentifierError_BadKey An invalid key was passed.
	@constant	kCMMetadataIdentifierError_BadKeyLength A key was passed that had an invalid length.
	@constant	kCMMetadataIdentifierError_BadKeyType A bad type was passed for a key.
	@constant	kCMMetadataIdentifierError_BadNumberKey The number passed for a key was not valid (not in the range 0-0xFFFFFFFF).
	@constant	kCMMetadataIdentifierError_BadKeySpace The keyspace passed in was invalid.
	@constant	kCMMetadataIdentifierError_BadIdentifier The identifier passed in was invalid.
	@constant	kCMMetadataIdentifierError_NoKeyValueAvailable A keyvalue was requested for the anonymous keyspace ('anon').
*/
// Range -16300 to -16309
#if COREMEDIA_USE_DERIVED_ENUMS_FOR_CONSTANTS
enum : OSStatus
#else
enum
#endif
{
	kCMMetadataIdentifierError_AllocationFailed				= -16300,
	kCMMetadataIdentifierError_RequiredParameterMissing		= -16301,
	kCMMetadataIdentifierError_BadKey						= -16302,
	kCMMetadataIdentifierError_BadKeyLength					= -16303,
	kCMMetadataIdentifierError_BadKeyType					= -16304,
	kCMMetadataIdentifierError_BadNumberKey					= -16305,
	kCMMetadataIdentifierError_BadKeySpace					= -16306,
	kCMMetadataIdentifierError_BadIdentifier				= -16307,
	kCMMetadataIdentifierError_NoKeyValueAvailable			= -16308,
} API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));

/*!
	@enum CMMetadata DataType Registry Errors
	@discussion The errors returned from the CMMetadata DataType Registry APIs
	@constant	kCMMetadataDataTypeRegistryError_AllocationFailed An allocation failed.
	@constant	kCMMetadataDataTypeRegistryError_RequiredParameterMissing NULL or 0 was passed for a required parameter.
	@constant	kCMMetadataDataTypeRegistryError_BadDataTypeIdentifier Bad datatype identifier.
	@constant	kCMMetadataDataTypeRegistryError_DataTypeAlreadyRegistered Datatype already registered.
	@constant	kCMMetadataDataTypeRegistryError_RequiresConformingBaseType Data type passed in requires a conforming data type that resolves to a base data type.
	@constant	kCMMetadataDataTypeRegistryError_MultipleConformingBaseTypes Data type passed specified more than one base data type.
*/
// Range -16310 to -16319
#if COREMEDIA_USE_DERIVED_ENUMS_FOR_CONSTANTS
enum : OSStatus
#else
enum
#endif
{
	kCMMetadataDataTypeRegistryError_AllocationFailed				= -16310,
	kCMMetadataDataTypeRegistryError_RequiredParameterMissing		= -16311,
	kCMMetadataDataTypeRegistryError_BadDataTypeIdentifier			= -16312,
	kCMMetadataDataTypeRegistryError_DataTypeAlreadyRegistered		= -16313,
	kCMMetadataDataTypeRegistryError_RequiresConformingBaseType		= -16314,
	kCMMetadataDataTypeRegistryError_MultipleConformingBaseTypes	= -16315,
} API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));


/*!
	@group	Metadata Identifier Services
*/

/*!
	@const kCMMetadataKeySpace_QuickTimeUserData
		Metadata keyspace for QuickTime User Data keys.
	@const kCMMetadataKeySpace_ISOUserData
		Metadata keyspace for MPEG-4 User Data keys.
	@const kCMMetadataKeySpace_QuickTimeMetadata
		Metadata keyspace for QuickTime Metadata keys.
	@const kCMMetadataKeySpace_iTunes
		Metadata keyspace for iTunes keys.
	@const kCMMetadataKeySpace_ID3
		Metadata keyspace for ID3 keys.
	@const kCMMetadataKeySpace_Icy
		Metadata keyspace for ShoutCast keys.
	@const kCMMetadataKeySpace_HLSDateRange
		Metadata keyspace for HLS DateRange tags.
*/
CM_ASSUME_NONNULL_BEGIN

CM_EXPORT const CFStringRef kCMMetadataKeySpace_QuickTimeUserData
								API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));
CM_EXPORT const CFStringRef kCMMetadataKeySpace_ISOUserData
								API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));
CM_EXPORT const CFStringRef kCMMetadataKeySpace_QuickTimeMetadata
								API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));
CM_EXPORT const CFStringRef kCMMetadataKeySpace_iTunes
								API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));
CM_EXPORT const CFStringRef kCMMetadataKeySpace_ID3
								API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));
CM_EXPORT const CFStringRef kCMMetadataKeySpace_Icy
								API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));
CM_EXPORT const CFStringRef kCMMetadataKeySpace_HLSDateRange
								API_AVAILABLE(macos(10.11.3), ios(9.3), tvos(9.3), watchos(6.0));

/*!
	@const kCMMetadataIdentifier_QuickTimeMetadataLocation_ISO6709
		Location information in ISO-6709 format.
	@const kCMMetadataIdentifier_QuickTimeMetadataDirection_Facing
		Direction the observer is facing.
*/
CM_EXPORT const CFStringRef kCMMetadataIdentifier_QuickTimeMetadataLocation_ISO6709
								API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));
CM_EXPORT const CFStringRef kCMMetadataIdentifier_QuickTimeMetadataDirection_Facing
								API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));

/*!
	@const kCMMetadataIdentifier_QuickTimeMetadataPreferredAffineTransform
		An affine transform that can be used in place of a track matrix for
		displaying a video track, to better reflect the current orientation
		of a video camera with respect to a scene.  For example, if the camera
		is rotated after a recording has started, the presence of this metadata
		will allow a player to adjust its rendering at the time the rotation occurred.
*/
CM_EXPORT const CFStringRef kCMMetadataIdentifier_QuickTimeMetadataPreferredAffineTransform
								API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));

/*!
	@const kCMMetadataIdentifier_QuickTimeMetadataVideoOrientation
		Video orientation as defined by TIFF/EXIF, which is enumerated by CGImagePropertyOrientation
		(see <ImageIO/CGImageProperties.h>).
*/
CM_EXPORT const CFStringRef kCMMetadataIdentifier_QuickTimeMetadataVideoOrientation
								API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(6.0));
	
/*!
	@const kCMMetadataIdentifier_QuickTimeMetadataLivePhotoStillImageTransform
		A perspective transform that can be used to adjust a Live Photo still image to match the Live Photo movie.
		Expected data type is kCMMetadataBaseDataType_PerspectiveTransformF64.
*/
CM_EXPORT const CFStringRef kCMMetadataIdentifier_QuickTimeMetadataLivePhotoStillImageTransform
								API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

/*!
	@const kCMMetadataIdentifier_QuickTimeMetadataLivePhotoStillImageTransformReferenceDimensions
		The dimensions of the image used to generate kCMMetadataIdentifier_QuickTimeMetadataLivePhotoStillImageTransform.
		Expected data type is kCMMetadataBaseDataType_DimensionsF32.
*/
CM_EXPORT const CFStringRef kCMMetadataIdentifier_QuickTimeMetadataLivePhotoStillImageTransformReferenceDimensions
								API_AVAILABLE(macos(10.15.1), ios(13.2), tvos(13.2), watchos(6.1));

	
CM_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

/*! 
	@functiongroup	Metadata Identifier services
*/

/*!
	@function	CMMetadataCreateIdentifierForKeyAndKeySpace
	@abstract	Creates a URL-like string identifier that represents a key/keyspace tuple.
    @discussion Metadata entities are identified by a key whose interpretation
                is defined by its keyspace.  When writing metadata to a QuickTime
                Movie, this tuple is part of the track's format description.
				
                The following constants make up the current list of supported keyspaces,
				which are documented elsewhere in this file:
<ul>				kCMMetadataKeySpace_QuickTimeUserData
<li>				kCMMetadataKeySpace_ISOUserData
<li>				kCMMetadataKeySpace_iTunes
<li>				kCMMetadataKeySpace_ID3
<li>				kCMMetadataKeySpace_QuickTimeMetadata
<li>				kCMMetadataKeySpace_Icy
</ul>
				Some keyspaces use OSTypes (a.k.a. FourCharCodes) to define their
				keys, and as such their keys are four bytes in length. The keyspaces
				that fall into this category are: kCMMetadataKeySpace_QuickTimeUserData,
				kCMMetadataKeySpace_ISOUserData, kCMMetadataKeySpace_iTunes, and
				kCMMetadataKeySpace_ID3.
				
				The keyspace kCMMetadataKeySpace_QuickTimeMetadata defines its
				key values to be expressed as reverse-DNS strings, which allows
				third parties to define their own keys in a well established way
				that avoids collisions.
				
				As a matter of convenience, known keyspaces allow for a key
				to be passed in using a variety of CFTypes.  Note that what
				is returned by CMMetadataCreateKeyFromIdentifier depends upon the
				keyspace, and may be a different CFType than what is passed
				to this routine (see the discussion below for what CFTypes are
				returned for known keyspaces).  To get a key represented as
				CFData, call CMMetadataCreateKeyFromIdentifierAsCFData.
				
				For OSType keyspaces, a key may be passed as a CFNumber,
				a CFString, or a CFData. A key passed as a CFNumber will have
				its value retrieved as kCFNumberSInt32Type comprising the four
				bytes of the key’s numeric value in big-endian byte order.
				A key passed as a CFString must be a valid ASCII string of four
				characters. A key passed as a CFData must be comprised of the
				four bytes of the key’s numeric value in big-endian byte order.
				
				All other keyspaces allow the key to be passed as a CFString
				or CFData. In both cases, the key will be interpreted as an
				ASCII string for the purposes of identifier encoding.
*/
CM_EXPORT
OSStatus CMMetadataCreateIdentifierForKeyAndKeySpace(
	CFAllocatorRef CM_NULLABLE allocator,					/*! @param allocator
																Allocator to use for creating the identifier. */
	CFTypeRef CM_NONNULL key,								/*! @param key
																Key data;  may be CFString, CFNumber, or CFData. */
	CFStringRef CM_NONNULL keySpace,						/*! @param keySpace
																Keyspace;  must be string of one to four printable
																ASCII characters. */
	CM_RETURNS_RETAINED_PARAMETER CFStringRef CM_NULLABLE * CM_NONNULL identifierOut)		/*! @param identifierOut
																The created identifier. */
							API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMMetadataCreateKeyFromIdentifier
    @abstract   Creates a copy of the key encoded in the identifier as a CFType.
    @discussion	The returned CFType is based on the keyspace encoded in the identifier.
    			
    			For OSType keyspaces, the key will be returned as a CFNumber,
				where a big endian interpretation of its kCFNumberSInt32Type value
				represents the four bytes of the key's numeric value.
    			
    			For the keyspaces kCMMetadataKeySpace_QuickTimeMetadata and
				kCMMetadataKeySpace_Icy, the key will be returned as a CFString.
				
				All other keyspaces will have the function return the key as a CFData.
*/
CM_EXPORT
OSStatus CMMetadataCreateKeyFromIdentifier(
	CFAllocatorRef CM_NULLABLE allocator,		/*! @param allocator
													Allocator to use for creating the key. */
	CFStringRef CM_NONNULL identifier,			/*! @param identifier
										Identifier being inspected. */
	CM_RETURNS_RETAINED_PARAMETER CFTypeRef CM_NULLABLE * CM_NONNULL keyOut)				/*! @param keyOut
										The key data that was used create the identifier. */
							API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMMetadataCreateKeyFromIdentifierAsCFData
    @abstract   Creates a copy of the key value that was encoded in the identifier as CFData.
				The bytes in the CFData correpsond to how they are serialized in the file.
*/
CM_EXPORT
OSStatus CMMetadataCreateKeyFromIdentifierAsCFData(
	CFAllocatorRef CM_NULLABLE allocator,		/*! @param allocator
													Allocator to use for creating the key. */
	CFStringRef CM_NONNULL identifier,			/*! @param identifier
													Identifier being inspected. */
	CM_RETURNS_RETAINED_PARAMETER CFDataRef CM_NULLABLE * CM_NONNULL keyOut)	/*! @param keyOut
													The key data that was used create the identifier, as a CFData. */
							API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMMetadataCreateKeySpaceFromIdentifier
    @abstract   Creates a copy of the key value that was encoded in the identifier as CFData.
*/
CM_EXPORT
OSStatus CMMetadataCreateKeySpaceFromIdentifier(
	CFAllocatorRef CM_NULLABLE allocator,				/*! @param allocator
															Allocator to use for creating the keyspace. */
	CFStringRef CM_NONNULL identifier,					/*! @param identifier
															Identifier being inspected. */
	CM_RETURNS_RETAINED_PARAMETER CFStringRef CM_NULLABLE * CM_NONNULL keySpaceOut)	/*! @param keySpaceOut
															The key space that was used to create the identifier. */
							API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));
	
CF_IMPLICIT_BRIDGING_ENABLED

/*!
	@group	Metadata Datatype Registry
*/

/*!
	@const kCMMetadataBaseDataType_RawData
		A sequence of bytes whose interpretation based upon an agreement between
		the reader and the writer.
	@const kCMMetadataBaseDataType_UTF8
		UTF-8 string.
	@const kCMMetadataBaseDataType_UTF16
		UTF-16 string.
	@const kCMMetadataBaseDataType_GIF
		GIF image.
	@const kCMMetadataBaseDataType_JPEG
		JPEG image.
	@const kCMMetadataBaseDataType_PNG
		PNG image.
	@const kCMMetadataBaseDataType_BMP
		BMP image.
	@const kCMMetadataBaseDataType_Float32
		32-bit big endian floating point number.
	@const kCMMetadataBaseDataType_Float64
		64-bit big endian floating point number.
	@const kCMMetadataBaseDataType_SInt8
		8-bit signed integer.
	@const kCMMetadataBaseDataType_SInt16
		16-bit big endian signed integer.
	@const kCMMetadataBaseDataType_SInt32
		32-bit big endian signed integer.
	@const kCMMetadataBaseDataType_SInt64
		64-bit big endian signed integer.
	@const kCMMetadataBaseDataType_UInt8
		8-bit unsigned integer.
	@const kCMMetadataBaseDataType_UInt16
		16-bit big endian unsigned integer.
	@const kCMMetadataBaseDataType_UInt32
		32-bit big endian unsigned integer.
	@const kCMMetadataBaseDataType_UInt64
		64-bit big endian unsigned integer.
	@const kCMMetadataBaseDataType_PointF32
		Consists of two 32-bit big endian floating point values, the x and y values, respectively.
	@const kCMMetadataBaseDataType_DimensionsF32
		Consists of a 32-bit big endian floating point x value followed by a 32-bit floating point y value.
	@const kCMMetadataBaseDataType_RectF32
		Consists of four 32-bit big endian floating point values, the origin's x, origin's y, width and height values, respectively.
		May also be interpreted as a 32-bit floating point origin followed by a 32-bit floating point dimension.
	@const kCMMetadataDataType_AffineTransformF64
		A 3x3 matrix of 64-bit big endian floating point numbers stored in row-major order that specify an affine transform.
	@const kCMMetadataBaseDataType_PolygonF32
		Three or more pairs of 32-bit floating point numbers (x and y values) that define the verticies of a polygon.
	@const kCMMetadataBaseDataType_PolylineF32
		Two or more pairs of 32-bit floating point numbers (x and y values) that define a multi-segmented line.
	@const kCMMetadataBaseDataType_JSON
		UTF-8 encoded JSON data.
	@const kCMMetadataBaseDataType_PerspectiveTransformF64
		A 3x3 matrix of 64-bit big endian floating point numbers stored in row-major order that specify a perspective transform.
*/
CM_ASSUME_NONNULL_BEGIN

CM_EXPORT const CFStringRef kCMMetadataBaseDataType_RawData
								API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));
CM_EXPORT const CFStringRef kCMMetadataBaseDataType_UTF8
								API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));
CM_EXPORT const CFStringRef kCMMetadataBaseDataType_UTF16
								API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));
CM_EXPORT const CFStringRef kCMMetadataBaseDataType_GIF
								API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));
CM_EXPORT const CFStringRef kCMMetadataBaseDataType_JPEG
								API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));
CM_EXPORT const CFStringRef kCMMetadataBaseDataType_PNG
								API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));
CM_EXPORT const CFStringRef kCMMetadataBaseDataType_BMP
								API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));
CM_EXPORT const CFStringRef kCMMetadataBaseDataType_Float32
								API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));
CM_EXPORT const CFStringRef kCMMetadataBaseDataType_Float64
								API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));
CM_EXPORT const CFStringRef kCMMetadataBaseDataType_SInt8
								API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));
CM_EXPORT const CFStringRef kCMMetadataBaseDataType_SInt16
								API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));
CM_EXPORT const CFStringRef kCMMetadataBaseDataType_SInt32
								API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));
CM_EXPORT const CFStringRef kCMMetadataBaseDataType_SInt64
								API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));
CM_EXPORT const CFStringRef kCMMetadataBaseDataType_UInt8
								API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));
CM_EXPORT const CFStringRef kCMMetadataBaseDataType_UInt16
								API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));
CM_EXPORT const CFStringRef kCMMetadataBaseDataType_UInt32
								API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));
CM_EXPORT const CFStringRef kCMMetadataBaseDataType_UInt64
								API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));
CM_EXPORT const CFStringRef kCMMetadataBaseDataType_PointF32
								API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));
CM_EXPORT const CFStringRef kCMMetadataBaseDataType_DimensionsF32
								API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));
CM_EXPORT const CFStringRef kCMMetadataBaseDataType_RectF32
								API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));
CM_EXPORT const CFStringRef kCMMetadataBaseDataType_AffineTransformF64
								API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));
CM_EXPORT const CFStringRef kCMMetadataBaseDataType_PolygonF32
								API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(6.0));
CM_EXPORT const CFStringRef kCMMetadataBaseDataType_PolylineF32
								API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(6.0));
CM_EXPORT const CFStringRef kCMMetadataBaseDataType_JSON
								API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(6.0));
CM_EXPORT const CFStringRef kCMMetadataBaseDataType_PerspectiveTransformF64
								API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

/*!
	@const kCMMetadataDataType_Location_ISO6709
		A string supplying location information in ISO-6709 format.  Conforms to
		kCMMetadataBaseDataType_UTF8.
	@const kCMMetadataDataType_Direction
		A string supplying degrees offset from magnetic North.  Conforms to
		kCMMetadataBaseDataType_UTF8.
*/
CM_EXPORT const CFStringRef kCMMetadataDataType_QuickTimeMetadataLocation_ISO6709
								API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));
CM_EXPORT const CFStringRef kCMMetadataDataType_QuickTimeMetadataDirection
								API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));

CM_ASSUME_NONNULL_END

/*! 
	@functiongroup	Metadata DataType Registry
*/

/*!
	@function	CMMetadataDataTypeRegistryRegisterDataType
	@abstract	Register a data type with the data type registry.
	@discussion	This routine is called by clients to register a data type with
				the data type registry.  The list of conforming data type identifiers
				must include a base data type.  If the data type has already
				been registered, then it is not considered an error to re-register it
				as long as the list of conforming data type identifiers has the same
				entries as the original;  otherwise an error will be returned.
*/
CM_EXPORT
OSStatus CMMetadataDataTypeRegistryRegisterDataType(
	CFStringRef CM_NONNULL dataType,						/*! @param dataType
																Identifier of data type being registered. */
	CFStringRef CM_NONNULL description,						/*! @param description
																Human readable description of data type being registered
																(for aiding debugging operations) */
	CFArrayRef CM_NONNULL conformingDataTypes)				/*! @param conformingDataTypes
																Data types that this data type conforms to. */
							API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMMetadataDataTypeRegistryDataTypeIsRegistered
	@abstract	Tests a data type identifier to see if it has been registered.
*/
CM_EXPORT
Boolean CMMetadataDataTypeRegistryDataTypeIsRegistered(
	CFStringRef CM_NONNULL dataType)						/*! @param dataType
																Identifier of data type being checked. */
							API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMMetadataDataTypeRegistryGetDataTypeDescription
	@abstract	Returns the data type's description (if any was provided when it was registered).
*/
CM_EXPORT
CFStringRef CM_NONNULL CMMetadataDataTypeRegistryGetDataTypeDescription(
	CFStringRef CM_NONNULL dataType)						/*! @param dataType
																Identifier of data type being interrogated. */
							API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMMetadataDataTypeRegistryGetConformingDataTypes
	@abstract	Returns the data type's conforming data types (if any were
				provided when it was registered).
	@returns	List of conforming data types registered for the given data type.
				NULL is returned if the data type has not been registered.
*/
CM_EXPORT
CFArrayRef CM_NONNULL CMMetadataDataTypeRegistryGetConformingDataTypes(
	CFStringRef CM_NONNULL dataType)						/*! @param dataType
																Identifier of data type being interrogated. */
							API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMMetadataDataTypeRegistryDataTypeConformsToDataType
	@abstract	Checks to see if a data type conforms to another data type.
	@discussion	A given data type will conform to a second data type if any of
				the following are true:
<ul>				1. The data type identifiers are the same.
<li>				2. The first data type identifier's conformance list contains the second data type identifier.
<li>				3. A recursive search of the conforming data types for each element in the first
<li>				   data type's conformance list yields the second data type identifer.
</ul>
	@returns	True if the first data type conforms to the second data type.
*/
CM_EXPORT
Boolean CMMetadataDataTypeRegistryDataTypeConformsToDataType(
	CFStringRef CM_NONNULL dataType,						/*! @param dataType
																Identifier of data type being interrogated. */
	CFStringRef CM_NONNULL conformsToDataType)				/*! @param conformsToDataType
																Identifier of data type being checked as as
																conforming data type. */
							API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMMetadataDataTypeRegistryGetBaseDataTypes
	@abstract	Returns an array of base data type identifiers.
	@discussion	There are a set of base data types that seed the data type
				registry.  All valid data types will have their conformance search
				end with a base data type.
*/
CM_EXPORT
CFArrayRef CM_NULLABLE CMMetadataDataTypeRegistryGetBaseDataTypes(void)
							API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMMetadataDataTypeRegistryDataTypeIsBaseDataType
	@abstract	Tests a data type identifier to see if it represents a base data type.
	@discussion	This is simply a convenience method to test to see if a given
				data type identifier is in the array returned by
				CMMetadataDataTypeRegistryGetBaseDataTypes.
*/
CM_EXPORT
Boolean CMMetadataDataTypeRegistryDataTypeIsBaseDataType(
	CFStringRef CM_NONNULL dataType)						/*! @param dataType
																Identifier of data type being checked. */
							API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMMetadataDataTypeRegistryGetBaseDataTypeForConformingDataType
	@abstract	Returns the base data type identifier that the given data type
				conforms to.
	@discussion	There are a set of base data types that seed the data type
				registry.  All valid data types will have their conformance search
				end with a base data type.
*/
CM_EXPORT
CFStringRef CM_NONNULL CMMetadataDataTypeRegistryGetBaseDataTypeForConformingDataType(
	CFStringRef CM_NONNULL dataType)								/*! @param dataType
																		Identifier of data type being interrogated. */
							API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(6.0));
	
CF_IMPLICIT_BRIDGING_DISABLED

#pragma pack(pop)
    
#ifdef __cplusplus
}
#endif
	
#endif // CMMETADATA_H
