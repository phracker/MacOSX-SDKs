/*
 * SyncServices -- SyncServicesErrors.h
 * Copyright (c) 2006, Apple Computer, Inc.  All rights reserved.
 */

#import <Foundation/Foundation.h>

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

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

typedef enum {
	ISyncServerDisabledReasonNone = 1000,        // Returned when isEnabled has not been called or has returned YES.
	ISyncServerDisabledReasonByPreference,      // Returned if syncing has been disabled with a preference
	ISyncServerDisabledReasonSharedNetworkHome,// Returned if another sync server is running against a network home directory.
	ISyncServerDisabledReasonUnresponsive,	 // Returned if isEnabled has timed out messaging to the Sync Server  
	ISyncServerDisabledReasonUnknown,           // Returned if the Sync Server fails to respond because of an unexpected error.
} ISyncServerDisabledReason;



#endif


#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6
SYNCSERVICES_EXPORT NSString * const ISyncInvalidSchemaException;    // Raised when a client tries to register an invalid schema or schema extension.
SYNCSERVICES_EXPORT NSString * const ISyncInvalidArgumentsException; // Raised when the sync services API is passed bad or inconsistent arguments.
#endif
