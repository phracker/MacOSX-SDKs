//
//  CNContact+Predicates.h
//  Contacts
//
//  Copyright (c) 2015–2018 Apple Inc. All rights reserved.
//

#import <Contacts/CNContact.h>

NS_ASSUME_NONNULL_BEGIN


/*!
 * @abstract The predicates to match contacts against.
 *
 * @discussion Can only use these predicates with CNContactStore and CNContactFetchRequest.
 */
@interface CNContact (Predicates)

/*!
 * @abstract To fetch contacts matching a name.
 *
 * @discussion The name can contain any number of words.
 */
+ (NSPredicate *)predicateForContactsMatchingName:(NSString *)name;

/*!
 * @abstract    Fetch contacts matching an email address.
 *
 * @discussion  Use this predicate to find the contact(s) which contain the specified
 *              email address. The search is not case-sensitive.
 *
 * @param       emailAddress
 *              The email address to search for. Do not include a scheme (e.g., "mailto:").
 */
+ (NSPredicate *)predicateForContactsMatchingEmailAddress:(NSString *)emailAddress API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0));

/*!
 * @abstract    Fetch contacts matching a phone number.
 *
 * @discussion  If the predicate and contact differ in their use or presence of country
 *              codes, a best effort will be made to match results; however, inexact
 *              matches are not guaranteed.
 *
 * @param       phoneNumber
 *              A @c CNPhoneNumber representing the phone number to search for.
 *              Do not include a scheme (e.g., "tel:").
 */
+ (NSPredicate *)predicateForContactsMatchingPhoneNumber:(CNPhoneNumber *)phoneNumber API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0));

/*! To fetch contacts matching contact identifiers. */
+ (NSPredicate *)predicateForContactsWithIdentifiers:(NSArray<NSString*> *)identifiers;

+ (NSPredicate *)predicateForContactsInGroupWithIdentifier:(NSString *)groupIdentifier;

+ (NSPredicate *)predicateForContactsInContainerWithIdentifier:(NSString *)containerIdentifier;

@end

NS_ASSUME_NONNULL_END
