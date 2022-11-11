#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UISheetPresentationController.h>)
//
//  UISheetPresentationController.h
//  UIKit
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <UIKit/UIPresentationController.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class UISheetPresentationController;


typedef NSString *UISheetPresentationControllerDetentIdentifier NS_TYPED_EXTENSIBLE_ENUM API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(tvos, watchos);

// The identifier for the system medium detent.
UIKIT_EXTERN const UISheetPresentationControllerDetentIdentifier UISheetPresentationControllerDetentIdentifierMedium API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(tvos, watchos);

// The identifier for the system large detent.
UIKIT_EXTERN const UISheetPresentationControllerDetentIdentifier UISheetPresentationControllerDetentIdentifierLarge API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(tvos, watchos);


UIKIT_EXTERN API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(tvos, watchos) NS_SWIFT_UI_ACTOR
@interface UISheetPresentationControllerDetent : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

// A system detent for a sheet that is approximately half the height of the screen, and is inactive in compact height.
+ (instancetype)mediumDetent;

// A system detent for a sheet at full height.
+ (instancetype)largeDetent;

@end


UIKIT_EXTERN API_AVAILABLE(ios(15.0)) API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(tvos, watchos)
const CGFloat UISheetPresentationControllerAutomaticDimension;


UIKIT_EXTERN API_AVAILABLE(ios(15.0)) API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(tvos, watchos) NS_SWIFT_UI_ACTOR
@protocol UISheetPresentationControllerDelegate <UIAdaptivePresentationControllerDelegate>

@optional

// Called when the selected detent of the sheet changes in response to user interaction.
// Not called if selectedDetentIdentifier is programmatically set.
- (void)sheetPresentationControllerDidChangeSelectedDetentIdentifier:(UISheetPresentationController *)sheetPresentationController;

@end


UIKIT_EXTERN API_AVAILABLE(ios(15.0)) API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(tvos, watchos) NS_SWIFT_UI_ACTOR
@interface UISheetPresentationController : UIPresentationController

// The delegate inherited from UIPresentationController, redeclared with conformance to UISheetPresentationControllerDelegate.
@property (nonatomic, weak, nullable) id<UISheetPresentationControllerDelegate> delegate;

// If specified, the sheet will attempt to visually center itself over this view.
// Default: nil
@property (nonatomic, strong, nullable) UIView *sourceView;

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
@property (nonatomic) BOOL prefersGrabberVisible;

// The preferred corner radius of the sheet when presented.
// This value is only respected when the sheet is at the front of its stack.
// Default: UISheetPresentationControllerAutomaticDimension
@property (nonatomic) CGFloat preferredCornerRadius;

// The array of detents that the sheet may rest at.
// This array must have at least one element.
// Detents must be specified in order from smallest to largest height.
// Default: an array of only [UISheetPresentationControllerDetent largeDetent]
@property (nonatomic, copy) NSArray<UISheetPresentationControllerDetent *> *detents;

// The identifier of the selected detent. When nil or the identifier is not found in detents, the sheet is displayed at the smallest detent.
// Default: nil
@property (nonatomic, copy, nullable) UISheetPresentationControllerDetentIdentifier selectedDetentIdentifier;

// The identifier of the largest detent that is not dimmed. When nil or the identifier is not found in detents, all detents are dimmed.
// Default: nil
@property (nonatomic, copy, nullable) UISheetPresentationControllerDetentIdentifier largestUndimmedDetentIdentifier;

// If there is a larger detent to expand to than the selected detent, and a descendent scroll view is scrolled to top, this controls whether scrolling down will expand to a larger detent.
// Useful to set to NO for non-modal sheets, where scrolling in the sheet should not expand the sheet and obscure the content above.
// Default: YES
@property (nonatomic) BOOL prefersScrollingExpandsWhenScrolledToEdge;

// To animate changing any of the above properties, set them inside a block passed to this method.
// By the time this method returns, the receiver and all adjacent sheets in the sheet stack and their subviews will have been laid out.
- (void)animateChanges:(void (NS_NOESCAPE ^)(void))changes;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UISheetPresentationController.h>
#endif
