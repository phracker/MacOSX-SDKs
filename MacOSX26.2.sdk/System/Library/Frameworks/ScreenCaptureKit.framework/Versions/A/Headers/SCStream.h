//
// SCStream.h
// ScreenCaptureKit
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>
#import <ScreenCaptureKit/SCShareableContent.h>
#import <CoreMedia/CMSampleBuffer.h>
#import <CoreMedia/CMSync.h>
#import <ScreenCaptureKit/SCRecordingOutput.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @typedef SCStreamOutputType
 @constant SCStreamOutputTypeScreen screen sample output type.
 @discussion
    SCStreamOutputTypeScreen is a screen capture sample buffer. This sample buffer that is wrapping a CMSampleBuffer that is backed by an IOSurface. The width and height of the sample buffer is what is defined in the SCStreamConfiguration for width and height. The sample buffer will be called back on the provided queue when adding a SCStreamOutput. The pixel format of the sample buffer will be what is defined in the SCStreamConfiguration. In the case of multiple window capture, the width and height will be that of the display passed in for the filter. The background color of multiwindow sample buffers will be default black and can be set through the SCStreamConfiguration.
 @constant SCStreamOutputTypeAudio audio sample output type.
 @constant SCStreamOutputTypeMicrophone microphone audio sample output type.
 @discussion
 SCStreamOutputTypeAudio is an audio capture sample buffer. This sample buffer that is wrapping an audio buffer list. The format of the audio buffer is based on sampleRate and channelCount set in SCStreamConfiguration.
 SCStreamOutputTypeMicrophone is a microphone audio capture sample buffer. This sample buffer that is wrapping an audio buffer list. The format of the audio buffer is based on the selected microphone capture device's native format.
*/
typedef NS_ENUM(NSInteger, SCStreamOutputType) {
    SCStreamOutputTypeScreen,
    SCStreamOutputTypeAudio API_AVAILABLE(macos(13.0), macCatalyst(18.2)),
    SCStreamOutputTypeMicrophone API_AVAILABLE(macos(15.0), macCatalyst(18.2))
} API_AVAILABLE(macos(12.3), macCatalyst(18.2));

/*!
 @typedef SCFrameStatus
 @abstract SCFrameStatus denotes the status of frame sample buffer.
 @constant SCFrameStatusComplete new frame was generated.
 @constant SCFrameStatusIdle new frame was not generated because the display did not change.
 @constant SCFrameStatusBlank new frame was not generated because the display has gone blank.
 @constant SCFrameStatusSuspended new frame was not generated because updates haves been suspended
 @constant SCFrameStatusStarted new frame that is indicated as the first frame sent after the stream has started.
 @constant SCFrameStatusStopped the stream was stopped.
*/
typedef NS_ENUM(NSInteger, SCFrameStatus) {
    SCFrameStatusComplete,
    SCFrameStatusIdle,
    SCFrameStatusBlank,
    SCFrameStatusSuspended,
    SCFrameStatusStarted,
    SCFrameStatusStopped
} API_AVAILABLE(macos(12.3), macCatalyst(18.2));

/*!
 @typedef SCPresenterOverlayAlertSetting
 @abstract SCPresenterOverlayAlertSetting denotes the setting that can be set to determine when to show the presenter overlay alert for any stream
 @constant SCPresenterOverlayAlertSettingSystem allow the system to determine when to show the presenter overlay privacy alert.
 @constant SCPresenterOverlayAlertSettingNever never show the presenter overlay privacy alert.
 @constant SCPresenterOverlayAlertAlways always show the presenter overlay privacy alert.
*/

typedef NS_ENUM(NSInteger, SCPresenterOverlayAlertSetting) {
    SCPresenterOverlayAlertSettingSystem,
    SCPresenterOverlayAlertSettingNever,
    SCPresenterOverlayAlertSettingAlways
} API_AVAILABLE(macos(14.0), macCatalyst(18.2));

/*!
 @typedef SCStreamType
 @abstract SCStreamTypeWindow window stream
 @constant SCStreamTypeDisplay display stream
*/
typedef NS_ENUM(NSInteger, SCStreamType) {
    SCStreamTypeWindow,
    SCStreamTypeDisplay
} API_DEPRECATED("Use SCShareableContentStyle instead", macos(14.0, 15.0));

typedef NS_ENUM(NSInteger, SCCaptureResolutionType) {
    SCCaptureResolutionAutomatic,
    SCCaptureResolutionBest,
    SCCaptureResolutionNominal
} API_AVAILABLE(macos(12.3), macCatalyst(18.2));

/*!
 @typedef SCCaptureDynamicRange
 @abstract SCCaptureDynamicRange client can specify whether the captured screen output will be SDR or HDR. When SCCaptureDynamicRangeHDR is set, the output screen capture buffer pixel format and color space will be updated in order to support HDR.
 @constant SCCaptureDynamicRangeSDR by default, screen capture output will be SDR.
 @constant SCCaptureDynamicRangeHDRLocalDisplay by default, screen capture output will be HDR, optimized for rendering on the local captured display
 @constant SCCaptureDynamicRangeHDRCanonicalDisplay by default, screen capture output will be HDR, optimized for rendering on any HDR display
*/
typedef NS_ENUM(NSInteger, SCCaptureDynamicRange) {
    SCCaptureDynamicRangeSDR,
    SCCaptureDynamicRangeHDRLocalDisplay,
    SCCaptureDynamicRangeHDRCanonicalDisplay
} API_AVAILABLE(macos(15.0), macCatalyst(18.2));

/*!
 @abstract SCContentFilter
 @discussion SCContentFilter is a object that determines the exact content to be captured in the SCStream. It can be filtered through displays, windows, excluded windows or applications.
*/
API_AVAILABLE(macos(12.3), macCatalyst(18.2))
@interface SCContentFilter : NSObject
/*!
  @abstract streamType type of stream
*/
@property(nonatomic, readonly) SCStreamType streamType API_DEPRECATED("Use style instead", macos(14.0, 14.2));

/*!
 @abstract style of stream
 */
@property (nonatomic, readonly) SCShareableContentStyle style API_AVAILABLE(macos(14.0));
/*!
 @abstract Pixel to points scaling factor
 */
@property (nonatomic, readonly) float pointPixelScale API_AVAILABLE(macos(14.0));

/*!
 @abstract Size and location of content in points
 */
@property (nonatomic, readonly) CGRect contentRect API_AVAILABLE(macos(14.0));

/*!
 @abstract To include menu bar as part of the capture. This property has no effect for the desktop independent window filter. For content filters created with initWithDisplay:excluding, the default value is YES. Display excluding content filters contains the desktop and dock. For content filters created with initWithDisplay:including, the default value is NO. Display including content filters do not contain the desktop and dock
 */
@property(nonatomic, assign) BOOL includeMenuBar API_AVAILABLE(macos(14.2));

/*!
 @abstract SCDisplays that are included in the content filter
 */
@property(nonnull, nonatomic, readonly) NSArray <SCDisplay *> *includedDisplays API_AVAILABLE(macos(15.2));

/*!
 @abstract Applications that are included in the content filter
 */
@property (nonnull, nonatomic, readonly) NSArray <SCRunningApplication *> *includedApplications API_AVAILABLE(macos(15.2));

/*!
 @abstract Windows that are included in the content filter
 */
@property (nonnull, nonatomic, readonly) NSArray <SCWindow *> *includedWindows API_AVAILABLE(macos(15.2));

/*!
 @abstract initWithDesktopIndependentWindow:
 @param window the independent SCWindow you wish to capture
 @discussion this method will create a SCContentFilter that captures just the independent window passed in.
*/
- (instancetype)initWithDesktopIndependentWindow:(SCWindow *)window;

/*!
 @abstract initWithDisplay:excludingWindows
 @param display the SCDisplay you wish to capture
 @param excluded the SCWindow(s) you wish to exclude from the passed in SCDisplay
 @discussion This method will create a SCContentFilter that captures the SCDisplay, excluding the passed in excluded SCWindow(s). The desktop background and dock will be included with this content filter.
*/
- (instancetype)initWithDisplay:(SCDisplay *)display excludingWindows:(NSArray<SCWindow *>*)excluded;

/*!
 @abstract initWithDisplay:includingWindows
 @param display the SCDisplay you wish to capture
 @param includedWindows a set of SCWindows you wish to capture
 @discussion This method will create a SCContentFilter that captures a group of SCWindows. The desktop background and dock will be excluded with this content filter.
*/
- (instancetype)initWithDisplay:(SCDisplay *)display includingWindows:(NSArray<SCWindow *>*)includedWindows;

/*!
 @abstract initWithDisplay:includingApplications:exceptingWindows
 @param display the SCDisplay you wish to capture
 @param applications the NSSet of SCRunningApplications that you wish to capture
 @param exceptingWindows the NSSet of SCWindows that you wish to be an exception to the filter
 @discussion This method creates a SCContentFilter that captures all windows owned by the passed in SCRunningApplications. Any windows that are an exception to the filter will not be shown if their owning application is in the provided list and will be shown otherwise. The desktop background and dock will be excluded with this content filter.
*/
- (instancetype)initWithDisplay:(SCDisplay *)display includingApplications:(NSArray<SCRunningApplication *>*)applications exceptingWindows:(NSArray<SCWindow *>*)exceptingWindows;

/*!
 @abstract initWithDisplay:excludingApplications:exceptingWindows
 @param display the SCDisplay you wish to capture
 @param applications the NSSet of SCRunningApplications that you do not wish to capture
 @param exceptingWindows the NSSet of SCWindows that you wish to be an exception to the filter
 @discussion This method creates a SCContentFilter that captures all windows not owned by the passed in SCRunningApplications. Any windows that are an exception to the filter will be shown if their owning application is in the provided list and will not be shown otherwise. The desktop background and dock will be included with this content filter.
*/
- (instancetype)initWithDisplay:(SCDisplay *)display excludingApplications:(NSArray<SCRunningApplication *>*)applications exceptingWindows:(NSArray<SCWindow *>*)exceptingWindows;

@end

/*!
 @abstract SCStreamConfiguration
 @discussion SCStreamConfiguration is an object that encapsulates the SCStream properties such as output width, height, pixelformat and others.
*/
API_AVAILABLE(macos(12.3), macCatalyst(18.2))
@interface SCStreamConfiguration : NSObject

/*!
 @typedef SCStreamConfigurationPreset
 @abstract Client can use SCStreamConfigurationPreset to create SCStreamConfiguration with suggested values of properties for various use cases
 @constant SCStreamConfigurationPresetCaptureHDRLocalDisplay using this preset will help client set suggested values for captureDynamicRange, pixelFormat, ColorSpace, colorMatrix in order to get HDR capture output with SCStream, optimized for rendering on the local captured display.
 @constant SCStreamConfigurationPresetCaptureHDRCanonicalDisplay using this preset will help client set suggested values for captureDynamicRange, pixelFormat, ColorSpace, colorMatrix in order to get HDR capture output with SCStream, optimized for rendering on canonical HDR display
 @constant SCStreamConfigurationPresetCaptureHDRScreenshotLocalDisplay using this preset will help client set suggested values for captureDynamicRange, pixelFormat, ColorSpace in order to get HDR screenshot with SCScreenshotManager, optimized for rendering on the local captured display.
 @constant SCStreamConfigurationPresetCaptureHDRScreenshotCanonicalDisplay using this preset will help client set suggested values for captureDynamicRange, pixelFormat, ColorSpace in order to get HDR screenshot with SCScreenshotManager, optimized for rendering on canonical HDR display
 @constant SCStreamConfigurationPresetCaptureHDRRecordingPreservedSDRHDR10 using this preset will help client set suggested values for captureDynamicRange, pixelFormat, and colorSpace intended for a stream recording in HDR10, optimized for rendering on the canonical HDR display.  This preset will also add HDR10 metadata to the video recording that is designed to preserve the SDR range during video playback.

*/
typedef NS_ENUM(NSInteger, SCStreamConfigurationPreset) {
    SCStreamConfigurationPresetCaptureHDRStreamLocalDisplay,
    SCStreamConfigurationPresetCaptureHDRStreamCanonicalDisplay,
    SCStreamConfigurationPresetCaptureHDRScreenshotLocalDisplay,
    SCStreamConfigurationPresetCaptureHDRScreenshotCanonicalDisplay,
    SCStreamConfigurationPresetCaptureHDRRecordingPreservedSDRHDR10 API_AVAILABLE(macos(26.0), macCatalyst(26.0))
} NS_SWIFT_NAME(SCStreamConfiguration.Preset) API_AVAILABLE(macos(15.0), macCatalyst(18.2));

/*!
 @abstract SCStreamProperty for output width as measured in pixels. Default is set to 1920.
 */
@property(nonatomic, assign) size_t width;

/*!
 @abstract SCStreamProperty for output height as measured in pixels. Default is set to 1080.
 */
@property(nonatomic, assign) size_t height;

/*!
 @abstract SCStreamProperty that specifies the desired minimum time in seconds between frame updates, allowing you to throttle the rate at which updates are received. The default value is 1/60, meaning that updates are coming in at or up to 60fps. Set this to kCMTimeZero to capture at display's native refresh rate.
 */
@property(nonatomic, assign) CMTime minimumFrameInterval;

/*!
 @abstract SCStreamProperty for output pixel format. Supported pixel formats are:
 'BGRA': Packed Little Endian ARGB8888
 'l10r': Packed Little Endian ARGB2101010
 '420v': 2-plane "video" range YCbCr 4:2:0
 '420f': 2-plane "full" range YCbCr 4:2:0
 'xf44': 2 plane "full" range YCbCr10 4:4:4
 'RGhA': 64 bit RGBA IEEE half-precision float, 16-bit little-endian
 See https://developer.apple.com/documentation/coregraphics/1455170-cgdisplaystreamcreate
 */
@property(nonatomic, assign) OSType pixelFormat;

/*!
 @abstract SCStreamProperty for output to be always scaled to fit into the provided width and height. For use for independent window capture. When true, the output scales up and down. When false, the output only scales down.
 */
@property(nonatomic, assign) BOOL scalesToFit;

/*!
 @abstract SCStreamProperty that specifies whether the  stream preserves the aspect ratio of the source pixel data. By default the aspect ratio is preserved.
 */
@property(nonatomic, assign) BOOL preservesAspectRatio API_AVAILABLE(macos(14.0));

/*!
 @abstract SCStreamProperty the name of the stream 
 */
@property(nonatomic, strong, nullable) NSString *streamName API_AVAILABLE(macos(14.0));

/*!
 @abstract SCStreamProperty that specifies whether the cursor should appear in the stream.  By default the cursor is visible.
 */
@property(nonatomic, assign) BOOL showsCursor;

/*!
 @abstract SCStreamProperty that specifies whether to draw a circle around the cursor click, default is NO. This property will not be affected by showsCursor. This property currently applies when pixelFormat is set to BGRA.
 */
@property (nonatomic, assign) BOOL showMouseClicks API_AVAILABLE(macos(15.0));

/*!
 @abstract SCStreamProperty for background color. By default the background color is clear.
 */
@property(nonatomic, assign) CGColorRef backgroundColor;

/*!
 @abstract SCStreamProperty that specifies that the stream only samples a subset of the frame input. For display streams, if not set, then the entire display is streamed. For independent window streams, if not set, then the entire window is streamed. The rectangle is specified in points in the display’s logical coordinate system.
 */
@property(nonatomic, assign) CGRect sourceRect;

/*!
 @abstract SCStreamProperty that specifies that the stream outputs the frame data into a subset of the output IOSurface object. For both display streams and independent window streams, if not set, then the entire output surface is used. The rectangle is specified in pixels in the display's coordinate system.
 */
@property(nonatomic, assign) CGRect destinationRect;

/*!
 @abstract SCStreamProperty that specifies the number of frames to keep in the queue.  If not set the default value is 8 frames.  Specifying more frames uses more memory, but may allow you to process frame data without stalling the display stream and should not exceed 8 frames.
 */
@property(nonatomic, assign) NSInteger queueDepth;

/*!
 @abstract SCStreamProperty that specifies the YCbCr matrix applied to the output surface.  The value must be one of the strings specified in https://developer.apple.com/documentation/coregraphics/quartz_display_services/display_stream_ycbcr_to_rgb_conversion_matrix_options. Should only be used if your pixel format is 420v or 420f.
 */
@property(nonatomic, assign) CFStringRef colorMatrix;

/*!
 @abstract SCStreamProperty that specifies the color space of the output buffer.  If not set the output buffer uses the same color space as the display. The value must be one of the strings specified in
 https://developer.apple.com/documentation/coregraphics/cgcolorspace/color_space_names.
 */
@property(nonatomic, assign) CFStringRef colorSpaceName;

/*!
 @abstract SCStreamProperty that specifies whether the audio will be captured.  By default audio is not captured.
 */
@property(nonatomic, assign) BOOL capturesAudio API_AVAILABLE(macos(13.0));

/*!
 @abstract SCStreamProperty to specify the sample rate for audio. Default is set to 48000.
 */
@property(nonatomic, assign) NSInteger sampleRate API_AVAILABLE(macos(13.0));

/*!
 @abstract SCStreamProperty to specify channel count. Default is set to two.
 */
@property(nonatomic, assign) NSInteger channelCount API_AVAILABLE(macos(13.0));

/*!
 @abstract SCAudioProperty whether to exclude audio from current process. Default is set to NO.
 */
@property(nonatomic, assign) BOOL excludesCurrentProcessAudio API_AVAILABLE(macos(13.0));

/*!
 @abstract SCStreamProperty to ignore framing on windows in the display sharing case (will ignore shadows).
 */
@property(nonatomic, assign) BOOL ignoreShadowsDisplay API_AVAILABLE(macos(14.0));

/*!
 @abstract SCStreamProperty to ignore framing on windows in the single window sharing case (will ignore shadows).
 */
@property(nonatomic, assign) BOOL ignoreShadowsSingleWindow API_AVAILABLE(macos(14.0));

/*!
 @abstract captureResolution Choose between automatic, best, and nominal.
 */
@property(nonatomic, assign) SCCaptureResolutionType captureResolution API_AVAILABLE(macos(14.0));

/*!
 @abstract SCStreamProperty to capture only the shadows of windows.
 */
@property(nonatomic, assign) BOOL capturesShadowsOnly API_AVAILABLE(macos(14.0));

/*!
 @abstract SCStreamProperty to ensure partially transparent areas on windows are backed by a solid white color so that the resulting image is fully opaque.
 */
@property(nonatomic, assign) BOOL shouldBeOpaque API_AVAILABLE(macos(14.0));

/*!
 @abstract SCStreamProperty to ignore framing on windows in the display sharing case (will ignore shadows).
 */
@property(nonatomic, assign) BOOL ignoreGlobalClipDisplay API_AVAILABLE(macos(14.0));

/*!
 @abstract SCStreamProperty to ignore global clipping when on single window share. When set to true, single window captures that are partially off the screen will not be clipped. (will ignore window placement in display context).
 */
@property(nonatomic, assign) BOOL ignoreGlobalClipSingleWindow API_AVAILABLE(macos(14.0));

/*!
 @abstract SCStreamProperty that informs the system if a privacy alert should be shown when using presenter overlay for a stream. Defaults to SCPresenterOverlayAlertSettingSystem;
 */
@property(nonatomic, assign) SCPresenterOverlayAlertSetting presenterOverlayPrivacyAlertSetting API_AVAILABLE(macos(14.0));

/*!
 @abstract SCStreamProperty to show the child windows in display bound windows and applications sharing.  Child windows are included by default.
 */
@property(nonatomic, assign) BOOL includeChildWindows API_AVAILABLE(macos(14.2));

/*!
 @abstract SCStreamProperty that specifies whether the microphone audio will be captured.  By default microphone is not captured.
 */
@property(nonatomic, assign) BOOL captureMicrophone API_AVAILABLE(macos(15.0));

/*!
 @abstract SCStreamProperty that specifies which microphone device to capture. This deviceID is the uniqueID from AVCaptureDevice for the microphone. System Default Microphone will be used if not specified by client. For Mac Catalyst apps, the System Default Microphone will be captured.
 */
@property(nonatomic, strong, nullable) NSString *microphoneCaptureDeviceID API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(macCatalyst);

/*!
 @abstract SCStreamProperty client will choose captureDynamicRange between SCCaptureDynamicRangeSDR, SCCaptureDynamicRangeHDRLocalDisplay,  SCCaptureDynamicRangeHDRCanonicalDisplay. By default, the stream is capturing with SCCaptureDynamicRangeSDR. HDR capture is only supported with Apple Silicon Mac, setting this property on Intel Mac will have no effect. HDR recording is not support yet, adding a recording output to a stream with SCCaptureDynamicRangeHDR set will fail.
 */
@property(nonatomic, assign) SCCaptureDynamicRange captureDynamicRange API_AVAILABLE(macos(15.0));

/*!
 @method streamConfigurationWithPreset:
 @abstract Returns an instance of SCStreamConfiguration corresponding to the given preset
 @param preset The enum identifier for the desired preset
 @discussion The SCStreamConfiguration of the returned object can be used as a guide for creating and configuring an SCStream. If all the suggested properties are respected in creating the SCStream, the resulting capture result will conform to the criteria implied by the preset.
 */
+ (instancetype)streamConfigurationWithPreset:(SCStreamConfigurationPreset)preset API_AVAILABLE(macos(15.0));

@end

/*!
 @abstract SCStream
 @discussion SCStream is the object that takes in an SCContentFilter and sets up a contentstream that gives the calling application back the screen captures based on the contentfilter and settings
*/
API_AVAILABLE(macos(12.3), macCatalyst(18.2))
@protocol SCStreamDelegate;

API_AVAILABLE(macos(12.3), macCatalyst(18.2))
typedef NSString * SCStreamFrameInfo NS_TYPED_ENUM;
/*!
 @key SCStreamFrameInfoStatus
 @abstract The key for the CFDictionary attached to the CMSampleBuffer that denotes the frames SCFrameStatus
 */
extern SCStreamFrameInfo const SCStreamFrameInfoStatus API_AVAILABLE(macos(12.3), macCatalyst(18.2));

/*!
 @key SCStreamFrameInfoDisplayTime
 @abstract The key for the CFDictionary attached to the CMSampleBuffer for the mach absolute time when the event occurred. For a frame event, this is when the frame was displayed by the window server.
 */
extern SCStreamFrameInfo const SCStreamFrameInfoDisplayTime API_AVAILABLE(macos(12.3), macCatalyst(18.2));

/*!
 @key SCStreamFrameInfoScaleFactor
 @abstract The key for the CFDictionary attached to the CMSampleBuffer for the display resolution associated with the frame. Display resolution is the pixel to point scaling factor. It should be in the range of [1, 4].
 */
extern SCStreamFrameInfo const SCStreamFrameInfoScaleFactor API_AVAILABLE(macos(12.3), macCatalyst(18.2));

/*!
 @key SCStreamFrameInfoContentScale
 @abstract The key for the CFDictionary attached to the CMSampleBuffer for the content scale associated with the frame. Content scale is the scaling factor from original content size to its size in surface.
 */
extern SCStreamFrameInfo const SCStreamFrameInfoContentScale API_AVAILABLE(macos(12.3), macCatalyst(18.2));

/*!
 @key SCStreamFrameInfoContentRect
 @abstract The key for the CFDictionary attached to the CMSampleBuffer for the content rect associated with the frame. Content rect is the size and location of content in points in surface.
 */
extern SCStreamFrameInfo const SCStreamFrameInfoContentRect API_AVAILABLE(macos(12.3), macCatalyst(18.2));

/*!
 @key SCStreamFrameInfoDirtyRects
 @abstract The key for the CFDictionary attached to the CMSampleBuffer for an array of rectangles that is the union of both rectangles that were redrawn and rectangles that were moved. This is an array of CGRect in NSValue. The CGRects elements are specified in pixels.
 */
extern SCStreamFrameInfo const SCStreamFrameInfoDirtyRects API_AVAILABLE(macos(12.3), macCatalyst(18.2));

/*!
 @key SCStreamFrameInfoScreenRect
 @abstract The key for the CFDictionary attached to the CMSampleBuffer for the onscreen location of the captured content
 */
extern SCStreamFrameInfo const SCStreamFrameInfoScreenRect API_AVAILABLE(macos(13.1), macCatalyst(18.2));

/*!
 @key SCStreamFrameInfoBoundingRect
 @abstract The key for the CFDictionary attached to the CMSampleBuffer for the bounding rect associated with the frame. Bounding rect is the size and location of smallest bounding box containing all captured windows in points and in surface coordinates.
 */
extern SCStreamFrameInfo const SCStreamFrameInfoBoundingRect API_AVAILABLE(macos(14.0), macCatalyst(18.2));

/*!
 @key SCStreamFrameInfoPresenterOverlayContentRect
 @abstract The key for the CFDictionary attached to the CMSampleBuffer for the content rect associated with the frame while in presenter overlay.  In presenter overlay small, this content rect is the size and location of smallest bounding box containing all captured windows plus small overlay window in points and in surface coordinates.
 In presenter overlay large, this content rect is the size and location of shared content in points and in surface coordinates.
 */
extern SCStreamFrameInfo const SCStreamFrameInfoPresenterOverlayContentRect API_AVAILABLE(macos(14.2), macCatalyst(18.2));

@protocol SCStreamOutput;
API_AVAILABLE(macos(12.3), macCatalyst(18.2))
@interface SCStream : NSObject

/*!
 @abstract Synchronization clock used for media capture.
 */
@property(nonatomic, readonly, nullable) CMClockRef synchronizationClock API_AVAILABLE(macos(13.0));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
/*!
 @abstract initWithFilter:configuration:delegate:
 @param contentFilter the requested content filter to be captured
 @param streamConfig the requested stream configuration to be applied to the SCStream
 @param delegate the SCStream delegate object
 @discussion this method create a SCStream object that has the particular output settings for the content stream
*/
- (instancetype)initWithFilter:(SCContentFilter *)contentFilter configuration:(SCStreamConfiguration *)streamConfig delegate:(id<SCStreamDelegate> _Nullable)delegate;

/*!
 @abstract addStreamOutput:type:sampleHandlerQueue:error:
 @param output an object that adheres to the SCStreamOutput protocol that will receive the frames and call its delegate frame call back on its sample handler queue
 @param type the SCStreamOutput type
 @param sampleHandlerQueue the return queue for the sample handler
 @param error the error pertaining to the add stream output
 @discussion An SCStreamOutput protocol object instance can only be added to a session using -addStreamOutput: Returns a BOOL denoting if the add was successful
*/
- (BOOL)addStreamOutput:(id<SCStreamOutput>)output type:(SCStreamOutputType)type sampleHandlerQueue:(dispatch_queue_t _Nullable)sampleHandlerQueue error:(NSError **)error NS_SWIFT_ASYNC_NAME (addStreamOutput(_:type:sampleHandlerQueue:)) NS_SWIFT_NAME (addStreamOutput(_:type:sampleHandlerQueue:));

/*!
 @abstract removeStreamOutput:type:error:
 @param output an object that adheres to the SCStreamOutput protocol that will received the frames and call its delegate frame call back on its sample handler queue
 @param type the SCStreamOutput type
 @param error the error pertaining to the removing stream output
 @discussion An SCStreamOutput protocol object instance can only be removed to a session using -addStreamOutput: Returns a BOOL denoting if the remove was successful
*/

- (BOOL)removeStreamOutput:(id<SCStreamOutput>)output type:(SCStreamOutputType)type error:(NSError **)error NS_SWIFT_ASYNC_NAME(removeStreamOutput(_:type:)) NS_SWIFT_NAME(removeStreamOutput(_:type:));

/*!
 @abstract updateContentFilter:completionHandler:
 @param contentFilter the requested content filter to be updated
 @param completionHandler the handler to be called when the function completes
 @discussion this method will update the content filter for a content stream. A completion handler will be called when the update is complete with an error denoting if the update has failed.
*/
- (void)updateContentFilter:(SCContentFilter *)contentFilter completionHandler:(nullable void (^)(NSError *_Nullable error))completionHandler NS_SWIFT_ASYNC_NAME(updateContentFilter(_:)) NS_SWIFT_NAME(updateContentFilter(_:completionHandler:));

/*!
 @abstract updateConfiguration:completionHandler:
 @param streamConfig the requested content filter to be updated
 @param completionHandler the handler to be called when the function completes
 @discussion this method will update the stream configuration for a content stream. A completion handler will be called when the update is complete with an error denoting if the update has failed.
*/
- (void)updateConfiguration:(SCStreamConfiguration *)streamConfig completionHandler:(nullable void (^)(NSError *_Nullable error))completionHandler NS_SWIFT_ASYNC_NAME(updateConfiguration(_:)) NS_SWIFT_NAME(updateConfiguration(_:completionHandler:));

/*!
 @abstract startCaptureWithCompletionHandler:
 @param completionHandler the handler to be called when the function completes
 @discussion this method starts the content stream. The handler will be called when the content stream start has completed with an error denoting if the start has failed.
*/
- (void)startCaptureWithCompletionHandler:(nullable void (^)(NSError *_Nullable error))completionHandler;

/*!
 @abstract stopCaptureWithCompletionHandler:
 @param completionHandler the handler to be called when the function completes
 @discussion this method stops the content stream. The handler will be called when the content stream stop has completed with an error denoting if the stop has failed.
*/
- (void)stopCaptureWithCompletionHandler:(nullable void (^)(NSError *_Nullable error))completionHandler;

/*!
 @method addRecordingOutput
 @abstract Add a SCRecordingOutput to the SCStream. Starts Recording if stream is already capturing, otherwise recording will be started after capture starts. Recording will be written into a file url specified in SCRecordingOutput. Media(Screen/Audio/Microphone) to be recorded will be based on the SCStream configuration.
 @param recordingOutput an SCRecordingOutput that including configuration of recording, and delegate for recording event.
 @param error the error pertaining to the add recording output
 @discussion Returns a BOOL denoting if the add was successful. Currently only support one recordingOutput on a stream. To guarantee the first sample captured in the stream to be written into the recording file, client need to add recordingOutput before startCapture. Delegate for recordingDidStart will be notified in SCRecordingOutput or recordingDidFinishWithError will be notified with an error associated if recording failed to start.
*/
- (BOOL)addRecordingOutput:(SCRecordingOutput *)recordingOutput error:(NSError **)error NS_SWIFT_NAME(addRecordingOutput(_:)) API_AVAILABLE(macos(15.0));

/*!
 @method removeRecordingOutput
 @abstract Remove SCRecordingOutput from the SCStream. Stops Recording if the stream is currently recording.
 @param recordingOutput an SCRecordingOutput that including configuration of recording, and delegate for recording event.
 @param error the error pertaining to the remove recording output
 @discussion Returns a BOOL denoting if the remove was successful. Delegate for recordingDidFinishWithError will be notified in SCRecordingOutput, associate with an error code if recording failed to finish written to the file. If stopCapture is called without removing recordingOutput, recording will be stopped and finish writting into the file. In case client update the stream configuration during recording, recording will be stopped as well.
*/
- (BOOL)removeRecordingOutput:(SCRecordingOutput *)recordingOutput error:(NSError **)error NS_SWIFT_NAME(removeRecordingOutput(_:)) API_AVAILABLE(macos(15.0));

@end

API_AVAILABLE(macos(12.3), macCatalyst(18.2))
@protocol SCStreamOutput <NSObject>
@optional
/*!
 @abstract stream:didOutputSampleBuffer:ofType:
 @param sampleBuffer the sample buffer
 @param type the sample buffer type
 @discussion protocol method for passing back screen sample buffers
*/
- (void)stream:(SCStream *)stream didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer ofType:(SCStreamOutputType)type;
@end
/*!
 @abstract SCStreamDelegate
 @discussion SCStreamDelegate is the object that adheres to the SCStream delegate call backs
*/
API_AVAILABLE(macos(12.3), macCatalyst(18.2))
@protocol SCStreamDelegate <NSObject>
@optional
/*!
 @abstract stream:didStopStreamWithError:
 @param stream the SCStream object
 @param error the error denoted by the stopping of the stream
 @discussion notifies the delegate that the stream has stopped and the error associated with it
*/
- (void)stream:(SCStream *)stream didStopWithError:(NSError *)error;

/*!
 @abstract outputVideoEffectDidStartForStream:
 @param stream the SCStream object
 @discussion notifies the delegate that the stream's overlay video effect has started.
*/
- (void)outputVideoEffectDidStartForStream:(SCStream *)stream API_AVAILABLE(macos(14.0));

/*!
 @abstract stream:outputVideoEffectDidStart:
 @param stream the SCStream object
 @discussion notifies the delegate that the stream's overlay video  effect has stopped.
*/
- (void)outputVideoEffectDidStopForStream:(SCStream *)stream API_AVAILABLE(macos(14.0));

/*!
 @abstract streamDidBecomeActive:
 @param stream the SCStream object
 @discussion notifies the delegate the first time any window that was being shared in the stream is re-opened after all the windows being shared are closed.  When all the windows being shared are closed, the client will receive streamDidBecomeInactive:.
 */
- (void)streamDidBecomeActive:(SCStream *)stream API_AVAILABLE(macos(15.2));

/*!
 @abstract streamDidBecomeInactive:
 @param stream the SCStream object
 @discussion notifies the delegate that all the windows that are currently being shared are exited. This callback occurs for all content filter types.
*/
- (void)streamDidBecomeInactive:(SCStream *)stream API_AVAILABLE(macos(15.2));

@end


NS_ASSUME_NONNULL_END
