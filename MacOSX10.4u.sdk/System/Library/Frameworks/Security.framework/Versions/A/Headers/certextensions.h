/*
 * Copyright (c) 2000-2004 Apple Computer, Inc. All Rights Reserved.
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
 * CertExtensions.h -- X.509 Cert Extensions as C structs
 */

#ifndef	_CERT_EXTENSIONS_H_
#define _CERT_EXTENSIONS_H_

#include <Security/cssmtype.h>

/***
 *** Structs for declaring extension-specific data. 
 ***/

/*
 * GeneralName, used in AuthorityKeyID, SubjectAltName, and 
 * IssuerAltName. 
 *
 * For now, we just provide explicit support for the types which are
 * represented as IA5Strings, OIDs, and octet strings. Constructed types
 * such as EDIPartyName and x400Address are not explicitly handled
 * right now and must be encoded and decoded by the caller. (See exception
 * for Name and OtherName, below). In those cases the CE_GeneralName.name.Data field 
 * represents the BER contents octets; CE_GeneralName.name.Length is the 
 * length of the contents; the tag of the field is not needed - the BER 
 * encoding uses context-specific implicit tagging. The berEncoded field 
 * is set to CSSM_TRUE in these case. Simple types have berEncoded = CSSM_FALSE. 
 *
 * In the case of a GeneralName in the form of a Name, we parse the Name
 * into a CSSM_X509_NAME and place a pointer to the CSSM_X509_NAME in the
 * CE_GeneralName.name.Data field. CE_GeneralName.name.Length is set to 
 * sizeof(CSSM_X509_NAME). In this case berEncoded is false. 
 *
 * In the case of a GeneralName in the form of a OtherName, we parse the fields
 * into a CE_OtherName and place a pointer to the CE_OtherName in the
 * CE_GeneralName.name.Data field. CE_GeneralName.name.Length is set to 
 * sizeof(CE_OtherName). In this case berEncoded is false. 
 *
 *      GeneralNames ::= SEQUENCE SIZE (1..MAX) OF GeneralName
 *
 *      GeneralName ::= CHOICE {
 *           otherName                       [0]     OtherName
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
	CSSM_OID				typeId;
	CSSM_DATA				value;		// unparsed, BER-encoded
} CE_OtherName;

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
 *  id-ce-cRLReason OBJECT IDENTIFIER ::= { id-ce 21 }
 *
 *   -- reasonCode ::= { CRLReason }
 *
 *   CRLReason ::= ENUMERATED {
 *  	unspecified             (0),
 *      keyCompromise           (1),
 *     	cACompromise            (2),
 *    	affiliationChanged      (3),
 *   	superseded              (4),
 *  	cessationOfOperation    (5),
 * 		certificateHold         (6),
 *		removeFromCRL           (8) }
 *
 * CSSM OID = CSSMOID_CrlReason
 *
 */
typedef uint32 CE_CrlReason;

#define CE_CR_Unspecified			0
#define CE_CR_KeyCompromise			1
#define CE_CR_CACompromise			2
#define CE_CR_AffiliationChanged	3
#define CE_CR_Superseded			4
#define CE_CR_CessationOfOperation	5
#define CE_CR_CertificateHold		6
#define CE_CR_RemoveFromCRL	 		8

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
 * CSSM_DATA containing the BER-encoded UserNotice sequence. 
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
 * CRLDistributionPoints.
 *
 *   id-ce-cRLDistributionPoints OBJECT IDENTIFIER ::=  { id-ce 31 }
 *
 *   cRLDistributionPoints ::= {
 *        CRLDistPointsSyntax }
 *
 *   CRLDistPointsSyntax ::= SEQUENCE SIZE (1..MAX) OF DistributionPoint
 *
 *   NOTE: RFC 2459 claims that the tag for the optional DistributionPointName
 *   is IMPLICIT as shown here, but in practice it is EXPLICIT. It has to be -
 *   because the underlying type also uses an implicit tag for distinguish
 *   between CHOICEs.
 *
 *   DistributionPoint ::= SEQUENCE {
 *        distributionPoint       [0]     DistributionPointName OPTIONAL,
 *        reasons                 [1]     ReasonFlags OPTIONAL,
 *        cRLIssuer               [2]     GeneralNames OPTIONAL }
 *
 *   DistributionPointName ::= CHOICE {
 *        fullName                [0]     GeneralNames,
 *        nameRelativeToCRLIssuer [1]     RelativeDistinguishedName }
 *
 *   ReasonFlags ::= BIT STRING {
 *        unused                  (0),
 *        keyCompromise           (1),
 *        cACompromise            (2),
 *        affiliationChanged      (3),
 *        superseded              (4),
 *        cessationOfOperation    (5),
 *        certificateHold         (6) }
 *
 * CSSM OID = CSSMOID_CrlDistributionPoints
 */
 
/*
 * Note that this looks similar to CE_CrlReason, but that's an enum and this
 * is an OR-able bit string.
 */
typedef uint8 CE_CrlDistReasonFlags;

#define CE_CD_Unspecified			0x80
#define CE_CD_KeyCompromise			0x40
#define CE_CD_CACompromise			0x20
#define CE_CD_AffiliationChanged	0x10
#define CE_CD_Superseded			0x08
#define CE_CD_CessationOfOperation	0x04
#define CE_CD_CertificateHold		0x02

typedef enum {
	CE_CDNT_FullName,
	CE_CDNT_NameRelativeToCrlIssuer
} CE_CrlDistributionPointNameType;

typedef struct {
	CE_CrlDistributionPointNameType		nameType;
	union {
		CE_GeneralNames					*fullName;
		CSSM_X509_RDN_PTR				rdn;
	} dpn;
} CE_DistributionPointName;

/*
 * The top-level CRLDistributionPoint.
 * All fields are optional; NULL pointers indicate absence. 
 */
typedef struct {
	CE_DistributionPointName			*distPointName;
	CSSM_BOOL							reasonsPresent;
	CE_CrlDistReasonFlags				reasons;
	CE_GeneralNames						*crlIssuer;
} CE_CRLDistributionPoint;

typedef struct {
	uint32								numDistPoints;
	CE_CRLDistributionPoint				*distPoints;
} CE_CRLDistPointsSyntax;

/* 
 * Authority Information Access and Subject Information Access.
 *
 * CSSM OID = CSSMOID_AuthorityInfoAccess
 * CSSM OID = CSSMOID_SubjectInfoAccess
 *
 * SubjAuthInfoAccessSyntax  ::=
 *		SEQUENCE SIZE (1..MAX) OF AccessDescription
 * 
 * AccessDescription  ::=  SEQUENCE {
 *		accessMethod          OBJECT IDENTIFIER,
 *		accessLocation        GeneralName  }
 */
typedef struct {
	CSSM_OID				accessMethod;
	CE_GeneralName			accessLocation;
} CE_AccessDescription;

typedef struct {
	uint32					numAccessDescriptions;
	CE_AccessDescription	*accessDescriptions;
} CE_AuthorityInfoAccess;

/*** CRL extensions ***/

/*
 * cRLNumber, an integer.
 *
 * CSSM OID = CSSMOID_CrlNumber
 */
typedef uint32 CE_CrlNumber;

/*
 * deltaCRLIndicator, an integer.
 *
 * CSSM OID = CSSMOID_DeltaCrlIndicator
 */
typedef uint32 CE_DeltaCrl;

/*
 * IssuingDistributionPoint
 *
 * id-ce-issuingDistributionPoint OBJECT IDENTIFIER ::= { id-ce 28 }
 *
 * issuingDistributionPoint ::= SEQUENCE {
 *      distributionPoint       [0] DistributionPointName OPTIONAL,
 *		onlyContainsUserCerts   [1] BOOLEAN DEFAULT FALSE,
 *      onlyContainsCACerts     [2] BOOLEAN DEFAULT FALSE,
 *      onlySomeReasons         [3] ReasonFlags OPTIONAL,
 *      indirectCRL             [4] BOOLEAN DEFAULT FALSE }
 *
 * CSSM OID = CSSMOID_IssuingDistributionPoint
 */
typedef struct {
	CE_DistributionPointName	*distPointName;		// optional
	CSSM_BOOL					onlyUserCertsPresent;
	CSSM_BOOL					onlyUserCerts;
	CSSM_BOOL					onlyCACertsPresent;
	CSSM_BOOL					onlyCACerts;
	CSSM_BOOL					onlySomeReasonsPresent;
	CE_CrlDistReasonFlags		onlySomeReasons;
	CSSM_BOOL					indirectCrlPresent;
	CSSM_BOOL					indirectCrl;
} CE_IssuingDistributionPoint;

/*
 * An enumerated list identifying one of the above per-extension
 * structs.
 */
typedef enum {
	DT_AuthorityKeyID,			// CE_AuthorityKeyID
	DT_SubjectKeyID,			// CE_SubjectKeyID
	DT_KeyUsage,				// CE_KeyUsage
	DT_SubjectAltName,			// implies CE_GeneralName
	DT_IssuerAltName,			// implies CE_GeneralName
	DT_ExtendedKeyUsage,		// CE_ExtendedKeyUsage
	DT_BasicConstraints,		// CE_BasicConstraints
	DT_CertPolicies,			// CE_CertPolicies
	DT_NetscapeCertType,		// CE_NetscapeCertType
	DT_CrlNumber,				// CE_CrlNumber
	DT_DeltaCrl,				// CE_DeltaCrl
	DT_CrlReason,				// CE_CrlReason
	DT_CrlDistributionPoints,	// CE_CRLDistPointsSyntax
	DT_IssuingDistributionPoint,// CE_IssuingDistributionPoint
	DT_AuthorityInfoAccess,		// CE_AuthorityInfoAccess
	DT_Other					// unknown, raw data as a CSSM_DATA
} CE_DataType;

/*
 * One unified representation of all the cert adn CRL extensions we know about.
 */
typedef union {
	CE_AuthorityKeyID			authorityKeyID;
	CE_SubjectKeyID				subjectKeyID;
	CE_KeyUsage					keyUsage;
	CE_GeneralNames				subjectAltName;
	CE_GeneralNames				issuerAltName;
	CE_ExtendedKeyUsage			extendedKeyUsage;
	CE_BasicConstraints			basicConstraints;
	CE_CertPolicies				certPolicies;
	CE_NetscapeCertType			netscapeCertType;
	CE_CrlNumber				crlNumber;
	CE_DeltaCrl					deltaCrl;
	CE_CrlReason				crlReason;
	CE_CRLDistPointsSyntax		crlDistPoints;
	CE_IssuingDistributionPoint	issuingDistPoint;
	CE_AuthorityInfoAccess		authorityInfoAccess;
	CSSM_DATA					rawData;			// unknown, not decoded
} CE_Data;

typedef struct {
	CE_DataType				type;
	CE_Data					extension;
	CSSM_BOOL				critical;
} CE_DataAndType;

#endif	/* _CERT_EXTENSIONS_H_ */
