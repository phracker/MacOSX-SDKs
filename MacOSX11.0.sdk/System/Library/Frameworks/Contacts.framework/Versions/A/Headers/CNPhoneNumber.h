//
//  CNPhoneNumber.h
//  Contacts
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Contacts/ContactsDefines.h>

NS_ASSUME_NONNULL_BEGIN


/*!
 * @abstract An immutable value object representing a phone number.
 *
 * @discussion CNPhoneNumber is thread safe.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface CNPhoneNumber : NSObject <NSCopying, NSSecureCoding>

/*! These will return nil if the stringValue is nil. */
+ (nullable instancetype)phoneNumberWithStringValue:(NSString *)stringValue;
- (nullable instancetype)initWithStringValue:(NSString *)string;

- (null_unspecified instancetype)init NS_DEPRECATED(10_11, 10_13, 9_0, 11_0, "Use initWithStringValue:");
+ (null_unspecified instancetype)new  NS_DEPRECATED(10_11, 10_13, 9_0, 11_0, "Use phoneNumberWithStringValue:");

@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *stringValue;

@end


// Phone number labels
CONTACTS_EXTERN NSString * const CNLabelPhoneNumberiPhone                NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNLabelPhoneNumberMobile                NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNLabelPhoneNumberMain                  NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNLabelPhoneNumberHomeFax               NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNLabelPhoneNumberWorkFax               NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNLabelPhoneNumberOtherFax              NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNLabelPhoneNumberPager                 NS_AVAILABLE(10_11, 9_0);

NS_ASSUME_NONNULL_END
