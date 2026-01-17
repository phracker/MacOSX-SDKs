/*
    NSPersistentStore.h
    Core Data
    Copyright (c) 2004-2015, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSSet.h>
#import <Foundation/NSString.h>
#import <Foundation/NSError.h>
#import <Foundation/NSURL.h>

NS_ASSUME_NONNULL_BEGIN

@class NSManagedObjectID;
@class NSManagedObjectModel;
@class NSManagedObjectContext;
@class NSPersistentStore;
@class NSPersistentStoreRequest;
@class NSPersistentStoreCoordinator;

NS_CLASS_AVAILABLE(10_5, 3_0)
@interface NSPersistentStore : NSObject {
    @private
    __weak NSPersistentStoreCoordinator *_coordinator;
    NSString *_configurationName;
    NSURL *_url;
    NSDictionary *_options;
    id* _oidFactories;
    id _defaultFaultHandler;
    struct _objectStoreFlags {
        unsigned int isReadOnly:1;
        unsigned int cleanOnRemove:1;
        unsigned int isMDDirty:1;
        unsigned int _RESERVED:29;
    } _flags;
	void *_temporaryIDClass;
	id _externalRecordsMonitor;
	void *_reserved3;
}

/* Get metadata from the persistent store at url. Must be overriden by subclasses.
   Subclasses should validate that the URL is the type of URL they are expecting, and 
   should verify that the file contents are appropriate for the store type before
   attempting to read from it. This method should never raise an exception.
 */
+ (nullable NSDictionary<NSString *, id> *)metadataForPersistentStoreWithURL:(NSURL *)url error:(NSError **)error;
/* Set the medatada of the store at url to metadata. Must be overriden by subclasses. */
+ (BOOL)setMetadata:(nullable NSDictionary<NSString *, id> *)metadata forPersistentStoreWithURL:(NSURL*)url error:(NSError **)error;

/* Returns the NSMigrationManager class optimized for this store class.  Subclasses of NSPersistentStore can override this to provide a custom migration manager subclass (eg to take advantage of store-specific functionality to improve migration performance).
 */
+ (Class)migrationManagerClass NS_AVAILABLE(10_6, 3_0);

/* the designated initializer for object stores. */
- (instancetype)initWithPersistentStoreCoordinator:(nullable NSPersistentStoreCoordinator *)root configurationName:(nullable NSString *)name URL:(NSURL *)url options:(nullable NSDictionary *)options NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;

/*  Store metadata must be accessible before -load: is called, but there is no way to return an error if the store is invalid 
*/
-(BOOL)loadMetadata:(NSError **)error; 

/* the bridge between the control & access layers. */
@property (nullable, nonatomic, readonly, weak) NSPersistentStoreCoordinator *persistentStoreCoordinator;

@property (readonly, copy) NSString *configurationName; // Which configuration does this store contain 
@property (nullable, readonly, strong) NSDictionary *options; // the options the store was initialized with

@property (nullable, strong) NSURL *URL;

@property (null_resettable, copy) NSString *identifier;

@property (readonly, copy) NSString *type; // stores always know their type

@property (getter=isReadOnly) BOOL readOnly;     // Do we know a priori the store is read only? 

@property (null_resettable, nonatomic, strong) NSDictionary<NSString *, id> *metadata; // includes store type and UUID

// Gives the store a chance to do any post-init work that's necessary
- (void)didAddToPersistentStoreCoordinator:(NSPersistentStoreCoordinator *)coordinator;

// Gives the store a chance to do any non-dealloc teardown (for example, closing a network connection) 
// before removal.
- (void)willRemoveFromPersistentStoreCoordinator:(nullable NSPersistentStoreCoordinator *)coordinator;

@end

NS_ASSUME_NONNULL_END
