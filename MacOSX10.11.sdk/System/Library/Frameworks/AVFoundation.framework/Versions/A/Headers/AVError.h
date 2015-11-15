/*
    File:  AVError.h
 
	Framework:  AVFoundation
 
	Copyright 2010-2014 Apple Inc. All rights reserved.

 */

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>

AVF_EXPORT NSString *const AVFoundationErrorDomain                  NS_AVAILABLE(10_7, 4_0);

AVF_EXPORT NSString *const AVErrorDeviceKey                         NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT NSString *const AVErrorTimeKey                           NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT NSString *const AVErrorFileSizeKey                       NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT NSString *const AVErrorPIDKey                            NS_AVAILABLE(10_7, 4_0);
AVF_EXPORT NSString *const AVErrorRecordingSuccessfullyFinishedKey  NS_AVAILABLE(10_7, 4_0); // an NSNumber carrying a BOOL indicating whether the recording is playable
AVF_EXPORT NSString *const AVErrorMediaTypeKey                      NS_AVAILABLE(10_7, 4_3); // an NSString, as defined in AVMediaFormat.h
AVF_EXPORT NSString *const AVErrorMediaSubTypeKey                   NS_AVAILABLE(10_7, 4_3); // an NSArray of NSNumbers carrying four character codes (4ccs) as defined in CoreAudioTypes.h for audio media and in CMFormatDescription.h for video media.
AVF_EXPORT NSString *const AVErrorPresentationTimeStampKey          NS_AVAILABLE(10_10, 8_0); // an NSValue carrying a CMTime
AVF_EXPORT NSString *const AVErrorPersistentTrackIDKey				NS_AVAILABLE(10_10, 8_0); // an NSNumber carrying a CMPersistentTrackID
AVF_EXPORT NSString *const AVErrorFileTypeKey						NS_AVAILABLE(10_10, 8_0); // an NSString, as defined in AVMediaFormat.h

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))

AVF_EXPORT NSString *const AVErrorDiscontinuityFlagsKey             NS_AVAILABLE(10_7, NA);

#endif // (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))

typedef NS_ENUM(NSInteger, AVError) {
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
    AVErrorDeviceIsNotAvailableInBackground NS_DEPRECATED_IOS(4_3, 9_0, "AVCaptureSession no longer produces an AVCaptureSessionRuntimeErrorNotification with this error. See AVCaptureSessionInterruptionReasonVideoDeviceNotAvailableInBackground.") = -11837,
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
    AVErrorFailedToParse	NS_AVAILABLE(10_10, 8_0)		= -11853,
	AVErrorFileTypeDoesNotSupportSampleReferences NS_AVAILABLE(10_10, 8_0)	= -11854,  // userInfo contains AVErrorFileTypeKey
    AVErrorUndecodableMediaData NS_AVAILABLE(10_10, 8_0)  = -11855,
    AVErrorAirPlayControllerRequiresInternet NS_AVAILABLE(10_10, 8_3) = -11856,
    AVErrorAirPlayReceiverRequiresInternet NS_AVAILABLE(10_10, 8_3) = -11857,
    AVErrorVideoCompositorFailed NS_AVAILABLE(10_11, 9_0) = -11858,
#if TARGET_OS_IPHONE
    AVErrorRecordingAlreadyInProgress NS_AVAILABLE_IOS(9_0) = -11859, // on iOS, AVCaptureMovieFileOutput only supports one recording at a time
#endif
	
};
