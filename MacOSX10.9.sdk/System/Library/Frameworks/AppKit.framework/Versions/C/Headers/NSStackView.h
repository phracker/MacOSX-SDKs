/*
 NSStackView.h
 Application Kit
 Copyright (c) 2012-2013, Apple Inc.
 All rights reserved.
 */

#import <AppKit/NSApplication.h>
#import <AppKit/NSLayoutConstraint.h>
#import <AppKit/NSView.h>

@class NSArray, NSView;
@protocol NSStackViewDelegate;

/*
 NSUserInterfaceLayoutOrientation describes the orientation of the StackView layout.
 The direction within that orientation can be determined and set with userInterfaceLayoutDirection
 
 See also:
 - orientation
 - [NSView userInterfaceLayoutDirection]
 */
typedef NS_ENUM(NSInteger, NSUserInterfaceLayoutOrientation) {
    NSUserInterfaceLayoutOrientationHorizontal = 0, // Arranges objects horizontally. This could be R2L or L2R as determined by -userInterfaceLayoutDirection
    NSUserInterfaceLayoutOrientationVertical = 1 // Arranges objects vertically. This is always top to bottom.
} NS_ENUM_AVAILABLE_MAC(10_9);

/*
 The gravity area describes the area within a StackView that a view will be placed.
 This placement is also highly related to the set orientation and layoutDirection.
 
 Gravity areas will align to a specific direction in the StackView, which are described through these enum values.
 Each gravity area is a distinct portion of the StackView, and the constraints for spacing between gravities is described further in the documentation for the spacing property.
 In addition to the gravity spacing constraints, the center gravity area also has a constraint tying it to the center of the StackView with a layout priority of NSLayoutPriorityDefaultLow.
 
 For horizontally-oriented StackViews, NSStackViewGravityLeading, NSStackViewGravityCenter, and NSStackViewGravityTrailing should be used. Leading and trailing are described by the userInterfaceLayoutDirection of the StackView, (leading = left for NSUserInterfaceLayoutDirectionLeftToRight vs leading = right for NSUserInterfaceLayoutDirectionRightToLeft).
 
 For a vertically-oriented StackView, NSStackViewGravityTop, NSStackViewGravityCenter, and NSStackViewGravityBottom should be used.
 
 See also:
 - insertView:atIndex:inGravity:
 - viewsInGravity:
 - setViews:inGravity:
 - NSUserInterfaceLayoutOrientation
 - NSUserInterfaceLayoutDirection
 */
typedef NS_ENUM(NSInteger, NSStackViewGravity) {
    NSStackViewGravityTop = 1, // The top-most gravity area, should only be used when orientation = NSUserInterfaceLayoutOrientationVertical
    NSStackViewGravityLeading = 1, // The leading gravity area (as described by userInterfaceLayoutDirection), should only be used when orientation = NSUserInterfaceLayoutOrientationHorizontal
    NSStackViewGravityCenter = 2, // The center gravity area, this is the center regardless of orientation
    NSStackViewGravityBottom = 3, // The bottom-most gravity area, should only be used when orientation = NSUserInterfaceLayoutOrientationVertical
    NSStackViewGravityTrailing = 3 // The trailing gravity area (as described by userInterfaceLayoutDirection), should only be used when orientation = NSUserInterfaceLayoutOrientationHorizontal
} NS_ENUM_AVAILABLE_MAC(10_9);

/*
 Visibility Priority describes the priority at which a view should be held (aka, not be detached).
 In the case that clippingResistancePriority is optional (< NSLayoutPriorityRequired) and there's not enough space to display all of StackView's subviews, views are able to be detached from the StackView.
 Views will be detached in order (from lowest to highest) of their visibility priority, and reattached in the reverse order (FILO).
 If multiple views share the lowest visibility priority, all those views will be dropped when one needs to be. Likewise, groups of views with equal visibility priorities will wait to be reattached until they can all be readded.
 
 A view with a higher visibility priority will never be detached while a lower priority view remains visible
 
 See also:
 - visibilityPriorityForView:
 - setVisibilityPriority:ForView:
 - clippingResistancePriority
 - detachedViews
 */
enum {
    NSStackViewVisibilityPriorityMustHold = 1000, //Maximum, default - the view will never be detached
    NSStackViewVisibilityPriorityDetachOnlyIfNecessary = 900,
    NSStackViewVisibilityPriorityNotVisible = 0 //Minimum - will force a view to be detached
} NS_ENUM_AVAILABLE_MAC(10_9);
typedef float NSStackViewVisibilityPriority NS_AVAILABLE_MAC(10_9);

#pragma mark - NSStackViewLayout
NS_CLASS_AVAILABLE(10_9, NA)
@interface NSStackView : NSView {
@private
    id<NSStackViewDelegate> _delegate;
    
    NSUserInterfaceLayoutOrientation _orientation;
    NSLayoutAttribute _alignment;
    NSEdgeInsets _edgeInsets;
    CGFloat _spacing;
    
    NSLayoutPriority _verticalClippingResistancePriority;
    NSLayoutPriority _horizontalClippingResistancePriority;
    NSLayoutPriority _verticalHuggingPriority;
    NSLayoutPriority _horizontalHuggingPriority;
    
    BOOL _hasEqualSpacing;
    
    id _animator;
    NSDictionary *_animationsDictionary;
    
    id _private;
    
    struct {
        unsigned int _inDealloc:1;
        unsigned int _reserved:31;
    } _flags;
}

+ (id) stackViewWithViews:(NSArray *)views; // Returns an autoreleased horizontal StackView with the provided views set as the leading views, and has translatesAutoresizingMaskIntoConstraints set to NO.

#pragma mark General StackView Properties

@property (assign) id<NSStackViewDelegate> delegate;
@property NSUserInterfaceLayoutOrientation orientation; // Orientation of the StackView, defaults to NSUserInterfaceLayoutOrientationHorizontal
@property NSLayoutAttribute alignment; // Describes how subviews are aligned within the StackView, defaults to NSLayoutAttributeCenterY for horizontal stacks, NSLayoutAttributeCenterX for vertical stacks. Setting NSLayoutAttributeNotAnAttribute will cause the internal alignment constraints to not be created, and could result in an ambiguous layout. Setting an inapplicable attribute for the set orientation will result in the alignment being ignored (similar to its handling with NSLayoutAttributeNotAnAttribute). The alignment constraints are established at a priority of NSStackViewVisibilityPriorityDefaultLow and is therefore overridable on an individual view basis.
@property NSEdgeInsets edgeInsets; // Default padding inside the StackView, around all of the subviews. Edge insets do not flip or rotate for changes to orientation or R2L languages.


#pragma mark Managing Views

/*
 Adds the view to the given gravity area at the end of that gravity area.
 This method will update the StackView's layout, and could result in the StackView changing its size or views being detached / clipped.
 */
- (void)addView:(NSView *)aView inGravity:(NSStackViewGravity)gravity;
/*
 Adds the view to the given gravity area at the index within that gravity area.
 Index numbers & counts are specific to each gravity area, and are indexed based on the set userInterfaceLayoutDirection.
 (For a L2R layout, index 0 in the leading gravity is the furthest left index; for a R2L layout index 0 in the leading gravity is the furthest right index)
 This method will update the StackView's layout, and could result in the StackView changing its size or views being detached / clipped.
 An NSRangeException will be raised if the index is out of bounds
 */
- (void)insertView:(NSView *)aView atIndex:(NSUInteger)index inGravity:(NSStackViewGravity)gravity;
/*
 Will remove aView from the StackView.
 [aView removeFromSuperview] will have the same behavior in the case that aView is visible (not detached) from the StackView.
 In the case that aView had been detached, this method must be used to remove it from the StackView.
 aView must be managed by the StackView, an exception will be raised if not.
 */
- (void)removeView:(NSView *)aView;

- (NSArray *)viewsInGravity:(NSStackViewGravity)gravity; // Getters will return the views that are contained by the corresponding gravity area, regardless of detach-status.
- (void)setViews:(NSArray *)views inGravity:(NSStackViewGravity)gravity; // Setters will update the views and the layout for that gravity area.

/*
 Returns an array of all the views managed by this StackView, regardless of detach-status or gravity area.
 This is indexed in the order of indexing within the StackView. Detached views are indexed at the positions they would have been if they were still attached.
 */
@property (readonly) NSArray *views;
@property (readonly) NSArray *detachedViews; // Returns the list of all of the detached views, regardless of gravity area

/*
 Sets and gets the visibility priorities for views in the StackView.
 When detaching a view, it will first detach views with the lowest visibility priority.
 If multiple views share the same lowest visibility priority, all of them will be dropped.

 Defaults to NSStackViewVisibilityPriorityMustHold.
 Setting the visibility priority to NSStackViewVisibilityPriorityNotVisible will force that view to be detached (regardless of available space).
 
 aView must be managed by the StackView, an exception will be raised if not.
 */
- (void)setVisibilityPriority:(NSStackViewVisibilityPriority)priority forView:(NSView *)aView;
- (NSStackViewVisibilityPriority)visibilityPriorityForView:(NSView *)aView;


#pragma mark Spacing & Layout

/*
 Spacing within a StackView is managed completely by the StackView.
 However, extra layout constraints can be added in conjunction with the StackView to create a more customized layout.
 Below describes the constraints the StackView uses to space its internal views.
 Spacing between view gravities have constraints with the following constraints:
 - Length >= spacing @ NSLayoutPriorityRequired
 - Length == spacing @ huggingPriority
 Spacing between views (within a gravity) have the following constraints:
 - Length >= spacing @ NSLayoutPriorityRequired
 - Length == spacing @ MAX(NSLayoutPriorityDefaultHigh, huggingPriority)
 */
@property CGFloat spacing; // Default (minimum) spacing between each view

/*
 Set and get custom spacing after a view. This custom spacing is used instead of the default spacing set with the spacing property.
 This is saved across layout updates, until the view is removed from the StackView or the custom spacing is changed.
 A value of NSStackViewSpacingUseDefault signifies that the spacing is the default spacing set with the StackView property.
 aView must be managed by the StackView, an exception will be raised if not.
 */
#define NSStackViewSpacingUseDefault (FLT_MAX)
- (void)setCustomSpacing:(CGFloat)spacing afterView:(NSView *)aView;
- (CGFloat)customSpacingAfterView:(NSView *)aView;

/*
 Property describing whether or not all spacing between views should be equivalent. Defaults to NO.
 If set to YES, this modifies the constraints used internally for spacing in such manners:
 - All spacing is >= spacing @ NSLayoutPriorityRequired
 - All spacing is == spacing @ huggingPriority
 - All spacing is == each other @ NSLayoutPriorityDefaultLow
 - Custom spacing is ignored. StackView's spacing property is used as the minimum spacing between each view
 */
@property BOOL hasEqualSpacing;

/*
 Priority at which the StackView will not clip its views, defaults to NSLayoutPriorityRequired
 Clipping begins from the right and bottom sides of the StackView.
 */
- (NSLayoutPriority)clippingResistancePriorityForOrientation:(NSLayoutConstraintOrientation)orientation;
- (void)setClippingResistancePriority:(NSLayoutPriority)clippingResistancePriority forOrientation:(NSLayoutConstraintOrientation)orientation;

// Priority at which the StackView wants its internal spacing to be as small as possible, defaults to NSLayoutPriorityDefaultLow
- (NSLayoutPriority)huggingPriorityForOrientation:(NSLayoutConstraintOrientation)orientation;
- (void)setHuggingPriority:(NSLayoutPriority)huggingPriority forOrientation:(NSLayoutConstraintOrientation)orientation;

@end

#pragma mark - NSStackViewDelegate
@protocol NSStackViewDelegate <NSObject>
@optional
/*
 These are called when the StackView detaches or readds a view (or multiple views) after it was detached.
 This is not called when a view is explicitly added or removed from the StackView
 */
- (void)stackView:(NSStackView *)stackView willDetachViews:(NSArray *)views;
- (void)stackView:(NSStackView *)stackView didReattachViews:(NSArray *)views;

@end
