//
//  GCExtendedGamepadSnapshot.h
//  GameController
//
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#import <GameController/GCExtendedGamepad.h>

NS_ASSUME_NONNULL_BEGIN

/**
 A GCExtendedGamepadSnapshot snapshot is a concrete GCExtendedGamepad implementation. It can be used directly in an
 application to implement controller input replays. It is also returned as the result of polling a controller.
 
 The current snapshotData is readily available to access as NSData. A developer can serialize this to any
 destination necessary using the NSData API.
 
 The data contains some version of a GCExtendedGamepadSnapShotData structure.

 @see -[GCExtendedGamepad saveSnapshot]
 */
API_DEPRECATED("Use the -[GCController controllerWithExtendedGamepad] method instead", macos(10.9, 10.15), ios(7.0, 13.0), tvos(9.0, 13.0))
@interface GCExtendedGamepadSnapshot : GCExtendedGamepad

@property (atomic, copy) NSData *snapshotData;

- (instancetype)initWithSnapshotData:(NSData *)data;
- (instancetype)initWithController:(GCController *)controller snapshotData:(NSData *)data;

@end


typedef NS_ENUM(NSInteger, GCExtendedGamepadSnapshotDataVersion) {
    GCExtendedGamepadSnapshotDataVersion1 = 0x0100,
    GCExtendedGamepadSnapshotDataVersion2 = 0x0101
} API_DEPRECATED("Use the -[GCController controllerWithExtendedGamepad] method instead", macos(10.15, 10.15), ios(13.0, 13.0), tvos(13.0, 13.0));

extern const GCExtendedGamepadSnapshotDataVersion GCCurrentExtendedGamepadSnapshotDataVersion API_DEPRECATED("Use the -[GCController controllerWithExtendedGamepad] method instead", macos(10.11, 10.15), ios(9.0, 13.0), tvos(9.0, 13.0));

#pragma pack(push, 1)
typedef struct {
    
#pragma mark - GCExtendedGamepadSnapshotDataVersion1+
    uint16_t version;
    uint16_t size;
    
    // Extended gamepad data
    // Axes in the range [-1.0, 1.0]
    float dpadX;
    float dpadY;
    
    // Buttons in the range [0.0, 1.0]
    float buttonA;
    float buttonB;
    float buttonX;
    float buttonY;
    float leftShoulder;
    float rightShoulder;
    
    // Axes in the range [-1.0, 1.0]
    float leftThumbstickX;
    float leftThumbstickY;
    float rightThumbstickX;
    float rightThumbstickY;
    
    // Buttons in the range [0.0, 1.0]
    float leftTrigger;
    float rightTrigger;
    
#pragma mark - GCExtendedGamepadSnapshotDataVersion2+
    // Boolean indicating whether the controller supports clickable thumbsticks (1) or not (0)
    BOOL supportsClickableThumbsticks API_AVAILABLE(macos(10.14.1), ios(12.1), tvos(12.1));
    
    // Left and right thumbstick clickable values (0, 1)
    BOOL leftThumbstickButton API_AVAILABLE(macos(10.14.1), ios(12.1), tvos(12.1));
    BOOL rightThumbstickButton API_AVAILABLE(macos(10.14.1), ios(12.1), tvos(12.1));
    
} GCExtendedGamepadSnapshotData API_DEPRECATED("Use the -[GCController controllerWithExtendedGamepad] method instead", macos(10.15, 10.15), ios(13.0, 13.0), tvos(13.0, 13.0));
#pragma pack(pop)

/**Fills out a snapshot from any compatible NSData source
 
 @return NO if data is nil, snapshotData is nil or the contents of data does not contain a compatible snapshot. YES for all other cases.
 */
BOOL GCExtendedGamepadSnapshotDataFromNSData(GCExtendedGamepadSnapshotData * _Nullable snapshotData, NSData * _Nullable data) API_DEPRECATED("Use the -[GCController controllerWithExtendedGamepad] method instead", macos(10.15, 10.15), ios(13.0, 13.0), tvos(13.0, 13.0));

/**Creates an NSData object from a snapshot.
 If the version and size is not set in the snapshot the data will automatically have the version GCCurrentExtendedGamepadSnapshotDataVersion and sizeof(GCExtendedGamepadSnapshotData) set as the values implicitly.
 
 @return nil if the snapshot is NULL, otherwise an NSData instance compatible with GCExtendedGamepadSnapshot.snapshotData
 */
NSData * _Nullable NSDataFromGCExtendedGamepadSnapshotData(GCExtendedGamepadSnapshotData * _Nullable snapshotData) API_DEPRECATED("Use the -[GCController controllerWithExtendedGamepad] method instead", macos(10.15, 10.15), ios(13.0, 13.0), tvos(13.0, 13.0));


#pragma mark - Deprecated Versioning System

#pragma pack(push)
typedef struct {
    // Standard information
    uint16_t version;   // 0x0100
    uint16_t size;      //sizeof(GCExtendedGamepadSnapShotDataV100) or larger
    
    // Extended gamepad data
    // Axes in the range [-1.0, 1.0]
    float dpadX;
    float dpadY;
    
    // Buttons in the range [0.0, 1.0]
    float buttonA;
    float buttonB;
    float buttonX;
    float buttonY;
    float leftShoulder;
    float rightShoulder;
    
    // Axes in the range [-1.0, 1.0]
    float leftThumbstickX;
    float leftThumbstickY;
    float rightThumbstickX;
    float rightThumbstickY;
    
    // Buttons in the range [0.0, 1.0]
    float leftTrigger;
    float rightTrigger;
    
} GCExtendedGamepadSnapShotDataV100 API_DEPRECATED("Use the -[GCController controllerWithExtendedGamepad] method instead", macos(10.9, 10.15), ios(7.0, 13.0), tvos(9.0, 13.0));
#pragma pack(pop)

/**Fills out a v100 snapshot from any compatible NSData source
 
 @return NO if data is nil, snapshotData is nil or the contents of data does not contain a compatible snapshot. YES for all other cases.
 */
BOOL GCExtendedGamepadSnapShotDataV100FromNSData(GCExtendedGamepadSnapShotDataV100 * _Nullable snapshotData, NSData * _Nullable data) API_DEPRECATED("Use the -[GCController controllerWithExtendedGamepad] method instead", macos(10.9, 10.15), ios(7.0, 13.0), tvos(9.0, 13.0));

/**Creates an NSData object from a v100 snapshot.
 If the version and size is not set in the snapshot the data will automatically have version 0x100 and sizeof(GCExtendedGamepadSnapShotDataV100) set as the values implicitly.
 
 @return nil if the snapshot is NULL, otherwise an NSData instance compatible with GCExtendedGamepadSnapshot.snapshotData
 */
NSData * _Nullable NSDataFromGCExtendedGamepadSnapShotDataV100(GCExtendedGamepadSnapShotDataV100 * _Nullable snapshotData) API_DEPRECATED("Use the -[GCController controllerWithExtendedGamepad] method instead", macos(10.9, 10.15), ios(7.0, 13.0), tvos(9.0, 13.0));

NS_ASSUME_NONNULL_END
