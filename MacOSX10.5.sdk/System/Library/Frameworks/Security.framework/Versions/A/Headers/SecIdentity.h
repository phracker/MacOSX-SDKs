/*
 * Copyright (c) 2002-2006 Apple Computer, Inc. All Rights Reserved.
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
	@header SecIdentity
	The functions provided in SecIdentity implement a convenient way to match private keys with certificates.
*/

#ifndef _SECURITY_SECIDENTITY_H_
#define _SECURITY_SECIDENTITY_H_

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFArray.h>
#include <Security/SecBase.h>
#include <Security/cssmtype.h>
#include <AvailabilityMacros.h>

#if defined(__cplusplus)
extern "C" {
#endif

/*!
	@function SecIdentityGetTypeID
	@abstract Returns the type identifier of SecIdentity instances.
	@result The CFTypeID of SecIdentity instances.
*/
CFTypeID SecIdentityGetTypeID(void);

/*!
	@function SecIdentityCreateWithCertificate
    @abstract Creates a new identity reference for the given certificate, assuming the associated private key is in one of the specified keychains.
    @param keychainOrArray A reference to an array of keychains to search, a single keychain, or NULL to search the user's default keychain search list.
	@param certificateRef A certificate reference.
    @param identityRef On return, an identity reference. You are responsible for releasing this reference by calling the CFRelease function.
    @result A result code. See "Security Error Codes" (SecBase.h).
*/
OSStatus SecIdentityCreateWithCertificate(
			CFTypeRef keychainOrArray,
			SecCertificateRef certificateRef,
            SecIdentityRef *identityRef);

/*!
	@function SecIdentityCopyCertificate
    @abstract Returns a reference to a certificate for the given identity reference.
    @param identityRef An identity reference.
	@param certificateRef On return, a reference to the found certificate. You are responsible for releasing this reference by calling the CFRelease function.
    @result A result code. See "Security Error Codes" (SecBase.h).
*/
OSStatus SecIdentityCopyCertificate(
            SecIdentityRef identityRef, 
            SecCertificateRef *certificateRef);

/*!
	@function SecIdentityCopyPrivateKey
    @abstract Returns the private key associated with an identity.
    @param identityRef An identity reference.
	@param privateKeyRef On return, a reference to the private key for the given identity. You are responsible for releasing this reference by calling the CFRelease function.
    @result A result code. See "Security Error Codes" (SecBase.h).
*/
OSStatus SecIdentityCopyPrivateKey(
            SecIdentityRef identityRef, 
            SecKeyRef *privateKeyRef);

/*!
    @function SecIdentityCopyPreference
    @abstract Returns the preferred identity for the specified name and key usage, optionally limiting the result to an identity issued by a certificate whose subject is one of the distinguished names in validIssuers. If a preferred identity does not exist, NULL is returned.
    @param name A string containing a URI, RFC822 email address, DNS hostname, or other name which uniquely identifies the service requiring an identity.
    @param keyUsage A key usage value, as defined in cssmtype.h. Pass 0 to ignore this parameter.
    @param validIssuers (optional) An array of CFDataRef instances whose contents are the subject names of allowable issuers, as returned by a call to SSLCopyDistinguishedNames (SecureTransport.h). Pass NULL if any issuer is allowed.
    @param identity On return, a reference to the preferred identity, or NULL if none was found. You are responsible for releasing this reference by calling the CFRelease function.
    @result A result code. See "Security Error Codes" (SecBase.h).
    @discussion If a preferred identity has not been set for the supplied name, the returned identity reference will be NULL. Your code should then typically perform a search for possible identities, using SecIdentitySearchCreate and SecIdentitySearchCopyNext (SecIdentitySearch.h) or SecKeychainCopyMatchingItems (SecKeychain.h), allowing the user to choose from a list if more than one is found.
*/
OSStatus SecIdentityCopyPreference(CFStringRef name, CSSM_KEYUSE keyUsage, CFArrayRef validIssuers, SecIdentityRef *identity);

/*!
    @function SecIdentitySetPreference
    @abstract Sets the preferred identity for the specified name and key usage.
    @param identity A reference to the identity which will be preferred.
    @param name A string containing a URI, RFC822 email address, DNS hostname, or other name which uniquely identifies a service requiring this identity.
    @param keyUsage A key usage value, as defined in cssmtype.h. Pass 0 to specify any key usage.
    @result A result code. See "Security Error Codes" (SecBase.h).
*/
OSStatus SecIdentitySetPreference(SecIdentityRef identity, CFStringRef name, CSSM_KEYUSE keyUsage);

/*!
	@function	SecIdentityCopySystemIdentity
	@abstract	Obtain the system-wide SecIdentityRef associated with 
				a specified domain.
	@param		domain  Identifies the SecIdentityRef to be obtained, typically
						in the form "com.apple.subdomain...". 
	@param		idRef	On return, the system SecIdentityRef assicated with 
						the specified domain. Caller must CFRelease this when 
						finished with it.	
	@param		actualDomain (optional) The actual domain name of the 
						the returned identity is returned here. This
						may be different from the requested domain. 
    @result		A result code.  See "Security Error Codes" (SecBase.h).
	@discussion	If no system SecIdentityRef exists for the specified
				domain, a domain-specific alternate may be returned
				instead, typically (but not exclusively) the 
				kSecIdentityDomainDefault SecIdentityRef. 
 */
OSStatus SecIdentityCopySystemIdentity(
   CFStringRef domain,          
   SecIdentityRef *idRef,
   CFStringRef *actualDomain); /* optional */

/*!
	@function	SecIdentitySetSystemIdentity
	@abstract	Assign the supplied SecIdentityRef to the specified
				domain.
	@param		domain Identifies the domain to which the specified 
				SecIdentityRef will be assigned.
	@param		idRef (optional) The identity to be assigned to the specified 
				domain. Pass NULL to delete a possible entry for the specified
				domain; in this case, it is not an error if no identity
				exists for the specified domain. 
    @result		A result code.  See "Security Error Codes" (SecBase.h).
	@discussion	The caller must be running as root.
*/
OSStatus SecIdentitySetSystemIdentity(
   CFStringRef domain,     
   SecIdentityRef idRef);


/*
 * Defined system identity domains.
 */

/*!
	@const kSecIdentityDomainDefault The system-wide default identity.
 */
extern const CFStringRef kSecIdentityDomainDefault;

/*!
	@const kSecIdentityDomainKerberosKDC Kerberos KDC identity.
*/
extern const CFStringRef kSecIdentityDomainKerberosKDC;

#if defined(__cplusplus)
}
#endif

#endif /* !_SECURITY_SECIDENTITY_H_ */
