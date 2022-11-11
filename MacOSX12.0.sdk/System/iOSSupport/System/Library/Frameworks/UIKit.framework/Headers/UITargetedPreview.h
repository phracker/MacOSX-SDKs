#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UITargetedPreview.h>)
//
//  UITargetedPreview.h
//  UIKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <CoreGraphics/CoreGraphics.h>
#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class UIPreviewParameters, UIView;

UIKIT_EXTERN API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR
@interface UIPreviewTarget : NSObject <NSCopying>

/* UIPreviewTarget specifies where a preview should come from, or go to.
 *
 * `container` must be a view that is currently in a window.
 * `center` specifies where the center of the preview should go,
 * in `container`'s coordinate system.
 * `transform` is an additional transform to apply to the preview,
 * for special effects like rotating or scaling the preview.
 * Use CGAffineTransformIdentity if you only want the preview to move.
 */
- (instancetype)initWithContainer:(UIView *)container center:(CGPoint)center transform:(CGAffineTransform)transform NS_DESIGNATED_INITIALIZER;

/* As above, but with transform = CGAffineTransformIdentity.
 */
- (instancetype)initWithContainer:(UIView *)container center:(CGPoint)center;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (nonatomic, readonly) UIView *container;
@property (nonatomic, readonly) CGPoint center;
@property (nonatomic, readonly) CGAffineTransform transform;

@end

UIKIT_EXTERN API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR
@interface UITargetedPreview : NSObject <NSCopying>

/* UITargetedPreview is a preview used during an interaction's animations.
 *
 * The preview will show the view, including all subviews, live. 
 * The UITargetedPreview will not change or move the view.
 */

/* To use this initializer, the view need not be in a window.
 */
- (instancetype)initWithView:(UIView *)view parameters:(__kindof UIPreviewParameters *)parameters target:(__kindof UIPreviewTarget *)target NS_DESIGNATED_INITIALIZER;

/* To use this initializer, the view must be in a window.
 * Sets the target based on the view's current superview, center, and transform.
 */
- (instancetype)initWithView:(UIView *)view parameters:(__kindof UIPreviewParameters *)parameters;

/* To use this initializer, the view must be in a window.
 * Sets the parameters to defaults.
 * Sets the target based on the view's current superview, center, and transform.
 */
- (instancetype)initWithView:(UIView *)view;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (nonatomic, readonly) __kindof UIPreviewTarget *target;

@property (nonatomic, readonly) UIView *view;

@property (nonatomic, readonly, copy) __kindof UIPreviewParameters *parameters;

/* Provide the size of the item.
 * You might use this size to create an appropriately-sized gap in your view,
 * where this item will land when it is dropped.
 */
@property (nonatomic, readonly) CGSize size;

/* Returns a preview with the same view and parameters, but a new target.
 *
 * You might call this in a UIDropInteractionDelegate in
 * -dropInteraction:previewForDroppingItem:withDefault:, or in
 * a UIDropInteractionDelegate in -dropInteraction:previewForCancellingItem:withDefault:,
 * to direct the default UITargetedPreview to a different target.
 */
- (__kindof UITargetedPreview *)retargetedPreviewWithTarget:(__kindof UIPreviewTarget *)newTarget;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UITargetedPreview.h>
#endif
