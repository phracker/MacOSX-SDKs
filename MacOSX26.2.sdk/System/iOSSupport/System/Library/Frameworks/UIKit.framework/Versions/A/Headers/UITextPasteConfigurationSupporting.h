#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UITextPasteConfigurationSupporting.h>)
//
//  UITextPasteConfigurationSupporting.h
//  UIKit 
//
//  Copyright © 2017-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIPasteConfigurationSupporting.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIPasteConfiguration.h>
#import <UIKit/UITextPasteDelegate.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

UIKIT_EXTERN API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR
@protocol UITextPasteConfigurationSupporting <UIPasteConfigurationSupporting>

@property (nonatomic, weak, nullable) id<UITextPasteDelegate> pasteDelegate;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UITextPasteConfigurationSupporting.h>
#endif
