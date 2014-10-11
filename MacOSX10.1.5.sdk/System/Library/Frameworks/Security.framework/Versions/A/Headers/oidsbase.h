/*
 * Copyright (c) 2000-2001 Apple Computer, Inc. All Rights Reserved.
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


/*
   File:      oidsbase.h

   Contains:  Basic Object Identifier Macros and Data Types.

   Copyright: (c) 1999-2000 Apple Computer, Inc., all rights reserved.
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

#define OID_PKIX							OID_DOD, 1, 5, 5, 7
#define OID_PKIX_LENGTH						6
#define OID_QT								OID_PKIX, 2
#define OID_QT_LENGTH						OID_PKIX_LENGTH + 1

#define OID_OIW_SECSIG        				OID_OIW, 3
#define OID_OIW_LENGTH       				2
#define OID_OIW_SECSIG_LENGTH 				OID_OIW_LENGTH +1

#define OID_OIW_ALGORITHM    				OID_OIW_SECSIG, 2
#define OID_OIW_ALGORITHM_LENGTH   			OID_OIW_SECSIG_LENGTH +1

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
 * Netscape extensions. 
 */
/*
 *  netscape-cert-extension OBJECT IDENTIFIER ::=
 * 		{ 2 16 840 1 113730 1 }
 *
 *	BER = 06 08 60 86 48 01 86 F8 42 01
 */
#define NETSCAPE_CERT_EXTEN		0x60, 0x86, 0x48, 0x01, 0x86, 0xf8, 0x42, 0x01
#define NETSCAPE_CERT_EXTEN_LENGTH	8

#ifdef __cplusplus
}
#endif

#endif /* _OIDSBASE_H_ */
