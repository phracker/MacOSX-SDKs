/*
    NSPersistentStore.h
    Core Data
    Copyright (c) 2004-2009 Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSObject.h>

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

@class NSPersistentStoreCoordinator;

@interface NSPersistentStore : NSObject {
    @private
    __weak NSPersistentStoreCoordinator *_coordinator;
    NSString *_configurationName;
    NSURL *_url;
    NSDictionary *_options;
    NSMutableDictionary *_oidFactories;
    id _defaultFaultHandler;
    struct _objectStoreFlags {
        unsigned int isReadOnly:1;
        unsigned int cleanOnRemove:1;
        unsigned int isMDDirty:1;
        unsigned int _RESERVED:29;
    } _flags;
	void *_temporaryIDClass;
	void *_reserved2;
	void *_reserved3;
}

// gets the metadata from the persistent store of this object store class at the given URL

+ (NSDictionary *)metadataForPersistentStoreWithURL:(NSURL *)url error:(NSError **)error;    
+ (BOOL)setMetadata:(NSDictionary *)metadata forPersistentStoreWithURL:(NSURL*)url error:(NSError **)error;

/* Returns the NSMigrationManager class optimized for this store class.  Subclasses of NSPersistentStore can override this to provide a custom migration manager subclass (eg to take advantage of store-specific functionality to improve migration performance).
 */
+ (Class)migrationManagerClass AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* the designated initializer for object stores. */
- (id)initWithPersistentStoreCoordinator:(NSPersistentStoreCoordinator *)root configurationName:(NSString *)name URL:(NSURL *)url options:(NSDictionary *)options ;

/*  Store metadata must be accessible before -load: is called, but there is no way to return an error if the store is invalid 
*/
-(BOOL)loadMetadata:(NSError **)error; 

/* the bridge between the control & access layers. */
- (NSPersistentStoreCoordinator*) persistentStoreCoordinator;

- (NSString *)configurationName; // Which configuration does this store contain 
- (NSDictionary *)options; // the options the store was initialized with

- (NSURL *)URL;
- (void)setURL:(NSURL *)url;

- (NSString *)identifier;
- (void)setIdentifier:(NSString *)identifier;

- (NSString *)type; // stores always know their type

- (BOOL)isReadOnly;     // Do we know a priori the store is read only? 
- (void)setReadOnly:(BOOL)flag;

- (NSDictionary *)metadata; // includes store type and UUID
- (void)setMetadata:(NSDictionary *)storeMetadata;

// Gives the store a chance to do any post-init work that's necessary
- (void)didAddToPersistentStoreCoordinator:(NSPersistentStoreCoordinator *)coordinator;

// Gives the store a chance to do any non-dealloc teardown (for example, closing a network connection) 
// before removal.
- (void)willRemoveFromPersistentStoreCoordinator:(NSPersistentStoreCoordinator *)coordinator; 

@end

#endif
