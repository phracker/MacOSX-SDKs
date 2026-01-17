//
//  EAAccessoryManager.h
//  ExternalAccessory
//
//  Copyright (c) 2008-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ExternalAccessory/ExternalAccessoryDefines.h> // EA_EXTERN

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, EABluetoothAccessoryPickerErrorCode) {
    EABluetoothAccessoryPickerAlreadyConnected,
	EABluetoothAccessoryPickerResultNotFound,
	EABluetoothAccessoryPickerResultCancelled,
	EABluetoothAccessoryPickerResultFailed
};

EA_EXTERN NSString *const EABluetoothAccessoryPickerErrorDomain;

typedef void(^EABluetoothAccessoryPickerCompletion)(NSError * __nullable error);

// EAAccessoryManager Notifications
EA_EXTERN NSString *const EAAccessoryDidConnectNotification __OSX_AVAILABLE_STARTING(__MAC_10_13,__IPHONE_3_0) __TVOS_AVAILABLE(10.0);
EA_EXTERN NSString *const EAAccessoryDidDisconnectNotification __OSX_AVAILABLE_STARTING(__MAC_10_13,__IPHONE_3_0) __TVOS_AVAILABLE(10.0);
// Keys in the EAAccessoryDidConnectNotification/EAAccessoryDidDisconnectNotification userInfo
EA_EXTERN NSString *const EAAccessoryKey __OSX_AVAILABLE_STARTING(__MAC_10_13,__IPHONE_3_0) __TVOS_AVAILABLE(10.0); // EAAccessory
EA_EXTERN NSString *const EAAccessorySelectedKey __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_6_0) __TVOS_AVAILABLE(10.0); // EAAccessory

@class EAAccessory;

__OSX_AVAILABLE_STARTING(__MAC_10_13,__IPHONE_3_0) @interface EAAccessoryManager : NSObject {
@private
    NSMutableArray *_connectedAccessories;
}

+ (EAAccessoryManager *)sharedAccessoryManager __OSX_AVAILABLE_STARTING(__MAC_10_13,__IPHONE_3_0) __TVOS_AVAILABLE(10.0);

- (void)showBluetoothAccessoryPickerWithNameFilter:(nullable NSPredicate *)predicate completion:(nullable EABluetoothAccessoryPickerCompletion)completion __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_6_0);

- (void)registerForLocalNotifications __OSX_AVAILABLE_STARTING(__MAC_10_13,__IPHONE_3_0) __TVOS_AVAILABLE(10.0);
- (void)unregisterForLocalNotifications __OSX_AVAILABLE_STARTING(__MAC_10_13,__IPHONE_3_0) __TVOS_AVAILABLE(10.0);

@property (nonatomic, readonly) NSArray<EAAccessory *> *connectedAccessories __OSX_AVAILABLE_STARTING(__MAC_10_13,__IPHONE_3_0) __TVOS_AVAILABLE(10.0);

@end

NS_ASSUME_NONNULL_END
