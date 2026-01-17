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
	File:		CertExtensions.h

	Contains:	X.509 Cert Extensions as C structs

	Copyright:	(c) 2000 by Apple Computer, Inc., all rights reserved.
*/

#ifndef	_CERT_EXTENSIONS_H_
#define _CERT_EXTENSIONS_H_

#include <Security/cssmtype.h>

/***
 *** Structs for declaring extension-specific data. 
 ***/

/*
 * GeneralName, used in AuthorityKeyID and SubjectAltName.
 *
 * For now, we just provide explicit support for the types which are
 * represented as IA5Strings, OIDs, and octet strings. Constructed types
 * such as EDIPartyName and x400Address are not explicitly handled
 * right now and must be encoded and decoded by the caller. In those
 * cases the CE_GeneralName.name.Data field represents the BER contents
 * octets; CE_GeneralName.name,Length is the length of the contents; the 
 * tag of the field is not needed - the BER encoding uses context-specific
 * implicit tagging. The berEncoded field is set to CSSM_TRUE in these
 * case. Simple types have berEncoded = CSSM_FALS. 
 *
 *      GeneralNames ::= SEQUENCE SIZE (1..MAX) OF GeneralName
 *
 *      GeneralName ::= CHOICE {
 *           otherName                       [0]     OtherName (i.e., OID),
 *           rfc822Name                      [1]     IA5String,
 *           dNSName                         [2]     IA5String,
 *           x400Address                     [3]     ORAddress,
 *           directoryName                   [4]     Name,
 *           ediPartyName                    [5]     EDIPartyName,
 *           uniformResourceIdentifier       [6]     IA5String,
 *           iPAddress                       [7]     OCTET STRING,
 *           registeredID                    [8]     OBJECT IDENTIFIER}
 *
 *      OtherName ::= SEQUENCE {
 *           type-id    OBJECT IDENTIFIER,
 *           value      [0] EXPLICIT ANY DEFINED BY type-id }
 *
 *      EDIPartyName ::= SEQUENCE {
 *           nameAssigner            [0]     DirectoryString OPTIONAL,
 *           partyName               [1]     DirectoryString }
 */
typedef enum {
	GNT_OtherName = 0,
	GNT_RFC822Name,
	GNT_DNSName,
	GNT_X400Address,
	GNT_DirectoryName,
	GNT_EdiPartyName,
	GNT_URI,
	GNT_IPAddress,
	GNT_RegisteredID
} CE_GeneralNameType;

typedef struct {
	CE_GeneralNameType		nameType;	// GNT_RFC822Name, etc.
	CSSM_BOOL				berEncoded;
	CSSM_DATA				name; 
} CE_GeneralName;

typedef struct {
	uint32					numNames;
	CE_GeneralName			*generalName;		
} CE_GeneralNames;	

/*
 * id-ce-authorityKeyIdentifier OBJECT IDENTIFIER ::=  { id-ce 35 }
 *
 *   AuthorityKeyIdentifier ::= SEQUENCE {
 *     keyIdentifier             [0] KeyIdentifier           OPTIONAL,
 *     authorityCertIssuer       [1] GeneralNames            OPTIONAL,
 *     authorityCertSerialNumber [2] CertificateSerialNumber OPTIONAL  }
 *
 *   KeyIdentifier ::= OCTET STRING
 *
 * CSSM OID = CSSMOID_AuthorityKeyIdentifier
 */
typedef struct {
	CSSM_BOOL			keyIdentifierPresent;
	CSSM_DATA			keyIdentifier;
	CSSM_BOOL			generalNamesPresent;
	CE_GeneralNames		*generalNames;
	CSSM_BOOL			serialNumberPresent;
	CSSM_DATA			serialNumber;
} CE_AuthorityKeyID;

/*
 * id-ce-subjectKeyIdentifier OBJECT IDENTIFIER ::=  { id-ce 14 }
 *   SubjectKeyIdentifier ::= KeyIdentifier
 *
 * CSSM OID = CSSMOID_SubjectKeyIdentifier
 */
typedef CSSM_DATA CE_SubjectKeyID;

/*
 * id-ce-keyUsage OBJECT IDENTIFIER ::=  { id-ce 15 }
 *
 *     KeyUsage ::= BIT STRING {
 *          digitalSignature        (0),
 *          nonRepudiation          (1),
 *          keyEncipherment         (2),
 *          dataEncipherment        (3),
 *          keyAgreement            (4),
 *          keyCertSign             (5),
 *          cRLSign                 (6),
 *          encipherOnly            (7),
 *          decipherOnly            (8) }
 *
 * CSSM OID = CSSMOID_KeyUsage
 *
 */
typedef uint16 CE_KeyUsage;

#define CE_KU_DigitalSignature	0x8000
#define CE_KU_NonRepudiation	0x4000
#define CE_KU_KeyEncipherment	0x2000
#define CE_KU_DataEncipherment	0x1000
#define CE_KU_KeyAgreement		0x0800
#define CE_KU_KeyCertSign	 	0x0400
#define CE_KU_CRLSign			0x0200
#define CE_KU_EncipherOnly	 	0x0100
#define CE_KU_DecipherOnly	 	0x0080

/*
 * id-ce-subjectAltName OBJECT IDENTIFIER ::=  { id-ce 17 }
 *
 *      SubjectAltName ::= GeneralNames
 *
 * CSSM OID = CSSMOID_SubjectAltName
 *
 * GeneralNames defined above.
 */

/*
 *  id-ce-extKeyUsage OBJECT IDENTIFIER ::= {id-ce 37}
 *
 *   ExtKeyUsageSyntax ::= SEQUENCE SIZE (1..MAX) OF KeyPurposeId*
 *
 *  KeyPurposeId ::= OBJECT IDENTIFIER
 *
 * CSSM OID = CSSMOID_ExtendedKeyUsage
 */
typedef struct {
	uint32			numPurposes;
	CSSM_OID_PTR	purposes;		// in Intel pre-encoded format
} CE_ExtendedKeyUsage;

/*
 * id-ce-basicConstraints OBJECT IDENTIFIER ::=  { id-ce 19 }
 *
 * BasicConstraints ::= SEQUENCE {
 *       cA                      BOOLEAN DEFAULT FALSE,
 *       pathLenConstraint       INTEGER (0..MAX) OPTIONAL }
 *
 * CSSM OID = CSSMOID_BasicConstraints
 */
typedef struct {
	CSSM_BOOL			cA;
	CSSM_BOOL			pathLenConstraintPresent;
	uint32				pathLenConstraint;
} CE_BasicConstraints;	

/*
 * id-ce-certificatePolicies OBJECT IDENTIFIER ::=  { id-ce 32 }
 *
 *   certificatePolicies ::= SEQUENCE SIZE (1..MAX) OF PolicyInformation
 *
 *   PolicyInformation ::= SEQUENCE {
 *        policyIdentifier   CertPolicyId,
 *        policyQualifiers   SEQUENCE SIZE (1..MAX) OF
 *                                PolicyQualifierInfo OPTIONAL }
 *
 *   CertPolicyId ::= OBJECT IDENTIFIER
 *
 *   PolicyQualifierInfo ::= SEQUENCE {
 *        policyQualifierId  PolicyQualifierId,
 *        qualifier          ANY DEFINED BY policyQualifierId } 
 *
 *   -- policyQualifierIds for Internet policy qualifiers
 *
 *   id-qt          OBJECT IDENTIFIER ::=  { id-pkix 2 }
 *   id-qt-cps      OBJECT IDENTIFIER ::=  { id-qt 1 }
 *   id-qt-unotice  OBJECT IDENTIFIER ::=  { id-qt 2 }
 *
 *   PolicyQualifierId ::=
 *        OBJECT IDENTIFIER ( id-qt-cps | id-qt-unotice )
 *
 *   Qualifier ::= CHOICE {
 *        cPSuri           CPSuri,
 *        userNotice       UserNotice }
 *
 *   CPSuri ::= IA5String
 *
 *   UserNotice ::= SEQUENCE {
 *        noticeRef        NoticeReference OPTIONAL,
 *        explicitText     DisplayText OPTIONAL}
 *
 *   NoticeReference ::= SEQUENCE {
 *        organization     DisplayText,
 *        noticeNumbers    SEQUENCE OF INTEGER }
 *
 *   DisplayText ::= CHOICE {
 *        visibleString    VisibleString  (SIZE (1..200)),
 *        bmpString        BMPString      (SIZE (1..200)),
 *        utf8String       UTF8String     (SIZE (1..200)) }
 *
 *  CSSM OID = CSSMOID_CertificatePolicies
 *
 * We only support down to the level of Qualifier, and then only the CPSuri
 * choice. UserNotice is transmitted to and from this library as a raw
 * CSSM_DATA representing the Contents octets of the BER-encoded UserNotice sequence. 
 */

typedef struct {
	CSSM_OID	policyQualifierId;			// CSSMOID_QT_CPS, CSSMOID_QT_UNOTICE
	CSSM_DATA	qualifier;					// CSSMOID_QT_CPS: IA5String contents
											// CSSMOID_QT_UNOTICE : Sequence contents
} CE_PolicyQualifierInfo;

typedef struct {
	CSSM_OID				certPolicyId;
	uint32					numPolicyQualifiers;	// size of *policyQualifiers;
	CE_PolicyQualifierInfo	*policyQualifiers;
} CE_PolicyInformation;

typedef struct {
	uint32					numPolicies;			// size of *policies;
	CE_PolicyInformation	*policies;
} CE_CertPolicies;

/*
 * netscape-cert-type, a bit string.
 *
 * CSSM OID = CSSMOID_NetscapeCertType
 *
 * Bit fields defined in oidsattr.h: CE_NCT_SSL_Client, etc.
 */
typedef uint16 CE_NetscapeCertType;

/*
 * An enumerated list identifying one of the above per-extension
 * structs.
 */
typedef enum {
	DT_AuthorityKeyID,			// CE_AuthorityKeyID
	DT_SubjectKeyID,			// CE_SubjectKeyID
	DT_KeyUsage,				// CE_KeyUsage
	DT_SubjectAltName,			// implies CE_GeneralName
	DT_ExtendedKeyUsage,		// CE_ExtendedKeyUsage
	DT_BasicConstraints,		// CE_BasicConstraints
	DT_CertPolicies,			// CE_CertPolicies
	DT_NetscapeCertType,		// CE_NetscapeCertType
	DT_Other					// unknown, raw data as a CSSM_DATA
} CE_DataType;

/*
 * One unified representation of all the cert extensions we know about.
 */
typedef union {
	CE_AuthorityKeyID		authorityKeyID;
	CE_SubjectKeyID			subjectKeyID;
	CE_KeyUsage				keyUsage;
	CE_GeneralNames			subjectAltName;
	CE_ExtendedKeyUsage		extendedKeyUsage;
	CE_BasicConstraints		basicConstraints;
	CE_CertPolicies			certPolicies;
	CE_NetscapeCertType		netscapeCertType;
	CSSM_DATA				rawData;			// unknown, not decoded
} CE_Data;

#endif	/* _CERT_EXTENSIONS_H_ */
