/*
 NSPersistentStoreResult.h
 Core Data
 Copyright (c) 2004-2016, Apple Inc.
 All rights reserved.
 */
#import <Foundation/NSArray.h>
#import <CoreData/NSFetchRequest.h>

NS_ASSUME_NONNULL_BEGIN

@class NSError;
@class NSProgress;
@class NSManagedObjectContext;
@class NSFetchRequest;
@class NSPersistentStoreAsynchronousResult;
@class NSAsynchronousFetchResult;
@class NSAsynchronousFetchRequest;

typedef NS_ENUM(NSUInteger, NSBatchUpdateRequestResultType) {
    NSStatusOnlyResultType = 0x0,            // Return a status boolean
    NSUpdatedObjectIDsResultType = 0x1,      // Return the object IDs of the rows that were updated
    NSUpdatedObjectsCountResultType = 0x2    // Return the number of rows that were updated
} API_AVAILABLE(macosx(10.10), ios(8.0));

typedef NS_ENUM(NSUInteger, NSBatchDeleteRequestResultType) {
    NSBatchDeleteResultTypeStatusOnly = 0x0, // Return a status boolean
    NSBatchDeleteResultTypeObjectIDs = 0x1,  // Return the object IDs of the rows that were deleted
    NSBatchDeleteResultTypeCount = 0x2,      // Return the number of rows that were deleted
} API_AVAILABLE(macosx(10.11), ios(9.0));

// Used to wrap the result of whatever is returned by the persistent store coordinator when
// -[NSManagedObjectContext executeRequest:error:] is called
API_AVAILABLE(macosx(10.10),ios(8.0))
@interface NSPersistentStoreResult : NSObject

@end

API_AVAILABLE(macosx(10.10),ios(8.0))
@interface NSPersistentStoreAsynchronousResult : NSPersistentStoreResult {
#if (!__OBJC2__)
@private
    NSProgress* _requestProgress;
    NSError* _requestError;
    NSManagedObjectContext* _requestContext;
    id _requestCompletionBlock;
    int32_t _flags;
#endif
}

@property (strong, readonly) NSManagedObjectContext* managedObjectContext;
@property (nullable, strong, readonly) NSError* operationError;
@property (nullable, strong, readonly) NSProgress* progress;

- (void)cancel;

@end

API_AVAILABLE(macosx(10.10),ios(8.0))
@interface NSAsynchronousFetchResult<ResultType:id<NSFetchRequestResult>> : NSPersistentStoreAsynchronousResult {
#if (!__OBJC2__)
@private
    NSAsynchronousFetchRequest* _fetchRequest;
    NSArray* _finalResult;
    id _intermediateResultCallback;
#endif
}

@property (strong, readonly) NSAsynchronousFetchRequest<ResultType> * fetchRequest;
@property (nullable, strong, readonly) NSArray<ResultType> * finalResult;

@end

// The result returned when executing an NSBatchUpdateRequest
API_AVAILABLE(macosx(10.10),ios(8.0))
@interface NSBatchUpdateResult : NSPersistentStoreResult {
#if (!__OBJC2__)
@private
    id _aggregatedResult;
    NSBatchUpdateRequestResultType _resultType;
#endif
}

// Return the result. See NSBatchUpdateRequestResultType for options
@property (nullable, strong, readonly) id result;
@property (readonly) NSBatchUpdateRequestResultType resultType;

@end


// The result returned when executing an NSBatchDeleteRequest
API_AVAILABLE(macosx(10.11),ios(9.0))
@interface NSBatchDeleteResult : NSPersistentStoreResult {
#if (!__OBJC2__)
@private
    id _aggregatedResult;
    NSBatchDeleteRequestResultType _resultType;
#endif
}

// Return the result. See NSBatchDeleteRequestResultType for options
@property (nullable, strong, readonly) id result;
@property (readonly) NSBatchDeleteRequestResultType resultType;

@end

NS_ASSUME_NONNULL_END
