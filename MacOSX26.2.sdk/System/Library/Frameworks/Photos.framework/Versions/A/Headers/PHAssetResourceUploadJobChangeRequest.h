//
//  PHAssetResourceUploadJobChangeRequest.h
//  PhotoKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//
#import <Photos/PHChangeRequest.h>

@class PHAssetResource;
@class PHAssetResourceUploadJob;

NS_ASSUME_NONNULL_BEGIN

/// Use within an application's `com.apple.photos.background-upload` extension to create and change ``PHAssetResourceUploadJob`` records.
///
/// When the extension's principal class receives a call to `process` background uploads, it can create new ``PHAssetResourceUploadJob``s through calls to perform changes on a PHPhotoLibrary using ``PHAssetResourceUploadJobChangeRequest`` and any in-flight upload jobs can be handled by updating their state to mark them as acknowledged, or to be retried. The maximum number of jobs that can be in flight is limited to the ``PHAssetResourceUploadJob.jobLimit``.
///
/// ``PHAssetResourceUploadJobChangeRequest`` can only be created or used within a photo library change block. For details on change blocks, see ``PHPhotoLibrary``.
API_AVAILABLE(ios(26.1)) API_UNAVAILABLE(macos, macCatalyst, tvos, visionos, watchos)
@interface PHAssetResourceUploadJobChangeRequest : PHChangeRequest

/// Creates an asset resource upload job.
///
/// If the number of jobs exceeds ``PHAssetResourceUploadJob/jobLimit`` the photo library ``performChanges`` request will fail with a ``PHPhotosErrorLimitExceeded`` error.
/// To generate jobs after this limit is triggered, you must acknowledge succeeded/failed jobs, and wait for the registered/pending ones to finish uploading, which will make those jobs also succeeded/failed.
///
/// - Parameter:
///     - destination: the destination <doc://com.apple.documentation/foundation/nsurlrequest> to which this asset resource will be sent.
///     - resource: the asset resource to be uploaded.
+ (void)createJobWithDestination:(NSURLRequest *)destination resource:(PHAssetResource *)resource NS_SWIFT_NAME(createJob(destination:resource:));

/// Creates a request for modifying the specified upload job.
///
/// - Parameter job: a job to be modified.
+ (nullable instancetype)changeRequestForUploadJob:(nonnull PHAssetResourceUploadJob *)job;

/// Acknowledges a successful or failed job. Jobs must be acknowledged to free up space for ``PHAssetResourceUploadJob/jobLimit``.
- (void)acknowledge;

/// Retries a job that is failed, unacknowledged, and has not been retried before. Successful retries also free up space for ``PHAssetResourceUploadJob/jobLimit``.
- (void)retryWithDestination:(nullable NSURLRequest *)destination NS_SWIFT_NAME(retry(destination:));

@end

NS_ASSUME_NONNULL_END
