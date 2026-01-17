//
//  SRWristDetection.h
//  SensorKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SensorKit/SRDefines.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, SRWristLocation) {
    SRWristLocationLeft,
    SRWristLocationRight,
} API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos) API_UNAVAILABLE(tvos);

typedef NS_ENUM(NSInteger, SRCrownOrientation) {
    SRCrownOrientationLeft,
    SRCrownOrientationRight,
} API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos) API_UNAVAILABLE(tvos);

SR_EXTERN API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos, macos)
@interface SRWristDetection : NSObject
@property(readonly) BOOL onWrist;
@property(readonly) SRWristLocation wristLocation;
@property(readonly) SRCrownOrientation crownOrientation;
@end

NS_ASSUME_NONNULL_END
