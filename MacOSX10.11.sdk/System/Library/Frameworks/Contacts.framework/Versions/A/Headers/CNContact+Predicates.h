//
//  CNContact+Predicates.h
//  Contacts
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
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

/*! To fetch contacts matching contact identifiers. */
+ (NSPredicate *)predicateForContactsWithIdentifiers:(NSArray<NSString*> *)identifiers;

+ (NSPredicate *)predicateForContactsInGroupWithIdentifier:(NSString *)groupIdentifier;

+ (NSPredicate *)predicateForContactsInContainerWithIdentifier:(NSString *)containerIdentifier;

@end

NS_ASSUME_NONNULL_END
