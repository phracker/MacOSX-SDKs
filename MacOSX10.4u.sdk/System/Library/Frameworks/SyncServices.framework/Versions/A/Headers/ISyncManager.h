/*
 * SyncServices -- ISyncManager.h
 * Copyright (c) 2003, Apple Computer, Inc.  All rights reserved.
 */

#import <SyncServices/ISyncCommon.h>

@class ISyncClient, ISyncRecordSnapshot;


/* ISyncManager is the starting point for clients looking to manage clients and syncs.  It
   provides methods to register new clients, look up and remove registered clients, and schedule
   syncs. */

@interface ISyncManager : NSObject

+ (ISyncManager *)sharedManager;

/* Check if the Sync Engine is enabled and available for syncing. */
- (BOOL)isEnabled;

- (ISyncClient *)clientWithIdentifier:(NSString *)clientId;

/* Register a new client.  You specify here all the details needed to  sync the client - supported
   entities and relationships, formatters, etc.  In return, you get back an ISyncClient to use
   and abuse.

   The client description file is a plist containing a single dictionary.  The dictionary may contain
   any of the following keys.  For keys which specify a path, a full path name may be specified, but
   usually you will just want to specify a path relative to the description file.  Unless explicitly
   stated, all keys are optional.

      Type - a string identifying the type of client.  This string must be one of the
      following pre-defined values: "app" (an application like iCal or AB), "device" (a phone, Palm or
      iPod), "server" (.Mac) or "peer" (a peer-to-peer client).  Assume the client is an app if not
      explicitly specified.

      DisplayName - a string containing the display name for this client.

      ImagePath - path to an image of the client.  This must be an absolute path except
      when the description is taken from a file.  Then, it can be a path relative to the description
      file.

      Entities - a dictionary mapping entity names to an array.  The array contains
      an array of property names (both attributes and relationships), indentifying the
      properties supported by the client on each record type.  This field is required.

      PullOnlyEntities - an array containing the names of the entities for which the
      client will pull changes from the engine but will never push changes to the engine.

      PushOnlyEntities - an array containing the names of the entities for which the
      client will only push changes to the engine but for which it will never pull changes from
      the engine.

      SyncsWith - a dictionary specifying the kinds of clients this client wants to sync
      with.  See -setShouldSynchronize:withClientsOfType: for details.  The dictionary contains the
      following keys:

         SyncAlertTypes - an array of the client types this client wants to sync with.

         SyncAlertToolPath - the path of a tool the engine will invoke when a client of the
         specified type starts syncing.  The tool with be passed two arguments on the command
         line: "--sync" and the client's client id.

   It is perfectly valid to call this method for a client that has already been registered to update
   the registration info.  Doing so is not required, however.  The engine will periodically stat the
   description file to see if it has changed and update the client description automagically.  This
   saves you from having to manually track changes to the client description.  If an upgrade lays down
   a new description file, for example, the engine will detect this and automatically pick up the
   changes to the client's description.

   Changing the client description may result in the engine forcing the client to slow sync on the
   next sync.  If a client adds support for additional properties in ISyncClientEntities, for
   example, the engine must slow-sync the client to guarantee the new keys are synchronized
   properly. */
- (ISyncClient *)registerClientWithIdentifier:(NSString *)clientId descriptionFilePath:(NSString *)descriptionFilePath;

/* Remove a previously registered client */
- (void)unregisterClient:(ISyncClient *)client;

/* Register a schema.  You can define new entities and relationships; you can extend an entity with
   additional attributes; you can specify a data validator; you can specify a conflict resolver; and
   you can provide localized names for your schema types.
   
   A schema is defined by a "Schema.plist" file contained in a .syncschema bundle which may contain additional
   images and code which support the plist.  The top-level object in the plist is a dictionary which may
   contain the following keys.  The engine will periodically check this file to see if it has changed.
   If the file has changed, the engine will automatically re-parse it to pick up the new schema
   definition.  This saves you from having to remember to manually re-register your schema in the event
   that it has changed.

    * Name - a string providing a unique name for this schema.  This key is required and
      you should never change the schema name.  Doing so will orphan the old schema definition and
      you will have to manually remove it.  We recommend using the reverse-DNS naming scheme,
	  e.g., "com.apple.Contacts".

    * DataClasses - an array containing various data class descriptions.  The data class
      description contains the following:

         Name - the name of the data class.  This key is required.  We recommend using the reverse-DNS
         naming scheme, e.g., "com.apple.Contacts". The name can be localized using the strings from Schema.strings
	     in the .syncschema bundle.

         Image - the path of an image representing the data class.  For most data classes this
         will be the same image as would be used for the associated document type.  (E.g. Contacts
         would use AddressBook's .vcd image.)  The path can be an absolute path, but if it is not
		 then SyncServices will attempt to use it to load an image resource from the .syncschema bundle.

    * Entities - the value is an array of record type extension descriptions.  Each
      description is an NSDictionary describing an extension to an existing record type.  A
      description may contain the following keys; unless explicitly stated, all of the keys are
      optional:
      
         Name - the name of the entity.  This key is required.  We recommend using the reverse-DNS naming
         scheme, e.g., "com.apple.Contacts". The name can be localized using the strings from Schema.strings in
         the .syncschema bundle.

         ExtensionName - the name of this extension, if you are adding attributes to an
         existing entity.  The extension name is used to scope
         the property and relationship names to prevent collisions.  We recommend using
         the reverse-DNS naming scheme, e.g. com.apple.AddressBook.ContactsExtensions.

         DataClass - the name of the data class this entity belongs to.

        ExcludeFromDataChangeAlert - <true/> or <false/>.  Defaults to false if omitted.  If this flag is set then
        a change to this entity will not count towards the number of changed entities for the purpose
        of displaying the data change alert.

         Attributes - an array containing the description of all attributes in the extension.
         Each attribute description is a dictionary containing the following sub-keys.

             Name - the name of the attribute. The name can be localized using the strings from Schema.strings in
             the .syncschema bundle. The key for the localized name of an attribute is "$entity/$attribute_name",
             for example the key for the attribute with the Name "title" in the entity with the name "com.apple.things.Thing"
             would be "com.apple.things.Thing/title".

            Type - the type of the attribute.  Must be one of the valid attribute
            types, such as string, number, etc.
            
            ExcludeFromDataChangeAlert - <true/> or <false/>.  Defaults to false if omitted.  If this flag is set then
            a change to this attribute will not count towards the number of changed attributes for the purpose
            of displaying the data change alert.

         Relationships - an array containing the description of all relationships in the
         extension.  Each relationship description is a dictionary containing the following keys.

            Name - this is the name of the relationship.  This key is required. The name can be localized using the
            strings from Schema.strings in the .syncschema bundle. The key for the localized name of a relationship is
            "$entity/$relationship_name", for example the key for the relationship with the Name "children" in the entity with
            the name "com.apple.things.Thing" would be "com.apple.things.Thing/children".

            Target - an array containing the names of the target entities.  Generally, a
            relationship has a single target.  If the relative ordering between different
            entities must be maintained, you may specify multiple entities in the target.

            DeleteRule - cascade or nullify.  Defaults to "nullify".

            Ordinality - one or many.  Defaults to "one".

            Ordering - none, weak or strong.  Defaults to "none".

            Required - yes or no.  Defaults to "no".

            InverseRelationships - an array or pairs specifying this relationship's inverse
            relationships.  Each pair is a dictionary containing the following keys:

                EntityName - the name of the entity.

                RelationshipName - the name of the inverse relationship on that entity.

         IdentityProperties - an array specifying the set of properties that are used to match a new
         record from a Sync client with an existing record. If the target of a one to one relationship
         is to be used, the name of the relationship is specified. 

         PropertyDependencies - an array specifying the set of dependencies between the
         properties.  A dependent property is one which must be pushed to a client if any of its
         dependencies are changed.  Each entry in the array is itself an array of strings, specifying
         the names of the co-dependent properties.  Entries may be an attribute name or a relationship
         name.

        ExcludeFromDataChangeAlert - <true/> or <false/>.  Defaults to false if omitted.  If this flag is set then
        a change to this relationship will not count towards the number of changed relationships for the purpose
        of displaying the data change alert.

   It is perfectly valid to call this method for a schema that has already been registered.  It is the
   recommended way to update a schema.  Certains kinds of changes may result in a slow sync of all
   clients synchronizing the constituent entities and relationships, however.  It depends on whether
   there is any overlap between the property and relationship descriptions which have changed with the
   properties and relationships supported by the client.  Changing a schema has serious implications for
   the clients synchronizing it - changes should not be undertaken lightly. */
- (BOOL)registerSchemaWithBundlePath:(NSString *)bundlePath;

- (void)unregisterSchemaWithName:(NSString *)schemaName;


/* Return a snapshot of the records in the Truth.  The Truth stores a copy of all synchronized records
   and contains the amalgamation of all properties from all clients.

   The snapshot is an immutable copy of the records, taken at the time you request it.  If the Truth is
   subsequently modified, the changes will not be reflected in the snapshot.  You can always ask for a
   new shapshot if you want an up-to-date copy.

   Do not use this method if you are syncing and want a snapshot of the Truth that is consistent with the
   sync session.  Another client may have mutated the Truth after the engine prepared your changes but
   before you ask for the snapshot.  If that happens, the records in this snapshot will not match the
   state in the session.  Use the method on ISyncSession instead. */
- (ISyncRecordSnapshot *)snapshotOfRecordsInTruthWithEntityNames:(NSArray /* NSString */ *)entityNames usingIdentifiersForClient:(ISyncClient *)client;

@end

/* Distributed notification posted by the server when availability/enablement changes.
   If isEnabled returns NO, and a client wants to sync when syncing becomes enabled
   again, the client should register for this notification. 

   This notification is sent both in the case where syncing is enabled, and when it is disabled.
   When this notification is sent, the object of the notification is an NSString with the value @"YES"
   if syncing is enabled, and @"NO" if disabled. After receiving this notification, the client should
   still call -isEnabled to be absolutely sure of the state of syncing. 
*/
SYNCSERVICES_EXPORT NSString * const ISyncAvailabilityChangedNotification;

/* Exception raised when communication to the server is lost. The reason is a string aggregating
   the name, reason, and user info from the originating exception.
*/
SYNCSERVICES_EXPORT NSString * const ISyncServerUnavailableException;
