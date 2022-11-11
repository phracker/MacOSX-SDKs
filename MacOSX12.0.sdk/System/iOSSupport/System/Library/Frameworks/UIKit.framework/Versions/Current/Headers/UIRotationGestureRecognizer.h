#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIRotationGestureRecognizer.h>)
//
//  UIRotationGestureRecognizer.h
//  UIKit
//
//  Copyright (c) 2009-2018 Apple Inc. All rights reserved.
//

#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIGestureRecognizer.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

// Begins:  when two touches have moved enough to be considered a rotation
// Changes: when a finger moves while two fingers are down
// Ends:    when both fingers have lifted

UIKIT_EXTERN API_AVAILABLE(ios(3.2)) API_UNAVAILABLE(tvos) NS_SWIFT_UI_ACTOR
@interface UIRotationGestureRecognizer : UIGestureRecognizer

@property (nonatomic)          CGFloat rotation;            // rotation in radians
@property (nonatomic,readonly) CGFloat velocity;            // velocity of the pinch in radians/second

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIRotationGestureRecognizer.h>
#endif
