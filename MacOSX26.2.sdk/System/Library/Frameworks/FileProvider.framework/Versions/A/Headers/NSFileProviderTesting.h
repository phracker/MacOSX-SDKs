//
//  NSFileProviderTesting.h
//  FileProvider
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <FileProvider/NSFileProviderManager.h>
#import <FileProvider/NSFileProviderReplicatedExtension.h>

NS_ASSUME_NONNULL_BEGIN

#pragma mark - Manual Scheduling Calls

/** Type of the operation
 */
typedef NS_ENUM(NSInteger, NSFileProviderTestingOperationType) {
    // A testing operation of type Ingestion
    NSFileProviderTestingOperationTypeIngestion = 0,

    // A testing operation of type Lookup
    NSFileProviderTestingOperationTypeLookup = 1,

    // A testing operation of type Creation
    NSFileProviderTestingOperationTypeCreation = 2,

    // A testing operation of type Modification
    NSFileProviderTestingOperationTypeModification = 3,

    // A testing operation of type Deletion
    NSFileProviderTestingOperationTypeDeletion = 4,

    // A testing operation of type ContentFetch
    NSFileProviderTestingOperationTypeContentFetch = 5,

    // A testing operation of type ChildrenEnumeration
    NSFileProviderTestingOperationTypeChildrenEnumeration = 6,

    // A testing operation of type CollisionResolution
    NSFileProviderTestingOperationTypeCollisionResolution = 7
} FILEPROVIDER_API_AVAILABILITY_V3_1_IOS;

@protocol NSFileProviderTestingIngestion;
@protocol NSFileProviderTestingLookup;
@protocol NSFileProviderTestingCreation;
@protocol NSFileProviderTestingModification;
@protocol NSFileProviderTestingDeletion;
@protocol NSFileProviderTestingContentFetch;
@protocol NSFileProviderTestingChildrenEnumeration;
@protocol NSFileProviderTestingCollisionResolution;

/** An operation that can scheduled.
 */
FILEPROVIDER_API_AVAILABILITY_V3_1_IOS
@protocol NSFileProviderTestingOperation <NSObject>

/** The operation type
 */
@property (nonatomic, readonly) NSFileProviderTestingOperationType type;

/** Returns the operation as an Ingestion.

 Returns the operation if it conforms to NSFileProviderTestingIngestion, otherwise returns nil.
 */
- (nullable id<NSFileProviderTestingIngestion>)asIngestion NS_SWIFT_UNAVAILABLE("use Swift's `as` operator");

/** Returns the operation as an Lookup.

 Returns the operation if it conforms to NSFileProviderTestingLookup, otherwise returns nil.
 */
- (nullable id<NSFileProviderTestingLookup>)asLookup NS_SWIFT_UNAVAILABLE("use Swift's `as` operator");

/** Returns the operation as an Creation.

 Returns the operation if it conforms to NSFileProviderTestingCreation, otherwise returns nil.
 */
- (nullable id<NSFileProviderTestingCreation>)asCreation NS_SWIFT_UNAVAILABLE("use Swift's `as` operator");

/** Returns the operation as an Modification.

 Returns the operation if it conforms to NSFileProviderTestingModification, otherwise returns nil.
 */
- (nullable id<NSFileProviderTestingModification>)asModification NS_SWIFT_UNAVAILABLE("use Swift's `as` operator");

/** Returns the operation as an Deletion.

 Returns the operation if it conforms to NSFileProviderTestingDeletion, otherwise returns nil.
 */
- (nullable id<NSFileProviderTestingDeletion>)asDeletion NS_SWIFT_UNAVAILABLE("use Swift's `as` operator");

/** Returns the operation as an ContentFetch.

 Returns the operation if it conforms to NSFileProviderTestingContentFetch, otherwise returns nil.
 */
- (nullable id<NSFileProviderTestingContentFetch>)asContentFetch NS_SWIFT_UNAVAILABLE("use Swift's `as` operator");

/** Returns the operation as an ChildrenEnumeration.

 Returns the operation if it conforms to NSFileProviderTestingChildrenEnumeration, otherwise returns nil.
 */
- (nullable id<NSFileProviderTestingChildrenEnumeration>)asChildrenEnumeration NS_SWIFT_UNAVAILABLE("use Swift's `as` operator");

/** Returns the operation as an Bounce.

 Returns the operation if it conforms to NSFileProviderTestingCollisionResolution, otherwise returns nil.
 */
- (nullable id<NSFileProviderTestingCollisionResolution>)asCollisionResolution NS_SWIFT_UNAVAILABLE("use Swift's `as` operator");

@end

/** Control the scheduling of operation.

 These methods are available on domain with the NSFileProviderDomainTestingModeInteractive
 enabled.

 In order to manually schedule the operation, the testing harness will first call
 -listAvailableTestingOperationWithError and get a list of operations that can be scheduled.
 It can pick one or more operations from that list and call -runTestingOperations:error: to
 schedule those operations.

 From that point, it should get the new list of available operations and iterate between listing,
 picking operation, running those operation and so on.

 A process must have the com.apple.developer.fileprovider.testing-mode entitlement in order to
 call the methods from this category.
 */
@interface NSFileProviderManager (TestingModeInteractive)

/** List the available operations.

 This lists all of the operations that are ready to be scheduled by the system. The system waits
 for all the pending disk and working set updates to be known before returning.

 The operations that are returned may become invalid if the system receives new disk or working
 set events, or if some operation are scheduled using -runTestingOperations:error:.
 */
- (nullable NSArray <id<NSFileProviderTestingOperation>> *)listAvailableTestingOperationsWithError:(NSError **)error
FILEPROVIDER_API_AVAILABILITY_V3_1_IOS;

/** Run a set of operations.

 Ask the system to schedule the execution of the listed operations. The system will wait until all
 those operations have completed and report a per-operation error in case an operation fails.
 */
- (nullable NSDictionary<id<NSFileProviderTestingOperation>, NSError *> *)runTestingOperations:(NSArray<id<NSFileProviderTestingOperation>> *)operations
                                                                                         error:(NSError **)error
FILEPROVIDER_API_AVAILABILITY_V3_1_IOS;

@end

#pragma mark - Testing Operations

/** Side affected by the operation.
 */
typedef NS_ENUM(NSUInteger, NSFileProviderTestingOperationSide) {
    /** The operation reads or writes the disk.
     */
    NSFileProviderTestingOperationSideDisk         = 0,

    /** The operation reads or writes the file provider extension.
     */
    NSFileProviderTestingOperationSideFileProvider = 1,
} FILEPROVIDER_API_AVAILABILITY_V3_1_IOS;


/** This operation causes the system to ingest a change.

 When running this operation, the system will discover a change from the disk or the provider.
 */
FILEPROVIDER_API_AVAILABILITY_V3_1_IOS
@protocol NSFileProviderTestingIngestion <NSFileProviderTestingOperation>

/** Side of the event.
 */
@property (readonly, nonatomic) NSFileProviderTestingOperationSide side;

/** Identifier of the affected item.
 */
@property (readonly, nonatomic) NSFileProviderItemIdentifier itemIdentifier;

/** The metadata of the item.

 This will be nil if the item is being deleted.
 */
@property (readonly, nullable, nonatomic) NSFileProviderItem item;

@end


/** This operation causes the system to lookup an item.
 */
FILEPROVIDER_API_AVAILABILITY_V3_1_IOS
@protocol NSFileProviderTestingLookup <NSFileProviderTestingOperation>

/** Side of the event.
 */
@property (readonly, nonatomic) NSFileProviderTestingOperationSide side;

/** Identifier of the affected item.
 */
@property (readonly, nonatomic) NSFileProviderItemIdentifier itemIdentifier;

@end


/** This operation causes the system to propagate a creation of an item from a source side to a target side.
 */
FILEPROVIDER_API_AVAILABILITY_V3_1_IOS
@protocol NSFileProviderTestingCreation <NSFileProviderTestingOperation>

/** The target side of the operation.
 */
@property (readonly, nonatomic) NSFileProviderTestingOperationSide targetSide;

/** The description of the item.
 */
@property (readonly, nonatomic) NSFileProviderItem sourceItem;

/** The domain version at the time the creation was discovered on the source side.
 */
@property (readonly, nonatomic, nullable) NSFileProviderDomainVersion *domainVersion;

@end


/** This operation causes the system to propagate a modification of an existing item from a source side to a target side.

 The modification happens if a change is identified on an item that is already known by both sides.
 */
FILEPROVIDER_API_AVAILABILITY_V3_1_IOS
@protocol NSFileProviderTestingModification <NSFileProviderTestingOperation>

/** The target side of the operation.
 */
@property (readonly, nonatomic) NSFileProviderTestingOperationSide targetSide;

/** The description of the item.
 */
@property (readonly, nonatomic) NSFileProviderItem sourceItem;

/** The identifier of the target item.
 */
@property (readonly, nonatomic) NSFileProviderItemIdentifier targetItemIdentifier;

/** The version of the target item on top of which the modification is applied
 */
@property (readonly, nonatomic) NSFileProviderItemVersion *targetItemBaseVersion;

/** The list of updated fields.
 */
@property (readonly, nonatomic) NSFileProviderItemFields changedFields;

/** The domain version at the time the change was discovered on the source side.
 */
@property (readonly, nonatomic, nullable) NSFileProviderDomainVersion *domainVersion;

@end


/** This operation causes the system to propagate a deletion from a source side to a target side.

 The deletion happens if an item that is known by the target side is deleted on the source side.
 */
FILEPROVIDER_API_AVAILABILITY_V3_1_IOS
@protocol NSFileProviderTestingDeletion <NSFileProviderTestingOperation>

/** The target side of the operation.
 */
@property (readonly, nonatomic) NSFileProviderTestingOperationSide targetSide;

/** The identifier of the source item.
 */
@property (readonly, nonatomic) NSFileProviderItemIdentifier sourceItemIdentifier;

/** The identifier of the target item.
 */
@property (readonly, nonatomic) NSFileProviderItemIdentifier targetItemIdentifier;

/** The version of the target item on top of which the deletion is applied
 */
@property (readonly, nonatomic) NSFileProviderItemVersion *targetItemBaseVersion;

/** The domain version at the time the change was discovered on the source side.
 */
@property (readonly, nonatomic, nullable) NSFileProviderDomainVersion *domainVersion;

@end


/** This operation causes the system to fetch the content of an item.
 */
FILEPROVIDER_API_AVAILABILITY_V3_1_IOS
@protocol NSFileProviderTestingContentFetch <NSFileProviderTestingOperation>

/** The side of the operation.
 */
@property (readonly, nonatomic) NSFileProviderTestingOperationSide side;

/** The identifier of the item.
 */
@property (readonly, nonatomic) NSFileProviderItemIdentifier itemIdentifier;

@end


/** This operation causes the system to list the children of an item
 */
FILEPROVIDER_API_AVAILABILITY_V3_1_IOS
@protocol NSFileProviderTestingChildrenEnumeration <NSFileProviderTestingOperation>

/** The side of the operation.
 */
@property (readonly, nonatomic) NSFileProviderTestingOperationSide side;

/** The identifier of the item.
 */
@property (readonly, nonatomic) NSFileProviderItemIdentifier itemIdentifier;

@end


/** This operation causes the system to resolve a collision by rename a colliding item.

 In case two items claim the same disk location because the have the same parent and filename,
 the system will choose to rename one of those items away from that location. The renamed item will
 have the same parent, but a slightly modified name (for instance "a.txt" will be renamed to "a 2.txt").

 This can for instance happen if the case sensitivity of the local filesystem and of the provider differs.
 */
FILEPROVIDER_API_AVAILABILITY_V3_1_IOS
@protocol NSFileProviderTestingCollisionResolution <NSFileProviderTestingOperation>

/** The side of the operation.
 */
@property (readonly, nonatomic) NSFileProviderTestingOperationSide side;

/** The state of the item.
 */
@property (readonly, nonatomic) NSFileProviderItem renamedItem;

@end


NS_ASSUME_NONNULL_END
