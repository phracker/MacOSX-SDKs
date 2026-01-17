/*
 * Copyright (c) 1999-2001,2004 Apple Computer, Inc. All Rights Reserved.
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
 * oidscrl.h -- Object Identifiers for X509 CRLs and OCSP
 */

#ifndef _OIDSCRL_H_
#define _OIDSCRL_H_  1

#include <Security/cssmconfig.h>
#include <Security/cssmtype.h>
#include <Security/oidsbase.h>

#ifdef __cplusplus
extern "C" {
#endif

#define INTEL_X509V2_CRL_R08 INTEL_SEC_FORMATS, 2, 1
#define INTEL_X509V2_CRL_R08_LENGTH INTEL_SEC_FORMATS_LENGTH+2

	
extern const CSSM_OID
    /* CRL OIDs */
	CSSMOID_X509V2CRLSignedCrlStruct,
	CSSMOID_X509V2CRLSignedCrlCStruct,
	CSSMOID_X509V2CRLTbsCertListStruct,
	CSSMOID_X509V2CRLTbsCertListCStruct,
	CSSMOID_X509V2CRLVersion,
	CSSMOID_X509V1CRLIssuerStruct,
	CSSMOID_X509V1CRLIssuerNameCStruct,
	CSSMOID_X509V1CRLIssuerNameLDAP,
	CSSMOID_X509V1CRLThisUpdate,
	CSSMOID_X509V1CRLNextUpdate,

	/* CRL Entry (CRL CertList) OIDS */
	CSSMOID_X509V1CRLRevokedCertificatesStruct,
	CSSMOID_X509V1CRLRevokedCertificatesCStruct,
	CSSMOID_X509V1CRLNumberOfRevokedCertEntries,
	CSSMOID_X509V1CRLRevokedEntryStruct,
	CSSMOID_X509V1CRLRevokedEntryCStruct,
	CSSMOID_X509V1CRLRevokedEntrySerialNumber,
	CSSMOID_X509V1CRLRevokedEntryRevocationDate,

	/* CRL Entry (CRL CertList) Extension OIDs */
	CSSMOID_X509V2CRLRevokedEntryAllExtensionsStruct,
	CSSMOID_X509V2CRLRevokedEntryAllExtensionsCStruct,
	CSSMOID_X509V2CRLRevokedEntryNumberOfExtensions,
	CSSMOID_X509V2CRLRevokedEntrySingleExtensionStruct,
	CSSMOID_X509V2CRLRevokedEntrySingleExtensionCStruct,
	CSSMOID_X509V2CRLRevokedEntryExtensionId,
	CSSMOID_X509V2CRLRevokedEntryExtensionCritical,
	CSSMOID_X509V2CRLRevokedEntryExtensionType,
	CSSMOID_X509V2CRLRevokedEntryExtensionValue,

	/* CRL Extension OIDs */
	CSSMOID_X509V2CRLAllExtensionsStruct,
	CSSMOID_X509V2CRLAllExtensionsCStruct,
	CSSMOID_X509V2CRLNumberOfExtensions,
	CSSMOID_X509V2CRLSingleExtensionStruct,
	CSSMOID_X509V2CRLSingleExtensionCStruct,
	CSSMOID_X509V2CRLExtensionId,
	CSSMOID_X509V2CRLExtensionCritical,
	CSSMOID_X509V2CRLExtensionType,
	
	/* OCSP */
	CSSMOID_PKIX_OCSP,
	CSSMOID_PKIX_OCSP_BASIC,
	CSSMOID_PKIX_OCSP_NONCE,
	CSSMOID_PKIX_OCSP_CRL,
	CSSMOID_PKIX_OCSP_RESPONSE,
	CSSMOID_PKIX_OCSP_NOCHECK,
	CSSMOID_PKIX_OCSP_ARCHIVE_CUTOFF,
	CSSMOID_PKIX_OCSP_SERVICE_LOCATOR;

	
#ifdef __cplusplus
}
#endif

#endif /* _OIDSCRL_H_ */
