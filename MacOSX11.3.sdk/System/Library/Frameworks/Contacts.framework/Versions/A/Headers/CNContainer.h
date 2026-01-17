//
//  CNContainer.h
//  Contacts
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Contacts/ContactsDefines.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, CNContainerType)
{
    CNContainerTypeUnassigned = 0,
    CNContainerTypeLocal,
    CNContainerTypeExchange,
    CNContainerTypeCardDAV
} NS_ENUM_AVAILABLE(10_11, 9_0);


/*!
 * @abstract An immutable value object representing a container.
 *
 * @discussion CNContainer is thread safe.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface CNContainer : NSObject <NSCopying, NSSecureCoding>

/*! The identifier is unique among containers on the device. It can be saved and used for fetching containers next application launch. */
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *identifier;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *name;
@property (readonly, NS_NONATOMIC_IOSONLY) CNContainerType type;

@end


// Properties that are always fetched. Can be used with key value coding and observing.
CONTACTS_EXTERN NSString * const CNContainerIdentifierKey	NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContainerNameKey			NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContainerTypeKey			NS_AVAILABLE(10_11, 9_0);

NS_ASSUME_NONNULL_END
