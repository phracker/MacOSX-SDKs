/*
	ScreenSaverView.h
	ScreenSaver
	Copyright (c) 2000-2020, Apple Inc.
	All rights reserved.
*/

#import <AppKit/AppKit.h>

API_UNAVAILABLE_BEGIN(ios, tvos, watchos)

#include <stdlib.h>
#include <limits.h>

/// An abstract class that defines the interface for subclassers to interact
/// with the screen saver infrastructure.
///
/// ``ScreenSaverView`` provides the interface for your screen saver, including
/// the content you animate onscreen and an optional configuration sheet. Create
/// your own custom subclass and add it to your screen saver bundle. Use your
/// subclass to create the animations that you want to appear onscreen, and to
/// specify additional animation details.
///
/// - Note: When someone previews your screen saver in System Preferences, the
/// system instantiates your ``ScreenSaverView`` subclass.
///
/// You can draw from your view’s ``ScreenSaverView/drawRect:`` method, or you
/// can draw directly from the ``ScreenSaverView/animateOneFrame`` method. If
/// you prefer to use the ``ScreenSaverView/drawRect:`` method, use the
/// ``ScreenSaverView/animateOneFrame`` method to call the
/// <doc://com.apple.documentation/documentation/appkit/nsview/1483475-setneedsdisplayinrect>
/// method and specify the portions of your view that require updates.
@interface ScreenSaverView : NSView
{
@private
    NSTimer *_animationTimer;
    NSTimeInterval _timeInterval;
    BOOL _isPreview;
    void *_reserved1;
    void *_reserved2;
    void *_reserved3;
}

/// Returns the type of backing store you want for your screen saver’s window.
///
/// ## Overview
///
/// This method returns <doc://com.apple.documentation/documentation/appkit/nsbackingstoretype/nsbackingstorebuffered>
/// by default. If you want to change the backing store type, override this method and
/// return a new value. If you override the method, you don’t need to call the inherited
/// version.
+ (NSBackingStoreType)backingStoreType;

/// Indicates whether to perform a gradual screen fade when the system starts and stops
/// your screen saver’s animation.
///
/// ## Overview
///
/// This class method allows the screen saver view to select how the desktop visibly
/// transitions to the screen saver view. When this method returns <doc://com.apple.documentation/documentation/objectivec/yes>,
/// the screen gradually darkens before the animation begins. When it returns <doc://com.apple.documentation/documentation/objectivec/no>,
/// the screen transitions immediately to the screen saver. The latter behavior is more
/// appropriate if the screen saver animates a screenshot of the desktop, as is the case
/// for optical lens effects. The default is <doc://com.apple.documentation/documentation/objectivec/yes>.
+ (BOOL)performGammaFade;

/// Creates a newly allocated screen saver view with the specified frame rectangle and
/// preview information.
///
/// ## Overview
///
///  The screen saver application installs the new view object into the view hierarchy
/// of an <doc://com.apple.documentation/documentation/appkit/nswindow> before the animation
/// begins. This method is the designated initializer for the ``ScreenSaver/ScreenSaverView``
/// class. Returns `self`.
///
/// - Parameters:
///   - frame: The frame rectangle for the view.
///
///   - isPreview: <doc://com.apple.documentation/documentation/objectivec/yes> if this view provides a
/// preview for system settings, or <doc://com.apple.documentation/documentation/objectivec/no>
/// if the system fills the screen with your view’s contents.
/// 
- (nullable instancetype)initWithFrame:(NSRect)frame isPreview:(BOOL)isPreview NS_DESIGNATED_INITIALIZER;

/// The time interval between animation frames.
///
/// If your screen saver has particular requirements for time between animation
/// frames, call this method to set the animation rate to a reasonable value.
@property (NS_NONATOMIC_IOSONLY) NSTimeInterval animationTimeInterval;

/// Activates the periodic timer that animates the screen saver.
///
/// ## Overview
///
/// The system calls this method when it’s time for you to start animating your screen
/// saver’s content. The system calls this method only once at the start of animations.
/// Use this method to set up any initial state information you require or to allocate
/// expensive resources. If you override this method, you must call the inherited implementation
/// at some point.
///
/// ## See also
///
/// - ``ScreenSaver/ScreenSaverView/stopAnimation``
- (void)startAnimation;

/// Deactivates the timer that advances the animation.
///
/// ## Overview
///
/// The system calls this method when it’s time for you to stop animating your screen
/// saver’s content. The system calls this method only once at the end of animations.
/// Use this method to unload expensive resources or to reset your screen saver to a
/// known state. If you override this method, you must call the inherited implementation
/// at some point.
///
/// ## See also
///
/// - ``ScreenSaver/ScreenSaverView/startAnimation``
///
- (void)stopAnimation;

/// A Boolean value that indicates whether the screen saver is animating.
///
/// ## Overview
///
/// The value of this property is <doc://com.apple.documentation/documentation/objectivec/yes>
/// when the screen saver is animating, and <doc://com.apple.documentation/documentation/objectivec/no>
/// when it isn’t.
///
/// ## See also
///
/// - ``ScreenSaver/ScreenSaverView/stopAnimation``
/// - ``ScreenSaver/ScreenSaverView/startAnimation``
///
@property (NS_NONATOMIC_IOSONLY, getter=isAnimating, readonly) BOOL animating;

/// Draws the screen saver view.
///
/// ## Overview
///
/// ``ScreenSaver/ScreenSaverView`` implements ``ScreenSaver/ScreenSaverView/drawRect:``
/// to draw a black background. Subclasses can do their drawing here or in ``ScreenSaver/ScreenSaverView/animateOneFrame``.
///
/// ## See also
///
/// - ``ScreenSaver/ScreenSaverView/stopAnimation``
/// - ``ScreenSaver/ScreenSaverView/animateOneFrame``
/// - ``ScreenSaver/ScreenSaverView/startAnimation``
///
- (void)drawRect:(NSRect)rect;

/// Advances the screen saver’s animation by a single frame.
///
/// ## Overview 
///
/// The system calls this method each time the timer animating the screen saver fires.
/// The time between calls to this method is always at least ``ScreenSaver/ScreenSaverView/animationTimeInterval``.
/// The system locks focus on your view before it calls this method, so you can use this
/// method to draw content. You can also let ``ScreenSaver/ScreenSaverView/drawRect:``
/// perform the drawing, in which case you use this method to call <doc://com.apple.documentation/documentation/appkit/nsview/1483475-setneedsdisplayinrect>
/// to mark your view as dirty. The default implementation of this method does nothing.
///
/// ## See also
///
/// - ``ScreenSaver/ScreenSaverView/drawRect:``
- (void)animateOneFrame;

/// A Boolean value that indicates whether the screen saver has an associated configuration sheet.
///
/// If you provide a configuration sheet in your bundle, override this method and return <doc://com.apple.documentation/documentation/objectivec/yes>.
///
/// ## See also
///
/// - ``ScreenSaver/ScreenSaverView/configureSheet``
///
@property (readonly) BOOL hasConfigureSheet;

/// The window that contains the controls to configure the screen saver.
///
/// The system runs this window as a sheet, so include buttons that allow the
/// user to end the modal session in which the sheet runs. When the user
/// dismisses the sheet, the controller in charge of the sheet must end the
/// document modal session by calling the
/// <doc://com.apple.documentation/documentation/appkit/nsapplication> method
/// <doc://com.apple.documentation/documentation/appkit/nsapplication/1428503-endsheet>
/// with the sheet’s window as the argument.
///
/// ## See also
///
/// - ``ScreenSaver/ScreenSaverView/hasConfigureSheet``
@property (readonly, strong) NSWindow * _Nullable configureSheet;

/// A Boolean value that indicates whether the screen saver view is set to a size suitable
/// for previewing its content.
///
/// ## Overview
///
/// The system sets the value of this property to <doc://com.apple.documentation/documentation/objectivec/yes>
/// when it creates a smaller preview of your screen saver. When the value is <doc://com.apple.documentation/documentation/objectivec/no>,
/// your view matches the size of the screen. Use this property to adjust the content
/// you present. For example, you might change the drawing parameters or data you display
/// in your view.
@property (NS_NONATOMIC_IOSONLY, getter=isPreview, readonly) BOOL preview;

@end

/// Returns a random integer value.
///
/// ## Overview
///
/// The Screen Saver framework automatically seeds the `random()` C function to generate
/// the number.
///
/// - Parameters:
///   - a: The first integer value.
///
///   - b: The second integer value.
static __inline__ int SSRandomIntBetween(int a, int b)
{
    int range = b - a < 0 ? b - a - 1 : b - a + 1;
    int value = (int)(range * ((float) random() / (float) RAND_MAX));
    return value == range ? a : a + value;
}

/// Returns a random float value.
///
/// ## Overview
///
/// The Screen Saver framework automatically seeds the `random()` C function to generate
/// the number.
///
/// - Parameters:
///   - a: The first floating-point value.
///
///   - b: The second floating-point value.
///
/// - Returns: A random floating-point value between the values `a` and `b`, inclusive.
static __inline__ CGFloat SSRandomFloatBetween(CGFloat a, CGFloat b)
{
    return a + (b - a) * ((CGFloat) random() / (CGFloat) RAND_MAX);
}

/// Returns a random point.
///
/// ## Overview
///
/// The Screen Saver framework automatically seeds the `random()` C function to generate
/// the point.
///
/// - Parameters:
///   - size: The horizontal and vertical amounts to subtract from the rectangle’s size.
///
///   - rect: The rectangle to contain the point.
///
/// - Returns: A random point within `rect`, constrained within `(rect.size - size)` from `rect`’s
/// origin.
static __inline__ NSPoint SSRandomPointForSizeWithinRect(NSSize size, NSRect rect)
{
    return NSMakePoint (
                SSRandomFloatBetween(rect.origin.x, (rect.origin.x + rect.size.width - size.width)), 
                SSRandomFloatBetween(rect.origin.y, (rect.origin.y + rect.size.height - size.height)));
}

/// Returns a rectangle.
///
/// - Parameters:
///   - innerRect: The rectangle to center.
///
///   - outerRect: The rectangle to contain `innerRect`.
///
/// - Returns: A rectangle that’s the same size as `innerRect`, but is centered inside `outerRect`.
///
/// 
static __inline__ NSRect SSCenteredRectInRect(NSRect innerRect, NSRect outerRect)
{
#if CGFLOAT_IS_DOUBLE
    innerRect.origin.x = outerRect.origin.x + floor((outerRect.size.width - innerRect.size.width) / 2);
    innerRect.origin.y = outerRect.origin.y + floor((outerRect.size.height - innerRect.size.height) / 2);
#else
    innerRect.origin.x = outerRect.origin.x + floorf((outerRect.size.width - innerRect.size.width) / 2);
    innerRect.origin.y = outerRect.origin.y + floorf((outerRect.size.height - innerRect.size.height) / 2);
#endif
    return innerRect;
}

API_UNAVAILABLE_END
