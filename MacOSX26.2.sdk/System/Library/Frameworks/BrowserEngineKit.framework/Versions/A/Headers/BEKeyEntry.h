//
//  BEKeyEntry.h
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <BrowserEngineKit/BEMacros.h>
#import <Foundation/Foundation.h>

#if BROWSERENGINEKIT_HAS_UIVIEW
#import <UIKit/UIKeyConstants.h>
#import <UIKit/UICommand.h>
#import <UIKit/UIKey.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, BEKeyPressState) {
    BEKeyPressStateDown = 1,
    BEKeyPressStateUp = 2,
} NS_SWIFT_NAME(BEKeyEntry.KeyPressState) BROWSERENGINE_TEXTINPUT_AVAILABILITY;

BROWSERENGINE_EXPORT BROWSERENGINE_TEXTINPUT_AVAILABILITY
@interface BEKeyEntry : NSObject

/**
 *  Data about the key that was pressed
 */
@property (nonatomic, readonly) UIKey *key;

/**
 * Type of the event, indicating whether it represents when the key is pressed or released.
 */
@property (nonatomic, readonly) BEKeyPressState state;

/**
 *  Represents whether the event is repeating.
 *
 *  For example, a continued press and hold on a key may result in its repeated insertion.
 */
@property (nonatomic, readonly, getter=isKeyRepeating) BOOL keyRepeating;

/**
 * Time at which the key event occurred.
 */
@property (nonatomic, readonly) NSTimeInterval timestamp;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

#endif // BROWSERENGINEKIT_HAS_UIVIEW
