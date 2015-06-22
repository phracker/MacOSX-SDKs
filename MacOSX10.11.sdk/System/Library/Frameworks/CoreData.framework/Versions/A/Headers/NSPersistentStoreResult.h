/*
 NSPersistentStoreResult.h
 Core Data
 Copyright (c) 2004-2015, Apple Inc.
 All rights reserved.
 */
#import <Foundation/NSArray.h>
#import <CoreData/NSPersistentStoreRequest.h>

NS_ASSUME_NONNULL_BEGIN

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
} NS_ENUM_AVAILABLE(10_10, 8_0);

typedef NS_ENUM(NSUInteger, NSBatchDeleteRequestResultType) {
    NSBatchDeleteResultTypeStatusOnly = 0x0,                 // Don't return anything
    NSBatchDeleteResultTypeObjectIDs = 0x1,   // Return the object IDs of the rows that were deleted
    NSBatchDeleteResultTypeCount = 0x2,   // Return the object IDs of the rows that were deleted
} NS_ENUM_AVAILABLE(10_11, 9_0);

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
@property (nullable, strong, readonly) NSError* operationError;
@property (nullable, strong, readonly) NSProgress* progress;

- (void)cancel;

@end

NS_CLASS_AVAILABLE(10_10, 8_0)
@interface NSAsynchronousFetchResult : NSPersistentStoreAsynchronousResult {
@private
    NSAsynchronousFetchRequest* _fetchRequest;
    NSArray* _finalResult;
    id _intermediateResultCallback;
}

@property (strong, readonly) NSAsynchronousFetchRequest* fetchRequest;
@property (nullable, strong, readonly) NSArray * finalResult;

@end

// The result returned when executing an NSBatchUpdateRequest
NS_CLASS_AVAILABLE(10_10,8_0)
@interface NSBatchUpdateResult : NSPersistentStoreResult {
@private
    id _aggregatedResult;
    NSBatchUpdateRequestResultType _resultType;
 
}

// Return the result. See NSBatchUpdateRequestResultType for options
@property (nullable, strong, readonly) id result;
@property (readonly) NSBatchUpdateRequestResultType resultType;

@end


// The result returned when executing an NSBatchDeleteRequest
NS_CLASS_AVAILABLE(10_11,9_0)
@interface NSBatchDeleteResult : NSPersistentStoreResult {
@private
    id _aggregatedResult;
    NSBatchDeleteRequestResultType _resultType;
    
}

// Return the result. See NSBatchDeleteRequestResultType for options
@property (nullable, strong, readonly) id result;
@property (readonly) NSBatchDeleteRequestResultType resultType;

@end

NS_ASSUME_NONNULL_END
