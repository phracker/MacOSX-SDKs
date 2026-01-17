//
//  BADownloaderExtension.h
//  BackgroundAssets
//
//  Copyright (c) 2022, Apple Inc.
//  All rights reserved.
//

#import <Foundation/Foundation.h>
#import <BackgroundAssets/BackgroundAssets.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(13.0), ios(16.1), visionos(2.4), tvos(18.4)) API_UNAVAILABLE(watchos)
NS_REFINED_FOR_SWIFT
@protocol BADownloaderExtension <NSObject>

@optional

/*!
 @abstract Invoked by the system when the extension should check for updated content.
 @discussion This method will be invoked by the system upon requested events defined in `BAContentRequest`.
 This method should return a set of all `BAURLDownload`'s that your extension would like to schedule.
 During the invocation of this method, `BADownloadManager` will prohibit the ability to schedule additional downloads
 until this method exits scope. Therefore, all downloads needing to be scheduled should be returned here.
 If a download fails, it can be rescheduled using `BADownloadManager` in any other method in this protocol.
 @param contentRequest The content request event that occurred that caused this method to be invoked.
 @param manifestURL A file URL to the local manifest that was pre-downloaded and specified in your App's Info.plist under the `BAManifestURL`.
 The file is read-only and will be deleted after this method returns. If you wish to keep it, you must copy it out.
 @param extensionInfo Information about your extension that may be useful for making a decision about
 what content needs to be scheduled.
 @result A set of unique `BAURLDownload` objects that the extension should schedule for download.
 @warning You cannot use `BADownloadManager` to manually schedule downloads using this method. All downloads to enqueue must be returned.
 */
- (NSSet<BADownload *> *)downloadsForRequest:(BAContentRequest)contentRequest
                                 manifestURL:(NSURL *)manifestURL
                               extensionInfo:(BAAppExtensionInfo *)extensionInfo;

/// @brief Download is about to begin but requires an authentication challenge to continue.
- (void)backgroundDownload:(BADownload *)download
       didReceiveChallenge:(NSURLAuthenticationChallenge *)challenge
         completionHandler:(void (^ NS_SWIFT_SENDABLE)(NSURLSessionAuthChallengeDisposition disposition, NSURLCredential * _Nullable credential))completionHandler;

/// @abstract This method is called when a download has failed but there is no `BADownloadManager` delegate to handle the completion event.
/// @discussion When a download has failed, this method will be invoked.
/// If a download fails you may reschedule it with `BADownloadManager`.
/// @param download The download object that has failed.
/// @param error The error that caused the failure.
- (void)backgroundDownload:(BADownload *)download failedWithError:(NSError *)error;

/// @abstract This method is called when a download has finished but there is no `BADownloadManager` delegate to handle the completion event.
/// @param download Download that has completed successfully.
/// @param fileURL A location to the file that has been downloaded.
/// @discussion When a download succeeds, this method will be invoked; however it is only invoked if there is no other client using `BADownloadManager`
/// with a hooked in `delegate`. The file located at `fileURL` must be moved before this method exits scope, or it will be deleted.
/// It is strongly advised to move the file to its permanent destination rather than copy it.
/// @warning The file is marked by the system for deletion when the device becomes low on storage. Avoid copying or modifying
/// the file, as this may remove the system's ability to delete the file.
- (void)backgroundDownload:(BADownload *)download finishedWithFileURL:(NSURL *)fileURL;

/// @brief This method may be called shortly before the extension is terminated.
/// @discussion This method is invoked if all extension callbacks have returned or if the extension has run over its allotted runtime.
/// This callback provides a last chance to tidy up state before process termination.
/// @warning This method is advisory only, there will be instances where the extension is terminated before this method is invoked.
/// Do not rely on this method being invoked before the extension is terminated.
- (void)extensionWillTerminate
API_DEPRECATED("extensionWillTerminate will not be invoked in all applicable circumstances and should not be relied upon.", ios(16.1, 16.4), macos(13.0, 13.3))
API_UNAVAILABLE(tvos, watchos, visionos);

@end

NS_ASSUME_NONNULL_END
