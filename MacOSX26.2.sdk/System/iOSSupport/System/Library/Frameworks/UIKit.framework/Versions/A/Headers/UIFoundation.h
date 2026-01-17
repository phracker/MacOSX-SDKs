//
//  UIFoundation.h
//  Text Kit
//
//  Copyright © 2021-2025 Apple Inc. All rights reserved.
//

#import <UIKit/NSTextRange.h>
#import <UIKit/NSTextList.h>
#import <UIKit/NSTextAttachment.h>
#import <UIKit/NSAdaptiveImageGlyph.h>

#if !TARGET_OS_WATCH || __has_include(<UIKit/NSTextElement.h>)
#import <UIKit/NSTextElement.h>
#import <UIKit/NSTextSelection.h>
#import <UIKit/NSTextSelectionNavigation.h>
#import <UIKit/NSTextViewportLayoutController.h>
#import <UIKit/NSTextContentManager.h>
#import <UIKit/NSTextLayoutFragment.h>
#import <UIKit/NSTextLayoutManager.h>
#import <UIKit/NSTextLineFragment.h>
#import <UIKit/NSTextListElement.h>
#endif /* !TARGET_OS_WATCH || __has_include(<UIKit/NSTextElement.h>) */
