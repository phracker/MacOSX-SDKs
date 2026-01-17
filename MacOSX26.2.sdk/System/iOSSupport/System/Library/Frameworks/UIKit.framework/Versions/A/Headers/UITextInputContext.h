#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UITextInputContext.h>)
//
//  UITextInputContext.h
//  UIKit
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <UIKit/UIKitCore.h>

// UITextInputContext provides a way to indicate Scribble, dictation, and hardware keyboard input.
UIKIT_EXTERN API_AVAILABLE(ios(16.4)) API_UNAVAILABLE(watchos)
@interface UITextInputContext : NSObject

@property (nonatomic, readwrite, getter=isPencilInputExpected) BOOL pencilInputExpected;
@property (nonatomic, readwrite, getter=isDictationInputExpected) BOOL dictationInputExpected;
@property (nonatomic, readwrite, getter=isHardwareKeyboardInputExpected) BOOL hardwareKeyboardInputExpected;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
+ (UITextInputContext *)current;
@end

#else
#import <UIKitCore/UITextInputContext.h>
#endif
