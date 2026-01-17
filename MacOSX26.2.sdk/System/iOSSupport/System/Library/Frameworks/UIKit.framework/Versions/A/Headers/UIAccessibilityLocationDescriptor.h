#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIAccessibilityLocationDescriptor.h>)
//
//  UIAccessibilityLocationDescriptor.h
//  UIKit
//
//  Copyright (c) 2017-2018 Apple Inc. All rights reserved.
//


#import <UIKit/UIKitDefines.h>
#import <UIKit/UIView.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/*
 * UIAccessibilityLocationDescriptor objects are used to describe to assistive
 * technologies points of interest within a view; where they are and how an assistive technology
 * should describe them. For example, the `accessibilityDragSourceDescriptors` and
 * `accessibilityDropPointDescriptors` properties in the UIAccessibilityDragging informal protocol
 * use UIAccessibilityLocationDescriptor objects to describe where drags may begin and end.
 */
UIKIT_EXTERN API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR
@interface UIAccessibilityLocationDescriptor : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/* Convenience initializer that uses the view's accessibilityActivationPoint. (This point will be
 * converted to the coordinate space of the view).
 *
 * Note that by default, the accessibilityActivationPoint of a view is its center.
 */
- (instancetype)initWithName:(NSString *)name view:(UIView *)view;

/* Provide the view, the point in that view's coordinate space that is of interest, and a name to
 * use to describe it to the user.
 */
- (instancetype)initWithName:(NSString *)name point:(CGPoint)point inView:(UIView *)view;
- (instancetype)initWithAttributedName:(NSAttributedString *)attributedName point:(CGPoint)point inView:(UIView *)view NS_DESIGNATED_INITIALIZER;

/* The view in which the described point resides.
 *
 * This property is weak to make it simple to avoid reference cycles. Descriptors whose views have
 * been deallocated (or are no longer in a visible window, or are obscured) will be silently
 * ignored. That said, you should still clean up after yourself.
 */
@property (nonatomic, readonly, weak) UIView *view;

/* The point in the view that is being described. The point is in the view's coordinate space.
 */
@property (nonatomic, readonly) CGPoint point;

/* The "name" property and initializer are conveniences for referring to the "attributedName"
 * property, which is the real underlying property.
 */
@property (nonatomic, readonly, strong) NSString *name;

/* Assistive technologies will use the attributedName of the descriptor when describing it to the
 * user (for instance, VoiceOver will speak it).
 */
@property (nonatomic, readonly, strong) NSAttributedString *attributedName;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIAccessibilityLocationDescriptor.h>
#endif
