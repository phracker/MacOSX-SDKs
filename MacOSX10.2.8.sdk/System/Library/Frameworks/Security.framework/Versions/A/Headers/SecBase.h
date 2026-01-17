/*
 * Copyright (c) 2000-2002 Apple Computer, Inc. All Rights Reserved.
 * 
 * The contents of this file constitute Original Code as defined in and are
 * subject to the Apple Public Source License Version 1.2 (the 'License').
 * You may not use this file except in compliance with the License. Please obtain
 * a copy of the License at http://www.apple.com/publicsource and read it before
 * using this file.
 * 
 * This Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS
 * OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES, INCLUDING WITHOUT
 * LIMITATION, ANY WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT. Please see the License for the
 * specific language governing rights and limitations under the License.
 */

/*!
	@header SecBase
	SecBase contains common declarations for the Security functions. 
*/

#ifndef _SECURITY_SECBASE_H_
#define _SECURITY_SECBASE_H_

#include <CoreFoundation/CFBase.h>

#if defined(__cplusplus)
extern "C" {
#endif

#ifndef __SEC_TYPES__
#define __SEC_TYPES__

/*!
    @typedef SecKeychainRef
    @abstract Contains information about a keychain.
*/
typedef struct OpaqueSecKeychainRef *SecKeychainRef;

/*!
    @typedef SecKeychainItemRef
    @abstract Contains information about a keychain item.
*/
typedef struct OpaqueSecKeychainItemRef *SecKeychainItemRef;

/*!
    @typedef SecKeychainSearchRef
    @abstract Contains information about a keychain search.
*/
typedef struct OpaqueSecKeychainSearchRef *SecKeychainSearchRef;

/*!
    @typedef SecKeychainAttrType
    @abstract Represents a keychain attribute type.
*/
typedef OSType SecKeychainAttrType;

/*!
    @struct SecKeychainAttribute
    @abstract Contains keychain attributes. 
    @field tag A 4-byte attribute tag.
    @field length The length of the buffer pointed to by data.
    @field data A pointer to the attribute data.
*/
struct SecKeychainAttribute 
{
    SecKeychainAttrType	tag;
    UInt32 length;
    void *data;
};
typedef struct SecKeychainAttribute SecKeychainAttribute;

/*!
    @typedef SecKeychainAttributePtr
    @abstract Represents a pointer to a keychain attribute structure.
*/
typedef SecKeychainAttribute *SecKeychainAttributePtr;

/*!
    @typedef SecKeychainAttributeList
    @abstract Represents a list of keychain attributes.
    @field count An unsigned 32-bit integer that represents the number of keychain attributes in the array.
    @field attr A pointer to the first keychain attribute in the array.
*/
struct SecKeychainAttributeList 
{
    UInt32 count;
    SecKeychainAttribute *attr;
};
typedef struct SecKeychainAttributeList  SecKeychainAttributeList;

/*!
    @typedef SecKeychainStatus
    @abstract Represents the status of a keychain.
*/
typedef UInt32 SecKeychainStatus;
#endif

/*!
    @typedef SecTrustedApplicationRef
    @abstract Contains information about a trusted application.
*/
typedef struct OpaqueSecTrustedApplicationRef *SecTrustedApplicationRef;

/*!
    @typedef SecPolicyRef
    @abstract Contains information about a policy.
*/
typedef struct OpaqueSecPolicyRef *SecPolicyRef;

/*!
    @typedef SecCertificateRef
    @abstract Contains information about a certificate.
*/
typedef struct OpaqueSecCertificateRef *SecCertificateRef;

/*!
    @typedef SecAccessRef
    @abstract Contains information about an access.
*/
typedef struct OpaqueSecAccessRef *SecAccessRef;

/*!
    @typedef SecIdentityRef
    @abstract Contains information about an identity.
*/
typedef struct OpaqueSecIdentityRef *SecIdentityRef;

/*!
    @typedef SecKeyRef
    @abstract Contains information about a key.
*/
typedef struct OpaqueSecKeyRef *SecKeyRef;

/*!
    @typedef SecACLRef
    @abstract Contains information about an access control list (ACL) entry.
*/
typedef struct OpaqueSecTrustRef *SecACLRef;

/*!
    @typedef SecKeychainAttributeInfo
    @abstract Represents an attribute. 
    @field count The number of tag-format pairs in the respective arrays. 
    @field tag A pointer to the first attribute tag in the array.
    @field format A pointer to the first attribute format in the array.
    @discussion Each tag and format item form a pair.  
*/
struct SecKeychainAttributeInfo
{
    UInt32 count;
    UInt32 *tag;
	UInt32 *format;
};
typedef struct SecKeychainAttributeInfo  SecKeychainAttributeInfo;

/*!
@enum Security Error Codes 
@abstract Represents the result codes.
@constant errSecNotAvailable No trust results are available.
@constant errSecReadOnly Read only error.
@constant errSecAuthFailed Authorization/Authentication failed.
@constant errSecNoSuchKeychain The keychain does not exist.
@constant errSecInvalidKeychain The keychain is not valid.
@constant errSecDuplicateKeychain A keychain with the same name already exists.
@constant errSecDuplicateCallback More than one callback of the same name exists.
@constant errSecInvalidCallback The callback is not valid.
@constant errSecDuplicateItem The item already exists.
@constant errSecItemNotFound The item cannot be found.
@constant errSecBufferTooSmall The buffer is too small.
@constant errSecDataTooLarge The data is too large.
@constant errSecNoSuchAttr The attribute does not exist.
@constant errSecInvalidItemRef The item reference is invalid.
@constant errSecInvalidSearchRef The search reference is invalid.
@constant errSecNoSuchClass The keychain item class does not exist.
@constant errSecNoDefaultKeychain A default keychain does not exist.
@constant errSecInteractionNotAllowed Interaction is not allowed with the Security Server.
@constant errSecReadOnlyAttr The attribute is read only.
@constant errSecWrongSecVersion The version is incorrect.
@constant errSecKeySizeNotAllowed The key size is not allowed.
@constant errSecNoStorageModule There is no storage module available.
@constant errSecNoCertificateModule There is no certificate module available.
@constant errSecNoPolicyModule There is no policy module available.
@constant errSecInteractionRequired User interaction is required.
@constant errSecDataNotAvailable The data is not available.
@constant errSecDataNotModifiable The data is not modifiable.
@constant errSecCreateChainFailed The attempt to create a certificate chain failed.
@constant errSecACLNotSimple The access control list is not in standard simple form.
@constant errSecPolicyNotFound The policy specified cannot be found.
@constant errSecInvalidTrustSetting The trust setting is invalid.
@constant errSecNoAccessForItem The specified item has no access control.
@discussion The assigned error space is discontinuous: -25240..-25279, -25290..25329.
*/
enum
{
    errSecNotAvailable           = -25291,
    errSecReadOnly               = -25292,
    errSecAuthFailed             = -25293,
    errSecNoSuchKeychain         = -25294,
    errSecInvalidKeychain        = -25295,
    errSecDuplicateKeychain      = -25296,
    errSecDuplicateCallback      = -25297,
    errSecInvalidCallback        = -25298,
    errSecDuplicateItem          = -25299,
    errSecItemNotFound           = -25300,
    errSecBufferTooSmall         = -25301,
    errSecDataTooLarge           = -25302,
    errSecNoSuchAttr             = -25303,
    errSecInvalidItemRef         = -25304,
    errSecInvalidSearchRef       = -25305,
    errSecNoSuchClass            = -25306,
    errSecNoDefaultKeychain      = -25307,
    errSecInteractionNotAllowed  = -25308,
    errSecReadOnlyAttr           = -25309,
    errSecWrongSecVersion        = -25310,
    errSecKeySizeNotAllowed      = -25311,
    errSecNoStorageModule        = -25312,
    errSecNoCertificateModule    = -25313,
    errSecNoPolicyModule         = -25314,
    errSecInteractionRequired    = -25315,
    errSecDataNotAvailable       = -25316,
    errSecDataNotModifiable      = -25317,
    errSecCreateChainFailed      = -25318,
	
	errSecACLNotSimple           = -25240,
	errSecPolicyNotFound         = -25241,
	errSecInvalidTrustSetting    = -25242,
	errSecNoAccessForItem        = -25243,
	errSecInvalidOwnerEdit       = -25244
};

#if defined(__cplusplus)
}
#endif

#endif /* !_SECURITY_SECBASE_H_ */
