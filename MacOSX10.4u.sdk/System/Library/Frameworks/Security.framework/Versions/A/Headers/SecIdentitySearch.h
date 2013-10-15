/*
 * Copyright (c) 2002-2004 Apple Computer, Inc. All Rights Reserved.
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
	@header SecIdentitySearch
	The functions provided in SecIdentitySearch implement a query for SecIdentity objects.
*/

#ifndef _SECURITY_SECIDENTITYSEARCH_H_
#define _SECURITY_SECIDENTITYSEARCH_H_

#include <Security/SecBase.h>
#include <Security/cssmtype.h>
#include <CoreFoundation/CFArray.h>


#if defined(__cplusplus)
extern "C" {
#endif

/*!
    @typedef SecIdentitySearchRef
    @abstract Contains information about an identity search.
*/
typedef struct OpaqueSecIdentitySearchRef *SecIdentitySearchRef;

/*!
	@function SecIdentitySearchGetTypeID
	@abstract Returns the type identifier of SecIdentitySearch instances.
	@result The CFTypeID of SecIdentitySearch instances.
*/
CFTypeID SecIdentitySearchGetTypeID(void);

/*!
	@function SecIdentitySearchCreate
	@abstract Creates a search reference for finding identities.
    @param keychainOrArray An reference to an array of keychains to search, a single keychain or NULL to search the user's default keychain search list.
	@param keyUsage A CSSM_KEYUSE value as defined in cssmtype.h.  Control the search by specifying the key usage for the identity. Pass in 0 if you want all identities returned by this search.  Passing in  CSSM_KEYUSE_ANY will limit the identities returned to those that can be used for every operation.
    @param searchRef On return, a pointer to the identity search reference. You must release the identity search reference by calling the CFRelease function.
    @result A result code.  See "Security Error Codes" (SecBase.h).
	@discussion You can set values for key usage, and one or more policies, to control the search for identities. You can use the returned search reference to obtain the remaining identities in subsequent calls to the SecIentitySearchCopyNext function. You must release the identity search reference by calling the CFRelease function.
*/
OSStatus SecIdentitySearchCreate(CFTypeRef keychainOrArray, CSSM_KEYUSE keyUsage, SecIdentitySearchRef *searchRef);
    
/*!
	@function SecIdentitySearchCopyNext
    @abstract Finds the next identity matching the given search criteria, as previously specified by a call to SecIdentitySearchCreate.
	@param searchRef A reference to the current identity search.  You create the identity search reference by calling the SecIdentitySearchCreate function.
	@param identity On return, a pointer to an identity reference of the next matching identity, if any. You must call the CFRelease function when finished with the identity search reference.
	@result A result code.  When there are no more identities that match the parameters specified to SecPolicySearchCreate, errSecItemNotFound is returned. See "Security Error Codes" (SecBase.h).
*/
OSStatus SecIdentitySearchCopyNext(SecIdentitySearchRef searchRef, SecIdentityRef *identity);

#if defined(__cplusplus)
}
#endif

#endif /* !_SECURITY_SECIDENTITYSEARCH_H_ */
