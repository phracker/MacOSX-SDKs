/*
    NSPersistentStoreCoordinator.h
    Core Data
    Copyright (c) 2004-2009 Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSLock.h>

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

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

// Persistent store types supported by Core Data:
COREDATA_EXTERN NSString * const NSSQLiteStoreType;
COREDATA_EXTERN NSString * const NSXMLStoreType;
COREDATA_EXTERN NSString * const NSBinaryStoreType;
COREDATA_EXTERN NSString * const NSInMemoryStoreType;

// Persistent store metadata dictionary keys:

// key in the metadata dictionary to identify the store type
COREDATA_EXTERN NSString * const NSStoreTypeKey;    

// key in the metadata dictionary to identify the store UUID - the store UUID is useful to identify stores through URI representations, but it is NOT guaranteed to be unique (while the UUID generated for new stores is unique, users can freely copy files and thus the UUID stored inside, so developers that track/reference stores explicitly do need to be aware of duplicate UUIDs and potentially override the UUID when a new store is added to the list of known stores in their application)
COREDATA_EXTERN NSString * const NSStoreUUIDKey;    

// user info dictionary contains information about the stores that were added or removed
COREDATA_EXTERN NSString * const NSPersistentStoreCoordinatorStoresDidChangeNotification;    

// sent during the invocation of NSPersistentStore's willRemoveFromPersistentStoreCoordinator during store deallocation or removal
COREDATA_EXTERN NSString * const NSPersistentStoreCoordinatorWillRemoveStoreNotification AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;    

// User info keys for NSPersistentStoreCoordinatorStoresDidChangeNotification:

// The object values for NSAddedPersistentStoresKey and NSRemovedPersistentStoresKey will be arrays containing added/removed stores
COREDATA_EXTERN NSString * const NSAddedPersistentStoresKey;
COREDATA_EXTERN NSString * const NSRemovedPersistentStoresKey;

// The object value for NSUUIDChangedPersistentStoresKey will be an array where the object at index 0 will be the old store instance, and the object at index 1 the new
COREDATA_EXTERN NSString * const NSUUIDChangedPersistentStoresKey;

// Persistent store option keys:

// flag indicating whether a store is treated as read-only or not - default is NO
COREDATA_EXTERN NSString * const NSReadOnlyPersistentStoreOption;    

// flag indicating whether an XML file should be validated with the DTD while opening - default is NO
COREDATA_EXTERN NSString * const NSValidateXMLStoreOption;    

// Migration keys:

/* Options key specifying the connection timeout for Core Data stores.  This value (an NSNumber) represents the duration, in seconds, Core Data will wait while attempting to create a connection to a persistent store.  If a connection is unable to be made within that timeframe, the operation is aborted and an error is returned.  
*/
COREDATA_EXTERN NSString * const NSPersistentStoreTimeoutOption AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* Options key for a dictionary of sqlite pragma settings with pragma values indexed by pragma names as keys.  All pragma values must be specified as strings.  The fullfsync and synchronous pragmas control the tradeoff between write performance (write to disk speed & cache utilization) and durability (data loss/corruption sensitivity to power interruption).  For more information on pragma settings visit <http://sqlite.org/pragma.html>
*/
COREDATA_EXTERN NSString * const NSSQLitePragmasOption AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* Option key to run an analysis of the store data to optimize indices based on statistical information when the store is added to the coordinator.  This invokes SQLite's ANALYZE command.  Ignored by other stores.
*/
COREDATA_EXTERN NSString * const NSSQLiteAnalyzeOption AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* Option key to rebuild the store file, forcing a database wide defragmentation when the store is added to the coordinator.  This invokes SQLite's VACUUM command.  Ignored by other stores.
 */
COREDATA_EXTERN NSString * const NSSQLiteManualVacuumOption AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* Options key to ignore the built-in versioning provided by Core Data.  If the value for this key (an NSNumber) evaluates to YES (using boolValue), Core Data will not compare the version hashes between the managed object model in the coordinator and the metadata for the loaded store.  (It will, however, continue to update the version hash information in the metadata.)  This key is specified by default for all applications linked on or before Mac OS X 10.4.
*/
COREDATA_EXTERN NSString * const NSIgnorePersistentStoreVersioningOption AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* Options key to automatically attempt to migrate versioned stores.  If the value for this key (an NSNumber) evaluates to YES (using boolValue) Core Data will, if the version hash information for added store is determined to be incompatible with the model for the coordinator, attempt to locate the source and mapping models in the application bundles, and perform a migration.  
*/
COREDATA_EXTERN NSString * const NSMigratePersistentStoresAutomaticallyOption AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* When combined with NSMigratePersistentStoresAutomaticallyOption, coordinator will attempt to infer a mapping model if none can be found */
COREDATA_EXTERN NSString * const NSInferMappingModelAutomaticallyOption AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* Key to represent the version hash information (dictionary) for the model used to create a persistent store.  This key is used in the metadata for a persistent store.
*/
COREDATA_EXTERN NSString * const NSStoreModelVersionHashesKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;    

/* Key to represent the version identifier for the model used to create the store. This key is used in the metadata for a persistent store.
*/
COREDATA_EXTERN NSString * const NSStoreModelVersionIdentifiersKey AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;    

/* Key to represent the earliest version of MacOS X the persistent store should support.  Backward compatibility may preclude some features.  The numeric values are defined in AvailabilityMacros.h
*/
COREDATA_EXTERN NSString * const NSPersistentStoreOSCompatibility AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;    

// Spotlight indexing and external record support keys

/* Values to be passed with NSExternalRecordsFileFormatOption indicating the format used when writing external records. 
   The files are serialized dictionaries. 
*/
COREDATA_EXTERN NSString * const NSXMLExternalRecordType AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
COREDATA_EXTERN NSString * const NSBinaryExternalRecordType AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* option indicating the file format used when writing external records.The default is NSXMLExternalRecordType if this options isn't specified. */
COREDATA_EXTERN NSString * const NSExternalRecordsFileFormatOption AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* option indicating the directory URL where external records are stored. External records are files that can be used by 
   Spotlight to index the contents of the store. They can also contain a serialized dictionary representation of the instances.
   The location specified with this option must be somewhere under the path ~/Library/Caches/Metadata/CoreData or ~/Library/CoreData
   This option must be set together with NSExternalRecordExtensionOption
*/
COREDATA_EXTERN NSString * const NSExternalRecordsDirectoryOption AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* option indicating the extension used in the external record files. This option must be set together with NSExternalRecordsDirectoryOption */
COREDATA_EXTERN NSString * const NSExternalRecordExtensionOption AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;    

/* Dictionary key for the entity name extracted from an external record file URL */
COREDATA_EXTERN NSString * const NSEntityNameInPathKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;    

/* Dictionary key for the store UUID extracted from an external record file URL */
COREDATA_EXTERN NSString * const NSStoreUUIDInPathKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;    

/* Dictionary key for the store URL extracted from an external record file URL */
COREDATA_EXTERN NSString * const NSStorePathKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;    

/* Dictionary key for the managed object model URL extracted from an external record file URL */
COREDATA_EXTERN NSString * const NSModelPathKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;    

/* Dictionary key for the object URI extracted from an external record file URL */
COREDATA_EXTERN NSString * const NSObjectURIKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;    

@interface NSPersistentStoreCoordinator : NSObject <NSLocking> {
@private
    void *_reserved;
    void *_reserved2;
    void *_reserved3;
    id _externalRecordsHelper;
    NSManagedObjectModel *_managedObjectModel;
    id _coreLock;
    NSMutableArray *_persistentStores;
}

/* Returns a dictionary of the registered store types:  the keys are the store type strings and the values are the NSPersistentStore subclasses wrapped in NSValues.
*/

+ (NSDictionary *)registeredStoreTypes AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* Registers the specified NSPersistentStore subclass for the specified store type string.  This method must be invoked before a custom subclass of NSPersistentStore can be loaded into a persistent store coordinator.  Passing nil for the store class argument will unregister the specified store type.
*/
+ (void)registerStoreClass:(Class)storeClass forStoreType:(NSString *)storeType AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* Allows to access the metadata stored in a persistent store without warming up a CoreData stack; the guaranteed keys in this dictionary are NSStoreTypeKey and NSStoreUUIDKey. If storeType is nil, Core Data will guess which store class should be used to get/set the store file's metadata. 
 */
+ (NSDictionary *)metadataForPersistentStoreOfType:(NSString *)storeType URL:(NSURL *)url error:(NSError **)error AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER; 
+ (BOOL)setMetadata:(NSDictionary *)metadata forPersistentStoreOfType:(NSString *)storeType URL:(NSURL*)url error:(NSError **)error AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* Takes a URL to an external record file file and returns a dictionary with the derived elements
  The keys in the dictionary are
        NSEntityNameInPathKey - the name of the entity for the managed object instance
        NSStoreUUIDInPathKey - UUID of the store containing the instance
        NSStorePathKey - path to the store file (this is resolved to the store-file path contained in the support directory)
        NSModelPathKey - path to the model file (this is resolved to the model.mom path contained in the support directory)
        NSObjectURIKey - URI of the object instance.
*/
+ (NSDictionary *)elementsDerivedFromExternalRecordURL:(NSURL *)fileURL AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* Creates and populates a store with the external records found at externalRecordsURL. The store is written to destinationURL using
    options and with type storeType. If storeIdentifier is nil, the records for a single store at externalRecordsURL at imported.
    externalRecordsURL must not exist as the store will be created from scratch (no appending to an existing store is allowed).
*/
- (NSPersistentStore *)importStoreWithIdentifier:(NSString *)storeIdentifier fromExternalRecordsDirectory:(NSURL *)externalRecordsURL toURL:(NSURL *)destinationURL options:(NSDictionary *)options withType:(NSString *)storeType error:(NSError **)error AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

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
- (BOOL)setURL:(NSURL*)url forPersistentStore:(NSPersistentStore *)store AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;    

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

- (void)lock;
- (void)unlock;
- (BOOL)tryLock;

/*
    Deprecated
 */
+ (NSDictionary *)metadataForPersistentStoreWithURL:(NSURL *)url error:(NSError **)error DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;

@end

#endif
