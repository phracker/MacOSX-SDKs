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
	@header SecAccess
	SecAccess implements a way to set and manipulate access control rules and
	restrictions on SecKeychainItems.
*/

#ifndef _SECURITY_SECACCESS_H_
#define _SECURITY_SECACCESS_H_

#include <Security/SecBase.h>
#include <Security/cssmtype.h>
#include <CoreFoundation/CFArray.h>


#if defined(__cplusplus)
extern "C" {
#endif

/*!
	@function SecAccessGetTypeID
	@abstract Returns the type identifier of SecAccess instances.
	@result The CFTypeID of SecAccess instances.
*/
CFTypeID SecAccessGetTypeID(void);

/*!
	@function SecAccessCreate
	@abstract Creates a new SecAccessRef that is set to the currently designated system default
		configuration of a (newly created) security object. Note that the precise nature of
		this default may change between releases.
	@param descriptor The name of the item as it should appear in security dialogs
	@param trustedlist A CFArray of TrustedApplicationRefs, specifying which applications
		should be allowed to access an item without triggering confirmation dialogs.
		If NULL, defaults to (just) the application creating the item. To set no applications,
		pass a CFArray with no elements.
	@param accessRef On return, a pointer to the new access reference.
	@result A result code.  See "Security Error Codes" (SecBase.h).
*/
OSStatus SecAccessCreate(CFStringRef descriptor, CFArrayRef trustedlist, SecAccessRef *accessRef);

/*!
	@function SecAccessCreateFromOwnerAndACL
	@abstract Creates a new SecAccessRef using the owner and access control list you provide.
	@param owner A pointer to a CSSM access control list owner.
	@param aclCount An unsigned 32-bit integer representing the number of items in the access control list.
	@param acls A pointer to the access control list.
	@param On return, a pointer to the new access reference.
	@result A result code.  See "Security Error Codes" (SecBase.h).
*/
OSStatus SecAccessCreateFromOwnerAndACL(const CSSM_ACL_OWNER_PROTOTYPE *owner, uint32 aclCount, const CSSM_ACL_ENTRY_INFO *acls, SecAccessRef *accessRef);

/*!
	@function SecAccessGetOwnerAndACL
	@abstract Retrieves the owner and the access control list of a given access.
	@param accessRef A reference to the access from which to retrieve the information.
	@param owner On return, a pointer to the access control list owner.
	@param aclCount On return, a pointer to an unsigned 32-bit integer representing the number of items in the access control list.
	@param acls On return, a pointer to the access control list.
	@result A result code.  See "Security Error Codes" (SecBase.h).
 */
OSStatus SecAccessGetOwnerAndACL(SecAccessRef accessRef, CSSM_ACL_OWNER_PROTOTYPE_PTR *owner, uint32 *aclCount, CSSM_ACL_ENTRY_INFO_PTR *acls);

/*!
	@function SecAccessCopyACLList
	@abstract Copies all the access control lists of a given access.
	@param accessRef A reference to the access from which to retrieve the information.
	@param aclList On return, a pointer to a new created CFArray of SecACL instances.  The caller is responsible for calling CFRelease on this array.
	@result A result code.  See "Security Error Codes" (SecBase.h).
*/
OSStatus SecAccessCopyACLList(SecAccessRef accessRef, CFArrayRef *aclList);

/*!
	@function SecAccessCopySelectedACLList
	@abstract Copies selected access control lists from a given access.
	@param accessRef A reference to the access from which to retrieve the information.
	@param action An authorization tag specifying what action with which to select the action control lists.
	@param aclList On return, a pointer to the selected access control lists.
	@result A result code.  See "Security Error Codes" (SecBase.h).
*/
OSStatus SecAccessCopySelectedACLList(SecAccessRef accessRef, CSSM_ACL_AUTHORIZATION_TAG action, CFArrayRef *aclList);


#if defined(__cplusplus)
}
#endif

#endif /* !_SECURITY_SECACCESS_H_ */
