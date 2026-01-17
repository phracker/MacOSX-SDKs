//
//  CKMarkNotificationsReadOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CloudKit/CKOperation.h>

NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKMarkNotificationsReadOperation : CKOperation

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithNotificationIDsToMarkRead:(NSArray /* CKNotificationID */ *)notificationIDs NS_DESIGNATED_INITIALIZER;

@property (nonatomic, copy) NSArray /* CKNotificationID */ *notificationIDs;

@property (nonatomic, copy) void (^markNotificationsReadCompletionBlock)(NSArray /* CKNotificationID */ *notificationIDsMarkedRead, NSError *operationError);

@end
