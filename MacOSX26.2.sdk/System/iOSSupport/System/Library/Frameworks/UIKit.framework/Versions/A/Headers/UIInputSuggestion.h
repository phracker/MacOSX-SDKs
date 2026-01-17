#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIInputSuggestion.h>)
//
//  UIInputSuggestion.h
//  UIKit
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

///@abstract A base class you use to handle suggestions from the keyboard or system.
UIKIT_EXTERN API_AVAILABLE(ios(18.4)) API_UNAVAILABLE(tvos, watchos, visionos, macCatalyst)
@interface UIInputSuggestion : NSObject

/// No properties at this time

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIInputSuggestion.h>
#endif
