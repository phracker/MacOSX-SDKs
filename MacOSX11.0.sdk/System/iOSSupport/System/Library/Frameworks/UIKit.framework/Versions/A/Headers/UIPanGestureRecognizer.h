#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIPanGestureRecognizer.h>)
//
//  UIPanGestureRecognizer.h
//  UIKit
//
//  Copyright (c) 2008-2018 Apple Inc. All rights reserved.
//

#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIGestureRecognizer.h>
#import <UIKit/UIKitDefines.h>

// Begins:  when at least minimumNumberOfTouches have moved enough to be considered a pan
// Changes: when a finger moves while at least minimumNumberOfTouches are down
// Ends:    when all fingers have lifted

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, UIScrollType) {
    UIScrollTypeDiscrete,   // Discrete scrolls originate from devices like a scroll wheel mouse
    UIScrollTypeContinuous, // Continuous scrolls originate from devices like trackpads
} API_AVAILABLE(ios(13.4)) API_UNAVAILABLE(tvos, watchos);

typedef NS_OPTIONS(NSInteger, UIScrollTypeMask) {
    UIScrollTypeMaskDiscrete    = 1 << UIScrollTypeDiscrete,
    UIScrollTypeMaskContinuous  = 1 << UIScrollTypeContinuous,
    UIScrollTypeMaskAll         = UIScrollTypeMaskDiscrete | UIScrollTypeMaskContinuous,
} API_AVAILABLE(ios(13.4)) API_UNAVAILABLE(tvos, watchos);

UIKIT_EXTERN API_AVAILABLE(ios(3.2)) @interface UIPanGestureRecognizer : UIGestureRecognizer 

@property (nonatomic)          NSUInteger minimumNumberOfTouches API_UNAVAILABLE(tvos);   // default is 1. the minimum number of touches required to match
@property (nonatomic)          NSUInteger maximumNumberOfTouches API_UNAVAILABLE(tvos);   // default is UINT_MAX. the maximum number of touches that can be down

- (CGPoint)translationInView:(nullable UIView *)view;                        // translation in the coordinate system of the specified view
- (void)setTranslation:(CGPoint)translation inView:(nullable UIView *)view;

- (CGPoint)velocityInView:(nullable UIView *)view;                           // velocity of the pan in points/second in the coordinate system of the specified view

@property(nonatomic)           UIScrollTypeMask allowedScrollTypesMask API_AVAILABLE(ios(13.4)) API_UNAVAILABLE(tvos, watchos);

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIPanGestureRecognizer.h>
#endif
