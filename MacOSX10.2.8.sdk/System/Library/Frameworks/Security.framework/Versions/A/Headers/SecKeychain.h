/*
 * Copyright (c) 2000-2002 Apple Computer, Inc. All Rights Reserved.
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

/*!
	@header SecKeychain
	SecKeychain implements a repository for securely storing items with publicly visible attributes by which to find the items.
*/

#ifndef _SECURITY_SECKEYCHAIN_H_
#define _SECURITY_SECKEYCHAIN_H_

#include <Security/SecBase.h>
#include <Security/cssmapple.h>
#include <CoreFoundation/CFArray.h>


#if defined(__cplusplus)
extern "C" {
#endif

/*!
	@enum KeychainStatus
	@abstract Defines the current status of a keychain.
	@constant kSecUnlockStateStatus Indicates the keychain is unlocked.
	@constant kSecReadPermStatus Indicates the keychain is readable.
	@constant kSecWritePermStatus Indicates the keychain is writable.
*/
enum
{
    kSecUnlockStateStatus        = 1,
    kSecReadPermStatus           = 2,
    kSecWritePermStatus          = 4
};

#define SEC_KEYCHAIN_SETTINGS_VERS1 1

/*!
	@typedef SecKeychainSettings
	@abstract Contains keychain settings.
	@field version An unsigned 32-bit integer representing the keychain version.
	@field lockOnSleep A boolean value indicating whether the keychain locks when the system sleeps.
	@field useLockInterval A boolean value indicating whether the keychain automatically locks after a certain period of time.
	@field lockInterval An unsigned 32-bit integer representing the number of seconds before the keychain locks.
*/
struct SecKeychainSettings
{ 
	UInt32		version; 
	Boolean		lockOnSleep;
	Boolean		useLockInterval;
	UInt32		lockInterval;
};
typedef struct SecKeychainSettings		SecKeychainSettings;

/*! 
    @typedef SecAuthenticationType
	@abstract Represents the type of authentication to use for an Internet password.
*/
typedef FourCharCode SecAuthenticationType;

/*!
	@enum AuthenticationConstants
	@abstract Defines constants you can use to identify the type of authentication to use for an Internet password.
	@constant kSecAuthenticationTypeNTLM Specifies Windows NT LAN Manager authentication.
	@constant kSecAuthenticationTypeMSN Specifies Microsoft Network default authentication.
	@constant kSecAuthenticationTypeDPA Specifies Distributed Password authentication.
	@constant kSecAuthenticationTypeRPA Specifies Remote Password authentication. 
	@constant kSecAuthenticationTypeHTTPDigest Specifies HTTP Digest Access authentication.
	@constant kSecAuthenticationTypeDefault Specifies the default authentication type.
*/
enum
{
    kSecAuthenticationTypeNTLM             = 'ntlm',
    kSecAuthenticationTypeMSN              = 'msna',
    kSecAuthenticationTypeDPA              = 'dpaa',
    kSecAuthenticationTypeRPA              = 'rpaa',
    kSecAuthenticationTypeHTTPDigest       = 'httd',
    kSecAuthenticationTypeDefault          = 'dflt'
};

/*!
	@typedef SecProtocolType
	@abstract Represents the protocol type associated with an AppleShare or Internet password.
*/
typedef FourCharCode SecProtocolType;

/*!
	@enum ProtocolTypeConstants
	@abstract Defines the protocol type associated with an AppleShare or Internet password.
	@constant kSecProtocolTypeFTP Indicates FTP.
	@constant kSecProtocolTypeFTPAccount Indicates FTP Account.
	@constant kSecProtocolTypeHTTP Indicates HTTP. 
	@constant kSecProtocolTypeIRC Indicates IRC.
	@constant kSecProtocolTypeNNTP Indicates NNTP.
	@constant kSecProtocolTypePOP3 Indicates POP3.
	@constant kSecProtocolTypeSMTP Indicates SMTP.
	@constant kSecProtocolTypeSOCKS Indicates SOCKS.
	@constant kSecProtocolTypeIMAP Indicates IMAP.
	@constant kSecProtocolTypeLDAP Indicates LDAP.
	@constant kSecProtocolTypeAppleTalk Indicates AFP over AppleTalk.
	@constant kSecProtocolTypeAFP Indicates AFP.
	@constant kSecProtocolTypeTelnet Indicates Telnet.
	@constant kSecProtocolTypeSSH Indicates SSH.
*/
enum
{
    kSecProtocolTypeFTP			= 'ftp ',
    kSecProtocolTypeFTPAccount	= 'ftpa',
    kSecProtocolTypeHTTP		= 'http',
    kSecProtocolTypeIRC			= 'irc ',
    kSecProtocolTypeNNTP		= 'nntp',
    kSecProtocolTypePOP3		= 'pop3',
    kSecProtocolTypeSMTP		= 'smtp',
    kSecProtocolTypeSOCKS		= 'sox ',
    kSecProtocolTypeIMAP		= 'imap',
    kSecProtocolTypeLDAP		= 'ldap',
    kSecProtocolTypeAppleTalk	= 'atlk',
    kSecProtocolTypeAFP			= 'afp ',
    kSecProtocolTypeTelnet		= 'teln',
	kSecProtocolTypeSSH			= 'ssh '
};

/*!
	@typedef SecKeychainEvent
	@abstract Represents an event in which the state of a keychain or one of its items changed.
*/
typedef UInt32 SecKeychainEvent;

/*!
	@enum KeychainEventConstants
	@abstract Defines the keychain-related event.
	@constant kSecLockEvent Indicates a keychain was locked.
	@constant kSecUnlockEvent Indicates a keychain was unlocked.
	@constant kSecAddEvent Indicates an item was added to a keychain.
	@constant kSecDeleteEvent Indicates an item was deleted from a keychain.
	@constant kSecUpdateEvent Indicates a keychain item was updated.
	@constant kSecPasswordChangedEvent Indicates the keychain password was changed.
	@constant kSecDefaultChangedEvent Indicates that a different keychain was specified as the default.
	@constant kSecDataAccessEvent Indicates a process has accessed a keychain item's data.
	@constant kSecKeychainListChangedEvent Indicates the list of keychains has changed.
*/
enum
{
    kSecLockEvent                = 1,
    kSecUnlockEvent              = 2,
    kSecAddEvent                 = 3,
    kSecDeleteEvent              = 4,
    kSecUpdateEvent              = 5,
    kSecPasswordChangedEvent     = 6,
    kSecDefaultChangedEvent      = 9,
    kSecDataAccessEvent          = 10,
    kSecKeychainListChangedEvent = 11
};

/*!
	@typedef SecKeychainEventMask
	@abstract Represents a bit mask of keychain events
*/
typedef UInt32 SecKeychainEventMask;

/*!
	@enum KeychainEventConstants
	@abstract Defines keychain event constants
	@constant kSecLockEventMask If the bit specified by this mask is set, your callback function will be invoked when a keychain is locked.
	@constant kSecUnlockEventMask If the bit specified by this mask is set, your callback function will be invoked when a keychain is unlocked.
	@constant kSecAddEventMask If the bit specified by this mask is set, your callback function will be invoked when an item is added to a keychain.
	@constant kSecDeleteEventMask If the bit specified by this mask is set, your callback function will be invoked when an item is deleted from a keychain.
	@constant kSecUpdateEventMask If the bit specified by this mask is set, your callback function will be invoked when a keychain item is updated.
	@constant kSecPasswordChangedEventMask If the bit specified by this mask is set, your callback function will be invoked when the keychain password is changed.
	@constant kSecDefaultChangedEventMask If the bit specified by this mask is set, your callback function will be invoked when a different keychain is specified as the default.
	@constant kSecDataAccessEventMask If the bit specified by this mask is set, your callback function will be invoked when a process accesses a keychain item's data.
	@constant kSecEveryEventMask If all the bits are set, your callback function will be invoked whenever any event occurs.
*/
enum
{
    kSecLockEventMask            = 1 << kSecLockEvent,
    kSecUnlockEventMask          = 1 << kSecUnlockEvent,
    kSecAddEventMask             = 1 << kSecAddEvent,
    kSecDeleteEventMask          = 1 << kSecDeleteEvent,
    kSecUpdateEventMask          = 1 << kSecUpdateEvent,
    kSecPasswordChangedEventMask = 1 << kSecPasswordChangedEvent,
    kSecDefaultChangedEventMask  = 1 << kSecDefaultChangedEvent,
    kSecDataAccessEventMask      = 1 << kSecDataAccessEvent,
    kSecKeychainListChangedMask  = 1 << kSecKeychainListChangedEvent,
    kSecEveryEventMask           = 0xffffffff
};

/*!
	@typedef SecKeychainCallbackInfo
	@abstract Contains information about a keychain event. 
	@field version The version of this structure.
	@field item A reference to the keychain item associated with this event, if any. Note that some events do not involve a particular keychain item.
	@field keychain A reference to the keychain in which the event occurred.
	@field pid The id of the process that generated this event.
	@discussion The SecKeychainCallbackInfo type represents a structure that contains information about the keychain event for which your application is being notified. For information on how to write a keychain event callback function, see SecKeychainCallback. 
*/
struct SecKeychainCallbackInfo 
{
    UInt32				version;
    SecKeychainItemRef	item;
    SecKeychainRef		keychain;
	pid_t				pid;
};
typedef struct SecKeychainCallbackInfo SecKeychainCallbackInfo;
									
/*!
	@function SecKeychainGetTypeID
	@abstract Returns the type identifier of SecKeychain instances.
	@result The CFTypeID of SecKeychain instances.
*/
CFTypeID SecKeychainGetTypeID(void);

/*!
	@function SecKeychainGetVersion
	@abstract Determines the version of the Keychain Manager installed on the userÕs system.
	@param returnVers On return, a pointer to the version number of the Keychain Manager installed on the current system.
	@result A result code.  See "Security Error Codes" (SecBase.h).
*/
OSStatus SecKeychainGetVersion(UInt32 *returnVers);

#pragma mark ÑÑÑÑ Keychain Management ÑÑÑÑ
/*!
    @function SecKeychainOpen
    @abstract Opens a keychain.
	@param pathName The POSIX path to a keychain.
    @param keychain On return, a pointer to the keychain reference. The memory that keychain occupies must be released by calling CFRelease when finished with it.
	@result A result code.  See "Security Error Codes" (SecBase.h). In addition, paramErr (-50) may be returned if the keychain parameter is invalid (NULL).
*/
OSStatus SecKeychainOpen(const char *pathName, SecKeychainRef *keychain);

/*!
	@function SecKeychainCreateNew
    @abstract Creates a new keychain.
    @param pathName The POSIX path to a keychain file.
    @param passwordLength An unsigned 32-bit integer representing the length of the password buffer.
    @param password A pointer to the buffer containing the password. The password must be in canonical UTF8 encoding.
	@param promptUser A boolean representing whether to display a password dialog to the user.
	@param initialAccess An access reference.
    @param keychain On return, a pointer to a keychain reference. The memory that keychain occupies must be released by calling CFRelease when finished with it.
	@result A result code.  See "Security Error Codes" (SecBase.h). In addition, paramErr (-50) may be returned if the keychain parameter is invalid (NULL).
*/
OSStatus SecKeychainCreate(const char *pathName, UInt32 passwordLength, const void *password, Boolean promptUser, SecAccessRef initialAccess, SecKeychainRef *keychain);

/*!
	@function SecKeychainDelete
    @abstract Deletes a keychain from the default searchlist, and removes the keychain itself if it is a file.
    @param keychain A pointer to a keychain reference.
	@result A result code.  See "Security Error Codes" (SecBase.h). In addition, paramErr (-50) may be returned if the keychain parameter is invalid (NULL).
*/
OSStatus SecKeychainDelete(SecKeychainRef keychain);

/*!
	@function SecKeychainSetSettings
	@abstract Changes the settings of a keychain.
    @param keychain A reference to a keychain.
 	@param newSettings A pointer to the new keychain settings.
	@result A result code.  See "Security Error Codes" (SecBase.h).
*/
OSStatus SecKeychainSetSettings(SecKeychainRef keychain, const SecKeychainSettings *newSettings);

/*!
	@function SecKeychainCopySettings
	@abstract Copy the keychain settings.
    @param keychain A reference to the keychain from which to copy its settings.
    @param outSettings  A pointer to a keychain settings structure. Since this structure is versioned, you must preallocate it and fill in the version of the structure.
 @result A result code.  See "Security Error Codes" (SecBase.h).
*/
OSStatus SecKeychainCopySettings(SecKeychainRef keychain, SecKeychainSettings *outSettings);

/*!
	@function SecKeychainUnlock
	@abstract Unlocks the specified keychain.
    @param keychain A reference to the keychain to unlock. Pass NULL to specify the default keychain. If you pass NULL and the default keychain is currently locked, the keychain will appear as the default choice. If you pass a locked keychain, SecKeychainUnlock will use the password provided to unlock it. If the default keychain is currently unlocked, SecKeychainUnlock returns noErr. 
	@param passwordLength An unsigned 32-bit integer representing the length of the password buffer.
	@param password A buffer containing the password for the keychain. Pass NULL if the user password is unknown. In this case, SecKeychainUnlock displays the Unlock Keychain dialog box, and the authentication user interface associated with the keychain about to be unlocked.
	@param usePassword A boolean indicating whether the password parameter is used.  You should pass TRUE if it is used or FALSE if it is ignored.
	@result A result code.  See "Security Error Codes" (SecBase.h).
	@discussion In most cases, your application does not need to call the SecKeychainUnlock function directly, since most Keychain Manager functions that require an unlocked keychain call SecKeychainUnlock automatically. If your application needs to verify that a keychain is unlocked, call the function SecKeychainGetStatus. 
*/
OSStatus SecKeychainUnlock(SecKeychainRef keychain, UInt32 passwordLength, void *password, Boolean usePassword);

/*!
	@function SecKeychainLock
	@abstract Locks the specified keychain. 
    @param keychain A reference to the keychain to lock.
	@result A result code.  See "Security Error Codes" (SecBase.h).
*/
OSStatus SecKeychainLock(SecKeychainRef	keychain);

/*!
	@function SecKeychainLockAll
	@abstract Locks all keychains belonging to the current user.
	@result A result code.  See "Security Error Codes" (SecBase.h).
*/
OSStatus SecKeychainLockAll(void);

/*!
	@function SecKeychainCopyDefault
	@abstract Retrieves a reference to the default keychain.
	@param keychain On return, a pointer to the default keychain reference.
	@result A result code.  See "Security Error Codes" (SecBase.h).
*/
OSStatus SecKeychainCopyDefault(SecKeychainRef *keychain);

/*!
	@function SecKeychainSetDefault
	@abstract Sets the default keychain. 
	@param keychain A reference to the keychain to set as default.
	@result A result code.  See "Security Error Codes" (SecBase.h). In addition, paramErr (-50) may be returned if the keychain parameter is invalid (NULL).
*/
OSStatus SecKeychainSetDefault(SecKeychainRef keychain);

/*!
	@function SecKeychainCopySearchList
	@abstract Retrieves a keychain search list.
	@param searchList The returned list of keychains to search. When finished with the array, you must call CFRelease() to release the memory.
	@result A result code.  See "Security Error Codes" (SecBase.h). In addition, paramErr (-50) may be returned if the keychain list is not specified (NULL).
*/
OSStatus SecKeychainCopySearchList(CFArrayRef *searchList);

/*!
	@function SecKeychainSetSearchList
	@abstract Specifies the list of keychains to use in a keychain search list.
	@param searchList The list of keychains to use in a search list when the SecKeychainCopySearchList function is called.
	@result A result code.  See "Security Error Codes" (SecBase.h). In addition, paramErr (-50) may be returned if the keychain list is not specified (NULL).
*/
OSStatus SecKeychainSetSearchList(CFArrayRef searchList);

/*!
	@function SecKeychainGetStatus
	@abstract Retrieves status information for the specified keychain.
	@param keychain A keychain reference. Pass NULL to specify the default keychain.
	@param keychainStatus On return, a pointer to the status of the specified keychain.  See KeychainStatus for valid status constants.
    @result A result code.  See "Security Error Codes" (SecBase.h).
*/
OSStatus SecKeychainGetStatus(SecKeychainRef keychain, SecKeychainStatus *keychainStatus);

/*!
	@function SecKeychainGetPath
	@abstract Get the path of the specified keychain.
    @param keychain A reference to a keychain.
    @param ioPathLength On input, a pointer to the size or the buffer pointed to by pathName. On return, the size of the buffer without the zero termination.
	@param pathName On return, the POSIX path to the keychain.
    @result A result code.  See "Security Error Codes" (SecBase.h).
*/
OSStatus SecKeychainGetPath(SecKeychainRef keychain, UInt32 *ioPathLength, char *pathName);

#pragma mark ÑÑÑÑ Keychain Item Attribute Information ÑÑÑÑ
/*!
	@function SecKeychainAttributeInfoForItemID
	@abstract Obtains tags for all possible attributes for a given item class.
    @param keychain A keychain reference.
	@param itemID The relation identifier of the item tags.
	@param info On return, a pointer to the keychain attribute information. User should call the SecKeychainFreeAttributeInfo function to release the structure when done with it. 
    @result A result code.  See "Security Error Codes" (SecBase.h). In addition, paramErr (-50) may be returned if not enough valid parameters were supplied (NULL).
	@discussion Warning, this call returns more attributes than are support by the old style Keychain API and passing them into older calls will yield an invalid attribute error. The recommended call to retrieve the attribute values is the SecKeychainItemCopyAttributesAndData function.
*/
OSStatus SecKeychainAttributeInfoForItemID(SecKeychainRef keychain,  UInt32 itemID, SecKeychainAttributeInfo **info);

/*!
	@function SecKeychainFreeAttributeInfo
	@abstract Releases the memory acquired by calling the SecKeychainAttributeInfoForItemID function.
	@param info A pointer to the keychain attribute information to release.
    @result A result code.  See "Security Error Codes" (SecBase.h). In addition, paramErr (-50) may be returned if not enough valid parameters were supplied (NULL).
*/
OSStatus SecKeychainFreeAttributeInfo(SecKeychainAttributeInfo *info);

#pragma mark ÑÑÑÑ Keychain Manager Callbacks ÑÑÑÑ
 
/*!
	@typedef SecKeychainCallback
	@abstract Defines a pointer to a customized callback function.  You supply the customized callback function to do a callback tailored to your application's needs.
	@param keychainEvent The keychain event that your application wishes to be notified of. See SecKeychainEvent for a description of possible values. The type of event that can trigger your callback depends on the bit mask you passed in the eventMask parameter of the function SecKeychainAddCallback. For more information, see the discussion. 
	@param info A pointer to a structure of type SecKeychainCallbackInfo. On return, the structure contains information about the keychain event that occurred. The Keychain Manager passes this information to your callback function via the info parameter. 
	@param context A pointer to application-defined storage that your application previously passed to the function SecKeychainAddCallback. You can use this value to perform operations like track which instance of a function is operating.
	@result A result code.  See "Security Error Codes" (SecBase.h).
	@discussion If you name your function MyKeychainEventCallback, you would declare it like this:
	OSStatus MyKeychainEventCallback (
		SecKeychainEvent keychainEvent, 
		SecKeychainCallbackInfo *info, 
		void *context);

	To add your callback function, use the SecKeychainAddCallback function.  To remove your callback function, use the SecKeychainRemoveCallback function.
*/
typedef OSStatus (*SecKeychainCallback)(SecKeychainEvent keychainEvent, SecKeychainCallbackInfo *info, void *context);

/*!
	@function SecKeychainAddCallback
	@abstract Registers your keychain event callback function
	@param callbackFunction A pointer to your keychain event callback function, described in SecKeychainCallback. You indicate the type of keychain events you want to receive by passing a bit mask of the desired events in the eventMask parameter.
	@param eventMask A bit mask indicating the keychain events that your application wishes to be notified of. See SecKeychainEventMask for a description of this bit mask. The Keychain Manager tests this mask to determine the keychain events that you wish to receive, and passes these events in the keychainEvent parameter of your callback function. See SecKeychainEvent for a description of these events.
	@param userContext A pointer to application-defined storage that will be passed to your callback function. Your application can use this to associate any particular call of SecKeychainAddCallback with any particular call of your keychain event callback function.
    @result A result code.  See "Security Error Codes" (SecBase.h).
*/
OSStatus SecKeychainAddCallback(SecKeychainCallback callbackFunction, SecKeychainEventMask eventMask, void* userContext);

/*!
	@function SecKeychainRemoveCallback
	@abstract Unregisters your keychain event callback function. Once removed, keychain events won't be sent to the owner of the callback.
	@param callbackFunction The callback function pointer to remove 
	@result A result code.  See "Security Error Codes" (SecBase.h).
*/
OSStatus SecKeychainRemoveCallback(SecKeychainCallback callbackFunction);

#pragma mark ÑÑÑÑ High Level Keychain Manager Calls ÑÑÑÑ
/*!
	@function SecKeychainAddInternetPassword
	@abstract Adds an internet password as a keychain item to the specified keychain.
	@param keychain	A reference to keychain in which to store an internet password.
	@param serverNameLength The length of the buffer pointed to by server name.
	@param serverName A pointer to a string containing the server name.
	@param securityDomainLength The length of the buffer pointed to by security domain.
	@param securityDomain A pointer to a string containing the security domain. This parameter is optional, as not all protocols will require it.
	@param accountNameLength The length of the buffer pointed to by account name.
	@param accountName A pointer to a string containing the account name.
	@param pathLength The length of the buffer pointed to by path.
	@param path A pointer to a string containing the path.
	@param port The TCP/IP port number.
	@param protocol The protocol associated with this password. See SecProtocolType for a description of possible values.
	@param authenticationType The authentication scheme used. See SecAuthenticationType for a description of possible values. Pass the constant kSecAuthenticationTypeDefault, to specify the default authentication scheme. 
	@param passwordLength The length of the buffer pointed to by passwordData.
	@param passwordData A pointer to a buffer which will hold the returned password data. Before calling SecKeychainAddInternetPassword, allocate enough memory for the buffer to hold the data you want to store.
	@param itemRef On return, a pointer to the new keychain item.
	@result A result code.  See "Security Error Codes" (SecBase.h).
	@discussion The SecKeychainAddInternetPassword function adds a new internet server password to the default keychain. Required parameters to identify the password are serverName and accountName (you cannot pass NULL for both parameters). In addition, some protocols may require an optional securityDomain when authentication is requested. SecKeychainAddInternetPassword optionally returns a reference to the newly added item. 
*/
OSStatus SecKeychainAddInternetPassword(SecKeychainRef keychain, UInt32 serverNameLength, const char *serverName, UInt32 securityDomainLength, const char *securityDomain, UInt32 accountNameLength, const char *accountName, UInt32 pathLength, const char *path, UInt16 port, SecProtocolType protocol, SecAuthenticationType authenticationType, UInt32 passwordLength, const void *passwordData, SecKeychainItemRef *itemRef);

/*!
	@function SecKeychainFindInternetPassword
	@abstract Finds an internet password based on the attributes passed.
    @param keychainOrArray An reference to an array of keychains to search, a single keychain or NULL to search the user's default keychain search list.
	@param serverNameLength The length of the buffer pointed to by server name.
	@param serverName A pointer to a string containing the server name.
	@param securityDomainLength The length of the buffer pointed to by security domain.
	@param securityDomain A pointer to a string containing the security domain. This parameter is optional, as not all protocols will require it.
	@param accountNameLength The length of the buffer pointed to by account name.
	@param accountName A pointer to a string containing the account name.
	@param pathLength The length of the buffer pointed to by path.
	@param path A pointer to a string containing the path.
	@param port The TCP/IP port number.
	@param protocol The protocol associated with this password. See SecProtocolType for a description of possible values.
	@param authenticationType The authentication scheme used. See SecAuthenticationType for a description of possible values. Pass the constant kSecAuthenticationTypeDefault, to specify the default authentication scheme. 
	@param passwordLength The length of the buffer pointed to by passwordData.
	@param passwordData A pointer to a buffer which will hold the returned password data. Before calling SecKeychainFindInternetPassword, allocate enough memory for the buffer to hold the data you want to store.
	@param itemRef The item reference of the internet password.
	@result A result code.  See "Security Error Codes" (SecBase.h).
	@discussion The SecKeychainFindInternetPassword function finds the first internet password item which matches the attributes you provide. The buffer specified in the passwordData parameter must be large enough to hold the password data, otherwise SecKeychainFindInternetPassword returns the result code errSecBufferTooSmall. In this case, your application must allocate a new buffer of sufficient size before calling SecKeychainFindInternetPassword again. SecKeychainFindInternetPassword optionally returns a reference to the found item. 
  
*/
OSStatus SecKeychainFindInternetPassword(CFTypeRef keychainOrArray, UInt32 serverNameLength, const char *serverName, UInt32 securityDomainLength, const char *securityDomain, UInt32 accountNameLength, const char *accountName, UInt32 pathLength, const char *path, UInt16 port, SecProtocolType protocol, SecAuthenticationType authenticationType, UInt32 *passwordLength, void **passwordData, SecKeychainItemRef *itemRef);

/*!
	@function SecKeychainAddGenericPassword
	@abstract Adds a generic password to the specified keychain.
	@param keychain A reference to keychain in which to store a generic password. 
	@param serviceNameLength The length of the buffer pointed to by service name.
	@param serviceName A pointer to a string containing the service name.
	@param accountNameLength The length of the buffer pointed to by account name.
	@param accountName A pointer to a string containing the account name.
	@param passwordLength The length of the buffer pointed to by passwordData.
	@param passwordData A pointer to a buffer which will hold the returned password data. Before calling SecKeychainAddInternetPassword, allocate enough memory for the buffer to hold the data you want to store.
	@param itemRef On return, a pointer to the new keychain item reference.
	@result A result code.  See "Security Error Codes" (SecBase.h).
	@discussion The SecKeychainAddGenericPassword function adds a new generic password to the default keychain. Required parameters to identify the password are serviceName and accountName, which are application-defined strings. SecKeychainAddGenericPassword optionally returns a reference to the newly added item. 

	You can use SecKeychainAddGenericPassword to add passwords for accounts other than Internet or Appleshare. For example, you might add passwords for your database or scheduling programs.
*/
OSStatus SecKeychainAddGenericPassword(SecKeychainRef keychain, UInt32 serviceNameLength, const char *serviceName, UInt32 accountNameLength, const char *accountName, UInt32 passwordLength, const void *passwordData, SecKeychainItemRef *itemRef);

/*!
	@function SecKeychainFindGenericPassword
	@abstract Find a generic password based on the attributes passed.
    @param keychainOrArray An reference to an array of keychains to search, a single keychain or NULL to search the user's default keychain search list.
	@param serviceNameLength The length of the buffer pointed to by service name.
	@param serviceName A pointer to a string containing the service name.
	@param accountNameLength The length of the buffer pointed to by account name.
	@param accountName A pointer to a string containing the account name.
	@param passwordLength The length of the buffer pointed to by passwordData.
	@param passwordData A pointer to a buffer which will hold the returned password data. Before calling SecKeychainAddInternetPassword, allocate enough memory for the buffer to hold the data you want to store.
	@param itemRef On return, a pointer to the new keychain item reference.
	@result A result code.  See "Security Error Codes" (SecBase.h).
	@discussion The SecKeychainFindGenericPassword function finds the first generic password item which matches the attributes you provide. The buffer specified in the passwordData parameter must be large enough to hold the password data, otherwise SecKeychainFindGenericPassword returns the result code errSecBufferTooSmall. In this case, your application must allocate a new buffer of sufficient size before calling SecKeychainFindGenericPassword again. SecKeychainFindGenericPassword optionally returns a reference to the found item. 
*/
OSStatus SecKeychainFindGenericPassword(CFTypeRef keychainOrArray,  UInt32 serviceNameLength, const char *serviceName, UInt32 accountNameLength, const char *accountName, UInt32 *passwordLength, void **passwordData, SecKeychainItemRef *itemRef);

#pragma mark ÑÑÑÑ Managing User Interaction ÑÑÑÑ
/*!
	@function SecKeychainSetUserInteractionAllowed
	@abstract Turns on or off any optional user interaction
	@param state A boolean representing the state of user interaction.  You should pass TRUE to allow user interaction, and FALSE to disallow user interaction
	@result A result code.  See "Security Error Codes" (SecBase.h).
*/
OSStatus SecKeychainSetUserInteractionAllowed(Boolean state);

/*!
	@function SecKeychainGetUserInteractionAllowed
	@abstract Retrieves the current state of user interaction.
	@param state On return, a pointer to the current state of user interaction.  If this is TRUE then user interaction is allowed, if it is FALSE, then user interaction is not allowed.
	@result A result code.  See "Security Error Codes" (SecBase.h).
*/
OSStatus SecKeychainGetUserInteractionAllowed(Boolean *state);

#pragma mark ÑÑÑÑ CSSM Bridge Functions ÑÑÑÑ
/*!
	@function SecKeychainGetCSPHandle
	@abstract Returns the CSSM_CSP_HANDLE attachment for the given keychain reference. The handle is valid until the keychain reference is released.
    @param keychain A keychain reference.
    @param cspHandle On return, a pointer to the CSSM_CSP_HANDLE for the given keychain.
    @result A result code.  See "Security Error Codes" (SecBase.h).
*/
OSStatus SecKeychainGetCSPHandle(SecKeychainRef keychain, CSSM_CSP_HANDLE *cspHandle);

/*!
	@function SecKeychainGetDLDBHandle
	@abstract Returns the CSSM_DL_DB_HANDLE for a given keychain reference. The handle is valid until the keychain reference is released.
    @param keychain A keychain reference.
    @param dldbHandle On return, a pointer to the CSSM_DL_DB_HANDLE for the given keychain.
    @result A result code.  See "Security Error Codes" (SecBase.h).
*/
OSStatus SecKeychainGetDLDBHandle(SecKeychainRef keychain, CSSM_DL_DB_HANDLE *dldbHandle);

#pragma mark ÑÑÑÑ Keychain Access Management ÑÑÑÑ
/*!
	@function SecKeychainCopyAccess
	@abstract Retrieves the access for a keychain. 
	@param keychain A reference to the keychain from which to copy the access.
    @param accessRef On return, a pointer to the access reference.
    @result A result code.  See "Security Error Codes" (SecBase.h).
*/
OSStatus SecKeychainCopyAccess(SecKeychainRef keychain, SecAccessRef *access);

/*!
	@function SecKeychainSetAccess
	@abstract Sets the access for a keychain.
    @param keychain A reference to the keychain for which to set the access.
    @param accessRef An access reference.
    @result A result code.  See "Security Error Codes" (SecBase.h).
*/
OSStatus SecKeychainSetAccess(SecKeychainRef keychain, SecAccessRef access);

#if defined(__cplusplus)
}
#endif

#endif /* !_SECURITY_SECKEYCHAIN_H_ */
