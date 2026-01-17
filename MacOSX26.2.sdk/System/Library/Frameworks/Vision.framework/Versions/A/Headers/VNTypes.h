//
//  VNTypes.h
//  Vision
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Vision/VNDefines.h>


typedef float VNConfidence;

typedef float VNAspectRatio;

typedef float VNDegrees;

typedef NS_ENUM(NSUInteger, VNImageCropAndScaleOption)
{
    VNImageCropAndScaleOptionCenterCrop = 0,  // scale image maintaining aspect ratio to fit on the short side and crop centered on the long side
    VNImageCropAndScaleOptionScaleFit = 1,    // scale to size required by algorithm while maintaining the original aspect ratio
    VNImageCropAndScaleOptionScaleFill = 2,
    VNImageCropAndScaleOptionScaleFitRotate90CCW = 0x100 + VNImageCropAndScaleOptionScaleFit, // scale image maintaining aspect ratio to fit on the long side but also rotate by 90 degrees counter clockwise to optimize portrait images to fit into landscape buffers for algorithms that are rotation agnostic
    VNImageCropAndScaleOptionScaleFillRotate90CCW = 0x100 + VNImageCropAndScaleOptionScaleFill, // scale image and rotate by 90 degrees counter clockwise to optimize portrait images to fill into landscape buffers for algorithms that are rotation agnostic
};


API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0))
typedef NSString* VNComputeStage NS_STRING_ENUM;

/*!
	@brief The stage of a request where the main functionality is being performed.
	@discussion All requests will have this compute stage.
*/
VN_EXPORT VNComputeStage const VNComputeStageMain NS_SWIFT_NAME(main) API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));

/*!
	@brief A compute stage for additional analysis and/or conversion of the data produced by the `VNComputeStageMain`.
	@discussion This is an optional compute stage that some requests may expose.
*/
VN_EXPORT VNComputeStage const VNComputeStagePostProcessing NS_SWIFT_NAME(postProcessing) API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));


/*!
	@brief Barcode symbologies that are supported by the Vision framework.
	
	@discussion The actual set of barcode symbologies that can actually be recognized by a specific version of the Vision framework should be determined by using the VNRequestNameSupportedBarcodeSymbologies request.
*/
typedef NSString *VNBarcodeSymbology NS_STRING_ENUM;

VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyAztec NS_SWIFT_NAME(aztec) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyCode39 NS_SWIFT_NAME(code39) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyCode39Checksum NS_SWIFT_NAME(code39Checksum) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyCode39FullASCII NS_SWIFT_NAME(code39FullASCII) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyCode39FullASCIIChecksum NS_SWIFT_NAME(code39FullASCIIChecksum) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyCode93 NS_SWIFT_NAME(code93) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyCode93i NS_SWIFT_NAME(code93i) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyCode128 NS_SWIFT_NAME(code128) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyDataMatrix NS_SWIFT_NAME(dataMatrix) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyEAN8 NS_SWIFT_NAME(ean8) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyEAN13 NS_SWIFT_NAME(ean13) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyI2of5 NS_SWIFT_NAME(i2of5) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyI2of5Checksum NS_SWIFT_NAME(i2of5Checksum) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyITF14 NS_SWIFT_NAME(itf14) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyPDF417 NS_SWIFT_NAME(pdf417) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyQR NS_SWIFT_NAME(qr) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyUPCE NS_SWIFT_NAME(upce) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
// Revision 2
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyCodabar NS_SWIFT_NAME(codabar) API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyGS1DataBar NS_SWIFT_NAME(gs1DataBar) API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyGS1DataBarExpanded NS_SWIFT_NAME(gs1DataBarExpanded) API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyGS1DataBarLimited NS_SWIFT_NAME(gs1DataBarLimited) API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyMicroPDF417 NS_SWIFT_NAME(microPDF417) API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyMicroQR NS_SWIFT_NAME(microQR) API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyMSIPlessey NS_SWIFT_NAME(msiPlessey) API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));


API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
typedef NS_ENUM(NSUInteger, VNElementType)
{
	VNElementTypeUnknown = 0,
	VNElementTypeFloat   = 1,		// IEEE 754 single-precision floating point value
	VNElementTypeDouble  = 2,		// IEEE 754 double-precision floating point value
};




typedef NSString* VNVideoProcessingOption NS_STRING_ENUM API_DEPRECATED_WITH_REPLACEMENT("VNVideoProcessorRequestProcessingOptions", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));
VN_EXPORT VNVideoProcessingOption const VNVideoProcessingOptionFrameCadence API_DEPRECATED_WITH_REPLACEMENT("VNVideoProcessorRequestProcessingOptions", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));
VN_EXPORT VNVideoProcessingOption const VNVideoProcessingOptionTimeInterval API_DEPRECATED_WITH_REPLACEMENT("VNVideoProcessorRequestProcessingOptions", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));


API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0))
typedef NS_CLOSED_ENUM(NSInteger, VNChirality)
{
    VNChiralityUnknown = 0,
    VNChiralityLeft = -1,
    VNChiralityRight = 1
};



API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0))
typedef NS_CLOSED_ENUM(NSInteger, VNPointsClassification)
{
	VNPointsClassificationDisconnected = 0,
	VNPointsClassificationOpenPath,
	VNPointsClassificationClosedPath
};


API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0))
typedef NS_CLOSED_ENUM(NSInteger, VNBarcodeCompositeType)
{
    VNBarcodeCompositeTypeNone= 0,
    VNBarcodeCompositeTypeLinked,
    VNBarcodeCompositeTypeGS1TypeA,
    VNBarcodeCompositeTypeGS1TypeB,
    VNBarcodeCompositeTypeGS1TypeC,
};



typedef NSString * VNRecognizedPointKey NS_STRING_ENUM;

typedef NSString * VNRecognizedPointGroupKey NS_STRING_ENUM;


typedef VNRecognizedPointKey VNAnimalBodyPoseObservationJointName NS_TYPED_ENUM NS_SWIFT_NAME(VNAnimalBodyPoseObservation.JointName) API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));

VN_EXPORT VNAnimalBodyPoseObservationJointName const VNAnimalBodyPoseObservationJointNameLeftEarTop API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));              // Head
VN_EXPORT VNAnimalBodyPoseObservationJointName const VNAnimalBodyPoseObservationJointNameRightEarTop API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));             // Head
VN_EXPORT VNAnimalBodyPoseObservationJointName const VNAnimalBodyPoseObservationJointNameLeftEarMiddle API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));           // Head
VN_EXPORT VNAnimalBodyPoseObservationJointName const VNAnimalBodyPoseObservationJointNameRightEarMiddle API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));          // Head
VN_EXPORT VNAnimalBodyPoseObservationJointName const VNAnimalBodyPoseObservationJointNameLeftEarBottom API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));           // Head
VN_EXPORT VNAnimalBodyPoseObservationJointName const VNAnimalBodyPoseObservationJointNameRightEarBottom API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));          // Head
VN_EXPORT VNAnimalBodyPoseObservationJointName const VNAnimalBodyPoseObservationJointNameLeftEye API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));                 // Head
VN_EXPORT VNAnimalBodyPoseObservationJointName const VNAnimalBodyPoseObservationJointNameRightEye API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));                // Head
VN_EXPORT VNAnimalBodyPoseObservationJointName const VNAnimalBodyPoseObservationJointNameNose API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));                    // Head
VN_EXPORT VNAnimalBodyPoseObservationJointName const VNAnimalBodyPoseObservationJointNameNeck API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));                    // Trunk
VN_EXPORT VNAnimalBodyPoseObservationJointName const VNAnimalBodyPoseObservationJointNameLeftFrontElbow API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));          // Forelegs
VN_EXPORT VNAnimalBodyPoseObservationJointName const VNAnimalBodyPoseObservationJointNameRightFrontElbow API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));         // Forelegs
VN_EXPORT VNAnimalBodyPoseObservationJointName const VNAnimalBodyPoseObservationJointNameLeftFrontKnee API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));           // Forelegs
VN_EXPORT VNAnimalBodyPoseObservationJointName const VNAnimalBodyPoseObservationJointNameRightFrontKnee API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));          // Forelegs
VN_EXPORT VNAnimalBodyPoseObservationJointName const VNAnimalBodyPoseObservationJointNameLeftFrontPaw API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));            // Forelegs
VN_EXPORT VNAnimalBodyPoseObservationJointName const VNAnimalBodyPoseObservationJointNameRightFrontPaw API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));           // Forelegs
VN_EXPORT VNAnimalBodyPoseObservationJointName const VNAnimalBodyPoseObservationJointNameLeftBackElbow API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));           // Hindlegs
VN_EXPORT VNAnimalBodyPoseObservationJointName const VNAnimalBodyPoseObservationJointNameRightBackElbow API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));          // Hindlegs
VN_EXPORT VNAnimalBodyPoseObservationJointName const VNAnimalBodyPoseObservationJointNameLeftBackKnee API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));            // Hindlegs
VN_EXPORT VNAnimalBodyPoseObservationJointName const VNAnimalBodyPoseObservationJointNameRightBackKnee API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));           // Hindlegs
VN_EXPORT VNAnimalBodyPoseObservationJointName const VNAnimalBodyPoseObservationJointNameLeftBackPaw API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));             // Hindlegs
VN_EXPORT VNAnimalBodyPoseObservationJointName const VNAnimalBodyPoseObservationJointNameRightBackPaw API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));            // Hindlegs
VN_EXPORT VNAnimalBodyPoseObservationJointName const VNAnimalBodyPoseObservationJointNameTailTop API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));                 // Tail
VN_EXPORT VNAnimalBodyPoseObservationJointName const VNAnimalBodyPoseObservationJointNameTailMiddle API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));              // Tail
VN_EXPORT VNAnimalBodyPoseObservationJointName const VNAnimalBodyPoseObservationJointNameTailBottom API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));              // Tail


typedef VNRecognizedPointGroupKey VNAnimalBodyPoseObservationJointsGroupName NS_TYPED_ENUM NS_SWIFT_NAME(VNAnimalBodyPoseObservation.JointsGroupName) API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));

VN_EXPORT VNAnimalBodyPoseObservationJointsGroupName const VNAnimalBodyPoseObservationJointsGroupNameHead API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));        // Nose, eyes and ears
VN_EXPORT VNAnimalBodyPoseObservationJointsGroupName const VNAnimalBodyPoseObservationJointsGroupNameTrunk API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));       // Neck
VN_EXPORT VNAnimalBodyPoseObservationJointsGroupName const VNAnimalBodyPoseObservationJointsGroupNameForelegs API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));    // Front left/right elbows, knees and paws
VN_EXPORT VNAnimalBodyPoseObservationJointsGroupName const VNAnimalBodyPoseObservationJointsGroupNameHindlegs API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));    // Back left/right elbows, knees and paws
VN_EXPORT VNAnimalBodyPoseObservationJointsGroupName const VNAnimalBodyPoseObservationJointsGroupNameTail API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));        // Top, middle, bottom parts of tail
VN_EXPORT VNAnimalBodyPoseObservationJointsGroupName const VNAnimalBodyPoseObservationJointsGroupNameAll API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));         // All


/*!
 @brief Human Body 3D Pose Joints that are suppported by Vision framework
 */
typedef VNRecognizedPointKey VNHumanBodyPose3DObservationJointName NS_TYPED_ENUM NS_SWIFT_NAME(VNHumanBodyPose3DObservation.JointName) API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));
VN_EXPORT VNHumanBodyPose3DObservationJointName const VNHumanBodyPose3DObservationJointNameRoot API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));
VN_EXPORT VNHumanBodyPose3DObservationJointName const VNHumanBodyPose3DObservationJointNameRightHip API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));
VN_EXPORT VNHumanBodyPose3DObservationJointName const VNHumanBodyPose3DObservationJointNameRightKnee API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));
VN_EXPORT VNHumanBodyPose3DObservationJointName const VNHumanBodyPose3DObservationJointNameRightAnkle API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));
VN_EXPORT VNHumanBodyPose3DObservationJointName const VNHumanBodyPose3DObservationJointNameLeftHip API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));
VN_EXPORT VNHumanBodyPose3DObservationJointName const VNHumanBodyPose3DObservationJointNameLeftKnee API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));
VN_EXPORT VNHumanBodyPose3DObservationJointName const VNHumanBodyPose3DObservationJointNameLeftAnkle API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));
VN_EXPORT VNHumanBodyPose3DObservationJointName const VNHumanBodyPose3DObservationJointNameSpine API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));
VN_EXPORT VNHumanBodyPose3DObservationJointName const VNHumanBodyPose3DObservationJointNameCenterShoulder API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));
VN_EXPORT VNHumanBodyPose3DObservationJointName const VNHumanBodyPose3DObservationJointNameCenterHead API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));
VN_EXPORT VNHumanBodyPose3DObservationJointName const VNHumanBodyPose3DObservationJointNameTopHead API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));
VN_EXPORT VNHumanBodyPose3DObservationJointName const VNHumanBodyPose3DObservationJointNameLeftShoulder API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));
VN_EXPORT VNHumanBodyPose3DObservationJointName const VNHumanBodyPose3DObservationJointNameLeftElbow API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));
VN_EXPORT VNHumanBodyPose3DObservationJointName const VNHumanBodyPose3DObservationJointNameLeftWrist API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));
VN_EXPORT VNHumanBodyPose3DObservationJointName const VNHumanBodyPose3DObservationJointNameRightShoulder API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));
VN_EXPORT VNHumanBodyPose3DObservationJointName const VNHumanBodyPose3DObservationJointNameRightElbow API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));
VN_EXPORT VNHumanBodyPose3DObservationJointName const VNHumanBodyPose3DObservationJointNameRightWrist API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));

typedef VNRecognizedPointGroupKey VNHumanBodyPose3DObservationJointsGroupName NS_TYPED_ENUM NS_SWIFT_NAME(VNHumanBodyPose3DObservation.JointsGroupName) API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));
VN_EXPORT VNHumanBodyPose3DObservationJointsGroupName const VNHumanBodyPose3DObservationJointsGroupNameHead API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0)); // center head, and top of head
VN_EXPORT VNHumanBodyPose3DObservationJointsGroupName const VNHumanBodyPose3DObservationJointsGroupNameTorso API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0)); // shoulders, spine, and hips
VN_EXPORT VNHumanBodyPose3DObservationJointsGroupName const VNHumanBodyPose3DObservationJointsGroupNameLeftArm API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0)); // left shoulder, left elbow, and left wrist
VN_EXPORT VNHumanBodyPose3DObservationJointsGroupName const VNHumanBodyPose3DObservationJointsGroupNameRightArm API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0)); // right shoulder, right elbow, and right wrist
VN_EXPORT VNHumanBodyPose3DObservationJointsGroupName const VNHumanBodyPose3DObservationJointsGroupNameLeftLeg API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0)); //  left ankle, left knee, and left hip
VN_EXPORT VNHumanBodyPose3DObservationJointsGroupName const VNHumanBodyPose3DObservationJointsGroupNameRightLeg API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0)); //  right ankle, right knee, and right hip
VN_EXPORT VNHumanBodyPose3DObservationJointsGroupName const VNHumanBodyPose3DObservationJointsGroupNameAll API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));

