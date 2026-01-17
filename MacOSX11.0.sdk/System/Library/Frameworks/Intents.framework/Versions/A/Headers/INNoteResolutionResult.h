//
//  INNoteResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

@class INNote;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macos, tvos)
@interface INNoteResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INNote. The resolvedNote can be different than the original INNote. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedNote:(INNote *)resolvedNote NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to disambiguate between the provided INNote.
+ (instancetype)disambiguationWithNotesToDisambiguate:(NSArray<INNote *> *)notesToDisambiguate NS_SWIFT_NAME(disambiguation(with:));

// This resolution result is to ask Siri to confirm if this is the note with which the user wants to continue.
+ (instancetype)confirmationRequiredWithNoteToConfirm:(nullable INNote *)noteToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
