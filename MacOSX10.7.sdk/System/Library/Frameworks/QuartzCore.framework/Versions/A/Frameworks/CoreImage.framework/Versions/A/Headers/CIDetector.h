//
//  CIDetector.h
//  CoreImage
//
//  Created by Daniel Eggert on 1/21/10.
//  Copyright 2010 Apple Inc. All rights reserved.
//


#import "CoreImageDefines.h"
#import <Foundation/Foundation.h>

@class CIImage;
@class CIContext;



/** Detects features in images.
 
 This class potentially holds onto a lot of state. Hence it may be beneficial from a performance perspective to re-use the same CIDetector instance. Specifying a CIContext when creating a detector may have an impact on performance since this context may be used when analyzing an image.
 */
CORE_IMAGE_CLASS_EXPORT
@interface CIDetector : NSObject {}

/** Returns a new detector instance of the given type.
 
 The type is used to specify the usage intent.
 
 The context argument specifies the CIContext to be used to operate on the image. May be nil.
 
 If the input image to -featuresInImage: is the output of a CoreImage operation, it may improve performance to specify the same context that was used to operate on that image.
 
 The detector may do image processing in this context and if the image is on the GPU and the specified context is a GPU context this may avoid additional upload to / download from the GPU. If the input image is on the CPU (or the output from a CPU based context) specifying a GPU based context (or vice versa) may reduce performance.
 
 The options parameter lets you optinally specify a accuracy / performance tradeoff. Can be nil or an empty dictionary. */
+ (CIDetector *)detectorOfType:(NSString*)type context:(CIContext *)context options:(NSDictionary *)options AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;

/** Returns an array of CIFeature instances in the given image.
 The array is sorted by confidence, highest confidence first. */
- (NSArray *)featuresInImage:(CIImage *)image AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;

@end



// Types to be used for +[CIDetector detectorOfType:context:options:]

/** Specifies a detector type for face recognition. */
CORE_IMAGE_EXPORT NSString* const CIDetectorTypeFace AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;


/** The key in the options dictionary used to specify a accuracy / performance tradeoff to be used. */
CORE_IMAGE_EXPORT NSString* const CIDetectorAccuracy AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;

/** These are values to be used with the CIDetectorAccuracy key when created a CIDetector.
 There is a performance / accuracy tradeoff to be made. The default value will work well for most
 situations, but using these the detector will favour performance over accuracy or
 accuracy over performance. */
CORE_IMAGE_EXPORT NSString* const CIDetectorAccuracyLow AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER; ///< Lower accuracy, higher performance
CORE_IMAGE_EXPORT NSString* const CIDetectorAccuracyHigh AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER; ///< Lower performance, higher accuracy

