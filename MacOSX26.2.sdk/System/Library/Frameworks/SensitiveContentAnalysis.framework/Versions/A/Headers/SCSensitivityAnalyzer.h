//
//  SCSensitivityAnalyzer.h
//  SensitiveContentAnalysis
//
//  Copyright (c).2023, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <ImageIO/ImageIO.h>
#import <SensitiveContentAnalysis/SCSensitivityAnalysis.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// SensitivityAnalysis Policy on device, represents type of interventions when enabled
typedef NS_ENUM(NSInteger, SCSensitivityAnalysisPolicy) {
    /// No feature enabled that is requiring Sensitive Analysis on device, analysis will be disabled
    SCSensitivityAnalysisPolicyDisabled = 0,
    /// Sensitive Analysis is enabled on device through "Sensitive Content Warning" in Settings.
    /// It is expected that brief/inline UI, like simple "show" button.
    SCSensitivityAnalysisPolicySimpleInterventions = 1,
    /// Sensitive Analysis is enabled for kids or teens in ScreenTime through "Communications Safety" feature.
    /// It's expected to have more descriptive UI for the user, explaining potential risks.
    SCSensitivityAnalysisPolicyDescriptiveInterventions = 2,
} API_AVAILABLE(macos(14.0), ios(17.0), visionos(2.0)) API_UNAVAILABLE(watchos, tvos);

/// Main class for content sensitivity analysis
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(14.0), ios(17.0), visionos(2.0)) API_UNAVAILABLE(watchos, tvos)
@interface SCSensitivityAnalyzer : NSObject

- (instancetype)init;

/// Current SCSensitivityAnalysisPolicy set on device. Can be used to determine whether analysis is available or not
@property (assign, readonly) SCSensitivityAnalysisPolicy analysisPolicy;

/**
 * Analyze sensitivity of Image File on disk (only local fileURL)
 * @param fileURL  Image file location on disk
 * @param completionHandler  Block to be called on completion (callback is called on unspecified queue)
 */
- (void)analyzeImageFile:(nonnull NSURL *)fileURL
       completionHandler:(void(^)(SCSensitivityAnalysis * _Nullable results, NSError * _Nullable error))completionHandler
            NS_SWIFT_NAME(analyzeImage(at:completionHandler:));

/**
 * Analyze sensitivity of CGImage in memory
 * @param image  CGImage reference
 * @param completionHandler  Block to be called on completion (callback is called on unspecified queue)
 */
- (void)analyzeCGImage:(nonnull CGImageRef)image
     completionHandler:(void(^)(SCSensitivityAnalysis * _Nullable results, NSError * _Nullable error))completionHandler
            NS_SWIFT_NAME(analyzeImage(_:completionHandler:));

/**
 * Analyze sensitivity of Video File on disk.
 * @param fileURL  Video file location on disk
 * @param completionHandler  Block to be called on completion (callback is called on unspecified queue)
 * @return An NSProgress instance for tracking video file analysis progress
 */
- (NSProgress *)analyzeVideoFile:(nonnull NSURL *)fileURL
               completionHandler:(void(^)(SCSensitivityAnalysis * _Nullable results, NSError * _Nullable error))completionHandler
                NS_REFINED_FOR_SWIFT;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
