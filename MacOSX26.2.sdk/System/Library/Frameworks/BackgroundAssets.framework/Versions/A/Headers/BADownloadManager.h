//
//  BADownloader.h
//  BackgroundAssets
//
//  Copyright (c) 2022, Apple Inc.
//  All rights reserved.
//

#import <BackgroundAssets/BackgroundAssets.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(13.0), ios(16.1), visionos(2.4), tvos(18.4)) API_UNAVAILABLE(watchos)
@protocol BADownloadManagerDelegate <NSObject>

@optional

/// @brief A download has started.
- (void)downloadDidBegin:(BADownload *)download;

/// @brief A download has paused.
- (void)downloadDidPause:(BADownload *)download;

/// @brief A download has made progress in bytes / total so far / total expected.
- (void)download:(BADownload *)download didWriteBytes:(int64_t)bytesWritten
                                    totalBytesWritten:(int64_t)totalBytesWritten
                            totalBytesExpectedToWrite:(int64_t)totalExpectedBytes;

/// @brief A download has tried to start but gotten a challenge quest.
- (void)download:(BADownload *)download didReceiveChallenge:(NSURLAuthenticationChallenge *)challenge
                                          completionHandler:(void (^)(NSURLSessionAuthChallengeDisposition disposition, NSURLCredential * _Nullable credential))completionHandler;

/// @brief A download has failed with a specific error.
- (void)download:(BADownload *)download failedWithError:(NSError *)error;

/// @brief Download has finished.
/// @param fileURL A location to the file that has been downloaded.
/// @discussion The file located at `fileURL` must be moved before this method exits scope, or it will be deleted.
/// It is strongly advised to move the file to its permanent destination rather than copy it.
/// @warning The file is marked by the system for deletion when the device becomes low on storage. Avoid copying or modifying
/// the file, as this may remove the system's ability to delete the file.
- (void)download:(BADownload *)download finishedWithFileURL:(NSURL *)fileURL;

@end

API_AVAILABLE(macos(13.0), ios(16.1), visionos(2.4), tvos(18.4)) API_UNAVAILABLE(watchos)
@interface BADownloadManager : NSObject

- (instancetype)init
NS_UNAVAILABLE;
+ (instancetype)new
NS_UNAVAILABLE;

/// @brief Gets the singleton downloader object.
@property (class, readonly, strong) BADownloadManager *sharedManager
API_AVAILABLE(macos(13.0), ios(16.1), visionos(2.4), tvos(18.4)) API_UNAVAILABLE(watchos)
NS_SWIFT_NAME(shared);

/// @brief A object confroming to BADownloadManagerDelegate to get notified when actions occur.
@property (weak) id<BADownloadManagerDelegate> delegate
API_AVAILABLE(macos(13.0), ios(16.1), visionos(2.4), tvos(18.4)) API_UNAVAILABLE(watchos);

/// @brief Fetches current downloads.
/// @discussion Fetches the current list of scheduled or in-flight downloads queued by your application or extension.
/// @param error An error representing why the downloads could not be fetched.
/// @return On success, returns a list of scheduled or in-flight downloads. On failure, returns nil and sets @c error.
/// @warning This method can block and should not be called from the main thread.
/// @seealso BADownloadManager:fetchCurrentDownloadsWithCompletionHandler
- (nullable NSArray<BADownload *> *)fetchCurrentDownloads:(NSError* _Nullable __autoreleasing *)error
API_AVAILABLE(macos(13.3), ios(16.4), visionos(2.4), tvos(18.4)) API_UNAVAILABLE(watchos);

/// @brief Fetches current downloads.
/// @discussion Fetches the current list of scheduled or in-flight downloads queued by your application or extension.
/// @param completionHandler A block to recieve the currently scheduled or in-flight downloads. The block is called on the same queue as all the other completion blocks in the class.
- (void)fetchCurrentDownloadsWithCompletionHandler:(void(^ NS_SWIFT_SENDABLE)(NSArray<BADownload *> *downloads, NSError *_Nullable error))completionHandler
API_AVAILABLE(macos(13.0), ios(16.1), visionos(2.4), tvos(18.4)) API_UNAVAILABLE(watchos)
NS_SWIFT_NAME(fetchCurrentDownloads(completionHandler:))
NS_SWIFT_ASYNC_NAME(getter:currentDownloads());

/// @brief Schedules a background download.
/// @discussion Specifies a download to schedule at a given priority. The download will automatically
/// start at the discretion of the system.
/// @param download A BADownload object representing a URL to be downloaded.
/// @param error A NSError representing why the BADownload could not be scheduled.
/// @return YES if @c download was scheduled. NO and @c error set if the download could not be scheduled.
- (BOOL)scheduleDownload:(BADownload *)download
                   error:(NSError* _Nullable __autoreleasing *)error
API_AVAILABLE(macos(13.0), ios(16.1), visionos(2.4), tvos(18.4)) API_UNAVAILABLE(watchos);

/// @brief Acquires exclusive access to the BADownloadManager across the app and application extension.
/// @discussion Acquires exclusive access to the BADownloadManager across the app and application extension. This ensures that your extension and app
/// do not perform operations at the same time. Both the extension and app must use this API to ensure exclusive access.
/// @param performHandler A block that will be executed once exclusive control is acquired.
/// If an error is non-nil then a problem occurred acquiring exclusive access.
- (void)performWithExclusiveControl:(void (^ NS_SWIFT_SENDABLE)(BOOL acquiredLock, NSError *_Nullable error))performHandler
API_AVAILABLE(macos(13.0), ios(16.1), visionos(2.4), tvos(18.4)) API_UNAVAILABLE(watchos)
NS_SWIFT_NAME(withExclusiveControl(_:))
NS_SWIFT_DISABLE_ASYNC;

/// @brief Acquires exclusive access to the BADownloadManager across the app and application extension.
/// @discussion Acquires exclusive access to the BADownloadManager across the app and application extension. This ensures that your extension and app
/// do not perform operations at the same time. Both the extension and app must use this API to ensure exclusive access.
/// @param date A date by which you want exclusive control acquired. If you pass +[NSDate date], control will attempt to be acquired and if it can not be, it will fail instantly.
/// @param performHandler A block that will be executed once exclusive control is acquired.
/// If an error is non-nil then a problem occurred acquiring exclusive access.
- (void)performWithExclusiveControlBeforeDate:(NSDate *)date
                               performHandler:(void (^ NS_SWIFT_SENDABLE)(BOOL acquiredLock, NSError *_Nullable error))performHandler
API_AVAILABLE(macos(13.0), ios(16.1), visionos(2.4), tvos(18.4)) API_UNAVAILABLE(watchos)
NS_SWIFT_NAME(withExclusiveControl(beforeDate:perform:))
NS_SWIFT_DISABLE_ASYNC;

/// @brief Attempts to schedule a BADownload in foreground mode.
/// @discussion Attempts to schedule a BADownload in foreground mode. This download will start (if it has not been started) immediately regrardlesss of battery or
/// network status. The download will remain in this foreground until the download manager is disconnected. This API only functions if the download manager is created in
/// the application and not the download extension. If this API is called from the download extension, NO will be returned along with a NSError with the settings
/// BAErrorDomain : BAErrorCodeCallFromExtensionNotAllowed. If this API is called from a app while it is in the background, NO will be returned along with a NSError
/// with the settings BAErrorDomain : BAErrorCodeCallFromInactiveProcessNotAllowed.
- (BOOL)startForegroundDownload:(BADownload *)download
                          error:(NSError* _Nullable __autoreleasing *)error
API_AVAILABLE(macos(13.0), ios(16.1), visionos(2.4), tvos(18.4)) API_UNAVAILABLE(watchos);

/// @brief Cancels a download.
/// @discussion Attempts to cancel a BADownload. If the download has not been schduled or has already completed, NO is returned along with a NSError set
/// to BAErrorDomain : BAErrorCodeDownloadNotScheduled.
/// @return YES if the download is canceled. NO if the download could not be canceled, @c error will be set with a reason why.
- (BOOL)cancelDownload:(BADownload *)download
                 error:(NSError **)error
API_AVAILABLE(macos(13.0), ios(16.1), visionos(2.4), tvos(18.4)) API_UNAVAILABLE(watchos);

@end

NS_ASSUME_NONNULL_END
