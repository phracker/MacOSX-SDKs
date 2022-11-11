/*
 * Copyright (c) 2006-2014 Apple Inc. All Rights Reserved.
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
    @header SecItem
    SecItem defines CoreFoundation-based constants and functions for
    access to Security items (certificates, keys, identities, and
    passwords.)
*/

#ifndef _SECURITY_SECITEM_H_
#define _SECURITY_SECITEM_H_

#include <Security/SecBase.h>
#include <CoreFoundation/CFNumber.h>
#include <CoreFoundation/CFArray.h>
#include <CoreFoundation/CFDictionary.h>

__BEGIN_DECLS

CF_ASSUME_NONNULL_BEGIN
CF_IMPLICIT_BRIDGING_ENABLED

/*!
    @enum Class Key Constant
    @discussion Predefined key constant used to get or set item class values in
        a dictionary. Its value is one of the constants defined in the Value
        Constants for kSecClass.
    @constant kSecClass Specifies a dictionary key whose value is the item's
        class code.  You use this key to get or set a value of type CFTypeRef
        that contains the item class code.
*/
extern const CFStringRef kSecClass
    API_AVAILABLE(macos(10.6), ios(2.0));

/*!
    @enum Class Value Constants
    @discussion Predefined item class constants used to get or set values in
        a dictionary. The kSecClass constant is the key and its value is one
        of the constants defined here. Note: on Mac OS X 10.6, only items
        of class kSecClassInternetPassword are supported.
    @constant kSecClassInternetPassword Specifies Internet password items.
    @constant kSecClassGenericPassword Specifies generic password items.
    @constant kSecClassCertificate Specifies certificate items.
    @constant kSecClassKey Specifies key items.
    @constant kSecClassIdentity Specifies identity items.
*/
extern const CFStringRef kSecClassInternetPassword
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecClassGenericPassword
    API_AVAILABLE(macos(10.7), ios(2.0));
extern const CFStringRef kSecClassCertificate
    API_AVAILABLE(macos(10.7), ios(2.0));
extern const CFStringRef kSecClassKey
    API_AVAILABLE(macos(10.7), ios(2.0));
extern const CFStringRef kSecClassIdentity
    API_AVAILABLE(macos(10.7), ios(2.0));

/*!
    @enum Attribute Key Constants
    @discussion Predefined item attribute keys used to get or set values in a
        dictionary. Not all attributes apply to each item class. The table
        below lists the currently defined attributes for each item class:

    kSecClassGenericPassword item attributes:
        kSecAttrAccess (OS X only)
        kSecAttrAccessControl
        kSecAttrAccessGroup (iOS; also OS X if kSecAttrSynchronizable and/or kSecUseDataProtectionKeychain set)
        kSecAttrAccessible (iOS; also OS X if kSecAttrSynchronizable and/or kSecUseDataProtectionKeychain set)
        kSecAttrCreationDate
        kSecAttrModificationDate
        kSecAttrDescription
        kSecAttrComment
        kSecAttrCreator
        kSecAttrType
        kSecAttrLabel
        kSecAttrIsInvisible
        kSecAttrIsNegative
        kSecAttrAccount
        kSecAttrService
        kSecAttrGeneric
        kSecAttrSynchronizable

    kSecClassInternetPassword item attributes:
        kSecAttrAccess (OS X only)
        kSecAttrAccessControl
        kSecAttrAccessGroup (iOS; also OS X if kSecAttrSynchronizable and/or kSecUseDataProtectionKeychain set)
        kSecAttrAccessible (iOS; also OS X if kSecAttrSynchronizable and/or kSecUseDataProtectionKeychain set)
        kSecAttrCreationDate
        kSecAttrModificationDate
        kSecAttrDescription
        kSecAttrComment
        kSecAttrCreator
        kSecAttrType
        kSecAttrLabel
        kSecAttrIsInvisible
        kSecAttrIsNegative
        kSecAttrAccount
        kSecAttrSecurityDomain
        kSecAttrServer
        kSecAttrProtocol
        kSecAttrAuthenticationType
        kSecAttrPort
        kSecAttrPath
        kSecAttrSynchronizable

    kSecClassCertificate item attributes:
        kSecAttrAccessible    (iOS only)
        kSecAttrAccessControl (iOS only)
        kSecAttrAccessGroup   (iOS only)
        kSecAttrCertificateType
        kSecAttrCertificateEncoding
        kSecAttrLabel
        kSecAttrSubject
        kSecAttrIssuer
        kSecAttrSerialNumber
        kSecAttrSubjectKeyID
        kSecAttrPublicKeyHash
        kSecAttrSynchronizable

    kSecClassKey item attributes:
        kSecAttrAccess (OS X only)
        kSecAttrAccessControl
        kSecAttrAccessGroup (iOS; also OS X if kSecAttrSynchronizable and/or kSecUseDataProtectionKeychain set)
        kSecAttrAccessible (iOS; also OS X if kSecAttrSynchronizable and/or kSecUseDataProtectionKeychain set)
        kSecAttrKeyClass
        kSecAttrLabel
        kSecAttrApplicationLabel
        kSecAttrIsPermanent
        kSecAttrApplicationTag
        kSecAttrKeyType
        kSecAttrPRF    (OS X only)
        kSecAttrSalt   (OS X only)
        kSecAttrRounds (OS X only)
        kSecAttrKeySizeInBits
        kSecAttrEffectiveKeySize
        kSecAttrCanEncrypt
        kSecAttrCanDecrypt
        kSecAttrCanDerive
        kSecAttrCanSign
        kSecAttrCanVerify
        kSecAttrCanWrap
        kSecAttrCanUnwrap
        kSecAttrSynchronizable

     Note that the attributes kSecAttrCan* describe attributes of the
     key itself at relatively high level. Some of these attributes are
     mathematical -- for example, a DSA key cannot encrypt. Others are
     key-level policy issues -- for example, it is good cryptographic
     hygiene to use an RSA key either for encryption or signing but not
     both. Compare these to the certificate-level policy values in
     SecPolicy.h.

    kSecClassIdentity item attributes:
        Since an identity is the combination of a private key and a
        certificate, this class shares attributes of both kSecClassKey and
        kSecClassCertificate.

     @constant kSecAttrAccessible Specifies a dictionary key whose value
     indicates when your application needs access to an item's data.  You
     should choose the most restrictive option that meets your application's
     needs to allow the system to protect that item in the best way possible.
     See the "kSecAttrAccessible Value Constants" section for a list of
     values which can be specified.
     IMPORTANT: This attribute is currently not supported for OS X keychain
     items, unless the kSecAttrSynchronizable attribute is also present. If
     both attributes are specified on either OS X or iOS, the value for the
     kSecAttrAccessible key may only be one whose name does not end with
     "ThisDeviceOnly", as those cannot sync to another device.

     @constant kSecAttrAccessControl Specifies a dictionary key whose value
     is SecAccessControl instance which contains access control conditions
     for item.
     IMPORTANT: This attribute is mutually exclusive with kSecAttrAccess
     attribute.

     @constant kSecAttrAccess Specifies a dictionary key whose value
     is a SecAccessRef describing the access control settings for this item.
     This key is available on OS X only.

     @constant kSecAttrAccessGroup Specifies a dictionary key whose value is
     a CFStringRef indicating which access group a item is in.  The access
     groups that a particular application has membership in are determined by
     two entitlements for that application.  The application-identifier
     entitlement contains the application's single access group, unless
     there is a keychain-access-groups entitlement present.  The latter
     has as its value a list of access groups; the first item in this list
     is the default access group. Unless a specific access group is provided
     as the value of kSecAttrAccessGroup when SecItemAdd is called, new items
     are created in the application's default access group.  Specifying this
     attribute in SecItemCopyMatching, SecItemUpdate, or SecItemDelete calls
     limits the search to the specified access group (of which the calling
     application must be a member to obtain matching results.)  To share
     keychain items between multiple applications, each application must have
     a common group listed in its keychain-access-groups entitlement, and each
     must specify this shared access group name as the value for the
     kSecAttrAccessGroup key in the dictionary passed to SecItem functions.

     @constant kSecAttrSynchronizable Specifies a dictionary key whose value is
     a CFBooleanRef indicating whether the item in question can be synchronized.
     To add a new item which can be synced to other devices, or to obtain
     synchronizable results from a query, supply this key with a value of
     kCFBooleanTrue. If the key is not supplied, or has a value of
     kCFBooleanFalse, then no synchronizable items will be added or returned.
     A predefined value, kSecAttrSynchronizableAny, may be provided instead of
     kCFBooleanTrue if both synchronizable and non-synchronizable results are
     desired.

     IMPORTANT: Specifying the kSecAttrSynchronizable key has several caveats:

         - Updating or deleting items using the kSecAttrSynchronizable key will
           affect all copies of the item, not just the one on your local device.
           Be sure that it makes sense to use the same password on all devices
           before deciding to make a password synchronizable.
         - Only password items can currently be synchronized. Keychain syncing
           is not supported for certificates or cryptographic keys.
         - Items stored or obtained using the kSecAttrSynchronizable key cannot
           specify SecAccessRef-based access control with kSecAttrAccess. If a
           password is intended to be shared between multiple applications, the
           kSecAttrAccessGroup key must be specified, and each application
           using this password must have a 'keychain-access-groups' entitlement
           with the specified access group value.
         - Items stored or obtained using the kSecAttrSynchronizable key may
           not also specify a kSecAttrAccessible value which is incompatible
           with syncing (namely, those whose names end with "ThisDeviceOnly".)
         - Items stored or obtained using the kSecAttrSynchronizable key cannot
           be specified by reference. You must pass kSecReturnAttributes and/or
           kSecReturnData to retrieve results; kSecReturnRef is currently not
           supported for synchronizable items.
         - Persistent references to synchronizable items should be avoided;
           while they may work locally, they cannot be moved between devices,
           and may not resolve if the item is modified on some other device.
         - When specifying a query that uses the kSecAttrSynchronizable key,
           search keys are limited to the item's class and attributes.
           The only search constant which may be used is kSecMatchLimit; other
           constants using the kSecMatch prefix are not supported at this time.

    @constant kSecAttrSynchronizableAny Specifies that both synchronizable and
        non-synchronizable results should be returned from this query. This may be
        used as a value for the kSecAttrSynchronizable dictionary key in a call to
        SecItemCopyMatching, SecItemUpdate, or SecItemDelete.

    @constant kSecAttrCreationDate (read-only) Specifies a dictionary key whose
        value is the item's creation date. You use this key to get a value
        of type CFDateRef that represents the date the item was created.
    @constant kSecAttrModificationDate (read-only) Specifies a dictionary key
        whose value is the item's modification date. You use this key to get
        a value of type CFDateRef that represents the last time the item was
        updated.
    @constant kSecAttrDescription Specifies a dictionary key whose value is
        the item's description attribute. You use this key to set or get a
        value of type CFStringRef that represents a user-visible string
        describing this particular kind of item (e.g., "disk image password").
    @constant kSecAttrComment Specifies a dictionary key whose value is the
        item's comment attribute. You use this key to set or get a value of
        type CFStringRef containing the user-editable comment for this item.
    @constant kSecAttrCreator Specifies a dictionary key whose value is the
        item's creator attribute. You use this key to set or get a value of
        type CFNumberRef that represents the item's creator. This number is
        the unsigned integer representation of a four-character code (e.g.,
        'aCrt').
    @constant kSecAttrType Specifies a dictionary key whose value is the item's
        type attribute. You use this key to set or get a value of type
        CFNumberRef that represents the item's type. This number is the
        unsigned integer representation of a four-character code (e.g.,
        'aTyp').
    @constant kSecAttrLabel Specifies a dictionary key whose value is the
        item's label attribute. You use this key to set or get a value of
        type CFStringRef containing the user-visible label for this item.
    @constant kSecAttrIsInvisible Specifies a dictionary key whose value is the
        item's invisible attribute. You use this key to set or get a value
        of type CFBooleanRef that indicates whether the item is invisible
        (i.e., should not be displayed.)
    @constant kSecAttrIsNegative Specifies a dictionary key whose value is the
        item's negative attribute. You use this key to set or get a value of
        type CFBooleanRef that indicates whether there is a valid password
        associated with this keychain item. This is useful if your application
        doesn't want a password for some particular service to be stored in
        the keychain, but prefers that it always be entered by the user.
    @constant kSecAttrAccount Specifies a dictionary key whose value is the
        item's account attribute. You use this key to set or get a CFStringRef
        that contains an account name. (Items of class
        kSecClassGenericPassword, kSecClassInternetPassword have this
        attribute.)
    @constant kSecAttrService Specifies a dictionary key whose value is the
        item's service attribute. You use this key to set or get a CFStringRef
        that represents the service associated with this item. (Items of class
        kSecClassGenericPassword have this attribute.)
    @constant kSecAttrGeneric Specifies a dictionary key whose value is the
        item's generic attribute. You use this key to set or get a value of
        CFDataRef that contains a user-defined attribute. (Items of class
        kSecClassGenericPassword have this attribute.)
    @constant kSecAttrSecurityDomain Specifies a dictionary key whose value
        is the item's security domain attribute. You use this key to set or
        get a CFStringRef value that represents the Internet security domain.
        (Items of class kSecClassInternetPassword have this attribute.)
    @constant kSecAttrServer Specifies a dictionary key whose value is the
        item's server attribute. You use this key to set or get a value of
        type CFStringRef that contains the server's domain name or IP address.
        (Items of class kSecClassInternetPassword have this attribute.)
    @constant kSecAttrProtocol Specifies a dictionary key whose value is the
        item's protocol attribute. You use this key to set or get a value of
        type CFNumberRef that denotes the protocol for this item (see the
        SecProtocolType enum in SecKeychainItem.h). (Items of class
        kSecClassInternetPassword have this attribute.)
    @constant kSecAttrAuthenticationType Specifies a dictionary key whose value
        is the item's authentication type attribute. You use this key to set
        or get a value of type CFNumberRef that denotes the authentication
        scheme for this item (see the kSecAttrAuthenticationType value
        constants below).
    @constant kSecAttrPort Specifies a dictionary key whose value is the item's
        port attribute. You use this key to set or get a CFNumberRef value
        that represents an Internet port number. (Items of class
        kSecClassInternetPassword have this attribute.)
    @constant kSecAttrPath Specifies a dictionary key whose value is the item's
        path attribute, typically this is the path component of the URL.  You use
        this key to set or get a CFStringRef value that represents a path. (Items
        of class kSecClassInternetPassword have this attribute.)
    @constant kSecAttrSubject (read-only) Specifies a dictionary key whose
        value is the item's subject. You use this key to get a value of type
        CFDataRef that contains the X.500 subject name of a certificate.
        (Items of class kSecClassCertificate have this attribute.)
    @constant kSecAttrIssuer (read-only) Specifies a dictionary key whose value
        is the item's issuer. You use this key to get a value of type
        CFDataRef that contains the X.500 issuer name of a certificate. (Items
        of class kSecClassCertificate have this attribute.)
    @constant kSecAttrSerialNumber (read-only) Specifies a dictionary key whose
        value is the item's serial number.  You use this key to get a value
        of type CFDataRef that contains the serial number data of a
        certificate. (Items of class kSecClassCertificate have this
        attribute.)
    @constant kSecAttrSubjectKeyID (read-only) Specifies a dictionary key whose
        value is the item's subject key ID. You use this key to get a value
        of type CFDataRef that contains the subject key ID of a certificate.
        (Items of class kSecClassCertificate have this attribute.)
    @constant kSecAttrPublicKeyHash (read-only) Specifies a dictionary key
        whose value is the item's public key hash. You use this key to get a
        value of type CFDataRef that contains the hash of a certificate's
        public key. (Items of class kSecClassCertificate have this attribute.)
    @constant kSecAttrCertificateType (read-only) Specifies a dictionary key
        whose value is the item's certificate type. You use this key to get
        a value of type CFNumberRef that denotes the certificate type
        (On iOS, currently the value of this attribute must be equal to the
        version of the X509 certificate.  So, 1 for v1, 2 for v2, and 3 for v3
        certificates). (On OSX, see the CSSM_CERT_TYPE enum in cssmtype.h).
        Only items of class kSecClassCertificate have this attribute.
    @constant kSecAttrCertificateEncoding (read-only) Specifies a dictionary
        key whose value is the item's certificate encoding. You use this key
        to get a value of type CFNumberRef that denotes the certificate
        encoding (On iOS, currently only the value 3 meaning
        kSecAttrCertificateEncodingDER is supported). On OSX, see the
        CSSM_CERT_ENCODING enum in cssmtype.h. Only items of class
        kSecClassCertificate have this attribute.
    @constant kSecAttrKeyClass (read only) Specifies a dictionary key whose
        value is one of kSecAttrKeyClassPublic, kSecAttrKeyClassPrivate or
        kSecAttrKeyClassSymmetric.
    @constant kSecAttrApplicationLabel Specifies a dictionary key whose value
        is the key's application label attribute. This is different from the
        kSecAttrLabel (which is intended to be human-readable). This attribute
        is used to look up a key programmatically; in particular, for keys of
        class kSecAttrKeyClassPublic and kSecAttrKeyClassPrivate, the value of
        this attribute is the hash of the public key. This item is a type of CFDataRef.
        Legacy keys may contain a UUID in this field as a CFStringRef.
    @constant kSecAttrIsPermanent Specifies a dictionary key whose value is a
        CFBooleanRef indicating whether the key in question will be stored
        permanently.
     @constant kSecAttrIsSensitive Specifies a dictionary key whose value is a
        CFBooleanRef indicating that the key in question can only be exported
        in a wrapped (encrypted) format. OS X only.
     @constant kSecAttrIsExtractable Specifies a dictionary key whose value is a
        CFBooleanRef indicating whether the key in question can be exported from
        its keychain container. OS X only.
    @constant kSecAttrApplicationTag Specifies a dictionary key whose value is a
        CFDataRef containing private tag data.
    @constant kSecAttrKeyType Specifies a dictionary key whose value is a
        CFNumberRef indicating the algorithm associated with this key
        (On iOS, currently only the value 42 is supported, alternatively you can use
        kSecAttrKeyTypeRSA). (On OSX, see the CSSM_ALGORITHMS enum in cssmtype.h).

    @constant kSecAttrPRF Specifies a dictionary key whose value is the PRF
        (pseudo-random function) for this key (see "kSecAttrPRF Value Constants".)
        OS X only.
    @constant kSecAttrSalt Specifies a dictionary key whose value is a
        CFData containing the salt to use for this key. OS X only.
    @constant kSecAttrRounds Specifies a dictionary key whose value is the
        number of rounds for the pseudo-random function specified by kSecAttrPRF.
        OS X only.
    @constant kSecAttrKeySizeInBits Specifies a dictionary key whose value
        is a CFNumberRef indicating the number of bits in this key.
    @constant kSecAttrEffectiveKeySize Specifies a dictionary key whose value
        is a CFNumberRef indicating the effective number of bits in this key.
        For example, a DES key has a kSecAttrKeySizeInBits of 64, but a
        kSecAttrEffectiveKeySize of 56 bits.
    @constant kSecAttrCanEncrypt Specifies a dictionary key whole value is a
        CFBooleanRef indicating whether the key in question can be used to
        encrypt data.
    @constant kSecAttrCanDecrypt Specifies a dictionary key whose value is a
        CFBooleanRef indicating whether the key in question can be used to
        decrypt data.
    @constant kSecAttrCanDerive Specifies a dictionary key whole value is a
        CFBooleanRef indicating whether the key in question can be used to
        derive another key.
    @constant kSecAttrCanSign Specifies a dictionary key whole value is a
        CFBooleanRef indicating whether the key in question can be used to
        create a digital signature.
    @constant kSecAttrCanVerify Specifies a dictionary key whole value is a
        CFBooleanRef indicating whether the key in question can be used to
        verify a digital signature.
    @constant kSecAttrCanWrap Specifies a dictionary key whole value is a
        CFBooleanRef indicating whether the key in question can be used to
        wrap another key.
    @constant kSecAttrCanUnwrap Specifies a dictionary key whole value is a
        CFBooleanRef indicating whether the key in question can be used to
        unwrap another key.
    @constant kSecAttrSyncViewHint Specifies a dictionary key whose value is
        a CFStringRef. This value is part of the primary key of each item, and
        can be used to help distiguish Sync Views when defining their
        queries. iOS and sychronizable items only.
    @constant kSecAttrTokenID Specifies a dictionary key whose presence
        indicates that item is backed by external token. Value of this attribute
        is CFStringRef uniquely identifying containing token. When this attribute
        is not present, item is stored in internal keychain database.
        Note that once item is created, this attribute cannot be changed - in other
        words it is not possible to migrate existing items to, from or between tokens.
        Currently the only available value for this attribute is
        kSecAttrTokenIDSecureEnclave, which indicates that item (private key) is
        backed by device's Secure Enclave.
 */
extern const CFStringRef kSecAttrAccessible
    API_AVAILABLE(macos(10.9), ios(4.0));
extern const CFStringRef kSecAttrAccess
    API_AVAILABLE(macos(10.7), ios(NA));
extern const CFStringRef kSecAttrAccessControl
    API_AVAILABLE(macos(10.10), ios(8.0));
extern const CFStringRef kSecAttrAccessGroup
    API_AVAILABLE(macos(10.9), ios(3.0));
extern const CFStringRef kSecAttrSynchronizable
    API_AVAILABLE(macos(10.9), ios(7.0));
extern const CFStringRef kSecAttrSynchronizableAny
    API_AVAILABLE(macos(10.9), ios(7.0));
extern const CFStringRef kSecAttrCreationDate
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrModificationDate
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrDescription
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrComment
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrCreator
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrType
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrLabel
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrIsInvisible
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrIsNegative
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrAccount
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrService
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrGeneric
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrSecurityDomain
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrServer
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocol
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrAuthenticationType
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrPort
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrPath
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrSubject
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrIssuer
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrSerialNumber
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrSubjectKeyID
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrPublicKeyHash
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrCertificateType
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrCertificateEncoding
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrKeyClass
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrApplicationLabel
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrIsPermanent
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrIsSensitive
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrIsExtractable
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrApplicationTag
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrKeyType
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrPRF
    API_AVAILABLE(macos(10.7), ios(NA));
extern const CFStringRef kSecAttrSalt
    API_AVAILABLE(macos(10.7), ios(NA));
extern const CFStringRef kSecAttrRounds
    API_AVAILABLE(macos(10.7), ios(NA));
extern const CFStringRef kSecAttrKeySizeInBits
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrEffectiveKeySize
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrCanEncrypt
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrCanDecrypt
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrCanDerive
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrCanSign
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrCanVerify
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrCanWrap
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrCanUnwrap
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrSyncViewHint
    API_AVAILABLE(macos(10.11), ios(9.0));
extern const CFStringRef kSecAttrTokenID
    API_AVAILABLE(macos(10.12), ios(9.0));
extern const CFStringRef kSecAttrPersistantReference
    API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));
extern const CFStringRef kSecAttrPersistentReference
    API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
    @enum kSecAttrAccessible Value Constants
    @discussion Predefined item attribute constants used to get or set values
        in a dictionary. The kSecAttrAccessible constant is the key and its
        value is one of the constants defined here.
        When asking SecItemCopyMatching to return the item's data, the error
        errSecInteractionNotAllowed will be returned if the item's data is not
        available until a device unlock occurs.
    @constant kSecAttrAccessibleWhenUnlocked Item data can only be accessed
        while the device is unlocked. This is recommended for items that only
        need be accesible while the application is in the foreground.  Items
        with this attribute will migrate to a new device when using encrypted
        backups.
    @constant kSecAttrAccessibleAfterFirstUnlock Item data can only be
        accessed once the device has been unlocked after a restart.  This is
        recommended for items that need to be accesible by background
        applications. Items with this attribute will migrate to a new device
        when using encrypted backups.
    @constant kSecAttrAccessibleAlways Item data can always be accessed
        regardless of the lock state of the device.  This is not recommended
        for anything except system use. Items with this attribute will migrate
        to a new device when using encrypted backups.
    @constant kSecAttrAccessibleWhenPasscodeSetThisDeviceOnly Item data can
        only be accessed while the device is unlocked. This is recommended for
        items that only need to be accessible while the application is in the
        foreground and requires a passcode to be set on the device. Items with
        this attribute will never migrate to a new device, so after a backup
        is restored to a new device, these items will be missing. This
        attribute will not be available on devices without a passcode. Disabling
        the device passcode will cause all previously protected items to
        be deleted.
    @constant kSecAttrAccessibleWhenUnlockedThisDeviceOnly Item data can only
        be accessed while the device is unlocked. This is recommended for items
        that only need be accesible while the application is in the foreground.
        Items with this attribute will never migrate to a new device, so after
        a backup is restored to a new device, these items will be missing.
    @constant kSecAttrAccessibleAfterFirstUnlockThisDeviceOnly Item data can
        only be accessed once the device has been unlocked after a restart.
        This is recommended for items that need to be accessible by background
        applications. Items with this attribute will never migrate to a new
        device, so after a backup is restored to a new device these items will
        be missing.
    @constant kSecAttrAccessibleAlwaysThisDeviceOnly Item data can always
        be accessed regardless of the lock state of the device.  This option
        is not recommended for anything except system use. Items with this
        attribute will never migrate to a new device, so after a backup is
        restored to a new device, these items will be missing.
*/
extern const CFStringRef kSecAttrAccessibleWhenUnlocked
    API_AVAILABLE(macos(10.9), ios(4.0));
extern const CFStringRef kSecAttrAccessibleAfterFirstUnlock
    API_AVAILABLE(macos(10.9), ios(4.0));
extern const CFStringRef kSecAttrAccessibleAlways
    API_DEPRECATED("Use an accessibility level that provides some user protection, such as kSecAttrAccessibleAfterFirstUnlock", macos(10.9, 10.14), ios(4.0, 12.0));
extern const CFStringRef kSecAttrAccessibleWhenPasscodeSetThisDeviceOnly
    API_AVAILABLE(macos(10.10), ios(8.0));
extern const CFStringRef kSecAttrAccessibleWhenUnlockedThisDeviceOnly
    API_AVAILABLE(macos(10.9), ios(4.0));
extern const CFStringRef kSecAttrAccessibleAfterFirstUnlockThisDeviceOnly
    API_AVAILABLE(macos(10.9), ios(4.0));
extern const CFStringRef kSecAttrAccessibleAlwaysThisDeviceOnly
    API_DEPRECATED("Use an accessibility level that provides some user protection, such as kSecAttrAccessibleAfterFirstUnlockThisDeviceOnly", macos(10.9, 10.14), ios(4.0, 12.0));

/*!
    @enum kSecAttrProtocol Value Constants
    @discussion Predefined item attribute constants used to get or set values
        in a dictionary. The kSecAttrProtocol constant is the key and its
        value is one of the constants defined here.
    @constant kSecAttrProtocolFTP.
    @constant kSecAttrProtocolFTPAccount.
    @constant kSecAttrProtocolHTTP.
    @constant kSecAttrProtocolIRC.
    @constant kSecAttrProtocolNNTP.
    @constant kSecAttrProtocolPOP3.
    @constant kSecAttrProtocolSMTP.
    @constant kSecAttrProtocolSOCKS.
    @constant kSecAttrProtocolIMAP.
    @constant kSecAttrProtocolLDAP.
    @constant kSecAttrProtocolAppleTalk.
    @constant kSecAttrProtocolAFP.
    @constant kSecAttrProtocolTelnet.
    @constant kSecAttrProtocolSSH.
    @constant kSecAttrProtocolFTPS.
    @constant kSecAttrProtocolHTTPS.
    @constant kSecAttrProtocolHTTPProxy.
    @constant kSecAttrProtocolHTTPSProxy.
    @constant kSecAttrProtocolFTPProxy.
    @constant kSecAttrProtocolSMB.
    @constant kSecAttrProtocolRTSP.
    @constant kSecAttrProtocolRTSPProxy.
    @constant kSecAttrProtocolDAAP.
    @constant kSecAttrProtocolEPPC.
    @constant kSecAttrProtocolIPP.
    @constant kSecAttrProtocolNNTPS.
    @constant kSecAttrProtocolLDAPS.
    @constant kSecAttrProtocolTelnetS.
    @constant kSecAttrProtocolIMAPS.
    @constant kSecAttrProtocolIRCS.
    @constant kSecAttrProtocolPOP3S.
*/
extern const CFStringRef kSecAttrProtocolFTP
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolFTPAccount
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolHTTP
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolIRC
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolNNTP
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolPOP3
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolSMTP
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolSOCKS
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolIMAP
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolLDAP
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolAppleTalk
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolAFP
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolTelnet
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolSSH
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolFTPS
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolHTTPS
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolHTTPProxy
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolHTTPSProxy
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolFTPProxy
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolSMB
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolRTSP
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolRTSPProxy
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolDAAP
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolEPPC
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolIPP
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolNNTPS
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolLDAPS
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolTelnetS
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolIMAPS
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolIRCS
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrProtocolPOP3S
    API_AVAILABLE(macos(10.6), ios(2.0));

/*!
    @enum kSecAttrAuthenticationType Value Constants
    @discussion Predefined item attribute constants used to get or set values
         in a dictionary. The kSecAttrAuthenticationType constant is the key
         and its value is one of the constants defined here.
    @constant kSecAttrAuthenticationTypeNTLM.
    @constant kSecAttrAuthenticationTypeMSN.
    @constant kSecAttrAuthenticationTypeDPA.
    @constant kSecAttrAuthenticationTypeRPA.
    @constant kSecAttrAuthenticationTypeHTTPBasic.
    @constant kSecAttrAuthenticationTypeHTTPDigest.
    @constant kSecAttrAuthenticationTypeHTMLForm.
    @constant kSecAttrAuthenticationTypeDefault.
*/
extern const CFStringRef kSecAttrAuthenticationTypeNTLM
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrAuthenticationTypeMSN
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrAuthenticationTypeDPA
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrAuthenticationTypeRPA
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrAuthenticationTypeHTTPBasic
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrAuthenticationTypeHTTPDigest
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrAuthenticationTypeHTMLForm
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecAttrAuthenticationTypeDefault
    API_AVAILABLE(macos(10.6), ios(2.0));

/*!
    @enum kSecAttrKeyClass Value Constants
    @discussion Predefined item attribute constants used to get or set values
        in a dictionary. The kSecAttrKeyClass constant is the key
        and its value is one of the constants defined here.
    @constant kSecAttrKeyClassPublic.
    @constant kSecAttrKeyClassPrivate.
    @constant kSecAttrKeyClassSymmetric.
*/
extern const CFStringRef kSecAttrKeyClassPublic
    API_AVAILABLE(macos(10.7), ios(2.0));
extern const CFStringRef kSecAttrKeyClassPrivate
    API_AVAILABLE(macos(10.7), ios(2.0));
extern const CFStringRef kSecAttrKeyClassSymmetric
    API_AVAILABLE(macos(10.7), ios(2.0));

/*!
    @enum kSecAttrKeyType Value Constants
    @discussion Predefined item attribute constants used to get or set values
        in a dictionary. The kSecAttrKeyType constant is the key
        and its value is one of the constants defined here.
    @constant kSecAttrKeyTypeECSECPrimeRandom. The used curve is P-192, P-256, P-384 or P-521.
        The size is specified by kSecAttrKeySizeInBits attribute. Curves are defined in FIPS PUB 186-4 standard.
    @constant kSecAttrKeyTypeEC This is the legacy name for kSecAttrKeyTypeECSECPrimeRandom, new applications should not use it.
    @constant kSecAttrKeyTypeDSA (OSX only)
    @constant kSecAttrKeyTypeAES (OSX only)
    @constant kSecAttrKeyType3DES (OSX only)
    @constant kSecAttrKeyTypeRC4 (OSX only)
    @constant kSecAttrKeyTypeRC2 (OSX only)
    @constant kSecAttrKeyTypeCAST (OSX only)
    @constant kSecAttrKeyTypeECDSA (deprecated; use kSecAttrKeyTypeECSECPrimeRandom instead.) (OSX only)
*/
extern const CFStringRef kSecAttrKeyTypeRSA
    API_AVAILABLE(macos(10.7), ios(2.0));
extern const CFStringRef kSecAttrKeyTypeDSA
    API_AVAILABLE(macos(10.7), ios(NA));
extern const CFStringRef kSecAttrKeyTypeAES
    API_AVAILABLE(macos(10.7), ios(NA));
extern const CFStringRef kSecAttrKeyTypeDES
    API_AVAILABLE(macos(10.7), ios(NA));
extern const CFStringRef kSecAttrKeyType3DES
    API_AVAILABLE(macos(10.7), ios(NA));
extern const CFStringRef kSecAttrKeyTypeRC4
    API_AVAILABLE(macos(10.7), ios(NA));
extern const CFStringRef kSecAttrKeyTypeRC2
    API_AVAILABLE(macos(10.7), ios(NA));
extern const CFStringRef kSecAttrKeyTypeCAST
    API_AVAILABLE(macos(10.7), ios(NA));
extern const CFStringRef kSecAttrKeyTypeECDSA
    API_AVAILABLE(macos(10.7), ios(NA));
extern const CFStringRef kSecAttrKeyTypeEC
    API_AVAILABLE(macos(10.9), ios(4.0));
extern const CFStringRef kSecAttrKeyTypeECSECPrimeRandom
    API_AVAILABLE(macos(10.12), ios(10.0));

/*
     @enum kSecAttrPRF Value Constants
     @discussion Predefined item attribute constants used to specify the PRF
     to use with SecKeyDeriveFromPassword. OS X only.
     @constant kSecAttrPRFHmacAlgSHA1
     @constant kSecAttrPRFHmacAlgSHA224
     @constant kSecAttrPRFHmacAlgSHA256
     @constant kSecAttrPRFHmacAlgSHA384
     @constant kSecAttrPRFHmacAlgSHA512
*/
extern const CFStringRef kSecAttrPRFHmacAlgSHA1
    API_AVAILABLE(macos(10.7), ios(NA));
extern const CFStringRef kSecAttrPRFHmacAlgSHA224
    API_AVAILABLE(macos(10.7), ios(NA));
extern const CFStringRef kSecAttrPRFHmacAlgSHA256
    API_AVAILABLE(macos(10.7), ios(NA));
extern const CFStringRef kSecAttrPRFHmacAlgSHA384
    API_AVAILABLE(macos(10.7), ios(NA));
extern const CFStringRef kSecAttrPRFHmacAlgSHA512
      API_AVAILABLE(macos(10.7), ios(NA));


/*!
    @enum Search Constants
    @discussion Predefined search constants used to set values in a query
        dictionary. You can specify a combination of search attributes and
        item attributes when looking for matching items with the
        SecItemCopyMatching function.
    @constant kSecMatchPolicy Specifies a dictionary key whose value is a
        SecPolicyRef. If provided, returned certificates or identities must
        verify with this policy.
    @constant kSecMatchItemList OS X only. Specifies a dictionary key whose value is a
         CFArray of SecKeychainItemRef items. If provided, returned items will be
         limited to the subset which are contained in this list.
         @constant kSecMatchSearchList Specifies a dictionary key whose value is a
         CFArray of SecKeychainRef items. If provided, the search will be limited
         to the keychains contained in this list.
    @constant kSecMatchIssuers Specifies a dictionary key whose value is a
        CFArray of X.500 names (of type CFDataRef). If provided, returned
        certificates or identities will be limited to those whose
        certificate chain contains one of the issuers provided in this list.
    @constant kSecMatchEmailAddressIfPresent Specifies a dictionary key whose
        value is a CFStringRef containing an RFC822 email address. If
        provided, returned certificates or identities will be limited to those
        that contain the address, or do not contain any email address.
    @constant kSecMatchSubjectContains Specifies a dictionary key whose value
        is a CFStringRef. If provided, returned certificates or identities
        will be limited to those containing this string in the subject.
    @constant kSecMatchSubjectStartsWith OS X only. Specifies a dictionary key whose value
        is a CFStringRef. If provided, returned certificates or identities
        will be limited to those with subject names that start with this string.
    @constant kSecMatchSubjectEndsWith OS X only. Specifies a dictionary key whose value
         is a CFStringRef. If provided, returned certificates or identities
         will be limited to those with subject names that end with this string.
    @constant kSecMatchSubjectWholeString OS X only. Specifies a dictionary key whose
         value is a CFStringRef. If provided, returned certificates or identities
         will be limited to those matching this string exactly in the subject.
    @constant kSecMatchCaseInsensitive Specifies a dictionary key whose value
        is a CFBooleanRef. If this value is kCFBooleanFalse, or is not
        provided, then case-sensitive string matching is performed.
    @constant kSecMatchDiacriticInsensitive OS X only. Specifies a dictionary key whose
        value is a CFBooleanRef. If this value is kCFBooleanFalse, or is not
        provided, then diacritic-sensitive string matching is performed.
    @constant kSecMatchWidthInsensitive OS X only. Specifies a dictionary key whose
        value is a CFBooleanRef. If this value is kCFBooleanFalse, or is not
        provided, then string matching is width-sensitive (e.g. 'a' != 0xFF41).
    @constant kSecMatchTrustedOnly Specifies a dictionary key whose value is
        a CFBooleanRef. If provided with a value of kCFBooleanTrue, only
        certificates which can be verified back to a trusted anchor will be
        returned. If this value is kCFBooleanFalse, or is not provided, then
        both trusted and untrusted certificates may be returned.
    @constant kSecMatchValidOnDate Specifies a dictionary key whose value is
        of type CFDateRef. If provided, returned keys, certificates or
        identities will be limited to those which are valid for the given date.
        Pass a value of kCFNull to indicate the current date.
    @constant kSecMatchLimit Specifies a dictionary key whose value is a
        CFNumberRef. If provided, this value specifies the maximum number of
        results to return. If not provided, results are limited to the first
        item found. Predefined values are provided for a single item
        (kSecMatchLimitOne) and all matching items (kSecMatchLimitAll).
    @constant kSecMatchLimitOne Specifies that results are limited to the first
        item found; used as a value for the kSecMatchLimit dictionary key.
    @constant kSecMatchLimitAll Specifies that an unlimited number of results
        may be returned; used as a value for the kSecMatchLimit dictionary
        key.
*/
extern const CFStringRef kSecMatchPolicy
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecMatchItemList
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecMatchSearchList
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecMatchIssuers
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecMatchEmailAddressIfPresent
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecMatchSubjectContains
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecMatchSubjectStartsWith
    API_AVAILABLE(macos(10.7), ios(NA));
extern const CFStringRef kSecMatchSubjectEndsWith
    API_AVAILABLE(macos(10.7), ios(NA));
extern const CFStringRef kSecMatchSubjectWholeString
    API_AVAILABLE(macos(10.7), ios(NA));
extern const CFStringRef kSecMatchCaseInsensitive
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecMatchDiacriticInsensitive
    API_AVAILABLE(macos(10.7), ios(NA));
extern const CFStringRef kSecMatchWidthInsensitive
    API_AVAILABLE(macos(10.7), ios(NA));
extern const CFStringRef kSecMatchTrustedOnly
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecMatchValidOnDate
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecMatchLimit
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecMatchLimitOne
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecMatchLimitAll
    API_AVAILABLE(macos(10.6), ios(2.0));


/*!
    @enum Return Type Key Constants
    @discussion Predefined return type keys used to set values in a dictionary.
        You use these keys to specify the type of results which should be
        returned by the SecItemCopyMatching or SecItemAdd function. You can
        specify zero or more of these return types. If more than one of these
        result types is specified, the result is returned as a CFDictionaryRef
        whose keys are the result types and values are the requested data.
    @constant kSecReturnData Specifies a dictionary key whose value is of type
        CFBooleanRef. A value of kCFBooleanTrue indicates that the data of
        an item (CFDataRef) should be returned. For keys and password
        items, data is secret (encrypted) and may require the user to enter
        a password for access.
    @constant kSecReturnAttributes Specifies a dictionary key whose value is
        of type CFBooleanRef. A value of kCFBooleanTrue indicates that the
        (non-encrypted) attributes of an item (CFDictionaryRef) should be
        returned.
    @constant kSecReturnRef Specifies a dictionary key whose value is a
        CFBooleanRef. A value of kCFBooleanTrue indicates that a reference
        should be returned. Depending on the item class requested, the
        returned reference(s) may be of type SecKeychainItemRef, SecKeyRef,
        SecCertificateRef, or SecIdentityRef.
    @constant kSecReturnPersistentRef Specifies a dictionary key whose value
        is of type CFBooleanRef. A value of kCFBooleanTrue indicates that a
        persistent reference to an item (CFDataRef) should be returned.
*/
extern const CFStringRef kSecReturnData
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecReturnAttributes
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecReturnRef
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecReturnPersistentRef
    API_AVAILABLE(macos(10.6), ios(2.0));


/*!
    @enum Value Type Key Constants
    @discussion Predefined value type keys used to pass values in a dictionary.
        You can specify zero or more of these types depending on the function
        you are calling.  For SecItemCopyMatching or SecItemAdd these are
        used as keys in the results dictionary.
    @constant kSecValueData Specifies a dictionary key whose value is of type
        CFDataRef.  For keys and password items, data is secret (encrypted)
        and may require the user to enter a password for access.
    @constant kSecValueRef Specifies a dictionary key whose value, depending
        on the item class requested, is of type SecKeychainItemRef, SecKeyRef,
        SecCertificateRef, or SecIdentityRef.
    @constant kSecValuePersistentRef Specifies a dictionary key whose value
        is of type CFDataRef.  The bytes in this CFDataRef can be stored by
        the caller and used on a subsequent invocation of the application (or
        even a different application) to retrieve the item referenced by it.
*/
extern const CFStringRef kSecValueData
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecValueRef
    API_AVAILABLE(macos(10.6), ios(2.0));
extern const CFStringRef kSecValuePersistentRef
    API_AVAILABLE(macos(10.6), ios(2.0));


/*!
    @enum Other Constants
    @discussion Predefined constants used to set values in a dictionary.
    @constant kSecUseItemList Specifies a dictionary key whose value is a
        CFArray of items. If provided, this array is treated as the set of
        all possible items to search, or add if the API being called is
        SecItemAdd. The items in this array may be of type SecKeyRef,
        SecCertificateRef, SecIdentityRef, or CFDataRef (for a persistent
        item reference.) The items in the array must all be of the same
        type. When this attribute is provided, no keychains are searched.
    @constant kSecUseKeychain OS X only. Specifies a dictionary key whose value is a
        keychain reference. You use this key to specify a value of type
        SecKeychainRef to which SecItemAdd will add the provided item(s).
    @constant kSecUseOperationPrompt Specifies a dictionary key whose value
        is a CFStringRef that represents a user-visible string describing
        the operation for which the application is attempting to authenticate.
        The application is responsible for the text localization.
    @constant kSecUseNoAuthenticationUI OS X only. Specifies a dictionary key whose value
        is a CFBooleanRef. If provided with a value of kCFBooleanTrue, the error
        errSecInteractionNotAllowed will be returned if the item is attempting
        to authenticate with UI.
    @constant kSecUseAuthenticationUI Specifies a dictionary key whose value
        is one of kSecUseAuthenticationUIAllow, kSecUseAuthenticationUIFail, kSecUseAuthenticationUISkip.
    @constant kSecUseAuthenticationContext Specifies a dictionary key whose value
        is LAContext to be used for keychain item authentication.
        * If the item requires authentication and this key is omitted, a new context
          will be created just for the purpose of the single call.
        * If the specified context has been previously authenticated, the operation
          will succeed without asking user for authentication.
        * If the specified context has not been previously authenticated, the new
          authentication will be started on this context, allowing caller to
          eventually reuse the successfully authenticated context in subsequent
          keychain operations.
    @constant kSecUseDataProtectionKeychain Specifies a dictionary key whose value
        is a CFBooleanRef. Set to kCFBooleanTrue to use kSecAttrAccessGroup and/or
        kSecAttrAccessible on macOS without requiring the item to be marked synchronizable.
*/
extern const CFStringRef kSecUseItemList
    API_AVAILABLE(macos(10.6))
    API_DEPRECATED("Not implemented on this platform", ios(2.0, 12.0), tvos(9.0, 12.0), watchos(1.0, 5.0), macCatalyst(13.0, 13.0))
    ;
extern const CFStringRef kSecUseKeychain
    API_AVAILABLE(macos(10.7), ios(NA));
extern const CFStringRef kSecUseOperationPrompt
    API_DEPRECATED("Use kSecUseAuthenticationContext and set LAContext.localizedReason property", macos(10.10, 11.0), ios(8.0, 14.0));
extern const CFStringRef kSecUseNoAuthenticationUI
    API_DEPRECATED("Use kSecUseAuthenticationUI instead.", macos(10.10, 10.11), ios(8.0, 9.0));
extern const CFStringRef kSecUseAuthenticationUI
    API_AVAILABLE(macos(10.11), ios(9.0));
extern const CFStringRef kSecUseAuthenticationContext
    API_AVAILABLE(macos(10.11), ios(9.0));
extern const CFStringRef kSecUseDataProtectionKeychain
    API_AVAILABLE(macos(10.15), ios(13.0));

/*!
    @enum kSecUseAuthenticationUI Value Constants
    @discussion Predefined item attribute constants used to get or set values
        in a dictionary. The kSecUseAuthenticationUI constant is the key and its
        value is one of the constants defined here.
        If the key kSecUseAuthenticationUI not provided then kSecUseAuthenticationUIAllow
        is used as default.
    @constant kSecUseAuthenticationUIAllow Specifies that authenticate UI can appear.
    @constant kSecUseAuthenticationUIFail Specifies that the error
        errSecInteractionNotAllowed will be returned if an item needs
        to authenticate with UI
    @constant kSecUseAuthenticationUIAllowSkip Specifies that all items which need
        to authenticate with UI will be silently skipped. This value can be used
        only with SecItemCopyMatching.
*/
extern const CFStringRef kSecUseAuthenticationUIAllow
    API_DEPRECATED("Instead of kSecUseAuthenticationUI, use kSecUseAuthenticationContext and set LAContext.interactionNotAllowed property", macos(10.11, 11.0), ios(9.0, 14.0));
extern const CFStringRef kSecUseAuthenticationUIFail
    API_DEPRECATED("Instead of kSecUseAuthenticationUI, use kSecUseAuthenticationContext and set LAContext.interactionNotAllowed property", macos(10.11, 11.0), ios(9.0, 14.0));
extern const CFStringRef kSecUseAuthenticationUISkip
    API_AVAILABLE(macos(10.11), ios(9.0));

/*!
     @enum kSecAttrTokenID Value Constants
     @discussion Predefined item attribute constant used to get or set values
         in a dictionary. The kSecAttrTokenID constant is the key and its value
         can be kSecAttrTokenIDSecureEnclave.
     @constant kSecAttrTokenIDSecureEnclave Specifies well-known identifier of the
         token implemented using device's Secure Enclave. The only keychain items
         supported by the Secure Enclave token are 256-bit elliptic curve keys
         (kSecAttrKeyTypeECSecPrimeRandom). Keys must be generated on the secure enclave using
         SecKeyGenerateKeyPair call with kSecAttrTokenID set to
         kSecAttrTokenIDSecureEnclave in the parameters dictionary, it is not
         possible to import pregenerated keys to kSecAttrTokenIDSecureEnclave token.
*/
extern const CFStringRef kSecAttrTokenIDSecureEnclave
    API_AVAILABLE(macos(10.12), ios(9.0));

/*!
     @enum kSecAttrAccessGroup Value Constants
     @constant kSecAttrAccessGroupToken Represents well-known access group
         which contains items provided by external token (typically smart card).
         This may be used as a value for kSecAttrAccessGroup attribute. Every
         application has access to this access group so it is not needed to
         explicitly list it in keychain-access-groups entitlement, but application
         must explicitly state this access group in keychain queries in order to
         be able to access items from external tokens.
*/
extern const CFStringRef kSecAttrAccessGroupToken
    API_AVAILABLE(macos(10.12), ios(10.0));

/*!
    @function SecItemCopyMatching
    @abstract Returns one or more items which match a search query.
    @param query A dictionary containing an item class specification and
        optional attributes for controlling the search. See the "Keychain
        Search Attributes" section for a description of currently defined
        search attributes.
    @param result On return, a CFTypeRef reference to the found item(s). The
        exact type of the result is based on the search attributes supplied
        in the query, as discussed below.
    @result A result code. See "Security Error Codes" (SecBase.h).
    @discussion Attributes defining a search are specified by adding key/value
        pairs to the query dictionary.

    A typical query consists of:

      * a kSecClass key, whose value is a constant from the Class
        Constants section that specifies the class of item(s) to be searched
      * one or more keys from the "Attribute Key Constants" section, whose value
        is the attribute data to be matched
      * one or more keys from the "Search Constants" section, whose value is
        used to further refine the search
      * a key from the "Return Type Key Constants" section, specifying the type of
        results desired

   Result types are specified as follows:

      * To obtain the data of a matching item (CFDataRef), specify
        kSecReturnData with a value of kCFBooleanTrue.
      * To obtain the attributes of a matching item (CFDictionaryRef), specify
        kSecReturnAttributes with a value of kCFBooleanTrue.
      * To obtain a reference to a matching item (SecKeychainItemRef,
        SecKeyRef, SecCertificateRef, or SecIdentityRef), specify kSecReturnRef
        with a value of kCFBooleanTrue.
      * To obtain a persistent reference to a matching item (CFDataRef),
        specify kSecReturnPersistentRef with a value of kCFBooleanTrue. Note
        that unlike normal references, a persistent reference may be stored
        on disk or passed between processes.
      * If more than one of these result types is specified, the result is
        returned as a CFDictionaryRef containing all the requested data.
      * If a result type is not specified, no results are returned.

    By default, this function returns only the first match found. To obtain
    more than one matching item at a time, specify kSecMatchLimit with a value
    greater than 1. The result will be a CFArrayRef containing up to that
    number of matching items; the items' types are described above.

    To filter a provided list of items down to those matching the query,
    specify a kSecMatchItemList whose value is a CFArray of SecKeychainItemRef,
    SecKeyRef, SecCertificateRef, or SecIdentityRef items. The objects in the
    provided array must be of the same type.

    On iOS, to convert from a persistent item reference to a normal item reference,
    specify a kSecValuePersistentRef whose value a CFDataRef (the persistent
    reference), and a kSecReturnRef whose value is kCFBooleanTrue.

    On OSX, to convert from persistent item references to normal item references,
    specify a kSecMatchItemList whose value is a CFArray containing one or
    more CFDataRef elements (the persistent reference), and a kSecReturnRef
    whose value is kCFBooleanTrue. The objects in the provided array must be
    of the same type.
*/
OSStatus SecItemCopyMatching(CFDictionaryRef query, CFTypeRef * __nullable CF_RETURNS_RETAINED result)
    API_AVAILABLE(macos(10.6), ios(2.0));

/*!
    @function SecItemAdd
    @abstract Add one or more items to a keychain.
    @param attributes A dictionary containing an item class specification and
        optional entries specifying the item's attribute values. See the
        "Attribute Key Constants" section for a description of currently defined
        attributes.
    @param result On return, a CFTypeRef reference to the newly added item(s).
        The exact type of the result is based on the values supplied
        in attributes, as discussed below. Pass NULL if this result is not
        required.
    @result A result code. See "Security Error Codes" (SecBase.h).
    @discussion Attributes defining an item are specified by adding key/value
        pairs to the attributes dictionary.  To add multiple items to a keychain
        at once use the kSecUseItemList key with an array of items as its value.
        This is currently only supported for non password items.

        On OSX, To add an item to a particular keychain, supply kSecUseKeychain
        with a SecKeychainRef as its value.

    Result types are specified as follows:

      * To obtain the data of the added item (CFDataRef), specify
        kSecReturnData with a value of kCFBooleanTrue.
      * To obtain all the attributes of the added item (CFDictionaryRef),
        specify kSecReturnAttributes with a value of kCFBooleanTrue.
      * To obtain a reference to the added item (SecKeychainItemRef, SecKeyRef,
        SecCertiicateRef, or SecIdentityRef), specify kSecReturnRef with a
        value of kCFBooleanTrue.
      * To obtain a persistent reference to the added item (CFDataRef), specify
        kSecReturnPersistentRef with a value of kCFBooleanTrue. Note that
        unlike normal references, a persistent reference may be stored on disk
        or passed between processes.
      * If more than one of these result types is specified, the result is
        returned as a CFDictionaryRef containing all the requested data.
      * On iOS, if a result type is not specified, no results are returned.
        On OSX, the added item is returned.
*/
OSStatus SecItemAdd(CFDictionaryRef attributes, CFTypeRef * __nullable CF_RETURNS_RETAINED result)
    API_AVAILABLE(macos(10.6), ios(2.0));

/*!
    @function SecItemUpdate
    @abstract Modify zero or more items which match a search query.
    @param query A dictionary containing an item class specification and
        optional attributes for controlling the search. See the "Attribute
        Constants" and "Search Constants" sections for a description of
        currently defined search attributes.
    @param attributesToUpdate A dictionary containing one or more attributes
        whose values should be set to the ones specified. Only real keychain
        attributes are permitted in this dictionary (no "meta" attributes are
        allowed.) See the "Attribute Key Constants" section for a description of
        currently defined value attributes.
    @result A result code. See "Security Error Codes" (SecBase.h).
    @discussion Attributes defining a search are specified by adding key/value
        pairs to the query dictionary.
*/
OSStatus SecItemUpdate(CFDictionaryRef query, CFDictionaryRef attributesToUpdate)
    API_AVAILABLE(macos(10.6), ios(2.0));

/*!
    @function SecItemDelete
    @abstract Delete zero or more items which match a search query.
    @param query A dictionary containing an item class specification and
        optional attributes for controlling the search. See the "Attribute
        Constants" and "Search Constants" sections for a description of
        currently defined search attributes.
    @result A result code.  See "Security Error Codes" (SecBase.h).
    @discussion Attributes defining a search are specified by adding key/value
        pairs to the query dictionary.

    By default, this function deletes all items matching the specified query.
    You can change this behavior by specifying one of the follow keys:

      * To delete an item identified by a transient reference, on iOS, specify
        kSecValueRef with a item reference. On OS X, give a kSecMatchItemList
        containing an item reference.
      * To delete an item identified by a persistent reference, on iOS, specify
        kSecValuePersistentRef with a persistent reference returned by
        using the kSecReturnPersistentRef key to SecItemCopyMatching or
        SecItemAdd. on OSX, use kSecMatchItemList with a persistent reference
        returned by using the kSecReturnPersistentRef key with
        SecItemCopyMatching or SecItemAdd.
      * To delete multiple items specify kSecMatchItemList with an array
        of references.
      * If more than one of these result keys is specified, the behavior is
        undefined.
*/
OSStatus SecItemDelete(CFDictionaryRef query)
    API_AVAILABLE(macos(10.6), ios(2.0));

CF_IMPLICIT_BRIDGING_DISABLED
CF_ASSUME_NONNULL_END

__END_DECLS

#endif /* !_SECURITY_SECITEM_H_ */
