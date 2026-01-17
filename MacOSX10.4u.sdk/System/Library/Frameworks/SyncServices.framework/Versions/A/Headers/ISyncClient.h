/*
 * SyncServices -- ISyncClient.h
 * Copyright (c) 2003, Apple Computer, Inc.  All rights reserved.
 */

#import <SyncServices/ISyncCommon.h>


/* Each registered client is represented by an ISyncClient object.  (Remember that we use the term
   "client" very generally, to include both applications and remote servers, such as .Mac, as well
   as physical devices like phones and PDAs.)  ISyncClient objects provide information about a
   device and methods for controlling how the device should be synchronized.

   You never create an ISyncClient instance yourself.  You get one back from ISyncManager when
   registering a new client; a specific client can be looked up with -[ISyncManager clientWithIdentifier:]
   and there is a method on ISyncManager for getting the list of all registered clients. */


typedef int ISyncStatus;
enum __ISyncStatus {
    ISyncStatusRunning = 1,  // currently syncing
    ISyncStatusSuccess,      // the last sync completed with no errors
    ISyncStatusWarnings,     // the last sync completed with warnings
    ISyncStatusErrors,       // the last sync completed with errors
    ISyncStatusCancelled,    // the user cancelled the last sync
    ISyncStatusFailed,       // the last sync failed to complete (ie. crashed)
    ISyncStatusNever         // never been synced
};


@interface ISyncClient : NSObject

/* Each client is identified by an id.  There are no restrictions on the content or length of an
   id, but it must be unique across all clients.  This is specified when the client is registered
   and can never be changed afterwards. */
- (NSString *)clientIdentifier;

/* A hint as to what kind of thing this client syncs data for.  Valid types are ISyncClientTypeApplication
   (an application such as iCal or AB), ISyncClientTypeDevice (a physical device like a phone,
   iPod or Palm), ISyncClientTypeServer (.Mac) and ISyncClientTypePeer (not yet implemented). */
- (NSString *)clientType;

/* The name of the client - in an ideal world, this will be the actual name of the device or
   application, such as "My iPod" or iCal.  If you refer to this client when dealing with
   the user, you should use the display name.  The display name doesn't have to be unique across
   all clients, but it probably will end up being that way.

   There is no magical discovery or divination of display names; the name is specified when the
   client is first registered and may be changed later by the client (or any other user of the
   SyncServices API). */
- (NSString *)displayName;
- (void)setDisplayName:(NSString *)displayName;

/* An image may be associated with a client.  This is used in applications like iSync to represent
   the client. */
- (NSString *)imagePath;
- (void)setImagePath:(NSString *)path;

/* These are the entities which are supported by the client.  These are not necessarily the
   entities that *will* be synchronized by a client - a phone might be capable of synchronizing
   both contacts and calendars but the user has chosen (via UI in iSync or on the phone) to
   synchronize only contacts, for example.  A client should inform the engine that it will not be
   synchronizing an entity using -setEnabled:forEntityNames:.  It is not strictly required, but
   it allows the engine to do a better job of managing which clients can push the Truth for a
   specific entity.  It is a GOOD IDEA to do that.

   This list of entities is used by the sync engine to maintain a set of databases about the client.
   These databases contain the meta-information needed to synchronize the client properly and when
   an entity is removed from this list, the engine cleans up the associated state.  If the record
   type is later added back, it appears to the engine as if the client were syncing it for the
   first time and so must be refresh synced.

   It is important to understand the implications of this.  Consider the case of calendars on a phone
   which does not support recurrences, requiring the client manually expand the recurrence in to a
   series of events.  If, in response to the user disabling a data class in the UI, the client
   removes the calendar entities from this list and then later adds them back, the engine will
   refresh sync the calendars with the phone.  The expanded recurrences will then erroneously be
   merged in to the user's data.  The user would be better served if the client, instead, disabled
   the entities using -setEnabled:forEntityNames:.

   The list is built from the information provided when the client was registered.  The information
   can be provided directly by the client or the client can specify a description file containing
   the info.  The engine will refresh this list if the contents of the description file change or
   if the client explicitly registers new information.  Changing the list of entities supported by
   a device may require some entities be slow synced on the next sync.  (It depends on the
   relationships between the new and old sets of entities.)  Newly added entities will be refresh
   synced. In this manner, conduits can easily evolve the properties and entities they synchronize
   without having to worry about when they need to slow sync to refresh their device with
   additional properties. */
- (NSArray /* NSString */ *)supportedEntityNames;

/* More information taken from the device description.  These methods indicate a conduit's ability
   to accept or provide changes to records of a particular type.  Again, these do not specify a
   device's willingness to do so - that is left for the conduit to negotiate with the engine when
   it starts a sync session.  They are advisory methods only.

   For example, the iPod conduit will probably indicate that is can accept changes to contacts and
   calendars but will never provide changes to the same. */
- (BOOL)canPushChangesForEntityName:(NSString *)entityName;
- (BOOL)canPullChangesForEntityName:(NSString *)entityName;

/* Return information about the last sync.  -lastSyncDate specifies the start date of the last
   sync, even if that sync was a failure.  It returns nil if the device has never synced a record
   type.  If a device is syncing the record type when asked, -lastSyncStatus will return
   ISyncStatusRunning but -lastSyncDate will continue to return the date of the last sync.

   The engine will maintain this information for as long as a device supports a record type name
   (ie. the record type name is returned from -entityNames).  When a device stops supporting
   a record type, this information is erased from the engine's database.  Should the device later
   start support the record type again, these methods will act as if the device had never before
   synced it. */
- (NSDate *)lastSyncDateForEntityName:(NSString *)entityName;
- (ISyncStatus)lastSyncStatusForEntityName:(NSString *)entityName;

/* The entities which a device (probably) *will* synchronize on the next sync.  These methods
   can be used in an advisory fashion for the client and the engine.  Say, for example, that a
   client can synchronize contacts and calendars (ie. both are specified in
   -supportedEntityNames).  Through the client's config UI, the user disables syncing calendars.
   The user must then be prevented from trying to push the Truth for contacts from this client.

   A client should probably use -enabledEntityNames as the list of entity names passed to
   ISyncSession's constructor, for example.  If an entity is not enabled, the engine will not
   allow the client to apply any changes for it; nor will the engine provide any changes for it.
   
   When a client attempts to sync for the first time, the user will be given an opportunity to allow
   or disallow it from syncing.  This choice is presented on a per-DataClass basis.  If the user
   chooses not to allow the client to sync a particular DataClass then all the Entities from that
   DataClass supported by the client will be disabled (setEnabled:NO...).  A client may wish to
   provide a mechanism whereby the user can ask it to re-enable (setEnabled:YES...) those entities
   in case they change their mind. If re-enabled, the next time the client attempts to sync those
   entities the user will be given another opportunity to allow or disallow it. */
- (NSArray /* NSString */ *)enabledEntityNames;
- (BOOL)isEnabledForEntityName:(NSString *)entityName;
- (void)setEnabled:(BOOL)flag forEntityNames:(NSArray /* NSString */ *)entityNames;

/* Tell the engine the client wants to pull the Truth.  The engine will not let the client push any
   changes.  The client is expected to erase its data store at the start of the pull phase, before
   pulling any changes.

   This option remains in effect until the client successfully passes through the pull phase of a sync
   session.  After that, the engine expects the client to synchronize normally. */
- (BOOL)shouldReplaceClientRecordsForEntityName:(NSString *)entityName;
- (void)setShouldReplaceClientRecords:(BOOL)flag forEntityNames:(NSArray /* NSString */ *)entityNames;

/* As a convenience to the conduit author, arbitrary objects can be associated with a device.  Any
   object can be used (we have a garbage-in-garbage-out policy) as long as it is archivable (ie.
   conforms to NSCoding).  Coordinating concurrent access to this information is entirely the
   responsibility of the client. */
- (id)objectForKey:(NSString *)key;
- (void)setObject:(id<NSCoding>)value forKey:(NSString *)key;

/* These are the filters used to control which records the client sees.  Don't call this method
   trivially: every time the filter changes, the engine must re-examine all records in the Truth
   to determine what needs to be pushed to the client.

   New records must be accepted by all matching filters (ie. filters whose -supportedEntityNames
   contains the record's entity).  If any matching filter rejects the record, the record will
   not be given to the client in the pull phase.

   Oh oh, it seems this is not the case: a record will be given to the client in the pull phase
   if at least one filter accepts it.  This is a bug and will be fixed; the behaviour described
   in the paragraph above is the expected behaviour.  For now, you should use a conjunction filter
   (+[ISyncFilter filterMatchingAllFilters:] and +[ISyncFilter filterMatchingAtLeastOneFilter:])
   to get your desired behaviour. */
- (NSArray /* id <ISyncFiltering> */ *)filters;
- (void)setFilters:(NSArray /* id <ISyncFiltering> */ *)filters;

/* Specifies that the receiver wants to synchronize with clients of the specified type (application,
   device, server or peer).  For example, Address Book might register to synchronize with all client
   types.  It will be given a chance to join a sync whenver any client synchronizes the Contacts
   entities.  .Mac might register to synchronize only with device types, so it can participate when a
   Palm of phone is synchronized.  The client will only be notified if it has entities in common with
   the.

   A client may be notified in one of two ways.  It may specify the path of a tool or application which
   will be launched by the sync engine.  The tool will be passed four arguments on the command line:
   "--sync <client id> --entitynames <entity names>".  The entity names is a single string suitable for
   passing to -[NSString componentsSeparatedByString:@","].  If the tool wishes to sync any of these
   entities, it may create an ISyncSession to join the sync.  The tool is not limited to syncing only
   these entities, but it must sync at least one of them.  If the tool terminates without creating a
   sync session, the engine will assume the client does not want to participate in the sync.

   Alternatively, an observer object may be registered.  The sync engine will invoke the selector on the
   observer.  The selector should have the following signature

         -(void)client:(ISyncClient *)client mightWantToSyncEntityNames:(NSArray *)entityNames.

   If it wishes to join the sync, it must create an ISyncSession before returning from the method.  Only
   one observer per client per machine may be registered.  If an observer is registered in a different
   process, -setSyncAlertHandler:selector: will throw an exception.  An observer is automatically
   removed when its process exits, of course.

   You can register both a sync tool and an observer, but only one of the notification methods will be
   used.  If both a tool and an observer are registered, only the observer will be called.

   When a client creates a sync session, it specifies how long it is willing to wait to start syncing (the
   "before date" parameter).  The sync engine will wait at most that amount of time for a notified
   clients to join the sync.  If a notified client takes too long, the sync will proceed without it. */
- (BOOL)shouldSynchronizeWithClientsOfType:(NSString *)clientType;
- (void)setShouldSynchronize:(BOOL)flag withClientsOfType:(NSString *)clientType;
- (NSString *)syncAlertToolPath;
- (void)setSyncAlertToolPath:(NSString *)path;
- (void)setSyncAlertHandler:(id)handler selector:(SEL)selector;

@end

SYNCSERVICES_EXPORT NSString * const ISyncClientTypeApplication;
SYNCSERVICES_EXPORT NSString * const ISyncClientTypeDevice;
SYNCSERVICES_EXPORT NSString * const ISyncClientTypeServer;
SYNCSERVICES_EXPORT NSString * const ISyncClientTypePeer;
