#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UILetterformAwareAdjusting.h>)
//
//  UILetterformAwareAdjusting.h
//  UIKit
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Background
///
/// When fonts created with `+[UIFont preferredFontForTextStyle:]` are used, UILabel, UITextField, and nonscrollable
/// UITextView will increase the height calculated in `-sizeThatFits:` and `-intrinsicContentSize` in the presence
/// of tall scripts.
///
/// Even with this increase, there will be some extreme ascenders and descenders that extend beyond this height.
///
/// Furthermore, this increase only occurs for the text-style fonts, so for non-text-style fonts such cases will be markedly more common.

typedef NS_ENUM(NSInteger, UILetterformAwareSizingRule) {
    /// `UILetterformAwareSizingRuleTypographic`: `-sizeThatFits:` and `-intrinsicContentSize` results will work well for typographic alignment of edges and centers of the view frames, but extreme ascenders or descenders in tall scripts may not be accounted for
    UILetterformAwareSizingRuleTypographic,
    
    /// `UILetterformAwareSizingRuleOversize`: `-sizeThatFits:` and `-intrinsicContentSize` results will account for extreme ascenders or descenders in tall scripts, but in such cases might not work well for typographic alignment of top and bottom edges and vertical centers of the view frames
    UILetterformAwareSizingRuleOversize,
} API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);

UIKIT_EXTERN API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@protocol UILetterformAwareAdjusting <NSObject>

/// `sizingRule` defaults to `UILetterformAwareSizingRuleTypographic` and determines what rule is used during the calculation of `-sizeThatFits:` and `-intrinsicContentSize`
@property(nonatomic) UILetterformAwareSizingRule sizingRule;
@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UILetterformAwareAdjusting.h>
#endif
