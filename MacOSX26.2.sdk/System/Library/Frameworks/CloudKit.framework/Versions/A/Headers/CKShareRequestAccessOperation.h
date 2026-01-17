//
//  CKShareRequestAccessOperation.h
//  CloudKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CloudKit/CKDatabaseOperation.h>

@class CKShare;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0))
@interface CKShareRequestAccessOperation : CKOperation

/// Creates a new, empty share request access operation.
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/// Creates a share request access operation configured with specified share URLs.
///
/// - Parameter shareURLs: An array of `NSURL` objects representing the shares to request access to.
/// - Returns: A configured ``CKShareRequestAccessOperation`` instance.
- (instancetype)initWithShareURLs:(NSArray<NSURL *> *)shareURLs NS_SWIFT_NAME(init(shareURLs:));

/// The URLs of the shares to request access to.
///
/// Include multiple URLs to request access to multiple shares simultaneously. The server processes each URL independently.
@property (nullable, copy, nonatomic) NSArray<NSURL *> *shareURLs;

/// A completion block called once for each processed share URL.
///
/// The server does not disclose share existence to protect user privacy.
///
/// - Parameters:
///   - shareURL: The URL of the share that was processed.
///   - shareRequestAccessError: An error describing why the access request failed, or `nil` if successful.
@property (nullable, copy, nonatomic) void (^perShareAccessRequestCompletionBlock)(NSURL *shareURL, NSError * _Nullable shareRequestAccessError) NS_REFINED_FOR_SWIFT;

/// A completion block called when the entire operation finishes.
///
/// - Parameter operationError: An error describing the overall operation failure, or `nil` if successful.
///
/// If `operationError` is `CKErrorPartialFailure`, the `userInfo` dictionary contains detailed errors for each share under ``CKPartialErrorsByItemIDKey``.
@property (nullable, copy, nonatomic) void (^shareRequestAccessCompletionBlock)(NSError * _Nullable operationError) NS_REFINED_FOR_SWIFT;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
