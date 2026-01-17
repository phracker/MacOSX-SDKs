/*
    NSLightweightMigrationStage.h
    Core Data
    Copyright (c) 2023-2025, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <CoreData/NSMigrationStage.h>

NS_ASSUME_NONNULL_BEGIN

/*
 * NSLightweightMigrationStage describes a series of models that did not require decomposition and that were lightweight
 * migration eligible. These lightweight migration stages are used to supplement the total ordering of models described
 * to Core Data in your app. All lightweight model versions must be represented in one or more NSLightweightMigrationStages.
 */
API_AVAILABLE(macosx(14.0),ios(17.0),tvos(17.0),watchos(10.0))
@interface NSLightweightMigrationStage : NSMigrationStage

@property (readonly, strong) NSArray<NSString *> *versionChecksums;

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithVersionChecksums:(NSArray<NSString *> *)versionChecksums NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
