//
//  PKToolPickerLassoItem.h
//  PencilKit
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <PencilKit/PKToolPickerItem.h>

@class PKLassoTool;

NS_ASSUME_NONNULL_BEGIN

/// A user interface for a lasso tool item in PKToolPicker.
API_AVAILABLE(ios(18.0), visionos(2.0))
@interface PKToolPickerLassoItem : PKToolPickerItem

/// Create a new lasso tool item.
- (instancetype)init;

/// A lasso tool for selecting parts of a drawing.
@property (nonatomic, readonly) PKLassoTool *lassoTool NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
