//
//  CKFetchWebAuthTokenOperation.h
//  CloudKit
//
//  Copyright © 2014 Apple Inc. All rights reserved.
//

#import <CloudKit/CKDatabaseOperation.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/*! @class CKFetchWebAuthTokenOperation
 *
 *  @abstract This operation will fetch a web auth token given an API token obtained from the CloudKit Dashboard for your container
 */
API_AVAILABLE(macos(10.11), ios(9.2), tvos(9.1), watchos(3.0))
@interface CKFetchWebAuthTokenOperation : CKDatabaseOperation

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithAPIToken:(NSString *)APIToken;

/*! APIToken is expected to be set before you begin this operation. */
@property (nullable, copy, nonatomic) NSString *APIToken;

/*! @abstract This block is called when the operation completes.
 *
 *  @discussion The @code -[NSOperation completionBlock] @endcode will also be called if both are set.
 *  Each @c CKOperation instance has a private serial queue. This queue is used for all callback block invocations.
 *  This block may share mutable state with other blocks assigned to this operation, but any such mutable state
 *  should not be concurrently used outside of blocks assigned to this operation.
 */
@property (nullable, copy, nonatomic) void (^fetchWebAuthTokenCompletionBlock)(NSString * _Nullable webAuthToken, NSError * _Nullable operationError) CK_SWIFT_DEPRECATED("Use fetchWebAuthTokenResultBlock instead", macos(10.11, 12.0), ios(9.2, 15.0), tvos(9.1, 15.0), watchos(3.0, 8.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
