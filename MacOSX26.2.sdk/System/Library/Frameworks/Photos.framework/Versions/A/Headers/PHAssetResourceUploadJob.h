
//
//  PHAssetResourceUploadJob.h
//  PhotoKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <Photos/PHObject.h>
#import <Photos/PhotosTypes.h>

@class PHAssetResource;
@class PHFetchOptions;
@class PHFetchResult<T>;

NS_ASSUME_NONNULL_BEGIN

/// An object that represents a request to upload an asset resource.
///
/// Use within an application's `com.apple.photos.background-upload` extension to request an upload of a ``PHAssetResource`` to a destination <doc://com.apple.documentation/documentation/foundation/nsurlrequest>.
///
/// When the extension's principal class receives a call to ``PHBackgroundResourceUploadExtension/process()`` background uploads, it can create new ``PHAssetResourceUploadJob`` objects using ``PHAssetResourceUploadJobChangeRequest``.
///
/// The maximum number of jobs that can be in flight is limited to the ``jobLimit``. To make space for new jobs, you must call ``PHAssetResourceUploadJobChangeRequest/fetchJobsWithAction:options:`` and retry/acknowledge them with ``PHAssetResourceUploadJobChangeRequest/acknowledge:`` or ``PHAssetResourceUploadJobChangeRequest/retryWithDestination:`` respectively.
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(26.1)) API_UNAVAILABLE(macos, macCatalyst, tvos, visionos, watchos)
@interface PHAssetResourceUploadJob : PHObject

/// The maximum number of unacknowledged upload jobs allowed.
///
/// This includes jobs that are in-flight and those that have succeeded or failed.
@property (class, readonly) NSInteger jobLimit;

/// The asset resource this job promises to upload.
@property (strong, readonly) PHAssetResource *resource;

/// The destination to send the job's resource.
@property (strong, readonly) NSURLRequest *destination;

/// The state of this upload job.
@property (readonly) PHAssetResourceUploadJobState state;

/// Returns all asset resource upload jobs applicable for a given action.
///
/// - Parameters:
///     - action: The actions a client can take on a job.
///     - options: The fetch options to be passed in.
///
/// - Returns: The jobs available on which you can apply an action found in ``PHAssetResourceUploadJobAction``.
+ (PHFetchResult<PHAssetResourceUploadJob *> *)fetchJobsWithAction:(PHAssetResourceUploadJobAction)action options:(nullable PHFetchOptions *)options NS_SWIFT_NAME(fetchJobs(action:options:));

@end

NS_ASSUME_NONNULL_END
