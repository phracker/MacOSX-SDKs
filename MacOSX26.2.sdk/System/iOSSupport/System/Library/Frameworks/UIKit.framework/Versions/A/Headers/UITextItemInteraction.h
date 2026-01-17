#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UITextItemInteraction.h>)
//
//  UITextItemInteraction.h
//  UIKit
//
//  Copyright (c) 2016-2018 Apple Inc. All rights reserved.
//

typedef NS_ENUM(NSInteger, UITextItemInteraction) {
    UITextItemInteractionInvokeDefaultAction,
    UITextItemInteractionPresentActions,
    UITextItemInteractionPreview,
} API_DEPRECATED("UITextItemInteraction has been replaced by text item methods on UITextViewDelegate", ios(10.0, 17.0), visionos(1.0, 1.0)) API_UNAVAILABLE(watchos);

#else
#import <UIKitCore/UITextItemInteraction.h>
#endif
