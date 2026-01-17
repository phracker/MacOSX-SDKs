//
//  CNSaveRequest.h
//  Contacts
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class CNContact, CNMutableContact, CNGroup, CNMutableGroup;


/*!
 * @abstract Specifies the changes to save.
 *
 * @discussion Create a new save request for each save execution on the contact store. Can have many changes batched into one save request. Do not access objects in the save request when it is executing.  A save request only applies the changes to the objects. If there are overlapping changes with multiple, concurrent CNSaveRequests then the last saved change wins.
 *
 * If adding an object (contact, group, container) and it is already in the contact store then the executing save request will fail to add that object and will return the error CNErrorCodeInsertedRecordAlreadyExists with CNErrorUserInfoAffectedRecordsKey value as an array containing that object.
 *
 * If updating/deleting an object (contact, group, container) and it is not in the contact store then the executing save request will fail to update/delete that object and will return the error CNErrorCodeRecordDoesNotExist with CNErrorUserInfoAffectedRecordsKey value as an array containing that object.
 *
 */
API_AVAILABLE(macos(10.11), ios(9)) __WATCHOS_PROHIBITED
@interface CNSaveRequest : NSObject

/*!
 * @abstract Add a new contact to the contact store.
 *
 * @discussion The contact may be modified by the executing save request. If the contact was previously specified to be deleted in the save request that will no longer occur.
 *
 * @param contact The new contact to add.
 * @param identifier The container identifier to add the new contact to. Set to nil for the default container.
 */
- (void)addContact:(CNMutableContact *)contact toContainerWithIdentifier:(nullable NSString *)identifier;

/*!
 * @abstract Update an existing contact in the contact store.
 *
 * @discussion The contact must already exist in the contact store. The contact may be modified by the executing save request.
 */
- (void)updateContact:(CNMutableContact *)contact;

/*!
 * @abstract Delete a contact from the contact store.
 *
 * @discussion If the contact was previously specified to be added in the save request that will no longer occur.
 */
- (void)deleteContact:(CNMutableContact *)contact;

/*!
 * @abstract Add a new group to the contact store.
 *
 * @discussion If the group was previously specified to be deleted in the save request that will no longer occur.
 *
 * @param group The new group to add.
 * @param identifier The container identifier to add the new group to. Set to nil for the default container.
 */
- (void)addGroup:(CNMutableGroup *)group toContainerWithIdentifier:(nullable NSString *)identifier;

/*!
 * @abstract Update an existing group in the contact store.
 *
 * @discussion The group must already exist in the contact store.
 */
- (void)updateGroup:(CNMutableGroup *)group;

/*!
 * @abstract Delete a group from the contact store.
 *
 * @discussion The contacts in the group are not deleted. If the group was previously specified to be added in the save request that will no longer occur.
 */
- (void)deleteGroup:(CNMutableGroup *)group;

/*!
 * @abstract Add a new subgroup to a group.
 *
 * @discussion If the subgroup was previously specified to be deleted in the save request that will no longer occur.
 *
 * @param subgroup The new group to add.
 * @param group The group to add the subgroup to.
 */
- (void)addSubgroup:(CNGroup *)subgroup toGroup:(CNGroup *)group API_AVAILABLE(macos(10.11)) API_UNAVAILABLE(ios);

/*!
 * @abstract Remove a subgroup from a group.
 *
 * @discussion The contacts in the subgroup's membership are not affected. If the subgroup was previously specified to be added in the save request that will no longer occur.
 *
 * @param subgroup The new group to add.
 * @param group The group to add the subgroup to.
 */
- (void)removeSubgroup:(CNGroup *)subgroup fromGroup:(CNGroup *)group API_AVAILABLE(macos(10.11)) API_UNAVAILABLE(ios);

/*!
 * @abstract Add a new member to a group.
 *
 * @discussion If the membership was previously specified to be deleted in the save request that will no longer occur.
 *
 * @param contact The new member to add to the group.
 * @param group The group to add the member to.
 */
- (void)addMember:(CNContact *)contact toGroup:(CNGroup *)group;

/*!
 * @abstract Remove a member from a group.
 *
 * @discussion The contact is not deleted. It is only removed as a member of the group. If the membership was previously specified to be added in the save request that will no longer occur.
 *
 * @param contact The member to remove from the group.
 * @param group The group to remove the member from.
 */
- (void)removeMember:(CNContact *)contact fromGroup:(CNGroup *)group;

/*!
 * @abstract    The author of this transaction.
 *
 * @discussion  Use this, in conjunction with @c CNChangeHistoryFetchRequest.excludedTransactionAuthors,
 *              to suppress fetching of changes the author already knows about.
 */
@property (copy, nonatomic, nullable) NSString *transactionAuthor API_AVAILABLE(macos(12), ios(15));

/*!
 * @abstract    Should the contacts be refetched as part of executing the save request.
 *
 * @discussion  Default is `YES` where added and updated contacts are refetched by the executing save request.
 *              Set to `NO` to suppress this refetch behavior and reduce the execution time of the save request.
 *
 * @note        If set to `NO` do not use the contacts after the executed save request as they may not be in a current state.
 */
@property (assign, nonatomic) BOOL shouldRefetchContacts API_AVAILABLE(macos(12.3), ios(15.4));

@end

NS_ASSUME_NONNULL_END
