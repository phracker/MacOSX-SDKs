/*
    NSBatchInsertRequest.h
    Core Data
    Copyright (c) 2004-2019, Apple Inc.
    All rights reserved.
*/

#import <CoreData/NSPersistentStoreRequest.h>
#import <CoreData/NSPersistentStoreResult.h>

@class NSManagedObject;
@class NSEntityDescription;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.15),ios(13.0),tvos(13.0),watchos(6.0))
@interface NSBatchInsertRequest : NSPersistentStoreRequest {
}

@property (copy, readonly) NSString *entityName;
@property (strong, nullable, readonly) NSEntityDescription *entity;
@property (copy, nullable) NSArray <NSDictionary<NSString *, id> *> *objectsToInsert;

// The type of result that should be returned from this request. Defaults to NSBatchInsertRequestResultTypeStatusOnly
@property NSBatchInsertRequestResultType resultType;

+ (instancetype)batchInsertRequestWithEntityName:(NSString *)entityName objects:(NSArray <NSDictionary<NSString *, id> *>*)dictionaries;

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithEntityName:(NSString *)entityName objects:(NSArray <NSDictionary<NSString *, id> *>*)dictionaries;
- (instancetype)initWithEntity:(NSEntityDescription *)entity objects:(NSArray <NSDictionary<NSString *, id> *>*)dictionaries;

@end

NS_ASSUME_NONNULL_END
