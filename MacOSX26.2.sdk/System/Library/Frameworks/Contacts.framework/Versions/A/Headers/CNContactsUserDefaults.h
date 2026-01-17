//
//  CNContactUserDefaults.h
//  Contacts
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Contacts/CNContactFetchRequest.h>

NS_ASSUME_NONNULL_BEGIN


/*!
 * @abstract The user defaults for contacts.
 *
 * @note This class is not thread safe.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface CNContactsUserDefaults : NSObject

+ (instancetype)sharedDefaults;

@property (readonly, NS_NONATOMIC_IOSONLY) CNContactSortOrder sortOrder;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *countryCode;

@end

NS_ASSUME_NONNULL_END
