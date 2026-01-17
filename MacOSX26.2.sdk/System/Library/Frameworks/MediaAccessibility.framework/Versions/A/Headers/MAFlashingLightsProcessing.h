//
//  MAFlashingLightsProcessing.h
//  MediaAccessibility
//

#ifdef __OBJC__

#import <Foundation/Foundation.h>
#import <MediaAccessibility/MADefinitions.h>
#import <IOSurface/IOSurfaceRef.h>

NS_ASSUME_NONNULL_BEGIN

MA_EXPORT API_AVAILABLE(ios(17.0), tvos(17.0), watchos(10.0), macos(14.0)) NS_REFINED_FOR_SWIFT
@interface MAFlashingLightsProcessorResult : NSObject

// Indicates whether the outSurface was modified. If the surface cannot be processed, this will be false.
@property (nonatomic, readonly) BOOL surfaceProcessed;

// Indicates the amount of dimming that will occur in the outSurface based on analysis of the intensity of the flashing lights. Range is [0-100].
@property (nonatomic, readonly) float mitigationLevel;

// Indicates the measured intensity of sequences of flashing lights for the specific inSurface. Range is [0-100].
@property (nonatomic, readonly) float intensityLevel;

@end

typedef NSString *MAFlashingLightsProcessorOptionKey NS_EXTENSIBLE_STRING_ENUM NS_SWIFT_NAME(MAFlashingLightsProcessor.OptionKey);

MA_EXPORT API_AVAILABLE(ios(17.0), tvos(17.0), watchos(10.0), macos(14.0))
@interface MAFlashingLightsProcessor : NSObject

/*!
 @abstract Determines whether the flashing lights processor is able to process the content in the surface for flashing lights. This might be false on
 unsupported hardware or unsupported color spaces.
 @result A boolean result.
 */
- (BOOL)canProcessSurface:(IOSurfaceRef)surface;

/*!
 @abstract Processes an inSurface by analyzing pixels for sequences of flashing lights and then darkens content to reduce the risk of discomfort from some users.
 The outSurface will contain the mitigated content.
 The timestamp indicates the time at which the surface will be shown in the video playback. FPS will be determined based on the values of the timestamps.
 Options dictionary for additional parameters.
 @result An object which indicates whether the surface was able to be processed, the amount of mitigation that was applied, and the intensitry level that was detected.
 */
- (MAFlashingLightsProcessorResult *)processSurface:(IOSurfaceRef)inSurface outSurface:(IOSurfaceRef)outSurface timestamp:(CFAbsoluteTime)timestamp options:(NSDictionary<MAFlashingLightsProcessorOptionKey, id> *_Nullable)options NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END

#endif
