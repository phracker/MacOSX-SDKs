#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIStackView.h>)
//
//  UIStackView.h
//  UIKit
//
//  Copyright © 2015-2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIView.h>
#import <UIKit/UIKitDefines.h>

/* Distribution—the layout along the stacking axis.
 
 All UIStackViewDistribution enum values fit first and last arranged subviews tightly to the container,
 and except for UIStackViewDistributionFillEqually, fit all items to intrinsicContentSize when possible.
 */
typedef NS_ENUM(NSInteger, UIStackViewDistribution) {
    
    /* When items do not fit (overflow) or fill (underflow) the space available
     adjustments occur according to compressionResistance or hugging
     priorities of items, or when that is ambiguous, according to arrangement
     order.
     */
    UIStackViewDistributionFill = 0,
    
    /* Items are all the same size.
     When space allows, this will be the size of the item with the largest
     intrinsicContentSize (along the axis of the stack).
     Overflow or underflow adjustments are distributed equally among the items.
     */
    UIStackViewDistributionFillEqually,
    
    /* Overflow or underflow adjustments are distributed among the items proportional
     to their intrinsicContentSizes.
     */
    UIStackViewDistributionFillProportionally,
    
    /* Additional underflow spacing is divided equally in the spaces between the items.
     Overflow squeezing is controlled by compressionResistance priorities followed by
     arrangement order.
     */
    UIStackViewDistributionEqualSpacing,
    
    /* Equal center-to-center spacing of the items is maintained as much
     as possible while still maintaining a minimum edge-to-edge spacing within the
     allowed area.
        Additional underflow spacing is divided equally in the spacing. Overflow 
     squeezing is distributed first according to compressionResistance priorities 
     of items, then according to subview order while maintaining the configured 
     (edge-to-edge) spacing as a minimum.
     */
    UIStackViewDistributionEqualCentering,
} API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(watchos);

/* Alignment—the layout transverse to the stacking axis.
 */
typedef NS_ENUM(NSInteger, UIStackViewAlignment) {
    /* Align the leading and trailing edges of vertically stacked items
     or the top and bottom edges of horizontally stacked items tightly to the container.
     */
    UIStackViewAlignmentFill,
    
    /* Align the leading edges of vertically stacked items
     or the top edges of horizontally stacked items tightly to the relevant edge
     of the container
     */
    UIStackViewAlignmentLeading,
    UIStackViewAlignmentTop = UIStackViewAlignmentLeading,
    UIStackViewAlignmentFirstBaseline, // Valid for horizontal axis only
    
    /* Center the items in a vertical stack horizontally
     or the items in a horizontal stack vertically
     */
    UIStackViewAlignmentCenter,
    
    /* Align the trailing edges of vertically stacked items
     or the bottom edges of horizontally stacked items tightly to the relevant
     edge of the container
     */
    UIStackViewAlignmentTrailing,
    UIStackViewAlignmentBottom = UIStackViewAlignmentTrailing,
    UIStackViewAlignmentLastBaseline, // Valid for horizontal axis only
} API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(watchos);

/* Used when setting custom spacing after an arranged subview to indicate reverting to 
 the value specified by the spacing property. 
 
 See -setCustomSpacing:afterView:, -customSpacingAfterView:
 */
static const CGFloat UIStackViewSpacingUseDefault API_AVAILABLE(ios(11.0), tvos(11.0)) API_UNAVAILABLE(watchos) = FLT_MAX;

/* Used when setting custom spacing after an arranged subview to request the system 
 spacing to the neighboring view. 
 
 Also used as a token for the spacing property to request system spacing between
 arranged subviews.
 
 See spacing, -setCustomSpacing:afterView:, -customSpacingAfterView:
 */
static const CGFloat UIStackViewSpacingUseSystem API_AVAILABLE(ios(11.0), tvos(11.0)) API_UNAVAILABLE(watchos) = FLT_MIN;

/* UIStackView is a non-rendering subclass of UIView, intended for managing layout of its subviews.
 You may not override +[UIStackView layerClass], and -drawLayer:inContext: will not be sent to
 UIStackView.

 UIStackView arranges its subviews in its arrangedSubviews list in the order of 
 that list along a vertical or horizontal axis, with exact arrangement determined
 by the distribution, alignment, and spacing properties.
 
 The layout will update automatically when arrangedSubviews list changes
 due to adding, removing, or inserting arrangedSubviews, and also when
 views in the arrangedSubviews list change their hidden property.
 
 A horizontal UIStackView will return its tallest view for -viewForFirst/LastBaselineLayout,
 or if that is another stack view, then the relevant viewForFirst/LastBaselineLayout from that
 stack view.
 
 A vertical UIStackView will return its first view for -viewForFirstBaselineLayout and its
 last view for -viewForLastBaselineLayout, or if that is another stack view, then the relevant  
 viewForFirst/LastBaselineLayout from that stack view.
 */
NS_HEADER_AUDIT_BEGIN(nullability, sendability)
UIKIT_EXTERN API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIStackView : UIView

- (instancetype)initWithFrame:(CGRect)frame NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

/* UIStackView enforces that all views in the arrangedSubviews list
 must be subviews of the UIStackView.
    Thus, when a view is added to the arrangedSubviews, UIStackView
 adds it as a subview if it isn't already. And when a view in a
 UIStackView's arrangedSubviews list receives -removeFromSuperview
 it is also removed from the arrangedSubviews.
 
 Please note that this is a convenience initializer and cannot be overridden in Swift.
 */
- (instancetype)initWithArrangedSubviews:(NSArray<__kindof UIView *> *)views; // Adds views as subviews of the receiver.
@property(nonatomic,readonly,copy) NSArray<__kindof UIView *> *arrangedSubviews;

/* Add a view to the end of the arrangedSubviews list.
 Maintains the rule that the arrangedSubviews list is a subset of the
 subviews list by adding the view as a subview of the receiver if
 necessary.
    Does not affect the subview ordering if view is already a subview 
 of the receiver.
 */
- (void)addArrangedSubview:(UIView *)view;

/* Removes a subview from the list of arranged subviews without removing it as
 a subview of the receiver.
    To remove the view as a subview, send it -removeFromSuperview as usual;
 the relevant UIStackView will remove it from its arrangedSubviews list
 automatically.
 */
- (void)removeArrangedSubview:(UIView *)view;
/*
 Adds the view as a subview of the container if it isn't already.
    Updates the stack index (but not the subview index) of the
 arranged subview if it's already in the arrangedSubviews list.
 */
- (void)insertArrangedSubview:(UIView *)view atIndex:(NSUInteger)stackIndex;

/* A stack with a horizontal axis is a row of arrangedSubviews,
and a stack with a vertical axis is a column of arrangedSubviews.
 */
@property(nonatomic) UILayoutConstraintAxis axis;

/* The layout of the arrangedSubviews along the axis
 */
@property(nonatomic) UIStackViewDistribution distribution;

/* The layout of the arrangedSubviews transverse to the axis;
 e.g., leading/trailing edges in a vertical stack
 */
@property(nonatomic) UIStackViewAlignment alignment;

/* Spacing between adjacent edges of arrangedSubviews.
 Used as a strict spacing for the Fill distributions, and
 as a minimum spacing for the EqualCentering and EqualSpacing
 distributions. Use negative values to allow overlap.
 
 On iOS 11.0 or later, use UIStackViewSpacingUseSystem (Swift: UIStackView.spacingUseSystem) 
 to get a system standard spacing value. Setting spacing to UIStackViewSpacingUseDefault 
 (Swift: UIStackView.spacingUseDefault) will result in a spacing of 0.
 
 System spacing between views depends on the views involved, and may vary across the 
 stack view.
 
 In vertical stack views with baselineRelativeArrangement == YES, the spacing between 
 text-containing views (such as UILabels) will depend on the fonts involved.
 */
@property(nonatomic) CGFloat spacing;

/* Set and get custom spacing after a view. 
 
 This custom spacing takes precedence over any other value that might otherwise be used 
 for the space following the arranged subview.
 
 Defaults to UIStackViewSpacingUseDefault (Swift: UIStackView.spacingUseDefault), where 
 resolved value will match the spacing property.
 
 You may also set the custom spacing to UIStackViewSpacingUseSystem (Swift: UIStackView.spacingUseSystem),
 where the resolved value will match the system-defined value for the space to the neighboring view, 
 independent of the spacing property.
 
 Maintained when the arranged subview changes position in the stack view, but not after it
 is removed from the arrangedSubviews list.
 
 Ignored if arrangedSubview is not actually an arranged subview.
 */
- (void)setCustomSpacing:(CGFloat)spacing afterView:(UIView *)arrangedSubview API_AVAILABLE(ios(11.0), tvos(11.0)) API_UNAVAILABLE(watchos);
- (CGFloat)customSpacingAfterView:(UIView *)arrangedSubview API_AVAILABLE(ios(11.0), tvos(11.0)) API_UNAVAILABLE(watchos);

/* Baseline-to-baseline spacing in vertical stacks.
    The baselineRelativeArrangement property supports specifications of vertical 
 space from the last baseline of one text-based view to the first baseline of a
 text-based view below, or from the  top (or bottom) of a container to the first
 (or last) baseline of a contained text-based view.
    This property is ignored in horizontal stacks. Use the alignment property
 to specify baseline alignment in horizontal stacks.
    Defaults to NO.
 */
@property(nonatomic,getter=isBaselineRelativeArrangement) BOOL baselineRelativeArrangement;

/* Uses margin layout attributes for edge constraints where applicable.
    Defaults to NO.
 */
@property(nonatomic,getter=isLayoutMarginsRelativeArrangement) BOOL layoutMarginsRelativeArrangement;    

@end
NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIStackView.h>
#endif
