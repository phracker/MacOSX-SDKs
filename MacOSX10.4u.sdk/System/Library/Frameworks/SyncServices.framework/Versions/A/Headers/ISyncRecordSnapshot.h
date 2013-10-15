/*
 * SyncServices -- ISyncRecordSnapshot.h
 * Copyright (c) 2004, Apple Computer, Inc.  All rights reserved.
 */

#import <Foundation/Foundation.h>


@interface ISyncRecordSnapshot : NSObject

/* Grab a set of records from the snap shot.  The key is the record id and the value is the record
   dictionary.  Deleted records and invalid record ids are not present - meaning there is no way to
   distinguish between the two. */
- (NSDictionary *)recordsWithIdentifiers:(NSArray /* NSString */ *)recordIds;

/* Get the ids of the records which are the targets of a relationship on some record.  If the
   relationship is weakly or strongly ordered, the order of the ids in the array is the ordering of the
   objects in the relationship.  A record id may appear in the array multiple times.  If the
   relationship is a to-one relationship, there will only ever be one record id in the array. */
- (NSArray *)targetIdentifiersForRelationshipName:(NSString *)relationshipName withSourceIdentifier:(NSString *)sourceId;

/* Get the ids of all records which have some record as a target of a relationship.  The ordering of
   the ids is irrelevant.  No record ids will be repeated in the array. */
- (NSArray *)sourceIdentifiersForRelationshipName:(NSString *)relationshipName withTargetIdentifier:(NSString *)sourceId;

- (NSDictionary *)recordsWithMatchingAttributes:(NSDictionary *)attributes;

@end
