/*
 NSPersistentStoreResult.h
 Core Data
 Copyright (c) 2004-2014 Apple Inc.
 All rights reserved.
 */
#import <Foundation/NSArray.h>
#import <CoreData/NSPersistentStoreRequest.h>
@class NSError;
@class NSProgress;
@class NSManagedObjectContext;
@class NSFetchRequest;
@class NSPersistentStoreAsynchronousResult;
@class NSAsynchronousFetchResult;
@class NSAsynchronousFetchRequest;

typedef NS_ENUM(NSUInteger, NSBatchUpdateRequestResultType) {
    NSStatusOnlyResultType = 0x0,                 // Don't return anything
    NSUpdatedObjectIDsResultType = 0x1,   // Return the object IDs of the rows that were updated
    NSUpdatedObjectsCountResultType = 0x2    // Return the number of rows that were updated
};

// Used to wrap the result of whatever is returned by the persistent store coordinator when
// -[NSManagedObjectContext executeRequest:error:] is called
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface NSPersistentStoreResult : NSObject

@end

NS_CLASS_AVAILABLE(10_10, 8_0)
@interface NSPersistentStoreAsynchronousResult : NSPersistentStoreResult {
@private
    NSProgress* _requestProgress;
    NSError* _requestError;
    NSManagedObjectContext* _requestContext;
    id _requestCompletionBlock;
    int32_t _flags;
}

@property (strong, readonly) NSManagedObjectContext* managedObjectContext;
@property (strong, readonly) NSError* operationError;
@property (strong, readonly) NSProgress* progress;

- (void)cancel;

@end

// The result returned when executing an NSBatchUpdateRequest
NS_CLASS_AVAILABLE(10_10,8_0)
@interface NSBatchUpdateResult : NSPersistentStoreResult {
@private
    id _aggregatedResult;
    NSBatchUpdateRequestResultType _resultType;
 
}

// Return the result. See NSBatchUpdateRequestResultType for options
@property (strong, readonly) id result;
@property (readonly) NSBatchUpdateRequestResultType resultType;

@end


NS_CLASS_AVAILABLE(10_10, 8_0)
@interface NSAsynchronousFetchResult : NSPersistentStoreAsynchronousResult {
@private
    NSAsynchronousFetchRequest* _fetchRequest;
    NSArray* _finalResult;
    id _intermediateResultCallback;
}

@property (strong, readonly) NSAsynchronousFetchRequest* fetchRequest;
@property (strong, readonly) NSArray* finalResult;


@end
