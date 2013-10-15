/*
 * SyncServices -- SyncServicesErrors.h
 * Copyright (c) 2006, Apple Computer, Inc.  All rights reserved.
 */

#import <Foundation/Foundation.h>

#if MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_X_VERSION_10_5

#import <SyncServices/ISyncCommon.h>

// Predefined domain for errors from SyncServices APIs.
SYNCSERVICES_EXPORT NSString *const ISyncErrorDomain            AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

enum {
    ISyncSessionClientAlreadySyncingError =        100, // a sync session was requested for a client already participating in a session
    ISyncSessionUserCanceledSessionError =         101, // the user canceled a sync via the data change alert
    ISyncSessionDriverRegistrationError =          200, // an ISyncSessionDriver was unable to register a client
    ISyncSessionDriverPullFailureError =           201, // an ISyncSessionDriver failed an -[ISyncSession prepareToPullChangesForEntityNames:beforeDate:] call
	ISyncSessionDriverFatalError =			       300  // ISyncSessionDriver received a fatal error
};

#endif
