/*
    NSStagedMigrationManager.h
    Core Data
    Copyright (c) 2023-2025, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>

NS_ASSUME_NONNULL_BEGIN

@class NSMigrationStage;

/*
 * The NSStagedMigrationManager class encapsulates a developer-described total ordering of NSCustomMigrationStage's
 * and supplementary NSLightweightMigrationStage's. The NSStagedMigrationManager will apply the stages in the order
 * in which they are indexed in the .stages property at the appropriate time during staged migration. The
 * NSStagedMigrationManager also manages the migration event loop and provides access to the migrating store via
 * an NSPersistentContainer. A NSStagedMigrationManager should be added to store options using
 * NSPersistentStoreStagedMigrationManagerOptionKey.
 */
API_AVAILABLE(macosx(14.0),ios(17.0),tvos(17.0),watchos(10.0))
@interface NSStagedMigrationManager : NSObject

/*
 * To perform staged migration, a total ordering of models must be described to Core Data. The models in the
 * .stages property should match the order of models for the app.
 */
@property (readonly, strong) NSArray<__kindof NSMigrationStage *> *stages;

/*
 * During migration, access to the migrating store can be obtained from this property. The NSPersistentContainer
 * will be configured with the appropriate model in the willMigrateHandler and didMigrateHandler of an
 * NSCustomMigrationStage.
 */
@property (readonly, strong, nullable) NSPersistentContainer *container;

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithMigrationStages:(NSArray<__kindof NSMigrationStage *> *)stages NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
