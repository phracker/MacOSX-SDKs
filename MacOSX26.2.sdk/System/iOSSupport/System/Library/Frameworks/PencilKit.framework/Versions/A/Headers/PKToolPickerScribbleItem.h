//
//  PKToolPickerScribbleItem.h
//  PencilKit
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <PencilKit/PKToolPickerItem.h>

NS_ASSUME_NONNULL_BEGIN

/// A user interface for a Scribble tool item in PKToolPicker.
API_AVAILABLE(ios(18.0)) API_UNAVAILABLE(visionos)
@interface PKToolPickerScribbleItem : PKToolPickerItem

/// Create a new Scribble tool item.
- (instancetype)init;

@end

NS_ASSUME_NONNULL_END
