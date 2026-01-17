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
 */

/*!
	@header SecKeychainItem
	SecKeychainItem implements an item which may be stored in a SecKeychain, with publicly
	visible attributes and encrypted data.  The access to the data of an item is protected
	using strong cryptographic algorithms.
*/

#ifndef _SECURITY_SECKEYCHAINITEM_H_
#define _SECURITY_SECKEYCHAINITEM_H_

#include <Security/SecBase.h>
#include <Security/cssmapple.h>

#if defined(__cplusplus)
extern "C" {
#endif

/*!
	@typedef SecItemClass
	@abstract Represents a keychain item's class.
*/
typedef FourCharCode 	SecItemClass;

/*!
	@enum ItemClassConstants
	@abstract Specifies a keychain item's class code.
	@constant kSecInternetPasswordItemClass Indicates that the item is an internet password.
	@constant kSecGenericPasswordItemClass Indicates that the item is a generic password.
	@constant kSecAppleSharePasswordItemClass Indicates that the item is an AppleShare password.
	@constant kSecCertificateItemClass Indicates that the item is a digital certificate.
	@discussion The SecItemClass enumeration defines constants your application can use to specify the type of the keychain item you wish to create, dispose, add, delete, update, copy, or locate. You can also use these constants with the tag constant SecItemAttr. 
*/
enum
{
    kSecInternetPasswordItemClass 	= 'inet',
    kSecGenericPasswordItemClass 	= 'genp',
    kSecAppleSharePasswordItemClass	= 'ashp',
    kSecCertificateItemClass      	= CSSM_DL_DB_RECORD_X509_CERTIFICATE,
};

/*!
	@typedef SecItemAttr
	@abstract Represents a keychain item's attributes.

*/
typedef FourCharCode SecItemAttr;

/*!
	@enum ItemAttributeConstants
	@abstract Specifies keychain item attributes.
	@constant kSecCreationDateItemAttr Identifies the creation date attribute. You use this tag to set or get a value of type UInt32 that indicates the date the item was created. 
	@constant kSecModDateItemAttr Identifies the modification date attribute. You use this tag to set or get a value of type UInt32 that indicates the last time the item was updated.
	@constant kSecDescriptionItemAttr Identifies the description attribute. You use this tag to set or get a value of type string that represents a user-visible string describing this particular kind of item (e.g. "disk image password").
	@constant kSecCommentItemAttr Identifies the comment attribute. You use this tag to set or get a value of type string that represents a user-editable string containing comments for this item.
	@constant kSecCreatorItemAttr Identifies the creator attribute. You use this tag to set or get a value that represents the item’s creator. 
	@constant kSecTypeItemAttr Identifies the type attribute. You use this tag to set or get a value that represents the item’s type. 
	@constant kSecScriptCodeItemAttr Identifies the script code attribute. You use this tag to set or get a value of type ScriptCode that represents the script code for all strings. (Note: use of this attribute is deprecated; string attributes should be stored in UTF-8 encoding.)
	@constant kSecLabelItemAttr Identifies the label attribute. You use this tag to set or get a value of type string that represents a user-editable string containing the label for this item. 
	@constant kSecInvisibleItemAttr Identifies the invisible attribute. You use this tag to set or get a value of type Boolean that indicates whether the item is invisible. 
	@constant kSecNegativeItemAttr Identifies the negative attribute. You use this tag to set or get a value of type Boolean that indicates whether there is a valid password associated with this keychain item. This is useful if your application doesn't want a password for some particular service to be stored in the keychain, but prefers that it always be entered by the user. The item (typically invisible and with zero-length data) acts as a placeholder to say “don't use me.”
	@constant kSecCustomIconItemAttr Identifies the custom icon attribute. You use this tag to set or get a value of type Boolean that indicates whether the item has an application-specific icon. To do this, you must also set the attribute value identified by the tag kSecTypeItemAttr to a file type for which there is a corresponding icon in the desktop database, and set the attribute value identified by the tag kSecCreatorItemAttr to an appropriate application creator type. If a custom icon corresponding to the item's type and creator can be found in the desktop database, it will be displayed by Keychain Access. Otherwise, default icons are used. 
	@constant kSecAccountItemAttr Identifies the account attribute. You use this tag to set or get a string that represents the user account. It also applies to generic and AppleShare passwords. 
	@constant kSecServiceItemAttr Identifies the service attribute. You use this tag to set or get a string that represents the service associated with this item (e.g. "iTools"). This is unique to generic password attributes.
	@constant kSecGenericItemAttr Identifies the generic attribute. You use this tag to set or get a value of untyped bytes that represents a user-defined attribute.  This is unique to generic password attributes.
	@constant kSecSecurityDomainItemAttr Identifies the security domain attribute. You use this tag to set or get a value that represents the Internet security domain. This is unique to Internet password attributes.
	@constant kSecServerItemAttr Identifies the server attribute. You use this tag to set or get a value of type string that represents the Internet server’s domain name or IP address. This is unique to Internet password attributes.
	@constant kSecAuthenticationTypeItemAttr Identifies the authentication type attribute. You use this tag to set or get a value of type SecAuthenticationType that represents the Internet authentication scheme. This is unique to Internet password attributes.
	@constant kSecPortItemAttr Identifies the port attribute. You use this tag to set or get a value of type UInt32 that represents the Internet port number. This is unique to Internet password attributes.
	@constant kSecPathItemAttr Identifies the path attribute. You use this tag to set or get a value  that represents the path. This is unique to Internet password attributes.
	@constant kSecVolumeItemAttr Identifies the volume attribute. You use this tag to set or get a value that represents the AppleShare volume. This is unique to AppleShare password attributes.
	@constant kSecAddressItemAttr Identifies the address attribute. You use this tag to set or get a value of type string that represents the AppleTalk zone name, or the IP or domain name that represents the server address. This is unique to AppleShare password attributes.
	@constant kSecSignatureItemAttr Identifies the server signature attribute. You use this tag to set or get a value of type SecAFPServerSignature that represents the server signature block. This is unique to AppleShare password attributes.
	@constant kSecProtocolItemAttr Identifies the protocol attribute. You use this tag to set or get a value of type SecProtocolType that represents the Internet protocol. This is unique to AppleShare and Internet password attributes.
	@constant kSecCertificateType Indicates a CSSM_CERT_TYPE type.
	@constant kSecCertificateEncoding Indicates a CSSM_CERT_ENCODING type.
	@constant kSecCrlType Indicates a CSSM_CRL_TYPE type.
	@constant kSecCrlEncoding Indicates a CSSM_CRL_ENCODING type.
	@constant kSecAlias Indicates an alias.
	@discussion To obtain information about a certificate, use the CDSA Certificate Library (CL) API. To obtain information about a key, use the SecKeyGetCSSMKey function and the CDSA Cryptographic Service Provider (CSP) API.
*/
enum
{											
    kSecCreationDateItemAttr		= 'cdat',
    kSecModDateItemAttr				= 'mdat',
    kSecDescriptionItemAttr			= 'desc',
    kSecCommentItemAttr				= 'icmt',
    kSecCreatorItemAttr				= 'crtr',
    kSecTypeItemAttr				= 'type',
    kSecScriptCodeItemAttr			= 'scrp',
    kSecLabelItemAttr				= 'labl',
    kSecInvisibleItemAttr			= 'invi',
    kSecNegativeItemAttr			= 'nega',
    kSecCustomIconItemAttr			= 'cusi',
    kSecAccountItemAttr				= 'acct',
    kSecServiceItemAttr				= 'svce',
    kSecGenericItemAttr				= 'gena',
    kSecSecurityDomainItemAttr		= 'sdmn',
    kSecServerItemAttr				= 'srvr',
    kSecAuthenticationTypeItemAttr	= 'atyp',
    kSecPortItemAttr				= 'port',
    kSecPathItemAttr				= 'path',
    kSecVolumeItemAttr				= 'vlme',
    kSecAddressItemAttr				= 'addr',
    kSecSignatureItemAttr			= 'ssig',
    kSecProtocolItemAttr			= 'ptcl',
	kSecCertificateType				= 'ctyp',
	kSecCertificateEncoding			= 'cenc',
	kSecCrlType						= 'crtp',
	kSecCrlEncoding					= 'crnc',
	kSecAlias						= 'alis'
};

/*!
	@typedef SecAFPServerSignature
	@abstract Represents a 16-byte Apple File Protocol server signature block.
*/
typedef UInt8	SecAFPServerSignature[16];

/*!
	@typedef SecPublicKeyHash
	@abstract Represents a 20-byte public key hash.
*/
typedef UInt8	SecPublicKeyHash[20];

#pragma mark ———— Keychain Item Management ————
/*!
	@function SecKeychainItemGetTypeID
	@abstract Returns the type identifier of SecKeychainItem instances.
	@result The CFTypeID of SecKeychainItem instances.
*/
CFTypeID SecKeychainItemGetTypeID(void);

/*!
	@function SecKeychainItemModifyAttributesAndData
	@abstract Updates an existing keychain item after changing its attributes or data.
	@param itemRef A reference to the keychain item to modify.
	@param attrList The list of attributes to set.
	@param length The length of the buffer pointed to by data.
	@param data Pointer to a buffer containing the data to store.
    @result A result code.  See "Security Error Codes" (SecBase.h).
	@discussion The keychain item is written to the keychain's permanent data store. If the keychain item has not previously been added to a keychain, a call to the SecKeychainItemModifyContent function does nothing and returns noErr.
*/
OSStatus SecKeychainItemModifyAttributesAndData(SecKeychainItemRef itemRef, const SecKeychainAttributeList *attrList, UInt32 length, const void *data);

/*!
	@function SecKeychainItemCreateFromContent
	@abstract Creates a new keychain item from the supplied parameters.
	@param itemClass A constant identifying the class of item to create.
	@param attrList The list of attributes of the item to create.
	@param length The length of the buffer pointed to by data.
	@param data A pointer to a buffer containing the data to store.
	@param initialAccess A reference to the access for this keychain item.
    @param keychainRef A reference to the keychain in which to add the item.
	@param itemRef On return, a pointer to a reference to the newly created keychain item (optional). When the item reference is no longer required, call CFRelease to deallocate memory occupied by the item.
    @result A result code.  See "Security Error Codes" (SecBase.h). In addition, paramErr (-50) may be returned if not enough valid parameters are supplied, or memFullErr (-108) if there is not enough memory in the current heap zone to create the object.
*/
OSStatus SecKeychainItemCreateFromContent(SecItemClass itemClass, SecKeychainAttributeList *attrList,
		UInt32 length, const void *data, SecKeychainRef keychainRef,
		SecAccessRef initialAccess, SecKeychainItemRef *itemRef);

/*!
	@function SecKeychainItemModifyContent
	@abstract Updates an existing keychain item after changing its attributes or data. This call should only be used in conjunction with SecKeychainItemCopyContent().
	@param itemRef A reference to the keychain item to modify.
	@param attrList The list of attributes to set.
	@param length The length of the buffer pointed to by data.
	@param data A pointer to a buffer containing the data to store.
    @result A result code.  See "Security Error Codes" (SecBase.h).
*/
OSStatus SecKeychainItemModifyContent(SecKeychainItemRef itemRef, const SecKeychainAttributeList *attrList, UInt32 length, const void *data);

/*!
	@function SecKeychainItemCopyContent
	@abstract Copies the data and/or attributes stored in the given keychain item. It is recommended that you use SecKeychainItemCopyAttributesAndData(). You must call SecKeychainItemFreeContent when you no longer need the attributes and data. If you want to modify the attributes returned here, use SecKeychainModifyContent().
	@param itemRef A reference to the keychain item to modify.
	@param itemClass The item's class. You should pass NULL if it is not required.
	@param attrList The list of attributes to get in this item on input, on output the attributes are filled in. You must call SecKeychainItemFreeContent when you no longer need the attributes.
	@param length On return, the length of the buffer pointed to by outData.
	@param outData On return, a pointer to a buffer containing the data in this item. You must call SecKeychainItemFreeContent when you no longer need the data.
    @result A result code.  See "Security Error Codes" (SecBase.h). In addition, paramErr (-50) may be returned if not enough valid parameters are supplied.
*/
OSStatus SecKeychainItemCopyContent(SecKeychainItemRef itemRef, SecItemClass *itemClass, SecKeychainAttributeList *attrList, UInt32 *length, void **outData);

/*!
	@function SecKeychainItemFreeContent
	@abstract Releases the memory used by the keychain attribute list and the keychain data retrieved in a call to SecKeychainItemCopyContent.
	@param attrList A pointer to the attribute list to release.
    @param data A pointer to the data buffer to release.
*/
OSStatus SecKeychainItemFreeContent(SecKeychainAttributeList *attrList, void *data);

/*!
	@function SecKeychainItemCopyAttributesAndData
	@abstract Copies the data and/or attributes stored in the given keychain item. You must call SecKeychainItemFreeAttributesAndData() when you no longer need the attributes and data. If you want to modify the attributes returned here, use SecKeychainModifyAttributesAndData().
	@param itemRef A reference to the keychain item to copy.
	@param info List of tags of attributes to retrieve.
	@param itemClass The item's class. You should pass NULL if not required.
	@param attrList on output, an attribute list with the attributes specified by info. You must call SecKeychainItemFreeAttributesAndData() when you no longer need this list.
	@param length on output the actual length of the data.
	@param outData Pointer to a buffer containing the data in this item. Pass NULL if not required. You must call SecKeychainItemFreeAttributesAndData() when you no longer need the data.
    @result A result code.  See "Security Error Codes" (SecBase.h). In addition, paramErr (-50) may be returned if not enough valid parameters are supplied.
*/
OSStatus SecKeychainItemCopyAttributesAndData(SecKeychainItemRef itemRef, SecKeychainAttributeInfo *info, SecItemClass *itemClass, SecKeychainAttributeList **attrList, UInt32 *length, void **outData);

/*!
	@function SecKeychainItemFreeAttributesAndData
	@abstract Releases the memory used by the keychain attribute list and the keychain data retrieved in a call to SecKeychainItemCopyAttributesAndData.
	@param attrList A pointer to the attribute list to release.
    @param data A pointer to the data buffer to release.
    @result A result code.  See "Security Error Codes" (SecBase.h).
*/
OSStatus SecKeychainItemFreeAttributesAndData(SecKeychainAttributeList *attrList, void *data);

/*!
	@function SecKeychainItemDelete
	@abstract Deletes a keychain item from the default keychain's permanent data store.
	@param itemRef A keychain item reference of the item to delete.
    @result A result code.  See "Security Error Codes" (SecBase.h).
	@discussion  If itemRef has not previously been added to the keychain,  SecKeychainItemDelete does nothing and returns noErr. IMPORTANT: SecKeychainItemDelete does not dispose the memory occupied by the item reference itself; use the CFRelease function when you are completely finished with an item.	
*/
OSStatus SecKeychainItemDelete(SecKeychainItemRef itemRef);

/*!
	@function SecKeychainItemCopyKeychain
	@abstract Copies an existing keychain reference from a keychain item.	
	@param itemRef A keychain item reference of the item to update.
	@param keychainRef On return, a pointer to a keychain reference.  Release this by calling CFRelease function.
    @result A result code.  See "Security Error Codes" (SecBase.h).
*/
OSStatus SecKeychainItemCopyKeychain(SecKeychainItemRef itemRef, SecKeychainRef *keychainRef);

/*!
	@function SecKeychainItemCreateCopy
	@abstract Copies a keychain item.
	@param itemRef A reference to the keychain item to copy.
	@param destKeychainRef A reference to the keychain in which to insert the copied keychain item.
	@param initialAccess The initial access for the copied keychain item.
	@param itemCopy On return, a pointer to a copy of the keychain item referenced by itemRef.
    @result A result code.  See "Security Error Codes" (SecBase.h).
*/
OSStatus SecKeychainItemCreateCopy(SecKeychainItemRef itemRef, SecKeychainRef destKeychainRef,
	SecAccessRef initialAccess, SecKeychainItemRef *itemCopy);


#pragma mark ———— CSSM Bridge Functions ————
/*!
    @function SecKeychainItemGetDLDBHandle
    @abstract Returns the CSSM_DL_DB_HANDLE for a given keychain item reference.
    @param keyItemRef A keychain item reference.
    @param dldbHandle On return, a CSSM_DL_DB_HANDLE for the keychain database containing the given item. The handle is valid until the keychain reference is released.
    @result A result code.  See "Security Error Codes" (SecBase.h).
*/
OSStatus SecKeychainItemGetDLDBHandle(SecKeychainItemRef keyItemRef, CSSM_DL_DB_HANDLE *dldbHandle);

/*!
	@function SecKeychainItemGetUniqueRecordID
	@abstract Returns a CSSM_DB_UNIQUE_RECORD for the given keychain item reference.
	@param itemRef A keychain item reference.
    @param uniqueRecordID On return, a pointer to a CSSM_DB_UNIQUE_RECORD structure for the given item.  The unique record is valid until the item reference is released.
    @result A result code.  See "Security Error Codes" (SecBase.h).
*/
OSStatus SecKeychainItemGetUniqueRecordID(SecKeychainItemRef itemRef, const CSSM_DB_UNIQUE_RECORD **uniqueRecordID);

#pragma mark ———— Keychain Item Access Management ————
/*!
	@function SecKeychainItemCopyAccess
	@abstract Copies the access of a given keychain item.
	@param itemRef A reference to a keychain item.
    @param access On return, a pointer to the keychain item's access.
    @result A result code.  See "Security Error Codes" (SecBase.h).
*/
OSStatus SecKeychainItemCopyAccess(SecKeychainItemRef itemRef, SecAccessRef *access);

/*!
	@function SecKeychainItemSetAccess
	@abstract Sets the access of a given keychain item.
	@param itemRef A reference to a keychain item.
    @param access A reference to an access to replace the keychain item's current access.
    @result A result code.  See "Security Error Codes" (SecBase.h).
*/
OSStatus SecKeychainItemSetAccess(SecKeychainItemRef itemRef, SecAccessRef access);

#if defined(__cplusplus)
}
#endif

#endif /* !_SECURITY_SECKEYCHAINITEM_H_ */
