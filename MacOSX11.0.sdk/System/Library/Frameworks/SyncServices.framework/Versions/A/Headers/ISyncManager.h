/*
 * SyncServices -- ISyncManager.h
 * Copyright (c) 2003 - 2008 Apple Computer, Inc.  All rights reserved.
 */

#import <Foundation/Foundation.h>
#import <SyncServices/ISyncCommon.h>

@class ISyncClient, ISyncRecordSnapshot;



/* ISyncManager is the starting point for clients looking to manage clients and syncs.  It
   provides methods to register new clients, look up and remove registered clients, and schedule
   syncs. */

@interface ISyncManager : NSObject

+ (ISyncManager *) sharedManager NS_DEPRECATED_MAC(10_4, 10_7);

/* Check if the Sync Engine is enabled and available for syncing. */
- (BOOL)isEnabled NS_DEPRECATED_MAC(10_4, 10_7);

/* After calling isEnabled, this method will return an NSError with one of the codes enumerated below. The returned NSError will have
   an info dictionary with an entry for the NSLocalizedDescriptionKey. The value of this key will be a string describing the disabled reason
   that is suitable for display. The error codes are declared in SyncServicesErrors.h.
   ISyncServerDisabledReasonNone,               Returned when isEnabled has returned YES.
   ISyncServerDisabledReasonByPreference,       Returned if syncing has been disabled with a preference
   ISyncServerDisabledReasonSharedNetworkHome,  Returned if another sync server is running against a network home directory.
   ISyncServerDisabledReasonUnresponsive,	    Returned if isEnabled has timed out messaging to the Sync Server  
   ISyncServerDisabledReasonUnknown,            Returned if the Sync Server fails to respond because of an unexpected error.
*/
- (NSError *)syncDisabledReason NS_DEPRECATED_MAC(10_4, 10_7);

- (ISyncClient *)clientWithIdentifier:(NSString *)clientId NS_DEPRECATED_MAC(10_4, 10_7);

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

      NeverFormatsRelationships - This is deprecated on 10.6, see FormatsRelationships.

      FormatsRelationships - a Boolean that indicates that this client MIGHT format
      a relationship that it pulls. On 10.6 we have changed the default sense for clients
      and assume that they DO NOT format relationships.
      
      SyncsWith - a dictionary specifying the kinds of clients this client wants to sync
      with.  See -setShouldSynchronize:withClientsOfType: for details.  The dictionary contains the
      following keys:

         SyncAlertTypes - an array of the client types this client wants to sync with.

         SyncAlertToolPath - the path of a tool the engine will invoke when a client of
         the specified type starts syncing.  The tool can be passed multiple arguments on
         the command line.  At a minimum it will be passed "--sync" followed by the
         client's client id. It may also be passed "--entitynames" followed by a comma
         delimited list of entity names being synced. Any other arguments on the command
         line should be ignored. In particular, tools should be prepared to handle options
         on the command line that are not followed by a value. Options are always prefixed
         by --. Options and values are always delimited by spaces. In 10.6 one no value
         option that is sometimes passed to an alert tool is --oneshot.

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
- (ISyncClient *)registerClientWithIdentifier:(NSString *)clientId descriptionFilePath:(NSString *)descriptionFilePath NS_DEPRECATED_MAC(10_4, 10_7);

/* Remove a previously registered client */
- (void)unregisterClient:(ISyncClient *)client NS_DEPRECATED_MAC(10_4, 10_7);

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

    * MajorVersion an integer value numbered representing the major version of this schema. Schemas with different major
      numbers are used to indicate a major incompatible change. Including version information is optional
      but recommended. In future releases this information may be used for validation and to assist with schema migration.

    * MinorVersion an integer value number representing the minor version of this schema. Schemas with different minor
      numbers are used to indicate compatible schema changes. (Optional)

    * BaseName the name of a schema that this schema is extending. (Optional, used with BaseMajorVersion and BaseMinorVersion.)

    * BaseMajorVersion an integer value representing the major version of the schema that this schema is extending. (Optional. See BaseName.)

    * BaseMinorVersion an integer value representing the minor version of the schema that this schema is extending. (Optional. See BaseName.)

	* StrictParsing - a bool that allows opting in / out of the new strict validation of schemas in Leopard. This is a top level key in a schema.
	  If this value is true, Leopard strict validation will be used.
	  If this value is false, the same checking as under Tiger will be used.
	  If this value is not present, it will be based on the version of the SyncServices framework the registering binary linked against.  
	  If it linked against a Leopard framework version, strict validation will be used.
	  
    * DataClasses - an array containing various data class descriptions.  The data class
      description contains the following:

         Name - the name of the data class.  This key is required.  We recommend using the reverse-DNS
         naming scheme, e.g., "com.apple.Contacts". The name can be localized using the strings from Schema.strings
	     in the .syncschema bundle.

         ImagePath - the path of an image representing the data class.  For most data classes this
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
            for example the key for the attribute with the Name "title" in the entity with the name
            "com.apple.things.Thing" would be "com.apple.things.Thing/title".

            Type - the type of the attribute.  Must be one of the valid attribute
            types, such as string, number, etc. On 10.6 set is also a supported type.
            
            ExcludeFromDataChangeAlert - <true/> or <false/>.  Defaults to false if omitted.  If this flag is set then
            a change to this attribute will not count towards the number of changed attributes for the purpose
            of displaying the data change alert.

            AutomaticConflictResolutionPolicy - A dictionary with one or two entries with the keys
            "PreferredClientTypes" and "PreferredRecord". The use of this keyword can help prevent conflicts.
            The value for the PreferredClientType entry is an array comprised of the client type strings e.g.,
            "app", "device", "server" and "peer".  The value for the PreferredRecord key is one of "Truth", "Client", or
            "LastModified". This property is per attribute and cannot be declared as a property of the
            Entity. One of the more common uses is to specify that the last modified value should alway be
            chosen. In this case, the PreferredClientTypes entry should be omitted. If both keys are specified,
            then they must be consistent with each other. In other words, if a client specifies a value for
            PreferredClientTypes of [app] and a PreferredRecord of LastModified, then the client that pushed the
            conflicting change that last modified the attribute must be of type app or a conflict will be
            generated.

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

            ExcludeFromDataChangeAlert - <true/> or <false/>.  Defaults to false if omitted.  If this flag is set then
            a change to this relationship will not count towards the number of changed relationships for the purpose
            of displaying the data change alert.


         IdentityProperties - an array specifying the set of property names that are used to match a new
         record from a Sync client with an existing record. If the target of a one to one relationship
         is to be used, the name of the relationship is specified. 

         CompoundIdentityProperties - an array of array of property names. If a schema specifies both this
         and the IdentityProperties key, this key is preferred. When a record is pushed, a match is
         searched by using the identity keys declared in each of the sub-arraya in the order that they
         appear. This means that the arrays should not have property names in common. For example, the
         Contacts schema now declares its identity keys as [[first name, middle name, last name],
         [company name]]. This allows a contact pushed without a company name to match a record that
         was previously pushed with the same first and last name along with a company name.

         PropertyDependencies - an array specifying the set of dependencies between the
         properties.  A dependent property is one which must be pushed to a client if any of its
         dependencies are changed.  Each entry in the array is itself an array of strings, specifying
         the names of the co-dependent properties.  Entries may only include attribute names. Relationship
         names are disallowed.

         Parent - the name of a relationship back to the parent for this entity. A parent is an enclosing
         entity type which is used to bill changes for data change alerts and to house child records in the
         conflict manager display. As an example, a contact is the parent of a phone number. If there is a
         change to a phone number (or if a phone number is added or deleted), that will count as a change
         to the parent contact, rather than a change to the phone number. If there is a conflict on a
         phone number, it will appear as if the parent contact is in conflict, not the phone number. Not
         all contained objects have a parent - for example although a bookmark is contained in a folder,
         the folder is not considered the parent of the bookmark. The parent is used when a record is really
         a "part" of an enclosing record, such as the phone number which is a "part" of a contact.
    
	* Comment - used to insert optional comments to document the schema.
	
    * ManagedObjectModels - an array containing paths to one or more CoreData managed object models (.mom files).
        Relative paths are resolved against the .syncschema bundle's Resources directory.  As a special case, 
        you can specify a path like "../../../foo.mom" to load a model that lives outside the schema bundle 
        (eg. in the application's Resources directory).
        This registers every entity, attribute and relationship in the managed object model with Sync Services.  
        (Entity extensions cannot be specified in a model file.)  Information specific to Sync Services is specified 
        in the entity or property's 'User Info' dictionary:
 
        Entity User Info:
            "com.apple.syncservices.SyncName" - the value is a string specifying the name the entity will be 
            registered as with Sync Services.  Clients must use this name when refering to this entity.  
            The "sync" name may be different from the entity's name: Sync Services uses a global name space 
            for entities and to avoid collisions, we recommend a reverse-DNS naming scheme, 
            eg. "com.apple.contacts.Contact".  Names with '.'s in them don't work too well with CoreData, 
            so this key lets you specify a globally unique name for the entity.
            This key is optional.  If it's not specified, Sync Services tries to construct a unique name for 
            the entity: if the entity name has a '.' in it, we use that directly; otherwise, we catenate the 
            entity's data class name with the entity's name, separated by a '.'  eg. a "Contact" entity in 
            the "com.apple.contacts" data class would be registered with Sync Services as "com.apple.contacts.Contact" 
            
            "com.apple.syncservices.DataClass" - the value is a string specifying the name of the entity's data class.
            This key is required.
 
            "com.apple.syncservices.Parent" - the value is a string specifying the name of a relationship 
            back to the parent for this entity. A parent is an enclosing entity type which is used to bill changes for 
            data change alerts and to house child records in the conflict manager display. As an example, a contact is 
            the parent of a phone number. If there is a change to a phone number (or if a phone number is added or deleted), 
            that will count as a change to the parent contact, rather than a change to the phone number. If there is a 
            conflict on a  phone number, it will appear as if the parent contact is in conflict, not the phone number. 
            Not all contained objects have a parent - for example although a bookmark is contained in a folder,
            the folder is not considered the parent of the bookmark. The parent is used when a record is really
            a "part" of an enclosing record, such as the phone number which is a "part" of a contact.
 
            "com.apple.syncservices.Syncable" - "YES" or "NO". Defaults to "YES" if omitted. If this flag is set to "NO"
            then the entity will not be parsed and thus not synchronized.
 
            "com.apple.syncservices.ExcludeFromDataChangeAlert" - "YES" or "NO". Defaults to "NO" if omitted. 
            If this flag is set to "YES" then a change to this entity will not count towards the number of changed 
            entities for the purpose of displaying the data change alert.
 
            "com.apple.syncservices.IdentityProperties" - an array of array of strings (no, that's not a typo) specifying
            the properties that are used to match a new record from a sync client with an existing record.  Properties
            are identified by name, eg "((property1, property2, property3))".  At this time, only the first array of strings
            is used and any subsequent arrays are quietly ignored.
 
        Attribute and Relationship User Info: 
            "com.apple.syncservices.Syncable" - "YES" or "NO". Defaults to "YES" if omitted. If this flag is set to "NO"
            then the attribute / relationship will not be parsed and thus not synchronized.
 
            "com.apple.syncservices.ExcludeFromDataChangeAlert" - "YES" or "NO". Defaults to "NO" if omitted. If this flag
            is set to "YES" then a change to this attribute / relationship will not count towards the number of changed 
            entities for the purpose of displaying the data change alert.
 
   It is perfectly valid to call this method for a schema that has already been registered.  It is the
   recommended way to update a schema.  Certains kinds of changes may result in a slow sync of all
   clients synchronizing the constituent entities and relationships, however.  It depends on whether
   there is any overlap between the property and relationship descriptions which have changed with the
   properties and relationships supported by the client.  Changing a schema has serious implications for
   the clients synchronizing it - changes should not be undertaken lightly. */
- (BOOL)registerSchemaWithBundlePath:(NSString *)bundlePath NS_DEPRECATED_MAC(10_4, 10_7);

- (void)unregisterSchemaWithName:(NSString *)schemaName NS_DEPRECATED_MAC(10_4, 10_7);

/* This API is for sync clients that will only sync when another client, not of type application, is syncing
 * the same entities. This is NOT the preferred way that clients should sync their changes. However, for
 * various reasons, sometimes it is the only viable option. This API has been introduced in In 10.6, because
 * some clients, such as MobileMe, may no longer sync if they determine they have no changes to push or pull.
 * This API allows clients to indicate that they have changes to sync without the overhead of creating a sync
 * session. Clients that use this API, will always be alerted to sync whenever a client they sync with
 * requests a sync session, even if the requesting client would otherwise have no changes to push or
 * pull. Clients that trickle sync or push their changes periodically on their own should not call this
 * method.
 */
- (void)clientWithIdentifier:(NSString *)clientId needsSyncing:(BOOL)flag NS_DEPRECATED_MAC(10_6, 10_7);

/* Return a snapshot of the records in the Truth.  The Truth stores a copy of all synchronized records
   and contains the amalgamation of all properties from all clients.

   The snapshot is an immutable copy of the records, taken at the time you request it.  If the Truth is
   subsequently modified, the changes will not be reflected in the snapshot.  You can always ask for a
   new shapshot if you want an up-to-date copy.

   Do not use this method if you are syncing and want a snapshot of the Truth that is consistent with the
   sync session.  Another client may have mutated the Truth after the engine prepared your changes but
   before you ask for the snapshot.  If that happens, the records in this snapshot will not match the
   state in the session.  Use the method on ISyncSession instead. */
- (ISyncRecordSnapshot *)snapshotOfRecordsInTruthWithEntityNames:(NSArray /* NSString */ *)entityNames usingIdentifiersForClient:(ISyncClient *)client NS_DEPRECATED_MAC(10_4, 10_7);

/* Clients that register sync alert handlers may use the following three methods to manage the request modes
   of the connections that are sent alerts by the sync server. (These request modes are simply the runloop modes
   of the runloop that  is servicing the connection's sync alerts.) The API mirrors that of NSConnection. For
   example, a client that registers a sync alert handler in a process that might present a modal dialog to the
   user should add the appropriate request mode of the loop, so alerts can be handled in a timely manner even
   when the application is blocked for user input. */
- (void)addRequestMode:(NSString *)mode NS_DEPRECATED_MAC(10_4, 10_7);
- (void)removeRequestMode:(NSString *)mode NS_DEPRECATED_MAC(10_4, 10_7);
- (NSArray *)requestModes NS_DEPRECATED_MAC(10_4, 10_7);

@end

/* Distributed notification and task specific notification posted by the server when availability/enablement changes.
   If isEnabled returns NO, and a client wants to sync when syncing becomes enabled again, the client should register
   for this notification. 

   This notification is sent both in the case where syncing is enabled, and when it is disabled.
   When this notification is sent, the object of the notification is an NSString with the value @"YES"
   if syncing is enabled, and @"NO" if disabled. After receiving this notification, the client should
   still call -isEnabled to be absolutely sure of the state of syncing.

   For clients that use an ISyncManager they should register with the NSNotificationCenter not the NSDistributedNotificationCenter.
*/
SYNCSERVICES_EXPORT NSString * const ISyncAvailabilityChangedNotification NS_DEPRECATED_MAC(10_4, 10_7);

/* Exception raised when communication to the server is lost. The reason is a string aggregating
   the name, reason, and user info from the originating exception.
*/
SYNCSERVICES_EXPORT NSString * const ISyncServerUnavailableException NS_DEPRECATED_MAC(10_4, 10_7);


