/*
 * File: IndexedSearch.h
 *
 * Copyright: 2010 by Apple Inc. All rights reserved.
 *
 */

/*!
	@header		IndexedSearch.h
	@abstract	Specifies the modern interfaces for searching and retrieving data.
				Supposed to be used by any client need to lookup large dictionaries
				e.g. Dictionary Services, Input Methods, etc.
*/

#ifndef __INDEXEDSEARCH__
#define __INDEXEDSEARCH__

#ifndef __COREFOUNDATION__
#include <CoreFoundation/CoreFoundation.h>
#endif

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 ===============================================================================
	Property names
 ===============================================================================
*/
extern const CFStringRef kIDXPropertyVersion;
extern const CFStringRef kIDXPropertyIndexList;

extern const CFStringRef kIDXPropertyIndexName;
extern const CFStringRef kIDXPropertyIndexPath;
extern const CFStringRef kIDXPropertyIndexAccessMethod;
extern const CFStringRef kIDXPropertyIndexKeyMatchingMethods;
extern const CFStringRef kIDXPropertyIndexDataSizeLength;
extern const CFStringRef kIDXPropertyIndexWritable;
extern const CFStringRef kIDXPropertyIndexSupportDataID;
extern const CFStringRef kIDXPropertyIndexBigEndian;
extern const CFStringRef kIDXPropertyDataFields;

extern const CFStringRef kIDXPropertyExternalFields;
extern const CFStringRef kIDXPropertyFixedFields;
extern const CFStringRef kIDXPropertyVariableFields;
extern const CFStringRef kIDXPropertyDataFieldName;
extern const CFStringRef kIDXPropertyDataSize;
extern const CFStringRef kIDXPropertyDataSizeLength;

/*
 ===============================================================================
	Search methods
 ===============================================================================
*/
extern const CFStringRef kIDXSearchExactMatch;
extern const CFStringRef kIDXSearchPrefixMatch;
extern const CFStringRef kIDXSearchCommonPrefixMatch;
extern const CFStringRef kIDXSearchWildcardMatch;
extern const CFStringRef kIDXSearchAllMatch;
extern const CFStringRef kIDXSearchExactMatchVoiceAmbi;
extern const CFStringRef kIDXSearchExactMatchSmallAmbi;
extern const CFStringRef kIDXSearchExactMatchVoiceAndSmallAmbi;
extern const CFStringRef kIDXSearchPrefixMatchVoiceAmbi;
extern const CFStringRef kIDXSearchPrefixMatchSmallAmbi;
extern const CFStringRef kIDXSearchPrefixMatchVoiceAndSmallAmbi;

/*
 ===============================================================================
	Basic type
 ===============================================================================
*/

/*!
	@typedef	IDXIndexRef
	@abstract	Opaque CF object that represents a index file in dictionary package
*/
typedef const struct __IDXIndex*	IDXIndexRef;

/*!
	@function	IDXIndexGetTypeID
	@abstract	Gets the CFTypeID of a IDXIndexRef
	@result		Returns the CFTypeID of a IDXIndexRef, for comparison with
				the result of CFGetTypeID().
*/
extern 
CFTypeID IDXIndexGetTypeID( void );

/*
 ===============================================================================
	Index object
 ===============================================================================
*/

/*!	@function	IDXCopyIndexNames
	@abstract	Returns a list of indices in the specified dictionary package
	@param		directoryURL
				Dictionary package URL which contains the target indices.
	@param		getFileURLs
				If this is true, returned CFArray contains CFURLRef of availbale indices
				in the dictionary. Otherwise, an array of CFStringRef for semantic name
				(or file name if that isn't defined) is returned.
	@result		Returns an array of CFStringRef or CFURLRef for availbale indices in
				the specified dictionary package.
*/
extern
CFArrayRef IDXCopyIndexNames( CFURLRef dictionaryURL, Boolean getFileURLs );

/*!	@function	IDXCreateIndexObject
	@abstract	Creates a dictionary index object for a specified index in the dictionary package.
	@param		allocator
				CF allocator. May be NULL.
	@param		dictionaryURL
				Dictionary package URL which contains the target index file.
	@param		indexName
				Name of the target index. This could be either semantic name defined in
				kIDXPropertyIndexName in plist, or actual file name.
				If this is NULL, the first index defined in plist will be used.
	@result 	Returns a created IDXIndexRef CFType object.
*/
extern 
IDXIndexRef IDXCreateIndexObject( CFAllocatorRef allocator, CFURLRef dictionaryURL, CFStringRef indexName );

/*
 ===============================================================================
	Search and retrieve data using keyword
 ===============================================================================
*/

/*!	@function	IDXSetSearchString
	@abstract	Sets search conditions, with CFStringRef, to the index object.
	@param		indexRef
				Dictionary index object to be searched.
	@param		keyString
				CFStringRef for search string. If kIDXSearchAllMatch is set as matching
				method, this parameter is ignored.
	@param		matchingMethod
				String matching option for search. The usable options depend on index and
				its data access class. For example, Oxford dictionaries will support
				kIDXExactMatch, kIDXPrefixMatch, and kIDXCommonPrefixMatch as matching method.
	@result		Returns true if all conditions are set successfully.
	@discussion	Only one seach condition can be set in the index object at a time.
				To perform mulptiple searches with different conditions concurrently,
				need to create multiple index objects for their conditions respectively.
*/
extern 
Boolean IDXSetSearchString( IDXIndexRef indexRef, CFStringRef keyString, CFStringRef matchingMethod );

/*!	@function	IDXSetSearchCharacters
	@abstract	Sets search conditions, with UniChar buffer, to the index object.
	@param		indexRef
				Dictionary index object to be searched.
	@param		keyBuffer
				UniChar buffer for search string. If kIDXSearchAllMatch is set as
				matching method, keyBuffer and keyLength are ignored.
	@param		keyLength
				Length of search string.
	@param		matchingMethod
				String matching option for search. The usable options depend on index and
				its data access class. For example, Oxford dictionaries will support
				kIDXExactMatch, kIDXPrefixMatch, and kIDXCommonPrefixMatch as matching method.
	@result		Returns true if all conditions are set successfully.
	@discussion	Only one seach condition can be set in the index object at a time.
				To perform mulptiple searches with different conditions concurrently,
				need to create multiple index objects for their conditions respectively.
*/
extern 
Boolean IDXSetSearchCharacters( IDXIndexRef indexRef, const UniChar *keyBuffer, CFIndex keyLength, CFStringRef matchingMethod );

/*!	@typedef	IDXSearchCallBack
	@abstract	Callback function which is called each time macthed data is found in IDXPerformSearch.
	@param		indexRef
				Dictionary index object which is being searched.
	@param		data
				Buffer of found data. Note that this data contains all fields.
	@param		isVolatilePtr
				If this flag is true, the lifetime of passed data pointer is limitted in this call.
				So, make sure to copy data contents if it's needed to refer this data later.
				If this flag is false, the lifetime of passed data is equal to indexRef object.
	@param		info
				An arbitrary program-defined data pointer which is specified in IDXPerformSearch.
*/
typedef void (*IDXSearchCallBack)( IDXIndexRef indexRef, const UInt8 *data, CFIndex dataSize, Boolean isVolatilePtr, void *info );

/*!	@function	IDXPerformSearch
	@abstract	Performs search with specified condition via IDXSetSearchCharacters or IDXSetSearchString,
				and returns found data one by one.
	@param		indexRef
				Dictionary index object to be searched.
	@param		callback
				Callback function which is called each time macthed data is found.
	@param		info
				An arbitrary program-defined data pointer which is passed to the callback.
	@discussion	This function can be replaced with combination of low-level functions
				if more complex/specialized operations are needed.
*/
extern 
void IDXPerformSearch( IDXIndexRef indexRef, IDXSearchCallBack callback, void *info );

/*!	@function	IDXContainsMatchData
	@abstract	Checks if there is any matched data with conditions specified via
				IDXSetSearchString/Characters.
	@param		indexRef
				Dictionary index object to be checked.
	@param		foundCommonPrefixes
				If kIDXSearchCommonPrefixMatch is specified in IDXSetSearchString/Characters
				and non NULL pointer is passed, each element corresponding to existing key length
				will have true on return. (e.g. {true, false, true} for string "ABC" means that
				"A" and "ABC" exist in index) Caller must prepare array enough for search length.
	@result		Returns true if matched data is found.
	@discussion	For just checking existence of key, this function should be faster than other
				search methods since it doesn't search multiple entries nor fetch associated data.
*/
extern
Boolean IDXContainsMatchData( IDXIndexRef indexRef, Boolean foundCommonPrefixes[] );

/*
 ===============================================================================
	Retrieve data using data ID
 ===============================================================================
*/

/*!	@function	IDXGetDataPtrByID
	@abstract	Returns data pointer uniquely specified by persistent ID.
	@param		indexRef
				Dictionary index object contains target data.
	@param		dataID
				Persistent ID to specify data uniquely.
	@param		dataSize
				Size of data is returned.
	@result 	Returns stable data pointer which has long lifetime equals to indexRef.
	@discussion	This function can be used for index which returns true by IDXSupportDataPtr
				and supports dataID access.
*/
extern 
const UInt8 *IDXGetDataPtrByID( IDXIndexRef indexRef, UInt64 dataID, CFIndex *dataSize );

/*!	@function	IDXGetDataByID
	@abstract	Copies data uniquely specified by persistent ID into buffer.
	@param		indexRef
				Dictionary index object contains target data.
	@param		dataID
				Persistent ID to specify data uniquely.
	@param		maxLength
				The size of passed buffer.
	@param		buffer
				Data buffer where the target data copied into.
	@result 	Returns actual data size. If that is larger than passed buffer size,
				need to call this function again with expanded buffer.
	@discussion	This function can be used for index which supports dataID access.
*/
extern 
CFIndex IDXGetDataByID( IDXIndexRef indexRef, UInt64 dataID, CFIndex maxLength, UInt8 *buffer );

/*
 ===============================================================================
	Separate and pick out field data from data chunk
 ===============================================================================
*/

/*!	@function	IDXSetRequestFields
	@abstract	Sets field names to be retrieved via upcoming IDXGetFieldDataPtrs.
	@param		indexRef
				Dictionary index object which is set target fields to.
	@param		fieldNames
				CFArrayRef contains CFStringRef for requesting field names
	@discussion Fields setting is once stored in indexRef, IDXGetFieldDataPtrs can be called many times.
				This function should be called only if changes of setting is actually needed.
*/
extern
void IDXSetRequestFields( IDXIndexRef indexRef, CFArrayRef fieldNames );

/*!	@function	IDXGetFieldDataPtrs
	@abstract	Separates data and returns each pointers and sizes for requested fields.
	@param		indexRef
				Dictionary index object where data derived from.
	@param		data
				Data which is retrieved by IDXPerformSearch.
	@param		dataSize
				Size of data which is retrieved by IDXPerformSearch.
	@param		fieldDataPtrs
				Data pointers for each field's data are set. Caller must prepare the array buffer.
				NULL is set to the slot where the requested field is not found.
	@param		fieldDataSizes
				Data sizes for each field's data are set. Caller must prepare the array buffer.
				Zero is set to the slot where the requested field is not found.
	@discussion	Field data separation is performed based on schema definition in property list.
*/
extern
void IDXGetFieldDataPtrs( IDXIndexRef indexRef, const UInt8 *data, CFIndex dataSize, const UInt8 *fieldDataPtrs[], CFIndex fieldDataSizes[] );

/*!	@function	IDXCreateFlattenData
	@abstract	Create flatten data used in IDXAddRecord from separated field data.
	@param		indexRef
				Dictionary index object where data adding to.
	@param		fieldData
				Contains each field CFTypeRef data with field name key.
				UTF-16 text data should be represented as CFStringRef, UTF-8 text data should be
				CFDataRef, number data should be CFNumberRef, and others should be CFDataRef.
				Note that CFDataRef data will be stored as is without endian conversion.
				Omitted field will be stored as zero-length or zero-filled data.
	@result 	Flatten CFDataRef packed with field data based on schema definition in plist.
*/
extern
CFDataRef IDXCreateFlattenData( IDXIndexRef indexRef, CFDictionaryRef fieldData );

/*
 ===============================================================================
	Modify index
 ===============================================================================
*/

/*!	@function	IDXAddRecord
	@abstract	Add new entry with specied key and data.
	@param		indexRef
				Dictionary index object which is added record to.
	@param		keyString
				String specifies the target record. May be NULL if the index supports
				only dataID access.
	@param		data
				Contains adding data.
	@param		dataID
				Persistent ID for accessing registered data is set if the index supports
				dataID access. If not, zero will be set.
	@result 	Returns true if adding new record is succeeded.
*/
extern 
Boolean IDXAddRecord( IDXIndexRef indexRef, CFStringRef keyString, CFDataRef data, UInt64 *dataID );

/*!	@function	IDXDeleteRecord
	@abstract	Delete entry with specied key and data.
	@param		indexRef
				Dictionary index object which is removed record from.
	@param		keyString
				String specifies the target record. May be NULL if the index supports
				only dataID access.
	@param		data
				Data indicates the target record. May be NULL if the index supports dataID access. 
	@param		dataID
				Persistent ID indicates the target record. May be zero if the index
				doesn't support dataID access.
	@result 	Returns true if deleting a record is succeeded.
	@discussion	The required combination to specify a record can be varied according to supported
				data access methods in the index - keyString + data, keyString + dataID,
				or only dataID.
*/
extern 
Boolean IDXDeleteRecord( IDXIndexRef indexRef, CFStringRef keyString, CFDataRef data, UInt64 dataID );

/*!	@function	IDXBuildIndexWithRecords
	@abstract	Build index with records all at once. This will be faster than IDXAddRecord.
	@param		indexRef
				Dictionary index object which is added records to. Index must be empty.
	@param		keyArray
				Array of CFStringRef which contains key string. May be NULL if the index
				supports only dataID access.
	@param		dataArray
				Array of CFDataRef which contains data.
	@param		dataIDs
				Persistent ID array indicates the registered records. Caller must prepare array
				buffer. If the index doesn't support dataID, the first element is set to zero.
	@result 	Returns true if adding records succeeded.
*/
extern
Boolean IDXBuildIndexWithRecords( IDXIndexRef indexRef, CFArrayRef keyArray, CFArrayRef dataArray, UInt64 dataIDs[] );

/*
 ===============================================================================
	Create a new dictionary package
 ===============================================================================
*/

/*!	@function	IDXCreateDictionaryPackage
	@abstract	Create a new dictionary package at the speicied location with designated indexes.
	@param		dictionaryURL
				URL for the creating dictionary package.
	@param		templateProperty
				Pass CFDictionaryRef which describes indices and their specifications,
				and is copied as Info.plist in the dictionary package. It can be NULL
				for creating a general purpose dictionary which has one index for searching
				keyword in exact, prefix, common-prefix, and wildcard match. For each keyword,
				one variable size data chunk (32bit-wide length) can be accompanied.
				Additionally, for some common pre-defined usages, it could be a CFStringRef
				for the pre-defined template name. See each API for available names.
	@result 	Returns true if creating a lexcon package is succeeded.
*/
extern 
Boolean IDXCreateDictionaryPackage( CFURLRef dictionaryURL, CFTypeRef templateProperty );

/*
 ===============================================================================
	Low-level data access
 ===============================================================================
*/

/*!	@function	IDXGetMatchDataPtr
	@abstract	Performs search with specified condition via IDXSetSearchCharacters or IDXSetSearchString,
				and returns found data pointers.
	@param		indexRef
				Dictionary index object to be searched.
	@param		maxCount
				Maximum number of returned data pointers at a time.
	@param		dataPtrs
				Found data pointers are set in this array. Returned pointers are valid until
				indexRef is released, and caller doesn't need to release these pointers.
	@param		dataSizes
				Found data sizes are set in this array.
	@result 	The number of returned data pointers.
	@discussion	This function can be used for the index which returns true by IDXSupportDataPtr.
				Caller needs call this function repeatedly until zero is returned to retrieve
				all search result data.
*/
extern 
CFIndex IDXGetMatchDataPtr( IDXIndexRef indexRef, CFIndex maxCount, const UInt8 *dataPtrs[], CFIndex dataSizes[] );

/*!	@function	IDXGetMatchData
	@abstract	Performs search with specified condition via IDXSetSearchCharacters or IDXSetSearchString,
				and copies found data into the buffer.
	@param		indexRef
				Dictionary index object to be searched.
	@param		requestCount
				The number of requesting records. Pass zero to request maximum records as possible.
	@param		maxLength
				Passed buffer size.
	@param		buffer
				Buffer which is offered by caller. On return, this buffer is filled with found data and
				array of pointers each points to respective data.
	@param		dataRanges
				Pointer to an array of ranges locating each data in the result buffer. The array itself
				resides in the provided buffer together with found data itself.
	@param		adjustedLength
				If the passed buffer is too small to copy next found data, required buffer
				size is set to this param. When all found data has been returned, zero is
				set. Otherwise, the current buffer size passed in maxLength is set.
	@result 	The number of copied data.
	@discussion	Caller needs call this function repeatedly until zero is returned in adjustedLength
				and result value to retrieve all requested number of search result data. If the result value
				is zero but adjustedLength is set to non-zero, caller can expand buffer to the adjustedLength
				and call the function again to retrieve failed data.
*/
extern 
CFIndex IDXGetMatchData( IDXIndexRef indexRef, CFIndex requestCount, CFIndex maxLength, UInt8 *buffer, CFRange *dataRanges[], CFIndex *adjustedLength );

/*!	@function	IDXSupportDataPtr
	@abstract	Checks if the index can return stable data pointer.
	@param		indexRef
				Dictionary index object.
	@result 	Returns true if the index can return stable data pointer which is valid until
				indexRef is releasaed and is not needed to be released explicitly.
				Actually, that means the index returns file-mapped memory address.
*/
extern 
Boolean IDXSupportDataPtr( IDXIndexRef indexRef );


#ifdef __cplusplus
}
#endif

#endif /* __INDEXEDSEARCH__ */

