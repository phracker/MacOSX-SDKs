/*
 *  ABGroup.h
 *  AddressBook
 *
 *  Copyright (c) 2010-2015 Apple Inc. All rights reserved.
 *
 *  An ABGroup is a non-ordered collection of records.
 *
 */

#ifndef __ABGroup__
#define __ABGroup__

#include <AddressBook/AddressBookDefines.h>
#include <AddressBook/ABAddressBook.h>
#include <AddressBook/ABRecord.h>
#include <AddressBook/ABPerson.h>
#include <AddressBook/ABSource.h>

AB_EXTERN const int kABGroupNameProperty AB_DEPRECATED("use CNGroup.name");

// ABGroupCreate creates a new group in the default source
AB_EXTERN ABRecordRef ABGroupCreate(void) AB_DEPRECATED("use [[CNMutableGroup alloc] init]");
AB_EXTERN ABRecordRef ABGroupCreateInSource(ABRecordRef source) AB_DEPRECATED("use [[CNMutableGroup alloc] init] and [CNSaveRequest addGroup:toContainerWithIdentifier:]");

AB_EXTERN ABRecordRef ABGroupCopySource(ABRecordRef group) AB_DEPRECATED("use [CNContactStore containersMatchingPredicate:[CNContainer predicateForContainerOfGroupWithIdentifier:] error:]");

AB_EXTERN CFArrayRef ABGroupCopyArrayOfAllMembers(ABRecordRef group) AB_DEPRECATED("use CNContactFetchRequest with predicate = [CNContact predicateForContactsInGroupWithIdentifier:]");
AB_EXTERN CFArrayRef ABGroupCopyArrayOfAllMembersWithSortOrdering(ABRecordRef group, ABPersonSortOrdering sortOrdering) AB_DEPRECATED("use CNContactFetchRequest with predicate = [CNContact predicateForContactsInGroupWithIdentifier:] and sortOrder");
AB_EXTERN bool ABGroupAddMember(ABRecordRef group, ABRecordRef person, CFErrorRef* error) AB_DEPRECATED("use [CNSaveRequest addMember:toGroup:]");
AB_EXTERN bool ABGroupRemoveMember(ABRecordRef group, ABRecordRef member, CFErrorRef* error) AB_DEPRECATED("use [CNSaveRequest removeMember:fromGroup:]");

// Finding groups
AB_EXTERN ABRecordRef ABAddressBookGetGroupWithRecordID(ABAddressBookRef addressBook, ABRecordID recordID) AB_DEPRECATED("use [CNContactStore groupsMatchingPredicate:[CNGroup predicateForGroupsWithIdentifiers:] error:]");
AB_EXTERN CFIndex ABAddressBookGetGroupCount(ABAddressBookRef addressBook) AB_DEPRECATED("use count of fetch results for [CNContactStore groupsMatchingPredicate:nil error:]");

AB_EXTERN CFArrayRef ABAddressBookCopyArrayOfAllGroups(ABAddressBookRef addressBook) AB_DEPRECATED("use [CNContactStore groupsMatchingPredicate:nil error:]");
AB_EXTERN CFArrayRef ABAddressBookCopyArrayOfAllGroupsInSource(ABAddressBookRef addressBook, ABRecordRef source) AB_DEPRECATED("use [CNContactStore groupsMatchingPredicate:[CNGroup predicateForGroupsInContainerWithIdentifier:] error:]");

#endif

