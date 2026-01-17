//
//  CKFetchShareMetadataOperation.h
//  CloudKit
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <CloudKit/CKOperation.h>

/* Since you can't know what container this share is in before you fetch its metadata, you may run this operation in any container you have access to */

@class CKShareMetadata, CKFetchShareMetadataOptions;

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0))
@interface CKFetchShareMetadataOperation : CKOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithShareURLs:(NSArray<NSURL *> *)shareURLs;

@property (nonatomic, copy, nullable) NSArray<NSURL *> *shareURLs;

/* If set to YES, the resulting CKShareMetadata will have a rootRecord object filled out.  Defaults to NO.
 The resulting CKShareMetadata will have a rootRecordID property regardless of the value of this property. */
@property (nonatomic, assign) BOOL shouldFetchRootRecord;

/* Declares which user-defined keys should be fetched and added to the resulting rootRecord.  Only consulted if shouldFetchRootRecord is YES.
 If nil, declares the entire root record should be downloaded. If set to an empty array, declares that no user fields should be downloaded.  Defaults to nil. */
@property (nonatomic, copy, nullable) NSArray<NSString *> *rootRecordDesiredKeys;

@property (nonatomic, copy, nullable) void (^perShareMetadataBlock)(NSURL *shareURL, CKShareMetadata * _Nullable shareMetadata, NSError * _Nullable error);

@property (nonatomic, copy, nullable) void (^fetchShareMetadataCompletionBlock)(NSError * _Nullable operationError);

@end
NS_ASSUME_NONNULL_END
