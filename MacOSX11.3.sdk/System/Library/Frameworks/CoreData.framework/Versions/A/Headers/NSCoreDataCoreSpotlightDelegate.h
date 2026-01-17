/*
    NSCoreDataCoreSpotlightDelegate.h
    Core Data
    Copyright (c) 2017-2020, Apple Inc.
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

/* CoreSpotlight domain identifer; default is the store's identifier */
- (NSString *)domainIdentifier;

/* CoreSpotlight index name; default nil */
- (nullable NSString *)indexName;

- (instancetype)init NS_UNAVAILABLE;

/*
 * NSCoreDataSpotlightDelegate requires that
 *  - the store type is NSSQLiteStoreType.
 *  - the store has persistent history tracking enabled.
 */
- (instancetype)initForStoreWithDescription:(NSPersistentStoreDescription *)description
                                      model:(NSManagedObjectModel *)model NS_DESIGNATED_INITIALIZER;

/* Create the searchable attributes for the managed object. Override to return nil if you do not want the object included in the index.
 */
- (nullable CSSearchableItemAttributeSet *)attributeSetForObject:(NSManagedObject*)object;

/* CSSearchableIndexDelegate conformance */
- (void)searchableIndex:(CSSearchableIndex *)searchableIndex reindexAllSearchableItemsWithAcknowledgementHandler:(void (^)(void))acknowledgementHandler;

- (void)searchableIndex:(CSSearchableIndex *)searchableIndex reindexSearchableItemsWithIdentifiers:(NSArray <NSString *> *)identifiers
 acknowledgementHandler:(void (^)(void))acknowledgementHandler;

@end

NS_ASSUME_NONNULL_END

