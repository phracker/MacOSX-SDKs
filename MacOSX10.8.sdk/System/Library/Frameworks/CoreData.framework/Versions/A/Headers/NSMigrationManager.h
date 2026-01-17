/*
    NSMigrationManager.h
    Core Data
    Copyright (c) 2004-2012 Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSError.h>

@class NSEntityDescription;
@class NSEntityMapping;
@class NSManagedObjectContext;
@class NSManagedObject;
@class NSManagedObjectModel;
@class NSMappingModel;
@class NSMigrationContext;

NS_CLASS_AVAILABLE(10_5, 3_0)
@interface NSMigrationManager : NSObject {
    @private
    NSManagedObjectModel *_sourceModel;
    NSDictionary *_sourceEntitiesByVersionHash;
    NSManagedObjectModel *_destinationModel;
    NSDictionary *_destinationEntitiesByVersionHash;
    NSMappingModel *_mappingModel;
    NSManagedObjectContext *_sourceManagedObjectContext;
    NSManagedObjectContext *_destinationManagedObjectContext;
    NSMigrationContext *_migrationContext;
    NSDictionary *_userInfo;
    struct _migrationManagerFlags {
        unsigned int _migrationWasCancelled:1;
        unsigned int _usesStoreSpecificMigrationManager:1;
        unsigned int _reservedMigrationManager:30;
    } _migrationManagerFlags;
	NSError *_migrationCancellationError;
	id _reserved1;
	id _reserved2;
	id _reserved3;
	id _reserved4;
}

/* Creates a migration manager instance with the corresponding source and destination models.  (All validation of the arguments is performed during migrateStoreFromURL:toURL:)  As with the NSPersistentStoreCoordinator, once models are added to the migration manager they are immutable and cannot be altered.*/

- (id)initWithSourceModel:(NSManagedObjectModel *)sourceModel destinationModel:(NSManagedObjectModel *)destinationModel;

/* Migrates of the store at the specified source URL to the store at the destination URL, performing all of the mappings in the mapping model.  A store must exist at the source URL;  if a store does not exist at the destination URL, one will be created (otherwise the migration will append to the existing store.)  Invoking this method will perform compatibility checks on the source and destination models (and the mapping model.)  If an error occurs during the validation or migration, this method will return NO.*/
- (BOOL)migrateStoreFromURL:(NSURL *)sourceURL type:(NSString *)sStoreType options:(NSDictionary *)sOptions withMappingModel:(NSMappingModel *)mappings toDestinationURL:(NSURL *)dURL destinationType:(NSString *)dStoreType destinationOptions:(NSDictionary *)dOptions error:(NSError **)error;

/* Tries to use a store specific migration manager to perform the store migration, note that a store specific migration manager class is not guaranteed to perform any of the migration manager delegate callbacks or update values for the observable properties.  
 Defaults to YES */
- (void)setUsesStoreSpecificMigrationManager:(BOOL)flag NS_AVAILABLE(10_7, 5_0); 
- (BOOL)usesStoreSpecificMigrationManager NS_AVAILABLE(10_7,  5_0);

/* Resets the association tables for the migration.  (Note this does NOT reset the source or destination contexts).*/
- (void)reset;

/* Accessors for the mapping model, source model, and destination model*/
- (NSMappingModel *)mappingModel;
- (NSManagedObjectModel *)sourceModel;
- (NSManagedObjectModel *)destinationModel;

/* Accessors for the managed object contexts used for reading the source and destination stores.  These contexts are created lazily, as part of the initialization of two Core Data stacks (one for reading, the other for writing data.)  */
- (NSManagedObjectContext *)sourceContext;
- (NSManagedObjectContext *)destinationContext;

/* Returns the NSEntityDescription for the source and destination entities, respectively, of the entity mapping.  (Entity mappings do not store the actual description objects, but rather the name and version information of the entity.)*/
- (NSEntityDescription *)sourceEntityForEntityMapping:(NSEntityMapping *)mEntity;
- (NSEntityDescription *)destinationEntityForEntityMapping:(NSEntityMapping *)mEntity;

/* Associates the source instance with the specified destination instance for the given entity mapping.  Since the migration is performed as a three-step process (first create the data, then relate the data, then validate the data) it is necessary to be able to associate data between the source and destination stores, in order to allow for relationship creation/fixup after the creation pass.  This method is called in the default
implementation of NSEntityMigrationPolicy's createDestinationInstancesForSourceInstance:entityMapping:manager:error: method.*/
- (void)associateSourceInstance:(NSManagedObject *)sourceInstance withDestinationInstance:(NSManagedObject *)destinationInstance forEntityMapping:(NSEntityMapping *)entityMapping;

/* Returns the managed object instances created in the destination store for the given entity mapping for the specified source instances.*/
- (NSArray *)destinationInstancesForEntityMappingNamed:(NSString *)mappingName sourceInstances:(NSArray*)sourceInstances;
 
/* Returns the managed object instances in the source store used to create the specified destination instances for the given entity mapping.*/
- (NSArray *)sourceInstancesForEntityMappingNamed:(NSString *)mappingName destinationInstances:(NSArray *)destinationInstances;

/* Observable property that can be used to determine progress of the migration process.  Returns the current entity mapping being processed. Each entity is processed a total of three times (instance creation, relationship creation, validation)*/
- (NSEntityMapping *)currentEntityMapping;

/* Observable property that can be used to determine progress of the migration process.  Returns the percentage complete of the migration process.  The progress value is a number from 0 to 1 indicating percent complete.*/
- (float)migrationProgress;

/* Returns/sets the user info for the migration manager*/
- (NSDictionary *)userInfo;
- (void)setUserInfo:(NSDictionary *)dict;

/* Cancels the migration with the specified error. Calling this method causes migrateStoreFromURL:type:options:withMappingModel:toDestinationURL:destinationType:destinationOptions:error: to abort the migration and return the specified error.  */
- (void)cancelMigrationWithError:(NSError *)error;

@end
