#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UISmartReplySuggestion.h>)
//
//  UISmartReplySuggestion.h
//  UIKit
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIInputSuggestion.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A class you use to handle a Smart Reply suggestion.
///
/// Use the ``smartReply`` string as a signal of the user’s intention when you generate long form text based on the option the user selected.
UIKIT_EXTERN API_AVAILABLE(ios(18.4)) API_UNAVAILABLE(tvos, watchos, visionos, macCatalyst)
@interface UISmartReplySuggestion : UIInputSuggestion

/// A string from the Smart Reply option the user selected.
///
/// Use this as a signal of the user’s intention when you generate long form text based on the option the user selected.
@property (copy, nonatomic, readonly) NSString *smartReply;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UISmartReplySuggestion.h>
#endif
