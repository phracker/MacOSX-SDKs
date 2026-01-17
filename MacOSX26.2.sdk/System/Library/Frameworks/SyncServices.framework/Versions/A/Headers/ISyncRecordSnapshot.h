/*
 * SyncServices -- ISyncRecordSnapshot.h
 * Copyright (c) 2004, Apple Computer, Inc.  All rights reserved.
 */

#import <Foundation/Foundation.h>


@interface ISyncRecordSnapshot : NSObject

/* Grab a set of records from the snap shot.  The key is the record id and the value is the record
   dictionary.  Deleted records and invalid record ids are not present - meaning there is no way to
   distinguish between the two. */
- (NSDictionary *)recordsWithIdentifiers:(NSArray /* NSString */ *)recordIds NS_DEPRECATED_MAC(10_4, 10_7);

/* Get the ids of the records which are the targets of a relationship on some record.  If the
   relationship is weakly or strongly ordered, the order of the ids in the array is the ordering of the
   objects in the relationship.  A record id may appear in the array multiple times.  If the
   relationship is a to-one relationship, there will only ever be one record id in the array. */
- (NSArray *)targetIdentifiersForRelationshipName:(NSString *)relationshipName withSourceIdentifier:(NSString *)sourceId NS_DEPRECATED_MAC(10_4, 10_7);

/* Get the ids of all records which have some record as a target of a relationship.  The ordering of
   the ids is irrelevant.  No record ids will be repeated in the array. */
- (NSArray *)sourceIdentifiersForRelationshipName:(NSString *)relationshipName withTargetIdentifier:(NSString *)sourceId NS_DEPRECATED_MAC(10_4, 10_7);

- (NSDictionary *)recordsWithMatchingAttributes:(NSDictionary *)attributes NS_DEPRECATED_MAC(10_4, 10_7);

@end


@class ISyncRecordReference;

@interface ISyncRecordSnapshot (ISyncRecordReference)
/* Get an ISyncRecordReference for a global identifier. The Snapshot can be scoped to any client,
   or global. The identifier must be in the record id scope of the Snapshot. */
- (ISyncRecordReference *) recordReferenceForRecordWithIdentifier:(NSString *)identifier NS_DEPRECATED_MAC(10_4, 10_7);

/* Get a record identifier in the Snapshot's scope for the reference. The Snapshot can be scoped to any
   client, or global. If pModified is non-nil, pModified is set to YES if any data internal to the
   ISyncRecordRefence has changed and set to NO if not. 

   Note that self will have mutated if *pModified == YES.  The Client should store the new reference
   in its configuration for subsequent use. */
- (NSString *) recordIdentifierForReference:(ISyncRecordReference *)reference isModified:(BOOL *)pModified NS_DEPRECATED_MAC(10_4, 10_7);
@end

