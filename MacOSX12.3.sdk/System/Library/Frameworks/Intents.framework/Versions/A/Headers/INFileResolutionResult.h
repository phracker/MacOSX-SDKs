//
//  INFileResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

@class INFile;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), macos(11.0), watchos(6.0))
API_UNAVAILABLE(tvos)
@interface INFileResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INFile. The resolvedFile can be different than the original INFile. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedFile:(INFile *)resolvedFile NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to disambiguate between the provided INFile.
+ (instancetype)disambiguationWithFilesToDisambiguate:(NSArray<INFile *> *)filesToDisambiguate NS_SWIFT_NAME(disambiguation(with:));

// This resolution result is to ask Siri to confirm if this is the file with which the user wants to continue.
+ (instancetype)confirmationRequiredWithFileToConfirm:(nullable INFile *)fileToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END
