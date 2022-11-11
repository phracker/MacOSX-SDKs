#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIPreviewParameters.h>)
//
//  UIPreviewParameters.h
//  UIKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <CoreGraphics/CoreGraphics.h>
#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class UIBezierPath, UIColor;

UIKIT_EXTERN API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR
@interface UIPreviewParameters : NSObject <NSCopying>

/* The default parameters. Use these for most previews.
 */
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/* Parameters to show a preview of text.
 *
 * To clip the preview to only specific lines of text, specify one or more
 * `NSValue`s containing `CGRect`s of those lines, in the view's coordinate
 * system.
 *
 * The `visiblePath` property below will be set to a path based on the rects.
 * If `textLineRects` is empty, the whole view will be shown.
 */
- (instancetype)initWithTextLineRects:(NSArray<NSValue /* CGRect */ *> *)textLineRects;

/* The part of the view that should be shown in the preview.
 * If `nil`, the whole view will be shown.
 * Specify a path in the coordinate space of the view.
 */
@property (nonatomic, copy, nullable) UIBezierPath *visiblePath;

/* Bezier path to be used to draw the preview's shadow. If nil, the visiblePath is used.
 */
@property (nonatomic, copy, nullable) UIBezierPath *shadowPath API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, tvos);

/* The background color that the preview draws behind the specified view.
 * Set this to `nil` to reset to the default value.
 */
@property (nonatomic, copy, null_resettable) UIColor *backgroundColor;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIPreviewParameters.h>
#endif
