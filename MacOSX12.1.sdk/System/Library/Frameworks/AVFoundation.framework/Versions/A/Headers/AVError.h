#if !__has_include(<AVFCore/AVError.h>)
/*
    File:  AVError.h
 
	Framework:  AVFoundation
 
	Copyright 2010-2021 Apple Inc. All rights reserved.

 */

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>

AVF_EXPORT NSErrorDomain const AVFoundationErrorDomain              API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0));

AVF_EXPORT NSString *const AVErrorDeviceKey                         API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0));
AVF_EXPORT NSString *const AVErrorTimeKey                           API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0));
AVF_EXPORT NSString *const AVErrorFileSizeKey                       API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0));
AVF_EXPORT NSString *const AVErrorPIDKey                            API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0));
AVF_EXPORT NSString *const AVErrorRecordingSuccessfullyFinishedKey  API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0)); // an NSNumber carrying a BOOL indicating whether the recording is playable
AVF_EXPORT NSString *const AVErrorMediaTypeKey                      API_AVAILABLE(macos(10.7), ios(4.3), tvos(9.0), watchos(1.0)); // an NSString, as defined in AVMediaFormat.h
AVF_EXPORT NSString *const AVErrorMediaSubTypeKey                   API_AVAILABLE(macos(10.7), ios(4.3), tvos(9.0), watchos(1.0)); // an NSArray of NSNumbers carrying four character codes (4ccs) as defined in CoreAudioTypes.h for audio media and in CMFormatDescription.h for video media.
AVF_EXPORT NSString *const AVErrorPresentationTimeStampKey          API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0)); // an NSValue carrying a CMTime
AVF_EXPORT NSString *const AVErrorPersistentTrackIDKey				API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0)); // an NSNumber carrying a CMPersistentTrackID
AVF_EXPORT NSString *const AVErrorFileTypeKey						API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0)); // an NSString, as defined in AVMediaFormat.h

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))

AVF_EXPORT NSString *const AVErrorDiscontinuityFlagsKey             API_AVAILABLE(macos(10.7)) API_UNAVAILABLE(ios, tvos, watchos);

#endif // (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))

typedef NS_ERROR_ENUM(AVFoundationErrorDomain, AVError) {
    AVErrorUnknown                                      = -11800,
    AVErrorOutOfMemory                                  = -11801,
    AVErrorSessionNotRunning                            = -11803,
    AVErrorDeviceAlreadyUsedByAnotherSession            = -11804,
    AVErrorNoDataCaptured                               = -11805,
    AVErrorSessionConfigurationChanged                  = -11806,
    AVErrorDiskFull                                     = -11807,
    AVErrorDeviceWasDisconnected                        = -11808,
    AVErrorMediaChanged                                 = -11809,
    AVErrorMaximumDurationReached                       = -11810,
    AVErrorMaximumFileSizeReached                       = -11811,
    AVErrorMediaDiscontinuity                           = -11812,
    AVErrorMaximumNumberOfSamplesForFileFormatReached   = -11813,
    AVErrorDeviceNotConnected                           = -11814,
    AVErrorDeviceInUseByAnotherApplication              = -11815,
    AVErrorDeviceLockedForConfigurationByAnotherProcess = -11817,
#if TARGET_OS_IPHONE
    AVErrorSessionWasInterrupted                        = -11818,
    AVErrorMediaServicesWereReset                       = -11819,
#endif
    AVErrorExportFailed                                 = -11820,
    AVErrorDecodeFailed                                 = -11821,  // userInfo may contain AVErrorMediaTypeKey, AVErrorMediaSubTypeKey & AVErrorPresentationTimeStampKey, if available
    AVErrorInvalidSourceMedia                           = -11822,
    AVErrorFileAlreadyExists                            = -11823,
    AVErrorCompositionTrackSegmentsNotContiguous        = -11824,
    AVErrorInvalidCompositionTrackSegmentDuration       = -11825,
    AVErrorInvalidCompositionTrackSegmentSourceStartTime= -11826,
    AVErrorInvalidCompositionTrackSegmentSourceDuration = -11827,
    AVErrorFileFormatNotRecognized                      = -11828,
    AVErrorFileFailedToParse                            = -11829,
    AVErrorMaximumStillImageCaptureRequestsExceeded     = -11830,
    AVErrorContentIsProtected                           = -11831,
    AVErrorNoImageAtTime                                = -11832,
    AVErrorDecoderNotFound                              = -11833,  // userInfo may contain AVErrorMediaTypeKey & AVErrorMediaSubTypeKey, if available
    AVErrorEncoderNotFound                              = -11834,  // userInfo may contain AVErrorMediaTypeKey & AVErrorMediaSubTypeKey, if available
    AVErrorContentIsNotAuthorized                       = -11835,
    AVErrorApplicationIsNotAuthorized                   = -11836,
#if TARGET_OS_IPHONE
    AVErrorDeviceIsNotAvailableInBackground API_DEPRECATED("AVCaptureSession no longer produces an AVCaptureSessionRuntimeErrorNotification with this error. See AVCaptureSessionInterruptionReasonVideoDeviceNotAvailableInBackground.", ios(4.3, 9.0), tvos(9.0, 9.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(macos) = -11837,
#endif
    AVErrorOperationNotSupportedForAsset                = -11838,
    
    AVErrorDecoderTemporarilyUnavailable                = -11839,  // userInfo may contain AVErrorMediaTypeKey & AVErrorMediaSubTypeKey, if available
    AVErrorEncoderTemporarilyUnavailable                = -11840,  // userInfo may contain AVErrorMediaTypeKey & AVErrorMediaSubTypeKey, if available
    AVErrorInvalidVideoComposition                      = -11841,
    AVErrorReferenceForbiddenByReferencePolicy          = -11842,
    AVErrorInvalidOutputURLPathExtension                = -11843,
    AVErrorScreenCaptureFailed                          = -11844,
    AVErrorDisplayWasDisabled                           = -11845,
    AVErrorTorchLevelUnavailable                        = -11846,
#if TARGET_OS_IPHONE
    AVErrorOperationInterrupted                         = -11847,
#endif
    AVErrorIncompatibleAsset                            = -11848,
    AVErrorFailedToLoadMediaData                        = -11849,
    AVErrorServerIncorrectlyConfigured                  = -11850,
	AVErrorApplicationIsNotAuthorizedToUseDevice		= -11852,
    AVErrorFailedToParse	API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0))		= -11853,
	AVErrorFileTypeDoesNotSupportSampleReferences API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0))	= -11854,  // userInfo contains AVErrorFileTypeKey
    AVErrorUndecodableMediaData API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0))  = -11855,
    AVErrorAirPlayControllerRequiresInternet API_AVAILABLE(macos(10.10), ios(8.3), tvos(9.0), watchos(1.3)) = -11856,
    AVErrorAirPlayReceiverRequiresInternet API_AVAILABLE(macos(10.10), ios(8.3), tvos(9.0), watchos(1.3)) = -11857,
    AVErrorVideoCompositorFailed API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(2.0)) = -11858,
	AVErrorRecordingAlreadyInProgress API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0)) API_UNAVAILABLE(macos) = -11859, // on iOS, AVCaptureMovieFileOutput only supports one recording at a time
	AVErrorCreateContentKeyRequestFailed API_AVAILABLE(macos(10.11)) API_UNAVAILABLE(ios, tvos) API_UNAVAILABLE(watchos) = -11860,
	AVErrorUnsupportedOutputSettings API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0)) = -11861,
	AVErrorOperationNotAllowed API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0), watchos(3.0)) = -11862,
	AVErrorContentIsUnavailable API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0)) = -11863,
	AVErrorFormatUnsupported API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0))  = -11864,
	AVErrorMalformedDepth API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0))     = -11865,
	AVErrorContentNotUpdated API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0))	= -11866,
	AVErrorNoLongerPlayable	 API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0))	= -11867,
	AVErrorNoCompatibleAlternatesForExternalDisplay API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0)) = -11868,
	AVErrorNoSourceTrack API_AVAILABLE(macos(10.13.2), ios(11.2), tvos(11.2), watchos(4.2)) = -11869,
	AVErrorExternalPlaybackNotSupportedForAsset API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0), watchos(5.0)) = -11870,
	AVErrorOperationNotSupportedForPreset API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0)) = -11871,
	AVErrorSessionHardwareCostOverage API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos, watchos) = -11872,
	AVErrorUnsupportedDeviceActiveFormat API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos, watchos) = -11873,
	AVErrorIncorrectlyConfigured API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0), watchos(7.0)) = -11875,
	AVErrorSegmentStartedWithNonSyncSample API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0), watchos(7.0)) = -11876,
	AVErrorRosettaNotInstalled API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0), watchos(7.0)) = -11877,
	AVErrorOperationCancelled API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0)) = -11878,
	AVErrorContentKeyRequestCancelled API_AVAILABLE(macos(11.4), ios(14.6), tvos(14.6), watchos(7.5)) = -11879,

};

#else
#import <AVFCore/AVError.h>
#endif
