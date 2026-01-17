/*
 * Copyright (c) 2002-2009 Apple, Inc. All Rights Reserved.
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
	@header SecKey
	The functions provided in SecKey.h implement and manage a particular
    type of keychain item that represents a key.  A key can be stored in a
    keychain, but a key can also be a transient object.

	You can use a key as a keychain item in most functions.
*/

#ifndef _SECURITY_SECKEY_H_
#define _SECURITY_SECKEY_H_

#include <Security/SecBase.h>
#include <Security/cssmtype.h>
#include <CoreFoundation/CFDictionary.h>
#include <sys/types.h>

#if defined(__cplusplus)
extern "C" {
#endif

/*!
	@enum KeyItemAttributeConstants
	@abstract Specifies keychain item attributes for keys.
    @constant kSecKeyKeyClass type uint32 (CSSM_KEYCLASS), value
    is one of CSSM_KEYCLASS_PUBLIC_KEY, CSSM_KEYCLASS_PRIVATE_KEY
    or CSSM_KEYCLASS_SESSION_KEY.
    @constant kSecKeyPrintName type blob, human readable name of
    the key.  Same as kSecLabelItemAttr for normal keychain items.
    @constant kSecKeyAlias type blob, currently unused.
    @constant kSecKeyPermanent type uint32, value is nonzero iff
    this key is permanent (stored in some keychain).  This is always
    1.
    @constant kSecKeyPrivate type uint32, value is nonzero iff this
    key is protected by a user login or a password, or both.
    @constant kSecKeyModifiable type uint32, value is nonzero iff
    attributes of this key can be modified.
    @constant kSecKeyLabel type blob, for private and public keys
    this contains the hash of the public key.  This is used to
    associate certificates and keys.  It's value matches the value
    of the kSecPublicKeyHashItemAttr of a certificate and it's used
    to construct an identity from a certificate and a key.
    For symmetric keys this is whatever the creator of the key
    passed in during the generate key call.
    @constant kSecKeyApplicationTag type blob, currently unused.
    @constant kSecKeyKeyCreator type data, the data points to a
    CSSM_GUID structure representing the moduleid of the csp owning
    this key.
    @constant kSecKeyKeyType type uint32, value a CSSM_ALGORITHMS
    representing the algorithm associated with this key.
    @constant kSecKeyKeySizeInBits type uint32, value is the number
    of bits in this key.
    @constant kSecKeyEffectiveKeySize type uint32, value is the
    effective number of bits in this key.  For example a des key
    has a kSecKeyKeySizeInBits of 64 but a kSecKeyEffectiveKeySize
    of 56.
    @constant kSecKeyStartDate type CSSM_DATE.  Earliest date from
    which this key may be used.  If the value is all zeros or not
    present, no restriction applies.
    @constant kSecKeyEndDate type CSSM_DATE.  Latest date at
    which this key may be used.  If the value is all zeros or not
    present, no restriction applies.
    @constant kSecKeySensitive type uint32, iff value is nonzero
    this key cannot be wrapped with CSSM_ALGID_NONE.
    @constant kSecKeyAlwaysSensitive type uint32, value is nonzero
    iff this key has always been marked sensitive.
    @constant kSecKeyExtractable type uint32, value is nonzero iff
    this key can be wrapped.
    @constant kSecKeyNeverExtractable type uint32, value is nonzero
    iff this key was never marked extractable.
    @constant kSecKeyEncrypt type uint32, value is nonzero iff this
    key can be used in an encrypt operation.
    @constant kSecKeyDecrypt type uint32, value is nonzero iff this
    key can be used in a decrypt operation.
    @constant kSecKeyDerive type uint32, value is nonzero iff this
    key can be used in a deriveKey operation.
    @constant kSecKeySign type uint32, value is nonzero iff this
    key can be used in a sign operation.
    @constant kSecKeyVerify type uint32, value is nonzero iff this
    key can be used in a verify operation.
    @constant kSecKeySignRecover type uint32.
    @constant kSecKeyVerifyRecover type uint32.
    key can unwrap other keys.
    @constant kSecKeyWrap type uint32, value is nonzero iff this 
    key can wrap other keys.
    @constant kSecKeyUnwrap type uint32, value is nonzero iff this
    key can unwrap other keys.
	@discussion @@@.
*/
enum
{
    kSecKeyKeyClass =          0,
    kSecKeyPrintName =         1,
    kSecKeyAlias =             2,
    kSecKeyPermanent =         3,
    kSecKeyPrivate =           4,
    kSecKeyModifiable =        5,
    kSecKeyLabel =             6,
    kSecKeyApplicationTag =    7,
    kSecKeyKeyCreator =        8,
    kSecKeyKeyType =           9,
    kSecKeyKeySizeInBits =    10,
    kSecKeyEffectiveKeySize = 11,
    kSecKeyStartDate =        12,
    kSecKeyEndDate =          13,
    kSecKeySensitive =        14,
    kSecKeyAlwaysSensitive =  15,
    kSecKeyExtractable =      16,
    kSecKeyNeverExtractable = 17,
    kSecKeyEncrypt =          18,
    kSecKeyDecrypt =          19,
    kSecKeyDerive =           20,
    kSecKeySign =             21,
    kSecKeyVerify =           22,
    kSecKeySignRecover =      23,
    kSecKeyVerifyRecover =    24,
    kSecKeyWrap =             25,
    kSecKeyUnwrap =           26
};

/*!
    @typedef SecCredentialType
    @abstract Determines the type of credential returned by SecKeyGetCredentials.
*/
typedef uint32 SecCredentialType;

/*!
    @enum SecCredentialType
    @abstract Determines the type of credential returned by SecKeyGetCredentials.
    @constant kSecCredentialTypeWithUI Operations with this key are allowed to present UI if required.
    @constant kSecCredentialTypeNoUI Operations with this key are not allowed to present UI, and will fail if UI is required.
    @constant kSecCredentialTypeDefault The default setting for determining whether to present UI is used. This setting can be changed with a call to SecKeychainSetUserInteractionAllowed.
*/
enum
{
	kSecCredentialTypeDefault = 0,
	kSecCredentialTypeWithUI,
	kSecCredentialTypeNoUI
};

/*!
    @typedef SecPadding
    @abstract Supported padding types.
*/
typedef uint32_t SecPadding;
enum
{
    kSecPaddingNone      = 0,
    kSecPaddingPKCS1     = 1,

    /* For SecKeyRawSign/SecKeyRawVerify only, data to be signed is an MD2
       hash; standard ASN.1 padding will be done, as well as PKCS1 padding
       of the underlying RSA operation. */
    kSecPaddingPKCS1MD2  = 0x8000,

    /* For SecKeyRawSign/SecKeyRawVerify only, data to be signed is an MD5
       hash; standard ASN.1 padding will be done, as well as PKCS1 padding
       of the underlying RSA operation. */
    kSecPaddingPKCS1MD5  = 0x8001,

    /* For SecKeyRawSign/SecKeyRawVerify only, data to be signed is a SHA1
       hash; standard ASN.1 padding will be done, as well as PKCS1 padding
       of the underlying RSA operation. */
    kSecPaddingPKCS1SHA1 = 0x8002,
};


/*!
	@function SecKeyGetTypeID
	@abstract Returns the type identifier of SecKey instances.
	@result The CFTypeID of SecKey instances.
*/
CFTypeID SecKeyGetTypeID(void);

/*!
	@function SecKeyCreatePair
	@abstract Creates an asymmetric key pair and stores it in a specified keychain.
	@param keychainRef A reference to the keychain in which to store the private and public key items. Specify NULL for the default keychain.
    @param algorithm An algorithm for the key pair. This parameter is ignored if a valid (non-zero) contextHandle is supplied.
    @param keySizeInBits A key size for the key pair. This parameter is ignored if a valid (non-zero) contextHandle is supplied.
	@param contextHandle (optional) A CSSM_CC_HANDLE, or 0. If this argument is supplied, the algorithm and keySizeInBits parameters are ignored. If extra parameters are needed to generate a key (some algorithms require this), you should create a context using CSSM_CSP_CreateKeyGenContext, using the CSPHandle obtained by calling SecKeychainGetCSPHandle. Then use CSSM_UpdateContextAttributes to add parameters, and dispose of the context using CSSM_DeleteContext after calling this function.
	@param publicKeyUsage A bit mask indicating all permitted uses for the new public key. CSSM_KEYUSE bit mask values are defined in cssmtype.h.
    @param publicKeyAttr A bit mask defining attribute values for the new public key. The bit mask values are equivalent to a CSSM_KEYATTR_FLAGS and are defined in cssmtype.h.
    @param privateKeyUsage A bit mask indicating all permitted uses for the new private key. CSSM_KEYUSE bit mask values are defined in cssmtype.h.
    @param privateKeyAttr A bit mask defining attribute values for the new private key. The bit mask values are equivalent to a CSSM_KEYATTR_FLAGS and are defined in cssmtype.h.
    @param initialAccess (optional) A SecAccess object that determines the initial access rights to the private key. The public key is given "any/any" access rights by default.
    @param publicKey (optional) On return, the keychain item reference of the generated public key. Use the SecKeyGetCSSMKey function to obtain the CSSM_KEY. The caller must call CFRelease on this value if it is returned. Pass NULL if a reference to this key is not required.
    @param privateKey (optional) On return, the keychain item reference of the generated private key. Use the SecKeyGetCSSMKey function to obtain the CSSM_KEY. The caller must call CFRelease on this value if it is returned. Pass NULL if a reference to this key is not required.
	@result A result code. See "Security Error Codes" (SecBase.h).
*/
OSStatus SecKeyCreatePair(
        SecKeychainRef keychainRef,
        CSSM_ALGORITHMS algorithm,
        uint32 keySizeInBits,
        CSSM_CC_HANDLE contextHandle,
        CSSM_KEYUSE publicKeyUsage,
        uint32 publicKeyAttr,
        CSSM_KEYUSE privateKeyUsage,
        uint32 privateKeyAttr,
        SecAccessRef initialAccess,
        SecKeyRef* publicKey, 
        SecKeyRef* privateKey);

/*!
	@function SecKeyGenerate
	@abstract Creates a symmetric key and optionally stores it in a specified keychain.
	@param keychainRef (optional) A reference to the keychain in which to store the generated key. Specify NULL to generate a transient key.
    @param algorithm An algorithm for the symmetric key. This parameter is ignored if a valid (non-zero) contextHandle is supplied.
    @param keySizeInBits A key size for the key pair. This parameter is ignored if a valid (non-zero) contextHandle is supplied.
	@param contextHandle (optional) A CSSM_CC_HANDLE, or 0. If this argument is supplied, the algorithm and keySizeInBits parameters are ignored. If extra parameters are needed to generate a key (some algorithms require this), you should create a context using CSSM_CSP_CreateKeyGenContext, using the CSPHandle obtained by calling SecKeychainGetCSPHandle. Then use CSSM_UpdateContextAttributes to add parameters, and dispose of the context using CSSM_DeleteContext after calling this function.
	@param keyUsage A bit mask indicating all permitted uses for the new key. CSSM_KEYUSE bit mask values are defined in cssmtype.h.
    @param keyAttr A bit mask defining attribute values for the new key. The bit mask values are equivalent to a CSSM_KEYATTR_FLAGS and are defined in cssmtype.h.
    @param initialAccess (optional) A SecAccess object that determines the initial access rights for the key. This parameter is ignored if the keychainRef is NULL.
    @param keyRef On return, a reference to the generated key. Use the SecKeyGetCSSMKey function to obtain the CSSM_KEY. The caller must call CFRelease on this value if it is returned.
	@result A result code.  See "Security Error Codes" (SecBase.h).
*/
OSStatus SecKeyGenerate(
        SecKeychainRef keychainRef,
        CSSM_ALGORITHMS algorithm,
        uint32 keySizeInBits,
        CSSM_CC_HANDLE contextHandle,
        CSSM_KEYUSE keyUsage,
        uint32 keyAttr,
        SecAccessRef initialAccess,
        SecKeyRef* keyRef);

/*!
    @function SecKeyGetCSSMKey
    @abstract Returns a pointer to the CSSM_KEY for the given key item reference.
    @param key A keychain key item reference. The key item must be of class type kSecAppleKeyItemClass.
    @param cssmKey On return, a pointer to a CSSM_KEY structure for the given key. This pointer remains valid until the key reference is released. The caller should not attempt to modify or free this data.
    @result A result code. See "Security Error Codes" (SecBase.h).
    @discussion  The CSSM_KEY is valid until the key item reference is released.
*/
OSStatus SecKeyGetCSSMKey(SecKeyRef key, const CSSM_KEY **cssmKey);

/*!
    @function SecKeyGetCSPHandle
    @abstract Returns the CSSM_CSP_HANDLE for the given key reference. The handle is valid until the key reference is released.
    @param keyRef A key reference.
    @param cspHandle On return, the CSSM_CSP_HANDLE for the given keychain.
    @result A result code. See "Security Error Codes" (SecBase.h).
*/
OSStatus SecKeyGetCSPHandle(SecKeyRef keyRef, CSSM_CSP_HANDLE *cspHandle);

/*!
    @function SecKeyGetCredentials
    @abstract For a given key, return a pointer to a CSSM_ACCESS_CREDENTIALS structure which will allow the key to be used.
    @param keyRef The key for which a credential is requested.
    @param operation The type of operation to be performed with this key. See "Authorization tag type" for defined operations (cssmtype.h).
    @param credentialType The type of credential requested.
    @param outCredentials On return, a pointer to a CSSM_ACCESS_CREDENTIALS structure. This pointer remains valid until the key reference is released. The caller should not attempt to modify or free this data.
    @result A result code. See "Security Error Codes" (SecBase.h).
*/
OSStatus SecKeyGetCredentials(
        SecKeyRef keyRef,
        CSSM_ACL_AUTHORIZATION_TAG operation,
        SecCredentialType credentialType,
        const CSSM_ACCESS_CREDENTIALS **outCredentials);

/*!
    @function SecKeyGetBlockSize
    @abstract Decrypt a block of ciphertext. 
    @param key The key for which the block length is requested.
    @result The block length of the key in bytes.
    @discussion If for example key is an RSA key the value returned by 
    this function is the size of the modulus.
 */
size_t SecKeyGetBlockSize(SecKeyRef key);


#if defined(__cplusplus)
}
#endif

#endif /* !_SECURITY_SECKEY_H_ */
