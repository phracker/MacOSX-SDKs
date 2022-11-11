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

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, UIPageControlInteractionState) {
    /// The default interaction state, where no interaction has occurred.
    UIPageControlInteractionStateNone        = 0,
    /// The interaction state for which the page was changed via a single, discrete interaction.
    UIPageControlInteractionStateDiscrete    = 1,
    /// The interaction state for which the page was changed via a continuous interaction.
    UIPageControlInteractionStateContinuous  = 2,
} API_AVAILABLE(ios(14.0));

typedef NS_ENUM(NSInteger, UIPageControlBackgroundStyle) {
    /// The default background style that adapts based on the current interaction state.
    UIPageControlBackgroundStyleAutomatic  = 0,
    /// The background style that shows a full background regardless of the interaction
    UIPageControlBackgroundStyleProminent  = 1,
    /// The background style that shows a minimal background regardless of the interaction
    UIPageControlBackgroundStyleMinimal    = 2,
} API_AVAILABLE(ios(14.0));

UIKIT_EXTERN API_AVAILABLE(ios(2.0)) NS_SWIFT_UI_ACTOR
@interface UIPageControl : UIControl 

/// default is 0
@property (nonatomic, assign) NSInteger numberOfPages;

/// default is 0. Value is pinned to 0..numberOfPages-1
@property (nonatomic, assign) NSInteger currentPage;

/// hides the indicator if there is only one page, default is NO
@property (nonatomic) BOOL hidesForSinglePage;

/// The tint color for non-selected indicators. Default is nil.
@property (nullable, nonatomic, strong) UIColor *pageIndicatorTintColor API_AVAILABLE(ios(6.0)) UI_APPEARANCE_SELECTOR;

/// The tint color for the currently-selected indicators. Default is nil.
@property (nullable, nonatomic, strong) UIColor *currentPageIndicatorTintColor API_AVAILABLE(ios(6.0)) UI_APPEARANCE_SELECTOR;

/// The preferred background style. Default is UIPageControlBackgroundStyleAutomatic on iOS, and UIPageControlBackgroundStyleProminent on tvOS.
@property (nonatomic, assign) UIPageControlBackgroundStyle backgroundStyle API_AVAILABLE(ios(14.0));

/// The current interaction state for when the current page changes. Default is UIPageControlInteractionStateNone
@property (nonatomic, assign, readonly) UIPageControlInteractionState interactionState API_AVAILABLE(ios(14.0));

/// Returns YES if the continuous interaction is enabled, NO otherwise. Default is YES.
@property (nonatomic, assign) BOOL allowsContinuousInteraction API_AVAILABLE(ios(14.0));

/// The preferred image for indicators. Symbol images are recommended. Default is nil.
@property (nonatomic, strong, nullable) UIImage *preferredIndicatorImage API_AVAILABLE(ios(14.0));

/*!
 * @abstract Returns the override indicator image for the specific page, nil if no override image was set.
 * @param page Must be in the range of 0..numberOfPages
 */
- (nullable UIImage *)indicatorImageForPage:(NSInteger)page API_AVAILABLE(ios(14.0));

/*!
 * @abstract Override the indicator image for a specific page. Symbol images are recommended.
 * @param image    The image for the indicator. Resets to the default if image is nil.
 * @param page      Must be in the range of 0..numberOfPages
 */
- (void)setIndicatorImage:(nullable UIImage *)image forPage:(NSInteger)page API_AVAILABLE(ios(14.0));

/// Returns the minimum size required to display indicators for the given page count. Can be used to size the control if the page count could change.
- (CGSize)sizeForNumberOfPages:(NSInteger)pageCount;

/// if set, tapping to a new page won't update the currently displayed page until -updateCurrentPageDisplay is called. default is NO
@property (nonatomic) BOOL defersCurrentPageDisplay API_DEPRECATED("defersCurrentPageDisplay no longer does anything reasonable with the new interaction mode.", ios(2.0, 14.0));

/// update page display to match the currentPage. ignored if defersCurrentPageDisplay is NO. setting the page value directly will update immediately
- (void)updateCurrentPageDisplay API_DEPRECATED("updateCurrentPageDisplay no longer does anything reasonable with the new interaction mode.", ios(2.0, 14.0));

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIPageControl.h>
#endif
