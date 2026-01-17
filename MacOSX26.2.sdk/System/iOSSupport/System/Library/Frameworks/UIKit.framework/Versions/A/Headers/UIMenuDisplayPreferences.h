#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIMenuDisplayPreferences.h>)
//
//  UIMenuDisplayPreferences.h
//  UIKit
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

UIKIT_EXTERN API_AVAILABLE(ios(17.4)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIMenuDisplayPreferences : NSObject <NSCopying, NSSecureCoding>

/// Maximum number of title and subtitle lines displayed for this menu's elements. Defaults to NSNotFound, indicating no preference.
@property (nonatomic, assign) NSInteger maximumNumberOfTitleLines;

@end

NS_HEADER_AUDIT_END(nullability, sendability)


#else
#import <UIKitCore/UIMenuDisplayPreferences.h>
#endif
