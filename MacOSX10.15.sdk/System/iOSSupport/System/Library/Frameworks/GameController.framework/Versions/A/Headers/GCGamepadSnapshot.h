//
//  GCGamepadSnapshot.h
//  GameController
//
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#import <GameController/GameController.h>

NS_ASSUME_NONNULL_BEGIN

/**
 A GCGamepadSnapshot snapshot is a concrete GCGamepad implementation. It can be used directly in an
 application to implement controller input replays. It is also returned as the result API_DEPRECATED("GCGamepad has been deprecated, use GCExtendedGamepad instead", macos(10.9, 10.15), ios(7.0, 13.0), tvos(7.0, 13.0))of polling
 a controller.
 
 The current snapshotData is readily available to access as NSData. A developer can serialize this to any
 destination necessary using the NSData API.
 
 The data contains some version of a GCGamepadSnapShotData structure.
 
 @see -[GCGamepad saveSnapshot]
 */
API_DEPRECATED("GCGamepad has been deprecated, use GCExtendedGamepad instead", macos(10.9, 10.15), ios(7.0, 13.0), tvos(7.0, 13.0))
@interface GCGamepadSnapshot : GCGamepad
@property (atomic, copy) NSData *snapshotData;

- (instancetype)initWithSnapshotData:(NSData *)data;
- (instancetype)initWithController:(GCController *)controller snapshotData:(NSData *)data;

@end

#pragma pack(push, 1)
typedef struct {
    // Standard information
    uint16_t version; //0x0100
    uint16_t size;    //sizeof(GCGamepadSnapShotDataV100) or larger
    
    // Standard gamepad data
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
    
} GCGamepadSnapShotDataV100 API_DEPRECATED("GCGamepad has been deprecated, use GCExtendedGamepad instead", macos(10.9, 10.15), ios(7.0, 13.0), tvos(7.0, 13.0));
#pragma pack(pop)

/**Fills out a v100 snapshot from any compatible NSData source
 
 @return NO if data is nil, snapshotData is nil or the contents of data does not contain a compatible snapshot. YES for all other cases.
 */
BOOL GCGamepadSnapShotDataV100FromNSData(GCGamepadSnapShotDataV100 *__nullable snapshotData, NSData *__nullable data) API_DEPRECATED("GCGamepad has been deprecated, use GCExtendedGamepad instead", macos(10.9, 10.15), ios(7.0, 13.0), tvos(7.0, 13.0));

/**Creates an NSData object from a v100 snapshot.
 If the version and size is not set in the snapshot the data will automatically have version 0x100 and sizeof(GCGamepadSnapShotDataV100) set as the values implicitly.
 
 @return nil if the snapshot is NULL, otherwise an NSData instance compatible with GCGamepadSnapshot.snapshotData
 */
NSData *__nullable NSDataFromGCGamepadSnapShotDataV100(GCGamepadSnapShotDataV100 *__nullable snapshotData) API_DEPRECATED("GCGamepad has been deprecated, use GCExtendedGamepad instead", macos(10.9, 10.15), ios(7.0, 13.0), tvos(7.0, 13.0));

NS_ASSUME_NONNULL_END
