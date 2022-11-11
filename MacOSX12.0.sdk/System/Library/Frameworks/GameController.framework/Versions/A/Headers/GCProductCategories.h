//  
//  GCProductCategories.h
//  GameController
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <GameController/GCExtern.h>

/**
 A set of common values of -[GCDevice productCategory]. Check a device's' productCategory against these values to
 set appropriate UI elements based on what type of device is connected.
 
@see GCDevice.h
*/


/// Game Controller Product Categories

GAMECONTROLLER_EXTERN NSString *const GCProductCategoryDualSense API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));
GAMECONTROLLER_EXTERN NSString *const GCProductCategoryDualShock4 API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));
GAMECONTROLLER_EXTERN NSString *const GCProductCategoryMFi API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));
GAMECONTROLLER_EXTERN NSString *const GCProductCategoryXboxOne API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));



/// Remote Product Categories

/// The Siri Remote (1st generation), or Apple TV Remote (1st generation), was first introduced in 2015. It features a Touch surface for touch navigation, and supports device motion.
GAMECONTROLLER_EXTERN NSString *const GCProductCategorySiriRemote1stGen API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));

/// The Siri Remote (2nd generation), or Apple TV Remote (2nd generation), was first introduced in 2021. It features a touch-enabled clickpad for navigation.
GAMECONTROLLER_EXTERN NSString *const GCProductCategorySiriRemote2ndGen API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));

/// Users can use Apple TV Remote controls in Control Center on an iOS or iPadOS device.
GAMECONTROLLER_EXTERN NSString *const GCProductCategoryControlCenterRemote API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));

/// The Universal Electronics remote is an infrared and Bluetooth Low Energy remote designed to work with the Apple TV.
GAMECONTROLLER_EXTERN NSString *const GCProductCategoryUniversalElectronicsRemote API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));

/**
 If multiple remotes have been combined into one, the device will have the GCProductCategoryCoalescedRemote product category.
 
 @discussion By default, the Game Controller framework will try to coalesce, or combine, the physical Apple TV Remote and the
 virtual Control Center remote and treat them as a single GCDevice instance. By setting GCSupportsMultipleMicroGamepads in your
 app's plist to true, you can disable this behavior.
*/
GAMECONTROLLER_EXTERN NSString *const GCProductCategoryCoalescedRemote API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));



/// Keyboards and Mice Product Categories

GAMECONTROLLER_EXTERN NSString *const GCProductCategoryMouse API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));
GAMECONTROLLER_EXTERN NSString *const GCProductCategoryKeyboard API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));
