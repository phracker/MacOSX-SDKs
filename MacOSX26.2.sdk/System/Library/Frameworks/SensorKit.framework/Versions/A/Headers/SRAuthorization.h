//
//  SRAuthorization.h
//  SensorKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, SRAuthorizationStatus) {
    /// User has not yet made a choice regarding this application
    SRAuthorizationStatusNotDetermined = 0,

    /// User has granted authorization to this application
    SRAuthorizationStatusAuthorized,

    /// User has denied authorization to this application or
    /// data collection is disabled in Settings.
    SRAuthorizationStatusDenied,
} API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos, visionos) API_UNAVAILABLE(tvos);
