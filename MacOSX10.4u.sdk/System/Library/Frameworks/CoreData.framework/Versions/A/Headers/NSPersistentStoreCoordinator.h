/*
    NSPersistentStoreCoordinator.h
    Core Data
    Copyright (c) 2004-2005 Apple Computer, Inc.
    All rights reserved.
*/

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

#import <Foundation/NSObject.h>
#import <Foundation/NSLock.h>
#import <CoreData/CoreDataDefines.h>

@class NSArray;
@class NSMutableArray;
@class NSDictionary;
@class NSError;
@class NSManagedObjectID;
@class NSManagedObjectModel;
@class NSMutableDictionary;
@class NSString;
@class NSURL;

// Persistent store types supported by Core Data:
COREDATA_EXTERN NSString * const NSSQLiteStoreType;
COREDATA_EXTERN NSString * const NSXMLStoreType;
COREDATA_EXTERN NSString * const NSBinaryStoreType;
COREDATA_EXTERN NSString * const NSInMemoryStoreType;

// Persistent store metadata dictionary keys:
COREDATA_EXTERN NSString * const NSStoreTypeKey;    // key in the metadata dictionary to identify the store type
COREDATA_EXTERN NSString * const NSStoreUUIDKey;    // key in the metadata dictionary to identify the store UUID - the store UUID is useful to identify stores through URI representations, but it is NOT guaranteed to be unique (while the UUID generated for new stores is unique, users can freely copy files and thus the UUID stored inside, so developers that track/reference stores explicitly do need to be aware of duplicate UUIDs and potentially override the UUID when a new store is added to the list of known stores in their application)

COREDATA_EXTERN NSString * const NSPersistentStoreCoordinatorStoresDidChangeNotification;    // user info dictionary contains information about the stores that were added or removed

// User info keys for NSPersistentStoreCoordinatorStoresDidChangeNotification:
// The object values for NSAddedPersistentStoresKey and NSRemovedPersistentStoresKey 
// will be arrays containing added/removed stores
COREDATA_EXTERN NSString * const NSAddedPersistentStoresKey;
COREDATA_EXTERN NSString * const NSRemovedPersistentStoresKey;
// The object value for NSUUIDChangedPersistentStoresKey will be an array where the 
// object at index 0 will be the old store instance, and the object at index 1 the new
COREDATA_EXTERN NSString * const NSUUIDChangedPersistentStoresKey;

// Persistent store option keys:
COREDATA_EXTERN NSString * const NSReadOnlyPersistentStoreOption;    // flag indicating whether a store is treated as read-only or not - default is NO
COREDATA_EXTERN NSString * const NSValidateXMLStoreOption;    // flag indicating whether an XML file should be validated with the DTD while opening - default is NO


@interface NSPersistentStoreCoordinator : NSObject <NSLocking> {
@private
    void *_reserved;
    void *_reserved2;
    void *_reserved3;
    void *_reserved4;
    NSManagedObjectModel *_managedObjectModel;
    NSRecursiveLock* _coreLock;
    NSMutableArray *_persistentStores;
}

+ (NSDictionary *)metadataForPersistentStoreWithURL:(NSURL *)url error:(NSError **)error;    // allows to access the metadata stored in a persistent store without warming up a CoreData stack; the guaranteed keys in this dictionary are NSStoreTypeKey and NSStoreUUIDKey

- (void)setMetadata:(NSDictionary *)metadata forPersistentStore:(id)store;    // sets the metadata stored in the persistent store during the next save operation executed on it; the store type and UUID (NSStoreTypeKey and NSStoreUUIDKey) are always added automatically (but NSStoreUUIDKey is only added if it is not set manually as part of the dictionary argument)
- (NSDictionary *)metadataForPersistentStore:(id)store;    // returns the metadata currently stored or to-be-stored in the persistent store

- (id)initWithManagedObjectModel:(NSManagedObjectModel *)model;

- (NSManagedObjectModel *)managedObjectModel;

- (NSArray *)persistentStores;
- (id)persistentStoreForURL:(NSURL *)URL;
- (NSURL *)URLForPersistentStore:(id)store;

- (id)addPersistentStoreWithType:(NSString *)storeType configuration:(NSString *)configuration URL:(NSURL *)storeURL options:(NSDictionary *)options error:(NSError **)error;    // configuration can be nil, then it's the complete model; storeURL is usually the file location of the database
- (BOOL)removePersistentStore:(id)store error:(NSError **)error;
- (id)migratePersistentStore:(id)store toURL:(NSURL *)URL options:(NSDictionary *)options withType:(NSString *)storeType error:(NSError **)error;    // used for save as - performance may vary depending on the type of old and new store; the old store is usually removed from the coordinator by the migration operation, and therefore is no longer a useful reference after invoking this method

- (NSManagedObjectID *)managedObjectIDForURIRepresentation:(NSURL *)url;    // given a URI representation of an object ID, returns an object ID if a matching store is available or nil if a matching store cannot be found (the URI representation contains a UUID of the store the ID is coming from, and the coordinator can match it against the stores added to it)

- (void)lock;
- (void)unlock;
- (BOOL)tryLock;

@end

#endif
