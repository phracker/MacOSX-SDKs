/*
	File:  AVAssetExportSession.h

	Framework:  AVFoundation
 
	Copyright 2010-2013 Apple Inc. All rights reserved.

*/


#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>
#import <CoreMedia/CMTime.h>
#import <CoreMedia/CMTimeRange.h>

// for CGSize
#if TARGET_OS_IPHONE
#import <CoreGraphics/CoreGraphics.h>
#else // ! TARGET_OS_IPHONE
#import <ApplicationServices/../Frameworks/CoreGraphics.framework/Headers/CoreGraphics.h>
#endif // ! TARGET_OS_IPHONE

/*!
	@class		AVAssetExportSession

	@abstract	An AVAssetExportSession creates a new timed media resource from the contents of an 
				existing AVAsset in the form described by a specified export preset.

	@discussion
				Prior to initializing an instance of AVAssetExportSession, you can invoke
				+allExportPresets to obtain the complete list of presets available. Use
				+exportPresetsCompatibleWithAsset: to obtain a list of presets that are compatible
				with a specific AVAsset.

				To configure an export, initialize an AVAssetExportSession with an AVAsset that contains
				the source media, an AVAssetExportPreset, the output file type, (a UTI string from 
				those defined in AVMediaFormat.h) and the output URL.

				After configuration is complete, invoke exportAsynchronouslyWithCompletionHandler: 
				to start the export process. This method returns immediately; the export is performed 
				asynchronously. Invoke the -progress method to check on the progress. Note that in 
				some cases, depending on the capabilities of the device, when multiple exports are 
				attempted at the same time some may be queued until others have been completed. When 
				this happens, the status of a queued export will indicate that it's "waiting".

				Whether the export fails, completes, or is cancelled, the completion handler you
				supply to -exportAsynchronouslyWithCompletionHandler: will be called. Upon
				completion, the status property indicates whether the export has completed
				successfully. If it has failed, the value of the error property supplies additional
				information about the reason for the failure.

*/

// -- Export Preset Names --


#if TARGET_OS_IPHONE

/* These export options can be used to produce movie files with video size appropriate to the device.
	The export will not scale the video up from a smaller size. The video will be compressed using
	H.264 and the audio will be compressed using AAC.  */

AVF_EXPORT NSString *const AVAssetExportPresetLowQuality        NS_AVAILABLE_IOS(4_0);
AVF_EXPORT NSString *const AVAssetExportPresetMediumQuality     NS_AVAILABLE_IOS(4_0);
AVF_EXPORT NSString *const AVAssetExportPresetHighestQuality    NS_AVAILABLE_IOS(4_0);

#endif // TARGET_OS_IPHONE

/* These export options can be used to produce movie files with the specified video size.
	The export will not scale the video up from a smaller size. The video will be compressed using
	H.264 and the audio will be compressed using AAC.  Some devices cannot support some sizes. */
AVF_EXPORT NSString *const AVAssetExportPreset640x480			NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT NSString *const AVAssetExportPreset960x540   		NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT NSString *const AVAssetExportPreset1280x720  		NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT NSString *const AVAssetExportPreset1920x1080			NS_AVAILABLE(10_7, 5_0);

/*  This export option will produce an audio-only .m4a file with appropriate iTunes gapless playback data */
AVF_EXPORT NSString *const AVAssetExportPresetAppleM4A			NS_AVAILABLE(10_7, 4_0);

/* This export option will cause the media of all tracks to be passed through to the output exactly as stored in the source asset, except for
   tracks for which passthrough is not possible, usually because of constraints of the container format as indicated by the specified outputFileType.
   This option is not included in the arrays returned by -allExportPresets and -exportPresetsCompatibleWithAsset. */
AVF_EXPORT NSString *const AVAssetExportPresetPassthrough		NS_AVAILABLE(10_7, 4_0);

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))

/* These export options are used to produce files that can be played on the specified Apple devices. 
	These presets are available for Desktop export only.
	The files should have .m4v extensions (or .m4a for exports with audio only sources). */
AVF_EXPORT NSString *const AVAssetExportPresetAppleM4VCellular	NS_AVAILABLE(10_7, NA);
AVF_EXPORT NSString *const AVAssetExportPresetAppleM4ViPod		NS_AVAILABLE(10_7, NA);
AVF_EXPORT NSString *const AVAssetExportPresetAppleM4V480pSD	NS_AVAILABLE(10_7, NA);
AVF_EXPORT NSString *const AVAssetExportPresetAppleM4VAppleTV	NS_AVAILABLE(10_7, NA);
AVF_EXPORT NSString *const AVAssetExportPresetAppleM4VWiFi		NS_AVAILABLE(10_7, NA);
AVF_EXPORT NSString *const AVAssetExportPresetAppleM4V720pHD	NS_AVAILABLE(10_7, NA);
AVF_EXPORT NSString *const AVAssetExportPresetAppleM4V1080pHD	NS_AVAILABLE(10_8, NA);

/* This export option will produce a QuickTime movie with Apple ProRes 422 video and LPCM audio. */
AVF_EXPORT NSString *const AVAssetExportPresetAppleProRes422LPCM	NS_AVAILABLE(10_7, NA);

#endif // (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))


@class AVAsset;
@class AVAssetExportSessionInternal;
@class AVAudioMix;
@class AVVideoComposition;
@class AVMetadataItemFilter;
@protocol AVVideoCompositing;

enum {
	AVAssetExportSessionStatusUnknown,
    AVAssetExportSessionStatusWaiting,
    AVAssetExportSessionStatusExporting,
    AVAssetExportSessionStatusCompleted,
    AVAssetExportSessionStatusFailed,
    AVAssetExportSessionStatusCancelled
};
typedef NSInteger AVAssetExportSessionStatus;

NS_CLASS_AVAILABLE(10_7, 4_0)
@interface AVAssetExportSession : NSObject
{
@private
	AVAssetExportSessionInternal  *_exportSession;
}

/*!
	@method						allExportPresets
	@abstract					Returns all available export preset names.
	@discussion					Returns an array of NSStrings with the names of all available presets. Note that not all presets are 
								compatible with all AVAssets.
	@result						An NSArray containing an NSString for each of the available preset names.
*/
+ (NSArray *)allExportPresets;

/*!
	@method						exportPresetsCompatibleWithAsset:
	@abstract					Returns only the identifiers compatible with the given AVAsset object.
	@discussion					Not all export presets are compatible with all AVAssets. For example an video only asset is not compatible with an audio only preset.
								This method returns only the identifiers for presets that will be compatible with the given asset. 
								A client should pass in an AVAsset that is ready to be exported.
								In order to ensure that the setup and running of an export operation will succeed using a given preset no significant changes 
								(such as adding or deleting tracks) should be made to the asset between retrieving compatible identifiers and performing the export operation.
								This method will access the tracks property of the AVAsset to build the returned NSArray.  To avoid blocking the calling thread, 
								the tracks property should be loaded using the AVAsynchronousKeyValueLoading protocol before calling this method.
	@param asset				An AVAsset object that is intended to be exported.
	@result						An NSArray containing NSString values for the identifiers of compatible export types.  
								The array is a complete list of the valid identifiers that can be used as arguments to 
								initWithAsset:presetName: with the specified asset.
*/
+ (NSArray *)exportPresetsCompatibleWithAsset:(AVAsset *)asset;

/*!
	@method						determineCompatibilityOfExportPreset:withAsset:outputFileType:completionHandler:
	@abstract					Performs an inspection on the compatibility of an export preset, AVAsset and output file type.  Calls the completion handler with YES if
								the arguments are compatible; NO otherwise.
	@discussion					Not all export presets are compatible with all AVAssets and file types.  This method can be used to query compatibility.
								In order to ensure that the setup and running of an export operation will succeed using a given preset no significant changes 
								(such as adding or deleting tracks) should be made to the asset between retrieving compatible identifiers and performing the export operation.
	@param presetName			An NSString specifying the name of the preset template for the export.
	@param asset				An AVAsset object that is intended to be exported.
	@param outputFileType		An NSString indicating a file type to check; or nil, to query whether there are any compatible types.
	@param completionHandler	A block called with the compatibility result.
 */
+ (void)determineCompatibilityOfExportPreset:(NSString *)presetName withAsset:(AVAsset *)asset outputFileType:(NSString *)outputFileType completionHandler:(void (^)(BOOL compatible))handler NS_AVAILABLE(10_9, 6_0);

/*!
	@method						exportSessionWithAsset:presetName:
	@abstract					Returns an instance of AVAssetExportSession for the specified source asset and preset.
	@param		asset			An AVAsset object that is intended to be exported.
	@param		presetName		An NSString specifying the name of the preset template for the export.
	@result						An instance of AVAssetExportSession.
*/
+ (AVAssetExportSession *)exportSessionWithAsset:(AVAsset *)asset presetName:(NSString *)presetName NS_AVAILABLE(10_7, 4_1);

/*!
	@method						initWithAsset:presetName:
	@abstract					Initialize an AVAssetExportSession with the specified preset and set the source to the contents of the asset.
	@param		asset			An AVAsset object that is intended to be exported.
	@param		presetName		An NSString specifying the name of the preset template for the export.
	@result						Returns the initialized AVAssetExportSession.
*/
- (id)initWithAsset:(AVAsset *)asset presetName:(NSString *)presetName;


/* These properties are key-value observable unless documented otherwise */

/* Indicates the name of the preset with which the AVExportSession was initialized */
@property (nonatomic, readonly) NSString *presetName;

/* Indicates the instance of AVAsset with which the AVExportSession was initialized  */
@property (nonatomic, retain, readonly) AVAsset *asset NS_AVAILABLE(10_8, 5_0);

/* Indicates the types of files the target can write, according to the preset the target was initialized with.
   Does not perform an inspection of the AVAsset to determine whether its contents are compatible with the supported file types. If you need to make that determination before initiating the export, use - (void)determineCompatibleFileTypesWithCompletionHandler:(void (^)(NSArray *compatibleFileTypes))handler:. */
@property (nonatomic, readonly) NSArray *supportedFileTypes;

/* Indicates the type of file to be written by the session.
   The value of this property must be set before you invoke -exportAsynchronouslyWithCompletionHandler:; otherwise -exportAsynchronouslyWithCompletionHandler: will raise an NSInternalInconsistencyException.
   Setting the value of this property to a file type that's not among the session's supported file types will result in an NSInvalidArgumentException. See supportedFileTypes. */
@property (nonatomic, copy) NSString *outputFileType;

/* Indicates the URL of the export session's output. You may use UTTypeCopyPreferredTagWithClass(outputFileType, kUTTagClassFilenameExtension) to obtain an appropriate path extension for the outputFileType you have specified. For more information about UTTypeCopyPreferredTagWithClass and kUTTagClassFilenameExtension, on iOS see <MobileCoreServices/UTType.h> and on Mac OS X see <LaunchServices/UTType.h>.  */
@property (nonatomic, copy) NSURL *outputURL;

/* indicates the status of the export session */
@property (nonatomic, readonly) AVAssetExportSessionStatus status;

/* describes the error that occured if the export status is AVAssetExportSessionStatusFailed */
@property (nonatomic, readonly) NSError *error;

/* Specifies the progress of the export on a scale from 0 to 1.0.  A value of 0 means the export has not yet begun, A value of 1.0 means the export is complete. This property is not key-value observable. */
@property (nonatomic, readonly) float progress;

#if TARGET_OS_IPHONE

/* Provides an estimate of the maximum duration of exported media that is possible given the source asset, the export preset, and the current value of fileLengthLimit.  The export will not stop when it reaches this maximum duration; set the timeRange property to export only a certain time range.  */
@property (nonatomic, readonly) CMTime maxDuration;

#endif

/* Indicates the estimated byte size of exported file. Returns zero when export preset is AVAssetExportPresetPassthrough or AVAssetExportPresetAppleProRes422LPCM. This property will also return zero if a numeric value (ie. not invalid, indefinite, or infinite) for the timeRange property has not been set. */
@property (nonatomic, readonly) long long estimatedOutputFileLength NS_AVAILABLE(10_9, 5_0);

/* Specifies a time range to be exported from the source.  The default timeRange of an export session is kCMTimeZero..kCMTimePositiveInfinity, meaning that the full duration of the asset will be exported. */
@property (nonatomic) CMTimeRange timeRange;

/* Specifies an NSArray of AVMetadataItems that are to be written to the output file by the export session.
   If the value of this key is nil, any existing metadata in the exported asset will be translated as accurately as possible into
   the appropriate metadata keyspace for the output file and written to the output. */
@property (nonatomic, copy) NSArray *metadata; 

/* Specifies a filter object to be used during export to determine which metadata items should be transferred from the source asset.
   If the value of this key is nil, no filter will be applied.  This is the default.
   The filter will not be applied to metadata set with via the metadata property.  To apply the filter to metadata before it is set on the metadata property, see the methods in AVMetadataItem's AVMetadataItemArrayFiltering category. */
@property (nonatomic, retain) AVMetadataItemFilter *metadataItemFilter NS_AVAILABLE(10_9, 7_0);

#if TARGET_OS_IPHONE
/* Indicates the file length that the output of the session should not exceed.  Depending on the content of the source asset, it is possible for the output to slightly exceed the file length limit.  The length of the output file should be tested if you require that a strict limit be observed before making use of the output.  See also maxDuration and timeRange. */
@property (nonatomic) long long fileLengthLimit; 
#endif

/* Indicates the processing algorithm used to manage audio pitch for scaled audio edits.
   Constants for various time pitch algorithms, e.g. AVAudioTimePitchAlgorithmSpectral, are defined in AVAudioProcessingSettings.h. An NSInvalidArgumentException will be raised if this property is set to a value other than the constants defined in that file.
   The default value is AVAudioTimePitchAlgorithmSpectral. */
@property (nonatomic, copy) NSString *audioTimePitchAlgorithm NS_AVAILABLE(10_9, 7_0);

/* Indicates whether non-default audio mixing is enabled for export and supplies the parameters for audio mixing.  Ignored when export preset is AVAssetExportPresetPassthrough. */
@property (nonatomic, copy) AVAudioMix *audioMix;

/* Indicates whether video composition is enabled for export and supplies the instructions for video composition.  Ignored when export preset is AVAssetExportPresetPassthrough. */
@property (nonatomic, copy) AVVideoComposition *videoComposition;

/* Indicates the custom video compositor instance used, if any */
@property (nonatomic, readonly) id<AVVideoCompositing>customVideoCompositor NS_AVAILABLE(10_9, 7_0);

/* indicates the movie should be optimized for network use */
@property (nonatomic) BOOL shouldOptimizeForNetworkUse;

/*!
	@method						determineCompatibleFileTypesWithCompletionHandler:
	@abstract					Performs an inspection on the AVAsset and Preset the object was initialized with to determine a list of file types the ExportSession can write.
	@param						handler
								Called when the inspection completes with an array of file types the ExportSession can write.  Note that this may have a count of zero.
	@discussion					This method is different than the supportedFileTypes property in that it performs an inspection of the AVAsset in order to determine its
								compatibility with each of the session's supported file types.
*/
- (void)determineCompatibleFileTypesWithCompletionHandler:(void (^)(NSArray *compatibleFileTypes))handler NS_AVAILABLE(10_9, 6_0);

/*!
	@method						exportAsynchronouslyWithCompletionHandler:
	@abstract					Starts the asynchronous execution of an export session.
	@param						handler
								If internal preparation for export fails, the handler will be invoked synchronously.
								The handler may also be called asynchronously after -exportAsynchronouslyWithCompletionHandler: returns,
								in the following cases: 
								1) if a failure occurs during the export, including failures of loading, re-encoding, or writing media data to the output,
								2) if -cancelExport is invoked, 
								3) if export session succeeds, having completely written its output to the outputURL. 
								In each case, AVAssetExportSession.status will signal the terminal state of the asset reader, and if a failure occurs, the NSError 
								that describes the failure can be obtained from the error property.
	@discussion					Initiates an asynchronous export operation and returns immediately.
*/
- (void)exportAsynchronouslyWithCompletionHandler:(void (^)(void))handler;

/*!
	@method						cancelExport
	@abstract					Cancels the execution of an export session.
	@discussion					Cancel can be invoked when the export is running.
*/
- (void)cancelExport;

@end
