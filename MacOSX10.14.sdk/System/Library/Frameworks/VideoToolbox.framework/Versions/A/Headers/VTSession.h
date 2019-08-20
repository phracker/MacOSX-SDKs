/*
	File:  VTSession.h
	
	Framework:  VideoToolbox
 
    Copyright 2006-2013 Apple Inc. All rights reserved.
  
	Client APIs common to all Video Toolbox session types.
*/

#ifndef VTSESSION_H
#define VTSESSION_H

#include <CoreMedia/CMBase.h>
#include <VideoToolbox/VTBase.h>

#include <CoreFoundation/CoreFoundation.h>
#include <VideoToolbox/VTErrors.h>

#if defined(__cplusplus)
extern "C"
{
#endif
    
#pragma pack(push, 4)

/*!
	@typedef	VTSessionRef
	@abstract	A reference to either a Video Toolbox Decompression Session, 
				Compression Session or Pixel Transfer Session.
 */

typedef CM_BRIDGED_TYPE(id) CFTypeRef  VTSessionRef;

/*!
	@function	VTSessionCopySupportedPropertyDictionary
	@abstract	Returns a dictionary enumerating all the supported properties of a video toolbox session.  
	@discussion	
		The keys of the returned dictionary are the supported property keys.
		The values are themselves dictionaries, each containing the following optional fields:
		<OL>
		<LI> the type of value, (kVTPropertyTypeKey)
		<LI> the read/write status of the property (kVTPropertyReadWriteStatusKey),
		<LI> whether the property is suitable for serialization (kVTPropertyShouldBeSerializedKey),
		<LI> a range or list of the supported values, if appropriate, and
		<LI> developer-level documentation for the property (kVTPropertyDocumentationKey).
		</OL>
		The caller must release the returned dictionary.
*/

VT_EXPORT OSStatus 
VTSessionCopySupportedPropertyDictionary(
  CM_NONNULL VTSessionRef					session,
  CM_RETURNS_RETAINED_PARAMETER CM_NULLABLE CFDictionaryRef * CM_NONNULL supportedPropertyDictionaryOut ) API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2));

CF_IMPLICIT_BRIDGING_ENABLED

CM_ASSUME_NONNULL_BEGIN
	
VT_EXPORT const CFStringRef kVTPropertyTypeKey API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2)); // value is CFStringRef, one of the following:
	VT_EXPORT const CFStringRef kVTPropertyType_Enumeration API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2)); // value is one of a list of CFStrings
	VT_EXPORT const CFStringRef kVTPropertyType_Boolean API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2)); // value is a CFBoolean
	VT_EXPORT const CFStringRef kVTPropertyType_Number API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2)); // value is a CFNumber
VT_EXPORT const CFStringRef kVTPropertyReadWriteStatusKey API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2));
	VT_EXPORT const CFStringRef kVTPropertyReadWriteStatus_ReadOnly API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2));
	VT_EXPORT const CFStringRef kVTPropertyReadWriteStatus_ReadWrite API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2));
VT_EXPORT const CFStringRef kVTPropertyShouldBeSerializedKey API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2)); // CFBoolean, false by default
VT_EXPORT const CFStringRef kVTPropertySupportedValueMinimumKey API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2)); // CFNumber
VT_EXPORT const CFStringRef kVTPropertySupportedValueMaximumKey API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2)); // CFNumber
VT_EXPORT const CFStringRef kVTPropertySupportedValueListKey API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2)); // CFArray of appropriate values
VT_EXPORT const CFStringRef kVTPropertyDocumentationKey API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2)); // a CFString for developer eyes only

	
CM_ASSUME_NONNULL_END

/*!
	@function	VTSessionSetProperty
	@abstract	Sets a property on a video toolbox session.
	@discussion
		Setting a property value to NULL restores the default value.
*/
VT_EXPORT OSStatus 
VTSessionSetProperty(
  CM_NONNULL VTSessionRef       session,
  CM_NONNULL CFStringRef        propertyKey,
  CM_NULLABLE CFTypeRef         propertyValue ) API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2));
	
CF_IMPLICIT_BRIDGING_DISABLED

/*!
	@function	VTSessionCopyProperty
	@abstract	Retrieves a property on a video toolbox session.  
	@discussion	
		The caller must release the retrieved property value.
		<BR>
		Note: for most types of property, the returned values should be considered immutable.
		In particular, for CFPropertyList types, sharing of mutable property value 
		objects between the client, session and codec should be avoided.
		However, some properties will be used for exchanging service objects that are inherently 
		mutable (eg, CVPixelBufferPool).
	@param	propertyKey
		The key for the property to retrieve.
	@param	allocator
		An allocator suitable for use when copying property values.
	@param propertyValueOut
		Points to a variable to receive the property value, which must be a CF-registered type --
		the caller may call CFGetTypeID() on it to identify which specific type.
		The caller must release the this property value.
	@result
		noErr if successful; kVTPropertyNotSupportedErr for unrecognized or unsupported properties.
*/
VT_EXPORT OSStatus 
VTSessionCopyProperty(
  CM_NONNULL VTSessionRef		session,
  CM_NONNULL CFStringRef		propertyKey,
  CM_NULLABLE CFAllocatorRef	allocator,
  void * CM_NULLABLE			propertyValueOut ) API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2));

CF_IMPLICIT_BRIDGING_ENABLED
/*!
	@function	VTSessionSetProperties
	@abstract	Sets multiple properties at once.
	@discussion
		Sets the properties specified by keys in propertyDictionary to the corresponding values.
*/
VT_EXPORT OSStatus 
VTSessionSetProperties(
  CM_NONNULL VTSessionRef		session,
  CM_NONNULL CFDictionaryRef	propertyDictionary ) API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2));
	
CF_IMPLICIT_BRIDGING_DISABLED

/*!
	@function	VTSessionCopySerializableProperties
	@abstract	Retrieves the set of serializable property keys and their current values.
	@discussion	
		The serializable properties are those which can be saved and applied to a different session.
		The caller must release the returned dictionary.
*/
VT_EXPORT OSStatus
VTSessionCopySerializableProperties(
  CM_NONNULL VTSessionRef					session,
  CM_NULLABLE CFAllocatorRef				allocator,
  CM_RETURNS_RETAINED_PARAMETER CM_NULLABLE CFDictionaryRef * CM_NONNULL	dictionaryOut ) API_AVAILABLE(macosx(10.8), ios(8.0), tvos(10.2));


#pragma pack(pop)
    
#if defined(__cplusplus)
}
#endif

#endif // VTSESSION_H
