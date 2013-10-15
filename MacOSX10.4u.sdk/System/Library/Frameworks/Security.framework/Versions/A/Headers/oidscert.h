/*
 * Copyright (c) 1999-2004 Apple Computer, Inc. All Rights Reserved.
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
 *
 * oidscert.h -- Object Identifiers for X509 Certificate Library
 */

#ifndef _OIDSCERT_H_
#define _OIDSCERT_H_  1

#include <Security/cssmconfig.h>
#include <Security/cssmtype.h>
#include <Security/oidsbase.h>

#ifdef __cplusplus
extern "C" {
#endif

#define INTEL_X509V3_CERT_R08 INTEL_SEC_FORMATS, 1, 1
#define INTEL_X509V3_CERT_R08_LENGTH INTEL_SEC_FORMATS_LENGTH + 2

/* Prefix for defining Certificate Extension field OIDs */
#define INTEL_X509V3_CERT_PRIVATE_EXTENSIONS INTEL_X509V3_CERT_R08, 50
#define INTEL_X509V3_CERT_PRIVATE_EXTENSIONS_LENGTH INTEL_X509V3_CERT_R08_LENGTH + 1

/* Prefix for defining signature field OIDs */
#define INTEL_X509V3_SIGN_R08 INTEL_SEC_FORMATS, 3, 2
#define INTEL_X509V3_SIGN_R08_LENGTH INTEL_SEC_FORMATS_LENGTH + 2

/* Suffix specifying format or representation of a field value                                      */
/* Note that if a format suffix is not specified, a flat data representation is implied. */

#define INTEL_X509_C_DATATYPE					1
#define INTEL_X509_LDAPSTRING_DATATYPE		2

/* Certificate OIDS */
extern const CSSM_OID

	CSSMOID_X509V3SignedCertificate,
	CSSMOID_X509V3SignedCertificateCStruct,
	CSSMOID_X509V3Certificate,
	CSSMOID_X509V3CertificateCStruct,
	CSSMOID_X509V1Version,
	CSSMOID_X509V1SerialNumber,
	CSSMOID_X509V1IssuerName,			// normalized & encoded
	CSSMOID_X509V1IssuerNameStd,		// encoded
	CSSMOID_X509V1IssuerNameCStruct,	// CSSM_X509_NAME
	CSSMOID_X509V1IssuerNameLDAP,
	CSSMOID_X509V1ValidityNotBefore,
	CSSMOID_X509V1ValidityNotAfter,
	CSSMOID_X509V1SubjectName,			// normalized & encoded
	CSSMOID_X509V1SubjectNameStd,		// encoded
	CSSMOID_X509V1SubjectNameCStruct,	// CSSM_X509_NAME
	CSSMOID_X509V1SubjectNameLDAP,
	CSSMOID_CSSMKeyStruct,
	CSSMOID_X509V1SubjectPublicKeyCStruct,
	CSSMOID_X509V1SubjectPublicKeyAlgorithm,
	CSSMOID_X509V1SubjectPublicKeyAlgorithmParameters,
	CSSMOID_X509V1SubjectPublicKey,
	CSSMOID_X509V1CertificateIssuerUniqueId,
	CSSMOID_X509V1CertificateSubjectUniqueId,
	CSSMOID_X509V3CertificateExtensionsStruct,
	CSSMOID_X509V3CertificateExtensionsCStruct,
	CSSMOID_X509V3CertificateNumberOfExtensions,
	CSSMOID_X509V3CertificateExtensionStruct,
	CSSMOID_X509V3CertificateExtensionCStruct,
	CSSMOID_X509V3CertificateExtensionId,
	CSSMOID_X509V3CertificateExtensionCritical,
	CSSMOID_X509V3CertificateExtensionType,
	CSSMOID_X509V3CertificateExtensionValue,
	
	/* Signature OID Fields */
	CSSMOID_X509V1SignatureStruct,
	CSSMOID_X509V1SignatureCStruct,
	CSSMOID_X509V1SignatureAlgorithm,
	CSSMOID_X509V1SignatureAlgorithmTBS,
	CSSMOID_X509V1SignatureAlgorithmParameters,
	CSSMOID_X509V1Signature,
	
	/* Extension OID Fields */
	CSSMOID_SubjectSignatureBitmap,
	CSSMOID_SubjectPicture,
	CSSMOID_SubjectEmailAddress,
	CSSMOID_UseExemptions;

/*** 
 *** Apple addenda
 ***/
 
/* 
 * Standard Cert and CRL extensions.
 */
extern const CSSM_OID
	CSSMOID_SubjectDirectoryAttributes,
	CSSMOID_SubjectKeyIdentifier,
	CSSMOID_KeyUsage,
	CSSMOID_PrivateKeyUsagePeriod,
	CSSMOID_SubjectAltName,
	CSSMOID_IssuerAltName,
	CSSMOID_BasicConstraints,
	CSSMOID_CrlNumber,
	CSSMOID_CrlReason,
	CSSMOID_HoldInstructionCode,
	CSSMOID_InvalidityDate,
	CSSMOID_DeltaCrlIndicator,
	CSSMOID_IssuingDistributionPoint,
	CSSMOID_IssuingDistributionPoints,
	CSSMOID_CertIssuer,
	CSSMOID_NameConstraints,
	CSSMOID_CrlDistributionPoints,
	CSSMOID_CertificatePolicies,
	CSSMOID_PolicyMappings,
	CSSMOID_PolicyConstraints,
	CSSMOID_AuthorityKeyIdentifier,
	CSSMOID_ExtendedKeyUsage,
	CSSMOID_AuthorityInfoAccess,
	CSSMOID_SubjectInfoAccess,
	CSSMOID_ExtendedKeyUsageAny,
	CSSMOID_ServerAuth,
	CSSMOID_ClientAuth,
	CSSMOID_ExtendedUseCodeSigning,
	CSSMOID_EmailProtection,
	CSSMOID_TimeStamping,
	CSSMOID_OCSPSigning,
	CSSMOID_EKU_IPSec,
	CSSMOID_DOTMAC_CERT_EXTENSION,
	CSSMOID_DOTMAC_CERT_IDENTITY,
	CSSMOID_DOTMAC_CERT_EMAIL_SIGN,
	CSSMOID_DOTMAC_CERT_EMAIL_ENCRYPT,
	CSSMOID_APPLE_CERT_POLICY,
	CSSMOID_DOTMAC_CERT_POLICY,
	CSSMOID_APPLE_EKU_CODE_SIGNING, 
	CSSMOID_APPLE_EKU_CODE_SIGNING_DEV,
	CSSMOID_APPLE_EKU_ICHAT_SIGNING,
	CSSMOID_APPLE_EKU_ICHAT_ENCRYPTION
;
	
/*
 * Netscape extensions.
 */
extern const CSSM_OID	
	CSSMOID_NetscapeCertType,
	CSSMOID_NetscapeCertSequence,
	CSSMOID_NetscapeSGC;

extern const CSSM_OID CSSMOID_MicrosoftSGC;

/*
 * Field values for CSSMOID_NetscapeCertType, a bit string.
 * Assumes a 16 bit field, even though currently only 8 bits
 * are defined. 
 */
#define CE_NCT_SSL_Client	0x8000
#define CE_NCT_SSL_Server	0x4000
#define CE_NCT_SMIME		0x2000
#define CE_NCT_ObjSign		0x1000
#define CE_NCT_Reserved		0x0800
#define CE_NCT_SSL_CA		0x0400
#define CE_NCT_SMIME_CA		0x0200
#define CE_NCT_ObjSignCA	0x0100

#ifdef __cplusplus
}
#endif

#endif /* _OIDSCERT_H_ */
