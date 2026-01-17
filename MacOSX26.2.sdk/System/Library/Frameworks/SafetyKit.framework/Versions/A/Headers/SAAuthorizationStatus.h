//
//  SAAuthorizationStatus.h
//  SafetyKit
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*
 *  SAAuthorizationStatus
 *
 *  Discussion:
 *      Represents the current motion authorization state.
 *
 *      SAAuthorizationStatusNotDetermined when the user has not been prompted yet.
 *      SAAuthorizationStatusDenied when access is denied by the user.
 *      SAAuthorizationStatusAuthorized when access is authorized by the user.
 *
 */
API_AVAILABLE(ios(16.0), macos(13.0), watchos(10.1)) API_UNAVAILABLE(tvos)
typedef NS_ENUM(NSInteger, SAAuthorizationStatus) {
    SAAuthorizationStatusNotDetermined = 0,
    SAAuthorizationStatusDenied,
    SAAuthorizationStatusAuthorized
};

NS_ASSUME_NONNULL_END
