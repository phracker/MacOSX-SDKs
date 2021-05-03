//
//  CNGroup+Predicates.h
//  Contacts
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Contacts/CNGroup.h>

NS_ASSUME_NONNULL_BEGIN


/*!
 * @abstract The predicates to match groups against.
 *
 * @discussion Can only use these predicates with CNContactStore.
 */
@interface CNGroup (Predicates)

+ (NSPredicate *)predicateForGroupsWithIdentifiers:(NSArray<NSString*> *)identifiers;

+ (NSPredicate *)predicateForSubgroupsInGroupWithIdentifier:(NSString *)parentGroupIdentifier NS_AVAILABLE(10_11, NA);

+ (NSPredicate *)predicateForGroupsInContainerWithIdentifier:(NSString *)containerIdentifier;

@end

NS_ASSUME_NONNULL_END
