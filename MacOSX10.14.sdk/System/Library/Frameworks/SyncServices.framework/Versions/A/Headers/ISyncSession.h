/*
 * SyncServices -- ISyncSession.h
 * Copyright (c) 2003, Apple Computer, Inc.  All rights reserved.
 */

#import <Foundation/Foundation.h>
#import <SyncServices/ISyncCommon.h>


@class ISyncChange, ISyncClient, ISyncRecordSnapshot;


@interface ISyncSession : NSObject

/* Phase I: negotiating the sync mode. */
+ (ISyncSession *)beginSessionWithClient:(ISyncClient *)client entityNames:(NSArray /* entity name */ *)entityNames beforeDate:(NSDate *)date NS_DEPRECATED_MAC(10_4, 10_7);

/* Returns immediately and invokes a target callback when the session can start or if the session.
   cannot be started. The target is invoked with the selector and two arguments, the ISyncClient
   and the ISyncSession. The selector should be of this form:
   -(void)client:(ISyncClient *)can beginSession:(ISyncSession *)session;
   If the session cannot be started, the session parameter is nil.
*/
+ (void)beginSessionInBackgroundWithClient:(ISyncClient *)client entityNames:(NSArray /* entity name */ *)entityNames target:(id)target selector:(SEL)selector NS_DEPRECATED_MAC(10_4, 10_7);
+ (void)cancelPreviousBeginSessionWithClient:(ISyncClient *)client NS_DEPRECATED_MAC(10_4, 10_7);

/* If a client is using sync anchors, when starting a sync session, the client passes in the previous
   sync anchors, one per entity. The anchors dictionary is a map from the entity name to the sync anchor
   value, and the values are the anchors as last set in the previous sync's calls to the methods
   clientFinishedPushingChangesWithNextAnchors or clientCommittedAcceptedChanges. As a convenience, the
   user may specify a mapping for a single entity name for some representative entity of a
   dataclass. However, if more than one mapping per dataclass is provided, then mappings are required
   for every entity name being synchronized. The lack of a mapping in this case will force the entity
   without a mapping to be refreshed.
    
   The values that are passed in are compared to the previous values. If an anchor does not match for
   an entity, then the method shouldPushAllRecordsForEntityName will return YES for this entity.
    
   If there is no value for a entity's anchor, then the entity can either be left out of the dictionary,
   or even better, the value [NSNull null] can be can be put in the dictionary for that entity name. If
   there is no value the client will be refreshed and the sync will be treated as if it is the first
   sync done by the client. The null value (or lack of value) for an anchor should be used on the
   client's first sync (when there would be no value in the client's data store), or when the data store
   is cleared or lost.

   nil is an acceptable value for the dictionary, and will always result in a full refresh sync for all
   the entities specified in the sync.

   If a client is using sync anchors, it should also call the method
   clientFinishedPushingChangesWithNextAnchors after pushing changes, and call the sync anchor variant
   of clientCommittedAcceptedChanges as outlined below. Failure to make these calls will likely result
   in the next sync of these entities being a refresh sync. Finally, an exception will be raised if
   these methods are called on a session that was created using the earlier API that did not include a
   lastAnchors argument.
*/
+ (ISyncSession *)beginSessionWithClient:(ISyncClient *)client entityNames:(NSArray /* entity name */ *)entityNames beforeDate:(NSDate *)date lastAnchors:(NSDictionary /* string entity name -> string anchor */ *)anchors NS_DEPRECATED_MAC(10_5, 10_7);

+ (void)beginSessionInBackgroundWithClient:(ISyncClient *)client entityNames:(NSArray /* entity name */ *)entityNames target:(id)target selector:(SEL)selector lastAnchors:(NSDictionary /* string entity name -> string anchor */ *)anchors NS_DEPRECATED_MAC(10_5, 10_7);

// + (ISyncSession *)beginSessionWithClient:(ISyncClient *)client entityNames:(NSArray /* entity name */ *)entityNames beforeDate:(NSDate *)date lastAnchors: (NSDictionary *)anchors hasChanges:(BOOL)flag error: (NSError **)error;

/* The default is to assume that a client will be fast syncing all the entities specified when the
   session was created.  Telling the engine that a client was reset is tantamount to saying "forget
   everything you ever knew about me and let's start over again".  In sync parlance, this is what we
   call a refresh sync.  Telling the engine that you want to push all records (ie. slow syncing) just
   means that you, the client, can't figure out which records have changed since the last sync and so
   you're going to give all of your records to the engine.  The engine will figure out what has changed
   since the last sync and only provide to you the appropriate sets of changes. */
- (void)clientDidResetEntityNames:(NSArray /* NSString */ *)entityNames NS_DEPRECATED_MAC(10_4, 10_7);
- (void)clientWantsToPushAllRecordsForEntityNames:(NSArray /* NSString */ *)entityNames NS_DEPRECATED_MAC(10_4, 10_7);

/* These methods query how the engine is going to sync you, the client. -shouldPushChangesForEntityName:
   returns NO if you should not push any changes for an entity.  -shouldPushAllRecordsForEntityName:
   returns YES if you should give to the engine all of your records.  (What we call "slow syncing" in our
   parlance.)  Converseley, -shouldPullChangesForEntityName: returns NO if the engine will not be giving
   you any changes for an entity and -shouldReplaceAllRecordsOnClientForEntityName: returns YES if you
   should delete all of your records and replace them with the records the engine will hand you.  To a
   certain extent, these values may be modified by the methods -clientDidResetEntityNames: and
   -clientWantsToPushAllRecordsForEntityNames: as described above. */
- (BOOL)shouldPushChangesForEntityName:(NSString *)entityName NS_DEPRECATED_MAC(10_4, 10_7);
- (BOOL)shouldPushAllRecordsForEntityName:(NSString *)entityName NS_DEPRECATED_MAC(10_4, 10_7);
- (BOOL)shouldPullChangesForEntityName:(NSString *)entityName NS_DEPRECATED_MAC(10_4, 10_7);
- (BOOL)shouldReplaceAllRecordsOnClientForEntityName:(NSString *)entityName NS_DEPRECATED_MAC(10_4, 10_7);


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
- (void)pushChange:(ISyncChange *)change NS_DEPRECATED_MAC(10_4, 10_7);
- (void)pushChangesFromRecord:(NSDictionary *)record withIdentifier:(NSString *)recordId NS_DEPRECATED_MAC(10_4, 10_7);

/* A convenience to delete a record so you don't have to manually construct an ISyncChange. */
- (void)deleteRecordWithIdentifier:(NSString *)recordId NS_DEPRECATED_MAC(10_4, 10_7);

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
- (void)clientLostRecordWithIdentifier:(NSString *)recordId shouldReplaceOnNextSync:(BOOL)flag NS_DEPRECATED_MAC(10_4, 10_7);

/* If a client is using Sync Anchors, after pushing all changes, a client must create a new sync anchor
   string for each entity name that was synced, save the anchors in the client datastore, and pass the
   anchors to clientFinishedPushingChangesWithNextAnchors. As a convenience a single representative
   entity name to anchor mapping may be used for all of the entities in a dataclass. If the client is
   pulling the truth, the anchor is specified when calling clientCommittedAcceptedChanges.
*/
- (void)clientFinishedPushingChangesWithNextAnchors:(NSDictionary /* string entity  name -> string anchor */ *)anchors NS_DEPRECATED_MAC(10_5, 10_7);

/* Phase III: pulling changes for the client.  The entities that you specify here must be a subset of
   the entities specified when the session was created. */
- (BOOL)prepareToPullChangesForEntityNames:(NSArray /* NSString */ *)entityNames beforeDate:(NSDate *)date NS_DEPRECATED_MAC(10_4, 10_7);
- (void)prepareToPullChangesInBackgroundForEntityNames:(NSArray /* NSString */ *)entityNames target:(id)target selector:(SEL)selector NS_DEPRECATED_MAC(10_4, 10_7);

- (NSEnumerator /* ISyncChange */ *)changeEnumeratorForEntityNames:(NSArray /* NSString */ *)entityNames NS_DEPRECATED_MAC(10_4, 10_7);

- (void)clientAcceptedChangesForRecordWithIdentifier:(NSString *)recordId formattedRecord:(NSDictionary *)formattedRecord newRecordIdentifier:(NSString *)recordId NS_DEPRECATED_MAC(10_4, 10_7);

/* This method informs the sync engine that the client has
   refused to apply the changes for the record specified by recordIdentifier.

   After invoking this method, the sync engine will not send the same change
   during any subsequent syncs unless the record is modified. Use filtering if
   you want to permanently ignore some records. Refusing a record does not
   change the local id mapping for the client. Invoking this method will not
   effect other clients participating in the same sync session.

   This method will not touch the client info, if any, associated with this record.
*/
- (void)clientRefusedChangesForRecordWithIdentifier:(NSString *)recordId NS_DEPRECATED_MAC(10_4, 10_7);
- (void)clientCommittedAcceptedChanges NS_DEPRECATED_MAC(10_4, 10_7);
/* If a client is using sync anchors, after accepting pulled changes, a client must create a new sync anchor
   string for each entity that was synced, save the anchors in the client datastore, and pass the anchors to
   the call to clientCommittedAcceptedChangesWithNextAnchors. As a convenience a single representative entity
   name to anchor mapping may be used for all of the entities in a dataclass. If a client is pushing the
   truth, this method won't be called, but that is fine, as the sync anchors passed into the method
   clientFinishedPushingChangesWithNextAnchors will be used.
*/
- (void)clientCommittedAcceptedChangesWithNextAnchors:(NSDictionary /* string entity name -> string anchor */ *)anchors NS_DEPRECATED_MAC(10_5, 10_7);

- (void)clientChangedRecordIdentifiers:(NSDictionary *)oldToNew NS_DEPRECATED_MAC(10_4, 10_7);

- (BOOL)isCancelled NS_DEPRECATED_MAC(10_4, 10_7);
- (void)cancelSyncing NS_DEPRECATED_MAC(10_4, 10_7);
- (void)finishSyncing NS_DEPRECATED_MAC(10_4, 10_7);

/* Conduit-specific, unsynchronized information stored with a record.  The data is removed when
   the client removes the associated record.  You can specify any object here, but it must conform
   to the NSCoding protocol. */
- (id)clientInfoForRecordWithIdentifier:(NSString *)recordId NS_DEPRECATED_MAC(10_4, 10_7);
- (void)setClientInfo:(id <NSCoding>)clientInfo forRecordWithIdentifier:(NSString *)recordId NS_DEPRECATED_MAC(10_4, 10_7);

/* Return a snapshot of the records in the Truth.  ISyncSession creates two snap shots during the sync.
   The first is made when the session is created.  The second is made at the same time as the changes
   for the client are prepared (when -prepareToPullChangesForEntityNames:beforeDate: is called).
   Compare to the method on ISyncManager. */
- (ISyncRecordSnapshot *)snapshotOfRecordsInTruth NS_DEPRECATED_MAC(10_4, 10_7);

/* Clients can call this method to inform the server that they are still alive
   but doing something that keeps them busy and prevents them from talking to the server
   process. This will prevent the server from timing them out on the watchdog. */ 
- (void)ping NS_DEPRECATED_MAC(10_5, 10_7);

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
   client will still be applied.  On the next sync the client should only supply new changes.
   The client cannot proceed to the pull phase.

   If a sync is cancelled during the pull phase, the changes that have not been accepted or rejected by
   the client and explicitly committed (using -clientCommittedAcceptedChanges) will be given to the
   client again on a subsequent sync.  After a cancellation, a client may continue to accept or reject
   the changes it received prior to the cancellation; it may invoke -clientCommittedAcceptedChanges to
   indicate its acceptance of these changes; and it may use -clientChangedRecordIdentifiers: to update
   the client Ids.  It will not be given any further changes, however. */
SYNCSERVICES_EXPORT NSString * const ISyncSessionCancelledException NS_DEPRECATED_MAC(10_4, 10_7);

SYNCSERVICES_EXPORT NSString * const ISyncSessionUnavailableException NS_DEPRECATED_MAC(10_4, 10_7);

/* This exception may be thrown during the push phase.  It is thrown when the engine detects the client
   trying to push "bad" data - bad data being defined as anything which fails a data validation test.
   The engine has some built in validators, to check records conform to a schema specification.

   I wish I could say the exception will be thrown as soon as a bad record is applied by the client, but
   this may not be the case.  Some validation checks can only be done when additional context has been
   gathered; and for efficiency reasons, the engine may defer processing until a threshold of changes
   have been applied.

   The userInfo object in the exception contains the list of rejected records and the reasons for each. */
SYNCSERVICES_EXPORT NSString * const    ISyncInvalidRecordException NS_DEPRECATED_MAC(10_4, 10_7);
SYNCSERVICES_EXPORT NSString * const    ISyncInvalidRecordIdentifiersKey NS_DEPRECATED_MAC(10_4, 10_7); // an array of record ids
SYNCSERVICES_EXPORT NSString * const    ISyncInvalidRecordReasonsKey NS_DEPRECATED_MAC(10_4, 10_7); // a dictionary, keyed by record id
SYNCSERVICES_EXPORT NSString * const    ISyncInvalidRecordsKey NS_DEPRECATED_MAC(10_4, 10_7); // a dictionary, keyed by record id


/* These exceptions are thrown when trying to synchronize an invalid entity (one that has not been
   registered) or a valid entity that the client was not registered to synchronize. */
SYNCSERVICES_EXPORT NSString * const ISyncInvalidEntityException NS_DEPRECATED_MAC(10_4, 10_7);
SYNCSERVICES_EXPORT NSString * const ISyncUnsupportedEntityException NS_DEPRECATED_MAC(10_4, 10_7);

/* Other exceptions that can be generated on 10.6 include
 * ISyncInvalidSchemaException and ISyncInvalidArgumentsException.  These are
 * declared in SyncServicesErrors.h. On 10.5.6 NSInternalInconsistencyException
 * or NSInvalidArgumentsException exceptions when raised indicate an internal
 * problem that was encountered either because of some sort of data corruption,
 * an internal bug, or an unhandled condition. */


/* Every record passed to the sync engine (and every record received from the sync engine) must be
   associated with an entity.  The name of the entity is stored in the record dictionary using
   this key. */
SYNCSERVICES_EXPORT NSString * const ISyncRecordEntityNameKey NS_DEPRECATED_MAC(10_4, 10_7);
