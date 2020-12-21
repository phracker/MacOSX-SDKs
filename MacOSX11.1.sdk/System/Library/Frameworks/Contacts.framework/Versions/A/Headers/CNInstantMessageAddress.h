//
//  CNInstantMessageAddress.h
//  Contacts
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Contacts/ContactsDefines.h>

NS_ASSUME_NONNULL_BEGIN


/*!
 * @abstract An immutable value object representing an instant message address.
 *
 * @discussion CNInstantMessageAddress is thread safe.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface CNInstantMessageAddress : NSObject <NSCopying, NSSecureCoding>

@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *username;
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *service;

- (instancetype)initWithUsername:(NSString *)username service:(NSString *)service;

/*! Returns a user displayable property name. */
+ (NSString *)localizedStringForKey:(NSString *)key;

/*! Returns a user displayable service name. */
+ (NSString *)localizedStringForService:(NSString *)service;

@end


// Properties that are always fetched. Can be used with key value coding and observing.
CONTACTS_EXTERN NSString * const CNInstantMessageAddressUsernameKey          NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNInstantMessageAddressServiceKey           NS_AVAILABLE(10_11, 9_0);

// Instant message services.
CONTACTS_EXTERN NSString * const CNInstantMessageServiceAIM                  NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNInstantMessageServiceFacebook             NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNInstantMessageServiceGaduGadu             NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNInstantMessageServiceGoogleTalk           NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNInstantMessageServiceICQ                  NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNInstantMessageServiceJabber               NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNInstantMessageServiceMSN                  NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNInstantMessageServiceQQ                   NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNInstantMessageServiceSkype                NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNInstantMessageServiceYahoo                NS_AVAILABLE(10_11, 9_0);

NS_ASSUME_NONNULL_END
