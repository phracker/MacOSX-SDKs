/*
    NSCoreDataCoreSpotlightDelegate.h
    Core Data
    Copyright (c) 2017-2019, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>


@class NSManagedObjectContext;
@class NSPersistentStoreDescription;
@class NSManagedObjectModel;
@class NSManagedObject;
@class CSSearchableIndex;
@class CSSearchableItemAttributeSet;

NS_ASSUME_NONNULL_BEGIN

/* NSCoreDataSpotlightDelegate implements the CSSearchableIndexDelegate API, but can't
 publicly declare it due to linkage requirements.
 */
API_AVAILABLE(macosx(10.13),ios(11.0)) API_UNAVAILABLE(tvos,watchos)
@interface NSCoreDataCoreSpotlightDelegate : NSObject {
}

/* CoreSpotlight domain identifer; default nil */
- (NSString *)domainIdentifier;

/* CoreSpotlight index name; default is the store's identifier */
- (nullable NSString *)indexName;

- (instancetype)initForStoreWithDescription:(NSPersistentStoreDescription *)description  model:(NSManagedObjectModel *)model NS_DESIGNATED_INITIALIZER;

/* Create the searchable attributes for the managed object. Override to return nil if you don't
 want the object in the index for some reason.
 */
- (nullable CSSearchableItemAttributeSet *)attributeSetForObject:(NSManagedObject*)object;

/* CSSearchableIndexDelegate conformance */
- (void)searchableIndex:(CSSearchableIndex *)searchableIndex reindexAllSearchableItemsWithAcknowledgementHandler:(void (^)(void))acknowledgementHandler;

- (void)searchableIndex:(CSSearchableIndex *)searchableIndex reindexSearchableItemsWithIdentifiers:(NSArray <NSString *> *)identifiers
 acknowledgementHandler:(void (^)(void))acknowledgementHandler;

@end

NS_ASSUME_NONNULL_END

