#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIHoverGestureRecognizer.h>)
//
//  UIHoverGestureRecognizer.h
//  UIKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIGestureRecognizer.h>
#import <UIKit/UIKitDefines.h>

// UIHoverGestureRecognizer
// On macOS or iPadOS, this gesture recognizer will begin recognition when the cursor
// (while no mouse buttons are pressed) enters its view, changes during movement
// within the view and ends when the cursor leaves said view.
// Note: While buttons are pressed any currently active hover gesture recognizers
// are effectively paused (letting other gesture recognizers work) until all
// mouse buttons have been released.
//
// On iOS, this gesture recognizer doesn't recognize anything and is effectively
// a noop.
UIKIT_EXTERN API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, tvos) @interface UIHoverGestureRecognizer : UIGestureRecognizer
@end

#else
#import <UIKitCore/UIHoverGestureRecognizer.h>
#endif
