// Copyright © 2023 Apple Inc. All rights reserved.

#if !__METAL_VERSION__
#import <TargetConditionals.h>
#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <CoreText/CoreText.h>

#if __has_include(<QuartzCore/QuartzCore.h>)
#import <QuartzCore/QuartzCore.h>
#endif

#if TARGET_OS_VISION && __has_include(<Spatial/Spatial.h>)
#import <Spatial/Spatial.h>
#endif

#else
#include <SwiftUI/SwiftUI_Metal.h>
#endif
