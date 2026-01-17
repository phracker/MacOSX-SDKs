/*
    NSManagedObjectContext.h
    Core Data
    Copyright (c) 2004-2005 Apple Computer, Inc.
    All rights reserved.
*/

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

#import <Foundation/NSObject.h>
#import <Foundation/NSDate.h>
#import <Foundation/NSLock.h>
#import <CoreFoundation/CFArray.h>
#import <CoreFoundation/CFDictionary.h>
#import <CoreData/CoreDataDefines.h>

@class NSArray;
@class NSDictionary;
@class NSError;
@class NSFetchRequest;
@class NSManagedObject;
@class NSManagedObjectID;
@class NSMutableArray;
@class NSMutableDictionary;
@class NSMutableSet;
@class NSObjectStore;
@class NSPersistentStoreCoordinator;
@class NSRecursiveLock;
@class NSSet;
@class NSString;
@class NSUndoManager;

COREDATA_EXTERN NSString * const NSManagedObjectContextDidSaveNotification;
COREDATA_EXTERN NSString * const NSManagedObjectContextObjectsDidChangeNotification;    // user info dictionary contains information about the objects that changed and what changed

// User info keys for NSManagedObjectContextObjectsDidChangeNotification:
COREDATA_EXTERN NSString * const NSInsertedObjectsKey;
COREDATA_EXTERN NSString * const NSUpdatedObjectsKey;
COREDATA_EXTERN NSString * const NSDeletedObjectsKey;

COREDATA_EXTERN id NSErrorMergePolicy;    // Default policy for all managed object contexts - save returns with an error that contains the object IDs of the objects that had conflicts(NSInsertedObjectsKey, NSUpdatedObjectsKey).
COREDATA_EXTERN id NSMergeByPropertyStoreTrumpMergePolicy;    // This policy merges conflicts between the persistent store's version of the object and the current in memory version. The merge occurs by individual property. For properties which have been changed in both the external source and in memory, the external changes trump the in memory ones.
COREDATA_EXTERN id NSMergeByPropertyObjectTrumpMergePolicy;    // This policy merges conflicts between the persistent store's version of the object and the current in memory version. The merge occurs by individual property. For properties which have been changed in both the external source and in memory, the in memory changes trump the external ones.
COREDATA_EXTERN id NSOverwriteMergePolicy;    // This policy overwrites all state for the changed objects in conflict The current object's state is pushed upon the persistent store.
COREDATA_EXTERN id NSRollbackMergePolicy;    // This policy discards all state for the changed objects in conflict. The persistent store's version of the object is used.

@interface NSManagedObjectContext : NSObject <NSCoding, NSLocking> {
@private
  int32_t _spinLock;
  NSObjectStore *_objectStore;
  NSUndoManager *_undoManager;
  NSMutableArray *_children;
  struct _managedObjectContextFlags {
      unsigned int _registeredForCallback:1;
      unsigned int _propagatesDeletesAtEndOfEvent:1;
      unsigned int _exhaustiveValidation:1;
      unsigned int _processingChanges:1;
      unsigned int _useCommittedSnapshot:1;
      unsigned int _registeredUndoTransactionID:1;
      unsigned int _retainsAllRegisteredObjects:1;
      unsigned int _savingInProgress:1;
      unsigned int _wasDisposed:1;
      unsigned int _unprocessedChangesPending:1;
      unsigned int _isDirty:1;
      unsigned int _ignoreUndoCheckpoints:1;
      unsigned int _reservedFlags:20;
  } _flags;
  NSMutableSet *_unprocessedChanges;
  NSMutableSet *_unprocessedDeletes;
  NSMutableSet *_unprocessedInserts;
  NSMutableSet *_insertedObjects;
  NSMutableSet *_deletedObjects;
  NSMutableSet *_changedObjects;
  NSMutableSet *_lockedObjects;
  NSMutableSet *_refreshedObjects;
  CFMutableDictionaryRef     _infoByGID;
  NSMutableDictionary *_cachedObsInfoByEntity;
  short _undoTransactionID;
  NSRecursiveLock *_lock;
  int _lockCount;
  int _objectStoreLockCount;
  NSTimeInterval _fetchTimestamp;
  id _delegate;
  CFMutableArrayRef _referenceQueue;
  int _ignoreChangeNotification;
  id _mergePolicy;
   u_int32_t _cd_rc;
  struct _managedObjectContextEditorFlags {
      unsigned int _isEditing:1;
      unsigned int _reservedManagedObjectContext:31;
  } _managedObjectContextEditorFlags;
  CFMutableArrayRef _editors;
  void *_reserved1;
  void *_reserved2;
  void *_reserved3;
}

// coordinator which provides model and handles persistency (multiple contexts can share a coordinator)
- (void)setPersistentStoreCoordinator:(NSPersistentStoreCoordinator *)coordinator;
- (NSPersistentStoreCoordinator *)persistentStoreCoordinator;

- (void)setUndoManager:(NSUndoManager *)undoManager;
- (NSUndoManager *)undoManager;
- (BOOL)hasChanges;

- (NSManagedObject *)objectRegisteredForID:(NSManagedObjectID *)objectID;    // returns the object for the specified ID if it is registered in the context already or nil
- (NSManagedObject *)objectWithID:(NSManagedObjectID *)objectID;    // returns the object for the specified ID (the object does not already need to be registered in the context, it might be fetched or returned as a fault) - the object is assumed to exist as described by the ID
- (NSArray *)executeFetchRequest:(NSFetchRequest *)request error:(NSError **)error;    // method to fetch objects from the persistent stores into the context (fetch request defines the entity and predicate as well as a sort order for the objects); context will match the results from persistent stores with current changes in the context (so inserted objects are returned even if they are not persisted yet); to fetch a single object with an ID if it is not guaranteed to exist and thus -objectWithObjectID: cannot be used, one would create a predicate like [NSComparisonPredicate predicateWithLeftExpression:[NSExpression expressionForKeyPath:@"objectID"] rightExpression:[NSExpression expressionForConstantValue:<object id>] modifier:NSPredicateModifierDirect type:NSEqualToPredicateOperatorType options:0]

- (void)insertObject:(NSManagedObject *)object;
- (void)deleteObject:(NSManagedObject *)object;
- (void)refreshObject:(NSManagedObject *)object mergeChanges:(BOOL)flag;    // if flag is YES, merges an object with the state of the object available in the persistent store coordinator; if flag is NO, simply refaults an object without merging (which also causes other related managed objects to be released, so you can use this method to trim the portion of your object graph you want to hold in memory) 
- (void)detectConflictsForObject:(NSManagedObject *)object;    // marks an object for conflict detection, which means that the save fails if the object has been altered in the persistent store by another application.  This allows optimistic locking for unchanged objects.  Conflict detection is always performed on changed or deleted objects.
- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary *)change context:(void *)context;    // KVO
- (void)processPendingChanges;    // usually contexts process changes to the object graph coalesced at the end of the event - this method triggers it explicitly

- (void)assignObject:(id)object toPersistentStore:(id)store;    // specifies the store a newly inserted object will be saved in.  Unnecessary unless there are multiple writable persistent stores added to the NSPersistentStoreCoordinator which support this object's entity.

- (NSSet *)insertedObjects;
- (NSSet *)updatedObjects;
- (NSSet *)deletedObjects;
- (NSSet *)registeredObjects;

- (void)undo;
- (void)redo;
- (void)reset;
- (void)rollback;
- (BOOL)save:(NSError **)error;

- (void)lock;
- (void)unlock;
- (BOOL)tryLock;

- (BOOL)propagatesDeletesAtEndOfEvent;  // whether or not the context propagates deletes to related objects at the end of the event, or only at save time
- (void)setPropagatesDeletesAtEndOfEvent:(BOOL)flag;  // The default is YES.

- (BOOL)retainsRegisteredObjects;  // whether or not the context holds a retain on all registered objects, or only upon objects necessary for a pending save (inserted, updated, deleted, or locked)
- (void)setRetainsRegisteredObjects:(BOOL)flag;  // The default is NO.

// Staleness interval is the relative time until cached data should be considered stale. The value is applied on a per object basis. For example, a value of 300.0 informs the context to utilize cached information for no more than 5 minutes after that object was originally fetched. This does not affect objects currently in use. Principly, this controls whether fulfilling a fault uses data previously fetched by the application, or issues a new fetch.  It is a hint which may not be supported by all persistent store types.
- (NSTimeInterval)stalenessInterval;
- (void)setStalenessInterval:(NSTimeInterval)expiration;  // a negative value is considered infinite.  The default is infinite staleness.

- (void)setMergePolicy:(id)mergePolicy;  // acceptable merge policies are listed above as id constants
- (id)mergePolicy;    // default: NSErrorMergePolicy

@end

#endif
