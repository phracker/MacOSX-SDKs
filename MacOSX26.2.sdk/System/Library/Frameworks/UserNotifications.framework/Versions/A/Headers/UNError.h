//
//  UNError.h
//  UserNotifications
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

extern NSString * const UNErrorDomain API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0), tvos(10.0));

typedef NS_ENUM(NSInteger, UNErrorCode) {
    UNErrorCodeNotificationsNotAllowed = 1,
    
    UNErrorCodeAttachmentInvalidURL = 100,
    UNErrorCodeAttachmentUnrecognizedType,
    UNErrorCodeAttachmentInvalidFileSize,
    UNErrorCodeAttachmentNotInDataStore,
    UNErrorCodeAttachmentMoveIntoDataStoreFailed,
    UNErrorCodeAttachmentCorrupt,
    
    UNErrorCodeNotificationInvalidNoDate = 1400,
    UNErrorCodeNotificationInvalidNoContent,
    
    UNErrorCodeContentProvidingObjectNotAllowed = 1500,
    UNErrorCodeContentProvidingInvalid,
    
    UNErrorCodeBadgeInputInvalid = 1600,
} API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0), tvos(10.0));
