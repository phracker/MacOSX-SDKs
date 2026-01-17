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
   File:      cssmkrspi.h

   Contains:  Service Provider Interface for Key Recovery Modules

   Copyright: (c) 1999-2000 Apple Computer, Inc., all rights reserved.
*/

#ifndef _CSSMKRSPI_H_
#define _CSSMKRSPI_H_  1

#include <Security/cssmtype.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Data types for Key Recovery SPI */

typedef struct cssm_spi_kr_funcs {
    CSSM_RETURN (CSSMKRI *RegistrationRequest)
        (CSSM_KRSP_HANDLE KRSPHandle,
         CSSM_CC_HANDLE KRRegistrationContextHandle,
         const CSSM_CONTEXT *KRRegistrationContext,
         const CSSM_DATA *KRInData,
         const CSSM_ACCESS_CREDENTIALS *AccessCredentials,
         CSSM_KR_POLICY_FLAGS KRFlags,
         sint32 *EstimatedTime,
         CSSM_HANDLE_PTR ReferenceHandle);
    CSSM_RETURN (CSSMKRI *RegistrationRetrieve)
        (CSSM_KRSP_HANDLE KRSPHandle,
         CSSM_HANDLE ReferenceHandle,
         sint32 *EstimatedTime,
         CSSM_KR_PROFILE_PTR KRProfile);
    CSSM_RETURN (CSSMKRI *GenerateRecoveryFields)
        (CSSM_KRSP_HANDLE KRSPHandle,
         CSSM_CC_HANDLE KREnablementContextHandle,
         const CSSM_CONTEXT *KREnablementContext,
         CSSM_CC_HANDLE CryptoContextHandle,
         const CSSM_CONTEXT *CryptoContext,
         const CSSM_DATA *KRSPOptions,
         CSSM_KR_POLICY_FLAGS KRFlags,
         CSSM_DATA_PTR KRFields);
    CSSM_RETURN (CSSMKRI *ProcessRecoveryFields)
        (CSSM_KRSP_HANDLE KRSPHandle,
         CSSM_CC_HANDLE KREnablementContextHandle,
         const CSSM_CONTEXT *KREnablementContext,
         CSSM_CC_HANDLE CryptoContextHandle,
         const CSSM_CONTEXT *CryptoContext,
         const CSSM_DATA *KRSPOptions,
         CSSM_KR_POLICY_FLAGS KRFlags,
         const CSSM_DATA *KRFields);
    CSSM_RETURN (CSSMKRI *RecoveryRequest)
        (CSSM_KRSP_HANDLE KRSPHandle,
         CSSM_CC_HANDLE KRRequestContextHandle,
         const CSSM_CONTEXT *KRRequestContext,
         const CSSM_DATA *KRInData,
         const CSSM_ACCESS_CREDENTIALS *AccessCredentials,
         sint32 *EstimatedTime,
         CSSM_HANDLE_PTR ReferenceHandle);
    CSSM_RETURN (CSSMKRI *RecoveryRetrieve)
        (CSSM_KRSP_HANDLE KRSPHandle,
         CSSM_HANDLE ReferenceHandle,
         sint32 *EstimatedTime,
         CSSM_HANDLE_PTR CacheHandle,
         uint32 *NumberOfRecoveredKeys);
    CSSM_RETURN (CSSMKRI *GetRecoveredObject)
        (CSSM_KRSP_HANDLE KRSPHandle,
         CSSM_HANDLE CacheHandle,
         uint32 IndexInResults,
         CSSM_CSP_HANDLE CSPHandle,
         const CSSM_RESOURCE_CONTROL_CONTEXT *CredAndAclEntry,
         uint32 Flags,
         CSSM_KEY_PTR RecoveredKey,
         CSSM_DATA_PTR OtherInfo);
    CSSM_RETURN (CSSMKRI *RecoveryRequestAbort)
        (CSSM_KRSP_HANDLE KRSPHandle,
         CSSM_HANDLE ResultsHandle);
    CSSM_RETURN (CSSMKRI *PassThrough)
        (CSSM_KRSP_HANDLE KRSPHandle,
         CSSM_CC_HANDLE KeyRecoveryContextHandle,
         const CSSM_CONTEXT *KeyRecoveryContext,
         CSSM_CC_HANDLE CryptoContextHandle,
         const CSSM_CONTEXT *CryptoContext,
         uint32 PassThroughId,
         const void *InputParams,
         void **OutputParams);
} CSSM_SPI_KR_FUNCS, *CSSM_SPI_KR_FUNCS_PTR;

#ifdef __cplusplus
}
#endif

#endif /* _CSSMKRSPI_H_ */
