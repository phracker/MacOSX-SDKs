/*
    NSPersistentHistoryTransaction.h
    Core Data
    Copyright (c) 2016-2017, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <Foundation/NSDate.h>

NS_ASSUME_NONNULL_BEGIN

@class NSNotification;
@class NSPersistentHistoryToken;
@class NSPersistentHistoryChange;

API_AVAILABLE(macosx(10.13),ios(11.0),tvos(11.0),watchos(4.0))
@interface NSPersistentHistoryTransaction : NSObject <NSCopying>

@property (readonly,copy) NSDate *timestamp;
@property (nullable,readonly,copy) NSArray<NSPersistentHistoryChange *>*changes;
@property (readonly) int64_t transactionNumber;
@property (readonly,copy) NSString *storeID;
@property (readonly,copy) NSString *bundleID;
@property (readonly,copy) NSString *processID;
@property (nullable,readonly,copy) NSString *contextName;
@property (nullable,readonly,copy) NSString *author;
@property (readonly,strong) NSPersistentHistoryToken *token;

// Get a notification that can be consumed by a NSManagedObjectContext
- (NSNotification *) objectIDNotification;

@end

NS_ASSUME_NONNULL_END
