//
//  NSMergePolicy.h
//  Core Data
//  Copyright (c) 2004-2012 Apple Inc. All rights reserved.
//

#import <Foundation/NSArray.h>
#import <Foundation/NSError.h>
#import <CoreData/CoreDataDefines.h>

@class NSMergePolicy;
@class NSManagedObject;

// Default policy for all managed object contexts - save returns with an error that contains the object IDs of the objects that had conflicts(NSInsertedObjectsKey, NSUpdatedObjectsKey).
COREDATA_EXTERN id NSErrorMergePolicy NS_AVAILABLE(10_4, 3_0);

// This singleton policy merges conflicts between the persistent store's version of the object and the current in memory version. The merge occurs by individual property. For properties which have been changed in both the external source and in memory, the external changes trump the in memory ones.
COREDATA_EXTERN id NSMergeByPropertyStoreTrumpMergePolicy NS_AVAILABLE(10_4, 3_0);    

// This singleton policy merges conflicts between the persistent store's version of the object and the current in memory version. The merge occurs by individual property. For properties which have been changed in both the external source and in memory, the in memory changes trump the external ones.
COREDATA_EXTERN id NSMergeByPropertyObjectTrumpMergePolicy NS_AVAILABLE(10_4, 3_0);    

// This singleton policy overwrites all state for the changed objects in conflict The current object's state is pushed upon the persistent store.
COREDATA_EXTERN id NSOverwriteMergePolicy NS_AVAILABLE(10_4, 3_0);    

// This singleton policy discards all state for the changed objects in conflict. The persistent store's version of the object is used.
COREDATA_EXTERN id NSRollbackMergePolicy NS_AVAILABLE(10_4, 3_0);    


typedef NS_ENUM(NSUInteger, NSMergePolicyType) {
    NSErrorMergePolicyType                      = 0x00,
    NSMergeByPropertyStoreTrumpMergePolicyType	= 0x01,
    NSMergeByPropertyObjectTrumpMergePolicyType = 0x02,
    NSOverwriteMergePolicyType                  = 0x03,
    NSRollbackMergePolicyType                   = 0x04
};

NS_CLASS_AVAILABLE(10_7, 5_0)
@interface NSMergeConflict : NSObject {
@private
    id _source;
    id _snapshot1;
    id _snapshot2;
    id _snapshot3;
    NSUInteger _newVersion;
    NSUInteger _oldVersion;
}

@property (readonly, retain) NSManagedObject* sourceObject;
@property (readonly, retain) NSDictionary* objectSnapshot;
@property (readonly, retain) NSDictionary* cachedSnapshot;
@property (readonly, retain) NSDictionary* persistedSnapshot;
@property (readonly) NSUInteger newVersionNumber;
@property (readonly) NSUInteger oldVersionNumber;

/*
 * There are two situations in which a conflict may occur:
 * 
 * 1. Between the NSManagedObjectContext and its in-memory cached state at the NSPersistentStoreCoordinator layer.
 *    In this case, the merge conflict has a source object and a cached snapshot but no persisted snapshot (persnap is nil).
 *
 * 2. Between the cached state at the NSPersistentStoreCoordinator and the external store (file, database, etc.).
 *    In this case, the merge conflict has a cached snapshot and a persisted snapshot.  The source object is also provided as a convenience,
 *    but it is not directly involved in the conflict.
 * 
 *  Snapshot dictionaries include values for all attributes and to-one relationships, but not to-many relationships.  
 *   Relationship values are NSManagedObjectID references. to-many relationships must be pulled from the persistent store as needed. 
 *
 *  A newVersion number of 0 means the object was deleted and the corresponding snapshot is nil.
 */
- (instancetype)initWithSource:(NSManagedObject*)srcObject newVersion:(NSUInteger)newvers oldVersion:(NSUInteger)oldvers cachedSnapshot:(NSDictionary*)cachesnap persistedSnapshot:(NSDictionary*)persnap NS_DESIGNATED_INITIALIZER;

@end


NS_CLASS_AVAILABLE(10_7, 5_0)
@interface NSMergePolicy : NSObject {
@private
    NSUInteger _type;
    void* _reserved2;
    void* _reserved3;
}

@property (readonly) NSMergePolicyType mergeType;

/*
 * In a subclass implementation of initWithMergeType:, you should invoke super with the NSMergePolicyType that is closest to the behavior you want.
 * This will make it easier to use the superclass's implementation of -resolveConflicts:error:, and then customize the results.  You are strongly encouraged to do so.
 * Due to the complexity of merging to-many relationships, this class is designed with the expectation that you call super as the base implemenation.
 */
- (id)initWithMergeType:(NSMergePolicyType)ty NS_DESIGNATED_INITIALIZER;

/*
 * In a subclass, you are strongly encouraged to override initWithMergeType: and customize the results from calling super instead of performing your own actions from scratch.
 * Correctly merging to-many relationships is very challenging and any mistakes will cause permanent data corruption in the form of dangling foreign keys.
 */
- (BOOL)resolveConflicts:(NSArray*)list error:(NSError **)error;

@end

