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
   File:      oidsalg.h

   Contains:  OIDs defining crypto algorithms

   Copyright: (c) 1999-2000 Apple Computer, Inc., all rights reserved.
*/

#ifndef	_OIDS_ALG_H_
#define _OIDS_ALG_H_

#include <Security/cssmtype.h>

#ifdef	__cplusplus
extern "C" {
#endif

extern const CSSM_OID
	CSSMOID_MD2,
	CSSMOID_MD4,
	CSSMOID_MD5,
	CSSMOID_RSA,
	CSSMOID_MD2WithRSA,
	CSSMOID_MD4WithRSA,
	CSSMOID_MD5WithRSA,
	CSSMOID_SHA1WithRSA,
	CSSMOID_DH,
	CSSMOID_DSA,
	CSSMOID_SHA1WithDSA,
	CSSMOID_SHA1,
	CSSMOID_APPLE_ISIGN,
	CSSMOID_APPLE_X509_BASIC,
	CSSMOID_APPLE_TP_SSL,
	CSSMOID_APPLE_TP_LOCAL_CERT_GEN,
	CSSMOID_APPLE_TP_CSR_GEN,
	CSSMOID_APPLE_FEE,
	CSSMOID_APPLE_ASC,
	CSSMOID_APPLE_FEE_MD5,
	CSSMOID_APPLE_FEE_SHA1,
	CSSMOID_APPLE_FEED,
	CSSMOID_APPLE_FEEDEXP,
	CSSMOID_APPLE_ECDSA;

#ifdef	__cplusplus
}
#endif

#endif	/* _OIDS_ALG_H_ */
