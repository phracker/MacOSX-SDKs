#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UISheetPresentationController.h>)
//
//  UISheetPresentationController.h
//  UIKit
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <UIKit/UIPresentationController.h>
#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class UISheetPresentationController, UIVisualEffect;


typedef NSString *UISheetPresentationControllerDetentIdentifier NS_TYPED_EXTENSIBLE_ENUM API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(tvos, watchos, visionos);

// The identifier for the system medium detent.
UIKIT_EXTERN const UISheetPresentationControllerDetentIdentifier UISheetPresentationControllerDetentIdentifierMedium API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(tvos, watchos, visionos);

// The identifier for the system large detent.
UIKIT_EXTERN const UISheetPresentationControllerDetentIdentifier UISheetPresentationControllerDetentIdentifierLarge API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(tvos, watchos, visionos);


// A sentinel value indicating a detent that is inactive.
UIKIT_EXTERN API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos, watchos, visionos)
const CGFloat UISheetPresentationControllerDetentInactive;


// A context used for resolving custom UISheetPresentationControllerDetent values.
UIKIT_EXTERN API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos, watchos, visionos) NS_SWIFT_UI_ACTOR
@protocol UISheetPresentationControllerDetentResolutionContext <NSObject>

// The trait collection of the sheet's containerView. Effectively the same as the window's traitCollection, and does not include overrides from the sheet's overrideTraitCollection.
@property (nonatomic, readonly) UITraitCollection *containerTraitCollection;

// The maximum value a detent can have.
@property (nonatomic, readonly) CGFloat maximumDetentValue;

@end


UIKIT_EXTERN API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(tvos, watchos, visionos) NS_SWIFT_UI_ACTOR
@interface UISheetPresentationControllerDetent : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

// A system detent for a sheet that is approximately half the height of the screen, and is inactive in compact height.
+ (instancetype)mediumDetent;

// A system detent for a sheet at full height.
+ (instancetype)largeDetent;

// A custom detent that may compute a value based on the properties of the passed in context.
// If the detent needs to be referred to from other API on the sheet, such as `selectedDetentIdentifier`, specify an identifier for the detent.
// The identifier of each custom detent used by a sheet should be unique.
// If no identifier is specified, a random one will be generated.
// The value returned from the resolutionContextBlock is a height within the safe area of the sheet. For example, returning 200 will result in a detent where the height of the sheet is 200 + safeAreaInsets.bottom when edge-attached, and just 200 when floating. Return nil if the detent should be inactive based on the passed in context.
// If the block depends on any external inputs, call `invalidateDetents` on the sheet when the external inputs change.
// Do not set any properties on UISheetPresentationController during the execution of this block.
+ (instancetype)customDetentWithIdentifier:(nullable UISheetPresentationControllerDetentIdentifier)identifier resolver:(CGFloat (^)(id<UISheetPresentationControllerDetentResolutionContext> context))resolver API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos, watchos, visionos);

// The identifier of this detent.
@property (nonatomic, strong, readonly) UISheetPresentationControllerDetentIdentifier identifier API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos, watchos, visionos);

// Set the background effect for this detent. Set to nil to use default background. Default is nil.
@property (nonatomic, strong, nullable) UIVisualEffect *backgroundEffect API_AVAILABLE(ios(26.1)) API_UNAVAILABLE(macCatalyst, watchos, tvos, visionos, macos);

// Resolves a detent to its value. Returns UISheetPresentationControllerDetentInactive if the detent is inactive in the provided context.
// This may be used to get the values of the system medium and large detents, or the value of a custom detent.
// This is intended to be used inside `customDetentWithIdentifier:resolver:` as a way to construct a custom detent based on the values of known detents.
- (CGFloat)resolvedValueInContext:(id<UISheetPresentationControllerDetentResolutionContext>)context API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos, watchos, visionos);

@end


UIKIT_EXTERN API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(tvos, watchos)
const CGFloat UISheetPresentationControllerAutomaticDimension;


UIKIT_EXTERN API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(tvos, watchos) NS_SWIFT_UI_ACTOR
@protocol UISheetPresentationControllerDelegate <UIAdaptivePresentationControllerDelegate>

@optional

// Called when the selected detent of the sheet changes in response to user interaction.
// Not called if selectedDetentIdentifier is programmatically set.
- (void)sheetPresentationControllerDidChangeSelectedDetentIdentifier:(UISheetPresentationController *)sheetPresentationController API_UNAVAILABLE(visionos);

@end


UIKIT_EXTERN API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(tvos, watchos) NS_SWIFT_UI_ACTOR
@interface UISheetPresentationController : UIPresentationController

// The delegate inherited from UIPresentationController, redeclared with conformance to UISheetPresentationControllerDelegate.
@property (nonatomic, weak, nullable) id<UISheetPresentationControllerDelegate> delegate;

// If specified, the sheet will attempt to visually center itself over this view.
// Default: nil
@property (nonatomic, strong, nullable) UIView *sourceView;

// Whether the sheet sizes itself for readable content.
// When YES, this maps to the behavior of UIModalPresentationPageSheet, where the sheet width follows the readable width.
// When NO, this maps to the behavior of UIModalPresentationFormSheet, where the sheet size follows the presented view controller's `preferredContentSize`.
// Default: NO on iOS 18.0 and later, YES on earlier releases
@property (nonatomic) BOOL prefersPageSizing API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(tvos, watchos);

// Set to YES to cause the sheet to layout with an edge-attached appearance in compact height instead of full screen.
// Default: NO
@property (nonatomic) BOOL prefersEdgeAttachedInCompactHeight;

// Set to YES to allow preferredContentSize to influence the width of the sheet when edge-attached.
// When NO, the width of the sheet when edge-attached is always equal to the safe area width of the container.
// The value of this property is not respected in compact width regular height.
// Default: NO
@property (nonatomic) BOOL widthFollowsPreferredContentSizeWhenEdgeAttached;

// Set to YES to show a grabber at the top of the sheet.
// Default: NO
@property (nonatomic) BOOL prefersGrabberVisible API_UNAVAILABLE(visionos);

// The preferred corner radius of the sheet when presented.
// This value is only respected when the sheet is at the front of its stack.
// Default: UISheetPresentationControllerAutomaticDimension
@property (nonatomic) CGFloat preferredCornerRadius API_UNAVAILABLE(visionos);

// The array of detents that the sheet may rest at.
// This array must have at least one element.
// Detents must be specified in order from smallest to largest height.
// Default: an array of only [UISheetPresentationControllerDetent largeDetent]
@property (nonatomic, copy) NSArray<UISheetPresentationControllerDetent *> *detents API_UNAVAILABLE(visionos);

// If an external input (e.g. a captured property) to a custom detent changes, call this to notify the sheet to re-evaluate the detent in the next layout pass.
// There is no need to call this if `detents` only contains system detents, or if custom detents only use information from the passed in context.
// Call within an `animateChanges:` block to animate custom detents to their new heights.
- (void)invalidateDetents API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos, watchos, visionos);

// The identifier of the selected detent. When nil or the identifier is not found in detents, the sheet is displayed at the smallest detent.
// Default: nil
@property (nonatomic, copy, nullable) UISheetPresentationControllerDetentIdentifier selectedDetentIdentifier API_UNAVAILABLE(visionos);

// The identifier of the largest detent that is not dimmed. When nil or the identifier is not found in detents, all detents are dimmed.
// Default: nil
@property (nonatomic, copy, nullable) UISheetPresentationControllerDetentIdentifier largestUndimmedDetentIdentifier API_UNAVAILABLE(visionos);

// If there is a larger detent to expand to than the selected detent, and a descendent scroll view is scrolled to top, this controls whether scrolling down will expand to a larger detent.
// Useful to set to NO for non-modal sheets, where scrolling in the sheet should not expand the sheet and obscure the content above.
// Default: YES
@property (nonatomic) BOOL prefersScrollingExpandsWhenScrolledToEdge API_UNAVAILABLE(visionos);

// To animate changing any of the above properties, set them inside a block passed to this method.
// By the time this method returns, the receiver and all adjacent sheets in the sheet stack and their subviews will have been laid out.
- (void)animateChanges:(void (NS_NOESCAPE ^)(void))changes;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UISheetPresentationController.h>
#endif
