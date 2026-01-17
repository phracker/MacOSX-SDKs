//
//  PKToolPickerItem.h
//  PencilKit
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class PKTool;

/// A user interface for a tool item in PKToolPicker.
API_AVAILABLE(ios(18.0), visionos(2.0), macos(26.0))
@interface PKToolPickerItem : NSObject <NSCopying>
 
- (instancetype)init NS_UNAVAILABLE;

/// A string that identifies the item in the picker.
/// For example, com.example.myapp.toolpicker.pencil.
/// If multiple items with the same identifier are used to create the picker, only the first instance is used.
@property (nonatomic, readonly) NSString *identifier;

/// The `PKTool` this tool picker item represents.
@property (nonatomic, nullable, readonly) PKTool *tool API_AVAILABLE(ios(26.0), visionos(26.0)) NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
