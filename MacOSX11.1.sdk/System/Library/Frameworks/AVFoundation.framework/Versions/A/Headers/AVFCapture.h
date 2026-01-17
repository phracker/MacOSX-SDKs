/*
    File:  AVFCapture.h
 
    Framework:  AVFoundation
 
    Copyright 2020 Apple Inc. All rights reserved.
*/

#import <TargetConditionals.h>


#if (TARGET_OS_IPHONE || defined(__MAC_10_7))
#import <AVFoundation/AVCaptureDataOutputSynchronizer.h>
#import <AVFoundation/AVCaptureDevice.h>
#import <AVFoundation/AVCaptureInput.h>
#import <AVFoundation/AVCaptureOutput.h>
#import <AVFoundation/AVCaptureSession.h>
#import <AVFoundation/AVCaptureSystemPressure.h>
#import <AVFoundation/AVCaptureVideoPreviewLayer.h>
#endif

#import <AVFoundation/AVMetadataObject.h>

#import <AVFoundation/AVDepthData.h>
#import <AVFoundation/AVPortraitEffectsMatte.h>
#import <AVFoundation/AVSemanticSegmentationMatte.h>
