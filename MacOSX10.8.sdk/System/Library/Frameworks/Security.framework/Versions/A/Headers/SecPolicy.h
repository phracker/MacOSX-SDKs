/*
 * Copyright (c) 2002-2010 Apple Inc. All Rights Reserved.
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
    @header SecPolicy
    The functions provided in SecPolicy.h provide an interface to various
	X.509 certificate trust policies.
*/

#ifndef _SECURITY_SECPOLICY_H_
#define _SECURITY_SECPOLICY_H_

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFDictionary.h>
#include <Security/SecBase.h>
#include <Security/cssmtype.h>

#if defined(__cplusplus)
extern "C" {
#endif

/*!
    @enum Policy Constants
    @discussion Predefined constants used to specify a policy.
	@constant kSecPolicyAppleX509Basic
	@constant kSecPolicyAppleSSL
	@constant kSecPolicyAppleSMIME
	@constant kSecPolicyAppleEAP
	@constant kSecPolicyAppleIPsec
	@constant kSecPolicyAppleiChat
	@constant kSecPolicyApplePKINITClient
	@constant kSecPolicyApplePKINITServer
	@constant kSecPolicyAppleCodeSigning
	@constant kSecPolicyMacAppStoreReceipt
	@constant kSecPolicyAppleIDValidation
	@constant kSecPolicyAppleTimeStamping
*/
extern CFTypeRef kSecPolicyAppleX509Basic
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern CFTypeRef kSecPolicyAppleSSL
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern CFTypeRef kSecPolicyAppleSMIME
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern CFTypeRef kSecPolicyAppleEAP
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern CFTypeRef kSecPolicyAppleIPsec
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern CFTypeRef kSecPolicyAppleiChat
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern CFTypeRef kSecPolicyApplePKINITClient
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern CFTypeRef kSecPolicyApplePKINITServer
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern CFTypeRef kSecPolicyAppleCodeSigning
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern CFTypeRef kSecPolicyMacAppStoreReceipt
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern CFTypeRef kSecPolicyAppleIDValidation
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern CFTypeRef kSecPolicyAppleTimeStamping
    __OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_NA);

/*!
    @enum Policy Value Constants
    @discussion Predefined property key constants used to get or set values in
        a dictionary for a policy instance.

        All policies will have the following read-only value:
            kSecPolicyOid       (the policy object identifier)

        Additional policy values which your code can optionally set:
            kSecPolicyName      (name which must be matched)
            kSecPolicyClient	(evaluate for client, rather than server)

        Policy values may also specify CFBooleanRef key usage constraints:
            kSecPolicyKU_DigitalSignature
            kSecPolicyKU_NonRepudiation
            kSecPolicyKU_KeyEncipherment
            kSecPolicyKU_DataEncipherment
            kSecPolicyKU_KeyAgreement
            kSecPolicyKU_KeyCertSign
            kSecPolicyKU_CRLSign
            kSecPolicyKU_EncipherOnly
            kSecPolicyKU_DecipherOnly
            
        Note that these policy values cover certificate-level purpose
        definitions, in contrast to the key-level definitions in
        SecItem.h. For example, a key in a certificate might be
        acceptable for CRL signing, but not NonRepudiation. In either
        case, this key would definitely have (via SecItem.h) the ability
        to sign; it is the *context* of signing that is defined further
        in these policy constants. Similarly, a key might be able to do
        both encryption and decryption, but the certificate in which it
        resides might have a decipher-only certificate policy in
        certificate A, but not in certificate B. These policy values
        refine the key's attributes within the context of the
        certificate.
        
        They correspond to values defined in RFC 5280, section 4.2.1.3
        (Key Usage) which define the purpose of a key contained in a
        certificate, in contrast to section 4.1.2.7 which define what a
        key is capable of.
 
    @constant kSecPolicyOid Specifies the policy OID (value is a CFStringRef)
    @constant kSecPolicyName Specifies a CFStringRef containing a name which
        must be matched in the certificate to satisfy this policy. For SSL/TLS,
        this specifies the server name which must match the common name of the
        certificate. For S/MIME, this specifies the RFC822 email address.
    @constant kSecPolicyClient Specifies a CFBooleanRef value that indicates
        this evaluation should be for a client certificate. If not set (or
        false), the policy evaluates the certificate for the server.
    @constant kSecPolicyKU_DigitalSignature Specifies that the certificate must
        have a key usage that allows it to be used for signing.
    @constant kSecPolicyKU_NonRepudiation Specifies that the certificate must
        have a key usage that allows it to be used for non-repudiation.
    @constant kSecPolicyKU_KeyEncipherment Specifies that the certificate must
        have a key usage that allows it to be used for key encipherment.
    @constant kSecPolicyKU_DataEncipherment Specifies that the certificate must
        have a key usage that allows it to be used for data encipherment.
    @constant kSecPolicyKU_KeyAgreement Specifies that the certificate must
        have a key usage that allows it to be used for key agreement.
    @constant kSecPolicyKU_KeyCertSign Specifies that the certificate must
        have a key usage that allows it to be used for signing certificates.
    @constant kSecPolicyKU_CRLSign Specifies that the certificate must
        have a key usage that allows it to be used for signing CRLs.
    @constant kSecPolicyKU_EncipherOnly Specifies that the certificate must
        have a key usage that permits it to be used for encryption only.
    @constant kSecPolicyKU_DecipherOnly Specifies that the certificate must
        have a key usage that permits it to be used for decryption only.
*/
extern CFTypeRef kSecPolicyOid
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern CFTypeRef kSecPolicyName
	__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern CFTypeRef kSecPolicyClient
	__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);

extern CFTypeRef kSecPolicyKU_DigitalSignature
	__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern CFTypeRef kSecPolicyKU_NonRepudiation
	__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern CFTypeRef kSecPolicyKU_KeyEncipherment
	__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern CFTypeRef kSecPolicyKU_DataEncipherment
	__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern CFTypeRef kSecPolicyKU_KeyAgreement
	__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern CFTypeRef kSecPolicyKU_KeyCertSign
	__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern CFTypeRef kSecPolicyKU_CRLSign
	__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern CFTypeRef kSecPolicyKU_EncipherOnly
	__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern CFTypeRef kSecPolicyKU_DecipherOnly
	__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);


/*!
    @function SecPolicyGetTypeID
    @abstract Returns the type identifier of SecPolicy instances.
    @result The CFTypeID of SecPolicy instances.
*/
CFTypeID SecPolicyGetTypeID(void)
    __OSX_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_2_0);

/*!
    @function SecPolicyGetOID
    @abstract Returns a policy's object identifier.
    @param policyRef A policy reference.
    @param oid On return, a pointer to the policy's object identifier.
    @result A result code. See "Security Error Codes" (SecBase.h).
	@discussion This function is deprecated in Mac OS X 10.7 and later;
	use SecPolicyCopyProperties instead.
*/
OSStatus SecPolicyGetOID(SecPolicyRef policyRef, CSSM_OID *oid)
	DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
    @function SecPolicyGetValue
    @abstract Returns a policy's value.
    @param policyRef A policy reference.
    @param value On return, a pointer to the policy's value.
    @result A result code. See "Security Error Codes" (SecBase.h).
	@discussion This function is deprecated in Mac OS X 10.7 and later;
	use SecPolicyCopyProperties instead.
*/
OSStatus SecPolicyGetValue(SecPolicyRef policyRef, CSSM_DATA *value)
	DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
    @function SecPolicyCopyProperties
    @abstract Returns a dictionary of this policy's properties.
    @param policyRef A policy reference.
    @result A properties dictionary. See "Policy Value Constants" for a list
    of currently defined property keys. It is the caller's responsibility to
    CFRelease this reference when it is no longer needed.
    @result A result code. See "Security Error Codes" (SecBase.h).
	@discussion This function returns the properties for a policy, as set by the
	policy's construction function or by a prior call to SecPolicySetProperties.
*/
CFDictionaryRef SecPolicyCopyProperties(SecPolicyRef policyRef)
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);

/*!
    @function SecPolicySetValue
    @abstract Sets a policy's value.
    @param policyRef A policy reference.
    @param value The value to be set into the policy object, replacing any
	previous value.
    @result A result code. See "Security Error Codes" (SecBase.h).
	@discussion This function is deprecated in Mac OS X 10.7 and later;
	use SecPolicySetProperties instead.
*/
OSStatus SecPolicySetValue(SecPolicyRef policyRef, const CSSM_DATA *value)
	DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
    @function SecPolicySetProperties
    @abstract Sets a policy's properties.
    @param policyRef A policy reference.
    @param properties A properties dictionary. See "Policy Value Constants"
    for a list of currently defined property keys. This dictionary replaces the
    policy's existing properties, if any. Note that the policy OID (specified
    by kSecPolicyOid) is a read-only property of the policy and cannot be set.
    @result A result code. See "Security Error Codes" (SecBase.h).
*/
OSStatus SecPolicySetProperties(SecPolicyRef policyRef,
	CFDictionaryRef properties)
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);

/*!
    @function SecPolicyGetTPHandle
    @abstract Returns the CSSM trust policy handle for the given policy.
    @param policyRef A policy reference.
    @param tpHandle On return, a pointer to a value of type CSSM_TP_HANDLE.
    @result A result code. See "Security Error Codes" (SecBase.h).
	@discussion This function is deprecated in Mac OS X 10.7 and later.
*/
OSStatus SecPolicyGetTPHandle(SecPolicyRef policyRef, CSSM_TP_HANDLE *tpHandle)
	DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
    @function SecPolicyCreateBasicX509
    @abstract Returns a policy object for the default X.509 policy.
    @result A policy object. The caller is responsible for calling CFRelease
	on this when it is no longer needed.
*/
SecPolicyRef SecPolicyCreateBasicX509(void)
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);

/*!
    @function SecPolicyCreateSSL
    @abstract Returns a policy object for evaluating SSL certificate chains.
	@param server Passing true for this parameter creates a policy for SSL
	server certificates.
	@param hostname (Optional) If present, the policy will require the specified
	hostname to match the hostname in the leaf certificate.
    @result A policy object. The caller is responsible for calling CFRelease
	on this when it is no longer needed.
*/
SecPolicyRef SecPolicyCreateSSL(Boolean server, CFStringRef hostname)
    __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);

/*!
	@function SecPolicyCreateWithOID
	@abstract Returns a policy object based on an object identifier for the
	policy type. See the "Policy Constants" section for a list of defined
	policy object identifiers.
    @param policyOID The OID of the desired policy.
	@result The returned policy reference, or NULL if the policy could not be
	created.
*/
SecPolicyRef SecPolicyCreateWithOID(CFTypeRef policyOID)
    __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_2_0);


#if defined(__cplusplus)
}
#endif

#endif /* !_SECURITY_SECPOLICY_H_ */
