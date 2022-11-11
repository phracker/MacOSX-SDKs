#if !__has_include(<AVFCore/AVAssetDownloadTask.h>)
/*
	File:  AVAssetDownloadTask.h

	Framework:  AVFoundation

	Copyright 2015-2018 Apple Inc. All rights reserved.

*/

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>
#import	<AVFoundation/AVAsset.h>
#import <AVFoundation/AVMediaSelection.h>
#import <AVFoundation/AVAssetVariant.h>
#import <CoreMedia/CMTimeRange.h>

NS_ASSUME_NONNULL_BEGIN

@class AVAssetVariantQualifier;
@class AVAssetDownloadContentConfiguration;

// Keys for options dictionary for use with -[AVAssetDownloadURLSession assetDownloadTaskWithURLAsset:assetTitle:assetArtworkData:options:]

/*!
 @constant		AVAssetDownloadTaskMinimumRequiredMediaBitrateKey
 @abstract		The lowest media bitrate greater than or equal to this value will be selected. Value should be a NSNumber in bps. If no suitable media bitrate is found, the highest media bitrate will be selected.
				The value for this key should be a NSNumber.
 @discussion	By default, the highest media bitrate will be selected for download.
*/
AVF_EXPORT NSString *const AVAssetDownloadTaskMinimumRequiredMediaBitrateKey API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(tvos, watchos);

/*!
 @constant		AVAssetDownloadTaskMinimumRequiredPresentationSizeKey
 @abstract		The lowest media presentation size greater than or equal to this value will be selected. If no suitable media presentation size is found, the highest media presentation size will be selected.
				The value for this key should be a NSValue of CGSize.
 @discussion	By default, the highest media presentation size will be selected for download.
*/
AVF_EXPORT NSString *const AVAssetDownloadTaskMinimumRequiredPresentationSizeKey API_AVAILABLE(macos(11.0), ios(14.0)) API_UNAVAILABLE(tvos, watchos);

/*!
 @constant		AVAssetDownloadTaskMediaSelectionKey
 @abstract		The media selection for this download.
				The value for this key should be an AVMediaSelection.
 @discussion	By default, media selections for AVAssetDownloadTask will be automatically selected.
*/
AVF_EXPORT NSString *const AVAssetDownloadTaskMediaSelectionKey API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(tvos, watchos);

/*!
 @constant		AVAssetDownloadTaskMediaSelectionPrefersMultichannelKey
 @abstract		Download the specified media selections with or without support for multichannel playback.
 				The value for this key should be an NSNumber representing a BOOL.
 @discussion	By default AVAssetDownloadTask will prefer multichannel by downloading the most capable multichannel rendition available in additon to stereo.
*/
AVF_EXPORT NSString *const AVAssetDownloadTaskMediaSelectionPrefersMultichannelKey API_AVAILABLE(macos(10.15), ios(13.0)) API_UNAVAILABLE(tvos, watchos);

/*!
@constant		AVAssetDownloadTaskPrefersLosslessAudioKey
@abstract		Download the specified media selections in lossless audio representation.
				The value for this key should be an NSNumber representing a BOOL.
@discussion		By default AVAssetDownloadTask will prefer lossy audio representation.
 */
AVF_EXPORT NSString *const AVAssetDownloadTaskPrefersLosslessAudioKey API_AVAILABLE(macos(11.3), ios(14.5)) API_UNAVAILABLE(tvos, watchos);

/*!
@constant		AVAssetDownloadTaskPrefersHDRKey
@abstract		Download the specified media selections with or without HDR content.
				The value for this key should be an NSNumber representing a BOOL.
@discussion		By default AVAssetDownloadTask will prefer HDR content.
 */
AVF_EXPORT NSString *const AVAssetDownloadTaskPrefersHDRKey API_AVAILABLE(macos(11.0), ios(14.0)) API_UNAVAILABLE(tvos, watchos);

/*!
 @class			AVAssetDownloadTask
 @abstract		A NSURLSessionTask that accepts remote AVURLAssets to download locally.
 @discussion	Should be created with -[AVAssetDownloadURLSession assetDownloadTaskWithURLAsset:assetTitle:assetArtworkData:options:]. To utilize local data for playback for downloads that are in-progress, re-use the URLAsset supplied in initialization. An AVAssetDownloadTask may be instantiated with a destinationURL pointing to an existing asset on disk, for the purpose of completing or augmenting a downloaded asset.
*/

API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(tvos, watchos)
@interface AVAssetDownloadTask : NSURLSessionTask

/*!
 @property		URLAsset
 @abstract		The asset supplied to the download task upon initialization.
*/
@property (nonatomic, readonly) AVURLAsset *URLAsset;

/*!
 @property		destinationURL
 @abstract		The file URL supplied to the download task upon initialization.
 @discussion	This URL may have been appended with the appropriate extension for the asset.
*/
@property (nonatomic, readonly) NSURL *destinationURL API_DEPRECATED("Use the URL property of URLAsset instead", ios(9.0, 10.0)) API_UNAVAILABLE(tvos, watchos) API_UNAVAILABLE(macos);

/*!
 @property		options
 @abstract		The options supplied to the download task upon initialization.
*/
@property (nonatomic, readonly, nullable) NSDictionary<NSString *, id> *options;

/*!
 @property		loadedTimeRanges
 @abstract		This property provides a collection of time ranges for which the download task has media data already downloaded and playable. The ranges provided might be discontinuous.
 @discussion	Returns an NSArray of NSValues containing CMTimeRanges.
*/
@property (nonatomic, readonly) NSArray<NSValue *> *loadedTimeRanges;

// NSURLRequest and NSURLResponse objects are not available for AVAssetDownloadTask
AV_INIT_UNAVAILABLE
@property (readonly, copy) NSURLRequest *originalRequest NS_UNAVAILABLE;
@property (readonly, copy) NSURLRequest *currentRequest NS_UNAVAILABLE;
@property (readonly, copy) NSURLResponse *response NS_UNAVAILABLE;

@end

/*!
 @class			AVAssetDownloadConfiguration
 @abstract		Configuration parameters for the download task.
 @discussion	Download configuration consists of primary and auxiliary content configurations. Primary content configuration represents the primary set of renditions essential for offline playback. Auxiliary content configurations represent additional configurations to complement the primary.
				For example, the primary content configuration may represent stereo audio renditions and auxiliary configuration may represent complementing multichannel audio renditions.
 
				It is important to configure your download configuration object appropriately before using it to create a download task. Download task makes a copy of the configuration settings you provide and use those settings to configure the task. Once configured, the task object ignores any changes you make to the NSURLSessionConfiguration object. If you need to modify your settings, you must update the download configuration object and use it to create a new download task object.
 */
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos)
@interface AVAssetDownloadConfiguration : NSObject

AV_INIT_UNAVAILABLE

/*!
 @method		downloadConfigurationWithAsset:title:
 @abstract		Creates and initializes a download configuration object.
 @discussion	This method will throw an exception if AVURLAsset has been invalidated.
 @param			asset
				The asset to create the download configuration for.
 @param			title
				A human readable title for this asset, expected to be as suitable as possible for the user's preferred languages. Will show up in the usage pane of the settings app.
*/
+ (instancetype)downloadConfigurationWithAsset:(AVURLAsset *)asset title:(NSString *)title;

/*!
 @property		assetArtworkData
 @abstract		NSData representing artwork data for this asset. Optional. May be displayed, for example, by the usage pane of the Settings app. Must work with +[UIImage imageWithData:].
*/
@property (nonatomic, copy, nullable) NSData *artworkData;

/*!
 @property		primaryContentConfiguration
 @abstract		The primary content for the download.
*/
@property (nonatomic, readonly) AVAssetDownloadContentConfiguration *primaryContentConfiguration;

/*!
 @property		auxiliaryContentConfigurations
 @abstract		The auxiliary content for the download. Optional.
 @discussion	By default, auxiliaryContentConfigurations will have one or more default auxiliary content configurations. These content configurations can be augmented with additional content configurations or removed entirely if no auxiliary content is desired.
*/
@property (nonatomic, copy) NSArray <AVAssetDownloadContentConfiguration *> *auxiliaryContentConfigurations;

/*!
 @property		optimizesAuxiliaryContentConfigurations
 @abstract		Optimizes auxiliary content selection depending on the primary to minimize total number of video renditions downloaded. True by default.
 @discussion	For example, if the primary content configuration represents stereo renditions and auxiliary content configuration represents multichannel audio renditions, auxiliary multichannel variant will be chosen so as to avoid downloading duplicate video renditions.
*/
@property (nonatomic) BOOL optimizesAuxiliaryContentConfigurations;

@end

/*!
 @class			AVAssetDownloadContentConfiguration
 @abstract		Represents the configuration consisting of variant and the variant's media options.
*/
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos)
@interface AVAssetDownloadContentConfiguration : NSObject <NSCopying>

/*!
 @property		variantQualifiers
 @abstract		An array of variant qualifiers.
 @discussion	The qualifiers are expected to be added in the preferential order and will be evaluated in that order until the qualifier matches one or more AVAssetVariants. Only those variants which can be played on the current device configuration will be initially chosen for evaluation. If there is more than one match, automatic variant selection will be used to choose among the matched.
				If a variant qualifier is constructed to explicitly choose a variant, no evaluation is performed and the variant provided will be downloaded as is, even if it is not playable on current device configuration.
				If a variant qualifier has not been provided, or if the variant qualifier when evaluated does not match any of the variants which can be played according to the current device configuration, automatic variant selection will be used.
*/
@property (nonatomic, copy) NSArray<AVAssetVariantQualifier *> *variantQualifiers;

/*!
 @property		mediaSelections
 @abstract		An array of media selections obtained from the AVAsset.
 @discussion	If a media selection is not provided, automatic media selection associated with the asset will be used.
*/
@property (nonatomic, copy) NSArray<AVMediaSelection *> *mediaSelections;

@end

/*!
 @class			AVAggregateAssetDownloadTask
 @abstract		An AVAssetDownloadTask used for downloading multiple AVMediaSelections for a single AVAsset, under the umbrella of a single download task.
 @discussion	Should be created with -[AVAssetDownloadURLSession aggregateAssetDownloadTaskWithURLAsset:mediaSelections:assetTitle:assetArtworkData:options:. For progress tracking, monitor the delegate callbacks for each childAssetDownloadTask.
*/
API_AVAILABLE(macos(10.15), ios(11.0)) API_UNAVAILABLE(tvos, watchos)
@interface AVAggregateAssetDownloadTask : NSURLSessionTask

/*!
 @property		URLAsset
 @abstract		The asset supplied to the download task upon initialization.
*/
@property (nonatomic, readonly) AVURLAsset *URLAsset;

// NSURLRequest and NSURLResponse objects are not available for AVAggregateAssetDownloadTask
AV_INIT_UNAVAILABLE
@property (readonly, copy) NSURLRequest *originalRequest NS_UNAVAILABLE;
@property (readonly, copy) NSURLRequest *currentRequest NS_UNAVAILABLE;
@property (readonly, copy) NSURLResponse *response NS_UNAVAILABLE;

@end

/*!
 @protocol		AVAssetDownloadDelegate
 @abstract		Delegate methods to implement when adopting AVAssetDownloadTask.
*/

API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(tvos, watchos)
@protocol AVAssetDownloadDelegate <NSURLSessionTaskDelegate>
@optional
/*!
 @method		URLSession:assetDownloadTask:didFinishDownloadingToURL:
 @abstract		Sent when a download task that has completed a download.
 @discussion	Unlike NSURLSessionDownloadDelegate, the delegate should NOT move the file from this directory after it has been called. Downloaded assets must remain at the system provided URL. URLSession:task:didCompleteWithError: will still be called.
 @param			session
				The session the asset download task is on.
 @param			assetDownloadTask
				The AVAssetDownloadTask whose downloaded completed.
 @param			location
				The location the asset has been downloaded to.
*/
- (void)URLSession:(NSURLSession *)session assetDownloadTask:(AVAssetDownloadTask *)assetDownloadTask didFinishDownloadingToURL:(NSURL *)location API_AVAILABLE(macos(10.15), ios(10.0)) API_UNAVAILABLE(tvos, watchos);

/*!
 @method		URLSession:assetDownloadTask:didLoadTimeRange:totalTimeRangesLoaded:timeRangeExpectedToLoad:
 @abstract		Method to adopt to subscribe to progress updates of an AVAssetDownloadTask.
 @param			session
				The session the asset download task is on.
 @param			assetDownloadTask
				The AVAssetDownloadTask which is being updated.
 @param			timeRange
				A CMTimeRange indicating the time range loaded since the last time this method was called.
 @param			loadedTimeRanges
				A NSArray of NSValues of CMTimeRanges indicating all the time ranges loaded by this asset download task.
 @param			timeRangeExpectedToLoad
				A CMTimeRange indicating the single time range that is expected to be loaded when the download is complete.
*/
- (void)URLSession:(NSURLSession *)session assetDownloadTask:(AVAssetDownloadTask *)assetDownloadTask didLoadTimeRange:(CMTimeRange)timeRange totalTimeRangesLoaded:(NSArray<NSValue *> *)loadedTimeRanges timeRangeExpectedToLoad:(CMTimeRange)timeRangeExpectedToLoad API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(tvos, watchos);

/*
 @method		URLSession:assetDownloadTask:didResolveMediaSelection:
 @abstract		Method called when the media selection for the download is fully resolved, including any automatic selections.
 @param			session
				The session the asset download task is on.
 @param			assetDownloadTask
				The AVAssetDownloadTask which is being updated.
 @param			resolvedMediaSelection
				The resolved media selection for the download task. For the best chance of playing back downloaded content without further network I/O, apply this selection to subsequent AVPlayerItems.
*/
- (void)URLSession:(NSURLSession *)session assetDownloadTask:(AVAssetDownloadTask *)assetDownloadTask didResolveMediaSelection:(AVMediaSelection *)resolvedMediaSelection API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(tvos, watchos);

/*
 @method		URLSession:aggregateAssetDownloadTask:willDownloadToURL:
 @abstract		Method called when the aggregate download task determines the location this asset will be downloaded to.
 @discussion	This URL should be saved for future instantiations of AVAsset. While an AVAsset already exists for this content, it is advisable to re-use that instance.
 @param			session
				The session the aggregate asset download task is on.
 @param			aggregateAssetDownloadTask
				The AVAggregateAssetDownloadTask.
 @param			location
				The file URL this task will download media data to.
*/
- (void)URLSession:(NSURLSession *)session aggregateAssetDownloadTask:(AVAggregateAssetDownloadTask *)aggregateAssetDownloadTask willDownloadToURL:(NSURL *)location API_AVAILABLE(macos(10.15), ios(11.0)) API_UNAVAILABLE(tvos, watchos);

/*
 @method		URLSession:aggregateAssetDownloadTask:didCompleteForMediaSelection:
 @abstract		Method called when a child AVAssetDownloadTask completes.
 @param			session
				The session the aggregate asset download task is on.
 @param			aggregateAssetDownloadTask
				The AVAggregateAssetDownloadTask.
 @param			mediaSelection
				The AVMediaSelection which is now fully available for offline use.
*/
- (void)URLSession:(NSURLSession *)session aggregateAssetDownloadTask:(AVAggregateAssetDownloadTask *)aggregateAssetDownloadTask didCompleteForMediaSelection:(AVMediaSelection *)mediaSelection API_AVAILABLE(macos(10.15), ios(11.0)) API_UNAVAILABLE(tvos, watchos);

/*
 @method		URLSession:aggregateAssetDownloadTask:didLoadTimeRange:totalTimeRangesLoaded:timeRangeExpectedToLoad:forMediaSelection:
 @abstract		Method to adopt to subscribe to progress updates of an AVAggregateAssetDownloadTask
 @param			session
				The session the asset download task is on.
 @param			aggregateAssetDownloadTask
				The AVAggregateAssetDownloadTask.
 @param			timeRange
				A CMTimeRange indicating the time range loaded for the media selection being downloaded.
 @param			loadedTimeRanges
				A NSArray of NSValues of CMTimeRanges indicating all the time ranges loaded for the media selection being downloaded.
 @param			timeRangeExpectedToLoad
				A CMTimeRange indicating the single time range that is expected to be loaded when the download is complete for the media selection being downloaded.
 @param			mediaSelection
				The media selection which has additional media data loaded for offline use.
*/
- (void)URLSession:(NSURLSession *)session aggregateAssetDownloadTask:(AVAggregateAssetDownloadTask *)aggregateAssetDownloadTask didLoadTimeRange:(CMTimeRange)timeRange totalTimeRangesLoaded:(NSArray<NSValue *> *)loadedTimeRanges timeRangeExpectedToLoad:(CMTimeRange)timeRangeExpectedToLoad forMediaSelection:(AVMediaSelection *)mediaSelection API_AVAILABLE(macos(10.15), ios(11.0)) API_UNAVAILABLE(tvos, watchos);

@optional
/*!
 @method		URLSession:assetDownloadTask:willDownloadVariants:
 @abstract		Sent when a download task has completed the variant selection.
 @param			session
				The session the asset download task is on.
 @param			assetDownloadTask
				The asset download task.
 @param			variants
				The variants chosen. Depends on the environmental condition when the download starts.
*/
- (void)URLSession:(NSURLSession *)session assetDownloadTask:(AVAssetDownloadTask *)assetDownloadTask willDownloadVariants:(NSArray <AVAssetVariant *> *)variants API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos);

@end

/*!
 @class			AVAssetDownloadURLSession
 @abstract		A subclass of NSURLSession to support AVAssetDownloadTask.
*/
API_AVAILABLE(macos(10.15), ios(9.0)) API_UNAVAILABLE(tvos, watchos)
@interface AVAssetDownloadURLSession : NSURLSession

/*!
 @method		sessionWithConfiguration:assetDownloadDelegate:delegateQueue:
 @abstract		Creates and initializes an AVAssetDownloadURLSession for use with AVAssetDownloadTasks.
 @param			configuration
				The configuration for this URLSession. Must be a background configuration.
 @param			delegate
				The delegate object to handle asset download progress updates and other session related events.
 @param			delegateQueue
				The queue to receive delegate callbacks on. If nil, a serial queue will be provided.
*/
+ (AVAssetDownloadURLSession *)sessionWithConfiguration:(NSURLSessionConfiguration *)configuration assetDownloadDelegate:(nullable id <AVAssetDownloadDelegate>)delegate delegateQueue:(nullable NSOperationQueue *)delegateQueue;

/*!
 @method		assetDownloadTaskWithURLAsset:destinationURL:options:
 @abstract		Creates and initializes an AVAssetDownloadTask to be used with this AVAssetDownloadURLSession.
 @discussion	This method may return nil if the URLSession has been invalidated.
 @param			URLAsset
				The AVURLAsset to download locally.
 @param			destinationURL
				The local URL to download the asset to. This must be a file URL.
 @param			options
				See AVAssetDownloadTask*Key above. Configures non-default behavior for the download task. Using this parameter is required for downloading non-default media selections for HLS assets.
*/
- (nullable AVAssetDownloadTask *)assetDownloadTaskWithURLAsset:(AVURLAsset *)URLAsset destinationURL:(NSURL *)destinationURL options:(nullable NSDictionary<NSString *, id> *)options API_DEPRECATED("Use assetDownloadTaskWithURLAsset:assetTitle:assetArtworkData:options: instead", ios(9.0, 10.0)) API_UNAVAILABLE(tvos, watchos) API_UNAVAILABLE(macos);

/*!
 @method		assetDownloadTaskWithURLAsset:assetTitle:assetArtworkData:options:
 @abstract		Creates and initializes an AVAssetDownloadTask to be used with this AVAssetDownloadURLSession.
 @discussion	This method may return nil if the URLSession has been invalidated.
 @param			URLAsset
				The AVURLAsset to download locally.
 @param			title
				A human readable title for this asset, expected to be as suitable as possible for the user's preferred languages. Will show up in the usage pane of the settings app.
 @param			artworkData
				NSData representing artwork data for this asset. Optional. Will show up in the usage pane of the settings app. Must work with +[UIImage imageWithData:].
 @param			options
				See AVAssetDownloadTask*Key above. Configures non-default behavior for the download task. Using this parameter is required for downloading non-default media selections for HLS assets.
*/
- (nullable AVAssetDownloadTask *)assetDownloadTaskWithURLAsset:(AVURLAsset *)URLAsset assetTitle:(NSString *)title assetArtworkData:(nullable NSData *)artworkData options:(nullable NSDictionary<NSString *, id> *)options API_AVAILABLE(macos(10.15), ios(10.0)) API_UNAVAILABLE(tvos, watchos);

/*!
 @method		aggregateAssetDownloadTaskWithURLAsset:mediaSelections:assetTitle:assetArtworkData:options:
 @abstract		Creates and initializes an AVAggregateAssetDownloadTask to download multiple AVMediaSelections on an AVURLAsset.
 @discussion	This method may return nil if the URLSession has been invalidated. The value of AVAssetDownloadTaskMediaSelectionKey will be ignored.
 @param			URLAsset
				The AVURLAsset to download locally.
 @param			mediaSelections
				A list of AVMediaSelections. Each AVMediaSelection will correspond to a childAssetDownloadTask. Use -[AVAsset allMediaSelections] to download all AVMediaSelections on this AVAsset.
 @param			title
				A human readable title for this asset, expected to be as suitable as possible for the user's preferred languages. Will show up in the usage pane of the settings app.
 @param			artworkData
				Artwork data for this asset. Optional. Will show up in the usage pane of the settings app.
 @param			options
				See AVAssetDownloadTask*Key above. Configures non-default behavior for the download task.
*/
- (nullable AVAggregateAssetDownloadTask *)aggregateAssetDownloadTaskWithURLAsset:(AVURLAsset *)URLAsset mediaSelections:(NSArray <AVMediaSelection *> *)mediaSelections assetTitle:(NSString *)title assetArtworkData:(nullable NSData *)artworkData options:(nullable NSDictionary<NSString *, id> *)options API_AVAILABLE(macos(10.15), ios(11.0)) API_UNAVAILABLE(tvos, watchos);

/*!
 @method		assetDownloadTaskWithConfiguration:
 @abstract		Creates and initializes an AVAssetDownloadTask to be used with this AVAssetDownloadURLSession.
 @discussion	This method will throw an exception if the URLSession has been invalidated.
 @param			downloadConfiguration
				The configuration to be used to create the download task.
*/
- (AVAssetDownloadTask *)assetDownloadTaskWithConfiguration:(AVAssetDownloadConfiguration *)downloadConfiguration API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0));

// only AVAssetDownloadTasks can be created with AVAssetDownloadURLSession
AV_INIT_UNAVAILABLE
+ (NSURLSession *)sharedSession NS_UNAVAILABLE;
+ (NSURLSession *)sessionWithConfiguration:(NSURLSessionConfiguration *)configuration NS_UNAVAILABLE;
+ (NSURLSession *)sessionWithConfiguration:(NSURLSessionConfiguration *)configuration delegate:(nullable id <NSURLSessionDelegate>)delegate delegateQueue:(nullable NSOperationQueue *)queue NS_UNAVAILABLE;
- (NSURLSessionDataTask *)dataTaskWithRequest:(NSURLRequest *)request NS_UNAVAILABLE;
- (NSURLSessionDataTask *)dataTaskWithURL:(NSURL *)url NS_UNAVAILABLE;
- (NSURLSessionUploadTask *)uploadTaskWithRequest:(NSURLRequest *)request fromFile:(NSURL *)fileURL NS_UNAVAILABLE;
- (NSURLSessionUploadTask *)uploadTaskWithRequest:(NSURLRequest *)request fromData:(NSData *)bodyData NS_UNAVAILABLE;
- (NSURLSessionUploadTask *)uploadTaskWithStreamedRequest:(NSURLRequest *)request NS_UNAVAILABLE;
- (NSURLSessionDownloadTask *)downloadTaskWithRequest:(NSURLRequest *)request NS_UNAVAILABLE;
- (NSURLSessionDownloadTask *)downloadTaskWithURL:(NSURL *)url NS_UNAVAILABLE;
- (NSURLSessionDownloadTask *)downloadTaskWithResumeData:(NSData *)resumeData NS_UNAVAILABLE;
- (NSURLSessionDataTask *)dataTaskWithRequest:(NSURLRequest *)request completionHandler:(void (^)(NSData *data, NSURLResponse *response, NSError *error))completionHandler NS_UNAVAILABLE;
- (NSURLSessionDataTask *)dataTaskWithURL:(NSURL *)url completionHandler:(void (^)(NSData *data, NSURLResponse *response, NSError *error))completionHandler NS_UNAVAILABLE;
- (NSURLSessionUploadTask *)uploadTaskWithRequest:(NSURLRequest *)request fromFile:(NSURL *)fileURL completionHandler:(void (^)(NSData *data, NSURLResponse *response, NSError *error))completionHandler NS_UNAVAILABLE;
- (NSURLSessionUploadTask *)uploadTaskWithRequest:(NSURLRequest *)request fromData:(nullable NSData *)bodyData completionHandler:(void (^)(NSData *data, NSURLResponse *response, NSError *error))completionHandler NS_UNAVAILABLE;
- (NSURLSessionDownloadTask *)downloadTaskWithRequest:(NSURLRequest *)request completionHandler:(void (^)(NSURL *location, NSURLResponse *response, NSError *error))completionHandler NS_UNAVAILABLE;
- (NSURLSessionDownloadTask *)downloadTaskWithURL:(NSURL *)url completionHandler:(void (^)(NSURL *location, NSURLResponse *response, NSError *error))completionHandler NS_UNAVAILABLE;
- (NSURLSessionDownloadTask *)downloadTaskWithResumeData:(NSData *)resumeData completionHandler:(void (^)(NSURL *location, NSURLResponse *response, NSError *error))completionHandler NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCore/AVAssetDownloadTask.h>
#endif
