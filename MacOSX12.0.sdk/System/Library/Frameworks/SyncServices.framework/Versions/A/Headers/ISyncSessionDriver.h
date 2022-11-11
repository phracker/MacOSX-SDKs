/*
 * SyncServices -- ISyncSessionDriver.h
 * Copyright (c) 2003, Apple Computer, Inc.  All rights reserved.
 */

#import <Foundation/Foundation.h>
#import <SyncServices/ISyncCommon.h>

@protocol ISyncSessionDriverDataSource;

/* These are the allowed return values for - (ISyncSessionDriverMode)preferredSyncModeForEntityName:(NSString *)entity;
   A value of Fast indicates that we should attempt a fast sync with the server
    - note that the sync server may instead require a slow sync
   A value of Slow indicates that the Data Source will be asked for every record
   A value of Refresh indicates that the driver will call clientDidResetEntityNames:(NSArray *)entityNames
   on the ISyncSession being driven.  See ISyncSession.h for a discussion on sync modes */
typedef enum {
    ISyncSessionDriverModeFast = 1,
    ISyncSessionDriverModeSlow,
    ISyncSessionDriverModeRefresh,
} ISyncSessionDriverMode NS_DEPRECATED_MAC(10_4, 10_7);

/* These are the allowed return values for 
   - (ISyncSessionDriverChangeResult)applyChange:(ISyncChange *)change
      forEntityName:(NSString *)entityName
      remappedRecordIdentifier:(NSString **)outRecordIdentifier
      formattedRecord:(NSDictionary **)outRecord
      error:(NSError **)outError;
   A value of Refused means that the incoming change was refused by the client.
   A value of Accepted means that the incoming change was accepted by the client.
   A value of Ignored means that the incoming change will neither be accepted nor rejected by the client.
    If no other action is taken on the record in question, the client will pull the record on its next sync.
   A value of Error means that an error has occured, and that the sync should be cancelled.
*/
typedef enum {
    ISyncSessionDriverChangeRefused = 0,
    ISyncSessionDriverChangeAccepted,
    ISyncSessionDriverChangeIgnored,
    ISyncSessionDriverChangeError
} ISyncSessionDriverChangeResult NS_DEPRECATED_MAC(10_4, 10_7);

@class ISyncClient, ISyncSession, ISyncChange;

@interface ISyncSessionDriver : NSObject {
}

/* The designated method to create an ISyncSessionDriver.
   The driver can be reused for multiple sync sessions.
   Sample usage case:
   ISyncSessionDriver *sessionDriver = [[ISyncSessionDriver sessionDriverWithDataSource:myDataSource] retain];
   BOOL success = [sessionDriver sync];
   if (!success) myError = [sessionDriver lastError]; */
+ (ISyncSessionDriver *)sessionDriverWithDataSource:(id <ISyncSessionDriverDataSource>)dataSource NS_DEPRECATED_MAC(10_4, 10_7);

/* Initiate a sync.
   The driver will register the ISyncClient if it is not already registered.
   The driver will create an ISyncSession. */
- (BOOL)sync NS_DEPRECATED_MAC(10_4, 10_7);

/* This initiates an asynchronous sync.
   If the driver is unable to create a sync session, this call will return NO, and outError will contain the error.
   If the driver is able to create a sync session, this call will return YES.  Any errors that occur during a sync
   will cause sessionDriverDidCancelSession: to be called, and the error will be available via lastError
   Clients invoking this method must pay attention to the
   delegate callbacks sessionDriverDidFinishSession: and sessionDriverDidCancelSession: to determine
   if the sync succeeded or failed. */
- (BOOL)startAsynchronousSync:(NSError **)outError NS_DEPRECATED_MAC(10_4, 10_7);

/* If a previous call to sync returned NO, this method will return the error associated with that failed sync.
   This error is only valid until the driver begins a new sync */
- (NSError *)lastError NS_DEPRECATED_MAC(10_4, 10_7);

/* Get the data source object, which implements the ISyncSessionDriverDataSource Protocol.
   When an ISyncSessionDriver instance receives a sync invocation, it will 
   call back to the data source object for its data. */
- (id <ISyncSessionDriverDataSource>)dataSource NS_DEPRECATED_MAC(10_4, 10_7);

/* Set and get the delegate object.  If no delegate is supplied, an ISyncSessionDriver will use the
   dataSource object as the delegate. */
- (void)setDelegate:(id /*implements ISyncSessionDriverDelegate Informal Protocol*/)delegate NS_DEPRECATED_MAC(10_4, 10_7);
- (id /*implements ISyncSessionDriverDelegate Informal Protocol*/)delegate NS_DEPRECATED_MAC(10_4, 10_7);

/* Set and get shouldSyncOnAlert.  If this is true, then the driver will register as a sync alert handler.
   When the client is requested to join a sync, the driver will initiate a sync, and behave as though
   its -sync method was invoked. 
   This value defaults to NO */
- (void)setHandlesSyncAlerts:(BOOL)yesOrNo NS_DEPRECATED_MAC(10_4, 10_7);
- (BOOL)handlesSyncAlerts NS_DEPRECATED_MAC(10_4, 10_7);

/* Get the ISyncClient. The ISyncSessionDriver will construct an ISyncClient with the clientIdentifier
   specified by the data source. */
- (ISyncClient *)client NS_DEPRECATED_MAC(10_4, 10_7);

/* Get the ISyncSession.  The ISyncSessionDriver will create an ISyncSession as part of its
   sync method.  When the driver returns from an invocation of sync, and when either of 
   the delegate methods
   - (void)sessionDriverDidFinishSession:(ISyncSessionDriver *)sender;
   - (void)sessionDriverDidCancelSession:(ISyncSessionDriver *)sender;
   are called, the session object is no longer valid, and the driver will return nil.
   This method should be called only on the same thread in which the sync method has been invoked. */
- (ISyncSession *)session NS_DEPRECATED_MAC(10_4, 10_7);

/* Finish the current sync session.  This method should be used when a client wants to prematurely finish a sync session.
   This method should be used instead of [[sessionDriver session] finishSyncing] for all ISyncSessionDriverDataSources.
   If this method is invoked while the Driver is waiting for the Data Source to return from a callback,
   the return value of that callback is dropped. */
- (void)finishSyncing NS_DEPRECATED_MAC(10_4, 10_7);

@end

@protocol ISyncSessionDriverDataSource

/* Returns a unique client identifier to represent the client to the sync engine.
   This method is invoked when creating a sync client before beginning a sync session.
   Each client is identified by an id.  There are no restrictions on the content or length of an
   id, but it must be unique across all clients.  This is specified when the client is registered
   and can never be changed afterwards. */
- (NSString *)clientIdentifier NS_DEPRECATED_MAC(10_4, 10_7);

/* Returns a NSURL to the client's description property list.
   See ISyncManager.h for documentation regarding the layout of this plist. */
- (NSURL *)clientDescriptionURL NS_DEPRECATED_MAC(10_4, 10_7);

/* Returns a NSArray of NSURLs, each of which is a Schema Bundle
   See ISyncManager.h for documentation regarding the layout of schema bundles. */
- (NSArray * /* NSURL */)schemaBundleURLs NS_DEPRECATED_MAC(10_4, 10_7);

/* Method called during the negotiate phase of an ISyncSession */

/* Returns the sync type the client wants for any entity. */
- (ISyncSessionDriverMode)preferredSyncModeForEntityName:(NSString *)entity NS_DEPRECATED_MAC(10_4, 10_7);


/* Method called during the push phase of an ISyncSession */

/* Called with an entity to be slow synced. This returns a dictionary mapping one or more
   records (value) to their record identifiers (key). The records should be dictionaries
   suitable to be passed in to the sync server.
   To help with memory performance, the data source may choose to only return some records 
   during any given invocation of this method.  In that case, the data source should set
   *moreComing to YES.  The driver will repeatedly call this method on the data source with the
   same entity name, until the data source does not set *moreComing to YES.
   If the data source has no records to return, it should return an empty NSDictionary.
   If an error occurs in the data source, it should return nil, and set *outError to an NSError.
   If nil is returned, the sync session will be cancelled, the sync method will return NO, and
   calls to lastError will return *outError. */
- (NSDictionary *)recordsForEntityName:(NSString *)entity moreComing:(BOOL *)moreComing error:(NSError **)outError NS_DEPRECATED_MAC(10_4, 10_7);


/* Methods called during the pull phase of an ISyncSession */

/* Apply the specified ISyncChange.
   If the change is of type ISyncChangeTypeAdd or ISyncChangeTypeModify, and the change was accepted,
   the client can specify a local id by setting *outRecordIdentifier.  If the client formats the incoming record,
   it should set *outRecord to the new record.  If the client does not format the incoming record, it
   should not set *outRecord.
   outRecordIdentifier and outRecord will never be nil for ISyncChangeTypeAdd and ISyncChangeTypeModify
   If *outRecordIdentifier is not set, and the change is of type ISyncChangeTypeAdd, the record's global id will be used.
   If *outRecordIdentifier is not set, and the change is of type ISyncChangeTypeModify, the record's current local id will be used.
   If the change is of type ISyncChangeTypeDelete, *outRecordIdentifier and *outRecord are ignored.
   If an error occurs in the data source, it should return ISyncSessionDriverChangeError,
   and set *outError to an NSError.
   If ISyncSessionDriverChangeError is returned, the sync session will be cancelled, the sync method will return NO, and
   calls to lastError will return *outError. */
- (ISyncSessionDriverChangeResult)applyChange:(ISyncChange *)change forEntityName:(NSString *)entityName remappedRecordIdentifier:(NSString **)outRecordIdentifier formattedRecord:(NSDictionary **)outRecord error:(NSError **)outError NS_DEPRECATED_MAC(10_4, 10_7);

/* Called when the data source should remove all its records for an entity
   Clients should return YES if the resulting deletes were accepted.
   If an error occurs in the data source, it should return NO, and set *outError to an NSError.
   If NO is returned, the sync session will be cancelled, the sync method will return NO, and
   calls to lastError will return *outError. */
- (BOOL)deleteAllRecordsForEntityName:(NSString *)entityName error:(NSError **)outError NS_DEPRECATED_MAC(10_4, 10_7);

@optional

/* Returns a NSArray of NSStrings, each of which represents an entity to be synced
 Return an empty array to specify that no entities should be synced
 If this method is not implemented, ISyncSessionDriver will construct sync sessions
 with each entity listed in the client description that is enabled for the client. */
- (NSArray * /* NSString */)entityNamesToSync NS_DEPRECATED_MAC(10_4, 10_7);

/* This optional method should be implemented by clients that wish to pull a subset
 of the entities being pushed.  If this method is not implemented, ISyncSessionDriver
 will pull the same entities that were pushed
 Return an empty array to specify that no entities should be pulled */
- (NSArray * /* NSString */)entityNamesToPull NS_DEPRECATED_MAC(10_4, 10_7);

/* How long the client will wait for the Sync Server to begin a new session.
 If the data source doesn't implement this method, the default is 60.0 seconds */
- (NSTimeInterval)sessionBeginTimeout NS_DEPRECATED_MAC(10_4, 10_7);

/* How long the client will wait for the Sync Server in prepareToPullChanges
 If the client doesn't implement this method, the default is 600.0 seconds */
- (NSTimeInterval)sessionPullChangesTimeout NS_DEPRECATED_MAC(10_4, 10_7);

/* A data source must implement both, or neither of the following methods.
 See ISyncSession.h for a description of sync anchors
 lastSyncAnchorForEntityName: will be called immediately after a session is begun.
 nextSyncAnchorForEntityName: will be called immediately before prepareToPullChanges...
 is called on a sync session, and immediately before clientCommittedAcceptedChanges
 is called on a sync session.  An ISyncSessionDriver calls clientCommittedAcceptedChanges
 once per session, just before calling finishSyncing on that session.
 */

/* The data source should return the stored sync anchor from the last sync for the given entity name.
 * A client may specify a single anchor for a representative entity that will be used for all entities
 * in the dataclass. Such a representative entity must always be syncd by the client. If a client uses
 * a representative entity, then this method should return nil for all the other entities in a dataclass.*/
- (NSString *)lastAnchorForEntityName:(NSString *)entityName NS_DEPRECATED_MAC(10_4, 10_7);

/* The data source should create a new sync anchor for the given entity name, and store it
 alongside the data being synced. As in lastAnchorForEntityName: a client may specify a single
 anchor  for a representative entity of a dataclass. */
- (NSString *)nextAnchorForEntityName:(NSString *)entityName NS_DEPRECATED_MAC(10_4, 10_7);

/* Methods called during the push phase of an ISyncSession */

/* Called with an entity to be fast synced. This returns a dictionary mapping one or more
 records (value) to their record identifiers (key).
 The values should be full sync records.
 To help with memory performance, the data source may choose to only return some records
 during any given invocation of this method.  In that case, the data source should set
 *moreComing to YES.  The driver will repeatedly call this method on the data source with the
 same entity name, until the data source does not set *moreComing to YES.
 All sync session driver data sources that request a fast sync must respond to
 one or both of this message and changesForEntityName:moreComing:
 If the data source has no changed records to return, it should return an empty NSDictionary.
 If an error occurs in the data source, it should return nil, and set *outError to an NSError.
 If nil is returned, the sync session will be cancelled, the sync method will return NO, and
 calls to lastError will return *outError. */
- (NSDictionary *)changedRecordsForEntityName:(NSString *)entity moreComing:(BOOL *)moreComing error:(NSError **)outError NS_DEPRECATED_MAC(10_4, 10_7);

/* Called with an entity to be fast synced. This returns an array of one or more ISyncChange-s.
 To help with memory performance, the data source may choose to only return some changes 
 during any given invocation of this method.  In that case, the data source should set
 *moreComing to YES.  The driver will repeatedly call this method on the data source with the
 same entity name, until the data source does not set *moreComing to YES.
 All sync session driver data sources that request a fast sync must respond to 
 one or both of this message and changedRecordsForEntityName:moreComing:
 If the data source has no changed records to return, it should return an empty NSArray.
 If an error occurs in the data source, it should return nil, and set *outError to an NSError.
 If nil is returned, the sync session will be cancelled, the sync method will return NO, and
 calls to lastError will return *outError. */
- (NSArray *)changesForEntityName:(NSString *)entity moreComing:(BOOL *)moreComing error:(NSError **)outError NS_DEPRECATED_MAC(10_4, 10_7);

/* Called with an entity to be fast synced.  This returns an array of record identifiers of
 the deleted records for pushing.
 This method is an alternative to returning ISyncChanges of type ISyncChangeTypeDelete from a
 call to changesForEntityName:moreComing:
 To help with memory performance, the data source may choose to only return some record identifiers
 during any given invocation of this method.  In that case, the data source should set
 *moreComing to YES.  The driver will repeatedly call this method on the data source with the
 same entity name, until the data source does not set *moreComing to YES.
 If the data source has no identifiers of deleted records to return, it should return an empty NSArray.
 If an error occurs in the data source, it should return nil, and set *outError to an NSError.
 If nil is returned, the sync session will be cancelled, the sync method will return NO, and
 calls to lastError will return *outError. */
- (NSArray *)identifiersForRecordsToDeleteForEntityName:(NSString *)entityName moreComing:(BOOL *)moreComing error:(NSError **)outError NS_DEPRECATED_MAC(10_4, 10_7);

@end


@interface NSObject (ISyncSessionDriverDelegate)

/* Convenience methods.  These are called back to the client at different stages of the sync.
   If an error occurs in the delegate, it should return NO, and set *outError to an NSError.
   If NO is returned, the sync session will be cancelled, the sync method will return NO, and
   calls to lastError will return *outError.
   Beware that if the delegate raises in any of these callbacks
   (except sessionDriverWillCancelSession:, sessionDriverDidCancelSession:, and sessionDriverDidFinishSession:)
   any existing sync session will be cancelled. */
- (BOOL)sessionDriver:(ISyncSessionDriver *)sender didRegisterClientAndReturnError:(NSError **)outError NS_DEPRECATED_MAC(10_4, 10_7);
- (BOOL)sessionDriver:(ISyncSessionDriver *)sender willNegotiateAndReturnError:(NSError **)outError NS_DEPRECATED_MAC(10_4, 10_7);
- (BOOL)sessionDriver:(ISyncSessionDriver *)sender didNegotiateAndReturnError:(NSError **)outError NS_DEPRECATED_MAC(10_4, 10_7);
- (BOOL)sessionDriver:(ISyncSessionDriver *)sender willPushAndReturnError:(NSError **)outError NS_DEPRECATED_MAC(10_4, 10_7);
- (BOOL)sessionDriver:(ISyncSessionDriver *)sender didPushAndReturnError:(NSError **)outError NS_DEPRECATED_MAC(10_4, 10_7);
- (BOOL)sessionDriver:(ISyncSessionDriver *)sender willPullAndReturnError:(NSError **)outError NS_DEPRECATED_MAC(10_4, 10_7);
- (BOOL)sessionDriver:(ISyncSessionDriver *)sender didPullAndReturnError:(NSError **)outError NS_DEPRECATED_MAC(10_4, 10_7);

/* Either the Finish callbacks or Cancel callbacks will be called.
   If the Finish callbacks are called, the Cancel callbacks will not be called.
   If the Cancel callbacks are called, the Finish callbacks will not be called. */
- (BOOL)sessionDriver:(ISyncSessionDriver *)sender willFinishSessionAndReturnError:(NSError **)outError NS_DEPRECATED_MAC(10_4, 10_7);
/* For the following callbacks, either the session is completed
   (sessionDriverDidFinishSession: and sessionDriverDidCancelSession:)
   or the session is already set to cancel, due to a previous error
   (sessionDriverWillCancelSession:) */
- (void)sessionDriverDidFinishSession:(ISyncSessionDriver *)sender NS_DEPRECATED_MAC(10_4, 10_7);
- (void)sessionDriverWillCancelSession:(ISyncSessionDriver *)sender NS_DEPRECATED_MAC(10_4, 10_7);
- (void)sessionDriverDidCancelSession:(ISyncSessionDriver *)sender NS_DEPRECATED_MAC(10_4, 10_7);

/* This delegate method is called when the session driver receives a sync alert.  It allows a client to do any setup before the
   session driver calls its sync: method. If this method is implemented in a client, a failure to establish a session during a
   sync alert will cause the sessionDriver to call the sessionDriverDidCancelSession: delegate. */
- (BOOL)sessionDriver:(ISyncSessionDriver *)sender didReceiveSyncAlertAndReturnError:(NSError **)outError NS_DEPRECATED_MAC(10_4, 10_7);

@end

