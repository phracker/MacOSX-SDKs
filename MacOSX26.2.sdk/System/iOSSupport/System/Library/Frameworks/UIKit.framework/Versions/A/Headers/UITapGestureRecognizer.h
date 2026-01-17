#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UITapGestureRecognizer.h>)
//
//  UITapGestureRecognizer.h
//  UIKit
//
//  Copyright (c) 2008-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIGestureRecognizer.h>
#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

// Recognizes: when numberOfTouchesRequired have tapped numberOfTapsRequired times

// Touch Location Behaviors:
//     locationInView:         location of the tap, from the first tap in the sequence if numberOfTapsRequired > 1. this is the centroid if numberOfTouchesRequired > 1
//     locationOfTouch:inView: location of a particular touch, from the first tap in the sequence if numberOfTapsRequired > 1

UIKIT_EXTERN API_AVAILABLE(ios(3.2)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UITapGestureRecognizer : UIGestureRecognizer

@property (nonatomic) NSUInteger  numberOfTapsRequired;       // Default is 1. The number of taps required to match
@property (nonatomic) NSUInteger  numberOfTouchesRequired API_UNAVAILABLE(tvos);    // Default is 1. The number of fingers required to match

@property (nonatomic) UIEventButtonMask buttonMaskRequired API_AVAILABLE(ios(13.4)) API_UNAVAILABLE(tvos, watchos);  // Default is UIEventButtonMaskPrimary and cannot be 0. This property is only evaluated on indirect input devices and is the mask of pressed buttons to required to match.

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UITapGestureRecognizer.h>
#endif
