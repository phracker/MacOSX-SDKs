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
   File:      cssmaci.h

   Contains:  Sevice Provider Interface for Access Control Module

   Copyright: (c) 1999-2000 Apple Computer, Inc., all rights reserved.
 */

#ifndef _CSSMACI_H_
#define _CSSMACI_H_  1

#include <Security/cssmtype.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct cssm_spi_ac_funcs {
    CSSM_RETURN (CSSMACI *AuthCompute)
        (CSSM_AC_HANDLE ACHandle,
         const CSSM_TUPLEGROUP *BaseAuthorizations,
         const CSSM_TUPLEGROUP *Credentials,
         uint32 NumberOfRequestors,
         const CSSM_LIST *Requestors,
         const CSSM_LIST *RequestedAuthorizationPeriod,
         const CSSM_LIST *RequestedAuthorization,
         CSSM_TUPLEGROUP_PTR AuthorizationResult);
    CSSM_RETURN (CSSMACI *PassThrough)
        (CSSM_AC_HANDLE ACHandle,
         CSSM_TP_HANDLE TPHandle,
         CSSM_CL_HANDLE CLHandle,
         CSSM_CC_HANDLE CCHandle,
         const CSSM_DL_DB_LIST *DBList,
         uint32 PassThroughId,
         const void *InputParams,
         void **OutputParams);
} CSSM_SPI_AC_FUNCS, *CSSM_SPI_AC_FUNCS_PTR;

#ifdef __cplusplus
}
#endif

#endif /* _CSSMACI_H_ */
