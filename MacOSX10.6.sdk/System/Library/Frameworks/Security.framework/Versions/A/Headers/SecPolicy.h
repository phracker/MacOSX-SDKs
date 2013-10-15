/*
 * Copyright (c) 2002-2008 Apple Inc. All Rights Reserved.
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
 */

/*!
    @header SecPolicy
    The functions provided in SecPolicy.h provide an interface to various
	X.509 certificate trust policies.
*/

#ifndef _SECURITY_SECPOLICY_H_
#define _SECURITY_SECPOLICY_H_

#include <CoreFoundation/CFBase.h>
#include <Security/SecBase.h>
#include <Security/cssmtype.h>


#if defined(__cplusplus)
extern "C" {
#endif

/*!
    @function SecPolicyGetTypeID
    @abstract Returns the type identifier of SecPolicy instances.
    @result The CFTypeID of SecPolicy instances.
*/
CFTypeID SecPolicyGetTypeID(void);

/*!
    @function SecPolicyGetOID
    @abstract Returns a policy's object identifier.
    @param policyRef A policy reference.
    @param oid On return, a pointer to the policy's object identifier.
    @result A result code.  See "Security Error Codes" (SecBase.h).
*/
OSStatus SecPolicyGetOID(SecPolicyRef policyRef, CSSM_OID *oid);

/*!
    @function SecPolicyGetValue
    @abstract Returns a policy's value.
    @param policyRef A policy reference.
    @param value On return, a pointer to the policy's value.
    @result A result code.  See "Security Error Codes" (SecBase.h).
*/
OSStatus SecPolicyGetValue(SecPolicyRef policyRef, CSSM_DATA *value);

/*!
    @function SecPolicySetValue
    @abstract Sets a policy's value.
    @param policyRef A policy reference.
    @param value The value to be set into the policy object, replacing any previous value.
    @result A result code.  See "Security Error Codes" (SecBase.h).
*/
OSStatus SecPolicySetValue(SecPolicyRef policyRef, const CSSM_DATA *value);

/*!
    @function SecPolicyGetTPHandle
    @abstract Returns the CSSM trust policy handle for the given policy.
    @param policyRef A policy reference.
    @param tpHandle On return, a pointer to a value of type CSSM_TP_HANDLE.
    @result A result code.  See "Security Error Codes" (SecBase.h).
*/
OSStatus SecPolicyGetTPHandle(SecPolicyRef policyRef, CSSM_TP_HANDLE *tpHandle);

/*!
    @function SecPolicyCreateBasicX509
    @abstract Returns a policy object for the default X.509 policy.
    @result A policy object. The caller is responsible for calling CFRelease
	on this when it is no longer needed.
*/
SecPolicyRef SecPolicyCreateBasicX509(void);

/*!
    @function SecPolicyCreateSSL
    @abstract Returns a policy object for evaluating SSL certificate chains.
	@param server Passing true for this parameter create a policy for SSL
	server certificates.
	@param hostname (Optional) If present, the policy will require the specified
	hostname to match the hostname in the leaf certificate.
    @result A policy object. The caller is responsible for calling CFRelease
	on this when it is no longer needed.
*/
SecPolicyRef SecPolicyCreateSSL(Boolean server, CFStringRef hostname);

#if defined(__cplusplus)
}
#endif

#endif /* !_SECURITY_SECPOLICY_H_ */
