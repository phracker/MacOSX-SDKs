/*
    NSCustomMigrationStage.h
    Core Data
    Copyright (c) 2023-2025, Apple Inc.
    All rights reserved.
*/

#import <CoreData/NSManagedObjectModel.h>
#import <CoreData/NSMigrationStage.h>

NS_ASSUME_NONNULL_BEGIN

@class NSManagedObjectModelReference;
@class NSCustomMigrationStage;
@class NSStagedMigrationManager;

/*
 * Each decomposed version of the app's model should be represented using an NSCustomMigrationStage and contain
 * a source model reference and a destination model reference. NSCustomMigrationStage provides optional handlers
 * that run immediately prior to and after the migration stage.
 */
API_AVAILABLE(macosx(14.0),ios(17.0),tvos(17.0),watchos(10.0))
@interface NSCustomMigrationStage : NSMigrationStage

@property (readonly, strong) NSManagedObjectModelReference *currentModel;
@property (readonly, strong) NSManagedObjectModelReference *nextModel;

/*
 * This handler will be called immediately prior to migrating the store schema. Use this handler to
 * execute any tasks your app may need. Access to the persistent container may be obtained from the NSStagedMigrationManager.
 */
@property (nullable, copy) BOOL (^willMigrateHandler)(NSStagedMigrationManager *migrationManager, NSCustomMigrationStage *migrationStage, NSError * _Nullable *outError) NS_REFINED_FOR_SWIFT;

/*
 * This handler will be called immediately after to migrating the store schema. Use this handler to
 * execute any tasks your app may need. Access to the persistent container may be obtained from the NSStagedMigrationManager.
 */
@property (nullable, copy) BOOL (^didMigrateHandler)(NSStagedMigrationManager *migrationManager, NSCustomMigrationStage *migrationStage, NSError * _Nullable *outError) NS_REFINED_FOR_SWIFT;

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithCurrentModelReference:(NSManagedObjectModelReference *)currentModel
                           nextModelReference:(NSManagedObjectModelReference *)nextModel NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
