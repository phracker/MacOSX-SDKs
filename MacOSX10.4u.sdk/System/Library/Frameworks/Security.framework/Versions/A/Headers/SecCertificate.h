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
	@header SecCertificate
	The functions provided in SecCertificate implement and manage a particular type of keychain item that represents a certificate.  You can store a certificate in a keychain, but a certificate can also be a transient object.
	
	You can use a certificate as a keychain item in most functions.
*/

#ifndef _SECURITY_SECCERTIFICATE_H_
#define _SECURITY_SECCERTIFICATE_H_

#include <Security/SecBase.h>
#include <Security/cssmtype.h>

// @@@ Here for X509 specific defines
#include <Security/x509defs.h>


#if defined(__cplusplus)
extern "C" {
#endif


/*!
	@enum CertificateItemAttributes
	@abstract Indicates the type of a certificate item attribute.
	@constant kSecSubjectItemAttr Indicates a DER-encoded subject distinguished name.
	@constant kSecIssuerItemAttr Indicates a DER-encoded issuer distinguished name.
	@constant kSecSerialNumberItemAttr Indicates a DER-encoded certificate serial number.
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

#pragma mark ÑÑÑÑ Certificate Operations ÑÑÑÑ

/*!
	@function SecCertificateCreateFromData
	@abstract Creates a certificate based on the input data, type, and encoding. 
    @param data A pointer to the certificate data.
    @param type The certificate type as defined in cssmtype.h.
    @param encoding The certificate encoding as defined in cssmtype.h.
	@param certificate On return, a pointer to the newly created certificate reference.
    @result A result code.  See "Security Error Codes" (SecBase.h).
*/
OSStatus SecCertificateCreateFromData(const CSSM_DATA *data, CSSM_CERT_TYPE type, CSSM_CERT_ENCODING encoding, SecCertificateRef *certificate);

/*!
	@function SecCertificateAddToKeychain
	@abstract Adds a certificate to the keychain specified.
    @param certificate A reference to the certificate to add to the keychain.
    @param keychain A reference to the keychain to which to add the certificate. Pass NULL to add the certificate to the default keychain.
    @result A result code.  See "Security Error Codes" (SecBase.h).
	@discussion This function call only works if the certificate was created using the SecCertificateCreateFromData function and the certificate has not yet been added to a keychain.
*/
OSStatus SecCertificateAddToKeychain(SecCertificateRef certificate, SecKeychainRef keychain);

/*!
	@function SecCertificateGetData
	@abstract Retrieves the data for a given certificate.
    @param certificate A reference to the certificate from which to retrieve the data.
    @param data On return, a pointer to the data for the certificate specified.  The caller must allocate the space for a CSSM_DATA structure before calling this function.  This data pointer is only guaranteed to remain valid as long as the certificate remains unchanged and valid.
	@result A result code.  See "Security Error Codes" (SecBase.h).
*/
OSStatus SecCertificateGetData(SecCertificateRef certificate, CSSM_DATA_PTR data);

/*!
	@function SecCertificateGetType
	@abstract Retrieves the type for a given certificate.
    @param certificate A reference to the certificate from which to obtain the type.
    @param certificateType On return, a pointer to the certificate type of the certificate specified. Certificate types are defined in cssmtype.h
	@result A result code.  See "Security Error Codes" (SecBase.h).
*/
OSStatus SecCertificateGetType(SecCertificateRef certificate, CSSM_CERT_TYPE *certificateType);

/*!
	@function SecCertificateGetSubject
	@abstract Retrieves the subject for a given certificate.
    @param certificate A reference to the certificate from which to obtain the subject.
    @param subject On return, a pointer to the subject of the given certificate.
	@result A result code.  See "Security Error Codes" (SecBase.h).
*/
OSStatus SecCertificateGetSubject(SecCertificateRef certificate, CSSM_X509_NAME *subject);

/*!
	@function SecCertificateGetIssuer
	@abstract Retrieves the issuer of a given certificate.
    @param certificate A reference to the certificate from which to obtain the issuer.
    @param issuer On return, a pointer to the issuer of the given certificate.
	@result A result code.  See "Security Error Codes" (SecBase.h).
*/
OSStatus SecCertificateGetIssuer(SecCertificateRef certificate, CSSM_X509_NAME *issuer);

/*!
	@function SecCertificateGetCLHandle
	@abstract Retrieves the certificate library handle for a given certificate.
    @param certificate A reference to the certificate from which to obtain the certificate library handle.
    @param clHandle On return, a pointer to the certificate library handle of the given certificate.  This handle remains valid at least as long as the certificate does.
	@result A result code.  See "Security Error Codes" (SecBase.h).
*/
OSStatus SecCertificateGetCLHandle(SecCertificateRef certificate, CSSM_CL_HANDLE *clHandle);


#if defined(__cplusplus)
}
#endif

#endif /* !_SECURITY_SECCERTIFICATE_H_ */
