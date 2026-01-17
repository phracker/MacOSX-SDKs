/*
    NSMigrationStage.h
    Core Data
    Copyright (c) 2023-2025, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSString.h>

NS_ASSUME_NONNULL_BEGIN

/*
 * NSMigrationStage forms the basis for migrating between version of a model in staged migration. Each model version
 * in your app will be described with an NSMigrationStage.
 */
API_AVAILABLE(macosx(14.0),ios(17.0),tvos(17.0),watchos(10.0))
@interface NSMigrationStage : NSObject

/*
 * Describe the purpose of this migration stage. This label will be available when accessing persistent history
 * for the store
 */
@property (nonatomic, null_resettable, copy) NSString *label;

@end

NS_ASSUME_NONNULL_END
