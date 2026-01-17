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
	uintptr_t _flags;
	void* _reserved1;
}

// Default initializer.
- (instancetype)initWithInsertedObjects:(NSSet*)insertedObjects updatedObjects:(NSSet*)updatedObjects deletedObjects:(NSSet*)deletedObjects lockedObjects:(NSSet*)lockedObjects;

// Objects that were inserted into the calling context.
@property (readonly, strong) NSSet *insertedObjects;
// Objects that were modified in the calling context.
@property (readonly, strong) NSSet *updatedObjects;
// Objects that were deleted from the calling context.
@property (readonly, strong) NSSet *deletedObjects;
// Objects that were flagged for optimistic locking on the calling context via detectConflictsForObject:.
@property (readonly, strong) NSSet *lockedObjects;

@end
