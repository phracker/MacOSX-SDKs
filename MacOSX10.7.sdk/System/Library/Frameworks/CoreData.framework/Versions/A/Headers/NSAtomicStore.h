/*
    NSAtomicStore.h
    Core Data
    Copyright (c) 2004-2010 Apple Inc.
    All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <CoreData/NSPersistentStore.h>
#import <CoreData/NSAtomicStoreCacheNode.h>
#import <CoreData/NSManagedObject.h>

NS_CLASS_AVAILABLE(10_5,3_0)
@interface NSAtomicStore : NSPersistentStore {
	@private
    NSMutableDictionary *_nodeCache;
    NSMutableDictionary *_entityCache;
    NSMutableDictionary *_storeMetadata;
    NSInteger _nextReference;
	void *_reserved4;
	void *_reserved5;
}

// API method that may be overriden by subclasses for custom initialization
- (id)initWithPersistentStoreCoordinator:(NSPersistentStoreCoordinator *)coordinator configurationName:(NSString *)configurationName URL:(NSURL *)url options:(NSDictionary *)options;

// API method that must be overriden by subclasses
- (BOOL)load:(NSError **)error;

// API method that must be overriden by subclasses
- (BOOL)save:(NSError **)error;

// API method that must be overriden by subclasses
- (NSAtomicStoreCacheNode *)newCacheNodeForManagedObject:(NSManagedObject *)managedObject;

// API method that must be overriden by subclasses
- (void)updateCacheNode:(NSAtomicStoreCacheNode *)node fromManagedObject:(NSManagedObject *)managedObject;

// Utility method with implementation provided by NSAtomicStore
- (NSSet *)cacheNodes;

// Utility method with implementation provided by NSAtomicStore
- (void)addCacheNodes:(NSSet *)cacheNodes;

// Called before cache nodes are removed
- (void)willRemoveCacheNodes:(NSSet *)cacheNodes;

// Utility method with implementation provided by NSAtomicStore
- (NSAtomicStoreCacheNode *)cacheNodeForObjectID:(NSManagedObjectID *)objectID;

// Utility method with implementation provided by NSAtomicStore
- (NSManagedObjectID *)objectIDForEntity:(NSEntityDescription *)entity referenceObject:(id)data;

// This method MUST return a new unique primary key reference data for an instance of entity. This 
// primary key value MUST be an id

// API method that must be overriden by subclasses
- (id)newReferenceObjectForManagedObject:(NSManagedObject *)managedObject;

// Utility method with implementation provided by NSAtomicStore
- (id)referenceObjectForObjectID:(NSManagedObjectID *)objectID;

@end
