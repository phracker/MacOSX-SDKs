//
//  GCControllerProfile.h
//  GameController
//
//  Copyright (c) 2019 Apple Inc. All rights reserved.
//


@protocol GCDevice;
@class GCControllerElement;
@class GCControllerButtonInput;
@class GCControllerAxisInput;
@class GCControllerDirectionPad;
@class GCControllerTouchpad;

@compatibility_alias GCDeviceElement GCControllerElement;
@compatibility_alias GCDeviceButtonInput GCControllerButtonInput;
@compatibility_alias GCDeviceAxisInput GCControllerAxisInput;
@compatibility_alias GCDeviceDirectionPad GCControllerDirectionPad;
@compatibility_alias GCDeviceTouchpad GCControllerTouchpad;

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
A game controller profile representing physical buttons, thumbsticks, dpads, etc... on a controller.

All controller profiles provide a base level of information about the controller they belong to.

A profile maps the hardware notion of a controller into a logical controller. One that a developer can design for
and depend on, no matter the underlying hardware.
*/
API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0))
@interface GCPhysicalInputProfile : NSObject

/**
 A profile keeps a reference to the device that this profile is mapping input from
 */
@property (nonatomic, readonly, weak) id<GCDevice> device API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

/**
 The last time elements of this profile were updated.
 */
@property (atomic, readonly) NSTimeInterval lastEventTimestamp API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

/**
 Whether the user has remapped their physical input controls for this profile at the system level.
 
 @discussion On iOS and tvOS, users can remap their game controller inputs in Settings.
 */
@property (nonatomic, readonly) BOOL hasRemappedElements API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));

/**
 The following properties allow for runtime lookup of any input element on a profile, when provided with a valid alias.

 @example extendedGamepad.elements["Button A"] == extendedGamepad.buttonA // YES
 @example extendedGamepad.dpads["Left Thumbstick"] == extendedGamepad.leftThumbstick // YES
 @example extendedGamepad.dpads["Button B"] // returns nil, "Button B" is not a GCControllerDirectionPad
*/
@property (nonatomic, readonly, strong) NSDictionary<NSString *, GCDeviceElement *> *elements API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
@property (nonatomic, readonly, strong) NSDictionary<NSString *, GCDeviceButtonInput *> *buttons API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
@property (nonatomic, readonly, strong) NSDictionary<NSString *, GCDeviceAxisInput *> *axes API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
@property (nonatomic, readonly, strong) NSDictionary<NSString *, GCDeviceDirectionPad *> *dpads API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
@property (nonatomic, readonly, strong) NSDictionary<NSString *, GCDeviceTouchpad *> *touchpads API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

/**
 The following properties allow for dynamic querying of the input elements available on a profile.
*/
@property (nonatomic, readonly, strong) NSSet<GCDeviceElement *> *allElements API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
@property (nonatomic, readonly, strong) NSSet<GCDeviceButtonInput *> *allButtons API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
@property (nonatomic, readonly, strong) NSSet<GCDeviceAxisInput *> *allAxes API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
@property (nonatomic, readonly, strong) NSSet<GCDeviceDirectionPad *> *allDpads API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
@property (nonatomic, readonly, strong) NSSet<GCDeviceTouchpad *> *allTouchpads API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

/**
 Profile elements can be accessed using keyed subscript notation, with a valid alias of its inputs.
 
 @example extendedGamepad["Button A"] == extendedGamepad.buttonA // YES
 @example microGamepad["Button X"] == microGamepad.buttonX // YES
 @note Equivalent to -elements
 */
- (__kindof GCDeviceElement * _Nullable)objectForKeyedSubscript:(NSString *)key API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

/**
 Polls the state vector of the physical input input and saves it to a new and writable instance of GCPhysicalInputProfile.
 
 If your application is heavily multithreaded this may also be useful to guarantee atomicity of input handling as
 a snapshot will not change based on user input once it is taken.
 
 @see snapshot
 @return A new physical input profile with the duplicated state vector of the current physical input
 */
- (instancetype)capture API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

/**
 Sets the state vector of the physical input profile to a copy of the passed in physical input profile's state vector.
 
 @note If the controller's snapshot flag is set to NO, this method has no effect.
 @see GCController.snapshot
 */
- (void)setStateFromPhysicalInput:(GCPhysicalInputProfile *)physicalInput API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

/**
 Returns the primary alias of the GCControllerElement that a given physical input maps to.
 
 @discussion If the user were to map a physical press of the A button of their game controller to the B button, then
    -[GCPhysicalInputProfile  mappedElementAliasForPhysicalInputName: GCInputButtonA] would return GCInputButtonB.
    Note that mappings can change anytime your app is backgrounded, so make sure you update any relevant visuals when
    returning to foreground.
 
 @param inputName A GCInput string corresponding to the physical button you want the mapped element alias for.
 
 @returns A GCInput string corresponding to the primary alias of the GCControllerElement that a given physical button maps to, or nil if there is no mapping.
 */
- (NSString *)mappedElementAliasForPhysicalInputName:(NSString *)inputName API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));

/**
 Returns a set of GCInput strings corresponding to physical inputs that are mapped to a given GCControllerElement.
 
 @discussion If the user mapped the physical press of the A button, the B button, and the X button to the B button, then
    -[GCPhysicalInputProfile mappedPhysicalInputNamesForElementAlias: GCInputButtonB] would return  [GCInputButtonA, GCInputButtonB, GCInputButtonX].
    Note that mappings can change anytime your app is backgrounded, so make sure you update any relevant visuals when
    returning to foreground.
 
 @param elementAlias A GCInput string corresponding to an alias of the GCControllerElement you want the physical buttons for.
 
 @returns A set of GCInput strings corresponding to physical inputs that are mapped to a given GCControllerElement, or an empty set if there are no mappings.
 */
- (NSSet<NSString *> *)mappedPhysicalInputNamesForElementAlias:(NSString *)elementAlias API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));

@end

NS_ASSUME_NONNULL_END
