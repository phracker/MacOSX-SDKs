//
//  UNError.h
//  UserNotifications
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

extern NSString * const UNErrorDomain __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0) __OSX_AVAILABLE(10.14);

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
} __IOS_AVAILABLE(10.0) __TVOS_AVAILABLE(10.0) __WATCHOS_AVAILABLE(3.0) __OSX_AVAILABLE(10.14);
