//
//  IMService.h
//
//  Copyright (c) 2001 Apple Computer, Inc. All rights reserved.
//

/*! @header
 @discussion The IMService API provides a way to integrate a variety of data about a user's iChat connections into your
 application. It provides information on which services the user is connected to (AIM, Jabber, or Bonjour), their online
 screen names, their lists of acquaintances, their current status on a given service (away, idle, available), idle
 times, and other presence-specific details. The API also provides notifications to update your applications when
 a user's status, information, status images, or service connections have changed.
 
 A variety of status notifications related to the user's status and preferences are posted by the 
 IMService custom notification center. See "Notifications" for more information. 
 */

#ifndef _IMSERVICE_H_
#define _IMSERVICE_H_

#import <Foundation/Foundation.h>

@class ABPerson;

// Notifications for which clients can register
/*! @group Notifications */

/*! Received from IMService's custom notification center. Posted when the user logs in, logs off, goes away, and so on. 
 This notification is for the IMService object. The user information dictionary will not contain keys. The client 
 should call <tt>status</tt> to get the new status. */
extern NSString * const IMServiceStatusChangedNotification;

/*! Received from IMService's custom notification center. Posted when the local user changes online status.
 This notification is relevant to no particular object. The user information dictionary will not contain keys. 
 The client should call <tt>myStatus</tt> to get the new status. */
extern NSString * const IMMyStatusChangedNotification;

/*! Received from IMService's custom notification center. Posted when a different user (screenName) logs in, logs off, goes away, 
 and so on. This notification is for the IMService object. The user information dictionary will always contain an 
 IMPersonScreenNameKey and an IMPersonStatusKey, and no others. */
extern NSString * const IMPersonStatusChangedNotification;

/*! Received from IMService's custom notification center. Posted when a screenName changes some aspect of their published information. 
 This notification is for the IMService object. The user information dictionary will always contain an IMPersonScreenNameKey and may 
 contain any of the following keys as described by "Dictionary Keys" in this document: <tt>IMPersonStatusMessageKey, IMPersonIdleSinceKey, 
 IMPersonFirstNameKey, IMPersonLastNameKey, IMPersonEmailKey, IMPersonPictureDataKey, IMPersonAVBusyKey, IMPersonCapabilitiesKey</tt>.
 If a particular attribute has been removed, the value for the relevant key will be NSNull.*/
extern NSString * const IMPersonInfoChangedNotification;

/*! Received from IMService's custom notification center. Posted when the user changes their preferred images for displaying status. 
 This notification is relevant to no particular object. The user information dictionary will not contain keys. Clients that display 
 status information graphically (using the green/yellow/red dots) should call <tt>imageURLForStatus:</tt> to get the new image. 
 See "Class Methods" for IMService in this document. */
extern NSString * const IMStatusImagesChangedAppearanceNotification;

/*! @group Status States */

/*! Status states for the service (accessed using the <tt>status:</tt> instance method). <tt>IMServiceStatusDisconnected</tt> indicates the user
 was disconnected by the server, not by the user. */
enum {
    IMServiceStatusLoggedOut,
    IMServiceStatusDisconnected,     
    IMServiceStatusLoggingOut,
    IMServiceStatusLoggingIn,
    IMServiceStatusLoggedIn
};
typedef NSUInteger IMServiceStatus;

/*! Online status states for a person (accessed using the <tt>IMPersonStatus</tt> key) */
enum {
    IMPersonStatusUnknown,
    IMPersonStatusOffline,
    IMPersonStatusIdle,
    IMPersonStatusAway,
    IMPersonStatusAvailable,
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
    IMPersonStatusNoStatus
#endif
};
typedef NSUInteger IMPersonStatus;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
/*! Compare two IMPersonStatus values to determine which one has a higher availablity.
 You should always use this function when comparing status values. */
NSComparisonResult IMComparePersonStatus( IMPersonStatus status, IMPersonStatus compareTo );
#endif

// Keys for the notifications
/*! @group Dictionary Keys */
/*! Name of the service this person belongs to */
extern NSString* IMPersonServiceNameKey;
/*! Service-specific identifier for a person. Examples include "User123" or "steve&#64mac.com" for AIM, or "John Doe" for Bonjour. */
extern NSString* IMPersonScreenNameKey;
/*! NSNumber of IMPersonStatus, current online state, if known */
extern NSString* IMPersonStatusKey;
/*! Current status message */
extern NSString* IMPersonStatusMessageKey;
/*! NSDate of the time, in seconds, since the last user activity. Available if the user's status is idle. */
extern NSString* IMPersonIdleSinceKey;
/*! Person's first name. This is a key used directly by Bonjour; however, if a person has an Address Book entry associated with a
 relevant AIM account, this key will reflect the first name of that person. */
extern NSString* IMPersonFirstNameKey;
/*! Person's last name. This is a key used directly by Bonjour; however, if a person has an Address Book entry associated with a
 relevant AIM account, this key will reflect the last name of that person. */
extern NSString* IMPersonLastNameKey;
/*! Person's e-mail address. This is a key used directly by Bonjour; however, if a person has an Address Book entry associated with a
 relevant AIM account, this key will reflect the first e-mail address of that person. */
extern NSString* IMPersonEmailKey;
/*! NSData of the image that should be used for the user's icon. Sent with the IMPersonInfoChangedNotification. */
extern NSString* IMPersonPictureDataKey;
/*! NSNumber, 0 for audio/video available, 1 for audio/video busy */
extern NSString* IMPersonAVBusyKey;      
/*! NSArray of capabilities. See "Capabilities" in this document. */
extern NSString* IMPersonCapabilitiesKey;

/*! @group Capabilities */

/*! Text capability */
extern NSString * const IMCapabilityText;
/*! Direct connect capability */
extern NSString * const IMCapabilityDirectIM;
/*! File transfer capability */
extern NSString * const IMCapabilityFileTransfer;
/*! File sharing capability */
extern NSString * const IMCapabilityFileSharing;
/*! Audio chat capability */
extern NSString * const IMCapabilityAudioConference;
/*! Video chat capability */
extern NSString * const IMCapabilityVideoConference;

/*! @class IMService
 @abstract An IMService object represents a service available to a user through iChat, such as AIM, Jabber, and Bonjour.
 @discussion Each IMService object represents one service available through iChat. Class methods such as <tt>allServices</tt>
 and <tt>serviceWithName:</tt> will return these objects. Each object acts as the liaison to its single service,
 allowing you to access the individual user's global status, the user's list of acquaintances, and other information
 which can be integrated into your application. 
 
 A variety of status notifications related to the user's status and preferences are posted by the 
 IMService custom notification center. See the documentation for the full IMService.h header file
 for more information. 
 */
@interface IMService : NSObject { }

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
/*! 
 @method imageNameForStatus   
 @abstract Returns the name of the image corresponding to the IMPersonStatus specified by <i>status</i>. This image reflects the 
 status of the user, and is usually reflected by a colored bubble or triangle.
 @param status  An NSNumber from IMPersonStatus.
 @result  Returns an NSString with the name of an image suitable for passing to +[NSImage imageNamed:]
 */
+ (NSString *)imageNameForStatus:(IMPersonStatus)status;
#endif

/*! 
 @method allServices
 @abstract Returns the list of services currently available to the user, regardless of their status.
 @result Returns an NSArray of IMService objects corresponding to the current available services (AIM, Bonjour, Jabber, and so on.)
 */
+ (NSArray *)allServices;
/*! 
 @method serviceWithName
 @abstract Returns only the service specified by a given name. 
 @param name  An NSString containing a service name as returned by a previous call to <tt>name</tt>.
 Hard-coding the service names internally is not recommended.
 @result Returns an IMService object corresponding to the available service specified by <i>name</i>.
 */
+ (IMService *)serviceWithName:(NSString *)name;
/*! 
 @method notificationCenter   
 @abstract Returns the custom notification center for the Instant Messaging service. Manages the notifications
 specified by the Notifications list in this document.
 @result Returns an NSNotificationCenter object of the custom IMService notification center, not the default
 notification center.
 */
+ (NSNotificationCenter *)notificationCenter;
/*! 
 @method myStatus  
 @abstract Class method to return the status of the currently active user. This status is global across all services.
 @result Returns the appropriate IMPersonStatus.
 */
+ (IMPersonStatus)myStatus;
/*! 
 @method myIdleTime   
 @abstract Class method to return the idle time of the active user.
 @result Returns a NSDate, in seconds, of time since the currently active user went idle.
 */
+ (NSDate*)myIdleTime;

/*! 
 @method localizedName  
 @abstract Returns the user-visible localized name of the service.
 @result  Returns a NSString. Will contain the localized service name, such as "AOL Instant Messenger", "Jabber", or "Bonjour", 
 for example. This string will be localized if required.
 */
- (NSString *)localizedName;
/*! 
 @method localizedShortName   
 @abstract Returns a shorter version, if available, of the user-visible localized name of the service.
 @result Returns a NSString. Will return a localized string if required.
 */
- (NSString *)localizedShortName;
/*! 
 @method name   
 @abstract Returns the fixed canonical name of the service. 
 @result Returns a NSString. This string is not localized.
 */
- (NSString*)name; 
/*! 
 @method status   
 @abstract Returns the login status of the service. 
 @result Returns the appropriate IMServiceStatus number. See IMServiceStatus under "Status States" in this document.
 */
- (IMServiceStatus)status;

/*! 
 @method infoForScreenName   
 @abstract Returns information about the person specified by his/her <i>screenName</i>.
 @param screenName  An NSString containing the screen name identifier of a person. 
 @result Returns an NSDictionary with content specified by the Dictionary Keys. See "Dictionary Keys" in this document.
 */
- (NSDictionary *)infoForScreenName: (NSString*)screenName; 
/*! 
 @method infoForAllScreenNames   
 @abstract Returns information about all people and all accounts currently logged in to the service. If a person is
 logged in on multiple accounts (determined by the user's Address Book), this method will return the information for
 all of the logged-in accounts.
 @result Returns an NSArray of the dictionaries returned by <tt>infoForScreenName:</tt> for all people on all accounts. 
 */
- (NSArray *)infoForAllScreenNames;
/*! 
 @method infoForPreferredScreenNames   
 @abstract Returns information about all people and their primary accounts currently logged in to the service. If a person is
 logged in on multiple accounts (determined by the user's Address Book), this method will only return the information for the
 preferred account. The preferred account is determined by iChat, using a combination of capabilities (video chat capability, audio chat
 capability, and so on), status (available, idle, away), and other user attributes.
 @result  Returns an NSArray of the dictionaries returned by <tt>infoForScreenName:</tt> for all people and is guaranteed to provide only one
 array entry for any logged-in person. 
 */
- (NSArray *)infoForPreferredScreenNames;
/*! 
 @method peopleWithScreenName   
 @abstract Returns the Address Book person objects that correspond to the person with the screenName matched by <i>screenName</i>.
 @param screenName  An NSString containing the screen name identifier of a person or persons.
 @result Returns an NSArray of ABPerson objects that match the screen name matched by <i>screenName</i>. Can return an empty array or an array with one or more items.
 */
- (NSArray *)peopleWithScreenName:(NSString *)screenName;
/*! 
 @method screenNamesForPerson   
 @abstract Returns a list of valid screen names for any given person.
 @param person An Address Book ABPerson object.
 @result Returns an NSArray of NSStrings that are valid screen names for the person specified by <i>person</i>. See Address Book documentation for 
 more information on ABPerson and accessing the user's address book. Can return an empty array or an array with one or more items.
 */
- (NSArray *)screenNamesForPerson:(ABPerson *)person;

@end

@interface IMService (NSDeprecatedMethods)
/*! DEPRECATED in 10.5 or newer, please use imageNameForStatus, and [NSImage imageNamed: name]
 @method imageURLForStatus   
 @abstract Returns the URL of the image corresponding to the IMPersonStatus specified by <i>status</i>. This image reflects the 
 status of the user, and is usually reflected by a colored bubble or triangle.
 @param status  An NSNumber from IMPersonStatus.
 @result  Returns the newly initialized NSURL object with a URL to the image.
 */
+ (NSURL *)imageURLForStatus:(IMPersonStatus)status AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;
@end

#endif