/*
 * Copyright (c) 2002 Apple Computer, Inc. All Rights Reserved.
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
