//
//  CKError.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CloudKit/CKDefines.h>

NS_ASSUME_NONNULL_BEGIN

CK_EXTERN NSString * const CKErrorDomain NS_AVAILABLE(10_10, 8_0);

CK_EXTERN NSString * const CKPartialErrorsByItemIDKey NS_AVAILABLE(10_10, 8_0);

/* If the server rejects a record save because it has been modified since the last time it was read, 
   a CKErrorServerRecordChanged error will be returned and it will contain versions of the record 
   in its userInfo dictionary. Apply your custom conflict resolution logic to the server record (CKServerRecordKey) 
   and attempt a save of that record. */
CK_EXTERN NSString * const CKRecordChangedErrorAncestorRecordKey NS_AVAILABLE(10_10, 8_0);
CK_EXTERN NSString * const CKRecordChangedErrorServerRecordKey NS_AVAILABLE(10_10, 8_0);
CK_EXTERN NSString * const CKRecordChangedErrorClientRecordKey NS_AVAILABLE(10_10, 8_0);

/* On CKErrorServiceUnavailable or CKErrorRequestRateLimited errors the userInfo dictionary 
   may contain a NSNumber instance that specifies the period of time in seconds after
   which the client may retry the request.
 */
CK_EXTERN NSString * const CKErrorRetryAfterKey NS_AVAILABLE(10_10, 8_0);

typedef NS_ENUM(NSInteger, CKErrorCode) {
    CKErrorInternalError           = 1,  /* CloudKit.framework encountered an error.  This is a non-recoverable error. */
    CKErrorPartialFailure          = 2,  /* Some items failed, but the operation succeeded overall */
    CKErrorNetworkUnavailable      = 3,  /* Network not available */
    CKErrorNetworkFailure          = 4,  /* Network error (available but CFNetwork gave us an error) */
    CKErrorBadContainer            = 5,  /* Un-provisioned or unauthorized container. Try provisioning the container before retrying the operation. */
    CKErrorServiceUnavailable      = 6,  /* Service unavailable */
    CKErrorRequestRateLimited      = 7,  /* Client is being rate limited */
    CKErrorMissingEntitlement      = 8,  /* Missing entitlement */
    CKErrorNotAuthenticated        = 9,  /* Not authenticated (writing without being logged in, no user record) */
    CKErrorPermissionFailure       = 10, /* Access failure (save or fetch) */
    CKErrorUnknownItem             = 11, /* Record does not exist */
    CKErrorInvalidArguments        = 12, /* Bad client request (bad record graph, malformed predicate) */
    CKErrorResultsTruncated        = 13, /* Query results were truncated by the server */
    CKErrorServerRecordChanged     = 14, /* The record was rejected because the version on the server was different */
    CKErrorServerRejectedRequest   = 15, /* The server rejected this request.  This is a non-recoverable error */
    CKErrorAssetFileNotFound       = 16, /* Asset file was not found */
    CKErrorAssetFileModified       = 17, /* Asset file content was modified while being saved */
    CKErrorIncompatibleVersion     = 18, /* App version is less than the minimum allowed version */
    CKErrorConstraintViolation     = 19, /* The server rejected the request because there was a conflict with a unique field. */
    CKErrorOperationCancelled      = 20, /* A CKOperation was explicitly cancelled */
    CKErrorChangeTokenExpired      = 21, /* The previousServerChangeToken value is too old and the client must re-sync from scratch */
    CKErrorBatchRequestFailed      = 22, /* One of the items in this batch operation failed in a zone with atomic updates, so the entire batch was rejected. */
    CKErrorZoneBusy                = 23, /* The server is too busy to handle this zone operation. Try the operation again in a few seconds. */
    CKErrorBadDatabase             = 24, /* Operation could not be completed on the given database. Likely caused by attempting to modify zones in the public database. */
    CKErrorQuotaExceeded           = 25, /* Saving a record would exceed quota */
    CKErrorZoneNotFound            = 26, /* The specified zone does not exist on the server */
    CKErrorLimitExceeded           = 27, /* The request to the server was too large. Retry this request as a smaller batch. */
    CKErrorUserDeletedZone         = 28, /* The user deleted this zone through the settings UI. Your client should either remove its local data or prompt the user before attempting to re-upload any data to this zone. */
} NS_ENUM_AVAILABLE(10_10, 8_0);

NS_ASSUME_NONNULL_END
