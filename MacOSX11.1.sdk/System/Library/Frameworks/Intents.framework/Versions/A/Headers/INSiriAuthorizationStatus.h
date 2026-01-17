//
//  INSiriAuthorizationStatus.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#ifndef INSiriAuthorizationStatus_h
#define INSiriAuthorizationStatus_h

#import <Foundation/Foundation.h>

/*
 *  INSiriAuthorizationStatus
 *
 *  Discussion:
 *      Represents the current authorization state of the application.
 *
 */
typedef NS_ENUM(NSInteger, INSiriAuthorizationStatus) {
    // User has not yet made a choice with regards to this application.
    INSiriAuthorizationStatusNotDetermined = 0,
    
    // This application is not authorized to use Siri services.  Due
    // to active restrictions on Siri services, the user cannot change
    // this status, and may not have personally denied authorization.
    INSiriAuthorizationStatusRestricted,
    
    // User has explicitly denied authorization for this application, or
    // Siri services are disabled in Settings.
    INSiriAuthorizationStatusDenied,
    
    // User has authorized this application to use Siri services.
    INSiriAuthorizationStatusAuthorized
} API_AVAILABLE(ios(10.0), watchos(3.2), tvos(14.0)) API_UNAVAILABLE(macos);

#endif /* INSiriAuthorizationStatus_h */
