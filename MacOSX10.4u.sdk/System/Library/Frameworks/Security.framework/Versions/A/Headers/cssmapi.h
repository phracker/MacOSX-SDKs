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
 * cssmapi.h -- Application Programmers Interfaces for CSSM
 */

#ifndef _CSSMAPI_H_
#define _CSSMAPI_H_  1

#include <Security/cssmtype.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Core Functions */

CSSM_RETURN CSSMAPI
CSSM_Init (const CSSM_VERSION *Version,
           CSSM_PRIVILEGE_SCOPE Scope,
           const CSSM_GUID *CallerGuid,
           CSSM_KEY_HIERARCHY KeyHierarchy,
           CSSM_PVC_MODE *PvcPolicy,
           const void *Reserved);

CSSM_RETURN CSSMAPI
CSSM_Terminate (void);

CSSM_RETURN CSSMAPI
CSSM_ModuleLoad (const CSSM_GUID *ModuleGuid,
                 CSSM_KEY_HIERARCHY KeyHierarchy,
                 CSSM_API_ModuleEventHandler AppNotifyCallback,
                 void *AppNotifyCallbackCtx);

CSSM_RETURN CSSMAPI
CSSM_ModuleUnload (const CSSM_GUID *ModuleGuid,
                   CSSM_API_ModuleEventHandler AppNotifyCallback,
                   void *AppNotifyCallbackCtx);

CSSM_RETURN CSSMAPI
CSSM_Introduce (const CSSM_GUID *ModuleID,
                CSSM_KEY_HIERARCHY KeyHierarchy);

CSSM_RETURN CSSMAPI
CSSM_Unintroduce (const CSSM_GUID *ModuleID);

CSSM_RETURN CSSMAPI
CSSM_ModuleAttach (const CSSM_GUID *ModuleGuid,
                   const CSSM_VERSION *Version,
                   const CSSM_API_MEMORY_FUNCS *MemoryFuncs,
                   uint32 SubserviceID,
                   CSSM_SERVICE_TYPE SubServiceType,
                   CSSM_ATTACH_FLAGS AttachFlags,
                   CSSM_KEY_HIERARCHY KeyHierarchy,
                   CSSM_FUNC_NAME_ADDR *FunctionTable,
                   uint32 NumFunctionTable,
                   const void *Reserved,
                   CSSM_MODULE_HANDLE_PTR NewModuleHandle);

CSSM_RETURN CSSMAPI
CSSM_ModuleDetach (CSSM_MODULE_HANDLE ModuleHandle);

CSSM_RETURN CSSMAPI
CSSM_SetPrivilege (CSSM_PRIVILEGE Privilege);

CSSM_RETURN CSSMAPI
CSSM_GetPrivilege (CSSM_PRIVILEGE *Privilege);

CSSM_RETURN CSSMAPI
CSSM_GetModuleGUIDFromHandle (CSSM_MODULE_HANDLE ModuleHandle,
                              CSSM_GUID_PTR ModuleGUID);

CSSM_RETURN CSSMAPI
CSSM_GetSubserviceUIDFromHandle (CSSM_MODULE_HANDLE ModuleHandle,
                                 CSSM_SUBSERVICE_UID_PTR SubserviceUID);

CSSM_RETURN CSSMAPI
CSSM_ListAttachedModuleManagers (uint32 *NumberOfModuleManagers,
                                 CSSM_GUID_PTR ModuleManagerGuids);

CSSM_RETURN CSSMAPI
CSSM_GetAPIMemoryFunctions (CSSM_MODULE_HANDLE AddInHandle,
                            CSSM_API_MEMORY_FUNCS_PTR AppMemoryFuncs);


/* Cryptographic Context Operations */

CSSM_RETURN CSSMAPI
CSSM_CSP_CreateSignatureContext (CSSM_CSP_HANDLE CSPHandle,
                                 CSSM_ALGORITHMS AlgorithmID,
                                 const CSSM_ACCESS_CREDENTIALS *AccessCred,
                                 const CSSM_KEY *Key,
                                 CSSM_CC_HANDLE *NewContextHandle);

CSSM_RETURN CSSMAPI
CSSM_CSP_CreateSymmetricContext (CSSM_CSP_HANDLE CSPHandle,
                                 CSSM_ALGORITHMS AlgorithmID,
                                 CSSM_ENCRYPT_MODE Mode,
                                 const CSSM_ACCESS_CREDENTIALS *AccessCred,
                                 const CSSM_KEY *Key,
                                 const CSSM_DATA *InitVector,
                                 CSSM_PADDING Padding,
                                 void *Reserved,
                                 CSSM_CC_HANDLE *NewContextHandle);

CSSM_RETURN CSSMAPI
CSSM_CSP_CreateDigestContext (CSSM_CSP_HANDLE CSPHandle,
                              CSSM_ALGORITHMS AlgorithmID,
                              CSSM_CC_HANDLE *NewContextHandle);

CSSM_RETURN CSSMAPI
CSSM_CSP_CreateMacContext (CSSM_CSP_HANDLE CSPHandle,
                           CSSM_ALGORITHMS AlgorithmID,
                           const CSSM_KEY *Key,
                           CSSM_CC_HANDLE *NewContextHandle);

CSSM_RETURN CSSMAPI
CSSM_CSP_CreateRandomGenContext (CSSM_CSP_HANDLE CSPHandle,
                                 CSSM_ALGORITHMS AlgorithmID,
                                 const CSSM_CRYPTO_DATA *Seed,
                                 uint32 Length,
                                 CSSM_CC_HANDLE *NewContextHandle);

CSSM_RETURN CSSMAPI
CSSM_CSP_CreateAsymmetricContext (CSSM_CSP_HANDLE CSPHandle,
                                  CSSM_ALGORITHMS AlgorithmID,
                                  const CSSM_ACCESS_CREDENTIALS *AccessCred,
                                  const CSSM_KEY *Key,
                                  CSSM_PADDING Padding,
                                  CSSM_CC_HANDLE *NewContextHandle);

CSSM_RETURN CSSMAPI
CSSM_CSP_CreateDeriveKeyContext (CSSM_CSP_HANDLE CSPHandle,
                                 CSSM_ALGORITHMS AlgorithmID,
                                 CSSM_KEY_TYPE DeriveKeyType,
                                 uint32 DeriveKeyLengthInBits,
                                 const CSSM_ACCESS_CREDENTIALS *AccessCred,
                                 const CSSM_KEY *BaseKey,
                                 uint32 IterationCount,
                                 const CSSM_DATA *Salt,
                                 const CSSM_CRYPTO_DATA *Seed,
                                 CSSM_CC_HANDLE *NewContextHandle);

CSSM_RETURN CSSMAPI
CSSM_CSP_CreateKeyGenContext (CSSM_CSP_HANDLE CSPHandle,
                              CSSM_ALGORITHMS AlgorithmID,
                              uint32 KeySizeInBits,
                              const CSSM_CRYPTO_DATA *Seed,
                              const CSSM_DATA *Salt,
                              const CSSM_DATE *StartDate,
                              const CSSM_DATE *EndDate,
                              const CSSM_DATA *Params,
                              CSSM_CC_HANDLE *NewContextHandle);

CSSM_RETURN CSSMAPI
CSSM_CSP_CreatePassThroughContext (CSSM_CSP_HANDLE CSPHandle,
                                   const CSSM_KEY *Key,
                                   CSSM_CC_HANDLE *NewContextHandle);

CSSM_RETURN CSSMAPI
CSSM_GetContext (CSSM_CC_HANDLE CCHandle,
                 CSSM_CONTEXT_PTR *Context);

CSSM_RETURN CSSMAPI
CSSM_FreeContext (CSSM_CONTEXT_PTR Context);

CSSM_RETURN CSSMAPI
CSSM_SetContext (CSSM_CC_HANDLE CCHandle,
                 const CSSM_CONTEXT *Context);

CSSM_RETURN CSSMAPI
CSSM_DeleteContext (CSSM_CC_HANDLE CCHandle);

CSSM_RETURN CSSMAPI
CSSM_GetContextAttribute (const CSSM_CONTEXT *Context,
                          uint32 AttributeType,
                          CSSM_CONTEXT_ATTRIBUTE_PTR *ContextAttribute);

CSSM_RETURN CSSMAPI
CSSM_UpdateContextAttributes (CSSM_CC_HANDLE CCHandle,
                              uint32 NumberOfAttributes,
                              const CSSM_CONTEXT_ATTRIBUTE *ContextAttributes);

CSSM_RETURN CSSMAPI
CSSM_DeleteContextAttributes (CSSM_CC_HANDLE CCHandle,
                              uint32 NumberOfAttributes,
                              const CSSM_CONTEXT_ATTRIBUTE *ContextAttributes);


/* Cryptographic Sessions and Controlled Access to Keys */

CSSM_RETURN CSSMAPI
CSSM_CSP_Login (CSSM_CSP_HANDLE CSPHandle,
                const CSSM_ACCESS_CREDENTIALS *AccessCred,
                const CSSM_DATA *LoginName,
                const void *Reserved);

CSSM_RETURN CSSMAPI
CSSM_CSP_Logout (CSSM_CSP_HANDLE CSPHandle);

CSSM_RETURN CSSMAPI
CSSM_CSP_GetLoginAcl (CSSM_CSP_HANDLE CSPHandle,
                      const CSSM_STRING *SelectionTag,
                      uint32 *NumberOfAclInfos,
                      CSSM_ACL_ENTRY_INFO_PTR *AclInfos);

CSSM_RETURN CSSMAPI
CSSM_CSP_ChangeLoginAcl (CSSM_CSP_HANDLE CSPHandle,
                         const CSSM_ACCESS_CREDENTIALS *AccessCred,
                         const CSSM_ACL_EDIT *AclEdit);

CSSM_RETURN CSSMAPI
CSSM_GetKeyAcl (CSSM_CSP_HANDLE CSPHandle,
                const CSSM_KEY *Key,
                const CSSM_STRING *SelectionTag,
                uint32 *NumberOfAclInfos,
                CSSM_ACL_ENTRY_INFO_PTR *AclInfos);

CSSM_RETURN CSSMAPI
CSSM_ChangeKeyAcl (CSSM_CSP_HANDLE CSPHandle,
                   const CSSM_ACCESS_CREDENTIALS *AccessCred,
                   const CSSM_ACL_EDIT *AclEdit,
                   const CSSM_KEY *Key);

CSSM_RETURN CSSMAPI
CSSM_GetKeyOwner (CSSM_CSP_HANDLE CSPHandle,
                  const CSSM_KEY *Key,
                  CSSM_ACL_OWNER_PROTOTYPE_PTR Owner);

CSSM_RETURN CSSMAPI
CSSM_ChangeKeyOwner (CSSM_CSP_HANDLE CSPHandle,
                     const CSSM_ACCESS_CREDENTIALS *AccessCred,
                     const CSSM_KEY *Key,
                     const CSSM_ACL_OWNER_PROTOTYPE *NewOwner);

CSSM_RETURN CSSMAPI
CSSM_CSP_GetLoginOwner (CSSM_CSP_HANDLE CSPHandle,
                        CSSM_ACL_OWNER_PROTOTYPE_PTR Owner);

CSSM_RETURN CSSMAPI
CSSM_CSP_ChangeLoginOwner (CSSM_CSP_HANDLE CSPHandle,
                           const CSSM_ACCESS_CREDENTIALS *AccessCred,
                           const CSSM_ACL_OWNER_PROTOTYPE *NewOwner);

CSSM_RETURN CSSMAPI
CSSM_SignData (CSSM_CC_HANDLE CCHandle,
               const CSSM_DATA *DataBufs,
               uint32 DataBufCount,
               CSSM_ALGORITHMS DigestAlgorithm,
               CSSM_DATA_PTR Signature);

CSSM_RETURN CSSMAPI
CSSM_SignDataInit (CSSM_CC_HANDLE CCHandle);

CSSM_RETURN CSSMAPI
CSSM_SignDataUpdate (CSSM_CC_HANDLE CCHandle,
                     const CSSM_DATA *DataBufs,
                     uint32 DataBufCount);

CSSM_RETURN CSSMAPI
CSSM_SignDataFinal (CSSM_CC_HANDLE CCHandle,
                    CSSM_DATA_PTR Signature);

CSSM_RETURN CSSMAPI
CSSM_VerifyData (CSSM_CC_HANDLE CCHandle,
                 const CSSM_DATA *DataBufs,
                 uint32 DataBufCount,
                 CSSM_ALGORITHMS DigestAlgorithm,
                 const CSSM_DATA *Signature);

CSSM_RETURN CSSMAPI
CSSM_VerifyDataInit (CSSM_CC_HANDLE CCHandle);

CSSM_RETURN CSSMAPI
CSSM_VerifyDataUpdate (CSSM_CC_HANDLE CCHandle,
                       const CSSM_DATA *DataBufs,
                       uint32 DataBufCount);

CSSM_RETURN CSSMAPI
CSSM_VerifyDataFinal (CSSM_CC_HANDLE CCHandle,
                      const CSSM_DATA *Signature);

CSSM_RETURN CSSMAPI
CSSM_DigestData (CSSM_CC_HANDLE CCHandle,
                 const CSSM_DATA *DataBufs,
                 uint32 DataBufCount,
                 CSSM_DATA_PTR Digest);

CSSM_RETURN CSSMAPI
CSSM_DigestDataInit (CSSM_CC_HANDLE CCHandle);

CSSM_RETURN CSSMAPI
CSSM_DigestDataUpdate (CSSM_CC_HANDLE CCHandle,
                       const CSSM_DATA *DataBufs,
                       uint32 DataBufCount);

CSSM_RETURN CSSMAPI
CSSM_DigestDataClone (CSSM_CC_HANDLE CCHandle,
                      CSSM_CC_HANDLE *ClonednewCCHandle);

CSSM_RETURN CSSMAPI
CSSM_DigestDataFinal (CSSM_CC_HANDLE CCHandle,
                      CSSM_DATA_PTR Digest);

CSSM_RETURN CSSMAPI
CSSM_GenerateMac (CSSM_CC_HANDLE CCHandle,
                  const CSSM_DATA *DataBufs,
                  uint32 DataBufCount,
                  CSSM_DATA_PTR Mac);

CSSM_RETURN CSSMAPI
CSSM_GenerateMacInit (CSSM_CC_HANDLE CCHandle);

CSSM_RETURN CSSMAPI
CSSM_GenerateMacUpdate (CSSM_CC_HANDLE CCHandle,
                        const CSSM_DATA *DataBufs,
                        uint32 DataBufCount);

CSSM_RETURN CSSMAPI
CSSM_GenerateMacFinal (CSSM_CC_HANDLE CCHandle,
                       CSSM_DATA_PTR Mac);

CSSM_RETURN CSSMAPI
CSSM_VerifyMac (CSSM_CC_HANDLE CCHandle,
                const CSSM_DATA *DataBufs,
                uint32 DataBufCount,
                const CSSM_DATA *Mac);

CSSM_RETURN CSSMAPI
CSSM_VerifyMacInit (CSSM_CC_HANDLE CCHandle);

CSSM_RETURN CSSMAPI
CSSM_VerifyMacUpdate (CSSM_CC_HANDLE CCHandle,
                      const CSSM_DATA *DataBufs,
                      uint32 DataBufCount);

CSSM_RETURN CSSMAPI
CSSM_VerifyMacFinal (CSSM_CC_HANDLE CCHandle,
                     const CSSM_DATA *Mac);

CSSM_RETURN CSSMAPI
CSSM_QuerySize (CSSM_CC_HANDLE CCHandle,
                CSSM_BOOL Encrypt,
                uint32 QuerySizeCount,
                CSSM_QUERY_SIZE_DATA_PTR DataBlockSizes);

CSSM_RETURN CSSMAPI
CSSM_EncryptData (CSSM_CC_HANDLE CCHandle,
                  const CSSM_DATA *ClearBufs,
                  uint32 ClearBufCount,
                  CSSM_DATA_PTR CipherBufs,
                  uint32 CipherBufCount,
                  uint32 *bytesEncrypted,
                  CSSM_DATA_PTR RemData);

CSSM_RETURN CSSMAPI
CSSM_EncryptDataP (CSSM_CC_HANDLE CCHandle,
                   const CSSM_DATA *ClearBufs,
                   uint32 ClearBufCount,
                   CSSM_DATA_PTR CipherBufs,
                   uint32 CipherBufCount,
                   uint32 *bytesEncrypted,
                   CSSM_DATA_PTR RemData,
                   CSSM_PRIVILEGE Privilege);

CSSM_RETURN CSSMAPI
CSSM_EncryptDataInit (CSSM_CC_HANDLE CCHandle);

CSSM_RETURN CSSMAPI
CSSM_EncryptDataInitP (CSSM_CC_HANDLE CCHandle,
                       CSSM_PRIVILEGE Privilege);

CSSM_RETURN CSSMAPI
CSSM_EncryptDataUpdate (CSSM_CC_HANDLE CCHandle,
                        const CSSM_DATA *ClearBufs,
                        uint32 ClearBufCount,
                        CSSM_DATA_PTR CipherBufs,
                        uint32 CipherBufCount,
                        uint32 *bytesEncrypted);

CSSM_RETURN CSSMAPI
CSSM_EncryptDataFinal (CSSM_CC_HANDLE CCHandle,
                       CSSM_DATA_PTR RemData);

CSSM_RETURN CSSMAPI
CSSM_DecryptData (CSSM_CC_HANDLE CCHandle,
                  const CSSM_DATA *CipherBufs,
                  uint32 CipherBufCount,
                  CSSM_DATA_PTR ClearBufs,
                  uint32 ClearBufCount,
                  uint32 *bytesDecrypted,
                  CSSM_DATA_PTR RemData);

CSSM_RETURN CSSMAPI
CSSM_DecryptDataP (CSSM_CC_HANDLE CCHandle,
                   const CSSM_DATA *CipherBufs,
                   uint32 CipherBufCount,
                   CSSM_DATA_PTR ClearBufs,
                   uint32 ClearBufCount,
                   uint32 *bytesDecrypted,
                   CSSM_DATA_PTR RemData,
                   CSSM_PRIVILEGE Privilege);

CSSM_RETURN CSSMAPI
CSSM_DecryptDataInit (CSSM_CC_HANDLE CCHandle);

CSSM_RETURN CSSMAPI
CSSM_DecryptDataInitP (CSSM_CC_HANDLE CCHandle,
                       CSSM_PRIVILEGE Privilege);

CSSM_RETURN CSSMAPI
CSSM_DecryptDataUpdate (CSSM_CC_HANDLE CCHandle,
                        const CSSM_DATA *CipherBufs,
                        uint32 CipherBufCount,
                        CSSM_DATA_PTR ClearBufs,
                        uint32 ClearBufCount,
                        uint32 *bytesDecrypted);

CSSM_RETURN CSSMAPI
CSSM_DecryptDataFinal (CSSM_CC_HANDLE CCHandle,
                       CSSM_DATA_PTR RemData);

CSSM_RETURN CSSMAPI
CSSM_QueryKeySizeInBits (CSSM_CSP_HANDLE CSPHandle,
                         CSSM_CC_HANDLE CCHandle,
                         const CSSM_KEY *Key,
                         CSSM_KEY_SIZE_PTR KeySize);

CSSM_RETURN CSSMAPI
CSSM_GenerateKey (CSSM_CC_HANDLE CCHandle,
                  uint32 KeyUsage,
                  uint32 KeyAttr,
                  const CSSM_DATA *KeyLabel,
                  const CSSM_RESOURCE_CONTROL_CONTEXT *CredAndAclEntry,
                  CSSM_KEY_PTR Key);

CSSM_RETURN CSSMAPI
CSSM_GenerateKeyP (CSSM_CC_HANDLE CCHandle,
                   uint32 KeyUsage,
                   uint32 KeyAttr,
                   const CSSM_DATA *KeyLabel,
                   const CSSM_RESOURCE_CONTROL_CONTEXT *CredAndAclEntry,
                   CSSM_KEY_PTR Key,
                   CSSM_PRIVILEGE Privilege);

CSSM_RETURN CSSMAPI
CSSM_GenerateKeyPair (CSSM_CC_HANDLE CCHandle,
                      uint32 PublicKeyUsage,
                      uint32 PublicKeyAttr,
                      const CSSM_DATA *PublicKeyLabel,
                      CSSM_KEY_PTR PublicKey,
                      uint32 PrivateKeyUsage,
                      uint32 PrivateKeyAttr,
                      const CSSM_DATA *PrivateKeyLabel,
                      const CSSM_RESOURCE_CONTROL_CONTEXT *CredAndAclEntry,
                      CSSM_KEY_PTR PrivateKey);

CSSM_RETURN CSSMAPI
CSSM_GenerateKeyPairP (CSSM_CC_HANDLE CCHandle,
                       uint32 PublicKeyUsage,
                       uint32 PublicKeyAttr,
                       const CSSM_DATA *PublicKeyLabel,
                       CSSM_KEY_PTR PublicKey,
                       uint32 PrivateKeyUsage,
                       uint32 PrivateKeyAttr,
                       const CSSM_DATA *PrivateKeyLabel,
                       const CSSM_RESOURCE_CONTROL_CONTEXT *CredAndAclEntry,
                       CSSM_KEY_PTR PrivateKey,
                       CSSM_PRIVILEGE Privilege);

CSSM_RETURN CSSMAPI
CSSM_GenerateRandom (CSSM_CC_HANDLE CCHandle,
                     CSSM_DATA_PTR RandomNumber);

CSSM_RETURN CSSMAPI
CSSM_CSP_ObtainPrivateKeyFromPublicKey (CSSM_CSP_HANDLE CSPHandle,
                                        const CSSM_KEY *PublicKey,
                                        CSSM_KEY_PTR PrivateKey);

CSSM_RETURN CSSMAPI
CSSM_WrapKey (CSSM_CC_HANDLE CCHandle,
              const CSSM_ACCESS_CREDENTIALS *AccessCred,
              const CSSM_KEY *Key,
              const CSSM_DATA *DescriptiveData,
              CSSM_WRAP_KEY_PTR WrappedKey);

CSSM_RETURN CSSMAPI
CSSM_UnwrapKey (CSSM_CC_HANDLE CCHandle,
                const CSSM_KEY *PublicKey,
                const CSSM_WRAP_KEY *WrappedKey,
                uint32 KeyUsage,
                uint32 KeyAttr,
                const CSSM_DATA *KeyLabel,
                const CSSM_RESOURCE_CONTROL_CONTEXT *CredAndAclEntry,
                CSSM_KEY_PTR UnwrappedKey,
                CSSM_DATA_PTR DescriptiveData);

CSSM_RETURN CSSMAPI
CSSM_WrapKeyP (CSSM_CC_HANDLE CCHandle,
               const CSSM_ACCESS_CREDENTIALS *AccessCred,
               const CSSM_KEY *Key,
               const CSSM_DATA *DescriptiveData,
               CSSM_WRAP_KEY_PTR WrappedKey,
               CSSM_PRIVILEGE Privilege);

CSSM_RETURN CSSMAPI
CSSM_UnwrapKeyP (CSSM_CC_HANDLE CCHandle,
                 const CSSM_KEY *PublicKey,
                 const CSSM_WRAP_KEY *WrappedKey,
                 uint32 KeyUsage,
                 uint32 KeyAttr,
                 const CSSM_DATA *KeyLabel,
                 const CSSM_RESOURCE_CONTROL_CONTEXT *CredAndAclEntry,
                 CSSM_KEY_PTR UnwrappedKey,
                 CSSM_DATA_PTR DescriptiveData,
                 CSSM_PRIVILEGE Privilege);

CSSM_RETURN CSSMAPI
CSSM_DeriveKey (CSSM_CC_HANDLE CCHandle,
                CSSM_DATA_PTR Param,
                uint32 KeyUsage,
                uint32 KeyAttr,
                const CSSM_DATA *KeyLabel,
                const CSSM_RESOURCE_CONTROL_CONTEXT *CredAndAclEntry,
                CSSM_KEY_PTR DerivedKey);

CSSM_RETURN CSSMAPI
CSSM_FreeKey (CSSM_CSP_HANDLE CSPHandle,
              const CSSM_ACCESS_CREDENTIALS *AccessCred,
              CSSM_KEY_PTR KeyPtr,
              CSSM_BOOL Delete);

CSSM_RETURN CSSMAPI
CSSM_GenerateAlgorithmParams (CSSM_CC_HANDLE CCHandle,
                              uint32 ParamBits,
                              CSSM_DATA_PTR Param);


/* Miscellaneous Functions for Cryptographic Services */

CSSM_RETURN CSSMAPI
CSSM_CSP_GetOperationalStatistics (CSSM_CSP_HANDLE CSPHandle,
                                   CSSM_CSP_OPERATIONAL_STATISTICS *Statistics);

CSSM_RETURN CSSMAPI
CSSM_GetTimeValue (CSSM_CSP_HANDLE CSPHandle,
                   CSSM_ALGORITHMS TimeAlgorithm,
                   CSSM_DATA *TimeData);

CSSM_RETURN CSSMAPI
CSSM_RetrieveUniqueId (CSSM_CSP_HANDLE CSPHandle,
                       CSSM_DATA_PTR UniqueID);

CSSM_RETURN CSSMAPI
CSSM_RetrieveCounter (CSSM_CSP_HANDLE CSPHandle,
                      CSSM_DATA_PTR Counter);

CSSM_RETURN CSSMAPI
CSSM_VerifyDevice (CSSM_CSP_HANDLE CSPHandle,
                   const CSSM_DATA *DeviceCert);


/* Extensibility Functions for Cryptographic Services */

CSSM_RETURN CSSMAPI
CSSM_CSP_PassThrough (CSSM_CC_HANDLE CCHandle,
                      uint32 PassThroughId,
                      const void *InData,
                      void **OutData);


/* Trust Policy Operations */

CSSM_RETURN CSSMAPI
CSSM_TP_SubmitCredRequest (CSSM_TP_HANDLE TPHandle,
                           const CSSM_TP_AUTHORITY_ID *PreferredAuthority,
                           CSSM_TP_AUTHORITY_REQUEST_TYPE RequestType,
                           const CSSM_TP_REQUEST_SET *RequestInput,
                           const CSSM_TP_CALLERAUTH_CONTEXT *CallerAuthContext,
                           sint32 *EstimatedTime,
                           CSSM_DATA_PTR ReferenceIdentifier);

CSSM_RETURN CSSMAPI
CSSM_TP_RetrieveCredResult (CSSM_TP_HANDLE TPHandle,
                            const CSSM_DATA *ReferenceIdentifier,
                            const CSSM_TP_CALLERAUTH_CONTEXT *CallerAuthCredentials,
                            sint32 *EstimatedTime,
                            CSSM_BOOL *ConfirmationRequired,
                            CSSM_TP_RESULT_SET_PTR *RetrieveOutput);

CSSM_RETURN CSSMAPI
CSSM_TP_ConfirmCredResult (CSSM_TP_HANDLE TPHandle,
                           const CSSM_DATA *ReferenceIdentifier,
                           const CSSM_TP_CALLERAUTH_CONTEXT *CallerAuthCredentials,
                           const CSSM_TP_CONFIRM_RESPONSE *Responses,
                           const CSSM_TP_AUTHORITY_ID *PreferredAuthority);

CSSM_RETURN CSSMAPI
CSSM_TP_ReceiveConfirmation (CSSM_TP_HANDLE TPHandle,
                             const CSSM_DATA *ReferenceIdentifier,
                             CSSM_TP_CONFIRM_RESPONSE_PTR *Responses,
                             sint32 *ElapsedTime);

CSSM_RETURN CSSMAPI
CSSM_TP_CertReclaimKey (CSSM_TP_HANDLE TPHandle,
                        const CSSM_CERTGROUP *CertGroup,
                        uint32 CertIndex,
                        CSSM_LONG_HANDLE KeyCacheHandle,
                        CSSM_CSP_HANDLE CSPHandle,
                        const CSSM_RESOURCE_CONTROL_CONTEXT *CredAndAclEntry);

CSSM_RETURN CSSMAPI
CSSM_TP_CertReclaimAbort (CSSM_TP_HANDLE TPHandle,
                          CSSM_LONG_HANDLE KeyCacheHandle);

CSSM_RETURN CSSMAPI
CSSM_TP_FormRequest (CSSM_TP_HANDLE TPHandle,
                     const CSSM_TP_AUTHORITY_ID *PreferredAuthority,
                     CSSM_TP_FORM_TYPE FormType,
                     CSSM_DATA_PTR BlankForm);

CSSM_RETURN CSSMAPI
CSSM_TP_FormSubmit (CSSM_TP_HANDLE TPHandle,
                    CSSM_TP_FORM_TYPE FormType,
                    const CSSM_DATA *Form,
                    const CSSM_TP_AUTHORITY_ID *ClearanceAuthority,
                    const CSSM_TP_AUTHORITY_ID *RepresentedAuthority,
                    CSSM_ACCESS_CREDENTIALS_PTR Credentials);

CSSM_RETURN CSSMAPI
CSSM_TP_CertGroupVerify (CSSM_TP_HANDLE TPHandle,
                         CSSM_CL_HANDLE CLHandle,
                         CSSM_CSP_HANDLE CSPHandle,
                         const CSSM_CERTGROUP *CertGroupToBeVerified,
                         const CSSM_TP_VERIFY_CONTEXT *VerifyContext,
                         CSSM_TP_VERIFY_CONTEXT_RESULT_PTR VerifyContextResult);

CSSM_RETURN CSSMAPI
CSSM_TP_CertCreateTemplate (CSSM_TP_HANDLE TPHandle,
                            CSSM_CL_HANDLE CLHandle,
                            uint32 NumberOfFields,
                            const CSSM_FIELD *CertFields,
                            CSSM_DATA_PTR CertTemplate);

CSSM_RETURN CSSMAPI
CSSM_TP_CertGetAllTemplateFields (CSSM_TP_HANDLE TPHandle,
                                  CSSM_CL_HANDLE CLHandle,
                                  const CSSM_DATA *CertTemplate,
                                  uint32 *NumberOfFields,
                                  CSSM_FIELD_PTR *CertFields);

CSSM_RETURN CSSMAPI
CSSM_TP_CertSign (CSSM_TP_HANDLE TPHandle,
                  CSSM_CL_HANDLE CLHandle,
                  CSSM_CC_HANDLE CCHandle,
                  const CSSM_DATA *CertTemplateToBeSigned,
                  const CSSM_CERTGROUP *SignerCertGroup,
                  const CSSM_TP_VERIFY_CONTEXT *SignerVerifyContext,
                  CSSM_TP_VERIFY_CONTEXT_RESULT_PTR SignerVerifyResult,
                  CSSM_DATA_PTR SignedCert);

CSSM_RETURN CSSMAPI
CSSM_TP_CrlVerify (CSSM_TP_HANDLE TPHandle,
                   CSSM_CL_HANDLE CLHandle,
                   CSSM_CSP_HANDLE CSPHandle,
                   const CSSM_ENCODED_CRL *CrlToBeVerified,
                   const CSSM_CERTGROUP *SignerCertGroup,
                   const CSSM_TP_VERIFY_CONTEXT *VerifyContext,
                   CSSM_TP_VERIFY_CONTEXT_RESULT_PTR RevokerVerifyResult);

CSSM_RETURN CSSMAPI
CSSM_TP_CrlCreateTemplate (CSSM_TP_HANDLE TPHandle,
                           CSSM_CL_HANDLE CLHandle,
                           uint32 NumberOfFields,
                           const CSSM_FIELD *CrlFields,
                           CSSM_DATA_PTR NewCrlTemplate);

CSSM_RETURN CSSMAPI
CSSM_TP_CertRevoke (CSSM_TP_HANDLE TPHandle,
                    CSSM_CL_HANDLE CLHandle,
                    CSSM_CSP_HANDLE CSPHandle,
                    const CSSM_DATA *OldCrlTemplate,
                    const CSSM_CERTGROUP *CertGroupToBeRevoked,
                    const CSSM_CERTGROUP *RevokerCertGroup,
                    const CSSM_TP_VERIFY_CONTEXT *RevokerVerifyContext,
                    CSSM_TP_VERIFY_CONTEXT_RESULT_PTR RevokerVerifyResult,
                    CSSM_TP_CERTCHANGE_REASON Reason,
                    CSSM_DATA_PTR NewCrlTemplate);

CSSM_RETURN CSSMAPI
CSSM_TP_CertRemoveFromCrlTemplate (CSSM_TP_HANDLE TPHandle,
                                   CSSM_CL_HANDLE CLHandle,
                                   CSSM_CSP_HANDLE CSPHandle,
                                   const CSSM_DATA *OldCrlTemplate,
                                   const CSSM_CERTGROUP *CertGroupToBeRemoved,
                                   const CSSM_CERTGROUP *RevokerCertGroup,
                                   const CSSM_TP_VERIFY_CONTEXT *RevokerVerifyContext,
                                   CSSM_TP_VERIFY_CONTEXT_RESULT_PTR RevokerVerifyResult,
                                   CSSM_DATA_PTR NewCrlTemplate);

CSSM_RETURN CSSMAPI
CSSM_TP_CrlSign (CSSM_TP_HANDLE TPHandle,
                 CSSM_CL_HANDLE CLHandle,
                 CSSM_CC_HANDLE CCHandle,
                 const CSSM_ENCODED_CRL *CrlToBeSigned,
                 const CSSM_CERTGROUP *SignerCertGroup,
                 const CSSM_TP_VERIFY_CONTEXT *SignerVerifyContext,
                 CSSM_TP_VERIFY_CONTEXT_RESULT_PTR SignerVerifyResult,
                 CSSM_DATA_PTR SignedCrl);

CSSM_RETURN CSSMAPI
CSSM_TP_ApplyCrlToDb (CSSM_TP_HANDLE TPHandle,
                      CSSM_CL_HANDLE CLHandle,
                      CSSM_CSP_HANDLE CSPHandle,
                      const CSSM_ENCODED_CRL *CrlToBeApplied,
                      const CSSM_CERTGROUP *SignerCertGroup,
                      const CSSM_TP_VERIFY_CONTEXT *ApplyCrlVerifyContext,
                      CSSM_TP_VERIFY_CONTEXT_RESULT_PTR ApplyCrlVerifyResult);

CSSM_RETURN CSSMAPI
CSSM_TP_CertGroupConstruct (CSSM_TP_HANDLE TPHandle,
                            CSSM_CL_HANDLE CLHandle,
                            CSSM_CSP_HANDLE CSPHandle,
                            const CSSM_DL_DB_LIST *DBList,
                            const void *ConstructParams,
                            const CSSM_CERTGROUP *CertGroupFrag,
                            CSSM_CERTGROUP_PTR *CertGroup);

CSSM_RETURN CSSMAPI
CSSM_TP_CertGroupPrune (CSSM_TP_HANDLE TPHandle,
                        CSSM_CL_HANDLE CLHandle,
                        const CSSM_DL_DB_LIST *DBList,
                        const CSSM_CERTGROUP *OrderedCertGroup,
                        CSSM_CERTGROUP_PTR *PrunedCertGroup);

CSSM_RETURN CSSMAPI
CSSM_TP_CertGroupToTupleGroup (CSSM_TP_HANDLE TPHandle,
                               CSSM_CL_HANDLE CLHandle,
                               const CSSM_CERTGROUP *CertGroup,
                               CSSM_TUPLEGROUP_PTR *TupleGroup);

CSSM_RETURN CSSMAPI
CSSM_TP_TupleGroupToCertGroup (CSSM_TP_HANDLE TPHandle,
                               CSSM_CL_HANDLE CLHandle,
                               const CSSM_TUPLEGROUP *TupleGroup,
                               CSSM_CERTGROUP_PTR *CertTemplates);

CSSM_RETURN CSSMAPI
CSSM_TP_PassThrough (CSSM_TP_HANDLE TPHandle,
                     CSSM_CL_HANDLE CLHandle,
                     CSSM_CC_HANDLE CCHandle,
                     const CSSM_DL_DB_LIST *DBList,
                     uint32 PassThroughId,
                     const void *InputParams,
                     void **OutputParams);


/* Authorization Computation Operations */

CSSM_RETURN CSSMAPI
CSSM_AC_AuthCompute (CSSM_AC_HANDLE ACHandle,
                     const CSSM_TUPLEGROUP *BaseAuthorizations,
                     const CSSM_TUPLEGROUP *Credentials,
                     uint32 NumberOfRequestors,
                     const CSSM_LIST *Requestors,
                     const CSSM_LIST *RequestedAuthorizationPeriod,
                     const CSSM_LIST *RequestedAuthorization,
                     CSSM_TUPLEGROUP_PTR AuthorizationResult);

CSSM_RETURN CSSMAPI
CSSM_AC_PassThrough (CSSM_AC_HANDLE ACHandle,
                     CSSM_TP_HANDLE TPHandle,
                     CSSM_CL_HANDLE CLHandle,
                     CSSM_CC_HANDLE CCHandle,
                     const CSSM_DL_DB_LIST *DBList,
                     uint32 PassThroughId,
                     const void *InputParams,
                     void **OutputParams);


/* Certificate Library Operations */

CSSM_RETURN CSSMAPI
CSSM_CL_CertCreateTemplate (CSSM_CL_HANDLE CLHandle,
                            uint32 NumberOfFields,
                            const CSSM_FIELD *CertFields,
                            CSSM_DATA_PTR CertTemplate);

CSSM_RETURN CSSMAPI
CSSM_CL_CertGetAllTemplateFields (CSSM_CL_HANDLE CLHandle,
                                  const CSSM_DATA *CertTemplate,
                                  uint32 *NumberOfFields,
                                  CSSM_FIELD_PTR *CertFields);

CSSM_RETURN CSSMAPI
CSSM_CL_CertSign (CSSM_CL_HANDLE CLHandle,
                  CSSM_CC_HANDLE CCHandle,
                  const CSSM_DATA *CertTemplate,
                  const CSSM_FIELD *SignScope,
                  uint32 ScopeSize,
                  CSSM_DATA_PTR SignedCert);

CSSM_RETURN CSSMAPI
CSSM_CL_CertVerify (CSSM_CL_HANDLE CLHandle,
                    CSSM_CC_HANDLE CCHandle,
                    const CSSM_DATA *CertToBeVerified,
                    const CSSM_DATA *SignerCert,
                    const CSSM_FIELD *VerifyScope,
                    uint32 ScopeSize);

CSSM_RETURN CSSMAPI
CSSM_CL_CertVerifyWithKey (CSSM_CL_HANDLE CLHandle,
                           CSSM_CC_HANDLE CCHandle,
                           const CSSM_DATA *CertToBeVerified);

CSSM_RETURN CSSMAPI
CSSM_CL_CertGetFirstFieldValue (CSSM_CL_HANDLE CLHandle,
                                const CSSM_DATA *Cert,
                                const CSSM_OID *CertField,
                                CSSM_HANDLE_PTR ResultsHandle,
                                uint32 *NumberOfMatchedFields,
                                CSSM_DATA_PTR *Value);

CSSM_RETURN CSSMAPI
CSSM_CL_CertGetNextFieldValue (CSSM_CL_HANDLE CLHandle,
                               CSSM_HANDLE ResultsHandle,
                               CSSM_DATA_PTR *Value);

CSSM_RETURN CSSMAPI
CSSM_CL_CertAbortQuery (CSSM_CL_HANDLE CLHandle,
                        CSSM_HANDLE ResultsHandle);

CSSM_RETURN CSSMAPI
CSSM_CL_CertGetKeyInfo (CSSM_CL_HANDLE CLHandle,
                        const CSSM_DATA *Cert,
                        CSSM_KEY_PTR *Key);

CSSM_RETURN CSSMAPI
CSSM_CL_CertGetAllFields (CSSM_CL_HANDLE CLHandle,
                          const CSSM_DATA *Cert,
                          uint32 *NumberOfFields,
                          CSSM_FIELD_PTR *CertFields);

CSSM_RETURN CSSMAPI
CSSM_CL_FreeFields (CSSM_CL_HANDLE CLHandle,
                    uint32 NumberOfFields,
                    CSSM_FIELD_PTR *Fields);

CSSM_RETURN CSSMAPI
CSSM_CL_FreeFieldValue (CSSM_CL_HANDLE CLHandle,
                        const CSSM_OID *CertOrCrlOid,
                        CSSM_DATA_PTR Value);

CSSM_RETURN CSSMAPI
CSSM_CL_CertCache (CSSM_CL_HANDLE CLHandle,
                   const CSSM_DATA *Cert,
                   CSSM_HANDLE_PTR CertHandle);

CSSM_RETURN CSSMAPI
CSSM_CL_CertGetFirstCachedFieldValue (CSSM_CL_HANDLE CLHandle,
                                      CSSM_HANDLE CertHandle,
                                      const CSSM_OID *CertField,
                                      CSSM_HANDLE_PTR ResultsHandle,
                                      uint32 *NumberOfMatchedFields,
                                      CSSM_DATA_PTR *Value);

CSSM_RETURN CSSMAPI
CSSM_CL_CertGetNextCachedFieldValue (CSSM_CL_HANDLE CLHandle,
                                     CSSM_HANDLE ResultsHandle,
                                     CSSM_DATA_PTR *Value);

CSSM_RETURN CSSMAPI
CSSM_CL_CertAbortCache (CSSM_CL_HANDLE CLHandle,
                        CSSM_HANDLE CertHandle);

CSSM_RETURN CSSMAPI
CSSM_CL_CertGroupToSignedBundle (CSSM_CL_HANDLE CLHandle,
                                 CSSM_CC_HANDLE CCHandle,
                                 const CSSM_CERTGROUP *CertGroupToBundle,
                                 const CSSM_CERT_BUNDLE_HEADER *BundleInfo,
                                 CSSM_DATA_PTR SignedBundle);

CSSM_RETURN CSSMAPI
CSSM_CL_CertGroupFromVerifiedBundle (CSSM_CL_HANDLE CLHandle,
                                     CSSM_CC_HANDLE CCHandle,
                                     const CSSM_CERT_BUNDLE *CertBundle,
                                     const CSSM_DATA *SignerCert,
                                     CSSM_CERTGROUP_PTR *CertGroup);

CSSM_RETURN CSSMAPI
CSSM_CL_CertDescribeFormat (CSSM_CL_HANDLE CLHandle,
                            uint32 *NumberOfFields,
                            CSSM_OID_PTR *OidList);

CSSM_RETURN CSSMAPI
CSSM_CL_CrlCreateTemplate (CSSM_CL_HANDLE CLHandle,
                           uint32 NumberOfFields,
                           const CSSM_FIELD *CrlTemplate,
                           CSSM_DATA_PTR NewCrl);

CSSM_RETURN CSSMAPI
CSSM_CL_CrlSetFields (CSSM_CL_HANDLE CLHandle,
                      uint32 NumberOfFields,
                      const CSSM_FIELD *CrlTemplate,
                      const CSSM_DATA *OldCrl,
                      CSSM_DATA_PTR ModifiedCrl);

CSSM_RETURN CSSMAPI
CSSM_CL_CrlAddCert (CSSM_CL_HANDLE CLHandle,
                    CSSM_CC_HANDLE CCHandle,
                    const CSSM_DATA *Cert,
                    uint32 NumberOfFields,
                    const CSSM_FIELD *CrlEntryFields,
                    const CSSM_DATA *OldCrl,
                    CSSM_DATA_PTR NewCrl);

CSSM_RETURN CSSMAPI
CSSM_CL_CrlRemoveCert (CSSM_CL_HANDLE CLHandle,
                       const CSSM_DATA *Cert,
                       const CSSM_DATA *OldCrl,
                       CSSM_DATA_PTR NewCrl);

CSSM_RETURN CSSMAPI
CSSM_CL_CrlSign (CSSM_CL_HANDLE CLHandle,
                 CSSM_CC_HANDLE CCHandle,
                 const CSSM_DATA *UnsignedCrl,
                 const CSSM_FIELD *SignScope,
                 uint32 ScopeSize,
                 CSSM_DATA_PTR SignedCrl);

CSSM_RETURN CSSMAPI
CSSM_CL_CrlVerify (CSSM_CL_HANDLE CLHandle,
                   CSSM_CC_HANDLE CCHandle,
                   const CSSM_DATA *CrlToBeVerified,
                   const CSSM_DATA *SignerCert,
                   const CSSM_FIELD *VerifyScope,
                   uint32 ScopeSize);

CSSM_RETURN CSSMAPI
CSSM_CL_CrlVerifyWithKey (CSSM_CL_HANDLE CLHandle,
                          CSSM_CC_HANDLE CCHandle,
                          const CSSM_DATA *CrlToBeVerified);

CSSM_RETURN CSSMAPI
CSSM_CL_IsCertInCrl (CSSM_CL_HANDLE CLHandle,
                     const CSSM_DATA *Cert,
                     const CSSM_DATA *Crl,
                     CSSM_BOOL *CertFound);

CSSM_RETURN CSSMAPI
CSSM_CL_CrlGetFirstFieldValue (CSSM_CL_HANDLE CLHandle,
                               const CSSM_DATA *Crl,
                               const CSSM_OID *CrlField,
                               CSSM_HANDLE_PTR ResultsHandle,
                               uint32 *NumberOfMatchedFields,
                               CSSM_DATA_PTR *Value);

CSSM_RETURN CSSMAPI
CSSM_CL_CrlGetNextFieldValue (CSSM_CL_HANDLE CLHandle,
                              CSSM_HANDLE ResultsHandle,
                              CSSM_DATA_PTR *Value);

CSSM_RETURN CSSMAPI
CSSM_CL_CrlAbortQuery (CSSM_CL_HANDLE CLHandle,
                       CSSM_HANDLE ResultsHandle);

CSSM_RETURN CSSMAPI
CSSM_CL_CrlGetAllFields (CSSM_CL_HANDLE CLHandle,
                         const CSSM_DATA *Crl,
                         uint32 *NumberOfCrlFields,
                         CSSM_FIELD_PTR *CrlFields);

CSSM_RETURN CSSMAPI
CSSM_CL_CrlCache (CSSM_CL_HANDLE CLHandle,
                  const CSSM_DATA *Crl,
                  CSSM_HANDLE_PTR CrlHandle);

CSSM_RETURN CSSMAPI
CSSM_CL_IsCertInCachedCrl (CSSM_CL_HANDLE CLHandle,
                           const CSSM_DATA *Cert,
                           CSSM_HANDLE CrlHandle,
                           CSSM_BOOL *CertFound,
                           CSSM_DATA_PTR CrlRecordIndex);

CSSM_RETURN CSSMAPI
CSSM_CL_CrlGetFirstCachedFieldValue (CSSM_CL_HANDLE CLHandle,
                                     CSSM_HANDLE CrlHandle,
                                     const CSSM_DATA *CrlRecordIndex,
                                     const CSSM_OID *CrlField,
                                     CSSM_HANDLE_PTR ResultsHandle,
                                     uint32 *NumberOfMatchedFields,
                                     CSSM_DATA_PTR *Value);

CSSM_RETURN CSSMAPI
CSSM_CL_CrlGetNextCachedFieldValue (CSSM_CL_HANDLE CLHandle,
                                    CSSM_HANDLE ResultsHandle,
                                    CSSM_DATA_PTR *Value);

CSSM_RETURN CSSMAPI
CSSM_CL_CrlGetAllCachedRecordFields (CSSM_CL_HANDLE CLHandle,
                                     CSSM_HANDLE CrlHandle,
                                     const CSSM_DATA *CrlRecordIndex,
                                     uint32 *NumberOfFields,
                                     CSSM_FIELD_PTR *CrlFields);

CSSM_RETURN CSSMAPI
CSSM_CL_CrlAbortCache (CSSM_CL_HANDLE CLHandle,
                       CSSM_HANDLE CrlHandle);

CSSM_RETURN CSSMAPI
CSSM_CL_CrlDescribeFormat (CSSM_CL_HANDLE CLHandle,
                           uint32 *NumberOfFields,
                           CSSM_OID_PTR *OidList);

CSSM_RETURN CSSMAPI
CSSM_CL_PassThrough (CSSM_CL_HANDLE CLHandle,
                     CSSM_CC_HANDLE CCHandle,
                     uint32 PassThroughId,
                     const void *InputParams,
                     void **OutputParams);


/* Data Storage Library Operations */

CSSM_RETURN CSSMAPI
CSSM_DL_DbOpen (CSSM_DL_HANDLE DLHandle,
                const char *DbName,
                const CSSM_NET_ADDRESS *DbLocation,
                CSSM_DB_ACCESS_TYPE AccessRequest,
                const CSSM_ACCESS_CREDENTIALS *AccessCred,
                const void *OpenParameters,
                CSSM_DB_HANDLE *DbHandle);

CSSM_RETURN CSSMAPI
CSSM_DL_DbClose (CSSM_DL_DB_HANDLE DLDBHandle);

CSSM_RETURN CSSMAPI
CSSM_DL_DbCreate (CSSM_DL_HANDLE DLHandle,
                  const char *DbName,
                  const CSSM_NET_ADDRESS *DbLocation,
                  const CSSM_DBINFO *DBInfo,
                  CSSM_DB_ACCESS_TYPE AccessRequest,
                  const CSSM_RESOURCE_CONTROL_CONTEXT *CredAndAclEntry,
                  const void *OpenParameters,
                  CSSM_DB_HANDLE *DbHandle);

CSSM_RETURN CSSMAPI
CSSM_DL_DbDelete (CSSM_DL_HANDLE DLHandle,
                  const char *DbName,
                  const CSSM_NET_ADDRESS *DbLocation,
                  const CSSM_ACCESS_CREDENTIALS *AccessCred);

CSSM_RETURN CSSMAPI
CSSM_DL_CreateRelation (CSSM_DL_DB_HANDLE DLDBHandle,
                        CSSM_DB_RECORDTYPE RelationID,
                        const char *RelationName,
                        uint32 NumberOfAttributes,
                        const CSSM_DB_SCHEMA_ATTRIBUTE_INFO *pAttributeInfo,
                        uint32 NumberOfIndexes,
                        const CSSM_DB_SCHEMA_INDEX_INFO *pIndexInfo);

CSSM_RETURN CSSMAPI
CSSM_DL_DestroyRelation (CSSM_DL_DB_HANDLE DLDBHandle,
                         CSSM_DB_RECORDTYPE RelationID);

CSSM_RETURN CSSMAPI
CSSM_DL_Authenticate (CSSM_DL_DB_HANDLE DLDBHandle,
                      CSSM_DB_ACCESS_TYPE AccessRequest,
                      const CSSM_ACCESS_CREDENTIALS *AccessCred);

CSSM_RETURN CSSMAPI
CSSM_DL_GetDbAcl (CSSM_DL_DB_HANDLE DLDBHandle,
                  const CSSM_STRING *SelectionTag,
                  uint32 *NumberOfAclInfos,
                  CSSM_ACL_ENTRY_INFO_PTR *AclInfos);

CSSM_RETURN CSSMAPI
CSSM_DL_ChangeDbAcl (CSSM_DL_DB_HANDLE DLDBHandle,
                     const CSSM_ACCESS_CREDENTIALS *AccessCred,
                     const CSSM_ACL_EDIT *AclEdit);

CSSM_RETURN CSSMAPI
CSSM_DL_GetDbOwner (CSSM_DL_DB_HANDLE DLDBHandle,
                    CSSM_ACL_OWNER_PROTOTYPE_PTR Owner);

CSSM_RETURN CSSMAPI
CSSM_DL_ChangeDbOwner (CSSM_DL_DB_HANDLE DLDBHandle,
                       const CSSM_ACCESS_CREDENTIALS *AccessCred,
                       const CSSM_ACL_OWNER_PROTOTYPE *NewOwner);

CSSM_RETURN CSSMAPI
CSSM_DL_GetDbNames (CSSM_DL_HANDLE DLHandle,
                    CSSM_NAME_LIST_PTR *NameList);

CSSM_RETURN CSSMAPI
CSSM_DL_GetDbNameFromHandle (CSSM_DL_DB_HANDLE DLDBHandle,
                             char **DbName);

CSSM_RETURN CSSMAPI
CSSM_DL_FreeNameList (CSSM_DL_HANDLE DLHandle,
                      CSSM_NAME_LIST_PTR NameList);

CSSM_RETURN CSSMAPI
CSSM_DL_DataInsert (CSSM_DL_DB_HANDLE DLDBHandle,
                    CSSM_DB_RECORDTYPE RecordType,
                    const CSSM_DB_RECORD_ATTRIBUTE_DATA *Attributes,
                    const CSSM_DATA *Data,
                    CSSM_DB_UNIQUE_RECORD_PTR *UniqueId);

CSSM_RETURN CSSMAPI
CSSM_DL_DataDelete (CSSM_DL_DB_HANDLE DLDBHandle,
                    const CSSM_DB_UNIQUE_RECORD *UniqueRecordIdentifier);

CSSM_RETURN CSSMAPI
CSSM_DL_DataModify (CSSM_DL_DB_HANDLE DLDBHandle,
                    CSSM_DB_RECORDTYPE RecordType,
                    CSSM_DB_UNIQUE_RECORD_PTR UniqueRecordIdentifier,
                    const CSSM_DB_RECORD_ATTRIBUTE_DATA *AttributesToBeModified,
                    const CSSM_DATA *DataToBeModified,
                    CSSM_DB_MODIFY_MODE ModifyMode);

CSSM_RETURN CSSMAPI
CSSM_DL_DataGetFirst (CSSM_DL_DB_HANDLE DLDBHandle,
                      const CSSM_QUERY *Query,
                      CSSM_HANDLE_PTR ResultsHandle,
                      CSSM_DB_RECORD_ATTRIBUTE_DATA_PTR Attributes,
                      CSSM_DATA_PTR Data,
                      CSSM_DB_UNIQUE_RECORD_PTR *UniqueId);

CSSM_RETURN CSSMAPI
CSSM_DL_DataGetNext (CSSM_DL_DB_HANDLE DLDBHandle,
                     CSSM_HANDLE ResultsHandle,
                     CSSM_DB_RECORD_ATTRIBUTE_DATA_PTR Attributes,
                     CSSM_DATA_PTR Data,
                     CSSM_DB_UNIQUE_RECORD_PTR *UniqueId);

CSSM_RETURN CSSMAPI
CSSM_DL_DataAbortQuery (CSSM_DL_DB_HANDLE DLDBHandle,
                        CSSM_HANDLE ResultsHandle);

CSSM_RETURN CSSMAPI
CSSM_DL_DataGetFromUniqueRecordId (CSSM_DL_DB_HANDLE DLDBHandle,
                              const CSSM_DB_UNIQUE_RECORD *UniqueRecord,
                              CSSM_DB_RECORD_ATTRIBUTE_DATA_PTR Attributes,
                              CSSM_DATA_PTR Data);

CSSM_RETURN CSSMAPI
CSSM_DL_FreeUniqueRecord (CSSM_DL_DB_HANDLE DLDBHandle,
                          CSSM_DB_UNIQUE_RECORD_PTR UniqueRecord);

CSSM_RETURN CSSMAPI
CSSM_DL_PassThrough (CSSM_DL_DB_HANDLE DLDBHandle,
                uint32 PassThroughId,
                const void *InputParams,
                void **OutputParams);

#ifdef __cplusplus
}
#endif

#endif /* _CSSMAPI_H_ */
