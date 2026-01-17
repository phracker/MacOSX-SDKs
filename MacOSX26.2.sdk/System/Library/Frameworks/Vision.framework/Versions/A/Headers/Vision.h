//
//  Vision.h
//  Vision
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//
#import <Foundation/Foundation.h>

#import <Vision/VNDefines.h>
#import <Vision/VNTypes.h>
#import <Vision/VNError.h>
#import <Vision/VNUtils.h>
#import <Vision/VNFaceLandmarks.h>
#import <Vision/VNRequest.h>
#import <Vision/VNRequestRevisionProviding.h>
#import <Vision/VNFaceObservationAccepting.h>
#import <Vision/VNClassifyImageRequest.h>
#import <Vision/VNDetectBarcodesRequest.h>
#import <Vision/VNDetectFaceRectanglesRequest.h>
#import <Vision/VNDetectFaceLandmarksRequest.h>
#import <Vision/VNDetectFaceCaptureQualityRequest.h>
#import <Vision/VNDetectHorizonRequest.h>
#import <Vision/VNDetectRectanglesRequest.h>
#import <Vision/VNDetectTextRectanglesRequest.h>
#import <Vision/VNRecognizeTextRequest.h>
#import <Vision/VNGenerateAttentionBasedSaliencyImageRequest.h>
#import <Vision/VNGenerateObjectnessBasedSaliencyImageRequest.h>
#import <Vision/VNGenerateImageFeaturePrintRequest.h>
#import <Vision/VNCoreMLRequest.h>
#import <Vision/VNTargetedImageRequest.h>
#import <Vision/VNImageRegistrationRequest.h>
#import <Vision/VNRequestHandler.h>
#import <Vision/VNObservation.h>
#import <Vision/VNTrackingRequest.h>
#import <Vision/VNTrackObjectRequest.h>
#import <Vision/VNTrackRectangleRequest.h>
#import <Vision/VNDetectHumanRectanglesRequest.h>
#import <Vision/VNRecognizeAnimalsRequest.h>
#import <Vision/VNGenerateOpticalFlowRequest.h>
#import <Vision/VNVideoProcessor.h>
#import <Vision/VNDetectedPoint.h>
#import <Vision/VNDetectHumanBodyPoseRequest.h>
#import <Vision/VNDetectHumanHandPoseRequest.h>
#import <Vision/VNDetectContoursRequest.h>
#import <Vision/VNGeometry.h>
#import <Vision/VNGeometryUtils.h>
#import <Vision/VNDetectTrajectoriesRequest.h>
#import <Vision/VNGeneratePersonSegmentationRequest.h>
#import <Vision/VNDetectDocumentSegmentationRequest.h>
#import <Vision/VNGenerateForegroundInstanceMaskRequest.h>
#import <Vision/VNGeneratePersonInstanceMaskRequest.h>
#import <Vision/VNTrackTranslationalImageRegistrationRequest.h>
#import <Vision/VNTrackHomographicImageRegistrationRequest.h>
#import <Vision/VNTrackOpticalFlowRequest.h>
#import <Vision/VNDetectAnimalBodyPoseRequest.h>
#import <Vision/VNDetectHumanBodyPose3DRequest.h>
#import <Vision/VNHumanBodyRecognizedPoint3D.h>
#import <Vision/VNRecognizedPoint3D.h>
#import <Vision/VNCalculateImageAestheticsScoresRequest.h>

/* The version of the Vision framework */
VN_EXPORT double VNVisionVersionNumber API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
