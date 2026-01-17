//
//  CKAcceptSharesOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CloudKit/CKDatabaseOperation.h>

@class CKShare, CKShareMetadata;

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0))
@interface CKAcceptSharesOperation : CKOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithShareMetadatas:(NSArray<CKShareMetadata *> *)shareMetadatas;

@property (nonatomic, copy, nullable) NSArray<CKShareMetadata *> *shareMetadatas;

/*! Called once for each share metadata that the server processed. If error is nil then the share was successfully accepted. */
@property (nonatomic, copy, nullable) void (^perShareCompletionBlock)(CKShareMetadata *shareMetadata, CKShare * _Nullable acceptedShare, NSError * _Nullable error);

/*! @abstract This block is called when the operation completes.
 *
 *  @discussion The [NSOperation completionBlock] will also be called if both are set.
 *  If the error is `CKErrorPartialFailure`, the error's userInfo dictionary contains a dictionary of shareURLs to errors keyed off of `CKPartialErrorsByItemIDKey`.
 *  This call happens as soon as the server has seen all record changes, and may be invoked while the server is processing the side effects of those changes.
 */
@property (nonatomic, copy, nullable) void (^acceptSharesCompletionBlock)(NSError * _Nullable operationError);
@end

NS_ASSUME_NONNULL_END
