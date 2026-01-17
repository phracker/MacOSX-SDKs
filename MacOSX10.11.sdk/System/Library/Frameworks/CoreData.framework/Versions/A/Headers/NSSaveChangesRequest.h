/*
 NSSaveChangesRequest.h
 Core Data
 Copyright (c) 2004-2015, Apple Inc.
 All rights reserved.
 */

#import <Foundation/NSArray.h>
#import <Foundation/NSSet.h>
#import <CoreData/NSPersistentStoreRequest.h>

NS_ASSUME_NONNULL_BEGIN

@class NSPersistentStoreRequest;
@class NSManagedObject;

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
- (instancetype)initWithInsertedObjects:(nullable NSSet<NSManagedObject *> *)insertedObjects updatedObjects:(nullable NSSet<NSManagedObject *> *)updatedObjects deletedObjects:(nullable NSSet<NSManagedObject *> *)deletedObjects lockedObjects:(nullable NSSet<NSManagedObject *> *)lockedObjects;

// Objects that were inserted into the calling context.
@property (nullable, readonly, strong) NSSet<__kindof NSManagedObject *> *insertedObjects;
// Objects that were modified in the calling context.
@property (nullable, readonly, strong) NSSet<__kindof NSManagedObject *> *updatedObjects;
// Objects that were deleted from the calling context.
@property (nullable, readonly, strong) NSSet<__kindof NSManagedObject *> *deletedObjects;
// Objects that were flagged for optimistic locking on the calling context via detectConflictsForObject:.
@property (nullable, readonly, strong) NSSet<__kindof NSManagedObject *> *lockedObjects;

@end

NS_ASSUME_NONNULL_END
