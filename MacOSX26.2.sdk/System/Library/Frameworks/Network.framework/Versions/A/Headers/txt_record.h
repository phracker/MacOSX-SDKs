//
//  txt_record.h
//  Network
//
//  Copyright (c) 2018-2019 Apple Inc. All rights reserved.
//

#ifndef __NW_TXT_RECORD_H__
#define __NW_TXT_RECORD_H__

#ifndef __NW_INDIRECT__
#warning "Please include <Network/Network.h> instead of this file directly."
#endif // __NW_INDIRECT__

#include <Network/nw_object.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

NW_ASSUME_NONNULL_BEGIN

__BEGIN_DECLS

/*!
 * @typedef nw_txt_record_t
 * @abstract
 *		A TXT Record Object is used to provide additional information about a
 *		service during discovery. Two formats of the TXT record are supported:
 *
 *		1. A dictionary of key-value pairs as defined in RFC 1464.
 *		2. A buffer of bytes.
 *
 *		The format of a TXT Record object is defined at creation time and cannot
 *		be changed later. If the buffer provided to nw_txt_record_create_with_bytes()
 *		conforms to the key-value pair format, the TXT record object will be created
 *		as a dictionary. Otherwise, the TXT record object is created as a buffer
 *		of bytes and any key-value pair functions called on the object will fail.
 *
 *		This type supports ARC and the -[description] method. In non-ARC files, use
 *		nw_retain() and nw_release() to retain and release the object.
 */
#ifndef NW_TXT_RECORD_IMPL
NW_OBJECT_DECL(nw_txt_record);
#endif // NW_TXT_RECORD_IMPL

/*!
 * @typedef nw_txt_record_find_key_t
 * @abstract
 *		An enumeration of possible find results when trying to find a key-value
 *		pair in the TXT record object.
 */
typedef enum {
	/*!
	 *	@const nw_txt_record_find_key_invalid The key is invalid. According
	 *		to RFC 1464, a key is invalid if it is an empty string, contains
	 *		non-ASCII characters, or has length greater than UINT8_MAX.
	 */
	nw_txt_record_find_key_invalid = 0,
	/*!
	 *	@const nw_txt_record_find_key_not_present The key-value pair does not exist in the TXT record.
	 */
	nw_txt_record_find_key_not_present = 1,
	/*!
	 *	@const nw_txt_record_find_key_no_value The key exists in the TXT record, but has no assigned value.
	 */
	nw_txt_record_find_key_no_value = 2,
	/*!
	 *	@const nw_txt_record_find_key_empty_value The key exists in the TXT record with an empty value.
	 */
	nw_txt_record_find_key_empty_value = 3,
	/*!
	 *	@const nw_txt_record_find_key_non_empty_value The key exists in the TXT record with a non-empty value.
	 */
	nw_txt_record_find_key_non_empty_value = 4,
} nw_txt_record_find_key_t;

/*!
 * @function nw_txt_record_create_with_bytes
 *
 * @abstract
 *		Create a new TXT record object from a buffer of bytes. If the buffer
 *		follows the key-value pair format as defined in RFC 1464, the TXT record
 *		object will be created as a dictionary. Otherwise, it is created as a
 *		TXT record buffer.
 *
 * @param txt_bytes
 *		The pointer to the buffer.
 *
 * @param txt_len
 *		The length of the buffer.
 *
 * @result
 *		An instantiated TXT record object.
 *		Callers are responsible for deallocating using nw_release(obj) or
 *		[obj release]. These objects support ARC.
 *		Returns NULL on failure. Fails if txt_bytes is NULL or if txt_len is 0.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NW_RETURNS_RETAINED nw_txt_record_t
nw_txt_record_create_with_bytes(const uint8_t * txt_bytes, size_t txt_len);

/*!
 * @function nw_txt_record_create_dictionary
 *
 * @abstract
 *		Create an empty TXT record dictionary.
 *
 * @result
 *		An empty TXT record dictionary.
 *		Callers are responsible for deallocating using nw_release(obj) or
 *		[obj release]. These objects support ARC.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NW_RETURNS_RETAINED nw_txt_record_t
nw_txt_record_create_dictionary(void);

/*!
 * @function nw_txt_record_copy
 *
 * @abstract
 *      Create a deep copy of an existing TXT record object.
 *
 * @param txt_record
 *      The TXT record object to be copied.
 *
 * @result
 *		A deep copy of the TXT record object.
 *		Callers are responsible for deallocating using nw_release(obj) or
 *		[obj release]. These objects support ARC.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
NW_RETURNS_RETAINED _Nullable nw_txt_record_t
nw_txt_record_copy(nw_txt_record_t _Nullable txt_record);

/*!
 * @function nw_txt_record_find_key
 *
 * @abstract
 *		Find a key-value pair in the TXT record object.
 *
 * @param txt_record
 *		The TXT record object.
 *
 * @param key
 *		The key of the key-value pair.
 *
 * @result
 *		An nw_txt_record_find_key_t representing the type of the key-value pair found.
 *		The key may be invalid, may not exist, have no associated value, have an
 *		empty associated value, or have a non-empty associated value.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
nw_txt_record_find_key_t
nw_txt_record_find_key(nw_txt_record_t txt_record, const char *key);

#ifdef __BLOCKS__
/*!
 * @typedef nw_txt_record_access_key_t
 *
 * @abstract
 *		Access a value in the TXT record object with its key. Attempts to access
 *		or modify the TXT record object from within the block are prohibited.
 *
 * @param key
 *		The key of the value.
 *
 * @param found
 *		An nw_txt_record_find_key_t representing the type of the key-value pair found.
 *		The key may be invalid, may not exist, have no associated value, have an
 *		empty associated value, or have a non-empty associated value.
 *
 * @param value
 *		The value corresponding to the key. If the key does not exist or has no
 *		associated value, value will be NULL. Note that the bytes pointed to by
 *		value are only valid within the scope of the block.
 *
 * @param value_len
 *		The length of the value. If the key does not exist or has no associated
 *		value, value_len will be 0.
 *
 * @result
 *		An arbitrary return value defined by the user. For example, the user may
 *		want to return true if the operation succeeds.
 */
typedef bool (^nw_txt_record_access_key_t) (const char *key,
											const nw_txt_record_find_key_t found,
											const uint8_t * _Nullable value,
											const size_t value_len);

/*!
 * @function nw_txt_record_access_key
 *
 * @abstract
 *		Access a value in the TXT record object with its key. Attempts to access
 *		or modify the TXT record object from within the block are prohibited.
 *
 * @param txt_record
 *      The TXT record object.
 *
 * @param access_value
 *      The block that will be used to access the value of the given key.
 *
 * @result
 *      The return value of the access_value block. This is an arbitrary return
 *		value defined by the user.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
bool
nw_txt_record_access_key(nw_txt_record_t txt_record, const char *key,
						 nw_txt_record_access_key_t access_value);
#endif // __BLOCKS__

/*!
 * @function nw_txt_record_set_key
 *
 * @abstract
 *		Set a key-value pair on the TXT record object.
 *
 * @param txt_record
 *		The TXT record object.
 *
 * @param key
 *		The key that will be inserted. If the key already exists in the TXT
 *		record object, the existing key-value pair will be replaced.
 *
 * @param value
 *		The value that will be inserted. If value is set to NULL, then the key
 *		will be inserted with no value.
 *
 * @param value_len
 *		The length of the value will be inserted. If value is set to zero, then the
 *		key will be inserted with a zero-length value. Inserting a NULL value
 *		with a non-zero length will fail.
 *
 * @result
 *		A boolean indicating if the key-value pair was inserted successfully.
 *		Returns false if the key is invalid. A key is invalid if it is an empty
 *		string, contains non-ASCII characters, or has length greater than
 *		UINT8_MAX.
 *
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
bool
nw_txt_record_set_key(nw_txt_record_t txt_record, const char *key,
					  const uint8_t * _Nullable value, size_t value_len);

/*!
 * @function nw_txt_record_remove_key
 *
 * @abstract
 *		Removes a key-value pair in the TXT record object given its key.
 *
 * @param txt_record
 *		The TXT record object.
 *
 * @param key
 *		The key corresponding to the key-value pair.
 *
 * @result
 *		A boolean indicating if the key-value pair specified by the given key
 *		was removed. Returns false if the key is invalid or not present in the
 *		TXT dictionary. A key is invalid if it is an empty string, contains
 *		non-ASCII characters, or has length greater than UINT8_MAX.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
bool
nw_txt_record_remove_key(nw_txt_record_t txt_record,
						 const char *key);

/*!
 * @function nw_txt_record_get_key_count
 *
 * @abstract
 *		Count the number of keys in the TXT record object.
 *
 * @param txt_record
 *		A TXT record object.
 *
 * @result
 *		The number of keys in the TXT record object.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
size_t
nw_txt_record_get_key_count(nw_txt_record_t _Nullable txt_record);

#ifdef __BLOCKS__
/*!
 * @typedef nw_txt_record_access_bytes_t
 *
 * @abstract
 *		A block to access the raw TXT record inside the TXT record object. For
 *		example, the user can copy the raw TXT record into another buffer in the
 *		block, or read its contents.
 *
 * @param raw_txt_record
 *		The raw TXT record inside the TXT record object. Note that the bytes
 *		pointed to by raw_txt_record is only valid within the scope of the block.
 *
 * @param len
 *		The length of the raw TXT record.
 *
 * @result
 *		A user-defined return value. For example, the user may want to return a
 *	 	boolean indicating if the operation succeeds.
 */
typedef bool (^nw_txt_record_access_bytes_t) (const uint8_t *raw_txt_record,
											  size_t len);

/*!
 * @function nw_txt_record_access_bytes
 *
 * @abstract
 *		Access the raw TXT record inside the TXT record object.
 *
 * @param txt_record
 *		The TXT record object.
 *
 * @param access_bytes
 *		The block that will be used to access the raw TXT record inside the TXT
 *		record object.
 *
 * @result
 *		The return value of the access_bytes block, which is defined by the user.
 *		For example, the user may want to return a boolean indicating if the
 *		operation succeeds.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
bool
nw_txt_record_access_bytes(nw_txt_record_t txt_record,
						   nw_txt_record_access_bytes_t access_bytes);

/*!
 * @typedef nw_txt_record_applier_t
 *
 * @abstract
 *		A block that can be applied to every key-value pair in the TXT record
 *		object.
 *
 * @param key
 *		The key of the current iterating key-value pair. Note that key is only
 *		valid within the scope of the block.
 *
 * @param found
 *		An nw_txt_record_find_key_t representing the type of the key-value pair found.
 *		The key may be invalid, may not exist, have no associated value, have an
 *		empty associated value, or have a non-empty associated value.
 *
 * @param value
 *		The value of the current iterating key-value pair. Note that value is
 *		only valid within the scope of the block.
 *
 * @param value_len
 *		The length of the value.
 *
 * @result
 *		A boolean indicating whether iteration should continue.
 */
typedef bool (^nw_txt_record_applier_t) (const char *key,
										 const nw_txt_record_find_key_t found,
										 const uint8_t *value,
										 const size_t value_len);

/*!
 * @function nw_txt_record_apply
 *
 * @abstract
 *      Apply the block to every key-value pair in the TXT record object.
 *
 * @param txt_record
 *      The TXT record object.
 *
 * @param applier
 *      The block that will be applied to the entire TXT record object.
 *
 * @result
 *      A boolean indicating whether iteration of the TXT record object
 *		completed successfully. Iteration will only fail if the applier block
 *		returns false.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
bool
nw_txt_record_apply(nw_txt_record_t txt_record,
					nw_txt_record_applier_t applier);
#endif // __BLOCKS__

/*!
 * @function nw_txt_record_is_equal
 *
 * @abstract
 *      Check if the two TXT record objects are equal.
 *
 * @param left
 *      The first TXT record object to be compared.
 *
 * @param right
 *      The second TXT record object to be compared.
 *
 * @result
 *      A boolean indicating if the two TXT record objects are equal. Two TXT
 *		record objects are equal if they contain the same set of key-value pairs,
 *		where keys are compared case-insensitively. For example, "ABC=1" and
 *		"abc=1" are identical key-value pairs. The ordering of the key-value
 *		pairs does not matter.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
bool
nw_txt_record_is_equal(nw_txt_record_t _Nullable left,
					   nw_txt_record_t _Nullable right);

/*!
 * @function nw_txt_record_is_dictionary
 *
 * @abstract
 *      Check whether the TXT record is a dictionary or a buffer.
 *
 * @param txt_record
 *		The TXT record object.
 *
 * @result
 *      A boolean indicating whether the TXT record is a dictionary or a buffer.
 * 		If true, the TXT record is a dictionary. If false, the TXT record is a
 *		buffer.
 */
API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0))
bool
nw_txt_record_is_dictionary(nw_txt_record_t txt_record);

__END_DECLS

NW_ASSUME_NONNULL_END

#endif /* __NW_TXT_RECORD_H__ */
