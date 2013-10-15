/*
 * SyncServices -- ISyncSession.h
 * Copyright (c) 2003, Apple Computer, Inc.  All rights reserved.
 */

#import <SyncServices/ISyncCommon.h>

@class ISyncChange, ISyncClient, ISyncRecordSnapshot;



@interface ISyncSession : NSObject

/* Phase I: negotiating the sync mode. */
+ (ISyncSession *)beginSessionWithClient:(ISyncClient *)client entityNames:(NSArray /* entity name */ *)entityNames beforeDate:(NSDate *)date;
/* Returns immediately and invokes a target callback when the session can start or if the session.
   cannot be started. The target is invoked with the selector and two arguments, the ISyncClient
   and the ISyncSession. The selector should be of this form:
   -(void)client:(ISyncClient *)can beginSession:(ISyncSession *)session;
   If the session cannot be started, the session parameter is nil.
*/
+ (void)beginSessionInBackgroundWithClient:(ISyncClient *)client entityNames:(NSArray /* entity name */ *)entityNames target:(id)target selector:(SEL)selector;
+ (void)cancelPreviousBeginSessionWithClient:(ISyncClient *)client;

/* The default is to assume that a client will be fast syncing all the entities specified when the
   session was created.  Telling the engine that a client was reset is tantamount to saying "forget
   everything you ever knew about me and let's start over again".  In sync parlance, this is what we
   call a refresh sync.  Telling the engine that you want to push all records (ie. slow syncing) just
   means that you, the client, can't figure out which records have changed since the last sync and so
   you're going to give all of your records to the engine.  The engine will figure out what has changed
   since the last sync and only provide to you the appropriate sets of changes. */
- (void)clientDidResetEntityNames:(NSArray /* NSString */ *)entityNames;
- (void)clientWantsToPushAllRecordsForEntityNames:(NSArray /* NSString */ *)entityNames;

/* These methods query how the engine is going to sync you, the client. -shouldPushChangesForEntityName:
   returns NO if you should not push any changes for an entity.  -shouldPushAllRecordsForEntityName:
   returns YES if you should give to the engine all of your records.  (What we call "slow syncing" in our
   parlance.)  Converseley, -shouldPullChangesForEntityName: returns NO if the engine will not be giving
   you any changes for an entity and -shouldReplaceAllRecordsOnClientForEntityName: returns YES if you
   should delete all of your records and replace them with the records the engine will hand you.  To a
   certain extent, these values may be modified by the methods -clientDidResetEntityNames: and
   -clientWantsToPushAllRecordsForEntityNames: as described above. */
- (BOOL)shouldPushChangesForEntityName:(NSString *)entityName;
- (BOOL)shouldPushAllRecordsForEntityName:(NSString *)entityName;
- (BOOL)shouldPullChangesForEntityName:(NSString *)entityName;
- (BOOL)shouldReplaceAllRecordsOnClientForEntityName:(NSString *)entityName;


/* Phase II: pushing changes from the client.  You can create an ISyncChange object yourself and
   push that directly, or you can give the engine the entire record and let it figure out what
   the changes are.  If you are pushing the record, it should represent the entire state of the
   record from your backing store.  At the very least, every record dictionary MUST have an attribute
   identifying the entity this record is an instance of, keyed to ISyncRecordEntityNameKey.

   Consider, for example, some (purely fictional) contact with two email address.  The path of the
   first name is "first name".  There are two relationships involving this contact, one for the
   home address and one for the email addresses.  There is one home address, identified by the
   record 1492.address1, and two email addresses, 1492.email1 and 1492.email2.  The record dictionaries
   for these four records might look something like the following:

        1492 {
            ISyncRecordEntityNameKey = Contact;
            first name = Edgar;
            last name = Qwerty;
            Contact to Address = ( 1492.address1 );
            Contact to EmailAddress = ( 1492.email1, 1492.email2 );
        }
        
        1492.address1 {
            ISyncRecordEntityNameKey = Address;
            label = home;
            street = 123 Main St.;
            city = Everywhere;
            country = USA;
            postal code = 90210;
        }

        1492.email1 {
            ISyncRecordEntityNameKey = EmailAddress;
            type = home;
            email = asdf@asdf.com;
        }

        1492.email2 {
            ISyncRecordEntityNameKey = EmailAddress;
            type = work;
            label = summer cottage;
            email = qwerty@keyboard.com;
        }
*/
- (void)pushChange:(ISyncChange *)change;
- (void)pushChangesFromRecord:(NSDictionary *)record withIdentifier:(NSString *)recordId;

/* A convenience to delete a record so you don't have to manually construct an ISyncChange. */
- (void)deleteRecordWithIdentifier:(NSString *)recordId;

/* The proverbial "soft delete".  This indicates that a record no longer exists on the client but this
   should not be considered a delete.  This method is special in that it can be used during either the
   push phase and the pull phase.

   You may specify whether or not you want the record back (as an add) during the next pull phase.  If you
   call this method during the push phase and say YES, the record will be re-applied in the pull phase
   of this same session.  If you call this method during the pull phase, it will be replaced in the
   pull phase of the next session. 

   When invoked with flag set to NO during the pulling phase, this is equivalent
   to refusing a record using the method clientRefusedChangesForRecordWithIdentifier:

   This method will not touch the client info, if any, associated with this record.
*/
- (void)clientLostRecordWithIdentifier:(NSString *)recordId shouldReplaceOnNextSync:(BOOL)flag;


/* Phase III: pulling changes for the client.  The entities that you specify here must be a subset of
   the entities specified when the session was created. */
- (BOOL)prepareToPullChangesForEntityNames:(NSArray /* NSString */ *)entityNames beforeDate:(NSDate *)date;
- (void)prepareToPullChangesInBackgroundForEntityNames:(NSArray /* NSString */ *)entityNames target:(id)target selector:(SEL)selector;

- (NSEnumerator /* ISyncChange */ *)changeEnumeratorForEntityNames:(NSArray /* NSString */ *)entityNames;

- (void)clientAcceptedChangesForRecordWithIdentifier:(NSString *)recordId formattedRecord:(NSDictionary *)formattedRecord newRecordIdentifier:(NSString *)recordId;

/* This method informs the sync engine that the client has
   refused to apply the changes for the record specified by recordIdentifier.

   After invoking this method, the sync engine will not send the same change
   during any subsequent syncs unless the record is modified. Use filtering if
   you want to permanently ignore some records. Refusing a record does not
   change the local id mapping for the client. Invoking this method will not
   effect other clients participating in the same sync session.

   This method will not touch the client info, if any, associated with this record.
*/
- (void)clientRefusedChangesForRecordWithIdentifier:(NSString *)recordId;
- (void)clientCommittedAcceptedChanges;
- (void)clientChangedRecordIdentifiers:(NSDictionary *)oldToNew;

- (BOOL)isCancelled;
- (void)cancelSyncing;
- (void)finishSyncing;

/* Conduit-specific, unsynchronized information stored with a record.  The data is removed when
   the client removes the associated record.  You can specify any object here, but it must conform
   to the NSCoding protocol. */
- (id)clientInfoForRecordWithIdentifier:(NSString *)recordId;
- (void)setClientInfo:(id <NSCoding>)clientInfo forRecordWithIdentifier:(NSString *)recordId;

/* Return a snapshot of the records in the Truth.  ISyncSession creates two snap shots during the sync.
   The first is made when the session is created.  The second is made at the same time as the changes
   for the client are prepared (when -prepareToPullChangesForEntityNames:beforeDate: is called).
   Compare to the method on ISyncManager. */
- (ISyncRecordSnapshot *)snapshotOfRecordsInTruth;
@end


/* This exception may be thrown from any instance method on ISyncSession.  It indicates that the sync
   session has been cancelled, either directly on the session using -cancelSyncing or externally by
   someone else.

   If a sync is cancelled during the negotiate phase, the negotiations simply fail and
   +beginSessionWithClient:entityNames:beforeDate:(NSDate *)date returns nil.

   If a sync is cancelled during the push phase, no further changes from the client will be accepted.  The
   changes that have been accepted will be discarded.  If a client cannot provide those changes on a
   subsequent sync, it must force a slow sync.  The client cannot proceed to the mingle and pull
   phases.

   If a sync is cancelled during the mingle phase (ie. the exception is thrown from
   -prepareToPullChangesForEntityNames:beforeDate:), the changes that have been accepted from the
   client will be discarded.  If a client cannot provide those changes on a subsequent sync, it must
   force a slow sync.  The client cannot proceed to the pull phase.

   If a sync is cancelled during the pull phase, the changes that have not been accepted or rejected by
   the client and explicitly committed (using -clientCommittedAcceptedChanges) will be given to the
   client again on a subsequent sync.  After a cancellation, a client may continue to accept or reject
   the changes it received prior to the cancellation; it may invoke -clientCommittedAcceptedChanges to
   indicate its acceptance of these changes; and it may use -clientChangedRecordIdentifiers: to update
   the client Ids.  It will not be given any further changes, however. */
SYNCSERVICES_EXPORT NSString * const ISyncSessionCancelledException;

SYNCSERVICES_EXPORT NSString * const ISyncSessionUnavailableException;

/* This exception may be thrown during the push phase.  It is thrown when the engine detects the client
   trying to push "bad" data - bad data being defined as anything which fails a data validation test.
   The engine has some built in validators, to check records conform to a schema specification.

   I wish I could say the exception will be thrown as soon as a bad record is applied by the client, but
   this may not be the case.  Some validation checks can only be done when additional context has been
   gathered; and for efficiency reasons, the engine may defer processing until a threshold of changes
   have been applied.

   The userInfo object in the exception contains the list of rejected records and the reasons for each. */
SYNCSERVICES_EXPORT NSString * const    ISyncInvalidRecordException;
SYNCSERVICES_EXPORT NSString * const    ISyncInvalidRecordIdentifiersKey; // an array of record ids
SYNCSERVICES_EXPORT NSString * const    ISyncInvalidRecordReasonsKey; // a dictionary, keyed by record id
SYNCSERVICES_EXPORT NSString * const    ISyncInvalidRecordsKey; // a dictionary, keyed by record id


/* These exceptions are thrown when trying to synchronize an invalid entity (one that has not been
   registered) or a valid entity that the client was not registered to synchronize. */
SYNCSERVICES_EXPORT NSString * const ISyncInvalidEntityException;
SYNCSERVICES_EXPORT NSString * const ISyncUnsupportedEntityException;



/* Every record passed to the sync engine (and every record received from the sync engine) must be
   associated with an entity.  The name of the entity is stored in the record dictionary using
   this key. */
SYNCSERVICES_EXPORT NSString * const ISyncRecordEntityNameKey;
