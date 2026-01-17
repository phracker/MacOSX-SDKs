//
//  INVoiceShortcut.h
//  Intents
//
//  Copyright © 2018 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

@class INShortcut;

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract A shortcut that has been added to Siri
 */
API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macosx)
@interface INVoiceShortcut : NSObject <NSSecureCoding, NSCopying>

/*!
 @abstract The unique identifier for this voice shortcut
 */
@property (readonly, strong, NS_NONATOMIC_IOSONLY) NSUUID *identifier;

/*!
 @abstract The phrase the user speaks to invoke this shortcut; set by the user when they add it to Siri.
 */
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *invocationPhrase;

/*!
 @abstract The shortcut that will be performed when this voice shortcut is invoked via Siri.
 */
@property (readonly, copy, NS_NONATOMIC_IOSONLY) INShortcut *shortcut;

/*!
 An @c INVoiceShortcut cannot be created directly. Instead, create an @c INShortcut, and add it using @c INUIAddVoiceShortcutViewController.
 */
- (instancetype)init NS_UNAVAILABLE;

/*!
 An @c INVoiceShortcut cannot be created directly. Instead, create an @c INShortcut, and add it using @c INUIAddVoiceShortcutViewController.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
