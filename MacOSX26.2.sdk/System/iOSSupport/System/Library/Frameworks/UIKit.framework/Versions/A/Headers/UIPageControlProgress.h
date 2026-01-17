#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIPageControlProgress.h>)
//
//  UIPageControlProgress.h
//  UIKit
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class UIPageControlProgress;

API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@protocol UIPageControlProgressDelegate<NSObject>

@optional

/// Returns the initial progress (between 0...1) for the specified page. By default, `currentProgress` is set to 0 when the page changes.
- (float)pageControlProgress:(UIPageControlProgress *)progress initialProgressForPage:(NSInteger)page;

/// Called when the page control progress visibility has changed, which could occur when the page control is being interacted
/// with. The page control progress becomes hidden when the user begins to interact with the page control (when it begins
/// continuous interaction), and is visible again when the user stops interacting with the control. Observe the page control progress
/// visibility to pause or resume the paging content.
///
/// Example:
/// @code
/// - (void)pageControlProgressVisibilityDidChange:(UIPageControlProgress *)progress {
///     BOOL isProgressVisible = progress.isProgressVisible;
///     if (isProgressVisible) {
///         [self _resumeContentFromInteractionChanges];
///     } else {
///         [self _pauseContentFromInteractionChanges];
///     }
/// }
/// @endcode
- (void)pageControlProgressVisibilityDidChange:(UIPageControlProgress *)progress;

@end

UIKIT_EXTERN API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface UIPageControlProgress: NSObject

/// An object that defines the delegate of the page control progress.
@property (nonatomic, weak, nullable) id<UIPageControlProgressDelegate> delegate;

/// The current progress value of the active page control indicator, between 0 and 1.
/// Values outside of [0...1] will be clamped.
@property (nonatomic, assign) float currentProgress;

/// Returns `YES` if the progress indicator is visible. The progress indicator is hidden when
/// the user is actively interacting with the `UIPageControl`.
@property (nonatomic, assign, readonly, getter=isProgressVisible) BOOL progressVisible;

@end

#pragma mark - Timer Progress

@class UIPageControlTimerProgress;

API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@protocol UIPageControlTimerProgressDelegate<UIPageControlProgressDelegate>

@optional

/// Called when the progress has changed from the time interval progress.
- (void)pageControlTimerProgressDidChange:(UIPageControlTimerProgress *)progress;

/// Determines if the time interval progress should advance to the next page upon progress completion of
/// the current page's duration. Default is YES.
- (BOOL)pageControlTimerProgress:(UIPageControlTimerProgress *)progress shouldAdvanceToPage:(NSInteger)page;

@end

UIKIT_EXTERN API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface UIPageControlTimerProgress: UIPageControlProgress

/// Creates a time interval progress with a specified preferred duration.
- (instancetype)initWithPreferredDuration:(NSTimeInterval)preferredDuration NS_DESIGNATED_INITIALIZER;

/// An object that defines the delegate of the page control progress.
@property (nonatomic, weak, nullable) id<UIPageControlTimerProgressDelegate> delegate;

/// Determines if the page control should loop back to page 0 after the last page. Default is NO.
@property (nonatomic, assign) BOOL resetsToInitialPageAfterEnd;

/// Returns YES if the timer is currently active.
@property (nonatomic, assign, readonly, getter=isRunning) BOOL running;

/// Resume the timer if it is not currently active.
- (void)resumeTimer;

/// Pause the timer if it is active.
- (void)pauseTimer;

/// The preferred duration for the time interval progress, used when there is no custom page duration set for the current page.
/// The preferred duration must be greater than 0.0
@property (nonatomic, assign) NSTimeInterval preferredDuration;

/// Sets a custom duration for the specified page. Set 0.0 to remove the custom duration for the specified page.
- (void)setDuration:(NSTimeInterval)duration forPage:(NSInteger)page;

/// Returns the duration for the specified page, and `preferredDuration` when there is no custom duration set
/// for the specified page.
- (NSTimeInterval)durationForPage:(NSInteger)page;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIPageControlProgress.h>
#endif
