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
 * oidsattr.h -- Cert/CRL related OIDs.
 */

#ifndef	_CDSA_OIDSATTR_H_
#define _CDSA_OIDSATTR_H_

#include <Security/cssmtype.h>
#include <Security/oidsbase.h>

/* 
 * Directory name component identifiers.
 */
extern const CSSM_OID
	CSSMOID_ObjectClass,
	CSSMOID_AliasedEntryName,
	CSSMOID_KnowledgeInformation,
	CSSMOID_CommonName,
	CSSMOID_Surname,
	CSSMOID_SerialNumber,
	CSSMOID_CountryName,
	CSSMOID_LocalityName,
	CSSMOID_StateProvinceName,
	CSSMOID_CollectiveStateProvinceName,
	CSSMOID_StreetAddress,
	CSSMOID_CollectiveStreetAddress,
	CSSMOID_OrganizationName,
	CSSMOID_CollectiveOrganizationName,
	CSSMOID_OrganizationalUnitName,
	CSSMOID_CollectiveOrganizationalUnitName,
	CSSMOID_Title,
	CSSMOID_Description,
	CSSMOID_SearchGuide,
	CSSMOID_BusinessCategory,
	CSSMOID_PostalAddress,
	CSSMOID_CollectivePostalAddress,
	CSSMOID_PostalCode,
	CSSMOID_CollectivePostalCode,
	CSSMOID_PostOfficeBox,
	CSSMOID_CollectivePostOfficeBox,
	CSSMOID_PhysicalDeliveryOfficeName, 
	CSSMOID_CollectivePhysicalDeliveryOfficeName,
	CSSMOID_TelephoneNumber,
	CSSMOID_CollectiveTelephoneNumber,  
	CSSMOID_TelexNumber,
	CSSMOID_CollectiveTelexNumber,
	CSSMOID_TelexTerminalIdentifier,
	CSSMOID_CollectiveTelexTerminalIdentifier,
	CSSMOID_FacsimileTelephoneNumber,
	CSSMOID_CollectiveFacsimileTelephoneNumber,
	CSSMOID_X_121Address,
	CSSMOID_InternationalISDNNumber,
	CSSMOID_CollectiveInternationalISDNNumber,
	CSSMOID_RegisteredAddress,
	CSSMOID_DestinationIndicator,
	CSSMOID_PreferredDeliveryMethod,
	CSSMOID_PresentationAddress,
	CSSMOID_SupportedApplicationContext,
	CSSMOID_Member,
	CSSMOID_Owner,
	CSSMOID_RoleOccupant,
	CSSMOID_SeeAlso,
	CSSMOID_UserPassword,
	CSSMOID_UserCertificate,
	CSSMOID_CACertificate,
	CSSMOID_AuthorityRevocationList,
	CSSMOID_CertificateRevocationList,
	CSSMOID_CrossCertificatePair,
	CSSMOID_Name,
	CSSMOID_GivenName,
	CSSMOID_Initials,
	CSSMOID_GenerationQualifier,
	CSSMOID_UniqueIdentifier,
	CSSMOID_DNQualifier,
	CSSMOID_EnhancedSearchGuide,
	CSSMOID_ProtocolInformation,
	CSSMOID_DistinguishedName,
	CSSMOID_UniqueMember,
	CSSMOID_HouseIdentifier;
	
/* PKCS 9 */
extern const CSSM_OID
	CSSMOID_EmailAddress,
	CSSMOID_UnstructuredName,
	CSSMOID_ContentType,
	CSSMOID_MessageDigest,
	CSSMOID_SigningTime,
	CSSMOID_CounterSignature,
	CSSMOID_ChallengePassword,
	CSSMOID_UnstructuredAddress,
	CSSMOID_ExtendedCertificateAttributes;

/* PKIX */
extern const CSSM_OID
	CSSMOID_QT_CPS,
	CSSMOID_QT_UNOTICE,
	CSSMOID_AD_OCSP,
	CSSMOID_AD_CA_ISSUERS,
	CSSMOID_AD_TIME_STAMPING,
	CSSMOID_AD_CA_REPOSITORY;

/* PKCS7 */
extern const CSSM_OID
	CSSMOID_PKCS7_Data,
	CSSMOID_PKCS7_SignedData,
	CSSMOID_PKCS7_EnvelopedData,
	CSSMOID_PKCS7_SignedAndEnvelopedData,
	CSSMOID_PKCS7_DigestedData,
	CSSMOID_PKCS7_EncryptedData,
	CSSMOID_PKCS7_DataWithAttributes,
	CSSMOID_PKCS7_EncryptedPrivateKeyInfo,

/* PKCS8 */
	CSSMOID_PKCS9_FriendlyName,
	CSSMOID_PKCS9_LocalKeyId,
	CSSMOID_PKCS9_CertTypes,
	CSSMOID_PKCS9_CrlTypes,
	CSSMOID_PKCS9_X509Certificate,
	CSSMOID_PKCS9_SdsiCertificate,
	CSSMOID_PKCS9_X509Crl,
	
/* PKCS12 */
	CSSMOID_PKCS12_keyBag,
	CSSMOID_PKCS12_shroudedKeyBag,
	CSSMOID_PKCS12_certBag,
	CSSMOID_PKCS12_crlBag,
	CSSMOID_PKCS12_secretBag,
	CSSMOID_PKCS12_safeContentsBag;

#endif	/* _CDSA_OIDSATTR_H_*/
