/*
 * Copyright (c) 2000-2004 Apple Computer, Inc. All Rights Reserved.
 * 
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
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
    @typedef SecPasswordRef
    @abstract Contains information about a password.
*/
typedef struct OpaqueSecPasswordRef *SecPasswordRef;

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
@constant errSecNotAvailable No keychain is available.
@constant errSecReadOnly Read only error.
@constant errSecAuthFailed Authorization/Authentication failed.
@constant errSecNoSuchKeychain The keychain does not exist.
@constant errSecInvalidKeychain The keychain is not valid.
@constant errSecDuplicateKeychain A keychain with the same name already exists.
@constant errSecDuplicateCallback The specified callback is already installed.
@constant errSecInvalidCallback The specified callback is not valid.
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
@constant errSecInvalidOwnerEdit Invalid attempt to change the owner of this item.
@constant errSecTrustNotAvailable No trust results are available.
@constant errSecUnsupportedFormat Import/Export format unsupported.
@constant errSecUnknownFormat Unknown format in import.
@constant errSecKeyIsSensitive Key material must be wrapped for export.
@constant errSecMultiplePrivKeys An attempt was made to import multiple private keys.
@constant errSecPassphraseRequired Passphrase is required for import/export.

@discussion The assigned error space is discontinuous: -25240..-25279, -25290..25329.
*/

/*
    Note: the comments that appear after these errors are used to create SecErrorMessages.strings.
    The comments must not be multi-line, and should be in a form meaningful to an end user. If
    a different or additional comment is needed, it can be put in the header doc format, or on a
    line that does not start with errZZZ.
*/

enum
{
    errSecNotAvailable           = -25291,	/* No keychain is available. You may need to restart your computer. */
    errSecReadOnly               = -25292,	/* This keychain cannot be modified. */
    errSecAuthFailed             = -25293,	/* The user name or passphrase you entered is not correct. */
    errSecNoSuchKeychain         = -25294,	/* The specified keychain could not be found. */
    errSecInvalidKeychain        = -25295,	/* The specified keychain is not a valid keychain file. */
    errSecDuplicateKeychain      = -25296,	/* A keychain with the same name already exists. */
    errSecDuplicateCallback      = -25297,	/* The specified callback function is already installed. */
    errSecInvalidCallback        = -25298,	/* The specified callback function is not valid. */
    errSecDuplicateItem          = -25299,	/* The specified item already exists in the keychain. */
    errSecItemNotFound           = -25300,	/* The specified item could not be found in the keychain. */
    errSecBufferTooSmall         = -25301,	/* There is not enough memory available to use the specified item. */
    errSecDataTooLarge           = -25302,	/* This item contains information which is too large or in a format that cannot be displayed. */
    errSecNoSuchAttr             = -25303,	/* The specified attribute does not exist. */
    errSecInvalidItemRef         = -25304,	/* The specified item is no longer valid. It may have been deleted from the keychain. */
    errSecInvalidSearchRef       = -25305,	/* Unable to search the current keychain. */
    errSecNoSuchClass            = -25306,	/* The specified item does not appear to be a valid keychain item. */
    errSecNoDefaultKeychain      = -25307,	/* A default keychain could not be found. */
    errSecInteractionNotAllowed  = -25308,	/* User interaction is not allowed. */
    errSecReadOnlyAttr           = -25309,	/* The specified attribute could not be modified. */
    errSecWrongSecVersion        = -25310,	/* This keychain was created by a different version of the system software and cannot be opened. */
    errSecKeySizeNotAllowed      = -25311,	/* This item specifies a key size which is too large. */
    errSecNoStorageModule        = -25312,	/* A required component (data storage module) could not be loaded. You may need to restart your computer. */
    errSecNoCertificateModule    = -25313,	/* A required component (certificate module) could not be loaded. You may need to restart your computer. */
    errSecNoPolicyModule         = -25314,	/* A required component (policy module) could not be loaded. You may need to restart your computer. */
    errSecInteractionRequired    = -25315,	/* User interaction is required, but is currently not allowed. */
    errSecDataNotAvailable       = -25316,	/* The contents of this item cannot be retrieved. */
    errSecDataNotModifiable      = -25317,	/* The contents of this item cannot be modified. */
    errSecCreateChainFailed      = -25318,	/* One or more certificates required to validate this certificate cannot be found. */
	errSecInvalidPrefsDomain	 = -25319,  /* The specified preferences domain is not valid. */
	
	errSecACLNotSimple           = -25240,	/* The specified access control list is not in standard (simple) form. */
	errSecPolicyNotFound         = -25241,	/* The specified policy cannot be found. */
	errSecInvalidTrustSetting    = -25242,	/* The specified trust setting is invalid. */
	errSecNoAccessForItem        = -25243,	/* The specified item has no access control. */
	errSecInvalidOwnerEdit       = -25244,  /* Invalid attempt to change the owner of this item. */
	errSecTrustNotAvailable      = -25245,	/* No trust results are available. */
	errSecUnsupportedFormat		 = -25256,  /* Import/Export format unsupported. */
	errSecUnknownFormat			 = -25257,  /* Unknown format in import. */
	errSecKeyIsSensitive		 = -25258,  /* Key material must be wrapped for export. */
	errSecMultiplePrivKeys		 = -25259,  /* An attempt was made to import multiple private keys. */
	errSecPassphraseRequired	 = -25260,  /* Passphrase is required for import/export. */
    errSecInvalidPasswordRef     = -25261   /* Invalid SecPasswordRef */
};

#if defined(__cplusplus)
}
#endif

#endif /* !_SECURITY_SECBASE_H_ */
