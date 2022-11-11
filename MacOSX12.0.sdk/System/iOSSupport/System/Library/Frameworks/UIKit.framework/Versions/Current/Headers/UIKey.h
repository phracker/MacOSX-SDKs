#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIKey.h>)
//
//  UIKey.h
//  UIKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UICommand.h>
#import <UIKit/UIKeyConstants.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

UIKIT_EXTERN API_AVAILABLE(ios(13.4), tvos(13.4)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIKey : NSObject <NSCopying, NSCoding>

/// @returns a string representing what would be inserted into a text field when this key is pressed.
/// @discussion if a modifier key is held, this property will contain the modified characters according
/// the rules for that particular modifier key (i.e., if shift is held on a Latin keyboard, this will
/// contain capital letters). 
@property (nonatomic, readonly) NSString *characters;

/// @returns a string representing which characters would be inserted into a text field when this key is
/// pressed, not taking any held modifiers into account.
/// @discussion for Latin based languages, expect this to be always in lowercase (unmodified meaning not
/// taking shift key into account). If only a modifier key was pressed, this property will contain an empty string.
@property (nonatomic, readonly) NSString *charactersIgnoringModifiers;

/// @returns a bitfield representing which modifier keys are currently being held in addition to this key.
@property (nonatomic, readonly) UIKeyModifierFlags modifierFlags;

/// @returns the raw HID usage code for the pressed key. See UIKeyConstants.h.
@property (nonatomic, readonly) UIKeyboardHIDUsage keyCode;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIKey.h>
#endif
