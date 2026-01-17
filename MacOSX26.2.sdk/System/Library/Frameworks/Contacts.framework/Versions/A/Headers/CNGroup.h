//
//  CNGroup.h
//  Contacts
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Contacts/ContactsDefines.h>

NS_ASSUME_NONNULL_BEGIN


/*!
 * @abstract An immutable value object representing a group.
 *
 * @discussion CNGroup is thread safe.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface CNGroup : NSObject <NSCopying, NSMutableCopying, NSSecureCoding>

/*! The identifier is unique among groups on the device. It can be saved and used for fetching groups next application launch. */
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *identifier;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *name;

@end


// Properties that are always fetched. Can be used with key value coding and observing.
CONTACTS_EXTERN NSString * const CNGroupIdentifierKey	NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNGroupNameKey			NS_AVAILABLE(10_11, 9_0);

NS_ASSUME_NONNULL_END
