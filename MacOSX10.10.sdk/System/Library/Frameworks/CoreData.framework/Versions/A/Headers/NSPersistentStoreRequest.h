/*
 NSPersistentStoreRequest.h
 Core Data
 Copyright (c) 2004-2012 Apple Inc.
 All rights reserved.
 */

#import <Foundation/NSArray.h>
@class NSFetchRequest;
@class NSAsynchronousFetchResult;

typedef NS_ENUM(NSUInteger, NSPersistentStoreRequestType) {
    NSFetchRequestType = 1,
    NSSaveRequestType,
    NSBatchUpdateRequestType = 6
};

NS_CLASS_AVAILABLE(10_7, 5_0)
@interface NSPersistentStoreRequest : NSObject <NSCopying> {
	@private
	NSArray *_affectedStores;
}

// Stores this request should be sent to.
@property (nonatomic, strong) NSArray *affectedStores;

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
@property (strong, readonly) NSPersistentStoreAsynchronousFetchResultCompletionBlock completionBlock;
@property (nonatomic) NSInteger estimatedResultCount;

- (instancetype)initWithFetchRequest:(NSFetchRequest*)request completionBlock:(NSPersistentStoreAsynchronousFetchResultCompletionBlock)blk;

@end
