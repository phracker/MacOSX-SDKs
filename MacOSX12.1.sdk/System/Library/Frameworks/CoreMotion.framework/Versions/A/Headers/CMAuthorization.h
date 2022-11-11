/*
 *  CMAuthorization.h
 *  CoreMotion
 *
 *  Copyright (c) 2017 Apple Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>

/*
 *  CMAuthorizationStatus
 *
 *  Discussion:
 *      Represents the current motion authorization state.
 *
 *      CMAuthorizationStatusNotDetermined when the user has not been prompted yet.
 *      CMAuthorizationStatusRestricted when access is denied due to system-wide restrictions.
 *      CMAuthorizationStatusDenied when access is denied by the user.
 *      CMAuthorizationStatusAuthorized when access is authorized by the user.
 *
 */
typedef NS_ENUM(NSInteger, CMAuthorizationStatus) {
	CMAuthorizationStatusNotDetermined = 0,
	CMAuthorizationStatusRestricted,
	CMAuthorizationStatusDenied,
	CMAuthorizationStatusAuthorized
} API_AVAILABLE(ios(11.0), watchos(4.0));
