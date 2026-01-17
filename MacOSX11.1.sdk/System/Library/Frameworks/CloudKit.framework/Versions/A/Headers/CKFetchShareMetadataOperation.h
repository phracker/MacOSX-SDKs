//
//  CKFetchShareMetadataOperation.h
//  CloudKit
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <CloudKit/CKOperation.h>
#import <CloudKit/CKRecord.h>

@class CKShareMetadata, CKFetchShareMetadataOptions;

NS_ASSUME_NONNULL_BEGIN

/*! @class CKFetchShareMetadataOperation
 *
 *  @abstract Fetch the @c CKShareMetadata for a share URL.
 *
 *  @discussion Since you can't know what container this share is in before you fetch its metadata, you may run this operation in any container you have access to
 */
API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0))
@interface CKFetchShareMetadataOperation : CKOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithShareURLs:(NSArray<NSURL *> *)shareURLs;

@property (nonatomic, copy, nullable) NSArray<NSURL *> *shareURLs;

/*! @abstract If set to YES, the resulting @c CKShareMetadata will have a @c rootRecord object filled out.
 *
 *  @discussion Defaults to @c NO.
 *  The resulting @c CKShareMetadata will have a @c rootRecordID property regardless of the value of this property.
 */
@property (nonatomic, assign) BOOL shouldFetchRootRecord;

/*! @abstract Declares which user-defined keys should be fetched and added to the resulting @c rootRecord.
 *
 *  @discussion Only consulted if @c shouldFetchRootRecord is @c YES.
 *  If nil, declares the entire root record should be downloaded. If set to an empty array, declares that no user fields should be downloaded.
 *  Defaults to @c nil.
 */
@property (nonatomic, copy, nullable) NSArray<CKRecordFieldKey> *rootRecordDesiredKeys;

/*! @abstract Called once for each share URL that the server processed
 *
 *  @discussion Each @c CKOperation instance has a private serial queue. This queue is used for all callback block invocations.
 */
@property (nonatomic, copy, nullable) void (^perShareMetadataBlock)(NSURL *shareURL, CKShareMetadata * _Nullable shareMetadata, NSError * _Nullable error);

/*! @abstract This block is called when the operation completes.
 *
 *  @discussion The @code -[NSOperation completionBlock] @endcode will also be called if both are set.
 *  Each @c CKOperation instance has a private serial queue. This queue is used for all callback block invocations.
 */
@property (nonatomic, copy, nullable) void (^fetchShareMetadataCompletionBlock)(NSError * _Nullable operationError);

@end

NS_ASSUME_NONNULL_END
