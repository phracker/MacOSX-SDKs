//
//  INNoteContentResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

@class INNoteContent;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macos, tvos)
@interface INNoteContentResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INNoteContent. The resolvedNoteContent can be different than the original INNoteContent. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedNoteContent:(INNoteContent *)resolvedNoteContent NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to disambiguate between the provided INNoteContent.
+ (instancetype)disambiguationWithNoteContentsToDisambiguate:(NSArray<INNoteContent *> *)noteContentsToDisambiguate NS_SWIFT_NAME(disambiguation(with:));

// This resolution result is to ask Siri to confirm if this is the noteContent with which the user wants to continue.
+ (instancetype)confirmationRequiredWithNoteContentToConfirm:(nullable INNoteContent *)noteContentToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
