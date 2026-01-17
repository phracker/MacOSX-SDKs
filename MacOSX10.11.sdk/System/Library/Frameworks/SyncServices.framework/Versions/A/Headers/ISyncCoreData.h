/*
 * SyncServices -- ISyncCoreData.h
 * Copyright (c) 2006, Apple Computer, Inc.  All rights reserved.
 *
 */

#import <CoreData/CoreData.h>
#import <Foundation/Foundation.h>
#import <SyncServices/ISyncCommon.h>

@class ISyncClient, ISyncSession, ISyncChange;


@protocol NSPersistentStoreCoordinatorSyncing;


@interface NSPersistentStoreCoordinator (CoreDataSync)
/* This starts a synchronization of the receiving persistent store coordinator. Client must exist 
   and syncHandler will receive the NSPersistentStoreCoordinatorSyncHandler delegate methods.  If
   inBackground is true, the session is created in the caller's thread, before returning, using the
   non-blocking method +[ISyncSession beginSessionInBackgroundWithClient:entityNames:target:selector:].
   This makes it suitable for use in a sync alert when you don't want to block the calling thread
   (eg. if you registered the sync alert handler on the main thread).  When the sync session is
   ready to begin, we spawn off a new thread and perform the sync on that thread.  If inBackground
   is false, the sync is performed immediately, returning when done, in the caller's thread. */
- (BOOL)syncWithClient:(ISyncClient *)client inBackground:(BOOL)flag handler:(id <NSPersistentStoreCoordinatorSyncing>)syncHandler error:(NSError **)rError NS_DEPRECATED_MAC(10_4, 10_7);

/* Tell the persistent store coordinator where to store the details it needs to fast sync the stores.
   This must be called before any of its persistent stores are mutated.  If one of its stores is mutated
   without this path being set, we will slow sync on the next sync. */
- (void)setStoresFastSyncDetailsAtURL:(NSURL *)url forPersistentStore:(NSPersistentStore *)store NS_DEPRECATED_MAC(10_4, 10_7);
@end


@protocol NSPersistentStoreCoordinatorSyncing <NSObject>
@optional

/* Get the list of contexts that will be monitored during the sync.  When we pull a change from the
   session, we check that the record has not been updated in any of these contexts.  If it has, the
   change is ignored - this causes the change to be pushed in the next sync session and the sync engine
   can figure out whether there are any conflicts or not.  If no context has modified the object, the
   change will be applied to the persistent store.

   This narrows the window for collisions but does not close it completely.  Someone may change an object
   in a monitored context after the sync client has updated it.  The application must either prevent changes
   to objects modified during a sync or must be prepared to merge changes from the persistent stores with its
   contexts. */
- (NSArray *)managedObjectContextsToMonitorWhenSyncingPersistentStoreCoordinator:(NSPersistentStoreCoordinator *)coordinator NS_DEPRECATED_MAC(10_4, 10_7);

/* Get the list of contexts that will be updated when we save changes to the persistent store.  If the
   sync handler does not implement this method, it is the caller's responsibility to reload its contexts
   at the end of a sync. */
- (NSArray *)managedObjectContextsToReloadAfterSyncingPersistentStoreCoordinator:(NSPersistentStoreCoordinator *)coordinator NS_DEPRECATED_MAC(10_4, 10_7);

/* The following methods are called as we progress through the sync session (negotiation, pushing,
   pulling, done).  You may explicitly finish or cancel the sync session to finish syncing early. */
- (BOOL)persistentStoreCoordinatorShouldStartSyncing:(NSPersistentStoreCoordinator *)coordinator NS_DEPRECATED_MAC(10_4, 10_7);
- (void)persistentStoreCoordinator:(NSPersistentStoreCoordinator *)coordinator willPushChangesInSyncSession:(ISyncSession *)session NS_DEPRECATED_MAC(10_4, 10_7);
- (void)persistentStoreCoordinator:(NSPersistentStoreCoordinator *)coordinator didPushChangesInSyncSession:(ISyncSession *)session NS_DEPRECATED_MAC(10_4, 10_7);
- (void)persistentStoreCoordinator:(NSPersistentStoreCoordinator *)coordinator willPullChangesInSyncSession:(ISyncSession *)session NS_DEPRECATED_MAC(10_4, 10_7);
- (void)persistentStoreCoordinator:(NSPersistentStoreCoordinator *)coordinator didPullChangesInSyncSession:(ISyncSession *)session NS_DEPRECATED_MAC(10_4, 10_7);
- (void)persistentStoreCoordinator:(NSPersistentStoreCoordinator *)coordinator didFinishSyncSession:(ISyncSession *)session NS_DEPRECATED_MAC(10_4, 10_7);
- (void)persistentStoreCoordinator:(NSPersistentStoreCoordinator *)coordinator didCancelSyncSession:(ISyncSession *)session error:(NSError *)error NS_DEPRECATED_MAC(10_4, 10_7);


/* This method is called before the synchronizer pushes a record to the sync server. It can be used 
   by the delegate to modify the record on the fly.  If you return nil, no record will be pushed for
   the specified object. */
- (NSDictionary *)persistentStoreCoordinator:(NSPersistentStoreCoordinator *)coordinator willPushRecord:(NSDictionary *)record forManagedObject:(NSManagedObject *)managedObject inSyncSession:(ISyncSession *)session NS_DEPRECATED_MAC(10_4, 10_7);
- (BOOL)persistentStoreCoordinator:(NSPersistentStoreCoordinator *)coordinator willDeleteRecordWithIdentifier:(NSString *)identifier inSyncSession:(ISyncSession *)session NS_DEPRECATED_MAC(10_4, 10_7);


/* This method is called after the synchronizer pulls a record from the truth, and before it applies 
   it to its managed object context.  You can change the change that will be applied to the object. */
- (ISyncChange *)persistentStoreCoordinator:(NSPersistentStoreCoordinator *)coordinator willApplyChange:(ISyncChange *)change toManagedObject:(NSManagedObject *)managedObject inSyncSession:(ISyncSession *)session NS_DEPRECATED_MAC(10_4, 10_7);

/* This method is called after applying a change to an object. */
- (void)persistentStoreCoordinator:(NSPersistentStoreCoordinator *)coordinator didApplyChange:(ISyncChange *)change toManagedObject:(NSManagedObject *)managedObject inSyncSession:(ISyncSession *)session NS_DEPRECATED_MAC(10_4, 10_7);

/* This method is called after saving changes to the persistent stores.  Typically, this happens at the end
   of a sync but may occur multiple times during a sync.  (Essentially, whenever clientCommittedAcceptedChanges
   is called on the sync session.) */
- (void)persistentStoreCoordinator:(NSPersistentStoreCoordinator *)coordinator didCommitChanges:(NSDictionary *)changes inSyncSession:(ISyncSession *)session NS_DEPRECATED_MAC(10_4, 10_7);

@end


