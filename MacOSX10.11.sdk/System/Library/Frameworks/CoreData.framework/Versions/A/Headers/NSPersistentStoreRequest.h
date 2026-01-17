/*
 NSPersistentStoreRequest.h
 Core Data
 Copyright (c) 2004-2015, Apple Inc.
 All rights reserved.
 */

#import <Foundation/NSArray.h>

NS_ASSUME_NONNULL_BEGIN

@class NSFetchRequest;
@class NSAsynchronousFetchResult;
@class NSPersistentStore;

typedef NS_ENUM(NSUInteger, NSPersistentStoreRequestType) {
    NSFetchRequestType = 1,
    NSSaveRequestType,
    NSBatchUpdateRequestType NS_ENUM_AVAILABLE(10_10, 8_0) = 6,
    NSBatchDeleteRequestType NS_ENUM_AVAILABLE(10_11, 9_0) = 7
};

NS_CLASS_AVAILABLE(10_7, 5_0)
@interface NSPersistentStoreRequest : NSObject <NSCopying> {
	@private
	NSArray *_affectedStores;
}

// Stores this request should be sent to.
@property (nullable, nonatomic, strong) NSArray<NSPersistentStore *> *affectedStores;

// The type of the request.
@property (readonly) NSPersistentStoreRequestType requestType;

@end

typedef void (^NSPersistentStoreAsynchronousFetchResultCompletionBlock)(NSAsynchronousFetchResult *result);


NS_CLASS_AVAILABLE(10_10,8_0)
@interface NSAsynchronousFetchRequest : NSPersistentStoreRequest {
@private
    NSFetchRequest* _fetchRequest;
    id _requestCompletionBlock;
    NSInteger _estimatedResultCount;
}
@property (strong, readonly) NSFetchRequest* fetchRequest;
@property (nullable, strong, readonly) NSPersistentStoreAsynchronousFetchResultCompletionBlock completionBlock;
@property (nonatomic) NSInteger estimatedResultCount;

- (instancetype)initWithFetchRequest:(NSFetchRequest*)request completionBlock:(nullable NSPersistentStoreAsynchronousFetchResultCompletionBlock)blk;

@end

NS_ASSUME_NONNULL_END
