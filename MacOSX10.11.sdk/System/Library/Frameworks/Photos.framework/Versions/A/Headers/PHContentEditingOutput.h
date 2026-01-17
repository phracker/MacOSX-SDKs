//
//  PHContentEditingOutput.h
//  Photos
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class PHContentEditingInput, PHAdjustmentData;

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE_MAC(10_11) @interface PHContentEditingOutput : NSObject

- (instancetype)initWithContentEditingInput:(PHContentEditingInput *)contentEditingInput;

@property (readwrite, strong) PHAdjustmentData *adjustmentData;

// File URL where the rendered output, with adjustments baked-in, needs to be written to.
@property (readonly, copy) NSURL *renderedContentURL;

@end

NS_ASSUME_NONNULL_END