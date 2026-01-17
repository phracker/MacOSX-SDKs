//
//  UIKit.h
//  UIKit
//
//  Copyright © 2017-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitCore.h>

#if __has_include(<UIKit/UIFoundation.h>)
#import <UIKit/UIFoundation.h>
#elif __has_include(<UIKit/NSAdaptiveImageGlyph.h>)
#import <UIKit/NSAdaptiveImageGlyph.h>
#import <UIKit/NSTextRange.h>
#import <UIKit/NSTextList.h>
#import <UIKit/NSTextAttachment.h>
#endif

#if __has_include(<UIKit/DocumentManager.h>)
#import <UIKit/DocumentManager.h>
#endif

#if __has_include(<UIKit/ShareSheet.h>)
#import <UIKit/ShareSheet.h>
#endif

#if __has_include(<UIKit/PrintKitUI.h>)
#import <UIKit/PrintKitUI.h>
#endif
