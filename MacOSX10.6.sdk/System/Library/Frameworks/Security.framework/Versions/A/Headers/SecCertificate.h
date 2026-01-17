/*
 * Copyright (c) 2002-2008 Apple Inc. All Rights Reserved.
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
	@header SecCertificate
	The functions provided in SecCertificate implement and manage a particular type of keychain item that represents a certificate.  You can store a certificate in a keychain, but a certificate can also be a transient object.
	
	You can use a certificate as a keychain item in most functions.
*/

#ifndef _SECURITY_SECCERTIFICATE_H_
#define _SECURITY_SECCERTIFICATE_H_

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFArray.h>
#include <CoreFoundation/CFData.h>
#include <CoreFoundation/CFDate.h>
#include <Security/SecBase.h>
#include <Security/cssmtype.h>
#include <Security/x509defs.h>
#include <AvailabilityMacros.h>

#if defined(__cplusplus)
extern "C" {
#endif


/*!
	@enum CertificateItemAttributes
	@abstract Indicates the type of a certificate item attribute.
	@constant kSecSubjectItemAttr Indicates a DER-encoded subject distinguished name.
	@constant kSecIssuerItemAttr Indicates a DER-encoded issuer distinguished name.
	@constant kSecSerialNumberItemAttr Indicates a DER-encoded certificate serial number (without the tag and length).
	@constant kSecPublicKeyHashItemAttr Indicates a public key hash.
	@constant kSecSubjectKeyIdentifierItemAttr Indicates a subject key identifier.
	@constant kSecCertTypeItemAttr Indicates a certificate type.
	@constant kSecCertEncodingItemAttr Indicates a certificate encoding.
*/
enum
{
    kSecSubjectItemAttr 			 = 'subj',
    kSecIssuerItemAttr 				 = 'issu',
    kSecSerialNumberItemAttr     	 = 'snbr',
    kSecPublicKeyHashItemAttr    	 = 'hpky',
    kSecSubjectKeyIdentifierItemAttr = 'skid',
	kSecCertTypeItemAttr		 	 = 'ctyp',
	kSecCertEncodingItemAttr	 	 = 'cenc'
};

/*!
	@function SecCertificateGetTypeID
	@abstract Returns the type identifier of SecCertificate instances.
	@result The CFTypeID of SecCertificate instances.
*/
CFTypeID SecCertificateGetTypeID(void);

#pragma mark ---- Certificate Operations ----

/*!
	@function SecCertificateCreateFromData
	@abstract Creates a certificate based on the input data, type, and encoding. 
    @param data A pointer to the certificate data.
    @param type The certificate type as defined in cssmtype.h.
    @param encoding The certificate encoding as defined in cssmtype.h.
	@param certificate On return, a reference to the newly created certificate.
    @result A result code. See "Security Error Codes" (SecBase.h).
*/
OSStatus SecCertificateCreateFromData(const CSSM_DATA *data, CSSM_CERT_TYPE type, CSSM_CERT_ENCODING encoding, SecCertificateRef *certificate);

/*!
	@function SecCertificateCreateWithData
	@abstract Create a certificate reference given its DER representation as a CFData.
    @param allocator CFAllocator to allocate the certificate data. Pass NULL to use the default allocator.
    @param certificate DER encoded X.509 certificate.
	@result On return, a reference to the certificate. Returns NULL if the passed-in data is not a valid DER-encoded X.509 certificate.
*/
SecCertificateRef SecCertificateCreateWithData(CFAllocatorRef allocator, CFDataRef data);

/*!
	@function SecCertificateAddToKeychain
	@abstract Adds a certificate to the specified keychain.
    @param certificate A reference to a certificate.
    @param keychain A reference to the keychain in which to add the certificate. Pass NULL to add the certificate to the default keychain.
    @result A result code. See "Security Error Codes" (SecBase.h).
	@discussion This function is successful only if the certificate was created using the SecCertificateCreateFromData function and the certificate has not yet been added to a keychain.
*/
OSStatus SecCertificateAddToKeychain(SecCertificateRef certificate, SecKeychainRef keychain);

/*!
	@function SecCertificateGetData
	@abstract Retrieves the data for a given certificate.
    @param certificate A reference to the certificate from which to retrieve the data.
    @param data On return, the CSSM_DATA structure pointed to by data is filled in. You must allocate the space for a CSSM_DATA structure before calling this function. This data pointer is only guaranteed to remain valid as long as the certificate remains unchanged and valid.
	@result A result code. See "Security Error Codes" (SecBase.h).
*/
OSStatus SecCertificateGetData(SecCertificateRef certificate, CSSM_DATA_PTR data);

/*!
	@function SecCertificateCopyData
	@abstract Returns the DER representation of an X.509 certificate.
    @param certificate A reference to a certificate.
	@result On return, a data reference containing the DER encoded representation of the X.509 certificate.
*/
CFDataRef SecCertificateCopyData(SecCertificateRef certificate);

/*!
	@function SecCertificateGetType
	@abstract Retrieves the type for a given certificate.
    @param certificate A reference to the certificate from which to obtain the type.
    @param certificateType On return, the certificate type of the certificate. Certificate types are defined in cssmtype.h.
	@result A result code. See "Security Error Codes" (SecBase.h).
*/
OSStatus SecCertificateGetType(SecCertificateRef certificate, CSSM_CERT_TYPE *certificateType);

/*!
    @function SecCertificateGetSubject
    @abstract Retrieves the subject name for a given certificate.
    @param certificate A reference to the certificate from which to obtain the subject name.
    @param subject On return, a pointer to a CSSM_X509_NAME struct which contains the subject's X.509 name (x509defs.h). This pointer remains valid until the certificate reference is released. The caller should not attempt to free this pointer.
    @result A result code. See "Security Error Codes" (SecBase.h).
    @discussion Prior to Mac OS X 10.5, this function did not return any output in the subject parameter. Your code should check the returned pointer value (in addition to the function result) before attempting to use it.
        For example:
        const CSSM_X509_NAME *subject = NULL;
        OSStatus status = SecCertificateGetSubject(certificate, &subject);
        if ( (status == noErr) && (subject != NULL) ) {
            // subject is valid
        }
*/
OSStatus SecCertificateGetSubject(SecCertificateRef certificate, const CSSM_X509_NAME **subject);

/*!
    @function SecCertificateGetIssuer
    @abstract Retrieves the issuer name for a given certificate.
    @param certificate A reference to the certificate from which to obtain the issuer name.
    @param issuer On return, a pointer to a CSSM_X509_NAME struct which contains the issuer's X.509 name (x509defs.h). This pointer remains valid until the certificate reference is released. The caller should not attempt to free this pointer.
    @result A result code. See "Security Error Codes" (SecBase.h).
    @discussion Prior to Mac OS X 10.5, this function did not return any output in the issuer parameter. Your code should check the returned pointer value (in addition to the function result) before attempting to use it.
        For example:
        const CSSM_X509_NAME *issuer = NULL;
        OSStatus status = SecCertificateGetIssuer(certificate, &issuer);
        if ( (status == noErr) && (issuer != NULL) ) {
            // issuer is valid
        }
*/
OSStatus SecCertificateGetIssuer(SecCertificateRef certificate, const CSSM_X509_NAME **issuer);

/*!
    @function SecCertificateGetCLHandle
    @abstract Retrieves the certificate library handle for a given certificate.
    @param certificate A reference to the certificate from which to obtain the certificate library handle.
    @param clHandle On return, the certificate library handle of the given certificate. This handle remains valid at least as long as the certificate does.
    @result A result code. See "Security Error Codes" (SecBase.h).
*/
OSStatus SecCertificateGetCLHandle(SecCertificateRef certificate, CSSM_CL_HANDLE *clHandle);

/*!
    @function SecCertificateGetAlgorithmID
    @abstract Retrieves the algorithm identifier for a given certificate.
    @param certificate A reference to the certificate from which to retrieve the algorithm identifier.
    @param algid On return, a pointer to a CSSM_X509_ALGORITHM_IDENTIFIER struct which identifies the algorithm for this certificate (x509defs.h). This pointer remains valid until the certificate reference is released. The caller should not attempt to free this pointer.
    @result A result code. See "Security Error Codes" (SecBase.h).
*/
OSStatus SecCertificateGetAlgorithmID(SecCertificateRef certificate, const CSSM_X509_ALGORITHM_IDENTIFIER **algid);

/*!
    @function SecCertificateCopyPublicKey
    @abstract Retrieves the public key for a given certificate.
    @param certificate A reference to the certificate from which to retrieve the public key.
    @param key On return, a reference to the public key for the specified certificate. Your code must release this reference by calling the CFRelease function.
    @result A result code. See "Security Error Codes" (SecBase.h).
*/
OSStatus SecCertificateCopyPublicKey(SecCertificateRef certificate, SecKeyRef *key);

/*!
    @function SecCertificateCopyCommonName
    @abstract Retrieves the common name of the subject of a given certificate.
    @param certificate A reference to the certificate from which to retrieve the common name.
    @param commonName On return, a reference to the common name. Your code must release this reference by calling the CFRelease function.
    @result A result code. See "Security Error Codes" (SecBase.h).
*/
OSStatus SecCertificateCopyCommonName(SecCertificateRef certificate, CFStringRef *commonName);

/*!
	@function SecCertificateCopySubjectSummary
	@abstract Returns a simple string which hopefully represents a human understandable summary.
    @param certificate  A reference to the certificate from which to derive the subject summary string.
    @discussion All the data in this string comes from the certificate itself, and thus it's in whatever language the certificate itself is in.
	@result On return, a reference to the subject summary string. Your code must release this reference by calling the CFRelease function.
*/
CFStringRef SecCertificateCopySubjectSummary(SecCertificateRef certificate);

/*!
    @function SecCertificateCopyEmailAddresses
    @abstract Returns an array of zero or more email addresses for the subject of a given certificate.
    @param certificate A reference to the certificate from which to retrieve the common name.
    @param emailAddresses On return, an array of zero or more CFStringRef elements corresponding to each email address found. Your code must release this array reference by calling the CFRelease function.
    @result A result code. See "Security Error Codes" (SecBase.h).
*/
OSStatus SecCertificateCopyEmailAddresses(SecCertificateRef certificate, CFArrayRef *emailAddresses);

/*!
    @function SecCertificateCopyPreference
    @abstract Returns the preferred certificate for the specified name and key usage. If a preferred certificate does not exist for the specified name and key usage, NULL is returned.
    @param name A string containing an email address (RFC822) or other name for which a preferred certificate is requested.
    @param keyUsage A key usage value, as defined in cssmtype.h. Pass 0 to ignore this parameter.
    @param certificate On return, a reference to the preferred certificate, or NULL if none was found. You are responsible for releasing this reference by calling the CFRelease function.
    @result A result code. See "Security Error Codes" (SecBase.h).
    @discussion This function will typically be used to obtain the preferred encryption certificate for an email recipient.
*/
OSStatus SecCertificateCopyPreference(CFStringRef name, CSSM_KEYUSE keyUsage, SecCertificateRef *certificate);

/*!
    @function SecCertificateSetPreference
    @abstract Sets the preferred certificate for a specified name, key usage, and date.
    @param certificate A reference to the certificate which will be preferred.
    @param name A string containing an email address (RFC822) or other name for which a preferred certificate will be associated.
    @param keyUsage A key usage value, as defined in cssmtype.h. Pass 0 to avoid specifying a particular key usage.
    @param date (optional) A date reference. If supplied, the preferred certificate will be changed only if this date is later than the currently saved setting. Pass NULL if this preference should not be restricted by date.
    @result A result code. See "Security Error Codes" (SecBase.h).
    @discussion This function will typically be used to set the preferred encryption certificate for an email recipient, either manually (when encrypting email to a recipient) or automatically upon receipt of encrypted email.
*/
OSStatus SecCertificateSetPreference(SecCertificateRef certificate, CFStringRef name, CSSM_KEYUSE keyUsage, CFDateRef date);


#if defined(__cplusplus)
}
#endif

#endif /* !_SECURITY_SECCERTIFICATE_H_ */
