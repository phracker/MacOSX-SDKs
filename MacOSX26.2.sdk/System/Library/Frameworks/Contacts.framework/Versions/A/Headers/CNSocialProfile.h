//
//  CNSocialProfile.h
//  Contacts
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Contacts/ContactsDefines.h>

NS_ASSUME_NONNULL_BEGIN


/*!
 * @abstract An immutable value object representing a social profile.
 *
 * @discussion CNSocialProfile is thread safe.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface CNSocialProfile : NSObject <NSCopying, NSSecureCoding>

@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *urlString;
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *username;
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *userIdentifier;
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *service;

- (instancetype)initWithUrlString:(nullable NSString *)urlString username:(nullable NSString *)username userIdentifier:(nullable NSString *)userIdentifier service:(nullable NSString *)service;

/*! Returns a user displayable property name. */
+ (NSString *)localizedStringForKey:(NSString *)key;

/*! Returns a user displayable service name. */
+ (NSString* )localizedStringForService:(NSString *)service;

@end


// Properties that are always fetched. Can be used with key value coding and observing.
CONTACTS_EXTERN NSString * const CNSocialProfileURLStringKey                     NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNSocialProfileUsernameKey                      NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNSocialProfileUserIdentifierKey                NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNSocialProfileServiceKey                       NS_AVAILABLE(10_11, 9_0);

// Social profile services.
CONTACTS_EXTERN NSString * const CNSocialProfileServiceFacebook                  NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNSocialProfileServiceFlickr                    NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNSocialProfileServiceLinkedIn                  NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNSocialProfileServiceMySpace                   NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNSocialProfileServiceSinaWeibo                 NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNSocialProfileServiceTencentWeibo              NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNSocialProfileServiceTwitter                   NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNSocialProfileServiceYelp                      NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNSocialProfileServiceGameCenter                NS_AVAILABLE(10_11, 9_0);

NS_ASSUME_NONNULL_END
