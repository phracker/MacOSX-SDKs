//
//  CKError.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CloudKit/CKDefines.h>

NS_ASSUME_NONNULL_BEGIN

CK_EXTERN NSString * const CKErrorDomain API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0));

/* When a CKErrorPartialFailure happens this key will be set in the error's userInfo dictionary.
   The value of this key will be a dictionary, and the values will be errors for individual items with the keys being the item IDs that failed. */ 
CK_EXTERN NSString * const CKPartialErrorsByItemIDKey API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0));

/* If the server rejects a record save because it has been modified since the last time it was read, 
   a CKErrorServerRecordChanged error will be returned and it will contain versions of the record 
   in its userInfo dictionary. Apply your custom conflict resolution logic to the server record (CKServerRecordKey) 
   and attempt a save of that record. */
CK_EXTERN NSString * const CKRecordChangedErrorAncestorRecordKey API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0));
CK_EXTERN NSString * const CKRecordChangedErrorServerRecordKey API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0));
CK_EXTERN NSString * const CKRecordChangedErrorClientRecordKey API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0));

/* On CKErrorServiceUnavailable or CKErrorRequestRateLimited errors the userInfo dictionary 
   may contain a NSNumber instance that specifies the period of time in seconds after
   which the client may retry the request.
 */
CK_EXTERN NSString * const CKErrorRetryAfterKey API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0));

typedef NS_ENUM(NSInteger, CKErrorCode) {
    CKErrorInternalError                  = 1,  /* CloudKit.framework encountered an error.  This is a non-recoverable error. */
    CKErrorPartialFailure                 = 2,  /* Some items failed, but the operation succeeded overall. Check CKPartialErrorsByItemIDKey in the userInfo dictionary for more details. */
    CKErrorNetworkUnavailable             = 3,  /* Network not available */
    CKErrorNetworkFailure                 = 4,  /* Network error (available but CFNetwork gave us an error) */
    CKErrorBadContainer                   = 5,  /* Un-provisioned or unauthorized container. Try provisioning the container before retrying the operation. */
    CKErrorServiceUnavailable             = 6,  /* Service unavailable */
    CKErrorRequestRateLimited             = 7,  /* Client is being rate limited */
    CKErrorMissingEntitlement             = 8,  /* Missing entitlement */
    CKErrorNotAuthenticated               = 9,  /* Not authenticated (writing without being logged in, no user record) */
    CKErrorPermissionFailure              = 10, /* Access failure (save, fetch, or shareAccept) */
    CKErrorUnknownItem                    = 11, /* Record does not exist */
    CKErrorInvalidArguments               = 12, /* Bad client request (bad record graph, malformed predicate) */
    CKErrorResultsTruncated API_DEPRECATED("Will not be returned", macos(10.10, 10.12), ios(8.0, 10.0), tvos(9.0, 10.0), watchos(3.0, 3.0)) = 13,
    CKErrorServerRecordChanged            = 14, /* The record was rejected because the version on the server was different */
    CKErrorServerRejectedRequest          = 15, /* The server rejected this request.  This is a non-recoverable error */
    CKErrorAssetFileNotFound              = 16, /* Asset file was not found */
    CKErrorAssetFileModified              = 17, /* Asset file content was modified while being saved */
    CKErrorIncompatibleVersion            = 18, /* App version is less than the minimum allowed version */
    CKErrorConstraintViolation            = 19, /* The server rejected the request because there was a conflict with a unique field. */
    CKErrorOperationCancelled             = 20, /* A CKOperation was explicitly cancelled */
    CKErrorChangeTokenExpired             = 21, /* The previousServerChangeToken value is too old and the client must re-sync from scratch */
    CKErrorBatchRequestFailed             = 22, /* One of the items in this batch operation failed in a zone with atomic updates, so the entire batch was rejected. */
    CKErrorZoneBusy                       = 23, /* The server is too busy to handle this zone operation. Try the operation again in a few seconds. */
    CKErrorBadDatabase                    = 24, /* Operation could not be completed on the given database. Likely caused by attempting to modify zones in the public database. */
    CKErrorQuotaExceeded                  = 25, /* Saving a record would exceed quota */
    CKErrorZoneNotFound                   = 26, /* The specified zone does not exist on the server */
    CKErrorLimitExceeded                  = 27, /* The request to the server was too large. Retry this request as a smaller batch. */
    CKErrorUserDeletedZone                = 28, /* The user deleted this zone through the settings UI. Your client should either remove its local data or prompt the user before attempting to re-upload any data to this zone. */
    CKErrorTooManyParticipants            API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0)) = 29, /* A share cannot be saved because there are too many participants attached to the share */
    CKErrorAlreadyShared                  API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0)) = 30, /* A record/share cannot be saved, doing so would cause a hierarchy of records to exist in multiple shares */
    CKErrorReferenceViolation             API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0)) = 31, /* The target of a record's parent or share reference was not found */
    CKErrorManagedAccountRestricted       API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0)) = 32, /* Request was rejected due to a managed account restriction */
    CKErrorParticipantMayNeedVerification API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0)) = 33, /* Share Metadata cannot be determined, because the user is not a member of the share.  There are invited participants on the share with email addresses or phone numbers not associated with any iCloud account. The user may be able to join the share if they can associate one of those email addresses or phone numbers with their iCloud account via the system Share Accept UI. Call UIApplication's openURL on this share URL to have the user attempt to verify their information. */
    CKErrorServerResponseLost             API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0)) = 34, /* The server received and processed this request, but the response was lost due to a network failure.  There is no guarantee that this request succeeded.  Your client should re-issue the request (if it is idempotent), or fetch data from the server to determine if the request succeeded. */
} API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0));

NS_ASSUME_NONNULL_END
