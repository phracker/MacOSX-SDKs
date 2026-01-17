//
//  INPlacemarkResolutionResult.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

@class CLPlacemark;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0))
@interface INPlacemarkResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given CLPlacemark. The resolvedPlacemark can be different than the original CLPlacemark. This allows app extensions to dynamically fill-in details about the CLPlacemark, as appropriate. To make a new CLPlacemark, see <Intents/CLPlacemark+IntentsAdditions.h>. 
// Use +notRequired to continue with a 'nil' value.

+ (instancetype)successWithResolvedPlacemark:(CLPlacemark *)resolvedPlacemark NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to disambiguate between the provided placemarks.
+ (instancetype)disambiguationWithPlacemarksToDisambiguate:(NSArray<CLPlacemark *> *)placemarksToDisambiguate NS_SWIFT_NAME(disambiguation(with:));

// This resolution result is to ask Siri to confirm if this is the placemark with which the user wants to continue.
+ (instancetype)confirmationRequiredWithPlacemarkToConfirm:(nullable CLPlacemark *)placemarkToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
