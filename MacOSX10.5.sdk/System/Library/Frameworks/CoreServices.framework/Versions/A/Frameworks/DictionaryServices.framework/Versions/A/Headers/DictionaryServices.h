/*
	DictionaryServices.h
	DictionaryServices framework
     
	Copyright (c) 2007 Apple, Inc. All rights reserved.
*/

#ifndef __DICTIONARYSERVICES__
#define __DICTIONARYSERVICES__

#ifndef __COREFOUNDATION__
#include <CoreFoundation/CoreFoundation.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*!
	@typedef	DCSDictionaryRef
	@abstract	Opaque CF object that represents a dictionary file
*/
typedef const struct __DCSDictionary*	DCSDictionaryRef;

/*!
	@function	DCSGetTermRangeInString
	@abstract	Look for a word or a phrase that contains the specified offset in dictionaries
				activated in Dictionary.app preference
	@param		dictionary
				This parameter is not supported for Leopard. You should always pass NULL.
	@param		textString
				Text that contains the word or phrase to look up
	@param		offset
				Specifies a character offset in textString
	@result		Returns a detected range of word or phrase around the specified offset,
				or (kCFNotFound, 0) is returned if any term is not found in active dictionaries.
				The result range can be used as an input parameter of DCSCopyTextDefinition()
				and HIDictionaryWindowShow() in Carbon framework.
*/
extern CFRange DCSGetTermRangeInString( DCSDictionaryRef dictionary, CFStringRef textString, CFIndex offset );

/*!
	@function	DCSCopyTextDefinition
	@abstract	Copies definition for a specified range of text
	@param		dictionary
				This parameter is not supported for Leopard. You should always pass NULL.
	@param		textString
				Text that contains the word or phrase to look up
	@param		range
				Range of the target word or phrase in textString
	@result		Returns a definition of the specified term in range in plain text
*/
extern CFStringRef DCSCopyTextDefinition( DCSDictionaryRef dictionary, CFStringRef textString, CFRange range );

#ifdef __cplusplus
}
#endif

#endif // __DICTIONARYSERVICES__

