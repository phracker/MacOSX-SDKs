//
//  ARKit.h
//
//  Copyright © 2016-2023 Apple Inc. All rights reserved.
//

#include <TargetConditionals.h>

/** @framework ARKit
    @abstract A high-level Augmented Reality framework.
    @discussion ARKit lets you easily configure and use Augmented Reality techniques to track, detect, and render.
 */


#if __has_include(<ARKit/ARKitFoundation.h>)
#import <ARKit/ARKitFoundation.h>
#endif

#if __has_include(<ARKit/ARKitCore.h>)
#import <ARKit/ARKitCore.h>
#endif

#if __has_include(<ARKit/ARKitUI.h>)
#import <ARKit/ARKitUI.h>
#endif

