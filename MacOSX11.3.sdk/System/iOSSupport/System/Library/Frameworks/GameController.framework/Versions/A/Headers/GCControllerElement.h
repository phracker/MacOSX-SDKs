//
//  GCControllerElement.h
//  GameController
//
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Elements on a GCDevice can be used for system gestures. The system gesture state represents how input is handled in the app
 for a controller element that is bound to a system gesture.
 
 @example The Options button on an extended gamepad can be bound to take a screenshot with a long press. This occurs outside of
 the control of the app. If a user presses the Options button, the system gesture recognizer will run by default. If a long press is detected,
 input will not be forwarded to your app (your application won't see the Options button was pressed at all). If a long press is not detected,
 input will be forwared to your app, with a delay.
 
 If you do not want any delay in receiving input for this element, you have two options
 - Set the preferred state of the element to GCSystemGestureStateAlwaysReceive. The system gesture recognize will run
 concurrently with input being sent to your app. This removes input delay, but can lead to system gestures being triggered
 simulatenously with in-app actions.
 - Set the preferred state of the element to GCSystemGestureStateDisabled. This will disable the system gesture recognizer - your app
 will receive full control of the input for this element.
 
 @see GCControllerElement.boundToSystemGesture
 @see GCControllerElement.preferredSystemGestureState
 */
typedef NS_ENUM(NSInteger, GCSystemGestureState) {
    /** System gesture recognizers will run before input is sent to app, this is the default state */
    GCSystemGestureStateEnabled = 0,
    /** Input is sent to app and processed by system gesture recognizers simultaneously */
    GCSystemGestureStateAlwaysReceive,
    /** System gesture recognizers will not run at all. Input is passed directly to app */
    GCSystemGestureStateDisabled
} NS_SWIFT_NAME(GCControllerElement.SystemGestureState);

/**
 Every controller element knows which collection it belongs to and whether its input value is analog or digital.
 */
API_AVAILABLE(macos(10.9), ios(7.0), tvos(7.0))
@interface GCControllerElement : NSObject

/**
 Each element can be part of a wider collection of inputs that map to a single logical element. A directional pad (dpad)
 is a logical collection of two axis inputs and thus each axis belongs to the same collection element - the dpad.
 */
@property (nonatomic, weak, readonly, nullable) GCControllerElement *collection;

/**
 Check if the element can support more than just digital values, such as decimal ranges between 0 and 1.
 Defaults to YES for most elements.
 */
@property (nonatomic, readonly, getter = isAnalog) BOOL analog;

/**
 Check if the element is bound to a system gesture.
 Defaults to NO for most elements.
 
 @see preferredSystemGestureState
 @see GCSystemGestureState
 */
@property (nonatomic, readonly, getter = isBoundToSystemGesture) BOOL boundToSystemGesture;

/**
 The preferred system gesture state for this element.
 Defaults to GCSystemGestureStateEnabled for most elements
 
 @note This is merely the preferred system gesture state - it is not guaranteed to be respected by the system.
 @note It is highly recommended to leave this set to the default value, however there may be situations (for example, game
 streaming apps) where it is preferrable to disable system gestures.
 @see boundToSystemGesture
 */
@property (nonatomic, readwrite) GCSystemGestureState preferredSystemGestureState;

/**
 The element's SF Symbols name, taking input remapping into account.
 
 @note In almost all instances, you should use this over unmappedSfSymbolsName in your UI.
 */
@property (nonatomic, strong, nullable) NSString *sfSymbolsName;

/**
 The element's localized name, taking input remapping into account.
 
 @note In almost all instances, you should use this over unmappedLocalizedName in your UI.
 */
@property (nonatomic, strong, nullable) NSString *localizedName;

/**
 The element's SF Symbols name, not taking any input remapping into account.
 
 @note Use this in your games own remapping UI, or when you need to prompt a user that a given button has no mapping (sfSymbolsName is nil).
 */
@property (nonatomic, strong, nullable) NSString *unmappedSfSymbolsName;

/**
 The element's localized name, not taking any input remapping into account.
 
 @note Use this in your games own remapping UI, or when you need to prompt a user that a given button has no mapping (localizedName is nil).
 */
@property (nonatomic, strong, nullable) NSString *unmappedLocalizedName;

/**
 A set of aliases that can be used to access this element with keyed subscript notation.
 
 */
@property (nonatomic, readonly) NSSet<NSString *> *aliases API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

@end

NS_ASSUME_NONNULL_END
