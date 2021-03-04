//
// RPError.h
// ReplayKit
//
// Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
extern NSString *const __nonnull RPRecordingErrorDomain;

NS_ASSUME_NONNULL_BEGIN

NS_ENUM_AVAILABLE(11_0, 9_0)
typedef NS_ENUM (NSInteger, RPRecordingErrorCode) {
    RPRecordingErrorUnknown = -5800,
    RPRecordingErrorUserDeclined = -5801,                           // The user declined app recording.
    RPRecordingErrorDisabled = -5802,                               // App recording has been disabled via parental controls.
    RPRecordingErrorFailedToStart = -5803,                          // Recording failed to start
    RPRecordingErrorFailed = -5804,                                 // Failed during recording
    RPRecordingErrorInsufficientStorage = -5805,                    // Insufficient storage for recording.
    RPRecordingErrorInterrupted = -5806,                            // Recording interrupted by other app
    RPRecordingErrorContentResize = -5807,                          // Recording interrupted by multitasking and Content Resizing
    RPRecordingErrorBroadcastInvalidSession = -5808,                // Attempted to start a broadcast without a prior session
    RPRecordingErrorSystemDormancy = -5809,                         // Recording was forced to end when user pressed the power button
    RPRecordingErrorEntitlements = -5810,                           // Recording failed due to missing entitlements
    RPRecordingErrorActivePhoneCall = -5811,                        // Recording unable to to record due to active phone call
    RPRecordingErrorFailedToSave = -5812,                           // Failed to save recording to camera roll
    RPRecordingErrorCarPlay = -5813,                                // Failed to start recording due to carplay being active
    RPRecordingErrorFailedApplicationConnectionInvalid = -5814,     // Failed during recording application connection invalid
    RPRecordingErrorFailedApplicationConnectionInterrupted = -5815, // Failed during recording appliation connection interrupted
    RPRecordingErrorFailedNoMatchingApplicationContext = -5816,     // Failed during recording context id does not match application
    RPRecordingErrorFailedMediaServicesFailure = -5817,             // Failed during recording due to mediaservices failure
    RPRecordingErrorVideoMixingFailure = -5818,                     // Failed during recording due to audio/video mixing failure
    RPRecordingErrorBroadcastSetupFailed = -5819,                   // Failed during saving to camera roll
    RPRecordingErrorFailedToObtainURL = -5820,                      // Failed to obtain video URL
    RPRecordingErrorFailedIncorrectTimeStamps  = -5821,             // Failed to due to malformed start and end time intervals
    RPRecordingErrorFailedToProcessFirstSample = -5822,             // Failed to failure to process first sample buffer for the asset writer
    RPRecordingErrorFailedAssetWriterFailedToSave = -5823,          // Failed due to finishWritingWithCompletionHandler failed
    RPRecordingErrorFailedNoAssetWriter = -5824,                    // Failed due to no asset writer
    RPRecordingErrorFailedAssetWriterInWrongState = -5825,          // Failed due to no asset writer being in wrong state
    RPRecordingErrorFailedAssetWriterExportFailed = -5826,          // Failed due to export session failing
    RPRecordingErrorFailedToRemoveFile = -5827,                     // Failed to properly remove temp file for recording
    RPRecordingErrorFailedAssetWriterExportCanceled = -5828,        // Failed due to export session being canceled
    RPRecordingErrorAttemptToStopNonRecording = -5829,              // Failed due to attempting to stop a recording that wasn't in recording state
    RPRecordingErrorAttemptToStartInRecordingState = -5830,         // Failed due to attempting to start a recording thats already in a recording state
    RPRecordingErrorPhotoFailure = -5831,                           // Failed during saving to camera roll
    RPRecordingErrorRecordingInvalidSession = -5832,                // Attempted to start an invalid recording session
    RPRecordingErrorFailedToStartCaptureStack = -5833,              // Failed to start due to video/audio capture failure
    RPRecordingErrorInvalidParameter = -5834,                       // Failed due to invalid parameter
    RPRecordingErrorFilePermissions = -5835,                        // Failed due to file permissions error
    RPRecordingErrorCodeSuccessful = 0                              // Successfully saved video to camera roll
};

NS_ASSUME_NONNULL_END
