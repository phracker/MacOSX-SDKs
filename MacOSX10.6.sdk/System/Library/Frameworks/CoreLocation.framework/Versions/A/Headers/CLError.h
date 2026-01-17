
/*
 *  CLError.h
 *  CoreLocation
 *
 *  Copyright 2008 Apple Inc. All rights reserved.
 *
 */

#if ( !TARGET_OS_MAC || MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6 )

#import <Foundation/Foundation.h>


/*
 *  kCLErrorDomain
 *  
 *  Discussion:
 *    Error returned as the domain to NSError from CoreLocation.
 */
extern NSString *const kCLErrorDomain;

/*
 *  Error codes
 *  
 *  Discussion:
 *    Returned as code to NSError from CoreLocation.
 */
enum {
	kCLErrorLocationUnknown  = 0, // location is currently unknown, but CL will keep trying
	kCLErrorDenied // CL access has been denied (eg, user declined location use)
};

#endif
