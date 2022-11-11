//
//  INNoteContentTypeResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INNoteContentType.h>

NS_ASSUME_NONNULL_BEGIN

API_DEPRECATED("This resolution result is no longer used", ios(11.0, 13.0), watchos(4.0, 6.0))
API_UNAVAILABLE(macos)
API_UNAVAILABLE(tvos)
@interface INNoteContentTypeResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INNoteContentType. The resolvedValue can be different than the original INNoteContentType. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedNoteContentType:(INNoteContentType)resolvedNoteContentType NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithNoteContentTypeToConfirm:(INNoteContentType)noteContentTypeToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
