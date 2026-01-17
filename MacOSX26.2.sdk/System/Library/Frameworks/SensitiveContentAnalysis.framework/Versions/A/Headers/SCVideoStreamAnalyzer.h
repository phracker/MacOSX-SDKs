//
//  SCVideoStreamAnalyzer.h
//  UserSafety
//
//  Created by Rob Cadwallader on 9/26/24.
//

#import <CoreVideo/CVPixelBuffer.h>
#import <VideoToolbox/VTDecompressionSession.h>
#import <SensitiveContentAnalysis/SCSensitivityAnalysis.h>

@class AVCaptureDeviceInput;

/// Options for the different types of analyzed video streams.
///
/// Pass this enum into the ``SCVideoStreamAnalyzer/init(participantUUID:streamDirection:)`` initializer when creating an ``SCVideoStreamAnalyzer`` to analyze video streams.
typedef NS_ENUM(NSInteger, SCVideoStreamAnalyzerStreamDirection) {
    /// An option that refers to a video stream sent to another device.
    ///
    /// This option refers to the stream that originates from the device's camera.
    SCVideoStreamAnalyzerStreamDirectionOutgoing = 1,
    
    /// An option that indicates a video stream from another device.
    ///
    /// This option refers to a video stream that the device receives over the network from another device's camera.
    SCVideoStreamAnalyzerStreamDirectionIncoming = 2,

} NS_SWIFT_NAME(SCVideoStreamAnalyzer.StreamDirection) API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macos, macCatalyst, tvos, visionos);

/// A handler your app provides to receive video-stream analysis results.
///
/// Your app implements this handler and the framework calls it when the analyzer's video stream detects sensitive content, or an error providing corresponding analysis, or error as input parameters.
///
/// This handler receives an instance of ``SCSensitivityAnalysis``, and an <doc://com.apple.documentation/documentation/swift/error>, for example:
///
/// ```swift
/// analyzer.analysisChangedHandler = { analysis, error in
///     self.analysis = analysis
///     if analysis.shouldInterruptVideo {
///         // ...
///     }
///     if analysis.shouldIndicateSensitivity {
///         // ...
///     }
///     if analysis.shouldMuteAudio {
///         // ...
///     }
/// }
/// ```
API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macos, macCatalyst, tvos, visionos)
NS_SWIFT_UI_ACTOR
typedef void (^SCVideoStreamAnalysisChangeHandler)(SCSensitivityAnalysis * _Nullable,NSError * _Nullable) NS_SWIFT_UNAVAILABLE("Use AnalysisChanges instead");

NS_HEADER_AUDIT_BEGIN(nullability)

/// Monitors a stream of video by analyzing frames for sensitive content.
///
/// Use this class to detect senstive content in a video stream, such as on a conference call that your app implements. The class detects senstive content in the video stream from either the device's camera or the remote device(s) signed into the call, depending on how you configure the analyzer.
///
/// Create an instance of this class for each video stream in the call.
///
/// To begin analyzing the stream, pass it to either ``beginAnalysis(of:)-(AVCaptureDeviceInput)`` (<doc://com.apple.documentation/documentation/avfoundation/avcapturedeviceinput>) or ``beginAnalysis(of:)-(VTDecompressionSession)`` (<doc://com.apple.documentation/documentation/videotoolbox/vtdecompressionsession>), depending on your video playback implementation.
///
/// - Important: This class works only when the Communication Safety parental control in Screen Time is enabled, or when Sensitive Content Warnings is on in Settings. The initializers of this class throw an error if both settings are off.
///
/// ### React to sensitive content
///
/// When the framework detects sensitive content in the stream, it calls ``analysisChangedHandler`` immediately with an ``SCSensitivityAnalysis`` object that includes information about the detection.
///
/// You implement the ``analysisChangedHandler`` callback to inspect the detection results, which includes confirmation that content is sensitve as well as guidance on next steps your app can take. The framework offers your app suggestions in the handler, which include:
///
/// - Alerting the person to the presence of sensitive content (``SCSensitivityAnalysis/shouldIndicateSensitivity``)
/// - Interrupting video playback (``SCSensitivityAnalysis/shouldInterruptVideo``)
/// - Muting audio (``SCSensitivityAnalysis/shouldMuteAudio``)
///
/// To stop analyzing the stream, call ``endAnalysis()``. If your app implements a custom stream decoder, you can analyze individual frames by passing pixel buffers to ``analyze(_:)``.
///
/// In the event of an error during analysis, the handler receives an error object that details what went wrong. For more information, see: ``SCVideoStreamAnalysisChangeHandler``.
///
/// ### Add the app entitlement
///
/// To use this class, the system requires the <doc://com.apple.documentation/documentation/bundleresources/entitlements/com.apple.developer.sensitivecontentanalysis.client> entitlement in your app's code signature. Calls to the framework fail to return positive results without it. You can can add this entitlement to your app by enabling the Sensitive Content Analysis capability in Xcode; see <doc://com.apple.documentation/documentation/xcode/adding-capabilities-to-your-app>.
///
/// For more information, see <doc:detecting-nudity-in-media-and-providing-intervention-options>.
API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macos, macCatalyst, tvos, visionos)
@interface SCVideoStreamAnalyzer : NSObject

/// The results of the first detected sensitive video frame.
///
/// The analysis also includes suggestions for the app based on the nature of the sensitive content, specifically: ``SCSensitivityAnalysis/shouldInterruptVideo``, ``SCSensitivityAnalysis/shouldIndicateSensitivity`` and ``SCSensitivityAnalysis/shouldMuteAudio``.
@property (nullable, readonly) SCSensitivityAnalysis *analysis;

/// A handler that your app provides to react to sensitive content detection.
///
/// The system invokes all analyzer handlers on the same conference call with the updated analysis or error.
@property (nullable, copy, readwrite) SCVideoStreamAnalysisChangeHandler analysisChangedHandler NS_REFINED_FOR_SWIFT;

/// Creates a video stream analyzer for the given call participant and stream option.
///
/// - parameter participantUUID: A unique identifier that you provide to distinguish among multiple individuals on a conference call. Set this argument to the same value per person on the call, if your app supports multiple streams per person.
/// - parameter streamDirection: An option that indicates whether the stream comes from the device's camera or from a remote individual signed in to the call.
/// - parameter error: An error that occurs while intializing a video stream analyzer.
///
/// - Important: This class works only when the Communication Safety parental control in Screen Time is enabled, or when Sensitive Content Warnings is on in Settings. This method throws an error if both settings are off, or if the device doesn't support analysis for the specified stream direction.
- (nullable instancetype)initWithParticipantUUID:(NSString *)participantUUID
                                 streamDirection:(SCVideoStreamAnalyzerStreamDirection)streamDirection
                                           error:(NSError**)error;

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)new NS_UNAVAILABLE;

/// Analyzes individual video-stream frames for sensitive content.
///
/// This method analyzes a specific video frame and updates ``analysis`` according to the results. If your app implements a custom stream decoder, you can call this method for each video frame.
- (void)analyzePixelBuffer:(CVPixelBufferRef)pixelBuffer;

@end

API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macos, macCatalyst, tvos, visionos)
@interface SCVideoStreamAnalyzer (SessionManagement)

/// Analyzes video frames for the given decompression session.
///
/// - parameter decompressionSession: An object that provides video frames for your app to analyze for sensitive content.
/// - parameter error: An error object that describes an issue that occurs while providing the video decompression session.
/// - returns: `YES` if the method succeeds; otherwise, `NO`.
///
/// If the framework detects sensitive content in the video stream, the <doc://com.apple.documentation/documentation/videotoolbox/vtdecompressionsession> produces blank frames to effectively censor the video stream on the person's behalf. When your app is ready to show the video stream again, resume analysis by calling ``continueStream``.
- (BOOL)beginAnalysisOfDecompressionSession:(VTDecompressionSessionRef)decompressionSession error:(NSError**)error NS_SWIFT_NAME(beginAnalysis(of:));

/// Analyzes video frames for the given capture device input.
///
/// - parameter captureDeviceInput: An object that contains information about the specific camera and its captured content in the video stream.
/// - parameter error: An error object that describes an issue that occurs while processing the capture device input.
/// - returns: `YES` if the method succeeds; otherwise, `NO`.
///
/// Call this method to begin analyzing a video stream from the given <doc://com.apple.documentation/documentation/avfoundation/avcapturedeviceinput>. If the framework detects sensitive content in the video stream, the capture-device-input interrupts subsequent frames with the `AVCaptureSessionInterruptionReasonSensitiveContentMitigationActivated` interruption reason to effectively censor the video stream on the person's behalf. When your app is ready to show the video stream again, resume analysis by calling ``continueStream``.
- (BOOL)beginAnalysisOfCaptureDeviceInput:(AVCaptureDeviceInput *)captureDeviceInput error:(NSError**)error NS_SWIFT_NAME(beginAnalysis(of:));

/// Stops stream analysis.
///
/// This method stops analyzing the video stream in reference to the most recent call to `beginAnalysis`.
- (void)endAnalysis;

// MARK: - Continuation

/// Indicates that your app is ready to resume video stream analysis.
///
/// When the framework detects sensitive content in the video stream, it pauses analysis and begins censoring the stream's video frames. Call this method to resume analysis and stop censoring video frames when your app is ready to show the stream again.
- (void) continueStream;

@end

/// Intervention guidance that the framework recommends based on the nature of the detected sensitive content.
API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macos, macCatalyst, tvos, visionos)
@interface SCSensitivityAnalysis (VideoStreamAnalysis)

/// Intervention guidance that suggests the app interrupt the video stream.
@property (readonly) BOOL shouldInterruptVideo;

/// Intervention guidance that suggests the app indicate the presence of sensitive content.
@property (readonly) BOOL shouldIndicateSensitivity;

/// Intervention guidance that suggests the app mute the audio of the current video stream.
@property (readonly) BOOL shouldMuteAudio;

@end

NS_HEADER_AUDIT_END(nullability)
