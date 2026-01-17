/*
    NSPersistentHistoryChangeRequest.h
    Core Data
    Copyright (c) 2014-2018, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <Foundation/NSDate.h>
#import <CoreData/NSPersistentStoreRequest.h>
#import <CoreData/NSPersistentStoreResult.h>

NS_ASSUME_NONNULL_BEGIN

@class NSPersistentHistoryTransaction;
@class NSPersistentHistoryToken;

API_AVAILABLE(macosx(10.13),ios(11.0),tvos(11.0),watchos(4.0))
@interface NSPersistentHistoryChangeRequest : NSPersistentStoreRequest {
#if (!__OBJC2__)
@private
    NSPersistentHistoryToken *_token;
    NSPersistentHistoryResultType _resultType;
    NSArray *_transactionIDs;
    NSNumber *_transactionNumber;
    struct __persistentHistoryChangeRequestDescriptionFlags {
        unsigned int _useQueryGenerationToken:1;
        unsigned int _deleteHistoryRequest:1;
        unsigned int _fetchTransactionForToken:1;
        unsigned int _reservedPersistentHistoryChangeRequestDescription:29;
    } _persistentHistoryChangeRequestDescriptionFlags;

    id* _additionalPrivateIvars;
#endif
}

+ (nonnull instancetype)fetchHistoryAfterDate:(NSDate *)date;
+ (nonnull instancetype)fetchHistoryAfterToken:(nullable NSPersistentHistoryToken *)token;
+ (nonnull instancetype)fetchHistoryAfterTransaction:(nullable NSPersistentHistoryTransaction *)transaction;

+ (nonnull instancetype)deleteHistoryBeforeDate:(NSDate *)date;
+ (nonnull instancetype)deleteHistoryBeforeToken:(nullable NSPersistentHistoryToken *)token;
+ (nonnull instancetype)deleteHistoryBeforeTransaction:(nullable NSPersistentHistoryTransaction *)transaction;

// The type of result that should be returned from this request. Defaults to NSPersistentHistoryResultTypeTransactionsAndChanges
@property NSPersistentHistoryResultType resultType;
@property (nullable,readonly,strong) NSPersistentHistoryToken *token;

@end

NS_ASSUME_NONNULL_END
