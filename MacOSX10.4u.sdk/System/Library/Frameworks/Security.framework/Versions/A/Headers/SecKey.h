/*
 * Copyright (c) 2002-2004 Apple Computer, Inc. All Rights Reserved.
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
	The functions provided in SecKey implement a particular type of SecKeychainItem which represents a key.  SecKeys might be stored in a SecKeychain, but can also be used as transient object representing keys.

	Most SecKeychainItem* functions will work on an SecKeyRef.
*/

#ifndef _SECURITY_SECKEY_H_
#define _SECURITY_SECKEY_H_

#include <Security/SecBase.h>
#include <Security/cssmtype.h>


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
	@function SecKeyGetTypeID
	@abstract Returns the type identifier of SecKey instances.
	@result The CFTypeID of SecKey instances.
*/
CFTypeID SecKeyGetTypeID(void);

/*!
	@function SecKeyCreatePair
	@abstract Creates an asymmetric key pair and stores it in the keychain specified by the keychain parameter.
	@param keychainRef A reference to the keychain in which to store the private and public key items. Specify NULL for the default keychain.
    @param algorithm An algorithm for the key pair.  This parameter is ignored if contextHandle is non 0.
    @param keySizeInBits A key size for the key pair.  This parameter is ignored if contextHandle is non 0.
	@param contextHandle An optional CSSM_CC_HANDLE or 0.  If this argument is not 0 the algorithm and keySizeInBits parameters are ignored.  If extra parameters are need to generate a key (some algortihms require this) you should create a context using CSSM_CSP_CreateKeyGenContext(), using the CSPHandle obtained by calling SecKeychainGetCSPHandle(). Then use CSSM_UpdateContextAttributes() to add additional parameters and dispose of the context using CSSM_DeleteContext after calling this function.
	@param publicKeyUsage A bit mask indicating all permitted uses for the new public key. The bit mask values are defined in cssmtype.h
    @param publicKeyAttr A bit mask defining attribute values for the new public key. The bit mask values are equivalent to a CSSM_KEYATTR_FLAGS and are defined in cssmtype.h
    @param privateKeyUsage A bit mask indicating all permitted uses for the new private key. The bit mask values are defined in cssmtype.h
    @param privateKeyAttr A bit mask defining attribute values for the new private key. The bit mask values are equivalent to a CSSM_KEYATTR_FLAGS and are defined in cssmtype.h
    @param initialAccess A SecAccess object that determines the initial access rights to the private key.  The public key is given an any/any acl by default.
    @param publicKey Optional output pointer to the keychain item reference of the imported public key. Use the SecKeyGetCSSMKey function to obtain the CSSM_KEY. The caller must call CFRelease on this value if it is returned.
    @param privateKey Optional output pointer to the keychain item reference of the imported private key. Use the SecKeyGetCSSMKey function to obtain the CSSM_KEY. The caller must call CFRelease on this value if it is returned.
	@result A result code.  See "Security Error Codes" (SecBase.h).
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
	@function SecKeyGetCSSMKey
	@abstract Returns a pointer to the CSSM_KEY for the given key item reference.
    @param key A keychain key item reference. The key item must be of class type kSecAppleKeyItemClass.
    @param cssmKey A pointer to a CSSM_KEY structure for the given key. The caller should not modify or free this data as it is owned by the library.
    @result A result code.  See "Security Error Codes" (SecBase.h).
	@discussion  The CSSM_KEY is valid until the key item reference is released.
*/
OSStatus SecKeyGetCSSMKey(SecKeyRef key, const CSSM_KEY **cssmKey);


#if defined(__cplusplus)
}
#endif

#endif /* !_SECURITY_SECKEY_H_ */
