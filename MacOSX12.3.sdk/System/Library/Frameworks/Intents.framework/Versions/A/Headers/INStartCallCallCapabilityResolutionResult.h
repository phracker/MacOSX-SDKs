//
//  INStartCallCallCapabilityResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#import <Intents/INCallCapabilityResolutionResult.h>

typedef NS_ENUM(NSInteger, INStartCallCallCapabilityUnsupportedReason) {
    INStartCallCallCapabilityUnsupportedReasonVideoCallUnsupported = 1,
    INStartCallCallCapabilityUnsupportedReasonMicrophoneNotAccessible,
    INStartCallCallCapabilityUnsupportedReasonCameraNotAccessible,
} API_AVAILABLE(ios(13.0), watchos(6.0)) API_UNAVAILABLE(macos, tvos);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), watchos(6.0))
API_UNAVAILABLE(macos, tvos)
@interface INStartCallCallCapabilityResolutionResult : INCallCapabilityResolutionResult

+ (instancetype)unsupportedForReason:(INStartCallCallCapabilityUnsupportedReason)reason NS_SWIFT_NAME(unsupported(forReason:));

- (instancetype)initWithCallCapabilityResolutionResult:(INCallCapabilityResolutionResult *)callCapabilityResolutionResult;

@end

NS_ASSUME_NONNULL_END
