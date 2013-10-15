/* CoreImage - CIDetector.h
 
 Copyright (c) 2010 Apple Inc.
 All rights reserved. */


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

/** Returns an array of CIFeature instances in the given image.
 The array is sorted by confidence, highest confidence first. 
 The options dictionary can contain a CIDetectorImageOrientation key value. */
- (NSArray *)featuresInImage:(CIImage *)image options:(NSDictionary *)options __OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_5_0);

@end



// Types to be used for +[CIDetector detectorOfType:context:options:]

/* Specifies a detector type for face recognition. */
CORE_IMAGE_EXPORT NSString* const CIDetectorTypeFace __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);


// Options that can be used with +[CIDetector detectorOfType:context:options:]

/* The key in the options dictionary used to specify a accuracy / performance tradeoff to be used. */
CORE_IMAGE_EXPORT NSString* const CIDetectorAccuracy __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

/* These are values to be used with the CIDetectorAccuracy key when created a CIDetector.
 There is a performance / accuracy tradeoff to be made. The default value will work well for most
 situations, but using these the detector will favour performance over accuracy or
 accuracy over performance. */
CORE_IMAGE_EXPORT NSString* const CIDetectorAccuracyLow __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0); ///< Lower accuracy, higher performance
CORE_IMAGE_EXPORT NSString* const CIDetectorAccuracyHigh __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0); ///< Lower performance, higher accuracy

/*The key in the options dictionary used to specify that feature tracking should be used. */
CORE_IMAGE_EXPORT NSString* const CIDetectorTracking __OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_NA);

/* The key in the options dictionary used to specify the minimum size that the 
 detector will recognize as a feature.  The value for this key is an float NSNumber 
 from 0.0 ... 1.0 that represents a fraction of the minor dimension of the image. */
CORE_IMAGE_EXPORT NSString* const CIDetectorMinFeatureSize __OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_NA);


// Options that can be used with -[CIDetector featuresInImage:options:]

/* The value for this key is an integer NSNumber from 1..8 such as that
 found in kCGImagePropertyOrientation.  If present, the detection will be done
 based on that orientation but the coordinates in the returned features will
 still be based on those of the image. */
CORE_IMAGE_EXPORT NSString *const CIDetectorImageOrientation __OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_5_0);

