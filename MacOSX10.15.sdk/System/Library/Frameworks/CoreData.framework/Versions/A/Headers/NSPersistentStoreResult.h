/*
    NSPersistentStoreResult.h
    Core Data
    Copyright (c) 2004-2019, Apple Inc.
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

typedef NS_ENUM(NSUInteger, NSBatchInsertRequestResultType) {
    NSBatchInsertRequestResultTypeStatusOnly = 0x0,            // Return a status boolean
    NSBatchInsertRequestResultTypeObjectIDs = 0x1,             // Return the object IDs of the rows that were inserted/updated
    NSBatchInsertRequestResultTypeCount = 0x2                  // Return the number of rows that were inserted/updated
} API_AVAILABLE(macosx(10.15),ios(13.0),tvos(13.0),watchos(6.0));

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


typedef NS_ENUM(NSInteger, NSPersistentHistoryResultType) {
    NSPersistentHistoryResultTypeStatusOnly = 0x0,
    NSPersistentHistoryResultTypeObjectIDs = 0x1,   // Return the object IDs of the changes objects
    NSPersistentHistoryResultTypeCount = 0x2,       // Return the number of changes
    NSPersistentHistoryResultTypeTransactionsOnly = 0x3,// Return the transactions since
    NSPersistentHistoryResultTypeChangesOnly = 0x4,     // Return the changes since
    NSPersistentHistoryResultTypeTransactionsAndChanges = 0x5,// Return the transactions and changes since
} API_AVAILABLE(macosx(10.13),ios(11.0),tvos(11.0),watchos(4.0));

// Used to wrap the result of whatever is returned by the persistent store coordinator when
// -[NSManagedObjectContext executeRequest:error:] is called
API_AVAILABLE(macosx(10.10),ios(8.0))
@interface NSPersistentStoreResult : NSObject

@end

API_AVAILABLE(macosx(10.10),ios(8.0))
@interface NSPersistentStoreAsynchronousResult : NSPersistentStoreResult {
}

@property (strong, readonly) NSManagedObjectContext* managedObjectContext;
@property (nullable, strong, readonly) NSError* operationError;
@property (nullable, strong, readonly) NSProgress* progress;

- (void)cancel;

@end

API_AVAILABLE(macosx(10.10),ios(8.0))
@interface NSAsynchronousFetchResult<ResultType:id<NSFetchRequestResult>> : NSPersistentStoreAsynchronousResult {
}

@property (strong, readonly) NSAsynchronousFetchRequest<ResultType> * fetchRequest;
@property (nullable, strong, readonly) NSArray<ResultType> * finalResult;

@end

// The result returned when executing an NSBatchInsertRequest
API_AVAILABLE(macosx(10.15),ios(13.0),tvos(13.0),watchos(6.0))
@interface NSBatchInsertResult : NSPersistentStoreResult {
}

// Return the result. See NSBatchInsertRequestResultType for options
@property (nullable, strong, readonly) id result;
@property (readonly) NSBatchInsertRequestResultType resultType;

@end

// The result returned when executing an NSBatchUpdateRequest
API_AVAILABLE(macosx(10.10),ios(8.0))
@interface NSBatchUpdateResult : NSPersistentStoreResult {
}

// Return the result. See NSBatchUpdateRequestResultType for options
@property (nullable, strong, readonly) id result;
@property (readonly) NSBatchUpdateRequestResultType resultType;

@end


// The result returned when executing an NSBatchDeleteRequest
API_AVAILABLE(macosx(10.11),ios(9.0))
@interface NSBatchDeleteResult : NSPersistentStoreResult {
}

// Return the result. See NSBatchDeleteRequestResultType for options
@property (nullable, strong, readonly) id result;
@property (readonly) NSBatchDeleteRequestResultType resultType;

@end


// The result returned when executing an NSPersistentHistoryChangeRequest
API_AVAILABLE(macosx(10.13),ios(11.0),tvos(11.0),watchos(4.0))
@interface NSPersistentHistoryResult : NSPersistentStoreResult {
}

// Return the result. See NSPersistentHistoryResultType for options
@property (nullable, strong, readonly) id result;
@property (readonly) NSPersistentHistoryResultType resultType;

@end

NS_ASSUME_NONNULL_END
