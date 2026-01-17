#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIPageControl.h>)
//
//  UIPageControl.h
//  UIKit
//
//  Copyright (c) 2008-2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIControl.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIPageControlProgress.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

typedef NS_ENUM(NSInteger, UIPageControlInteractionState) {
    /// The default interaction state, where no interaction has occurred.
    UIPageControlInteractionStateNone        = 0,
    /// The interaction state for which the page was changed via a single, discrete interaction.
    UIPageControlInteractionStateDiscrete    = 1,
    /// The interaction state for which the page was changed via a continuous interaction.
    UIPageControlInteractionStateContinuous  = 2,
} API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos);

typedef NS_ENUM(NSInteger, UIPageControlBackgroundStyle) {
    /// The default background style that adapts based on the current interaction state.
    UIPageControlBackgroundStyleAutomatic  = 0,
    /// The background style that shows a full background regardless of the interaction
    UIPageControlBackgroundStyleProminent  = 1,
    /// The background style that shows a minimal background regardless of the interaction
    UIPageControlBackgroundStyleMinimal    = 2,
} API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos);

typedef NS_ENUM(NSInteger, UIPageControlDirection) {
    /// Page indicators are laid out in the natural direction of the system locale.
    /// By default, this is equivalent to @c UIPageControlDirectionLeftToRight on LTR locales, and
    /// @c UIPageControlDirectionRightToLeft on RTL locales.
    UIPageControlDirectionNatural          = 0,
    /// Page indicators are laid out from left to right.
    UIPageControlDirectionLeftToRight      = 1,
    /// Page indicators are laid out from right to left.
    UIPageControlDirectionRightToLeft      = 2,
    /// Page indicators are laid out from top to bottom.
    UIPageControlDirectionTopToBottom      = 3,
    /// Page indicators are laid out from bottom to top.
    UIPageControlDirectionBottomToTop      = 4,
} API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos);

UIKIT_EXTERN API_AVAILABLE(ios(2.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIPageControl : UIControl 

/// default is 0
@property (nonatomic, assign) NSInteger numberOfPages;

/// default is 0. Value is pinned to 0..numberOfPages-1
@property (nonatomic, assign) NSInteger currentPage;

/// hides the indicator if there is only one page, default is NO
@property (nonatomic) BOOL hidesForSinglePage;

/// An object that defines the progress of the page control. Default is nil.
@property (nonatomic, strong, nullable) UIPageControlProgress *progress API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/// The tint color for non-selected indicators. Default is nil.
@property (nullable, nonatomic, strong) UIColor *pageIndicatorTintColor API_AVAILABLE(ios(6.0)) UI_APPEARANCE_SELECTOR;

/// The tint color for the currently-selected indicators. Default is nil.
@property (nullable, nonatomic, strong) UIColor *currentPageIndicatorTintColor API_AVAILABLE(ios(6.0)) UI_APPEARANCE_SELECTOR;

/// The preferred background style. Default is UIPageControlBackgroundStyleAutomatic on iOS, and UIPageControlBackgroundStyleProminent on tvOS.
@property (nonatomic, assign) UIPageControlBackgroundStyle backgroundStyle API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos);

/// The layout direction of the page indicators. The default value is \c UIPageControlDirectionNatural.
@property (nonatomic, assign) UIPageControlDirection direction API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos);

/// The current interaction state for when the current page changes. Default is UIPageControlInteractionStateNone
@property (nonatomic, assign, readonly) UIPageControlInteractionState interactionState API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos);

/// Returns YES if continuous interaction is supported and enabled, NO otherwise. Default is YES for platforms that support it.
@property (nonatomic, assign) BOOL allowsContinuousInteraction API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos);

/// The preferred image for indicators. Symbol images are recommended. Default is nil.
@property (nonatomic, strong, nullable) UIImage *preferredIndicatorImage API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos);

/*!
 * @abstract Returns the override indicator image for the specific page, nil if no override image was set.
 * @param page Must be in the range of 0..numberOfPages
 */
- (nullable UIImage *)indicatorImageForPage:(NSInteger)page API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos);

/*!
 * @abstract Override the indicator image for a specific page. Symbol images are recommended.
 * @param image     The image for the indicator. Resets to the default if image is nil.
 * @param page      Must be in the range of 0..numberOfPages
 */
- (void)setIndicatorImage:(nullable UIImage *)image forPage:(NSInteger)page API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos);

/// The preferred image for the current page indicator. Symbol images are recommended. Default is nil.
/// If this value is nil, then UIPageControl will use \c preferredPageIndicatorImage (or its per-page variant) as
/// the indicator image.
@property (nonatomic, strong, nullable) UIImage *preferredCurrentPageIndicatorImage API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos);

/*!
 * @abstract Returns the override current page indicator image for the specific page, nil if no override image was set.
 * @param page Must be in the range of 0..numberOfPages
 */
- (nullable UIImage *)currentPageIndicatorImageForPage:(NSInteger)page API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos);

/*!
 * @abstract Override the current page indicator image for a specific page. Symbol images are recommended.
 * @param image     The image for the indicator. Resets to the default if image is nil.
 * @param page      Must be in the range of 0..numberOfPages
 */
- (void)setCurrentPageIndicatorImage:(nullable UIImage *)image forPage:(NSInteger)page API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos);

/// Returns the minimum size required to display indicators for the given page count. Can be used to size the control if the page count could change.
- (CGSize)sizeForNumberOfPages:(NSInteger)pageCount;

/// if set, tapping to a new page won't update the currently displayed page until -updateCurrentPageDisplay is called. default is NO
@property (nonatomic) BOOL defersCurrentPageDisplay API_DEPRECATED("defersCurrentPageDisplay no longer does anything reasonable with the new interaction mode.", ios(2.0, 14.0), visionos(1.0, 1.0)) API_UNAVAILABLE(watchos);

/// update page display to match the currentPage. ignored if defersCurrentPageDisplay is NO. setting the page value directly will update immediately
- (void)updateCurrentPageDisplay API_DEPRECATED("updateCurrentPageDisplay no longer does anything reasonable with the new interaction mode.", ios(2.0, 14.0), visionos(1.0, 1.0)) API_UNAVAILABLE(watchos);

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIPageControl.h>
#endif
