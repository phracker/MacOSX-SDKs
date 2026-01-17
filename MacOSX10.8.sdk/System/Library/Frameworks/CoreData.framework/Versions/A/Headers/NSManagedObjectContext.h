/*
    NSManagedObjectContext.h
    Core Data
    Copyright (c) 2004-2012 Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSSet.h>
#import <Foundation/NSDate.h>
#import <Foundation/NSLock.h>
#import <CoreData/CoreDataDefines.h>

@class NSError;
@class NSFetchRequest;
@class NSManagedObject;
@class NSManagedObjectID;
@class NSPersistentStore;
@class NSPersistentStoreCoordinator;
@class NSUndoManager;
@class NSNotification;

// Notifications immediately before and immediately after the context saves.  The user info dictionary contains information about the objects that changed and what changed
COREDATA_EXTERN NSString * const NSManagedObjectContextWillSaveNotification NS_AVAILABLE(10_5, 3_0);
COREDATA_EXTERN NSString * const NSManagedObjectContextDidSaveNotification NS_AVAILABLE(10_4, 3_0);

// Notification when objects in a context changed:  the user info dictionary contains information about the objects that changed and what changed
COREDATA_EXTERN NSString * const NSManagedObjectContextObjectsDidChangeNotification NS_AVAILABLE(10_4, 3_0);    

// User info keys for NSManagedObjectContextObjectsDidChangeNotification:  the values for these keys are sets of managed objects
COREDATA_EXTERN NSString * const NSInsertedObjectsKey NS_AVAILABLE(10_4, 3_0);
COREDATA_EXTERN NSString * const NSUpdatedObjectsKey NS_AVAILABLE(10_4, 3_0);
COREDATA_EXTERN NSString * const NSDeletedObjectsKey NS_AVAILABLE(10_4, 3_0);

COREDATA_EXTERN NSString * const NSRefreshedObjectsKey NS_AVAILABLE(10_5, 3_0);
COREDATA_EXTERN NSString * const NSInvalidatedObjectsKey NS_AVAILABLE(10_5, 3_0);

// User info keys for NSManagedObjectContextObjectsDidChangeNotification:  the values for these keys are arrays of objectIDs
COREDATA_EXTERN NSString * const NSInvalidatedAllObjectsKey NS_AVAILABLE(10_5, 3_0); // All objects in the context have been invalidated

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

enum {
    NSConfinementConcurrencyType		= 0x00,
    NSPrivateQueueConcurrencyType		= 0x01,
    NSMainQueueConcurrencyType			= 0x02
};
typedef NSUInteger NSManagedObjectContextConcurrencyType;

NS_CLASS_AVAILABLE(10_4,3_0)
@interface NSManagedObjectContext : NSObject <NSCoding, NSLocking> {
@private
  int32_t _spinLock;
  id _parentObjectStore;
  NSUndoManager *_undoManager;
  void *_dispatchQueue;
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
	  unsigned int _propagatingDeletes:1;
	  unsigned int _isNSEditorEditing:1;
      unsigned int _isMainThreadBlessed:1;
      unsigned int _isImportContext:1;
      unsigned int _preflightSaveInProgress:1;
      unsigned int _disableDiscardEditing:1;
      unsigned int _isParentStoreContext:1;
      unsigned int _postSaveNotifications:1;
      unsigned int _isMerging:1;
      unsigned int _reservedFlags:11;
  } _flags;
  NSMutableSet *_unprocessedChanges;
  NSMutableSet *_unprocessedDeletes;
  NSMutableSet *_unprocessedInserts;
  NSMutableSet *_insertedObjects;
  NSMutableSet *_deletedObjects;
  NSMutableSet *_changedObjects;
  NSMutableSet *_lockedObjects;
  NSMutableSet *_refreshedObjects;
  id _infoByGID;
  id *_cachedObsInfoByEntity;
  short _undoTransactionID;
  id _lock;
  long _lockCount;
  long _objectStoreLockCount;
  NSTimeInterval _fetchTimestamp;
  id _delegate;
  id _referenceQueue;
  id _userinfo;
  id _mergePolicy;
  int32_t _cd_rc;
  int32_t _ignoreChangeNotification;
  id _editors;
  id* _debuggingRecords;
  id _childObjectStores;
  id _reserved2;
}

- (id)initWithConcurrencyType:(NSManagedObjectContextConcurrencyType)ct NS_AVAILABLE(10_7,  5_0);

#if NS_BLOCKS_AVAILABLE
- (void)performBlock:(void (^)())block NS_AVAILABLE(10_7,  5_0);
- (void)performBlockAndWait:(void (^)())block NS_AVAILABLE(10_7,  5_0);
#endif /* NS_BLOCKS_AVAILABLE */

/* coordinator which provides model and handles persistency (multiple contexts can share a coordinator) */
- (void)setPersistentStoreCoordinator:(NSPersistentStoreCoordinator *)coordinator;
- (NSPersistentStoreCoordinator *)persistentStoreCoordinator;

- (void)setParentContext:(NSManagedObjectContext*)parent NS_AVAILABLE(10_7,  5_0);
- (NSManagedObjectContext*)parentContext NS_AVAILABLE(10_7,  5_0);

- (void)setUndoManager:(NSUndoManager *)undoManager;
- (NSUndoManager *)undoManager;

- (BOOL)hasChanges;
- (NSMutableDictionary*)userInfo NS_AVAILABLE(10_7,  5_0);
- (NSManagedObjectContextConcurrencyType)concurrencyType NS_AVAILABLE(10_7,  5_0);

/* returns the object for the specified ID if it is registered in the context already or nil. It never performs I/O. */
- (NSManagedObject *)objectRegisteredForID:(NSManagedObjectID *)objectID;    

/* returns the object for the specified ID if it is already registered, otherwise it creates a fault corresponding to that objectID.  It never returns nil, and never performs I/O.  The object specified by objectID is assumed to exist, and if that assumption is wrong the fault may throw an exception when used. */
- (NSManagedObject *)objectWithID:(NSManagedObjectID *)objectID;    

/* returns the object for the specified ID if it is already registered in the context, or faults the object into the context.  It might perform I/O if the data is uncached.  If the object cannot be fetched, or does not exist, or cannot be faulted, it returns nil.  Unlike -objectWithID: it never returns a fault.  */
- (NSManagedObject*)existingObjectWithID:(NSManagedObjectID*)objectID error:(NSError**)error NS_AVAILABLE(10_6, 3_0);

// method to fetch objects from the persistent stores into the context (fetch request defines the entity and predicate as well as a sort order for the objects); context will match the results from persistent stores with current changes in the context (so inserted objects are returned even if they are not persisted yet); to fetch a single object with an ID if it is not guaranteed to exist and thus -objectWithObjectID: cannot be used, one would create a predicate like [NSComparisonPredicate predicateWithLeftExpression:[NSExpression expressionForKeyPath:@"objectID"] rightExpression:[NSExpression expressionForConstantValue:<object id>] modifier:NSPredicateModifierDirect type:NSEqualToPredicateOperatorType options:0]
- (NSArray *)executeFetchRequest:(NSFetchRequest *)request error:(NSError **)error;    

// returns the number of objects a fetch request would have returned if it had been passed to -executeFetchRequest:error:.   If an error occurred during the processing of the request, this method will return NSNotFound. 
- (NSUInteger) countForFetchRequest: (NSFetchRequest *)request error: (NSError **)error NS_AVAILABLE(10_5, 3_0);    

- (void)insertObject:(NSManagedObject *)object;
- (void)deleteObject:(NSManagedObject *)object;

// if flag is YES, merges an object with the state of the object available in the persistent store coordinator; if flag is NO, simply refaults an object without merging (which also causes other related managed objects to be released, so you can use this method to trim the portion of your object graph you want to hold in memory) 
- (void)refreshObject:(NSManagedObject *)object mergeChanges:(BOOL)flag;    

// marks an object for conflict detection, which means that the save fails if the object has been altered in the persistent store by another application.  This allows optimistic locking for unchanged objects.  Conflict detection is always performed on changed or deleted objects.
- (void)detectConflictsForObject:(NSManagedObject *)object;    

// key-value observation
- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary *)change context:(void *)context;    

// usually contexts process changes to the object graph coalesced at the end of the event - this method triggers it explicitly
- (void)processPendingChanges;    

// specifies the store a newly inserted object will be saved in.  Unnecessary unless there are multiple writable persistent stores added to the NSPersistentStoreCoordinator which support this object's entity.
- (void)assignObject:(id)object toPersistentStore:(NSPersistentStore *)store;    

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

// whether or not the context propagates deletes to related objects at the end of the event, or only at save time
- (BOOL)propagatesDeletesAtEndOfEvent;  
- (void)setPropagatesDeletesAtEndOfEvent:(BOOL)flag;  // The default is YES.

// whether or not the context holds a retain on all registered objects, or only upon objects necessary for a pending save (inserted, updated, deleted, or locked)
- (BOOL)retainsRegisteredObjects;  
- (void)setRetainsRegisteredObjects:(BOOL)flag;  // The default is NO.

// Staleness interval is the relative time until cached data should be considered stale. The value is applied on a per object basis. For example, a value of 300.0 informs the context to utilize cached information for no more than 5 minutes after that object was originally fetched. This does not affect objects currently in use. Principly, this controls whether fulfilling a fault uses data previously fetched by the application, or issues a new fetch.  It is a hint which may not be supported by all persistent store types.
- (NSTimeInterval)stalenessInterval;
- (void)setStalenessInterval:(NSTimeInterval)expiration;  // a negative value is considered infinite.  The default is infinite staleness.

- (void)setMergePolicy:(id)mergePolicy;  // acceptable merge policies are listed above as id constants
- (id)mergePolicy;    // default: NSErrorMergePolicy

/* Converts the object IDs of the specified objects to permanent IDs.  This implementation will convert the object ID of each managed object in the specified array to a permanent ID.  Any object in the target array with a permanent ID will be ignored;  additionally, any managed object in the array not already assigned to a store will be assigned, based on the same rules Core Data uses for assignment during a save operation (first writable store supporting the entity, and appropriate for the instance and its related items.)  Although the object will have a permanent ID, it will still respond positively to -isInserted until it is saved.  If an error is encountered obtaining an identifier, the return value will be NO.
*/
- (BOOL)obtainPermanentIDsForObjects:(NSArray *)objects error:(NSError **)error NS_AVAILABLE(10_5, 3_0);

/* Merges the changes specified in notification object received from another context's NSManagedObjectContextDidSaveNotification into the receiver.  This method will refresh any objects which have been updated in the other context, fault in any newly inserted objects, and invoke deleteObject: on those which have been deleted.  The developer is only responsible for the thread safety of the receiver.
*/
- (void)mergeChangesFromContextDidSaveNotification:(NSNotification *)notification NS_AVAILABLE(10_5, 3_0);

@end
