/*
 * Copyright (c) 2006-2010 Apple Inc. All Rights Reserved.
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

#include <CoreFoundation/CFNumber.h>
#include <CoreFoundation/CFArray.h>
#include <CoreFoundation/CFDictionary.h>

#if defined(__cplusplus)
extern "C" {
#endif
	
/*!
	 @enum Class Key Constant
	 @discussion Predefined key constant used to get or set item class values in
	 a dictionary. Its value is one of the constants defined in the Value
	 Constants for kSecClass.
	 @constant kSecClass Specifies a dictionary key whose value is the item's
	 class code.  You use this key to get or set a value of type CFTypeRef
	 that contains the item class code.
*/
extern const CFTypeRef kSecClass
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);

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
extern const CFTypeRef kSecClassInternetPassword
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecClassGenericPassword
	__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_2_0);
extern const CFTypeRef kSecClassCertificate
	__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_2_0);
extern const CFTypeRef kSecClassKey
	__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_2_0);
extern const CFTypeRef kSecClassIdentity
	__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_2_0);

/*!
	 @enum Attribute Key Constants
	 @discussion Predefined item attribute keys used to get or set values in a
	 dictionary. Not all attributes apply to each item class. The table
	 below lists the currently defined attributes for each item class:
	 
	 kSecClassGenericPassword item attributes:
	 kSecAttrAccess
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
	 
	 kSecClassInternetPassword item attributes:
	 kSecAttrAccess
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
	 
	 kSecClassCertificate item attributes:
	 kSecAttrCertificateType
	 kSecAttrCertificateEncoding
	 kSecAttrLabel
	 kSecAttrSubject
	 kSecAttrIssuer
	 kSecAttrSerialNumber
	 kSecAttrSubjectKeyID
	 kSecAttrPublicKeyHash
	 
	 kSecClassKey item attributes:
	 kSecAttrAccess
	 kSecAttrKeyClass
	 kSecAttrLabel
	 kSecAttrApplicationLabel
	 kSecAttrIsPermanent
	 kSecAttrApplicationTag
	 kSecAttrKeyType
	 kSecAttrPRF
	 kSecAttrSalt
	 kSecAttrRounds
	 kSecAttrKeySizeInBits
	 kSecAttrEffectiveKeySize
	 kSecAttrCanEncrypt
	 kSecAttrCanDecrypt
	 kSecAttrCanDerive
	 kSecAttrCanSign
	 kSecAttrCanVerify
	 kSecAttrCanWrap
	 kSecAttrCanUnwrap
	 
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
	 
    @constant kSecAttrAccess Specifies a dictionary key whose value
	 is a SecAccessRef describing the access control settings for this item.
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
	 a value of type CFNumberRef that denotes the certificate type (see the
	 CSSM_CERT_TYPE enum in cssmtype.h). (Items of class
	 kSecClassCertificate have this attribute.)
	 @constant kSecAttrCertificateEncoding (read-only) Specifies a dictionary
	 key whose value is the item's certificate encoding. You use this key
	 to get a value of type CFNumberRef that denotes the certificate
	 encoding (see the CSSM_CERT_ENCODING enum in cssmtype.h). (Items of
	 class kSecClassCertificate have this attribute.)
	 @constant kSecAttrKeyClass (read only) Specifies a dictionary key whose
	 value is one of kSecAttrKeyClassPublic, kSecAttrKeyClassPrivate or
	 kSecAttrKeyClassSymmetric.
	 @constant kSecAttrApplicationLabel Specifies a dictionary key whose value
	 is the key's application label attribute. This is different from the
	 kSecAttrLabel (which is intended to be human-readable). This attribute
	 is used to look up a key programmatically; in particular, for keys of
	 class kSecAttrKeyClassPublic and kSecAttrKeyClassPrivate, the value of
	 this attribute is the hash of the public key.
	 @constant kSecAttrIsPermanent Specifies a dictionary key whose value is a
	 CFBooleanRef indicating whether the key in question will be stored
	 permanently.
	 @constant kSecAttrApplicationTag Specifies a dictionary key whose value is a
	 CFDataRef containing private tag data.
	 @constant kSecAttrKeyType Specifies a dictionary key whose value is a
	 CFNumberRef indicating the algorithm associated with this key (see the
	 CSSM_ALGORITHMS enum in cssmtype.h).
	 @constant kSecAttrPRF Specifies a dictionary key whose value is the PRF
	 (pseudo-random function) for this key (see "kSecAttrPRF Value Constants".)
	 @constant kSecAttrSalt Specifies a dictionary key whose value is a
	 CFData containing the salt to use for this key.
	 @constant kSecAttrRounds Specifies a dictionary key whose value is the
	 number of rounds for the pseudo-random function specified by kSecAttrPRF.
	 @constant kSecAttrKeySizeInBits Specifies a dictionary key whose value
	 is a CFNumberRef indicating the number of bits in this key.
	 @constant kSecAttrEffectiveKeySize Specifies a dictionary key whose value
	 is a CFNumberRef indicating the effective number of bits in this key.
	 For example, a DES key has a kSecAttrKeySizeInBits of 64, but a
	 kSecAttrEffectiveKeySize of 56 bits.
	 @constant kSecAttrCanEncrypt Specifies a dictionary key whole value is a
	 CFBooleanRef indicating whether the key in question can be used to
	 encrypt data.
	 @constant kSecAttrCanDecrypt Specifies a dictionary key whole value is a
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
*/
extern const CFTypeRef kSecAttrAccess
	__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern const CFTypeRef kSecAttrCreationDate
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrModificationDate
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrDescription
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrComment
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrCreator
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrType
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrLabel
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrIsInvisible
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrIsNegative
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrAccount
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrService
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrGeneric
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrSecurityDomain
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrServer
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrProtocol
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrAuthenticationType
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrPort
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrPath
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrSubject
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrIssuer
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrSerialNumber
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrSubjectKeyID
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrPublicKeyHash
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrCertificateType
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrCertificateEncoding
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrKeyClass
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrApplicationLabel
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrIsPermanent
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrApplicationTag
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrKeyType
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrPRF
	__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern const CFTypeRef kSecAttrSalt
	__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern const CFTypeRef kSecAttrRounds
	__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern const CFTypeRef kSecAttrKeySizeInBits
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrEffectiveKeySize
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrCanEncrypt
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrCanDecrypt
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrCanDerive
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrCanSign
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrCanVerify
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrCanWrap
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrCanUnwrap
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
	
/*!
	 @enum kSecAttrProtocol Value Constants
	 @discussion Predefined item attribute constants used to get or set values
	 in a dictionary. The kSecAttrProtocol constant is the key and its
	 value is one of the constants defined here.
	 @constant kSecAttrProtocolFTP
	 @constant kSecAttrProtocolFTPAccount
	 @constant kSecAttrProtocolHTTP
	 @constant kSecAttrProtocolIRC
	 @constant kSecAttrProtocolNNTP
	 @constant kSecAttrProtocolPOP3
	 @constant kSecAttrProtocolSMTP
	 @constant kSecAttrProtocolSOCKS
	 @constant kSecAttrProtocolIMAP
	 @constant kSecAttrProtocolLDAP
	 @constant kSecAttrProtocolAppleTalk
	 @constant kSecAttrProtocolAFP
	 @constant kSecAttrProtocolTelnet
	 @constant kSecAttrProtocolSSH
	 @constant kSecAttrProtocolFTPS
	 @constant kSecAttrProtocolHTTPS
	 @constant kSecAttrProtocolHTTPProxy
	 @constant kSecAttrProtocolHTTPSProxy
	 @constant kSecAttrProtocolFTPProxy
	 @constant kSecAttrProtocolSMB
	 @constant kSecAttrProtocolRTSP
	 @constant kSecAttrProtocolRTSPProxy
	 @constant kSecAttrProtocolDAAP
	 @constant kSecAttrProtocolEPPC
	 @constant kSecAttrProtocolIPP
	 @constant kSecAttrProtocolNNTPS
	 @constant kSecAttrProtocolLDAPS
	 @constant kSecAttrProtocolTelnetS
	 @constant kSecAttrProtocolIMAPS
	 @constant kSecAttrProtocolIRCS
	 @constant kSecAttrProtocolPOP3S
*/
extern const CFTypeRef kSecAttrProtocolFTP
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrProtocolFTPAccount
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrProtocolHTTP
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrProtocolIRC
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrProtocolNNTP
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrProtocolPOP3
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrProtocolSMTP
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrProtocolSOCKS
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrProtocolIMAP
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrProtocolLDAP
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrProtocolAppleTalk
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrProtocolAFP
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrProtocolTelnet
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrProtocolSSH
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrProtocolFTPS
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrProtocolHTTPS
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrProtocolHTTPProxy
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrProtocolHTTPSProxy
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrProtocolFTPProxy
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrProtocolSMB
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrProtocolRTSP
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrProtocolRTSPProxy
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrProtocolDAAP
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrProtocolEPPC
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrProtocolIPP
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrProtocolNNTPS
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrProtocolLDAPS
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrProtocolTelnetS
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrProtocolIMAPS
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrProtocolIRCS
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrProtocolPOP3S
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
	
/*!
	 @enum kSecAttrAuthenticationType Value Constants
	 @discussion Predefined item attribute constants used to get or set values
	 in a dictionary. The kSecAttrAuthenticationType constant is the key
	 and its value is one of the constants defined here.
	 @constant kSecAttrAuthenticationTypeNTLM
	 @constant kSecAttrAuthenticationTypeMSN
	 @constant kSecAttrAuthenticationTypeDPA
	 @constant kSecAttrAuthenticationTypeRPA
	 @constant kSecAttrAuthenticationTypeHTTPBasic
	 @constant kSecAttrAuthenticationTypeHTTPDigest
	 @constant kSecAttrAuthenticationTypeHTMLForm
	 @constant kSecAttrAuthenticationTypeDefault
*/
extern const CFTypeRef kSecAttrAuthenticationTypeNTLM
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrAuthenticationTypeMSN
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrAuthenticationTypeDPA
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrAuthenticationTypeRPA
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrAuthenticationTypeHTTPBasic
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrAuthenticationTypeHTTPDigest
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrAuthenticationTypeHTMLForm
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecAttrAuthenticationTypeDefault
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
	
/*!
	 @enum kSecAttrKeyClass Value Constants
	 @discussion Predefined item attribute constants used to get or set values
	 in a dictionary. The kSecAttrKeyClass constant is the key
	 and its value is one of the constants defined here.
	 @constant kSecAttrKeyClassPublic
	 @constant kSecAttrKeyClassPrivate
	 @constant kSecAttrKeyClassSymmetric
*/
extern const CFTypeRef kSecAttrKeyClassPublic
	__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_2_0);
extern const CFTypeRef kSecAttrKeyClassPrivate
	__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_2_0);
extern const CFTypeRef kSecAttrKeyClassSymmetric
	__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_2_0);
	
/*!
	 @enum kSecAttrKeyType Value Constants
	 @discussion Predefined item attribute constants used to get or set values
	 in a dictionary. The kSecAttrKeyType constant is the key
	 and its value is one of the constants defined here.
	 @constant kSecAttrKeyTypeRSA
	 @constant kSecAttrKeyTypeDSA
	 @constant kSecAttrKeyTypeAES
	 @constant kSecAttrKeyType3DES
	 @constant kSecAttrKeyTypeRC4
	 @constant kSecAttrKeyTypeRC2
	 @constant kSecAttrKeyTypeCAST
	 @constant kSecAttrKeyTypeECDSA
*/
extern const CFTypeRef kSecAttrKeyTypeRSA
	__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_2_0);
extern const CFTypeRef kSecAttrKeyTypeDSA
	__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern const CFTypeRef kSecAttrKeyTypeAES
	__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern const CFTypeRef kSecAttrKeyTypeDES
	__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern const CFTypeRef kSecAttrKeyType3DES
	__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern const CFTypeRef kSecAttrKeyTypeRC4
	__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern const CFTypeRef kSecAttrKeyTypeRC2
	__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern const CFTypeRef kSecAttrKeyTypeCAST
	__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern const CFTypeRef kSecAttrKeyTypeECDSA
	__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
    
/*!
	 @enum kSecAttrPRF Value Constants
	 @discussion Predefined item attribute constants used to specify the PRF
     to use with SecKeyDeriveFromPassword.
	 @constant kSecAttrPRFHmacAlgSHA1
     @constant kSecAttrPRFHmacAlgSHA224
     @constant kSecAttrPRFHmacAlgSHA256
     @constant kSecAttrPRFHmacAlgSHA384
     @constant kSecAttrPRFHmacAlgSHA512
*/
extern const CFTypeRef kSecAttrPRFHmacAlgSHA1
	__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern const CFTypeRef kSecAttrPRFHmacAlgSHA224
	__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern const CFTypeRef kSecAttrPRFHmacAlgSHA256
	__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern const CFTypeRef kSecAttrPRFHmacAlgSHA384
	__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern const CFTypeRef kSecAttrPRFHmacAlgSHA512
  	__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
 
/*!
	 @enum Search Constants
	 @discussion Predefined search constants used to set values in a query
	 dictionary. You can specify a combination of search attributes and
	 item attributes when looking for matching items with the
	 SecItemCopyMatching function.
	 @constant kSecMatchPolicy Specifies a dictionary key whose value is a
	 SecPolicyRef. If provided, returned certificates or identities must
	 verify with this policy.
	 @constant kSecMatchItemList Specifies a dictionary key whose value is a
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
	 @constant kSecMatchSubjectStartsWith Specifies a dictionary key whose value
	 is a CFStringRef. If provided, returned certificates or identities
	 will be limited to those with subject names that start with this string.
	 @constant kSecMatchSubjectEndsWith Specifies a dictionary key whose value
	 is a CFStringRef. If provided, returned certificates or identities
	 will be limited to those with subject names that end with this string.
	 @constant kSecMatchSubjectWholeString Specifies a dictionary key whose
	 value is a CFStringRef. If provided, returned certificates or identities
	 will be limited to those matching this string exactly in the subject.
	 @constant kSecMatchCaseInsensitive Specifies a dictionary key whose value
	 is a CFBooleanRef. If this value is kCFBooleanFalse, or is not
	 provided, then case-sensitive string matching is performed.
	 @constant kSecMatchDiacriticInsensitive Specifies a dictionary key whose
	 value is a CFBooleanRef. If this value is kCFBooleanFalse, or is not
	 provided, then diacritic-sensitive string matching is performed.
	 @constant kSecMatchWidthInsensitive Specifies a dictionary key whose
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
extern const CFTypeRef kSecMatchPolicy
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecMatchItemList
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecMatchSearchList
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecMatchIssuers
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecMatchEmailAddressIfPresent
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecMatchSubjectContains
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecMatchSubjectStartsWith
	__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern const CFTypeRef kSecMatchSubjectEndsWith
	__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern const CFTypeRef kSecMatchSubjectWholeString
	__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern const CFTypeRef kSecMatchCaseInsensitive
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecMatchDiacriticInsensitive
	__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern const CFTypeRef kSecMatchWidthInsensitive
	__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);
extern const CFTypeRef kSecMatchTrustedOnly
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecMatchValidOnDate
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecMatchLimit
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecMatchLimitOne
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecMatchLimitAll
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
	
	
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
	 (non-encrypted) attributes of an item (in a CFDictionaryRef) should be
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
extern const CFTypeRef kSecReturnData
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecReturnAttributes
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecReturnRef
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecReturnPersistentRef
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);

	
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
extern const CFTypeRef kSecValueData
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecValueRef
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecValuePersistentRef
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
	
	
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
	 @constant kSecUseKeychain Specifies a dictionary key whose value is a
	 keychain reference. You use this key to specify a value of type
	 SecKeychainRef to which SecItemAdd will add the provided item(s).
*/
extern const CFTypeRef kSecUseItemList
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
extern const CFTypeRef kSecUseKeychain
	__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_NA);

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
	 
	 By default, this function returns only the first match found. To obtain
	 more than one matching item at a time, specify kSecMatchLimit with a value
	 greater than 1. The result will be a CFArrayRef containing up to that
	 number of matching items; the items' types are described above.
	 
	 To filter a provided list of items down to those matching the query,
	 specify a kSecMatchItemList whose value is a CFArray of SecKeychainItemRef,
	 SecKeyRef, SecCertificateRef, or SecIdentityRef items. The objects in the
	 provided array must be of the same type.
	 
	 To convert from persistent item references to normal item references,
	 specify a kSecMatchItemList whose value is a CFArray containing one or
	 more CFDataRef elements (the persistent reference), and a kSecReturnRef
	 whose value is kCFBooleanTrue. The objects in the provided array must be
	 of the same type.
*/
OSStatus SecItemCopyMatching(CFDictionaryRef query, CFTypeRef *result)
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
	
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
	 This is currently only supported for non password items.  To add an item
	 to a particular keychain, supply kSecUseKeychain with a SecKeychainRef as
	 its value.
	 
	 Result types are specified as follows:
	 
	 * To obtain the data of the added item (CFDataRef), specify
	 kSecReturnData with a value of kCFBooleanTrue.
	 * To obtain all the attributes of the added item (CFDictionaryRef),
	 specify kSecReturnAttributes with a value of kCFBooleanTrue.
	 * To obtain a reference to the added item (SecKeychainItemRef, SecKeyRef,
	 SecCertificateRef, or SecIdentityRef), specify kSecReturnRef with a
	 value of kCFBooleanTrue. This is the default behavior if a result
	 type is not explicitly specified.
	 * To obtain a persistent reference to the added item (CFDataRef), specify
	 kSecReturnPersistentRef with a value of kCFBooleanTrue. Note that
	 unlike normal references, a persistent reference may be stored on disk
	 or passed between processes.
	 * If more than one of these result types is specified, the result is
	 returned as a CFDictionaryRef containing all the requested data.
*/
OSStatus SecItemAdd(CFDictionaryRef attributes, CFTypeRef *result)
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);
	
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
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);

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
	 
	 * To delete an item identified by a transient reference, specify
	 kSecMatchItemList with a reference returned by using the kSecReturnRef
	 key in a previous call to SecItemCopyMatching or SecItemAdd.
	 * To delete an item identified by a persistent reference, specify
	 kSecMatchItemList with a persistent reference returned by using the
	 kSecReturnPersistentRef key to SecItemCopyMatching or SecItemAdd.
	 * If more than one of these result keys is specified, the behavior is
	 undefined.
*/
OSStatus SecItemDelete(CFDictionaryRef query)
	__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_2_0);

#if defined(__cplusplus)
}
#endif

#endif /* !_SECURITY_SECITEM_H_ */
