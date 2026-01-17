/*
 NSSaveChangesRequest.h
 Core Data
 Copyright (c) 2004-2012 Apple Inc.
 All rights reserved.
 */

#import <Foundation/NSSet.h>
#import <CoreData/NSPersistentStoreRequest.h>

@class NSPersistentStoreRequest;

NS_CLASS_AVAILABLE(10_7,5_0)
@interface NSSaveChangesRequest : NSPersistentStoreRequest {
@private
    NSSet *_insertedObjects;
    NSSet *_updatedObjects;
    NSSet *_deletedObjects;
    NSSet* _optimisticallyLockedObjects;
	void* _reserved1;
	void* _reserved2;
}

// Default initializer.
- (id)initWithInsertedObjects:(NSSet*)insertedObjects updatedObjects:(NSSet*)updatedObjects deletedObjects:(NSSet*)deletedObjects lockedObjects:(NSSet*)lockedObjects;

// Objects that were inserted into the calling context.
- (NSSet *)insertedObjects;
// Objects that were modified in the calling context.
- (NSSet *)updatedObjects;
// Objects that were deleted from the calling context.
- (NSSet *)deletedObjects;
// Objects that were flagged for optimistic locking on the calling context via detectConflictsForObject:.
- (NSSet *)lockedObjects;

@end
