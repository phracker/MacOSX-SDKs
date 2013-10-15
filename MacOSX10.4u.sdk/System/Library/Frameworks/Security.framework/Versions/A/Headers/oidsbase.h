/*
 * Copyright (c) 1999-2001,2003-2004 Apple Computer, Inc. All Rights Reserved.
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
 * oidsbase.h -- Basic Object Identifier Macros and Data Types.
 */

#ifndef _OIDSBASE_H_
#define _OIDSBASE_H_  1

#ifdef __cplusplus
extern "C" {
#endif

/* Intel CSSM */

#define INTEL 96, 134, 72, 1, 134, 248, 77
#define INTEL_LENGTH 7

#define INTEL_CDSASECURITY INTEL, 2
#define INTEL_CDSASECURITY_LENGTH (INTEL_LENGTH + 1)

#define INTEL_SEC_FORMATS INTEL_CDSASECURITY, 1
#define INTEL_SEC_FORMATS_LENGTH (INTEL_CDSASECURITY_LENGTH + 1)

#define INTEL_SEC_ALGS INTEL_CDSASECURITY, 2, 5
#define INTEL_SEC_ALGS_LENGTH (INTEL_CDSASECURITY_LENGTH + 2)

#define INTEL_SEC_OBJECT_BUNDLE INTEL_SEC_FORMATS, 4
#define INTEL_SEC_OBJECT_BUNDLE_LENGTH (INTEL_SEC_FORMATS_LENGTH + 1)

#define INTEL_CERT_AND_PRIVATE_KEY_2_0 INTEL_SEC_OBJECT_BUNDLE, 1
#define INTEL_CERT_AND_PRIVATE_KEY_2_0_LENGTH (INTEL_SEC_OBJECT_BUNDLE_LENGTH + 1)

/* Suffix specifying format or representation of a field value */
/* Note that if a format suffix is not specified, a flat data
representation is implied */
#define INTEL_X509_C_DATATYPE 1
#define INTEL_X509_LDAPSTRING_DATATYPE 2

#define OID_ISO_CCITT_DIR_SERVICE 			85
#define OID_DS              				OID_ISO_CCITT_DIR_SERVICE 
#define OID_DS_LENGTH       				1
#define OID_ATTR_TYPE        				OID_DS, 4                
#define OID_ATTR_TYPE_LENGTH 				OID_DS_LENGTH + 1
#define OID_EXTENSION        				OID_DS, 29          
#define OID_EXTENSION_LENGTH 				OID_DS_LENGTH + 1
#define OID_ISO_STANDARD      	 			40
#define OID_ISO_MEMBER         				42                     
#define OID_US                 				OID_ISO_MEMBER, 134, 72

#define OID_ISO_IDENTIFIED_ORG 				43
#define OID_OSINET             				OID_ISO_IDENTIFIED_ORG, 4
#define OID_GOSIP              				OID_ISO_IDENTIFIED_ORG, 5
#define OID_DOD                				OID_ISO_IDENTIFIED_ORG, 6
#define OID_OIW                				OID_ISO_IDENTIFIED_ORG, 14 

/* From the PKCS Standards */
#define OID_ISO_MEMBER_LENGTH 				1
#define OID_US_LENGTH         				OID_ISO_MEMBER_LENGTH + 2
#define OID_RSA               				OID_US, 134, 247, 13
#define OID_RSA_LENGTH        				OID_US_LENGTH + 3
#define OID_RSA_HASH          				OID_RSA, 2
#define OID_RSA_HASH_LENGTH   				OID_RSA_LENGTH + 1
#define OID_RSA_ENCRYPT       				OID_RSA, 3
#define OID_RSA_ENCRYPT_LENGTH	 			OID_RSA_LENGTH + 1
#define OID_PKCS             				OID_RSA, 1
#define OID_PKCS_LENGTH       				OID_RSA_LENGTH +1
#define OID_PKCS_1          				OID_PKCS, 1
#define OID_PKCS_1_LENGTH   				OID_PKCS_LENGTH +1
#define OID_PKCS_2          				OID_PKCS, 2
#define OID_PKCS_3          				OID_PKCS, 3
#define OID_PKCS_3_LENGTH   				OID_PKCS_LENGTH +1
#define OID_PKCS_4          				OID_PKCS, 4
#define OID_PKCS_5          				OID_PKCS, 5
#define OID_PKCS_5_LENGTH   				OID_PKCS_LENGTH +1
#define OID_PKCS_6          				OID_PKCS, 6
#define OID_PKCS_7          				OID_PKCS, 7
#define OID_PKCS_7_LENGTH   				OID_PKCS_LENGTH +1
#define OID_PKCS_8          				OID_PKCS, 8
#define OID_PKCS_9          				OID_PKCS, 9
#define OID_PKCS_9_LENGTH   				OID_PKCS_LENGTH +1
#define OID_PKCS_10         				OID_PKCS, 10
#define OID_PKCS_11          				OID_PKCS, 11
#define OID_PKCS_11_LENGTH   				OID_PKCS_LENGTH +1
#define OID_PKCS_12          				OID_PKCS, 12
#define OID_PKCS_12_LENGTH   				OID_PKCS_LENGTH +1

/* ANSI X9.42 */
#define OID_ANSI_X9_42						OID_US, 206, 62, 2
#define OID_ANSI_X9_42_LEN					OID_US_LENGTH + 3
#define OID_ANSI_X9_42_SCHEME				OID_ANSI_X9_42, 3
#define OID_ANSI_X9_42_SCHEME_LEN			OID_ANSI_X9_42_LEN + 1
#define OID_ANSI_X9_42_NAMED_SCHEME			OID_ANSI_X9_42, 4
#define OID_ANSI_X9_42_NAMED_SCHEME_LEN		OID_ANSI_X9_42_LEN + 1

#define OID_PKIX							OID_DOD, 1, 5, 5, 7
#define OID_PKIX_LENGTH						6
#define OID_PE								OID_PKIX, 1
#define OID_PE_LENGTH						OID_PKIX_LENGTH + 1
#define OID_QT								OID_PKIX, 2
#define OID_QT_LENGTH						OID_PKIX_LENGTH + 1
#define OID_KP								OID_PKIX, 3
#define OID_KP_LENGTH						OID_PKIX_LENGTH + 1
#define OID_AD								OID_PKIX, 48
#define OID_AD_LENGTH						OID_PKIX_LENGTH + 1
#define OID_AD_OCSP							OID_AD, 1
#define OID_AD_OCSP_LENGTH					OID_AD_LENGTH + 1

#define OID_OIW_SECSIG        				OID_OIW, 3
#define OID_OIW_LENGTH       				2
#define OID_OIW_SECSIG_LENGTH 				OID_OIW_LENGTH +1

#define OID_OIW_ALGORITHM    				OID_OIW_SECSIG, 2
#define OID_OIW_ALGORITHM_LENGTH   			OID_OIW_SECSIG_LENGTH +1

/* NIST defined digest algorithm arc (2, 16, 840, 1, 101, 3, 4, 2) */
#define OID_NIST_HASHALG					0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02
#define OID_NIST_HASHALG_LENGTH				8

/*
 * Apple-specific OID bases
 */
 
/* 
 * apple OBJECT IDENTIFIER ::=
 * 	{ iso(1) member-body(2) US(840) 113635 }
 * 
 * BER = 06 06 2A 86 48 86 F7 63
 */
#define APPLE_OID				OID_US, 0x86, 0xf7, 0x63
#define APPLE_OID_LENGTH		OID_US_LENGTH + 3

/* appleDataSecurity OBJECT IDENTIFIER ::=
 *		{ apple 100 }
 *      { 1 2 840 113635 100 }
 *
 * BER = 06 07 2A 86 48 86 F7 63 64
 */
#define APPLE_ADS_OID			APPLE_OID, 0x64
#define APPLE_ADS_OID_LENGTH	APPLE_OID_LENGTH + 1

/*
 * appleTrustPolicy OBJECT IDENTIFIER ::=
 *		{ appleDataSecurity 1 }
 *      { 1 2 840 113635 100 1 }
 *
 * BER = 06 08 2A 86 48 86 F7 63 64 01 
 */ 
#define APPLE_TP_OID			APPLE_ADS_OID, 1
#define APPLE_TP_OID_LENGTH		APPLE_ADS_OID_LENGTH + 1

/*
 *	appleSecurityAlgorithm OBJECT IDENTIFIER ::=
 *		{ appleDataSecurity 2 }
 *      { 1 2 840 113635 100 2 }
 *
 * BER = 06 08 2A 86 48 86 F7 63 64 02
 */
#define APPLE_ALG_OID			APPLE_ADS_OID, 2
#define APPLE_ALG_OID_LENGTH	APPLE_ADS_OID_LENGTH + 1

/*
 * appleDotMacCertificate OBJECT IDENTIFIER ::= 
 *		{ appleDataSecurity 3 }
 *      { 1 2 840 113635 100 3 }
 */
#define APPLE_DOTMAC_CERT_OID			APPLE_ADS_OID, 3
#define APPLE_DOTMAC_CERT_OID_LENGTH	APPLE_ADS_OID_LENGTH + 1

/*
 * Basis of Policy OIDs for .mac TP requests
 *
 * dotMacCertificateRequest OBJECT IDENTIFIER ::= 
 *		{ appleDotMacCertificate 1 }
 *      { 1 2 840 113635 100 3 1 }
 */
#define APPLE_DOTMAC_CERT_REQ_OID			APPLE_DOTMAC_CERT_OID, 1
#define APPLE_DOTMAC_CERT_REQ_OID_LENGTH	APPLE_DOTMAC_CERT_OID_LENGTH + 1

/*
 * Basis of .mac Certificate Extensions
 *
 * dotMacCertificateExtension OBJECT IDENTIFIER ::= 
 *		{ appleDotMacCertificate 2 }
 *      { 1 2 840 113635 100 3 2 }
 */
#define APPLE_DOTMAC_CERT_EXTEN_OID			APPLE_DOTMAC_CERT_OID, 2
#define APPLE_DOTMAC_CERT_EXTEN_OID_LENGTH  APPLE_DOTMAC_CERT_OID_LENGTH + 1

/*
 * Basis of .mac Certificate request OID/value identitifiers
 *
 * dotMacCertificateRequestValues OBJECT IDENTIFIER ::= 
 *		{ appleDotMacCertificate 3 }
 *      { 1 2 840 113635 100 3 3 }
 */
#define APPLE_DOTMAC_CERT_REQ_VALUE_OID			APPLE_DOTMAC_CERT_OID, 3
#define APPLE_DOTMAC_CERT_REQ_VALUE_OID_LENGTH  APPLE_DOTMAC_CERT_OID_LENGTH + 1

/*
 * Basis of Apple-specific extended key usages
 *
 * appleExtendedKeyUsage OBJECT IDENTIFIER ::= 
 *		{ appleDataSecurity 4 }
 *      { 1 2 840 113635 100 4 }
 */
#define APPLE_EKU_OID					APPLE_ADS_OID, 4
#define APPLE_EKU_OID_LENGTH			APPLE_ADS_OID_LENGTH + 1

/* 
 * Basis of Apple Code Signing extended key usages
 * appleCodeSigning  OBJECT IDENTIFIER ::= 
 *		{ appleExtendedKeyUsage 1 }
 *      { 1 2 840 113635 100 4 1}
 */
#define APPLE_EKU_CODE_SIGNING			APPLE_EKU_OID, 1
#define APPLE_EKU_CODE_SIGNING_LENGTH	APPLE_EKU_OID_LENGTH + 1

/*
 * Basis of Apple-specific Certific Policy IDs.
 * appleCertificatePolicies OBJECT IDENTIFIER ::= 
 *		{appleDataSecurity 5}
 *		{ 1 2 840 113635 100 5 }
 */
#define APPLE_CERT_POLICIES				APPLE_ADS_OID, 5
#define APPLE_CERT_POLICIES_LENGTH		APPLE_ADS_OID_LENGTH + 1

/*
 * Netscape OIDs.
 */
#define NETSCAPE_BASE_OID		0x60, 0x86, 0x48, 0x01, 0x86, 0xf8, 0x42
#define NETSCAPE_BASE_OID_LEN   7

/*
 * Netscape cert extension.
 *
 *  netscape-cert-extension OBJECT IDENTIFIER ::=
 * 		{ 2 16 840 1 113730 1 }
 *
 *	BER = 06 08 60 86 48 01 86 F8 42 01
 */
#define NETSCAPE_CERT_EXTEN			NETSCAPE_BASE_OID, 0x01
#define NETSCAPE_CERT_EXTEN_LENGTH	NETSCAPE_BASE_OID_LEN + 1

#define NETSCAPE_CERT_POLICY		NETSCAPE_BASE_OID, 0x04
#define NETSCAPE_CERT_POLICY_LENGTH	NETSCAPE_BASE_OID_LEN + 1

#ifdef __cplusplus
}
#endif

#endif /* _OIDSBASE_H_ */
