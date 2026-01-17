//
//  PHContentEditingOutput.h
//  Photos
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class PHContentEditingInput, PHAdjustmentData, UTType;

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE_BEGIN(macos(10.11), ios(8), tvos(10))

OS_EXPORT
@interface PHContentEditingOutput : NSObject

- (instancetype)initWithContentEditingInput:(PHContentEditingInput *)contentEditingInput;

@property (readwrite, strong, nullable) PHAdjustmentData *adjustmentData;

/// File URL where the rendered output in the default format, with adjustments baked-in, needs to be written to.
@property (readonly, copy) NSURL *renderedContentURL;

/// Returns the default type for the rendered content output
@property (readonly, copy, nullable) UTType *defaultRenderedContentType API_AVAILABLE(macos(14), ios(17), tvos(17));

/// Returns the supported types for the rendered content output
@property (readonly, copy) NSArray<UTType *> *supportedRenderedContentTypes API_AVAILABLE(macos(14), ios(17), tvos(17));

/// Returns a file URL where the rendered output in the specified format, with adjustments baked-in, needs to be written to. Returns nil and provides an error identifying the reason if the format is unsupported or the requested content URL cannot be provided
- (nullable NSURL *)renderedContentURLForType:(UTType *)type error:(NSError * __autoreleasing *)error API_AVAILABLE(macos(14), ios(17), tvos(17));

@end

API_AVAILABLE_END
NS_ASSUME_NONNULL_END
