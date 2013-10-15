/*
    NSPersistentStoreCoordinator.h
    Core Data
    Copyright (c) 2004-2010 Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSLock.h>
#import <CoreData/CoreDataDefines.h>

#if MAC_OS_X_VERSION_MAX_ALLOWED < MAC_OS_X_VERSION_10_5
#ifndef NSPersistentStore
#define NSPersistentStore NSObject
#endif
#endif

@class NSArray;
@class NSMutableArray;
@class NSDictionary;
@class NSError;
@class NSManagedObjectID;
@class NSManagedObjectModel;
@class NSPersistentStore;
@class NSMutableDictionary;
@class NSString;
@class NSURL;
@class NSPersistentStoreRequest;

// Persistent store types supported by Core Data:
COREDATA_EXTERN NSString * const NSSQLiteStoreType NS_AVAILABLE(10_4, 3_0);
COREDATA_EXTERN NSString * const NSXMLStoreType NS_AVAILABLE(10_4, NA);
COREDATA_EXTERN NSString * const NSBinaryStoreType NS_AVAILABLE(10_4, 3_0);
COREDATA_EXTERN NSString * const NSInMemoryStoreType NS_AVAILABLE(10_4, 3_0);

// Persistent store metadata dictionary keys:

// key in the metadata dictionary to identify the store type
COREDATA_EXTERN NSString * const NSStoreTypeKey NS_AVAILABLE(10_4, 3_0);    

// key in the metadata dictionary to identify the store UUID - the store UUID is useful to identify stores through URI representations, but it is NOT guaranteed to be unique (while the UUID generated for new stores is unique, users can freely copy files and thus the UUID stored inside, so developers that track/reference stores explicitly do need to be aware of duplicate UUIDs and potentially override the UUID when a new store is added to the list of known stores in their application)
COREDATA_EXTERN NSString * const NSStoreUUIDKey NS_AVAILABLE(10_4, 3_0);    

// user info dictionary contains information about the stores that were added or removed
COREDATA_EXTERN NSString * const NSPersistentStoreCoordinatorStoresDidChangeNotification NS_AVAILABLE(10_4, 3_0);    

// sent during the invocation of NSPersistentStore's willRemoveFromPersistentStoreCoordinator during store deallocation or removal
COREDATA_EXTERN NSString * const NSPersistentStoreCoordinatorWillRemoveStoreNotification NS_AVAILABLE(10_5, 3_0);    

// User info keys for NSPersistentStoreCoordinatorStoresDidChangeNotification:

// The object values for NSAddedPersistentStoresKey and NSRemovedPersistentStoresKey will be arrays containing added/removed stores
COREDATA_EXTERN NSString * const NSAddedPersistentStoresKey NS_AVAILABLE(10_4, 3_0);
COREDATA_EXTERN NSString * const NSRemovedPersistentStoresKey NS_AVAILABLE(10_4, 3_0);

// The object value for NSUUIDChangedPersistentStoresKey will be an array where the object at index 0 will be the old store instance, and the object at index 1 the new
COREDATA_EXTERN NSString * const NSUUIDChangedPersistentStoresKey NS_AVAILABLE(10_4, 3_0);

// Persistent store option keys:

// flag indicating whether a store is treated as read-only or not - default is NO
COREDATA_EXTERN NSString * const NSReadOnlyPersistentStoreOption NS_AVAILABLE(10_4, 3_0);    

// flag indicating whether an XML file should be validated with the DTD while opening - default is NO
COREDATA_EXTERN NSString * const NSValidateXMLStoreOption NS_AVAILABLE(10_4, NA);    

// Migration keys:

/* Options key specifying the connection timeout for Core Data stores.  This value (an NSNumber) represents the duration, in seconds, Core Data will wait while attempting to create a connection to a persistent store.  If a connection is unable to be made within that timeframe, the operation is aborted and an error is returned.  
*/
COREDATA_EXTERN NSString * const NSPersistentStoreTimeoutOption NS_AVAILABLE(10_5, 3_0);

/* Options key for a dictionary of sqlite pragma settings with pragma values indexed by pragma names as keys.  All pragma values must be specified as strings.  The fullfsync and synchronous pragmas control the tradeoff between write performance (write to disk speed & cache utilization) and durability (data loss/corruption sensitivity to power interruption).  For more information on pragma settings visit <http://sqlite.org/pragma.html>
*/
COREDATA_EXTERN NSString * const NSSQLitePragmasOption NS_AVAILABLE(10_5, 3_0);

/* Option key to run an analysis of the store data to optimize indices based on statistical information when the store is added to the coordinator.  This invokes SQLite's ANALYZE command.  Ignored by other stores.
*/
COREDATA_EXTERN NSString * const NSSQLiteAnalyzeOption NS_AVAILABLE(10_5, 3_0);

/* Option key to rebuild the store file, forcing a database wide defragmentation when the store is added to the coordinator.  This invokes SQLite's VACUUM command.  Ignored by other stores.
 */
COREDATA_EXTERN NSString * const NSSQLiteManualVacuumOption NS_AVAILABLE(10_6, 3_0);

/* Options key to ignore the built-in versioning provided by Core Data.  If the value for this key (an NSNumber) evaluates to YES (using boolValue), Core Data will not compare the version hashes between the managed object model in the coordinator and the metadata for the loaded store.  (It will, however, continue to update the version hash information in the metadata.)  This key is specified by default for all applications linked on or before Mac OS X 10.4.
*/
COREDATA_EXTERN NSString * const NSIgnorePersistentStoreVersioningOption NS_AVAILABLE(10_5, 3_0);

/* Options key to automatically attempt to migrate versioned stores.  If the value for this key (an NSNumber) evaluates to YES (using boolValue) Core Data will, if the version hash information for added store is determined to be incompatible with the model for the coordinator, attempt to locate the source and mapping models in the application bundles, and perform a migration.  
*/
COREDATA_EXTERN NSString * const NSMigratePersistentStoresAutomaticallyOption NS_AVAILABLE(10_5, 3_0);

/* When combined with NSMigratePersistentStoresAutomaticallyOption, coordinator will attempt to infer a mapping model if none can be found */
COREDATA_EXTERN NSString * const NSInferMappingModelAutomaticallyOption NS_AVAILABLE(10_6, 3_0);

/* Key to represent the version hash information (dictionary) for the model used to create a persistent store.  This key is used in the metadata for a persistent store.
*/
COREDATA_EXTERN NSString * const NSStoreModelVersionHashesKey NS_AVAILABLE(10_5, 3_0);    

/* Key to represent the version identifier for the model used to create the store. This key is used in the metadata for a persistent store.
*/
COREDATA_EXTERN NSString * const NSStoreModelVersionIdentifiersKey NS_AVAILABLE(10_5, 3_0);    

/* Key to represent the earliest version of MacOS X the persistent store should support.  Backward compatibility may preclude some features.  The numeric values are defined in AvailabilityMacros.h
*/
COREDATA_EXTERN NSString * const NSPersistentStoreOSCompatibility NS_AVAILABLE(10_5, 3_0);    

// Spotlight indexing and external record support keys

/* Values to be passed with NSExternalRecordsFileFormatOption indicating the format used when writing external records. 
   The files are serialized dictionaries. 
*/
COREDATA_EXTERN NSString * const NSXMLExternalRecordType NS_AVAILABLE(10_6, NA);
COREDATA_EXTERN NSString * const NSBinaryExternalRecordType NS_AVAILABLE(10_6, NA);

/* option indicating the file format used when writing external records.The default is NSXMLExternalRecordType if this options isn't specified. */
COREDATA_EXTERN NSString * const NSExternalRecordsFileFormatOption NS_AVAILABLE(10_6, NA);

/* option indicating the directory URL where external records are stored. External records are files that can be used by 
   Spotlight to index the contents of the store. They can also contain a serialized dictionary representation of the instances.
   The location specified with this option must be somewhere under the path ~/Library/Caches/Metadata/CoreData or ~/Library/CoreData
   This option must be set together with NSExternalRecordExtensionOption
*/
COREDATA_EXTERN NSString * const NSExternalRecordsDirectoryOption NS_AVAILABLE(10_6, NA);

/* option indicating the extension used in the external record files. This option must be set together with NSExternalRecordsDirectoryOption */
COREDATA_EXTERN NSString * const NSExternalRecordExtensionOption NS_AVAILABLE(10_6, NA);    

/* Dictionary key for the entity name extracted from an external record file URL */
COREDATA_EXTERN NSString * const NSEntityNameInPathKey NS_AVAILABLE(10_6, NA);    

/* Dictionary key for the store UUID extracted from an external record file URL */
COREDATA_EXTERN NSString * const NSStoreUUIDInPathKey NS_AVAILABLE(10_6, NA);    

/* Dictionary key for the store URL extracted from an external record file URL */
COREDATA_EXTERN NSString * const NSStorePathKey NS_AVAILABLE(10_6, NA);    

/* Dictionary key for the managed object model URL extracted from an external record file URL */
COREDATA_EXTERN NSString * const NSModelPathKey NS_AVAILABLE(10_6, NA);    

/* Dictionary key for the object URI extracted from an external record file URL */
COREDATA_EXTERN NSString * const NSObjectURIKey NS_AVAILABLE(10_6, NA);

/* option indicating that a persistent store has a given name in ubiquity, this option is required for ubiquity to function  */
COREDATA_EXTERN NSString * const NSPersistentStoreUbiquitousContentNameKey NS_AVAILABLE(10_7, NA);    

/* option indicating the log path to use for ubiquity logs, this option is optional for ubiquity, a default path will be generated for the store if none is provided */
COREDATA_EXTERN NSString * const NSPersistentStoreUbiquitousContentURLKey NS_AVAILABLE(10_7, NA);

/* Notification sent after records are imported from the ubiquity store. The notification is sent with the object set to the NSPersistentStoreCoordinator instance which registered the store. */
COREDATA_EXTERN NSString * const NSPersistentStoreDidImportUbiquitousContentChangesNotification NS_AVAILABLE(10_7, NA);

NS_CLASS_AVAILABLE(10_4, 3_0)
@interface NSPersistentStoreCoordinator : NSObject <NSLocking> {
@private
    struct _persistentStoreCoordinatorFlags {
        unsigned int _isRegistered:1;
        unsigned int _reservedFlags:31;
    } _flags;
#ifdef __LP64__
	uint32_t _reserved32;
#endif
    void *_reserved;
    NSMutableArray *_extendedStoreURLs;
    id _externalRecordsHelper;
    NSManagedObjectModel *_managedObjectModel;
    id _coreLock;
    NSMutableArray *_persistentStores;
}

/* Returns a dictionary of the registered store types:  the keys are the store type strings and the values are the NSPersistentStore subclasses wrapped in NSValues.
*/

+ (NSDictionary *)registeredStoreTypes NS_AVAILABLE(10_5, 3_0);

/* Registers the specified NSPersistentStore subclass for the specified store type string.  This method must be invoked before a custom subclass of NSPersistentStore can be loaded into a persistent store coordinator.  Passing nil for the store class argument will unregister the specified store type.
*/
+ (void)registerStoreClass:(Class)storeClass forStoreType:(NSString *)storeType NS_AVAILABLE(10_5, 3_0);

/* Allows to access the metadata stored in a persistent store without warming up a CoreData stack; the guaranteed keys in this dictionary are NSStoreTypeKey and NSStoreUUIDKey. If storeType is nil, Core Data will guess which store class should be used to get/set the store file's metadata. 
 */
+ (NSDictionary *)metadataForPersistentStoreOfType:(NSString *)storeType URL:(NSURL *)url error:(NSError **)error NS_AVAILABLE(10_5, 3_0); 
+ (BOOL)setMetadata:(NSDictionary *)metadata forPersistentStoreOfType:(NSString *)storeType URL:(NSURL*)url error:(NSError **)error NS_AVAILABLE(10_5, 3_0);

/* Takes a URL to an external record file file and returns a dictionary with the derived elements
  The keys in the dictionary are
        NSEntityNameInPathKey - the name of the entity for the managed object instance
        NSStoreUUIDInPathKey - UUID of the store containing the instance
        NSStorePathKey - path to the store file (this is resolved to the store-file path contained in the support directory)
        NSModelPathKey - path to the model file (this is resolved to the model.mom path contained in the support directory)
        NSObjectURIKey - URI of the object instance.
*/
+ (NSDictionary *)elementsDerivedFromExternalRecordURL:(NSURL *)fileURL NS_AVAILABLE(10_6, NA);

/* Creates and populates a store with the external records found at externalRecordsURL. The store is written to destinationURL using
    options and with type storeType. If storeIdentifier is nil, the records for a single store at externalRecordsURL at imported.
    externalRecordsURL must not exist as the store will be created from scratch (no appending to an existing store is allowed).
*/
- (NSPersistentStore *)importStoreWithIdentifier:(NSString *)storeIdentifier fromExternalRecordsDirectory:(NSURL *)externalRecordsURL toURL:(NSURL *)destinationURL options:(NSDictionary *)options withType:(NSString *)storeType error:(NSError **)error NS_AVAILABLE(10_6, NA);

/* Sets the metadata stored in the persistent store during the next save operation executed on it; the store type and UUID (NSStoreTypeKey and NSStoreUUIDKey) are always added automatically (but NSStoreUUIDKey is only added if it is not set manually as part of the dictionary argument) 
*/
- (void)setMetadata:(NSDictionary *)metadata forPersistentStore:(NSPersistentStore *)store;    

/* Returns the metadata currently stored or to-be-stored in the persistent store
*/
- (NSDictionary *)metadataForPersistentStore:(NSPersistentStore *)store;    

- (id)initWithManagedObjectModel:(NSManagedObjectModel *)model;

- (NSManagedObjectModel *)managedObjectModel;

- (NSArray *)persistentStores;
- (NSPersistentStore *)persistentStoreForURL:(NSURL *)URL;
- (NSURL *)URLForPersistentStore:(NSPersistentStore *)store;

/* Sets the URL for the specified store in the coordinator.  For atomic stores, this will alter the location to which the next save operation will persist the file;  for non-atomic stores, invoking this method will release the existing connection and create a new one at the specified URL.  (For non-atomic stores, a store must pre-exist at the destination URL; a new store will not be created.) 
*/
- (BOOL)setURL:(NSURL*)url forPersistentStore:(NSPersistentStore *)store NS_AVAILABLE(10_5, 3_0);    

/* Adds the store at the specified URL (of the specified type) to the coordinator with the model configuration and options.  The configuration can be nil -- then it's the complete model; storeURL is usually the file location of the database 
*/
- (NSPersistentStore *)addPersistentStoreWithType:(NSString *)storeType configuration:(NSString *)configuration URL:(NSURL *)storeURL options:(NSDictionary *)options error:(NSError **)error;    
- (BOOL)removePersistentStore:(NSPersistentStore *)store error:(NSError **)error;


/* Used for save as - performance may vary depending on the type of old and new store; the old store is usually removed from the coordinator by the migration operation, and therefore is no longer a useful reference after invoking this method 
*/
- (NSPersistentStore *)migratePersistentStore:(NSPersistentStore *)store toURL:(NSURL *)URL options:(NSDictionary *)options withType:(NSString *)storeType error:(NSError **)error;    

/* Given a URI representation of an object ID, returns an object ID if a matching store is available or nil if a matching store cannot be found (the URI representation contains a UUID of the store the ID is coming from, and the coordinator can match it against the stores added to it) 
*/
- (NSManagedObjectID *)managedObjectIDForURIRepresentation:(NSURL *)url;    

/* Sends a request to all of the stores associated with this coordinator. 
   Returns an array if successful,  nil if not.
   The contents of the array will vary depending on the request type: NSFetchRequest results will be an array of managed objects, managed object IDs, or NSDictionaries;  
   NSSaveChangesRequests will an empty array. User defined requests will return arrays of arrays, where the nested array is the result returned form a single store.
 */
- (id)executeRequest:(NSPersistentStoreRequest *)request withContext:(NSManagedObjectContext *)context error:(NSError**)error NS_AVAILABLE(10_7, NA);

- (void)lock;
- (void)unlock;
- (BOOL)tryLock;

/*
    Deprecated
 */
+ (NSDictionary *)metadataForPersistentStoreWithURL:(NSURL *)url error:(NSError **)error NS_DEPRECATED_MAC(10_4,10_5);

@end
