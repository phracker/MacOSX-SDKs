//
//  SystemHealthManager.h
//  SystemHealthManager
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//
#import <Foundation/Foundation.h>

typedef NS_ENUM(uint64_t, SHComponentType) {
    SHComponentTypeBattery = 0,
    SHComponentTypeDisplay = 1,
    SHComponentTypeCamera = 2,
    SHComponentTypeWifi = 3,
    SHComponentTypeSpeaker = 4,
    SHComponentTypeBluetooth = 5,
    SHComponentTypeCellular = 6,
    SHComponentTypeNFC = 7,
    SHComponentTypeUWB = 8,
    SHComponentTypeTrueDepthIR = 9,
    SHComponentTypeRCameraFail = 10,
    SHComponentTypeAudioCodec = 11,
    SHComponentTypeTouchID = 12,
    // Add new components above
    SHComponentAlertType_Count,
};

typedef NS_ENUM(uint64_t, SHComponentStatus) {
    SHComponentStatusNotAvailable = 0,
    SHComponentStatusHardwarePass = 1,
    SHComponentStatusHardwareFail = 2,

    // Add new status above
    SHComponentStatus_Count,
};

__attribute__((visibility("default")))
@interface SystemHealthManager : NSObject

/// registerComponentHealthFor
/// @discussion asynchronous call, returns whether or not the data collection notice for the provided component should be displayed
- (void) postComponentStatusEventFor:(SHComponentType)component
                              status:(SHComponentStatus)status
                           withReply:(void (^)(BOOL success, NSError *error)) reply;

@end
