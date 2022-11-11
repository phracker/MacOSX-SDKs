//
//  CNContainer+Predicates.h
//  Contacts
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Contacts/CNContainer.h>

NS_ASSUME_NONNULL_BEGIN


/*!
 * @abstract The predicates to match containers against.
 *
 * @discussion Can only use these predicates with CNContactStore.
 */
@interface CNContainer (Predicates)

+ (NSPredicate *)predicateForContainersWithIdentifiers:(NSArray<NSString*> *)identifiers;

/*! @discussion If the identifier is for a unified contact then the fetch will return an empty array. To fetch the containers of a unified contact, first fetch the linked contacts then fetch the container of each linked contact. */
+ (NSPredicate *)predicateForContainerOfContactWithIdentifier:(NSString *)contactIdentifier;

+ (NSPredicate *)predicateForContainerOfGroupWithIdentifier:(NSString *)groupIdentifier;

@end

NS_ASSUME_NONNULL_END
