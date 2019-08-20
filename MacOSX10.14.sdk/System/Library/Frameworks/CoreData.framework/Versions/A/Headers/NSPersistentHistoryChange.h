/*
    NSPersistentHistoryChange.h
    Core Data
    Copyright (c) 2016-2018, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSDictionary.h>
#import <Foundation/NSData.h>
#import <Foundation/NSSet.h>

NS_ASSUME_NONNULL_BEGIN

@class NSPersistentHistoryTransaction;
@class NSManagedObjectID;
@class NSPropertyDescription;


typedef NS_ENUM (NSInteger, NSPersistentHistoryChangeType) {
    NSPersistentHistoryChangeTypeInsert,
    NSPersistentHistoryChangeTypeUpdate,
    NSPersistentHistoryChangeTypeDelete,
} API_AVAILABLE(macosx(10.13),ios(11.0),tvos(11.0),watchos(4.0));

API_AVAILABLE(macosx(10.13),ios(11.0),tvos(11.0),watchos(4.0))
@interface NSPersistentHistoryChange : NSObject <NSCopying>

@property (readonly) int64_t changeID;
@property (readonly,copy) NSManagedObjectID *changedObjectID;
@property (readonly) NSPersistentHistoryChangeType changeType;
@property (nullable,readonly,copy) NSDictionary *tombstone;
@property (nullable,readonly,strong) NSPersistentHistoryTransaction *transaction;
@property (nullable,readonly,copy) NSSet<NSPropertyDescription *> *updatedProperties;

@end

NS_ASSUME_NONNULL_END
